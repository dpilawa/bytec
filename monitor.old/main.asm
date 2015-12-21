; Homebuilt 16-bit Computer OS/Monitor
; Dawid Pilawa (C) 2011, 2012
; --------------------------------------------------------------

        .data org 0x3000
        .text org 0x0000

        jmp __krn_start

        include(kern_defs.asm)
        include(kern_shell.asm)
        include(kern_rs232.asm)
        include(kern_rtc.asm)
        include(kern_ide.asm)
        include(kern_util.asm)

; Source code (text)
; --------------------------------------------------------------

        .text

; initialize kernel

__krn_start:

; initialize memory banks
    
        ld dp, REG_CODEPAGE0
        ld al, 0x00
        st (dp), al
        
        ld dp, REG_CODEPAGE1
        ld al, 0x01
        st (dp), al       

; copy OS data segment from ROM to RAM and set data banks
        
        ld dp, REG_DATAPAGE0
        ld al, 0x04
        st (dp), al

        ld dp, REG_DATAPAGE1
        ld al, 0x03		
        st (dp), al        
        
        ld x, KRN_MEM_DATA
romcopy:
        ld y, (x:0x8000)
        st (x:0), y
        inc x
        inc x
        mov a, x
        cmp a, 0x8000
        jne romcopy

        ld dp, REG_DATAPAGE0
        ld al, 0x04
        st (dp), al

        ld dp, REG_DATAPAGE1
        ld al, 0x05
        st (dp), al                
                
; setup stack

        ld sp, 0x8000   ; first stack entry will be 0x7fff
        
; initialize interrupt vector
        
        ; IRQ 0
        ld dp, KRN_MEM_IVEC
        ld a, __invalidisr
        st (dp), a
        ; IRQ 1
        ld dp, KRN_MEM_IVEC+0x01*2
        ld a, ideisr_
        st (dp), a
        ; UART0
        ld dp, KRN_MEM_IVEC+0x02*2
        ld a, uart0isr_
        st (dp), a
        ; UART1
        ld dp, KRN_MEM_IVEC+0x03*2
        ld a, uart1isr_
        st (dp), a        
        ; IRQ 4
        ld dp, KRN_MEM_IVEC+0x04*2
        ld a, __invalidisr
        st (dp), a
        ; IRQ 5
        ld dp, KRN_MEM_IVEC+0x05*2
        ld a, __invalidisr
        st (dp), a
        ; IRQ 6
        ld dp, KRN_MEM_IVEC+0x06*2
        ld a, __invalidisr
        st (dp), a
        ; IRQ 7
        ld dp, KRN_MEM_IVEC+0x07*2
        ld a, __invalidisr
        st (dp), a  
        ; SYSCALL map
        ld dp, KRN_MEM_IVEC+0x0f*2
        ld a, krn_syscall_map
        st (dp), a

; initialize and say hello

        ld al, 0x00                 ; initialize serial port
        syscall KRN_UART_SEL
        syscall KRN_UART_INIT
        
        ld dp, vt100clrscr
        syscall KRN_UART_PSTR
        
        ld dp, vt100scroll
        syscall KRN_UART_PSTR
        
        ld dp, msggreet1
        syscall KRN_UART_PSTRNL
        
        ld dp, msggreet2
        syscall KRN_UART_PSTRNL
        
        ld dp, emptystr
        syscall KRN_UART_PSTRNL
        
        ld dp, msgrev
        syscall KRN_UART_PSTRNL
        
        ld dp, emptystr
        syscall KRN_UART_PSTRNL
        
; detect memory and devices

        ld dp, msgmem1              ; detect memory
        syscall KRN_UART_PSTR
        call __krn_memdetect
        ld dp, strbuf
        call __krn_prndecw
        syscall KRN_UART_PSTR
        ld dp, msgmem2
        syscall KRN_UART_PSTRNL

        ld dp, msguart0             ; check for UART0
        syscall KRN_UART_PSTR
        ld al, 0x00
        syscall KRN_UART_SEL
        syscall KRN_UART_DETECT
        cmp al, 0x01
        je uart0checkfound
        ld dp, msgnfound
        syscall KRN_UART_PSTRNL        
        jmp uart0checkend
uart0checkfound:
        ld dp, msgfound
        syscall KRN_UART_PSTRNL
uart0checkend:
        
        ld dp, msguart1             ; check for UART1
        syscall KRN_UART_PSTR
        ld al, 0x01
        syscall KRN_UART_SEL
        syscall KRN_UART_DETECT
        cmp al, 0x01
        je uart1checkfound
        ld al, 0x00
        syscall KRN_UART_SEL
        ld dp, msgnfound
        syscall KRN_UART_PSTRNL        
        jmp uart1checkend
uart1checkfound:
        ld al, 0x00
        syscall KRN_UART_SEL
        ld dp, msgfound
        syscall KRN_UART_PSTRNL
uart1checkend:        

        ld dp, msgrtc               ; check for RTC
        syscall KRN_UART_PSTR
        syscall KRN_RTC_DETECT
        cmp al, 0x01
        je rtccheckfound
        ld dp, msgnfound
        syscall KRN_UART_PSTRNL        
        jmp rtccheckend
rtccheckfound:
        ld dp, msgfound
        syscall KRN_UART_PSTRNL
rtccheckend: 

		syscall KRN_IDE_INIT

        ld dp, msgide0              ; check for IDE0 (master)
        syscall KRN_UART_PSTR
		ld al, 0x00
		syscall KRN_IDE_DEVSEL
		cmp al, 0xff
		je ide0notfound
		syscall KRN_IDE_SPINUP
		ld dp, ideidstr
        syscall KRN_IDE_DETECT
        syscall KRN_UART_PSTRNL
        jmp ide0end
ide0notfound:
		ld dp, idemsgnone
		syscall KRN_UART_PSTRNL
ide0end:

        ld dp, msgide1              ; check for IDE1 (slave)
        syscall KRN_UART_PSTR
		ld al, 0x01
		syscall KRN_IDE_DEVSEL
		cmp al, 0xff
		je ide1notfound
		syscall KRN_IDE_SPINUP
		ld dp, ideidstr
        syscall KRN_IDE_DETECT
        syscall KRN_UART_PSTRNL
        jmp ide1end
ide1notfound:
		ld dp, idemsgnone
		syscall KRN_UART_PSTRNL
ide1end:

; setup RTC

        ld al, 0x00					; disable interrupts
		syscall KRN_RTC_SETIER

        ld al, 0x07					; set control register
		syscall KRN_RTC_SETCTL

; enable interrupts

        sti        

; allow serial peer to send data

        ld al, 0x02 				; set CTS
        syscall KRN_UART_SETMCR
        
; shell

        call __krn_shell

; end work
        
        cli
        halt
      
__invalidisr:
        ld dp, msginvirq
        syscall KRN_UART_PSTRNL
        iret

; Source code (data)
; --------------------------------------------------------------
        
        .data

; literals
        
msgrev      db 'Monitor/OS build syscmd(`date|tr -d ''\n''')', 0x00
msggreet1   db 'DIY Computer Project', 0x00
msggreet2   db 'Dawid Pilawa, Warsaw, Poland', 0x00
msgmem1     db 'Memory: 128kB ROM, ', 0x00
msgmem2     db 'kB RAM', 0x00
msguart0    db 'UART0:  ', 0x00
msguart1    db 'UART1:  ', 0x00
msgrtc      db 'RTC:    ', 0x00
msgide0     db 'IDE0:   ', 0x00
msgide1     db 'IDE1:   ', 0x00

msgfound    db 'found', 0x00
msgnfound   db 'not found', 0x00

msginvirq   db 'ISR not present', 0x00

emptystr    db 0x00

; buffers

strbuf      db 0x00:512

; kernel exported (via syscall) functions map

krn_syscall_map dw  _krn_syscall_uart_sel,      ; 0x00
                    _krn_syscall_uart_detect,   ; 0x01
                    _krn_syscall_uart_init,     ; 0x02
                    _krn_syscall_uart_setmcr,   ; 0x03
                    _krn_syscall_uart_putc,     ; 0x04
                    _krn_syscall_uart_getc,     ; 0x05
                    _krn_syscall_uart_pstr,     ; 0x06
                    _krn_syscall_uart_pstrnl,   ; 0x07            
                    _krn_syscall_uart_gstr,     ; 0x08
                    0x0000,                     ; 0x09
                    0x0000,                     ; 0x0a
                    0x0000,                     ; 0x0b
                    0x0000,                     ; 0x0c
                    0x0000,                     ; 0x0d                    
                    0x0000,                     ; 0x0e
                    0x0000,                     ; 0x0f                    
                    _krn_syscall_rtc_detect,    ; 0x10
                    _krn_syscall_rtc_setier,    ; 0x11
                    _krn_syscall_rtc_setctl,    ; 0x12
                    0x0000,                     ; 0x13
                    0x0000,                     ; 0x14
                    0x0000,                     ; 0x15                    
                    0x0000,                     ; 0x16
                    0x0000,                     ; 0x17  
                    0x0000,                     ; 0x18
                    0x0000,                     ; 0x19
                    0x0000,                     ; 0x1a
                    0x0000,                     ; 0x1b
                    0x0000,                     ; 0x1c                    
                    0x0000,                     ; 0x1d
                    0x0000,                     ; 0x1e 
                    0x0000,                     ; 0x1f                                       
                    _krn_syscall_ide_init,      ; 0x20  
                    _krn_syscall_ide_devsel,    ; 0x21  
                    _krn_syscall_ide_spinup,    ; 0x22  
                    _krn_syscall_ide_spindown,  ; 0x23  
                    _krn_syscall_ide_detect     ; 0x24 
                    
