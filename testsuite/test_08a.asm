; Test suite - set 08 subset a
; test SP/KSP operations
;
; Test success: machine halts with value 0xabcd in register A (KSP=0x00fe SP=0x01fe)
; Test fail:    otherwise


_start:
            ; initialize memory pages
            ld a, 0x2000
            mov dp, a
            ld al, 0
            st (dp), al

            ld a, 0x2200
            mov dp, a
            ld al, 1
            st (dp), al

            ld a, 0x2400
            mov dp, a
            ld al, 4
            st (dp), al

            ld a, 0x2600
            mov dp, a
            ld al, 5
            st (dp), al

            ; setup stack for supervisor mode
            ld a, 0x0100
            mov sp, a                   ; KSP=0x0100

            ; push onto stack in kernel mode
            ld a, 0x8899                ; KSP=0x00fe
            push a

            mov a, sp
            cmp a, 0x00fe
            jne error

            ; switch to user mode
            mov al, msw
            or a, 0x0020
            mov msw, al

            ; set up stack for user mode
            ld a, 0x0200
            mov sp, a                   ; SP=0x0200

            ; push onto stack in user mode
            ld a, 0x5577
            push a                      ; SP=0x01fe

            mov a, sp
            cmp a, 0x01fe
            jne error

            ; here KSP=0x00fe SP=0x01fe

            ld a, 0xabcd
            halt

error:

            ld a, 0xdead
            halt
