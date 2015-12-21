; Test suite - set 02
; memory loads (16-bit targets)
;
; Test success: machine halts with value 0xabcd in register A
; Test fail:    otherwise

_start:

            ; prepare memory paging

            ld a, 0x2400
            mov dp, a
            ld a, 0x0004
            st (dp:0), al

            ld a, 0x2600
            mov dp, a
            ld a, 0x0005
            st (dp:0), al

            ; --- test 16-bit and 8-bit immediate to accumulator load (with sign extention)
            ld a, 0xfafb
            cmp a, 0xfafb
            jne error
            ld a, 16
            cmp a, 0x0010
            jne error
            ld a, -3
            cmp a, 0xfffd
            jne error

            ; --- test 16-bit and 8-bit immediate to X load (with sign extention)
            ld x, 0xacbc
            mov a, x
            cmp a, 0xacbc
            jne error
            ld x, 18
            mov a, x
            cmp a, 0x0012
            jne error
            ld x, -5
            mov a, x
            cmp a, 0xfffb
            jne error

            ; --- test 16-bit and 8-bit immediate to Y load (with sign extention)
            ld y, 0xab17
            mov a, y
            cmp a, 0xab17
            jne error
            ld y, 17
            mov a, y
            cmp a, 0x0011
            jne error
            ld y, -4
            mov a, y
            cmp a, 0xfffc
            jne error

            ; --- test stack relative accumulator loads
            ld a, 0x7000
            mov sp, a
            ld a, 0x1234
            push a
            ld a, 0x5678
            push a
            ld a, 0x9abc
            push a
            ld a, 0xdef0
            push a
            pop a

            ld a, (sp:-2)       ; test ld a, (sp:#i8) for negative offset
            cmp a, 0xdef0
            jne error

            ld a, (sp:2)        ; test ld a, (sp:#i8) for positive offset
            cmp a, 0x5678
            jne error

            ld a, (sp)          ; test ld a, (sp)
            cmp a, 0x9abc
            jne error

            mov a, sp
            add a, 0x1111
            mov dp, a
            ld a, 0x1717
            st (dp:0), a
            xor a, a

            ld a, (sp:0x1111)   ; test ld a, (sp:#i16)
            cmp a, 0x1717
            jne error

            ; --- test stack relative X register loads
            ld a, 0xd100
            mov sp, a
            ld a, 0x1234
            push a
            ld a, 0x5678
            push a
            ld a, 0x9abc
            push a
            ld a, 0xdef0
            push a
            pop a

            ld x, (sp:-2)       ; test ld x, (sp:#i8) for negative offset
            mov a, x
            cmp a, 0xdef0
            jne error

            ld x, (sp:2)        ; test ld x, (sp:#i8) for positive offset
            mov a, x
            cmp a, 0x5678
            jne error

            ld x, (sp)          ; test ld x, (sp)
            mov a, x
            cmp a, 0x9abc
            jne error

            mov a, sp
            add a, 0x1111
            mov dp, a
            ld a, 0x1717
            st (dp:0), a

            ld x, (sp:0x1111)   ; test ld x, (sp:#i16)
            mov a, x
            cmp a, 0x1717
            jne error

            ; --- test stack relative Y register loads
            ld a, 0xd200
            mov sp, a
            ld a, 0x1234
            push a
            ld a, 0x5678
            push a
            ld a, 0x9abc
            push a
            ld a, 0xdef0
            push a
            pop a

            ld y, (sp:-2)       ; test ld y, (sp:#i8) for negative offset
            mov a, y
            cmp a, 0xdef0
            jne error

            ld y, (sp:2)        ; test ld y, (sp:#i8) for positive offset
            mov a, y
            cmp a, 0x5678
            jne error

            ld y, (sp)          ; test ld y, (sp)
            mov a, y
            cmp a, 0x9abc
            jne error

            mov a, sp
            add a, 0x1111
            mov dp, a
            ld a, 0x1717
            st (dp:0), a

            ld y, (sp:0x1111)   ; test ld y, (sp:#i16)
            mov a, y
            cmp a, 0x1717
            jne error

            ; --- test register indirect accumulator loads

            ld a, 0x7000
            ld x, 12345
            st (a:0), x

            mov dp, a
            ld a, (dp)          ; test ld a, (dp)
            cmp a, 12345
            jne error

            ld a, 0x1001
            mov dp, a
            ld a, 0x5fff
            mov x, a
            mov y, a

            xor a, a
            ld a, (dp:x)        ; test ld a, (dp:x)
            cmp a, 12345
            jne error

            xor a, a
            ld a, (dp:y)        ; test ld a, (dp:y)
            cmp a, 12345
            jne error

            ld a, 0x1001
            mov dp, a
            mov x, a
            mov y, a

            ld a, (dp:0x5fff)   ; test ld a, (dp:#i16)
            cmp a, 12345
            jne error

            xor a, a
            ld a, (x:0x5fff)    ; test ld a, (x:#i16)
            cmp a, 12345
            jne error

            xor a, a
            ld a, (y:0x5fff)    ; test ld a, (y:#i16)
            cmp a, 12345
            jne error

            ld a, 1
            ld a, (a:0x6fff)    ; test ld a, (a:#i16)
            cmp a, 12345
            jne error

            ; --- test register indirect X register loads

            ld a, 0x7000
            ld x, 12345
            st (a:0), x

            ld a, 0x1001
            mov dp, a
            mov x, a
            mov y, a

            ld x, (a:0x5fff)    ; test ld x, (a:#i16)
            mov a, x
            cmp a, 12345
            jne error

            ld x, (dp:0x5fff)   ; test ld x, (dp:#i16)
            mov a, x
            cmp a, 12345
            jne error

            ld x, 1
            ld x, (x:0x6fff)    ; test ld x, (x:#i16)
            mov a, x
            cmp a, 12345
            jne error

            ld x, (y:0x5fff)    ; test ld x, (y:#i16)
            mov a, x
            cmp a, 12345
            jne error

            ; --- test register indirect Y register loads

            ld a, 0x7000
            ld x, 12345
            st (a:0), x

            ld a, 0x1001
            mov dp, a
            mov x, a
            mov y, a

            ld y, (a:0x5fff)    ; test ld y, (a:#i16)
            mov a, y
            cmp a, 12345
            jne error

            ld y, (dp:0x5fff)   ; test ld y, (dp:#i16)
            mov a, y
            cmp a, 12345
            jne error

            ld y, 1
            ld y, (y:0x6fff)    ; test ld y, (y:#i16)
            mov a, y
            cmp a, 12345
            jne error

            ld y, (x:0x5fff)    ; test ld y, (y:#i16)
            mov a, y
            cmp a, 12345
            jne error

pass:
            ld a, 0xabcd
            halt

error:
            ld a, 0xdead
            halt
