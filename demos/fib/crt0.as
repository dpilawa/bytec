; standard boilerplate when no OS
; set-up memory segments, copy ROM to RAM and jump to main 

	.const #REG_SUPER_CODE0 0x2000
	.const #REG_SUPER_CODE1 0x2200
	.const #REG_SUPER_DATA0 0x2400
	.const #REG_SUPER_DATA1 0x2600

	.extern _main

	.text
	
; copy OS data segment from ROM to RAM and set data banks

	ld a, 0x8000
	mov sp, a
	
	ld x, #REG_SUPER_DATA0
	ld al, 0x06
	st (x:0), al
              
	ld a, 0x8000
__romcopy_lo:
	ld x, #REG_SUPER_DATA1
	push a
	ld al, 0x02
	st (x:0), al
	pop a 
	ld y, (a:0)
	push a
	ld al, 0x04
	st (x:0), al
	pop a 	
	st (a:0), y
	add a, 2
	jnz __romcopy_lo

	ld a, 0x8000
__romcopy_hi:
	ld x, #REG_SUPER_DATA1
	push a
	ld al, 0x03
	st (x:0), al
	pop a 
	ld y, (a:0)
	push a
	ld al, 0x05
	st (x:0), al
	pop a 	
	st (a:0), y
	add a, 2
	jnz __romcopy_hi

	ld x, #REG_SUPER_DATA0
	ld al, 0x04
	st (x:0), al

	ld x, #REG_SUPER_DATA1
	ld al, 0x05
	st (x:0), al 	

; setup stack and global pointer

	ld a, 0x0000
	mov sp, a
	mov dp, a
	
	call _main
	halt

