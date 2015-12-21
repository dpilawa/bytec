; Test suite - set 10
; Compute Fibonacci Sequence
;
; Test success: machine halts with value 0x0037 (decimal 55) in register A
; Test fail: 	otherwise

_start:

        ; setup stack
        ld a, 0x5000
        mov sp, a

        ; compute fibonacci(10)
        ld a, 1		; fib(1)
        ld x, 0		; fib(0)
        ld y, 9
fibo:
        push a
        add a, x
        pop x
        dec y
        jnz fibo

        halt
