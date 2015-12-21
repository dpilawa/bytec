; Test suite - set 04
; memory store operations (16-bit operands)
;
; Test success: machine halts with value 0xabcd in register A
; Test fail:    otherwise

_start:
            ; initialize memory pages

            ld a, 0x2400
            mov dp, a
            ld a, 0x0004
            st (dp:0), al

            ld a, 0x2600
            mov dp, a
            ld a, 0x0005
            st (dp:0), al

            ; A operand

            ld a, 0x5000        ; set up
            mov sp, a
            ld a, 0x6000
            mov dp, a
            ld x, 0x3000
            ld y, 0x4000

            ld a, 0x7005        ; st (sp), a
            st (sp), a
            xor a, a
            ld a, (sp)
            call checkA

            st (sp:7), a        ; st (sp:#i8), a
            xor a, a
            ld a, (sp:7)
            call checkA

            st (sp:0xf000), a   ; st (sp:#i16), a
            xor a, a
            ld a, (sp:0xf000)
            call checkA

            st (dp:5000), a     ; st (dp:#i16), a
            xor a, a
            ld a, (dp:5000)
            call checkA

            st (dp), a          ; st (dp), a
            xor a, a
            ld a, (dp)
            call checkA

            st (dp:x), a        ; st (dp:x), a
            xor a, a
            ld a, (dp:x)
            call checkA

            st (dp:y), a        ; st (dp:y), a
            xor a, a
            ld a, (dp:y)
            call checkA

            st (a:0x1892), a    ; st (a:#i16), a
            ld a, (a:0x1892)
            call checkA

            st (x:0x1111), a    ; st (x:#i16), a
            xor a, a
            ld a, (x:0x1111)
            call checkA

            st (y:0x1771), a    ; st (y:#i16), a
            xor a, a
            ld a, (y:0x1771)
            call checkA

            ; X operand

            ld a, 0x5100        ; set up
            mov sp, a
            ld a, 0x6200
            mov dp, a
            ld x, 0x3300
            ld y, 0x4400

            ld x, 0x9712        ; st (sp), x
            st (sp), x
            xor x, x
            ld x, (sp)
            call checkX

            st (sp:-5), x       ; st (sp:#i8), x
            xor x, x
            ld x, (sp:-5)
            call checkX

            st (sp:0xf000), x   ; st (sp:#i16), x
            xor x, x
            ld x, (sp:0xf000)
            call checkX

            st (dp:5000), x     ; st (dp:#i16), x
            xor x, x
            ld x, (dp:5000)
            call checkX

            ld a, 0x3300        ; st (a:#i16), x
            st (a:0x1892), x
            xor x, x
            ld x, (a:0x1892)
            call checkX

            st (x:0x1111), x    ; st (x:#i16), x
            ld x, (x:0x1111)
            call checkX

            st (y:0x1771), x    ; st (y:#i16), x
            xor x, x
            ld x, (y:0x1771)
            call checkX

            ; Y operand

            ld a, 0x5110        ; set up
            mov sp, a
            ld a, 0x6220
            mov dp, a
            ld x, 0x3330
            ld y, 0x4440

            ld y, 0x5613        ; st (sp), Y
            st (sp), y
            xor y, y
            ld y, (sp)
            call checkY

            st (sp:-3), y       ; st (sp:#i8), y
            xor y, y
            ld y, (sp:-3)
            call checkY

            st (sp:0xf000), y   ; st (sp:#i16), y
            xor y, y
            ld y, (sp:0xf000)
            call checkY

            st (dp:5000), y     ; st (dp:#i16), y
            xor y, y
            ld y, (dp:5000)
            call checkY

            ld a, 0x3330        ; st (a:#i16), y
            st (a:0x1892), y
            xor y, y
            ld y, (a:0x1892)
            call checkY

            st (x:0x1771), y    ; st (x:#i16), y
            xor y, y
            ld y, (x:0x1771)
            call checkY

            st (y:0x1111), y    ; st (y:#i16), y
            ld y, (y:0x1111)
            call checkY

pass:
            ld a, 0xabcd
            halt

error:
            ld a, 0xdead
            halt

checkA:     cmp a, 0x7005
            jne error
            ret

checkX:     mov a, x
            cmp a, 0x9712
            jne error
            ret

checkY:     mov a, y
            cmp a, 0x5613
            jne error
            ret
