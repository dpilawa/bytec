; Homebuilt 16-bit Computer OS/Monitor
; Dawid Pilawa (C) 2012
;
; Real-Time-Clock driver routines
;
; --------------------------------------------------------------

; defines
; --------------------------------------------------------------

REG_RTC_SEC 		equ 0x00	; Seconds
REG_RTC_SECA 		equ 0x01	; Seconds alarm
REG_RTC_MIN 		equ 0x02	; Minutes
REG_RTC_MINA 		equ 0x03	; Minutes alarm
REG_RTC_HR 			equ 0x04	; Hours
REG_RTC_HRA 		equ 0x05	; Hours alarm
REG_RTC_DAY	 		equ 0x06	; Day
REG_RTC_DAYA 		equ 0x07	; Day alarm
REG_RTC_DOW 		equ 0x08	; Day of week
REG_RTC_MON 		equ 0x09	; Month
REG_RTC_YEAR 		equ 0x0a	; Year
REG_RTC_PRI 		equ 0x0b	; Programmable Rates Register
REG_RTC_IER 		equ 0x0c	; Interrupt Enable Register
REG_RTC_FLG			equ 0x0d	; Flags Register
REG_RTC_CTL			equ 0x0e	; Control Register
REG_RTC_ZERO 		equ 0x0f	; Unused register (reads as zero)

; text segment
; --------------------------------------------------------------

        .text

; exported functions

_krn_syscall_rtc_detect:
        call _krn_rtc_detect
        st (sp:IRQ_REG_AL), al        
        iret

_krn_syscall_rtc_setier:
        call _krn_rtc_setier    
        iret

_krn_syscall_rtc_setctl:
        call _krn_rtc_setctl
        iret
        
; kernel functions

; --------------------------------------------------------------
; KRN_RTC_DETECT
;
; Detect real-time clock
;
; Input:
;   None
; Output:
;	AL - detection result (0x01 if found, 0x00 otherwise)
_krn_rtc_detect:
		push dp
        ld dp, REG_RTC
        ld al, (dp:REG_RTC_CTL)
        or al, 0b00001111
        cmp al, 0b00001111
        jne krn_rtc_detect_nfound
        ld al, 0b01010101
        st (dp:REG_RTC_ZERO), al
        ld al, (dp:REG_RTC_ZERO)
        cmp al, 0
        jne krn_rtc_detect_nfound
        ld al, 1
        jmp krn_rtc_detect_end
krn_rtc_detect_nfound:
        ld al, 0
krn_rtc_detect_end:
		pop dp
        ret

; --------------------------------------------------------------
; KRN_RTC_SETIER
; 
; Set IER register value
;
; Input:
;   AL - IER register value
; Output:
;	None
_krn_rtc_setier:
		push dp
        ld dp, REG_RTC
        st (dp:REG_RTC_IER), al
        pop dp
        ret

; --------------------------------------------------------------
; KRN_RTC_SETCTL
; 
; Set CTL register value
;
; Input:
;   AL - CTK register value
; Output:
;	None
_krn_rtc_setctl:
		push dp
        ld dp, REG_RTC
        st (dp:REG_RTC_CTL), al
        pop dp
        ret

; kelner helpers


; interrupt service routines


; data segment
; --------------------------------------------------------------
        
        .data

