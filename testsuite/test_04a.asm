; Test suite - set 04a
; memory stores (8-bit operands)
;
; Test success: machine halts with value 0xabcd in register A
; Test fail:    otherwise

_start:
            ; initialize paging

            ld x, 0x2600
            ld al, 7
            st (x:0), al

            ; go

            ld a, 0x5000
            mov sp, a           ; initialize stack pointer
            ld a, 0x0000
            st (sp), a          ; clear two bytes at sp
            st (sp:100), a      ; clear two bytes at sp+100
            st (sp:0x0f00), a   ; clear two bytes at sp+0x0f00

            ld a, 0x1357        ; test st (sp), ah
            st (sp), ah         ; store 0x13
            xor a, a            ; clear a, to be sure
            ld a, (sp)          ; read a from memory
            cmp a, 0x1300
            jne error

            ld a, 0x1357        ; test st (sp), al
            st (sp), al
            xor a, a
            ld a, (sp)
            cmp a, 0x5700
            jne error

            ld a, 0x8765        ; test st (sp:#i8), al
            st (sp:100), al
            xor a, a
            ld a, (sp:100)
            cmp a, 0x6500
            jne error

            ld a, 0x8765        ; test st (sp:#i8), ah
            st (sp:100), ah
            xor a, a
            ld a, (sp:100)
            cmp a, 0x8700
            jne error

            ld a, 0x9885        ; test st (sp:#i16), al
            st (sp:0x0f00), al
            xor a, a
            ld a, (sp:0x0f00)
            cmp a, 0x8500
            jne error

            ld a, 0x9885        ; test st (sp:#i16), ah
            st (sp:0x0f00), ah
            xor a, a
            ld a, (sp:0x0f00)
            cmp a, 0x9800
            jne error

            ld a, 0x7000        ; setup dp
            mov dp, a
            xor a, a
            st (dp:15), a

            ld a, 0x1221        ; test st (dp:#i16), al
            st (dp:15), al
            xor a, a
            ld a, (dp:15)
            cmp a, 0x2100
            jne error

            ld a, 0x1221        ; test st (dp:#i16), al
            st (dp:15), ah
            xor a, a
            ld a, (dp:15)
            cmp a, 0x1200
            jne error

            ld a, 0x3576        ; test st (dp), al
            st (dp), al
            xor a, a
            ld al, (dp)
            cmp a, 0x0076
            jne error

            ld a, 0x5566
            st (a:0x1234), al   ; test st (a:#i16), al
            st (a:0x1235), ah   ; test st (a:#i16), ah
            ld a, (a:0x1234)
            cmp a, 0x6655
            jne error

            ld a, 0x5566
            ld x, 0xfa00
            st (x:0x0015), al   ; test st (x:#i16), al
            st (x:0x0016), ah   ; test st (x:#i16), ah
            ld a, (x:0x0015)
            cmp a, 0x6655
            jne error

            ld a, 0x5566
            ld y, 0xfb00
            st (y:0x0015), al   ; test st (y:#i16), al
            st (y:0x0016), ah   ; test st (y:#i16), ah
            ld a, (y:0x0015)
            cmp a, 0x6655
            jne error

pass:
            ld a, 0xabcd
            halt

error:
            ld a, 0xdead
            halt

