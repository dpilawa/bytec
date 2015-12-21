; Homebuilt 16-bit Computer OS/Monitor
; Dawid Pilawa (C) 2011, 2012
;
; RS/232 driver routines
;
; --------------------------------------------------------------

; defines
; --------------------------------------------------------------

REG_UART_RBR 	equ 0x00	; Receiver Buffer Register (DLAB=0)
REG_UART_THR 	equ 0x00	; Tramsmitter Holding Register (DLAB=0)
REG_UART_DLL 	equ 0x00	; Divisor Latch LS (DLAB=1)
REG_UART_DLM 	equ 0x01	; Divisor Latch MS (DLAB=1)
REG_UART_IER	equ 0x01	; Interrupt Enable Register (DLAB=0)
REG_UART_IIR	equ 0x02	; Interrupt Identification Register
REG_UART_FCR	equ 0x02	; FIFO Control Register
REG_UART_LCR	equ 0x03	; Line Control Register
REG_UART_MCR	equ 0x04	; Modem Control Register
REG_UART_LSR	equ 0x05	; Line Status Register
REG_UART_MSR	equ 0x06	; Modem Status Register
REG_UART_SCR	equ 0x07	; Scratch Register

; text segment
; --------------------------------------------------------------

        .text

; exported functions

_krn_syscall_uart_sel:
        call _krn_uart_sel
        iret

_krn_syscall_uart_detect:
        call _krn_uart_detect
        st (sp:IRQ_REG_AL), al
        iret

_krn_syscall_uart_init:
        call _krn_uart_init
        iret

_krn_syscall_uart_setmcr:
        call _krn_uart_setmcr
        iret

_krn_syscall_uart_putc:
        call _krn_uart_putc
        iret

_krn_syscall_uart_getc:
        call _krn_uart_getc
        st (sp:IRQ_REG_AL), al        
        iret

_krn_syscall_uart_pstr:
        call _krn_uart_pstr
        iret

_krn_syscall_uart_pstrnl:
        call _krn_uart_pstrnl
        iret

_krn_syscall_uart_gstr:
        call _krn_uart_gstr
        iret

; kernel functions

; --------------------------------------------------------------
; KRN_UART_SEL
; 
; Select current UART
;
; Input:
;   AL - UART number (0x00 or 0x01)
; Output:
;	None
_krn_uart_sel:
		push dp
		push al
        ld dp, uartsel
        and al, 0x01				; assure either 0 or 1 is in AL
        st (dp), al
        pop al
        pop dp
        ret
        
; --------------------------------------------------------------
; KRN_UART_DETECT
;
; Detect UART card
;
; Input:
;   None
; Output:
;	AL - detection result (0x01 if found, 0x00 otherwise)
_krn_uart_detect:
		push dp
        call __krn_uart_seldp
        ld al, 0b10101010           ; check if 16550's scratch register usable
        st (dp:REG_UART_SCR), al
        ld al, (dp:REG_UART_SCR)
        cmp al, 0b10101010
        jne krn_uart_detect_nfound
        ld al, 0b01010101
        st (dp:REG_UART_SCR), al
        ld al, (dp:REG_UART_SCR)
        cmp al, 0b01010101
        jne krn_uart_detect_nfound
        ld al, 1
        jmp krn_uart_detect_end
krn_uart_detect_nfound:
        ld al, 0
krn_uart_detect_end:
        pop dp
        ret

; --------------------------------------------------------------
; KRN_UART_INIT
; 
; Initialize current UART
;
; Input:
;   None
; Output:
;	None
_krn_uart_init:
		push dp
		push a
        call __krn_uart_seldp
        ld al, 0x80                 ; divisor latch access
        st (dp:REG_UART_LCR), al
        ld a, 0x0600            	; 19200 baud
        st (dp:REG_UART_DLL), ah
        st (dp:REG_UART_DLM), al
        ld al, 0x03                 ; 8N1, buffer access
        st (dp:REG_UART_LCR), al     
        ld al, 0xc7                 ; enable FIFO, clear buffers
        st (dp:REG_UART_FCR), al
        ld al, 0x09                 ; enable UART interrupts (received data available, modem status)
        st (dp:REG_UART_IER), al        
        pop a
        pop dp
        ret

; --------------------------------------------------------------
; KRN_UART_SETMCR
; 
; Set MCR register of current UART
;
; Input:
;   AL - MCR register value
; Output:
;	None
_krn_uart_setmcr:
		push dp
        call __krn_uart_seldp
        st (dp:REG_UART_MCR), al
        pop dp
        ret

; --------------------------------------------------------------
; KRN_UART_PUTC
; 
; Write character (1 byte) to current UART
;
; Input:
;   AL - value to send
; Output:
;	None
_krn_uart_putc:
		push dp
		push a
		push x
		mov al, msw
		push al
        ld dp, uartsel              ; determine buffer pointer
        ld ah, (dp:0)
        cmp ah, 0
        jne krn_uart_putc_s1
krn_uart_putc_s0:
        ld dp, uart0tbuf
        jmp krn_uart_putc_write
krn_uart_putc_s1:
        ld dp, uart1tbuf
krn_uart_putc_write:
        cli                         ; disable interrupts (critical section)
        ld ah, (dp:255+3)
        cmp ah, 0xff
        je krn_uart_putc_wait       ; buffer full, wait until empty
        cmp ah, 0x00
        je krn_uart_putc_fifo       ; buffer empty, write directly to fifo
        ld a, (dp:255+1)
        add al, 1
        st (dp:255+1), a
        cmp al, (dp:255+1)          
        jne krn_uart_putc_tbnfull
        ld ah, 0xff                 ; set buffer full flag (0xff)
        st (dp:255+3), ah
        jmp krn_uart_putc_tbput
krn_uart_putc_tbnfull:
        ld ah, 0x01                 ; unset buffer empty flag
        st (dp:255+3), ah        
krn_uart_putc_tbput:        
        sub al, 1
        and a, 0x00ff
        mov x, a
        ld al, (sp:5)
        st (dp:x), al
        jmp krn_uart_putc_end
krn_uart_putc_fifo:
		push dp
        call __krn_uart_seldp
        ld ah, 0x10                 ; check if peer allows to send (CTS), otherwise copy char to buffer
        and ah, (dp:REG_UART_MSR)
        pop dp
        jz krn_uart_putc_write 
        call __krn_uart_seldp
krn_uart_putc_waitthre:
        ld ah, 0x20                 ; wait until FIFO ready to accept next character (THRE empty)
        and ah, (dp:REG_UART_LSR)
        jz krn_uart_putc_waitthre
krn_uart_putc_send:
		ld al, (sp:4)
        st (dp:REG_UART_THR), al    ; transmit
krn_uart_putc_end:
		pop al                      ; restore interrupts flag (end critical section)
        mov msw, al
        pop x
        pop a
        pop dp
        ret
krn_uart_putc_wait:
        ld a, (sp)	                ; temporarily restore interrupts flag
        mov msw, al
        jmp krn_uart_putc_write
        
; --------------------------------------------------------------
; KRN_UART_GETC
; 
; Read character (1 byte) from current UART
;
; Input:
;   None
; Output:
;	AL - received value
_krn_uart_getc:
		push dp
		push x
        mov al, msw
        push al
        ld dp, uartsel				; determine buffer address
        ld al, (dp:REG_UART_RBR)
        cmp al, 0
        jne krn_uart_getc_s1
krn_uart_getc_s0:
        ld dp, uart0rbuf
        jmp krn_uart_getc_read
krn_uart_getc_s1:
        ld dp, uart1rbuf        
krn_uart_getc_read:
        cli                         ; disable interrupts
        ld al, (dp:255+3)           ; wait if buffer empty
        cmp al, 0x00
        je krn_uart_getc_wait                           
        ld a, (dp:255+1)            ; set buffer pointers
        add ah, 1
        st (dp:255+1), a
        cmp ah, (dp:255+2)
        jne krn_uart_getc_nempty
        ld al, 0x00                 ; set buffer empty flag (0x00)
        st (dp:255+3), al
        jmp krn_uart_getc_readbuf
krn_uart_getc_nempty:
        ld al, 0xfe                 ; unset buffer full flag
        st (dp:255+3), al        
krn_uart_getc_readbuf:
        xor a, a                    ; compute buffer offset
        ld al, (dp:255+1)
        sub al, 1
        mov x,  a
		pop al                      ; restore interrupts flag
        mov msw, al
        ld al, (dp:x)				; store result
        pop x
        pop dp                      
        ret
krn_uart_getc_wait:
        ld a, (sp)	                ; temporarily restore interrupts flag
        mov msw, al
        jmp krn_uart_getc_read

; --------------------------------------------------------------
; KRN_UART_PSTR
; 
; Write null terminated string to current UART
;
; Input:
;   DP - address of string
; Output:
;	None
_krn_uart_pstr:
		push x
		push al
        xor x, x
krn_uart_pstrloop:
        ld al, (dp:x)
        cmp al, 0
        je krn_uart_pstrend
        call _krn_uart_putc
        inc x
        jmp krn_uart_pstrloop
krn_uart_pstrend:
		pop al
		pop x
        ret

; --------------------------------------------------------------
; KRN_UART_PSTRNL
; 
; Write null terminated string with newline to current UART
;
; Input:
;   DP - address of string
; Output:
;	None
_krn_uart_pstrnl:
		push dp
        call _krn_uart_pstr
        ld dp, vt100endl
        call _krn_uart_pstr
        pop dp
        ret

; --------------------------------------------------------------
; KRN_UART_GSTR
; 
; Read string from current UART (read until RETURN)
;
; Input:
;   DP - buffer address
; Output:
;	None
_krn_uart_gstr:
		push x
		push al
        push dp                     ; store original pointer
_krn_uart_gstr_empty:
        xor x, x
_krn_uart_gstr_loop:
        call _krn_uart_getc
        cmp al, 0x0d                ; check for RETURN
        je _krn_uart_gstr_end
        cmp al, 127                 ; check for DEL
        jne _krn_uart_gstr_nodel
		dec x
        jn _krn_uart_gstr_empty
        call _krn_uart_putc			; echo character (DEL)
        jmp _krn_uart_gstr_loop
_krn_uart_gstr_nodel:
        st (dp:x), al               ; store and echo character
        inc x
        call _krn_uart_putc
        jmp _krn_uart_gstr_loop
_krn_uart_gstr_end:
        ld al, 0x00                 ; end string with 0x00
        st (dp:x), al
        ld dp, vt100endl            ; echo newline
        call _krn_uart_pstr
        pop dp                      ; retrieve original pointer
        pop al
        pop x
        ret

; helper routines

; --------------------------------------------------------------
; Set DP to base address of current UART
__krn_uart_seldp:
        push al
        ld dp, uartsel
        ld al, (dp)
        cmp al, 0
        jne krn_uart_seldp_uart1
krn_uart_seldp_uart0:        
        ld dp, REG_UART0
        jmp krn_uart_seldp_end
krn_uart_seldp_uart1:  
        ld dp, REG_UART1
krn_uart_seldp_end:
        pop al
        ret

; interrupt service routines

; --------------------------------------------------------------
; UART interrupt service routine
define(`UART_MACRO', `
uart$1isr_:
        ld dp, REG_UART$1
        ld al, (dp:2)
        and al, 0x07
uart$1rda:
        cmp al, 0x04
        jne uart$1msr
        
uart$1recv:
        ld dp, uart$1rbuf           ; check if there is space in receiver buffer
        ld al, (dp:255+3)
        cmp al, 0xff
        je uart$1rtsoff             ; exit if no space
uart$1recvbuf:
        ld a, (dp:255+1)            ; set new buffer pointers
        add al, 1
        st (dp:255+1), a        
        cmp al, (dp:255+1)          
        jne uart$1rnfull
        ld ah, 0xff                 ; set buffer full flag (0xff)
        st (dp:255+3), ah
        jmp uart$1read
uart$1rnfull:
        ld ah, 0x01                 ; unset buffer empty flag
        st (dp:255+3), ah        
uart$1read:        
        sub al, 1                   ; compute buffer offset            
        and a, 0x00ff
        mov x, a              
        ld dp, REG_UART$1           ; read char from fifo
        ld al, (dp)
        ld ah, (dp:5)               ; read RDA status
        ld dp, uart$1rbuf           ; store in buffer
        st (dp:x), al               ; x contains buffer offset
        and ah, 0x01                ; check for more data in fifo (RDA)
        jnz uart$1recv
uart$1rtson:
        ld dp, REG_UART$1           ; FIFO is empty, toggle /RTS low
        ld al, 0x02                 
        st (dp:4), al
        jmp uart$1end
uart$1rtsoff:
        ld dp, REG_UART$1           ; receiver buffer full, toggle /RTS high (disallow peer to send)
        ld al, 0x00
        st (dp:4), al        
        jmp uart$1end

        
uart$1msr:
        cmp al, 0x00                ; modem status register interrupt, push out data from transmitter buffer
        jne uart$1end
        ld al, 0x01                 ; check CTS delta
        and al, (dp:6)
        jz uart$1end
uart$1tx:
        ld ah, 0x10                 ; check if peer allows to send (CTS), otherwise exit
        and ah, (dp:6)
        jz uart$1end
        ld dp, uart$1tbuf           ; get character from buffer
        ld al, (dp:255+3)           ; do nothing if empty
        cmp al, 0x00
        je uart$1end
        ld a, (dp:255+1)            ; set buffer pointers
        add ah, 1
        st (dp:255+1), a
        cmp ah, (dp:255+2)
        jne uart$1tnempty
        ld al, 0x00                 ; set buffer empty flag (0x00)
        st (dp:255+3), al
        jmp uart$1write
uart$1tnempty:
        ld al, 0xfe                 ; unset buffer full flag
        st (dp:255+3), al        
uart$1write:        
        xor a, a
        ld al, (dp:255+1)
        sub al, 1
        mov x, a
        ld ah, (dp:x)               ; character is in AH
uart$1wthre:        
        ld dp, REG_UART$1           ; wait until transmitter holding register empty
        ld al, 0x20
        and al, (dp:5)
        jz uart$1wthre
        st (dp:0), ah               ; transmit
        jmp uart$1tx                ; loop transmit


uart$1end:
        iret
')

        UART_MACRO(`0')
        UART_MACRO(`1')

; data segment
; --------------------------------------------------------------
        
        .data

; VT100 terminal control codes

vt100clrscr db 0x1b, '[2J', 0
vt100endl   db 0x1b, 'E', 0
vt100scroll db 0x1b, '[r', 0 
vt100del    db 0x1b, '^?', 0
vt100inv    db 0x1b, '[7m', 0
vt100uline  db 0x1b, '[4m', 0
vt100bold   db 0x1b, '[1m', 0
vt100norm   db 0x1b, '[0m', 0

vt100red    db 0x1b, '[0;31;0m', 0

; UART buffers

uartsel     db 0x00                         ; selected UART
uart0rbuf   db 0x00:256, 0x00, 0x00, 0x00   ; UART0 cyclic receive buffer
uart1rbuf   db 0x00:256, 0x00, 0x00, 0x00   ; UART1 cyclic receive buffer
uart0tbuf   db 0x00:256, 0x00, 0x00, 0x00   ; UART0 cyclic transmit buffer
uart1tbuf   db 0x00:256, 0x00, 0x00, 0x00   ; UART1 cyclic transmit buffer
