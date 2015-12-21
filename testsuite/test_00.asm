; Test suite - set 00
; MOV instructions
;
; Test success: machine halts with value 0xabcd in register A
; Test fail:    otherwise

_start:
            ld a, 0x1111
            mov x, a        ; x should be 0x1111
            ld a, 0x2222
            mov y, a        ; y should be 0x2222
            ld a, 0x3333
            mov sp, a       ; sp should be 0x3333
            ld a, 0x4444
            mov dp, a       ; dp should be 0x4444

            xor a, a        ; clear a
            mov a, x
            cmp a, 0x1111
            jne error

            xor a, a        ; clear a
            mov a, y
            cmp a, 0x2222
            jne error

            xor a, a        ; clear a
            mov a, sp
            cmp a, 0x3333
            jne error

            xor a, a        ; clear a
            mov a, dp
            cmp a, 0x4444
            jne error

            mov x, y
            mov a, x
            cmp a, 0x2222
            jne error

            ld a, 0x1111
            mov x, a
            mov y, x
            mov a, y
            cmp a, 0x1111
            jne error

            mov sp, dp
            mov a, sp
            cmp a, 0x4444
            jne error

            ld a, 0x3333
            mov sp, a
            mov dp, sp
            mov a, dp
            cmp a, 0x3333
            jne error

            mov al, msw
            and a, 0xfff0
            mov msw, al     ; clear CZNV flags
            xor a, a        ; sets flag Z, clears other flags
            mov al, msw
            and a, 0x000f
            cmp a, 0x0002   ; only flag Z is set
            jne error

pass:
            ld a, 0xabcd
            halt
error:
            ld a, 0xdead
            halt
