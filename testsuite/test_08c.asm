; Test suite - set 08 subset c
; test interrupts
;
; this test requires that interrupt lines are asserted (low active)
;
; below is the snippet from Computer.cpp in the simulator
;   // assert interrupt lines
;   if (cycle == 130) irq->go(2, time, 5000);
;   if (cycle == 140) irq->go(3, time, 5000);
;   if (cycle == 150) irq->go(4, time, 5000);
;
; interrupt handlers should change A, X and Y register values
; interrupt priority should be enforced by priority encoders

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

            ; setup stack
            ld a, 0x0000
            mov sp, a

            ; set interrupt vector for IRQ2
            ld a, 0x0004
            mov dp, a
            ld a, isr2
            st (dp:0), a

            ; set interrupt vector for IRQ3
            ld a, 0x0006
            mov dp, a
            ld a, isr3
            st (dp:0), a

            ; set interrupt vector for IRQ4
            ld a, 0x0008
            mov dp, a
            ld a, isr4
            st (dp:0), a

            ; setup machine state
            ld x, 0x3344
            ld y, 0x5566
            mov al, msw
            and a, 0xfff0   ; clear CZNV
            mov msw, al
            ld a, 0x1122

            ; pre-interrupt: A=0x1122 X=0x3344 Y=0x5566

            ; enable interrupts, go to user mode and halt
            sti
            
            mov al, msw
            or  a, 0x0020
            mov msw, al

            halt

isr3:
            ; interrupt driver
            ld a, 0x3030
            add a, 0x0303
            mov x, a
            mov y, a
            iret

isr2:
            ; interrupt driver
            ld a, 0x2020
            add a, 0x0202
            mov x, a
            mov y, a
            iret

isr4:
            ; interrupt driver
            ld a, 0x4040
            add a, 0x0404
            mov x, a
            mov y, a
            iret
