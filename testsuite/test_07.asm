; Test suite - set 07
; compare and branch
;
; Test success: machine halts with value 0xabcd in register A
; Test fail:    otherwise

_start:

            ; initialize data memory

            ld x, 0x2400
            ld al, 4
            st (x:0), al

            ld x, 0x2600
            ld al, 5
            st (x:0), al

            ; JL JLE JE JNE JG JGE (16-bit comparisons)

            ld a, 64            ; cmp a, #i8
            cmp a, 32
            jg error
            jge error
            je error
            jne next1
            jmp error
next1:      jle next2
            jmp error
next2:      jl next3
            jmp error

next3:      ld a, 32
            cmp a, 64
            jl error
            jle error
            je error
            jne next4
            jmp error
next4:      jge next5
            jmp error
next5:      jg next6
            jmp error

next6:      ld a, -32
            cmp a, -64
            jg error
            jge error
            je error
            jne next7
            jmp error
next7:      jle next8
            jmp error
next8:      jl next9
            jmp error

next9:      ld a, -64
            cmp a, -32
            jl error
            jle error
            je error
            jne next10
            jmp error
next10:     jg next11
            jmp error
next11:     jge next12
            jmp error


next12:     ld a, 1024          ; cmp a, #i16
            cmp a, 512
            jg error
            jge error
            je error
            jne next13
            jmp error
next13:     jle next14
            jmp error
next14:     jl next15
            jmp error

next15:     ld a, 512
            cmp a, 1024
            jl error
            jle error
            je error
            jne next16
            jmp error
next16:     jge next17
            jmp error
next17:     jg next18
            jmp error

next18:     ld a, -512
            cmp a, -1024
            jg error
            jge error
            je error
            jne next19
            jmp error
next19:     jle next20
            jmp error
next20:     jl next21
            jmp error

next21:     ld a, -1024
            cmp a, -512
            jl error
            jle error
            je error
            jne next22
            jmp error
next22:     jg next23
            jmp error
next23:     jge next24
            jmp error

next24:     ld a, 1024          ; cmp a, x
            ld x, 512
            cmp a, x
            jg error
            jge error
            je error
            jne next25
            jmp error
next25:     jle next26
            jmp error
next26:     jl next27
            jmp error

next27:     ld a, 512
            ld x, 1024
            cmp a, x
            jl error
            jle error
            je error
            jne next28
            jmp error
next28:     jge next29
            jmp error
next29:     jg next30
            jmp error

next30:     ld a, -512
            ld x, -1024
            cmp a, x
            jg error
            jge error
            je error
            jne next31
            jmp error
next31:     jle next32
            jmp error
next32:     jl next33
            jmp error

next33:     ld a, -1024
            ld x, -512
            cmp a, x
            jl error
            jle error
            je error
            jne next34
            jmp error
next34:     jg next35
            jmp error
next35:     jge next36
            jmp error

next36:     ld a, 1024          ; cmp a, y
            ld y, 512
            cmp a, y
            jg error
            jge error
            je error
            jne next37
            jmp error
next37:     jle next38
            jmp error
next38:     jl next39
            jmp error

next39:     ld a, 512
            ld y, 1024
            cmp a, y
            jl error
            jle error
            je error
            jne next40
            jmp error
next40:     jge next41
            jmp error
next41:     jg next42
            jmp error

next42:     ld a, -512
            ld y, -1024
            cmp a, y
            jg error
            jge error
            je error
            jne next43
            jmp error
next43:     jle next44
            jmp error
next44:     jl next45
            jmp error

next45:     ld a, -1024
            ld y, -512
            cmp a, y
            jl error
            jle error
            je error
            jne next46
            jmp error
next46:     jg next47
            jmp error
next47:     jge next48
            jmp error

next48:     ld a, 0x0700
            mov sp, a
            ld a, 1024          ; cmp a, (sp)
            ld y, 512
            push y
            cmp a, (sp)
            jg error
            jge error
            je error
            jne next49
            jmp error
next49:     jle next50
            jmp error
next50:     jl next51
            jmp error

next51:     ld a, 512
            ld y, 1024
            push y
            cmp a, (sp)
            jl error
            jle error
            je error
            jne next52
            jmp error
next52:     jge next53
            jmp error
next53:     jg next54
            jmp error

next54:     ld a, -512
            ld y, -1024
            push y
            cmp a, (sp)
            jg error
            jge error
            je error
            jne next55
            jmp error
next55:     jle next56
            jmp error
next56:     jl next57
            jmp error

next57:     ld a, -1024
            ld y, -512
            push y
            cmp a, (sp)
            jl error
            jle error
            je error
            jne next58
            jmp error
next58:     jg next59
            jmp error
next59:     jge next60
            jmp error

next60:     ld a, 1024          ; cmp a, (sp:#i8)
            cmp a, (sp:6)       ; 512
            jg error
            jge error
            je error
            jne next61
            jmp error
next61:     jle next62
            jmp error
next62:     jl next63
            jmp error

next63:     ld a, 512
            cmp a, (sp:4)       ; 1024
            jl error
            jle error
            je error
            jne next64
            jmp error
next64:     jge next65
            jmp error
next65:     jg next66
            jmp error

next66:     ld a, -512
            cmp a, (sp:2)       ; -1024
            jg error
            jge error
            je error
            jne next67
            jmp error
next67:     jle next68
            jmp error
next68:     jl next69
            jmp error

next69:     ld a, -1024
            cmp a, (sp:0)       ; -512
            jl error
            jle error
            je error
            jne next70
            jmp error
next70:     jg next71
            jmp error
next71:     jge next72
            jmp error

next72:     xor a, a
            mov sp, a
            ld a, 1024          ; cmp a, (sp:#i16)
            cmp a, (sp:0x06fe)  ; 512
            jg error
            jge error
            je error
            jne next73
            jmp error
next73:     jle next74
            jmp error
next74:     jl next75
            jmp error

next75:     ld a, 512
            cmp a, (sp:0x06fc)  ; 1024
            jl error
            jle error
            je error
            jne next76
            jmp error
next76:     jge next77
            jmp error
next77:     jg next78
            jmp error

next78:     ld a, -512
            cmp a, (sp:0x06fa)  ; -1024
            jg error
            jge error
            je error
            jne next79
            jmp error
next79:     jle next80
            jmp error
next80:     jl next81
            jmp error

next81:     ld a, -1024
            cmp a, (sp:0x06f8)  ; -512
            jl error
            jle error
            je error
            jne next82
            jmp error
next82:     jg next83
            jmp error
next83:     jge next84
            jmp error

next84:     ld a, 0x0100
            mov dp, a
            ld a, 1024          ; cmp a, (dp:#i16)
            cmp a, (dp:0x05fe)  ; 512
            jg error
            jge error
            je error
            jne next85
            jmp error
next85:     jle next86
            jmp error
next86:     jl next87
            jmp error

next87:     ld a, 512
            cmp a, (dp:0x05fc)  ; 1024
            jl error
            jle error
            je error
            jne next88
            jmp error
next88:     jge next89
            jmp error
next89:     jg next90
            jmp error

next90:     ld a, -512
            cmp a, (dp:0x05fa)  ; -1024
            jg error
            jge error
            je error
            jne next91
            jmp error
next91:     jle next92
            jmp error
next92:     jl next93
            jmp error

next93:     ld a, -1024
            cmp a, (dp:0x05f8)  ; -512
            jl error
            jle error
            je error
            jne next94
            jmp error
next94:     jg next95
            jmp error
next95:     jge next96
            jmp error

            ; JL JLE JE JNE JG JGE (8-bit comparisons)

next96:     ld a, 0x0700
            mov sp, a
            xor a, a
            ld ah, 32
            push ah
            ld ah, 64           ; cmp ah, (sp)
            cmp ah, (sp)
            jg error
            jge error
            je error
            jne next97
            jmp error
next97:     jle next98
            jmp error
next98:     jl next99
            jmp error

next99:     ld ah, 64
            push ah
            ld ah, 32
            cmp ah, (sp)
            jl error
            jle error
            je error
            jne next100
            jmp error
next100:    jge next101
            jmp error
next101:    jg next102
            jmp error

next102:    ld ah, -64
            push ah
            ld ah, -32
            cmp ah, (sp)
            jg error
            jge error
            je error
            jne next103
            jmp error
next103:    jle next104
            jmp error
next104:    jl next105
            jmp error

next105:    ld ah, -32
            push ah
            ld ah, -64
            cmp ah, (sp)
            jl error
            jle error
            je error
            jne next106
            jmp error
next106:    jg next107
            jmp error
next107:    jge next108
            jmp error

next108:    ld ah, 64           ; cmp ah, (sp:#i8)
            cmp ah, (sp:3)      ; 32
            jg error
            jge error
            je error
            jne next109
            jmp error
next109:    jle next110
            jmp error
next110:    jl next111
            jmp error

next111:    ld ah, 32
            cmp ah, (sp:2)      ; 64
            jl error
            jle error
            je error
            jne next112
            jmp error
next112:    jge next113
            jmp error
next113:    jg next114
            jmp error

next114:    ld ah, -32
            cmp ah, (sp:1)      ; -64
            jg error
            jge error
            je error
            jne next115
            jmp error
next115:    jle next116
            jmp error
next116:    jl next117
            jmp error

next117:    ld ah, -64
            cmp ah, (sp:0)      ; -32
            jl error
            jle error
            je error
            jne next118
            jmp error
next118:    jg next119
            jmp error
next119:    jge next120
            jmp error

next120:    ld a, 0
            mov sp, a
            ld ah, 64           ; cmp ah, (sp:#i16)
            cmp ah, (sp:0x06ff) ; 32
            jg error
            jge error
            je error
            jne next121
            jmp error
next121:    jle next122
            jmp error
next122:    jl next123
            jmp error

next123:    ld ah, 32
            cmp ah, (sp:0x06fe) ; 64
            jl error
            jle error
            je error
            jne next124
            jmp error
next124:    jge next125
            jmp error
next125:    jg next126
            jmp error

next126:    ld ah, -32
            cmp ah, (sp:0x06fd) ; -64
            jg error
            jge error
            je error
            jne next127
            jmp error
next127:    jle next128
            jmp error
next128:    jl next129
            jmp error

next129:    ld ah, -64
            cmp ah, (sp:0x06fc) ; -32
            jl error
            jle error
            je error
            jne next130
            jmp error
next130:    jg next131
            jmp error
next131:    jge next132
            jmp error

next132:    ld a, 0
            mov dp, a
            ld ah, 64           ; cmp ah, (dp:#i16)
            cmp ah, (dp:0x06ff) ; 32
            jg error
            jge error
            je error
            jne next133
            jmp error
next133:    jle next134
            jmp error
next134:    jl next135
            jmp error

next135:    ld ah, 32
            cmp ah, (dp:0x06fe) ; 64
            jl error
            jle error
            je error
            jne next136
            jmp error
next136:    jge next137
            jmp error
next137:    jg next138
            jmp error

next138:    ld ah, -32
            cmp ah, (dp:0x06fd) ; -64
            jg error
            jge error
            je error
            jne next139
            jmp error
next139:    jle next140
            jmp error
next140:    jl next141
            jmp error

next141:    ld ah, -64
            cmp ah, (dp:0x06fc) ; -32
            jl error
            jle error
            je error
            jne next142
            jmp error
next142:    jg next143
            jmp error
next143:    jge next144
            jmp error

next144:    ld a, 0x0700
            mov sp, a
            xor a, a
            ld al, 32
            push al
            ld al, 64           ; cmp al, (sp)
            cmp al, (sp)
            jg error
            jge error
            je error
            jne next145
            jmp error
next145:    jle next146
            jmp error
next146:    jl next147
            jmp error

next147:    ld al, 64
            push al
            ld al, 32
            cmp al, (sp)
            jl error
            jle error
            je error
            jne next148
            jmp error
next148:    jge next149
            jmp error
next149:    jg next150
            jmp error

next150:    ld al, -64
            push al
            ld al, -32
            cmp al, (sp)
            jg error
            jge error
            je error
            jne next151
            jmp error
next151:    jle next152
            jmp error
next152:    jl next153
            jmp error

next153:    ld al, -32
            push al
            ld al, -64
            cmp al, (sp)
            jl error
            jle error
            je error
            jne next154
            jmp error
next154:    jg next155
            jmp error
next155:    jge next156
            jmp error

next156:    ld al, 64           ; cmp al, (sp:#i8)
            cmp al, (sp:3)      ; 32
            jg error
            jge error
            je error
            jne next157
            jmp error
next157:    jle next158
            jmp error
next158:    jl next159
            jmp error

next159:    ld al, 32
            cmp al, (sp:2)      ; 64
            jl error
            jle error
            je error
            jne next160
            jmp error
next160:    jge next161
            jmp error
next161:    jg next162
            jmp error

next162:    ld al, -32
            cmp al, (sp:1)      ; -64
            jg error
            jge error
            je error
            jne next163
            jmp error
next163:    jle next164
            jmp error
next164:    jl next165
            jmp error

next165:    ld al, -64
            cmp al, (sp:0)      ; -32
            jl error
            jle error
            je error
            jne next166
            jmp error
next166:    jg next167
            jmp error
next167:    jge next168
            jmp error

next168:    ld a, 0
            mov sp, a
            ld al, 64           ; cmp al, (sp:#i16)
            cmp al, (sp:0x06ff) ; 32
            jg error
            jge error
            je error
            jne next169
            jmp error
next169:    jle next170
            jmp error
next170:    jl next171
            jmp error

next171:    ld al, 32
            cmp al, (sp:0x06fe) ; 64
            jl error
            jle error
            je error
            jne next172
            jmp error
next172:    jge next173
            jmp error
next173:    jg next174
            jmp error

next174:    ld al, -32
            cmp al, (sp:0x06fd) ; -64
            jg error
            jge error
            je error
            jne next175
            jmp error
next175:    jle next176
            jmp error
next176:    jl next177
            jmp error

next177:    ld al, -64
            cmp al, (sp:0x06fc) ; -32
            jl error
            jle error
            je error
            jne next178
            jmp error
next178:    jg next179
            jmp error
next179:    jge next180
            jmp error

next180:    ld a, 0
            mov dp, a
            ld al, 64           ; cmp al, (dp:#i16)
            cmp al, (dp:0x06ff) ; 32
            jg error
            jge error
            je error
            jne next181
            jmp error
next181:    jle next182
            jmp error
next182:    jl next183
            jmp error

next183:    ld al, 32
            cmp al, (dp:0x06fe) ; 64
            jl error
            jle error
            je error
            jne next184
            jmp error
next184:    jge next185
            jmp error
next185:    jg next186
            jmp error

next186:    ld al, -32
            cmp al, (dp:0x06fd) ; -64
            jg error
            jge error
            je error
            jne next187
            jmp error
next187:    jle next188
            jmp error
next188:    jl next189
            jmp error

next189:    ld al, -64
            cmp al, (dp:0x06fc) ; -32
            jl error
            jle error
            je error
            jne next190
            jmp error
next190:    jg next191
            jmp error
next191:    jge next192
            jmp error

next192:

            ; JC JNC

            ld a, 0xffff
            add a, 1            ; set carry
            jnc error
            ld a, 0x0000
            add a, 1            ; clear carry
            jc error

            ; JZ JNZ

            ld a, 1
            sub a, 1            ; set zero
            jnz error
            ld a, 1
            sub a, 0            ; clear zero
            jz error

            ; JN JNN

            ld a, 10
            sub a, 11           ; set negative
            jnn error
            ld a, 10
            sub a, 9            ; clear negative
            jn error

            ; JV JNV

            ld a, 0x7000
            add a, 0x2000       ; set overflow
            jnv error
            ld a, 0xffff
            add a, 0x0001       ; clear overflow
            jv error

pass:
            ld a, 0xabcd
            halt
error:
            ld a, 0xdead
            halt

