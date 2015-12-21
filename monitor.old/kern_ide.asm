; Homebuilt 16-bit Computer OS/Monitor
; Dawid Pilawa (C) 2011, 2012
;
; IDE driver routines
;
; --------------------------------------------------------------

; defines
; --------------------------------------------------------------

; defines
; --------------------------------------------------------------

REG_IDE_DATA        equ 0x00    ; Data I/O port
REG_IDE_ERROR       equ 0x01    ; Error register
REG_IDE_S           equ 0x03    ; Sector register
REG_IDE_CL          equ 0x04    ; Cylinder register (low byte)
REG_IDE_CH          equ 0x05    ; Cylinder register (high byte)
REG_IDE_H           equ 0x06    ; Head and drive register
REG_IDE_CMD         equ 0x07    ; Command register (write)
REG_IDE_STATUS      equ 0x07    ; Status register (read)
REG_IDE_IER         equ 0x0e    ; Interrupt enable and reset register (write)
REG_IDE_STATUS2     equ 0x0e    ; Alternative status register (read)
REG_IDE_ASR         equ 0x0f    ; Active status register

IDE_CMD_INITDRV     equ 0x91    ; Initialize drive parameters
IDE_CMD_SPINDOWN    equ 0xe0    ; Spin drive down
IDE_CMD_SPINUP      equ 0xe1    ; Spin drive up
IDE_CMD_IDENTIFY    equ 0xec    ; Identify drive

; text segment
; --------------------------------------------------------------

        .text

; exported functions

_krn_syscall_ide_init:
        call _krn_ide_init
        iret

_krn_syscall_ide_devsel:
        call _krn_ide_devsel
        st (sp:IRQ_REG_AL), al
        iret

_krn_syscall_ide_spinup:
        call _krn_ide_spinup
        iret

_krn_syscall_ide_spindown:
        call _krn_ide_spindown
        iret

_krn_syscall_ide_detect:
        call _krn_ide_detect
        st (sp:IRQ_REG_AL), al
        iret

; kernel functions


; --------------------------------------------------------------
; KRN_IDE_INIT
;
; Initialize IDE controller
;
; Input:
;   None
; Output:
;   None
_krn_ide_init:
        push dp
        push al

        ld al, 0b00001110			; issue software reset to devices
        st (dp:REG_IDE_IER), al
        ld al, 0b00001010           ; clear reset bit
        st (dp:REG_IDE_IER), al 

        ld dp, REG_IDE
        ld al, 0x00                 ; check if master device present
        call _krn_ide_devsel
        ld al, 0b00001000			; enable interrupts
        st (dp:REG_IDE_IER), al
        ld al, (dp:REG_IDE_ERROR)   ; check ERROR register
        ld dp, idemaster
        st (dp), al					; store device present flag

        ld dp, REG_IDE
        ld al, 0x01                 ; check if slave device present
        call _krn_ide_devsel
        ld al, 0b00001000			; enable interrupts
        st (dp:REG_IDE_IER), al
        ld al, (dp:REG_IDE_ERROR)   ; check ERROR register
        ld dp, ideslave
        st (dp), al
        
        pop al
        pop dp
        ret


; --------------------------------------------------------------
; KRN_IDE_DEVSEL
;
; Select IDE device (master/slave)
;
; Input:
;   AL - device selection (0x00 for master, otherwise slave)
; Output:
;   AL - result (0xff if device missing)
_krn_ide_devsel:
        push dp
        push ah
        ld dp, REG_IDE
        ld ah, (dp:REG_IDE_H)
        cmp al, 0x00
        jne krn_ide_devsel_slave
        ld dp, idemaster
        ld al, (dp)
        and ah, 0b11101111
        jmp krn_ide_devsel_end
krn_ide_devsel_slave:
        ld dp, ideslave
        ld al, (dp)
        or ah, 0b00010000
krn_ide_devsel_end:
        ld dp, REG_IDE
        st (dp:REG_IDE_H), ah
        pop ah
        pop dp
        ret


; --------------------------------------------------------------
; KRN_IDE_SPINUP
;
; Spin up current IDE device
;
; Input:
;   None
; Output:
;   None
_krn_ide_spinup:
        push dp
        push al
krn_ide_spinup_wait:
        ld dp, REG_IDE
        ld al, (dp:REG_IDE_STATUS)  ; wait for RDY=1 and BUSY=0 flags
        and al, 0b11000000
        cmp al, 0b01000000
        jne krn_ide_spinup_wait
        ld al, IDE_CMD_SPINUP       ; spin-up the drive
        st (dp:REG_IDE_CMD), al
        pop al
        pop dp
        ret

; --------------------------------------------------------------
; KRN_IDE_SPINDOWN
;
; Spin down current IDE device
;
; Input:
;   None
; Output:
;   None
_krn_ide_spindown:
        push dp
        push al
krn_ide_spindown_wait:
        ld dp, REG_IDE
        ld al, (dp:REG_IDE_STATUS)  ; wait for RDY=1 and BUSY=0 flags
        and al, 0b11000000
        cmp al, 0b01000000
        jne krn_ide_spindown_wait
        ld al, IDE_CMD_SPINDOWN     ; spin-down the drive
        st (dp:REG_IDE_CMD), al
        pop al
        pop dp
        ret

; --------------------------------------------------------------
; KRN_IDE_DETECT
;
; Detect current ide device and prepare identification string
;
; Input:
;   DP - address of the string buffer
; Output:
;   None
_krn_ide_detect:
        push a
        push x
        push dp
        push dp                     ; scratch pointer
_krn_ide_detect_wait:
        ld dp, REG_IDE              ; wait for RDY=1 and BUSY=0 flags
        ld al, (dp:REG_IDE_STATUS)
        and al, 0b11000000
        cmp al, 0b01000000
        jne _krn_ide_detect_wait

        ld al, IDE_CMD_IDENTIFY
        st (dp:REG_IDE_CMD), al
_krn_ide_detect_wait2:
        ld dp, REG_IDE              ; wait for DRQ=1 and BUSY=0 flags
        ld al, (dp:REG_IDE_CMD)
        and al, 0b10001000
        cmp al, 0b00001000
        jne _krn_ide_detect_wait2

        ld dp, idesecbuf            ; read ID sector to buffer
        ld x, 256
_krn_ide_detect_read:
        push dp
        ld dp, REG_IDE
        ld al, (dp:0)
        ld dp, REG_IDEHI
        ld ah, (dp:0)
        pop dp
        st (dp:0), a
        add dp, 2
        dec x
        jnz _krn_ide_detect_read

        ld dp, idesecbuf+0x36       ; check device label
        ld al, 0x00
        st (dp:40), al
        call __krn_rtrim
        ld x, (sp:0)
        call __krn_strcpy
        ld dp, m_space
        call __krn_strcpy
        st (sp:0), x

        ld dp, idesecbuf+0x78       ; check device size (in MB)
        ld a, (dp)
        shr a
        shr a
        shr a
        shr a
        shr a
        shr a
        shr a
        shr a
        shr a
        shr a
        shr a
        push a
        ld a, (dp:2)
        shl a
        shl a
        shl a
        shl a
        shl a
        or a, (sp)
        pop x
        ld dp, strbuf
        call __krn_prndecw
        ld x, (sp:0)
        call __krn_strcpy

        ld dp, idemsgmb
        call __krn_strcpy

_krn_ide_detect_end:

        pop dp                      ; discard scratch pointer
        pop dp
        pop x
        pop a
        ret


; kelner helpers


; interrupt service routines

ideisr_:
        cli
        ld dp, idemisr
        syscall KRN_UART_PSTRNL
        ld dp, REG_IDE
        ld al, (dp:REG_IDE_STATUS)
        sti
        iret


; data segment
; --------------------------------------------------------------

        .data

; data structures

idemaster   db  0xff        ; 0xff - device not present
ideslave    db  0xff        ; 0xff - device not present
idesecbuf   db  0x00:512    ; sector buffer
ideidstr    db  0x00:128    ; identification string buffer

; strings

idemsgmb    db 'MB', 0x00
idemsgcsh   db 'C/S/H:', 0x00
idemsglba   db 'LBA:', 0x00
idemsgy     db 'Y', 0x00
idemsgn     db 'N', 0x00
idemsgnone  db 'None', 0x00
idemisr     db 'IDEACT', 0x00
