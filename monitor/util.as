;
;     Kernel routines
;     BYTEC/16 Homebuilt Microcomputer Monitor Program
;     Dawid Pilawa (C) 2015
;

.global ___kern_mswflg
.global ___kern_mswld
.global ___kern_mswst

.const  #KERN_MSW_OR     0x01
.const  #KERN_MSW_AND    0x00

.text

; apply given mask in MSW
___kern_mswflg:
        ld  al,(sp:3)
        cmp al,#KERN_MSW_OR
        jne ___kern_mswflg_and
        mov al,msw
        or  al,(sp:5)
        mov msw,al
        ret
___kern_mswflg_and:
        mov al,msw
        and al,(sp:5)
        mov msw,al
        ret

; return MSW
___kern_mswld:
        ld ah,0
        mov al,msw
        ret

; save MSW
___kern_mswst:
        ld al,(sp:3)
        mov msw,al
        ret
