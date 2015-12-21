; Test suite - set 11
; Compute Fibonacci Sequence - stress test
;
; Test success: machine runs continuously computing Fibonacci of 10 (does not halt)
; Test fail: 	otherwise

_start:
        ; setup stack
        ld a, 0x5000
        mov sp, a

setup_fibo:
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

        cmp a, 0x0037
        je setup_fibo

error:

        ld x, 0xdead
        halt
