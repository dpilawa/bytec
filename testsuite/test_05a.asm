; Test suite - set 05a
; artithetic operations (subtractions)
;
; Test success: machine halts with valie 0xabcd in register A
; Test fail:    otherwise

_start:
            ; initialize data memory

            ld x, 0x2400
            ld al, 4
            st (x:0), al

            ld x, 0x2600
            ld al, 5
            st (x:0), al

            ; SUBTRACTIONS (16-bit target)

            ld a, 0x1122        ; test sub a, #i8 results
            sub a, 11           ; positive operand
            cmp a, 0x1117
            jne error
            ld a, 0x1122
            sub a, -111         ; negative operand
            cmp a, 0x1191
            jne error

            ld a, 10000         ; test sub a, #i16
            sub a, 2500
            cmp a, 7500
            jne error

            ld a, 0x1122        ; test sub a, x
            ld x, 300
            sub a, x
            cmp a, 0x0ff6
            jne error

            ld a, 0x1122        ; test sub a, y
            ld y, 19
            sub a, y
            cmp a, 0x110f
            jne error

            ld a, 0xf005        ; test sub a, (sp)
            mov sp, a
            ld a, 0x1010
            st (sp), a
            ld a, 0x0a0a
            sub a, (sp)
            cmp a, 0xf9fa
            jne error

            ld a, 0xf000        ; test sub a, (sp:#i8)
            mov sp, a
            ld a, 0xffff
            sub a, (sp:0x05)
            cmp a, 0xefef
            jne error

            ld a, 0x0007        ; test sub a, (sp:#i16)
            mov sp, a
            ld a, 0x1200
            sub a, (sp:0xeffe)
            cmp a, 0x01f0
            jne error

            ld a, 0             ; test sub a, (dp:#i16)
            mov dp, a
            ld a, -11
            st (dp:0x3000), a
            ld a, 1
            mov dp, a
            ld a, 5
            sub a, (dp:0x2fff)
            cmp a, 16
            jne error

            ; now some flag setting tests

            ld a, 0x0003        ; test sub a, #i8 (positive-positive=negative; borrow = no carry)
            sub a, 5
            jc error
            jz error
            jnn error
            jv error

            ld a, 0x8001        ; test sub a, #i8 (negative-positive=positive; no borrow = carry)
            sub a, 100
            jnv error
            jn error
            jz error
            jnc error

            ld a, 0x7ff0        ; test sub a, #i8 (positive-negative=negative; borrow = no carry)
            sub a, -21
            jz error
            jnv error
            jc error
            jnn error

            ld a, 0x1000        ; test if sub a, #i16 correctly sets borrow (borrow = no carry!)
            sub a, 0x2000
            jc error
            jz error
            jnn error
            jv error

            ld a, 0x7fff        ; test if sub a, #i16 correctly sets overflow and negative
            sub a, 0x8001
            jnv error
            jnn error
            jz error
            jc error

            ld a, 0xf000        ; test if sub a, #i16 correctly sets zero
            sub a, 0xf000
            jnz error
            jv error
            jnc error
            jn error

            ; SUBTRACTIONS (8-bit target)

            ld a, 0x7000        ; test sub ah, (sp)
            mov sp, a

            ld a, 0x0322        ; put something at SP
            st (sp), a
            ld a, 0x0567        ; put something in A
            sub ah, (sp)
            cmp a, 0x0267       ; chceck if high byte decreased and low byte unchanged
            jne error
            ld a, 0x0567        ; put something back in A
            sub ah, (sp)
            jz error            ; check flags
            jv error
            jnc error           ; carry set = no borrow for subtraction
            jn error

            ld a, 0xe001        ; same test for positive - negative = positive (no overflow)
            st (sp), a
            ld a, 0x5067
            sub ah, (sp)
            cmp a, 0x7067
            jne error
            ld a, 0x5067
            sub ah, (sp)
            jz error
            jv error
            jc error
            jn error

            ld a, 0x1001        ; negative - positive = positive (overflow)
            st (sp), a
            ld a, 0x8567
            sub ah, (sp)
            cmp a, 0x7567
            jne error
            ld a, 0x8567
            sub ah, (sp)
            jz error
            jnv error
            jnc error
            jn error

            ld a, 0x9001        ; negative - negative = 0
            st (sp), a
            ld a, 0x9010
            sub ah, (sp)
            cmp a, 0x0010
            jne error
            ld a, 0x9010
            sub ah, (sp)
            jnz error           ; zero flag should be set (it is a high byte operation)
            jv error            ; no overflow
            jnc error           ; no borrow
            jn error            ; the result is not negative

            ld a, 0x7000        ; test sub ah, (sp:#i8)
            mov sp, a
            ld a, 0x3344
            st (sp), a
            ld a, 0x1122
            sub ah, (sp:1)
            cmp a, 0xcd22
            jne error

            ld a, 0             ; test sub ah, (sp:#i16)
            mov sp, a
            ld a, 0x1122
            sub ah, (sp:0x7000)
            cmp a, 0xde22
            jne error

            ld a, 0             ; test sub ah, (dp:#i16)
            mov dp, a
            ld a, 0x1122
            sub ah, (dp:0x7000)
            cmp a, 0xde22
            jne error

            ; ---

            ld a, 0x7000        ; test sub al, (sp)
            mov sp, a

            ld a, 0x0720        ; put something at SP
            st (sp), a
            ld a, 0x0527        ; put something in A
            sub al, (sp)
            cmp a, 0x0520       ; check if low byte decreased and high byte unchanged
            jne error
            ld a, 0x0527        ; put something back in A
            sub al, (sp)
            jz error            ; check flags
            jv error
            jnc error
            jn error

            ld a, 0xd050        ; same test for positive - negative = positive
            st (sp), a
            ld a, 0x6701
            sub al, (sp)
            cmp a, 0x6731
            jne error
            ld a, 0x6701
            sub al, (sp)
            jz error
            jv error
            jc error
            jn error

            ld a, 0x0550        ; positive - positive = negative (borrow)
            st (sp), a
            ld a, 0x6703
            sub al, (sp)
            cmp a, 0x67fe
            jne error
            ld a, 0x6703
            sub al, (sp)
            jz error
            jv error            ; no overflow
            jc error            ; borrow
            jnn error

            ld a, 0x0180        ; negative - positive = positive (overflow)
            st (sp), a
            ld a, 0xff80
            sub al, (sp)
            cmp a, 0xff7f
            jne error
            ld a, 0xff80
            sub al, (sp)
            jz error            ; not zero
            jnv error           ; overflow should be set
            jnc error           ; there was no borrow, so carry should be set
            jn error            ; the result is not negative

            ld a, 0x7000        ; test sub al, (sp:#i8)
            mov sp, a
            ld a, 0x3344
            st (sp), a
            ld a, 0x1122
            sub al, (sp:1)
            cmp a, 0x11de
            jne error

            ld a, 0             ; test sub al, (sp:#i16)
            mov sp, a
            ld a, 0x1122
            sub al, (sp:0x7000)
            cmp a, 0x11ef
            jne error

            ld a, 0             ; test sub al, (dp:#i16)
            mov dp, a
            ld a, 0x1122
            sub al, (dp:0x7000)
            cmp a, 0x11ef
            jne error

            ; SUBTRACT WITH CARRY

            mov al, msw
            or a, 0x0001
            mov msw, al         ; set carry flag (flag set = no borrow)

            ld a, 0x3333        ; test sbc a, x
            ld x, 0x1111
            sbc a, x
            cmp a, 0x2222
            jne error

            mov al, msw
            and a, 0xfffe
            mov msw, al         ; clear carry flag (flag cleared = borrow)

            ld a, 0x3333        ; same op as before
            ld x, 0x1111
            sbc a, x
            cmp a, 0x2221
            jne error

            mov al, msw
            and a, 0xfffe
            mov msw, al         ; clear carry flag (set borrow)

            ld a, 0x8000        ; test if sbc a, x sets flags
            ld x, 0x0000
            sbc a, x            ; negative - positive - borrow = positive
            jnv error           ; overflow
            jn error            ; not negative
            jz error            ; not zero
            jnc error           ; no borrow (carry should be set)

            mov al, msw
            and a, 0xfffe
            mov msw, al         ; clear carry flag (set borrow)

            ld a, 0x8000        ; test sdc a, y
            ld y, 0x7fff
            sbc a, y
            jnz error

            ; DEC operations

            ld a, 0x1000        ; test dec x
            mov x, a
            dec x
            mov a, x
            cmp a, 0x0fff
            jne error

            ld a, 0x2000        ; test dec y
            mov y, a
            dec y
            mov a, y
            cmp a, 0x1fff
            jne error

pass:
            ld a, 0xabcd
            halt

error:
            ld a, 0xdead
            halt

