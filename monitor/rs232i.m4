; Homebuilt 16-bit Computer OS/Monitor
; Dawid Pilawa (C) 2015
;
; RS/232 driver routines
;
; --------------------------------------------------------------

; external symbols
; --------------------------------------------------------------

.global ___kern_rs232_uart0isr
.global ___kern_rs232_uart1isr

.extern ___kern_rs232_uart0rbuf
.extern ___kern_rs232_uart0tbuf
.extern ___kern_rs232_uart1rbuf
.extern ___kern_rs232_uart1tbuf

; constants
; --------------------------------------------------------------

.const #REG_UART0 0x1000    ; UART0 base address
.const #REG_UART1 0x1010    ; UART1 base address

.const #REG_UART_RBR 0x00	; Receiver Buffer Register (DLAB=0)
.const #REG_UART_THR 0x00	; Tramsmitter Holding Register (DLAB=0)
.const #REG_UART_DLL 0x00	; Divisor Latch LS (DLAB=1)
.const #REG_UART_DLM 0x01	; Divisor Latch MS (DLAB=1)
.const #REG_UART_IER 0x01	; Interrupt Enable Register (DLAB=0)
.const #REG_UART_IIR 0x02	; Interrupt Identification Register
.const #REG_UART_FCR 0x02	; FIFO Control Register
.const #REG_UART_LCR 0x03	; Line Control Register
.const #REG_UART_MCR 0x04	; Modem Control Register
.const #REG_UART_LSR 0x05	; Line Status Register
.const #REG_UART_MSR 0x06	; Modem Status Register
.const #REG_UART_SCR 0x07	; Scratch Register

; text segment
; --------------------------------------------------------------

        .text

; interrupt service routines

; --------------------------------------------------------------
; UART interrupt service routine
define(`UART_MACRO', `
___kern_rs232_uart$1isr:
        ld a, #REG_UART$1
        mov dp, a
        
        ld al, (dp:2)
        and al, 0x07
uart$1rda:
        cmp al, 0x04
        jne uart$1msr
        
uart$1recv:
        ld a, ___kern_rs232_uart$1rbuf           ; check if there is space in receiver buffer
        mov dp, a
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
        ld a, #REG_UART$1           ; read char from fifo
        mov dp, a
        ld al, (dp:0)
        ld ah, (dp:5)               ; read RDA status
        ld y, ___kern_rs232_uart$1rbuf           ; store in buffer
        add y, x
        st (y:0), al              
        and ah, 0x01                ; check for more data in fifo (RDA)
        jnz uart$1recv
uart$1rtson:
        ld a, #REG_UART$1           ; FIFO is empty, toggle /RTS low
        mov dp, a
        ld al, 0x02                 
        st (dp:4), al
        jmp uart$1end
uart$1rtsoff:
        ld a, #REG_UART$1           ; receiver buffer full, toggle /RTS high (disallow peer to send)
        mov dp, a
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
        ld a, ___kern_rs232_uart$1tbuf           ; get character from buffer
        mov dp, a
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
        ld a, 0
        ld al, (dp:255+1)
        sub al, 1
        ld x, ___kern_rs232_uart$1tbuf
        add x, a
        ld ah, (x:0)               ; character is in AH
uart$1wthre:        
        ld a, #REG_UART$1           ; wait until transmitter holding register empty
        mov dp, a
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

