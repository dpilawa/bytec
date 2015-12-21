; Test suite - set 06
; bitwise operations
;
; Test success: machine halts with valie 0xabcd in register A
; Test fail:    otherwise

_start:

            ; initialize data memory pages

            ld x, 0x2400
            ld al, 4
            st (x:0), al

            ld x, 0x2600
            ld al, 5
            st (x:0), al

            ; AND

            ld a, 0x2345    ; and a, #i16
            and a, 0x0ff0
            cmp a, 0x0340
            jne error

            ld a, 0x2345    ; and a, x
            ld x, 0xf00f
            and a, x
            cmp a, 0x2005
            jne error

            ld a, 0x2345    ; and a, y
            ld y, 0xf0f0
            and a, y
            cmp a, 0x2040
            jne error

            ld a, 0xa000    ; and a, (sp)
            mov sp, a
            ld a, 0xf00f
            st (sp), a
            ld a, 0x2345
            and a, (sp)
            cmp a, 0x2005
            jne error

            ld a, 0xa000+4
            mov sp, a
            ld a, 0xf00f    ; and a, (sp:#i8)
            push a
            push a          ; stack now contains f0 0f f0 0f
            ld a, 0x2345
            and a, (sp:1)   ; & 0ff0
            cmp a, 0x0340
            jne error

            ld a, 0x0000    ; and a, (sp:#i16)
            mov sp, a
            ld a, 0x2345
            and a, (sp:0xa002)
            cmp a, 0x2005
            jne error

            ld a, 0x0000    ; and a, (dp:#i16)
            mov dp, a
            ld a, 0x2345
            and a, (dp:0xa001)
            cmp a, 0x0340
            jne error

            ld a, 0xa000    ; and ah, (sp)
            mov sp, a
            ld a, 0x2345
            and ah, (sp)
            cmp a, 0x2045
            jne error

            ld a, 0xa000    ; and ah, (sp:#i8)
            mov sp, a
            ld a, 0x2345
            and ah, (sp:1)
            cmp a, 0x0345
            jne error

            ld a, 0x0000    ; and ah, (sp:#i16)
            mov sp, a
            ld a, 0x2345
            and ah, (sp:0xa000)
            cmp a, 0x2045
            jne error

            ld a, 0x0000    ; and ah, (dp:#i16)
            mov dp, a
            ld a, 0x2345
            and ah, (dp:0xa001)
            cmp a, 0x0345
            jne error

            ld a, 0xa000    ; and al, (sp)
            mov sp, a
            ld a, 0x2345
            and al, (sp)
            cmp a, 0x2340
            jne error

            ld a, 0xa000    ; and al, (sp:#i8)
            mov sp, a
            ld a, 0x2345
            and al, (sp:1)
            cmp a, 0x2305
            jne error

            ld a, 0x0000    ; and al, (sp:#i16)
            mov sp, a
            ld a, 0x2345
            and al, (sp:0xa000)
            cmp a, 0x2340
            jne error

            ld a, 0x0000    ; and al, (dp:#i16)
            mov dp, a
            ld a, 0x2345
            and al, (dp:0xa001)
            cmp a, 0x2305
            jne error

            ; OR

            ld a, 0x2345    ; or a, #i16
            or a, 0x0ff0
            cmp a, 0x2ff5
            jne error

            ld a, 0x2345    ; or a, x
            ld x, 0xf00f
            or a, x
            cmp a, 0xf34f
            jne error

            ld a, 0x0001    ; or a, y
            ld y, 0xfffe
            or a, y
            cmp a, 0xffff
            jne error

            ld a, 0xa000    ; or a, (sp)
            mov sp, a
            ld a, 0xf00f
            st (sp), a
            ld a, 0x2345
            or a, (sp)
            cmp a, 0xf34f
            jne error

            ld a, 0xa000+4
            mov sp, a
            ld a, 0xf00f    ; or a, (sp:#i8)
            push a
            push a          ; stack now contains f0 0f f0 0f
            ld a, 0x2345
            or a, (sp:1)    ; | 0ff0
            cmp a, 0x2ff5
            jne error

            ld a, 0x0000    ; or a, (sp:#i16)
            mov sp, a
            ld a, 0x2345
            or a, (sp:0xa002)
            cmp a, 0xf34f
            jne error

            ld a, 0x0000    ; or a, (dp:#i16)
            mov dp, a
            ld a, 0x2345
            or a, (dp:0xa001)
            cmp a, 0x2ff5
            jne error

            ld a, 0xa000    ; or ah, (sp)
            mov sp, a
            ld a, 0x2345
            or ah, (sp)
            cmp a, 0xf345
            jne error

            ld a, 0xa000    ; or ah, (sp:#i8)
            mov sp, a
            ld a, 0x2345
            or ah, (sp:1)
            cmp a, 0x2f45
            jne error

            ld a, 0x0000    ; or ah, (sp:#i16)
            mov sp, a
            ld a, 0x2345
            or ah, (sp:0xa000)
            cmp a, 0xf345
            jne error

            ld a, 0x0000    ; or ah, (dp:#i16)
            mov dp, a
            ld a, 0x2345
            or ah, (dp:0xa001)
            cmp a, 0x2f45
            jne error

            ld a, 0xa000    ; or al, (sp)
            mov sp, a
            ld a, 0x2345
            or al, (sp)
            cmp a, 0x23f5
            jne error

            ld a, 0xa000    ; or al, (sp:#i8)
            mov sp, a
            ld a, 0x2345
            or al, (sp:1)
            cmp a, 0x234f
            jne error

            ld a, 0x0000    ; or al, (sp:#i16)
            mov sp, a
            ld a, 0x2345
            or al, (sp:0xa000)
            cmp a, 0x23f5
            jne error

            ld a, 0x0000    ; or al, (dp:#i16)
            mov dp, a
            ld a, 0x2345
            or al, (dp:0xa001)
            cmp a, 0x234f
            jne error

            ; XOR

            ld a, 0xfeef    ; xor a, #i16
            xor a, 0x011f
            cmp a, 0xfff0
            jne error

            ld a, 0x8734    ; xor a, a
            xor a, a
            jnz error

            ld a, 0x0110    ; xor a, x
            ld x, 0x5555
            xor a, x
            cmp a, 0x5445
            jne error

            ld a, 0x3322    ; xor a, y
            ld y, 0x5577
            xor a, y
            cmp a, 0x6655
            jne error

            ld x, 0x3802    ; xor x, x
            xor x, x
            jnz error

            ld y, 0x8927    ; xor y, y
            xor y,y
            jnz error

            ; 16-bit shifts

            ld a, 0xffff    ; shl a
            shl a
            jnc error       ; carry flag should be generated of pushed out MSB
            cmp a, 0xfffe
            jne error
            ld a, 0x7fff
            shl a
            jc error
            cmp a, 0xfffe
            jne error
            ld a, 0x8000
            shl a           ; set carry flag
            ld a, 0x8000
            shl a
            cmp a, 0        ; carry should NOT be pushed into LSB
            jne error

            ld x, 0xf000    ; shl x
            shl x
            jnc error       ; carry flag should be generated of pushed out MSB
            mov a, x
            cmp a, 0xe000
            jne error
            ld x, 0x0001
            shl x
            jc error
            mov a, x
            cmp a, 0x0002
            jne error

            ld y, 0xf000    ; shl y
            shl y
            jnc error       ; carry flag should be generated of pushed out MSB
            mov a, y
            cmp a, 0xe000
            jne error
            ld y, 0x0001
            shl y
            jc error
            mov a, y
            cmp a, 0x0002
            jne error

            ld a, 0xffff    ; shr a
            shr a
            jnc error       ; carry flag should be generated of pushed out LSB
            cmp a, 0x7fff
            jne error
            ld a, 0xfffe
            shr a
            jc error
            cmp a, 0x7fff
            jne error
            ld a, 0x8000
            shl a           ; set carry flag
            ld a, 0x0002
            shr a
            cmp a, 0x0001   ; carry should NOT be pushed into MSB
            jne error

            ld x, 0x0003    ; shr x
            shr x
            jnc error       ; carry flag should be generated of pushed out LSB
            mov a, x
            cmp a, 0x0001
            jne error
            ld x, 0xfffe
            shr x
            jc error
            mov a, x
            cmp a, 0x7fff
            jne error

            ld y, 0x0003    ; shr y
            shr y
            jnc error       ; carry flag should be generated of pushed out LSB
            mov a, y
            cmp a, 0x0001
            jne error
            ld y, 0xfffe
            shr y
            jc error
            mov a, y
            cmp a, 0x7fff
            jne error

            ; 8-bit shifts

            ld a, 0xfff1    ; shl ah
            shl ah
            jnc error
            cmp a, 0xfef1
            jne error
            ld a, 0x7ff1
            shl ah
            jc error
            cmp a, 0xfef1
            jne error

            ld a, 0x00f1    ; shl al
            shl al
            jnc error
            cmp a, 0x00e2
            jne error
            ld a, 0x017f
            shl al
            jc error
            cmp a, 0x01fe
            jne error

            ld a, 0xff00    ; shr ah
            shr ah
            jnc error
            cmp a, 0x7f00
            jne error
            ld a, 0x7e01
            shr ah
            jc error
            cmp a, 0x3f01
            jne error

            ld a, 0x010f    ; shr al
            shr al
            jnc error
            cmp a, 0x0107
            jne error
            ld a, 0x0134
            shr al
            jc error
            cmp a, 0x011a
            jne error

pass:
            ld a, 0xabcd
            halt
error:
            ld a, 0xdead
            halt
