; Test suite - set 01
; stack operations
;
; Test success: machine halts with value 0xabcd in register A
; Test fail:    otherwise

_start:
            ; set up memory pages

            ld a, 0x2400
            mov dp, a
            ld a, 0x0004
            st (dp), al

            ld a, 0x2600
            mov dp, a
            ld a, 0x0005
            st (dp), al

            ; set stack location
            ld a, 0xf000
            mov sp, a

            ; 8-bit push
            ld a, 0x3254
            push ah
            push al
            pop a
            cmp a, 0x5432
            jne error

            ; push a
            ld a, 0x1001
            push a

            ; push x
            ld x, 0x2002
            push x

            ; push y
            ld y, 0x3003
            push y

            ; push sp
            push sp

            ; push dp
            ld a, 0x4004
            mov dp, a
            push dp

            ; clear all
            xor a, a
            xor x, x
            xor y, y
            mov dp, a

            ; pop dp
            pop dp
            mov a, dp
            cmp a, 0x4004
            jne error

            ; pop sp
            pop sp

            ; pop y
            pop y
            mov a, y
            cmp a, 0x3003
            jne error

            ; pop x
            pop x
            mov a, x
            cmp a, 0x2002
            jne error

            ; pop a
            pop a
            cmp a, 0x1001
            jne error

            ; test program counter push/pop
            ld a, p1
            push a
            pop pc

            jmp error
p1:
            push pc
            pop a
            cmp a, p1 + 1
            jne error

pass:
            ld a, 0xabcd
            halt

error:
            ld a, 0xdead
            halt
