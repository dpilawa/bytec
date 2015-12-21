; Homebuilt 16-bit Computer OS/Monitor
; Dawid Pilawa (C) 2011, 2012
;
; Kernel shell
;
; --------------------------------------------------------------

; text segment
; --------------------------------------------------------------

        .text

__krn_shell:

        ld dp, emptystr             ; newline
        syscall KRN_UART_PSTRNL

        ld dp, m_hint               ; display help hint
        syscall KRN_UART_PSTRNL

__krn_shell_prompt:

        ld dp, emptystr             ; newline
        syscall KRN_UART_PSTRNL
        
        ld dp, prompt               ; display prompt
        syscall KRN_UART_PSTR
        
        ld dp, usrc                 ; read user command
        syscall KRN_UART_GSTR
                
        ld dp, usrc                 ; HALT
        ld x, c_halt                
        call __krn_strcmp
        cmp al, 0
        je krn_shell_exit

        ld dp, usrc                 ; HELP
        ld x, c_help                
        call __krn_strcmp
        cmp al, 0
        je krn_shell_help

        ld dp, usrc                 ; DDMP
        ld x, c_ddmp
        call __krn_strcmp
        cmp al, 0
        ld ah, 0
        je krn_shell_mdmp

        ld dp, usrc                 ; CDMP
        ld x, c_cdmp
        call __krn_strcmp
        cmp al, 0
        ld ah, 1
        je krn_shell_mdmp

        ld dp, usrc                 ; REGS
        ld x, c_regs
        call __krn_strcmp
        cmp al, 0
        je krn_shell_regs

        ld dp, usrc                 ; TIME
        ld x, c_time
        call __krn_strcmp
        cmp al, 0
        je krn_shell_time
    
        ld dp, m_inv
        syscall KRN_UART_PSTR   
        ld dp, usrc
        syscall KRN_UART_PSTR
        ld dp, m_apo
        syscall KRN_UART_PSTRNL
        
        jmp __krn_shell_prompt

; EXIT - halt the machine
krn_shell_exit:        
        ; spin down IDE master device
        ld al, 0x00
        syscall KRN_IDE_DEVSEL
        cmp al, 0xff
        je krn_shell_exit_sl
        syscall KRN_IDE_SPINDOWN
krn_shell_exit_sl:        
        ; spin down IDE slave device
        ld al, 0x01
        syscall KRN_IDE_DEVSEL      
        cmp al, 0xff
        je krn_shell_exit_end
        syscall KRN_IDE_SPINDOWN
krn_shell_exit_end:        
        ; display message
        ld dp, m_halted
        syscall KRN_UART_PSTRNL
        ret

; HELP - print help information
krn_shell_help:        
        ld dp, m_help1
        syscall KRN_UART_PSTRNL
        ld dp, m_help2
        syscall KRN_UART_PSTRNL
        ld dp, m_help3
        syscall KRN_UART_PSTRNL
        ld dp, m_help4
        syscall KRN_UART_PSTRNL
        ld dp, m_help5
        syscall KRN_UART_PSTRNL
        ld dp, m_help6
        syscall KRN_UART_PSTRNL
        ld dp, m_help7
        syscall KRN_UART_PSTRNL
        ld dp, m_help8
        syscall KRN_UART_PSTRNL
        ld dp, m_help9
        syscall KRN_UART_PSTRNL
        ld dp, m_help10
        syscall KRN_UART_PSTRNL
        ld dp, m_help11
        syscall KRN_UART_PSTRNL                
        ld dp, m_help12
        syscall KRN_UART_PSTRNL 
        jmp __krn_shell_prompt

; MDMP - dump memory contents (AH=01 code; data otherwise)
krn_shell_mdmp:
        ld dp, 0x1020
        ld x,  0x0100
krn_shell_mdmp_loop:

        push dp                     ; print address    
        push x
        push a
        mov a, dp
        ld dp, vt100bold
        syscall KRN_UART_PSTR
        ld dp, strbuf
        call __krn_prnhexw
        syscall KRN_UART_PSTR
        ld dp, vt100norm
        syscall KRN_UART_PSTR
        ld dp, m_space
        syscall KRN_UART_PSTR
        syscall KRN_UART_PSTR
        pop a
        pop x
        pop dp

        push x                      ; print 16 hex bytes
        push dp
        ld y, SHL_DUMPLINEWIDTH
krn_shell_mdmp_loop_hex:
        push x
        push y
        push a
        ld al, (dp)
        cmp ah, 0x01
        jne krn_shell_mdmp_loop_hex_data
        xor x,x
        ldc al, (dp:x)
krn_shell_mdmp_loop_hex_data:
        add dp, 1
        push dp
        ld dp, strbuf
        call __krn_prnhexb
        syscall KRN_UART_PSTR
        ld dp, m_space
        syscall KRN_UART_PSTR
        pop dp
        pop a
        pop y
        pop x        
        dec x
        jz krn_shell_mdmp_loop_hex_align
        dec y
        jz krn_shell_mdmp_loop_hex_end
        jmp krn_shell_mdmp_loop_hex
krn_shell_mdmp_loop_hex_align:
        dec y
        jz krn_shell_mdmp_loop_hex_end
        ld dp, m_space
        syscall KRN_UART_PSTR
        syscall KRN_UART_PSTR
        syscall KRN_UART_PSTR
        jmp krn_shell_mdmp_loop_hex_align
krn_shell_mdmp_loop_hex_end:

        ld dp, m_space
        syscall KRN_UART_PSTR

        pop dp                      ; print 16 ascii bytes
        pop x
        ld y, SHL_DUMPLINEWIDTH
krn_shell_mdmp_loop_asc:
        push x
        push a
        ld al, (dp)
        cmp ah, 0x01
        jne krn_shell_mdmp_loop_asc_data
        xor x,x
        ldc al, (dp:x)
krn_shell_mdmp_loop_asc_data:
        add dp, 1
        push dp
        cmp al, 0x20
        jl krn_shell_mdmp_loop_asc_dot
        syscall KRN_UART_PUTC
        jmp krn_shell_mdmp_loop_asc_nodot
krn_shell_mdmp_loop_asc_dot:
        ld dp, m_dot
        syscall KRN_UART_PSTR
krn_shell_mdmp_loop_asc_nodot:
        pop dp
        pop a
        pop x
        dec x
        jz krn_shell_mdmp_end
        dec y
        jnz krn_shell_mdmp_loop_asc
        
        push dp                     ; print new line
        ld dp, emptystr
        syscall KRN_UART_PSTRNL
        pop dp
        
        jmp krn_shell_mdmp_loop
        
krn_shell_mdmp_end:                 ; end

        ld dp, emptystr
        syscall KRN_UART_PSTRNL

        jmp __krn_shell_prompt


; REGS - display register contents
krn_shell_regs:        
        
        push pc
        push sp
        push dp
        push y
        push x
        push a
        
        ld dp, m_reg_a              ; A
        syscall KRN_UART_PSTR
        ld dp, strbuf
        pop a
        call __krn_prnhexw
        syscall KRN_UART_PSTR
        ld dp, emptystr
        syscall KRN_UART_PSTR
        ld dp, m_space
        syscall KRN_UART_PSTR
        
        ld dp, m_reg_x              ; X
        syscall KRN_UART_PSTR
        ld dp, strbuf
        pop a
        call __krn_prnhexw
        syscall KRN_UART_PSTR
        ld dp, emptystr
        syscall KRN_UART_PSTR
        ld dp, m_space
        syscall KRN_UART_PSTR

        ld dp, m_reg_y              ; Y
        syscall KRN_UART_PSTR
        ld dp, strbuf
        pop a
        call __krn_prnhexw
        syscall KRN_UART_PSTR
        ld dp, emptystr
        syscall KRN_UART_PSTR
        ld dp, m_space
        syscall KRN_UART_PSTR

        ld dp, m_reg_dp             ; DP
        syscall KRN_UART_PSTR
        ld dp, strbuf
        pop a
        call __krn_prnhexw
        syscall KRN_UART_PSTR
        ld dp, emptystr
        syscall KRN_UART_PSTR
        ld dp, m_space
        syscall KRN_UART_PSTR

        ld dp, m_reg_sp             ; SP
        syscall KRN_UART_PSTR
        ld dp, strbuf
        pop a
        call __krn_prnhexw
        syscall KRN_UART_PSTR
        ld dp, emptystr
        syscall KRN_UART_PSTR
        ld dp, m_space
        syscall KRN_UART_PSTR

        ld dp, m_reg_pc             ; PC
        syscall KRN_UART_PSTR
        ld dp, strbuf
        pop a
        call __krn_prnhexw
        syscall KRN_UART_PSTR
        ld dp, emptystr
        syscall KRN_UART_PSTR
        ld dp, m_space
        syscall KRN_UART_PSTR

        ld dp, m_reg_msw            ; MSW
        syscall KRN_UART_PSTR
        ld dp, strbuf
        mov al, msw
        call __krn_prnhexb
        syscall KRN_UART_PSTR   

        ld dp, emptystr
        syscall KRN_UART_PSTRNL

        jmp __krn_shell_prompt


; TIME - display current date & time
krn_shell_time:        

        ld dp, REG_RTC
        ld al, 0x0f
        st (dp:14), al

        ld dp, REG_RTC              ; day of week
        xor a, a
        ld al, (dp:8)
        sub a, 1
        shl a
        shl a
        add a, m_time_wday
        mov dp, a
        syscall KRN_UART_PSTR
        ld dp, m_comma
        syscall KRN_UART_PSTR
        ld dp, m_space
        syscall KRN_UART_PSTR

        ld dp, REG_RTC              ; day
        ld al, (dp:6)
        ld ah, 0
        shr a
        shr a
        shr a
        shr a
        ld dp, strbuf
        call __krn_prndecw
        syscall KRN_UART_PSTR

        ld dp, REG_RTC
        ld al, (dp:6)
        ld ah, 0
        and al, 0b00001111
        ld dp, strbuf
        call __krn_prndecw
        syscall KRN_UART_PSTR

        ld dp, m_space
        syscall KRN_UART_PSTR

        ld dp, REG_RTC              ; month
        xor a, a
        ld al, (dp:9)
        and al, 0b00010000
        jz krn_shell_time_m10
        add al, 2
krn_shell_time_m10:
        push a
        ld al, (dp:9)
        and al, 0b00001111
        add al, (sp:1)
        ld ah, 0
        sub a, 1
        shl a
        shl a
        add a, m_time_mon
        mov dp, a
        syscall KRN_UART_PSTR
        ld dp, m_space
        syscall KRN_UART_PSTR
        pop a
        
        
        ld a, 20                    ; year
        ld dp, strbuf
        call __krn_prndecw
        syscall KRN_UART_PSTR          
        
        ld dp, REG_RTC
        ld al, (dp:10)
        ld ah, 0
        shr a
        shr a
        shr a
        shr a
        ld dp, strbuf
        call __krn_prndecw
        syscall KRN_UART_PSTR        

        ld dp, REG_RTC
        ld al, (dp:10)
        ld ah, 0
        and al, 0b00001111
        ld dp, strbuf
        call __krn_prndecw
        syscall KRN_UART_PSTR

        ld dp, m_space
        syscall KRN_UART_PSTR

        
        ld dp, REG_RTC              ; hour
        ld al, (dp:4)
        ld ah, 0
        shr a
        shr a
        shr a
        shr a
        and al, 0b00000011
        ld dp, strbuf
        call __krn_prndecw
        syscall KRN_UART_PSTR

        ld dp, REG_RTC
        ld al, (dp:4)
        ld ah, 0
        and al, 0b00001111
        ld dp, strbuf
        call __krn_prndecw
        syscall KRN_UART_PSTR

        ld dp, m_colon
        syscall KRN_UART_PSTR

        ld dp, REG_RTC              ; minute
        ld al, (dp:2)
        ld ah, 0
        shr a
        shr a
        shr a
        shr a
        ld dp, strbuf
        call __krn_prndecw
        syscall KRN_UART_PSTR

        ld dp, REG_RTC
        ld al, (dp:2)
        ld ah, 0
        and al, 0b00001111
        ld dp, strbuf
        call __krn_prndecw
        syscall KRN_UART_PSTR

        ld dp, m_colon
        syscall KRN_UART_PSTR

        ld dp, REG_RTC              ; second
        ld al, (dp)
        ld ah, 0
        shr a
        shr a
        shr a
        shr a
        ld dp, strbuf
        call __krn_prndecw
        syscall KRN_UART_PSTR

        ld dp, REG_RTC
        ld al, (dp)
        ld ah, 0
        and al, 0b00001111
        ld dp, strbuf
        call __krn_prndecw
        syscall KRN_UART_PSTRNL        

        ld dp, REG_RTC
        ld al, 0x07
        st (dp:14), al
        
        jmp __krn_shell_prompt

; data segment
; --------------------------------------------------------------
        
        .data
        
; prompt message
        
prompt      db '> ', 0x00

; commands

c_help      db 'help', 0x00     ; display help message
c_ddmp      db 'ddmp', 0x00     ; dump data memory contents
c_cdmp      db 'cdmp', 0x00     ; dump code memory contents
c_mset      db 'mset', 0x00     ; set memory contents
c_regs      db 'regs', 0x00     ; display registers
c_halt      db 'halt', 0x00     ; halt the machine
c_time      db 'time', 0x00     ; display current date & time

; help text

m_help1     db 'help                          - print this help information', 0
m_help2     db 'halt                          - exit and halt the machine', 0
m_help3     db 'ddmp adr<hex16> cnt<hex16>    - display data memory content' , 0
m_help4     db 'cdmp adr<hex16> cnt<hex16>    - display code memory content' , 0
m_help5     db 'disa adr<hex16> cnt<hex16>    - disassemble code memory content', 0
m_help6     db 'regs                          - display register contents', 0
m_help7     db 'cdep adr<hex16> b<hex8> (...) - deposit bytes at code memory', 0
m_help8     db 'ddep adr<hex16> b<hex8> (...) - deposit bytes at data memory', 0
m_help9     db 'lser                          - load user program from serial' , 0
m_help10    db 'exec                          - execute loaded user program' , 0
m_help11    db 'lexe                          - load & execute program from serial', 0
m_help12    db 'time                          - display current date & time', 0

; strings

m_hint      db 'Use ''help'' to list vailable commands.', 0x00
m_inv       db 'Invalid command ''', 0x00
m_halted    db 'Machine halted', 0x00
m_apo       db '''', 0x00 
m_dot       db '.', 0x00
m_comma     db ',', 0x00
m_space     db ' ', 0x00
m_colon     db ':', 0x00

m_reg_a     db 'A=', 0x00
m_reg_x     db 'X=', 0x00
m_reg_y     db 'Y=', 0x00
m_reg_dp    db 'DP=', 0x00
m_reg_sp    db 'SP=', 0x00
m_reg_pc    db 'PC=', 0x00
m_reg_msw   db 'MSW=', 0x00

m_time_mon  db 'Jan', 0x00, 'Feb', 0x00, 'Mar', 0x00, 'Apr', 0x00, 
               'May', 0x00, 'Jun', 0x00, 'Jul', 0x00, 'Aug', 0x00,
               'Sep', 0x00, 'Oct', 0x00, 'Nov', 0x00, 'Dec', 0x00

m_time_wday db 'Sun', 0x00, 'Mon', 0x00, 'Tue', 0x00, 'Wed', 0x00,
               'Thu', 0x00, 'Fri', 0x00, 'Sat', 0x00

; data structures

usrc        db 0x00:128
