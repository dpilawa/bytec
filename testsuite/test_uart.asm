; UART test
;
; UART0, 9600 baud, 8-N-1, no flow control

_start:
labl2:
lab3:
        ; setup UART
       
        ld a, 0x1003    ; set DLA
        mov dp, a		
        ld al, 0x80
        st (dp), al     ; divisor latch access

        ld a, 0x1000    ; low word of divisor latch
        mov dp, a
        ld al, 12
        st (dp), al     ; 9600 baud

        ld a, 0x1001    ; high word of divisor latch
        mov dp, a
        ld al, 0
        st (dp), al

        ld a, 0x1003    ; set LCR
        mov dp, a
        ld al, 0x03
        st (dp), al     ; 8N1, buffer access

        ld a, 0x1002    ; enable FIFO
        mov dp, a
        ld al, 0x07
        st (dp), al

        ld a, 0x1001    ; disable interrupts
        mov dp, a
        ld al, 0x00
        st (dp), al

        ; transmit 'Hello world!'

        ld a, 0x1000
        mov dp, a
        ld al, 0x48
        st (dp), al   ; H
        ld al, 0x65
        st (dp), al   ; e
        ld al, 0x6c
        st (dp), al   ; l
        st (dp), al   ; l
        ld al, 0x6f
        st (dp), al   ; o
        ld al, 0x20
        st (dp), al   ; <space>
        ld al, 0x77
        st (dp), al   ; w
        ld al, 0x6f
        st (dp), al   ; o
        ld al, 0x72
        st (dp), al   ; r
        ld al, 0x6c
        st (dp), al   ; l
        ld al, 0x64
        st (dp), al   ; d
        ld al, 0x21
        st (dp), al   ; !


        halt
