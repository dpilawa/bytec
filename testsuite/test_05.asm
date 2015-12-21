; Test suite - set 05
; artithmetic operations (additions)
;
; Test success: machine halts with value 0xabcd in register A
; Test fail:    otherwise

_start:
            ; initialize data memory pages

            ld x, 0x2400
            ld al, 4
            st (x:0), al

            ld x, 0x2600
            ld al, 5
            st (x:0), al

            ; ADDITIONS (16-bit target)

            ld a, 0x1122        ; test add a, #i8 results
            add a, 19
            cmp a, 0x1135
            jne error
            ld a, 0x1122
            add a, -111
            cmp a, 0x10b3
            jne error

            ld a, 10000         ; test add a, #i16
            add a, 2345
            cmp a, 12345
            jne error

            ld a, 0x1122        ; test add a, x
            ld x, 19
            add a, x
            cmp a, 0x1135
            jne error

            ld a, 0x1122        ; test add a, y
            ld y, 19
            add a, y
            cmp a, 0x1135
            jne error

            ld a, 0xc00f        ; test add sp, #i8
            mov sp, a
            add sp, 5
            mov a, sp
            cmp a, 0xc014
            jne error
            add sp, -5
            mov a, sp
            cmp a, 0xc00f
            jne error

            ld a, 0xc00f        ; test add dp, #i8
            mov dp, a
            add dp, 5
            mov a, dp
            cmp a, 0xc014
            jne error
            add dp, -5
            mov a, dp
            cmp a, 0xc00f
            jne error

            ld x, 0xc00f        ; test add x, #i8
            add x, 5
            mov a, x
            cmp a, 0xc014
            jne error
            add x, -5
            mov a, x
            cmp a, 0xc00f
            jne error

            ld y, 0xc00f        ; test add y, #i8
            add y, 5
            mov a, y
            cmp a, 0xc014
            jne error
            add y, -5
            mov a, y
            cmp a, 0xc00f
            jne error

            ld a, 0xf005        ; test add a, (sp)
            mov sp, a
            ld a, 0x1010
            st (sp), a
            ld a, 0x0a0a
            add a, (sp)
            cmp a, 0x1a1a
            jne error

            ld a, 0xf000        ; test add a, (sp:#i8)
            mov sp, a
            ld a, 0xffff
            add a, (sp:0x0005)
            cmp a, 0x100f
            jne error

            ld a, 0x0007        ; test add a, (sp:#i16)
            mov sp, a
            ld a, 0x1000
            add a, (sp:0xeffe)
            cmp a, 0x2010
            jne error

            ld a, 0             ; test add a, (dp:#i16)
            mov dp, a
            ld a, -11
            st (dp:0x3000), a
            ld a, 1
            mov dp, a
            ld a, 5
            add a, (dp:0x2fff)
            cmp a, -6
            jne error

            ; now some flag setting tests

            ld a, 0xfffe        ; test if add a, #i8 correctly sets carry
            add a, 5
            jnc error
            jz error
            jn error
            jv error

            ld a, 0x7ff0        ; test if add a, #i8 correctly sets overflow and negative
            add a, 100
            jnv error
            jnn error
            jz error
            jc error

            ld a, 0xfff0        ; test if add a, #i8 correctly sets zero
            add a, 16
            jnz error
            jv error
            jnc error
            jn error

            ld a, 0x1000        ; test if add a, #i16 correctly sets carry
            add a, 0xf005
            jnc error
            jz error
            jn error
            jv error

            ld a, 0x1000        ; test if add a, #i16 correctly sets overflow and negative
            add a, 0x7100
            jnv error
            jnn error
            jz error
            jc error

            ld a, 0xf000        ; test if add a, #i16 correctly sets zero
            add a, 0x1000
            jnz error
            jv error
            jnc error
            jn error

            ; ADDITIONS (8-bit target)

            ld a, 0x7000        ; test add ah, (sp)
            mov sp, a

            ld a, 0x0522        ; put sometging at SP
            st (sp), a
            ld a, 0xd067        ; put something in A
            add ah, (sp)
            cmp a, 0xd567       ; chceck if high byte increased and low byte unchanged
            jne error
            ld a, 0xd067        ; put something back in A
            add ah, (sp)
            jz error            ; check flags
            jv error
            jc error
            jnn error

            ld a, 0x5001        ; same test for positive + negative = positive
            st (sp), a
            ld a, 0xd067
            add ah, (sp)
            cmp a, 0x2067
            jne error
            ld a, 0xd067
            add ah, (sp)
            jz error
            jv error
            jnc error
            jn error

            ld a, 0x5001        ; positive + positive = negative (overflow)
            st (sp), a
            ld a, 0x4067
            add ah, (sp)
            cmp a, 0x9067
            jne error
            ld a, 0x4067
            add ah, (sp)
            jz error
            jnv error
            jc error
            jnn error

            ld a, 0x8001        ; negative + negative = positive (overflow)
            st (sp), a
            ld a, 0x8010
            add ah, (sp)
            cmp a, 0x0010
            jne error
            ld a, 0x8010
            add ah, (sp)
            jnz error           ; zero flag should be set (it is a high byte operation)
            jnv error           ; overflow should be set
            jnc error           ; carry should be set
            jn error            ; the result is not negative

            ld a, 0x7000        ; test add ah, (sp:#i8)
            mov sp, a
            ld a, 0x3344
            st (sp), a
            ld a, 0x1122
            add ah, (sp:1)
            cmp a, 0x5522
            jne error

            ld a, 0             ; test add ah, (sp:#i16)
            mov sp, a
            ld a, 0x1122
            add ah, (sp:0x7000)
            cmp a, 0x4422
            jne error

            ld a, 0             ; test add ah, (dp:#i16)
            mov dp, a
            ld a, 0x1122
            add ah, (dp:0x7000)
            cmp a, 0x4422
            jne error

            ; ---

            ld a, 0x7000        ; test add al, (sp)
            mov sp, a

            ld a, 0x2051        ; put something at SP
            st (sp), a
            ld a, 0x0587        ; put something in A
            add al, (sp)
            cmp a, 0x05a7       ; check if low byte increased and high byte unchanged
            jne error
            ld a, 0x0587        ; put something back in A
            add al, (sp)
            jz error            ; check flags
            jv error
            jc error
            jnn error

            ld a, 0x5001        ; same test for positive + negative = positive
            st (sp), a
            ld a, 0x67d0
            add al, (sp)
            cmp a, 0x6720
            jne error
            ld a, 0x67d0
            add al, (sp)
            jz error
            jv error
            jnc error
            jn error

            ld a, 0x5001        ; positive + positive = negative (overflow)
            st (sp), a
            ld a, 0x6740
            add al, (sp)
            cmp a, 0x6790
            jne error
            ld a, 0x6740
            add al, (sp)
            jz error
            jnv error
            jc error
            jnn error

            ld a, 0x8001        ; negative + negative = positive (overflow)
            st (sp), a
            ld a, 0xff80
            add al, (sp)
            cmp a, 0xff00
            jne error
            ld a, 0xff80
            add al, (sp)
            jnz error           ; zero flag should be set (it is a high byte operation)
            jnv error           ; overflow should be set
            jnc error           ; carry should be set
            jn error            ; the result is not negative

            ld a, 0x7000        ; test add al, (sp:#i8)
            mov sp, a
            ld a, 0x3344
            st (sp), a
            ld a, 0x1122
            add al, (sp:1)
            cmp a, 0x1166
            jne error

            ld a, 0             ; test add al, (sp:#i16)
            mov sp, a
            ld a, 0x1122
            add al, (sp:0x7000)
            cmp a, 0x1155
            jne error

            ld a, 0             ; test add al, (dp:#i16)
            mov dp, a
            ld a, 0x1122
            add al, (dp:0x7000)
            cmp a, 0x1155
            jne error

            ; ADDITION WITH CARRY

            mov al, msw
            or a, 0x0001
            mov msw, al         ; set carry flag

            ld a, 0x1111        ; test adc a, x
            ld x, 0x2220
            adc a, x
            cmp a, 0x3332
            jne error

            mov al, msw
            or a, 0x0001
            mov msw, al         ; set carry flag

            ld a, 0x7fff        ; test if adc a, x sets flags
            ld x, 0x0000
            adc a, x            ; positive+positive+carry=negative addition
            jnv error
            jnn error
            jz error
            jc error

            mov al, msw
            or a, 0x0001
            mov msw, al         ; set carry flag

            ld a, 0x8000        ; test adc a, y
            ld y, 0x7fff
            adc a, y
            jnz error

            ; INC operations

            ld x, 0x1000        ; test inc x
            inc x
            mov a, x
            cmp a, 0x1001
            jne error

            ld y, 0x2000        ; test inc y
            inc y
            mov a, y
            cmp a, 0x2001
            jne error

pass:
            ld a, 0xabcd
            halt

error:
            ld a, 0xdead
            halt
