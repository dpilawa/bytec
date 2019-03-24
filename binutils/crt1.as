; crt1
; set-up stack and base pointers
; jump to main 
; provide integer multiplication, division and modulo routines

    .extern _main

    .global __mulu16
    .global __divu16
    .global __modu16
    .global __muli16
    .global __divi16
    .global __modi16

	.text
	
; setup stack and global pointer

    ld a, 0x1000
	mov sp, a
    ld a, 0x0000
	mov dp, a
	
; jump to main
    
    call _main
__halt:	
	jmp __halt

; implement integer arithmetics

; 16-bit unsigned * unsigned - shift and add algorithm
__mulu16:
    ld y, 0     ; product
__mulu16_1:
    push a
    and a, 1
    jz __mulu16_2
    add y, x
__mulu16_2:
    mov a, x
    shl a
    mov x, a
    pop a
    shr a
    jnz __mulu16_1
    mov a, y
    ret

; 16-bit unsigned / unsigned - long division algorithm
__divu16:
    push a      ; N (sp:8)
    push x      ; D (sp:6)
    ld a, 0
    push a      ; Q (sp:4)
    push a      ; R (sp:2)
    ld a, 0b1000000000000000
    push a      ; mask (sp:0)
    ld x, 16
__divu16_1:
    ld a, (sp:2)
    shl a 
    mov y, a
    ld a, (sp:8)
    shl a
    st (sp:8), a
    mov a, y
    ld y, 0
    adc a, y
    cmp a, (sp:6)
    jlu __divu16_2
    sub a, (sp:6)
    st (sp:2), a
    ld a, (sp:0)
    or a, (sp:4)
    st (sp:4), a
    jmp __divu16_3
__divu16_2:
    st (sp:2), a
__divu16_3:
    ld a, (sp:0)
    shr a
    st (sp:0), a
    sub x, 1
    jnz __divu16_1
    ld a, (sp:4)
    add sp, 10
    ret

; 16-bit unsigned / unsigned - long division algorithm
; simplified for remainder, quotiend discarded
__modu16:
    push a      ; N (sp:4)
    push x      ; D (sp:2)
    ld a, 0
    push a      ; R (sp:0)
    ld x, 16
__modu16_1:
    ld a, (sp:0)
    shl a
    mov y, a
    ld a, (sp:4)
    shl a
    st (sp:4), a
    mov a, y
    ld y, 0
    adc a, y
    cmp a, (sp:2)
    jlu __modu16_2
    sub a, (sp:2)
__modu16_2:
    st (sp:0), a
    sub x, 1
    jnz __modu16_1
    add sp, 6 
    ret


; 16-bit signed * signed - determine sign + shift and add algorithm
__muli16:
    ; check if multiplier is negative, and if yes then
    ; negate both numbers and do unsigned multiplication
    cmp a, 0
    jg __muli16_1
    ld y, -1
    xor a, y
    add a, 1
    push a
    mov a, x
    xor a, y
    add a, 1
    mov x, a
    pop a
__muli16_1:
    call __mulu16
    ret

__divi16:
    ; convert to positive, divide as signed numbers
    ; fix quotient sign afterwards 
    push a      
    push a
    xor a, x
    and a, 0b10000000
    st (sp:2), a ; remember sign
    pop a
    ld y, -1
    cmp a, 0
    jg __divi16_1
    xor a, y
    add a, 1
__divi16_1:
    push a
    mov a, x
    cmp a, 0
    jg __divi16_2
    xor a, y
    add a, 1
    mov x, a
__divi16_2:
    pop a
    call __divu16
    push a
    ld a, (sp:2)
    cmp a, 0
    pop a
    je __divi16_3
    ld y, -1
    xor a, y
    add a, 1
__divi16_3:
    pop x ; discard sign
    ret

__modi16:
    ; convert to positive, divide as signed numbers
    ; fix reminder sign afterwards 
    push a ; remember dividend sign
    ld y, -1
    cmp a, 0
    jg __modi16_1
    xor a, y
    add a, 1
__modi16_1:
    push a
    mov a, x
    cmp a, 0
    jg __modi16_2
    xor a, y
    add a, 1
    mov x, a
__modi16_2:
    pop a
    call __modu16
    push a
    ld a, (sp:2)
    cmp a, 0
    pop a
    jg __modi16_3
    ld y, -1
    xor a, y
    add a, 1
__modi16_3:
    pop x ; discard dividend sign
    ret

