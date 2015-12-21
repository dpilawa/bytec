; Test suite - set 03
; CALL and RET instructions
;
; Test success: machine halts with value 0xabcd in register A
; Test fail:    otherwise

_start:
            ; initialize paging
            ld x, 0x2400
            ld al, 4
            st (x:0), al

            ld x, 0x2600
            ld al, 5
            st (x:0), al

            ; set stack location
            ld a, 0xf000
            mov sp, a

            call proc

            cmp a, 0xf00f   ; check if subroutine worked
            jne error
            mov a, x
            cmp a, 15
            jne error

pass:
            ld a, 0xabcd
            halt

proc:       or a, 0x000f    ; some ops
            ld x, 15        ; some ops
            nop             ; some ops
            ret             ; return to caller

error:
            ld a, 0xdead
            halt
