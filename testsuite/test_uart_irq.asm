; UART test
;
; UART0, 9600 baud, 8-N-1, no flow control

_start:

        ; initialize memory banks
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

        ; setup stack
        ld a, 0x0000
        mov sp, a

        ; setup UART
       
        ld a, 0x1003    ; set DLA
        mov dp, a
        ld al, 0x80
        st (dp), al     ; divisor latch access

        ld a, 0x1000    ; low word of divisor latch
        mov dp, a
        ld al, 0x0c
        st (dp), al     ; 9600 baud

        ld a, 0x1001    ; high word of divisor latch
        mov dp, a
        ld al, 0x00
        st (dp), al

        ld a, 0x1003    ; set LCR
        mov dp, a
        ld al, 0x03
        st (dp), al     ; 8N1, buffer access

        ld a, 0x1002    ; enable FIFO, clear buffers
        mov dp, a
        ld al, 0xc7
        st (dp), al

        ld x, 0x0004    ; set IRQ2 handler (UART0)
        ld a, irq_handler
        st (x:0), a

        sti             ; enable interrupts in the CPU

        ld a, 0x1001    ; enable UART interrupts
        mov dp, a
        ld al, 0x01
        st (dp), al

        ; transmit prompt

        ld a, 0x1000
        mov dp, a
        ld al, 0x4d
        st (dp), al   ; M
        ld al, 0x6f
        st (dp), al   ; o
        ld al, 0x6e
        st (dp), al   ; n
        ld al, 0x69
        st (dp), al   ; i
        ld al, 0x74
        st (dp), al   ; t
        ld al, 0x6f
        st (dp), al   ; o
        ld al, 0x72
        st (dp), al   ; r
        ld al, 0x3a
        st (dp), al   ; :
        ld al, 0x20
        st (dp), al   ; <sp>

        halt

irq_handler:        
        ld a, 0x1005
        mov dp, a
        ld al, (dp)
        and a, 0x0001
        cmp a, 0x0001
        jne empty
        ld a, 0x1000
        mov dp, a
        ld al, (dp)
        st (dp), al
        jmp irq_handler
empty:
        iret
