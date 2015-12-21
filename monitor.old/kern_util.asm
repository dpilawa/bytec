; Homebuilt 16-bit Computer OS/Monitor
; Dawid Pilawa (C) 2011, 2012
;
; Kernel utility functions
;
; --------------------------------------------------------------

; text segment
; --------------------------------------------------------------

        .text

; detect available RAM (result in kB in A)
__krn_memdetect:
        ld al, 4
krn_memdetect_loop:                 ; loop memory banks
        ld dp, REG_DATAPAGE1
        st (dp), al
        add al, 1
        push a
        ld dp, 0xf000               ; check load/store
        ld x, (dp:0)
        push x
        inc x
        st (dp:0), x
        ld x, (dp:0)
        dec x
        st (dp:0), x
        pop a
        cmp a, x
        jne krn_memdetect_end
        pop a
        cmp al, 0x00
        jne krn_memdetect_loop
krn_memdetect_end:
        pop a                       ; compute result in kB
        ld ah, 0
        sub al, 5
        shl a
        shl a
        shl a
        shl a
        shl a
        push a
        ld dp, REG_DATAPAGE1        ; restore memory banks
        ld al, 0x05
        st (dp), al
        pop a        
        ret

; compare two strings (pointers in X and DP, result in AL)
__krn_strcmp:
        push dp
        push x
krn_strcmp_loop:
        ld al, (x:0)
        sub al, (dp:0)
        jnz krn_strcmp_end
        ld ah, 0
        cmp ah, (dp:0) 
        je krn_strcmp_end
        inc x
        add dp, 1
        jmp krn_strcmp_loop
krn_strcmp_end:
        pop x
        pop dp
        ret

; copy string (source in DP, destination in X)
; target buffer pointer set to end of string
__krn_strcpy:
        push dp
krn_strcpy_loop:
        ld al, (dp:0)
        st (x:0), al
		cmp al, 0x00
		je krn_strcpy_end
        inc x
        add dp, 1
        jmp krn_strcpy_loop
krn_strcpy_end:
        pop dp
        ret

; right trim a string (pointer in DP)
__krn_rtrim:
        push dp
        xor y, y
        xor x, x
krn_rtrim_loop:
        ld al, (dp:x)
        inc x
        cmp al, 0x00
        je krn_rtrim_loopend
        cmp al, 0x20
        je krn_rtrim_wspace
        mov y, x
krn_rtrim_wspace:
        jmp krn_rtrim_loop
krn_rtrim_loopend:
        ld al, 0x00
        mov x, y
        st (dp:x), al
        pop dp
        ret

; print hex byte (value in AL, pointer to string in DP)
__krn_prnhexb:
		push a
        push a
        push dp
        and a, 0x000f       ; low nibble
        ld dp, hexd
        mov x, a
        ld al, (dp:x)
        pop dp
        st (dp:1), al
        pop a
        push dp
        and a, 0x00f0       ; high nibble
        shr a
        shr a
        shr a
        shr a
        ld dp, hexd
        mov x, a
        ld al, (dp:x)
        pop dp
        st (dp), al
        st (dp:2), ah       ; end of string
        pop a
        ret

; print hex word (value in A, pointer to string in DP)
__krn_prnhexw:
        push dp
        push a
        ld al, (sp:0)       ; high byte
        call __krn_prnhexb
        ld al, (sp:1)       ; low byte
        add dp, 2
        call __krn_prnhexb
        pop a
        pop dp
        ret

; print decimal word (value in A, pointer to string in DP)
__krn_prndecw:
        push a
        push dp
        ld y, divisors
krn_prndecw_getdiv:
        push a
        ld a, (y:0)
        mov x, a
        cmp a, 1
        pop a
        je krn_prndecw_end
        add y, 2
        push y
        xor y, y
krn_prndecw_check:
        cmp a, x
        jge krn_prndecw_sub
        cmp a, 0
        jge krn_prndecw_next
krn_prndecw_sub:
        inc y
        sub a, x
        jmp krn_prndecw_check
krn_prndecw_next:
        push a
        ld a, decd
        add a, y
        push dp
        mov dp, a
        ld al, (dp)
        pop dp
        cmp al, '0'
        jne krn_prndecw_pdigit
        mov y, a
        mov a, dp
        cmp a, (sp:4)
        mov a, y
        je krn_prndecw_skip
krn_prndecw_pdigit:	
        st (dp), al
        add dp, 1
krn_prndecw_skip:
        pop a
        pop y
        jmp krn_prndecw_getdiv
krn_prndecw_end:
        add a, decd
        push dp
        mov dp, a
        ld al, (dp)
        pop dp
        st (dp), al
        add dp, 1	
        ld al, 0
        st (dp), al
        pop dp
        pop a
        ret

; data segment
; --------------------------------------------------------------

        .data
        
hexd        db '0123456789abcdef'
decd        db '0123456789'
divisors    dw 10000, 1000, 100, 10, 1
