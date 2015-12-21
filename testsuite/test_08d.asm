; Test suite - set 08 subset d
; test syscall
;
; test completes successfuly if 
; A = 0xabcd
; X = 0x2345
; Y = 0x6789

_start:
            ; initialize memory pages
            ld a, 0x2000
            mov dp, a
            ld al, 0
            st (dp), al

            ld a, 0x2200
            mov dp, a
            ld al, 1
            st (dp), al

            ld a, 0x2400
            mov dp, a
            ld al, 4
            st (dp), al

            ld a, 0x2600
            mov dp, a
            ld al, 5
            st (dp), al

            ; setup stack
            ld a, 0x0000
            mov sp, a

            ; set vector for SYSCALL
            ld a, 0x001e
            mov dp, a
            ld a, sys
            st (dp), a

            ; clear x and y
            xor x,x
            xor y,y

            ; setup user mode
            mov al, msw
            or a, 0x0020
            mov msw, al

            ; USER MODE PROGRAM 

            ld a, 0xabcd
            ld x, 0x2345
            syscall
            ld y, 0x6789

            ; halt
            halt

sys:
            ; sys driver
            ld a, 0xdcba
            iret
