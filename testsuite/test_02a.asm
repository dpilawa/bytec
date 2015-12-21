; Test suite - set 02a
; memory loads (8-bit targets)
;
; Test success: machine halts with value 0xabcd in register A
; Test fail:    otherwise

_start:

            ; immediate loads

            xor a, a
            ld ah, 5            ; load into high byte of A
            ld al, 254          ; load into low byte of A
            cmp a, 0x05fe       ; see how it worked
            jne error

            ; stack relative loads

            ld a, 0x0200        ; first, set up and populate stack
            mov sp, a
            ld a, 0x1234
            push a
            add a, 0x1111
            push a              ; stack memory before 0x0200 should be now 0x23 0x45 0x12 0x34 [SP+0 SP+1 SP+2 SP+3]

            ld a, 0
            ld ah, (sp:1)       ; ld ah, (sp:#i8)
            ld al, (sp:3)       ; ld al, (sp:#i8)
            cmp a, 0x4534
            jne error

            ld a, 1
            mov sp, a
            ld ah, (sp:0x01fe)  ; ld ah, (sp:#i16)
            ld al, (sp:0x01fd)  ; ld al, (sp:#i16)
            cmp a, 0x3412
            jne error

            ; register indirect loads

            ld a, 40000
            ld ah, (a:-39489)   ; ld ah, (a:#i16)
            and a, 0xff00
            cmp a, 0x3400
            jne error

            ld a, 40000
            ld al, (a:-39491)   ; ld al, (a:#i16)
            and a, 0x00ff
            cmp a, 0x0045
            jne error

            ld x, 50000
            ld ah, (x:-49489)   ; ld ah, (x:#i16)
            ld al, (x:-49491)   ; ld al, (x:#i16)
            cmp a, 0x3445
            jne error

            ld a, 0x01fd
            mov dp, a
            ld al, (dp)         ; ld al, (dp)
            cmp a, 0x0145
            jne error

            mov sp, a
            ld x, 0x5555        ; now a different test (forward 16-bit displacement)
            push x
            pop dp
            st (dp:0), a        ; 0x0145 is now at memory location 0x5555 (2 bytes)
            ld y, 0x0100
            ld ah, (y:0x5456)   ; ld ah, (y:#i16)
            ld al, (y:0x5455)   ; ld al, (y:#i16)
            cmp a, 0x4501
            jne error

pass:
            ld a, 0xabcd
            halt

error:
            ld a, 0xdead
            halt

