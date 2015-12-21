; Test suite - set 09
; memory paging
;
; Test success: machine halts with value 0xabcd in register A
; Test fail:    otherwise


_start:

            ; set-up fault handler
            ld a, 0x0010 + 0
            mov dp, a
            ld a, mv_handler
            st (dp), a
            
            ; supervisor mode

            ld a, 0x2000
            mov dp, a
            ld al, 0x00
            st (dp:0), al       ; set physical page #0 (0) for logical code page #0

            ld a, 0x2200
            mov dp, a
            ld al, 0x01
            st (dp:0), al       ; set physical page #1 (1) for logical code page #1

            ld a, 0x2400
            mov dp, a
            ld al, 0x11
            st (dp:0), al       ; set physical page #11 (17) for logical data page #0

            ld a, 0x2600
            mov dp, a
            ld al, 0x04
            st (dp:0), al       ; set physical page #4 (4) for logical data page #1

            ld a, 0x8100
            mov dp, a
            ld a, 0x5678
            st (dp:5), a        ; value 0x5678 @ page #4 (4), offset 105

            ld a, 0x0100
            mov dp, a
            ld a, 0x1234
            st (dp:1), a        ; value 0x1234 @ 0x00020101 (hardwired physical page #04), offset 101

            ; user mode - code pages are set correctly (same as in supervisor mode), so transition should go fine

            mov al, msw
            or a, 0x0020
            mov msw, al

            ld a, 0x0001
            mov dp, a
            ld a, 0x9012
            st (dp:7), a        ; value 0x9012 @ page #11, offset 8

            ld a, 0xc000
            mov dp, a
            ld a, 0x3456
            st (dp:0), a        ; value 0x3456 @ page #4, offset 0x4000

            ; read what just wrote

            ld a, 0xc000
            mov dp, a
            ld a, (dp:0)
            cmp a, 0x3456
            jne error

            ld a, 0x0008
            mov dp, a
            ld a, (dp:0)
            cmp a, 0x9012
            jne error

            ; check what supervisor wrote

            ld a, 0x8101
            mov dp, a
            ld a, (dp:0)
            cmp a, 0x1234
            jne error

            ld a, 0x8105
            mov dp, a
            ld a, (dp:0)
            cmp a, 0x5678
            jne error
            
            ; back to supervisor mode

            mov al, msw
            and a, 0xffdf
            mov msw, al         ; this will fault but fault handler will change MSW on the stack before returning

            ; check what user mode wrote in page #11 (17)

            ld a, 0x2600
            mov dp, a
            ld al, 0x11
            st (dp:0), al       ; set physical page #11 (17) for logical data page #1

            ld a, 0x8008
            mov dp, a
            ld a, (dp:0)
            cmp a, 0x9012
            jne error

            ld a, 0x4000
            mov dp, a
            ld a, (dp:0)
            cmp a, 0x3456
            jne error

pass:
            ld a, 0xabcd
            halt
error:
            ld a, 0xdead
            halt

mv_handler:
            ld al, (sp:12)       ; hack MSW on the stack to return to supervisor mode
            and a, 0xffdf
            st (sp:12), al
            iret
