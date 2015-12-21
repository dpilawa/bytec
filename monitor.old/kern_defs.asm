; Homebuilt 16-bit Computer OS/Monitor
; Dawid Pilawa (C) 2011, 2012
;
; System wide constants
;
; --------------------------------------------------------------

REG_CODEPAGE0       equ 0x2000
REG_CODEPAGE1       equ 0x2200
REG_DATAPAGE0       equ 0x2400
REG_DATAPAGE1       equ 0x2600
REG_UART0           equ 0x1000
REG_UART1           equ 0x1010
REG_RTC             equ 0x1020
REG_IDE             equ 0x1030
REG_IDEHI           equ 0x1040

KRN_MEM_IVEC        equ 0x0000 ; interrupt vector address
KRN_MEM_DATA        equ 0x3000 ; kernel data segment start address

IRQ_REG_PC          equ 0x00   ; stack offsets for ISR
IRQ_REG_DP          equ 0x02
IRQ_REG_Y           equ 0x04  
IRQ_REG_X           equ 0x06  
IRQ_REG_A           equ 0x08
IRQ_REG_AH          equ IRQ_REG_A
IRQ_REG_AL          equ IRQ_REG_A+1
IRQ_REG_SP          equ 0x10     
IRQ_REG_MSW         equ 0x12  

; OS functions (SYSCALL)

KRN_UART_SEL        equ 0x00
KRN_UART_DETECT     equ 0x01
KRN_UART_INIT       equ 0x02
KRN_UART_SETMCR     equ 0x03
KRN_UART_PUTC       equ 0x04
KRN_UART_GETC       equ 0x05
KRN_UART_PSTR       equ 0x06
KRN_UART_PSTRNL     equ 0x07
KRN_UART_GSTR       equ 0x08

KRN_RTC_DETECT      equ 0x10
KRN_RTC_SETIER      equ 0x11
KRN_RTC_SETCTL      equ 0x12

KRN_IDE_INIT		equ 0x20
KRN_IDE_DEVSEL		equ 0x21
KRN_IDE_SPINUP		equ 0x22
KRN_IDE_SPINDOWN	equ 0x23
KRN_IDE_DETECT      equ 0x24

; shell defines

SHL_DUMPLINEWIDTH   equ 0x10
