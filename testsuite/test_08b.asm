; Test suite - set 08 subset b
; test fault
;
; Test success: machine halts with value 0xabcd in register A
; Test fail:    otherwise

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

            ; set-up stack
            ld a, 0xf000
            mov sp, a           ; KSP

            ; set-up fault handler
            ld a, 0x0010 + 0
            mov dp, a
            ld a, mv_handler
            st (dp:0), a

            ; play with msw
            mov al, msw
            mov msw, al

            ; switch to user mode
            mov al, msw
            or a, 0x0020
            mov msw, al

            ; play with msw
            mov al, msw
            mov msw, al     ; FAULT HERE (CPU mode violation)

            nop             ; this is never reached
            nop
            nop

            ld a, 0xdead

            halt

mv_handler:
            ld a, 0xabcd
            halt
            iret
