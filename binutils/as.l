/* 
 * 
 *    as.l - this file is part of BYTEC/16 binutils (Assembler)
 *   
 *    Copyright 2010, 2011, 2012, 2013 Dawid Pilawa
 * 
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

%{
#include <stdlib.h>
#include "as.tab.h"
void yyerror(char *);
int offset;
%}

digit [0-9]
digit19 [1-9]
bin [0-1]
hex [0-9a-fA-F]
alpha [A-Za-z_]

%x comment

%%

"nop"                           return NOP;
"halt"                          return HALT;
"mov"                           return MOV;
"movl"                          return MOVL;
"ld"                            return LD;
"st"                            return ST;
"add"                           return ADD;
"sub"                           return SUB;
"adc"                           return ADC;
"sbc"                           return SBC;
"and"                           return AND;
"or"                            return OR;
"xor"                           return XOR;
"shl"                           return SHL;
"shr"                           return SHR;
"lea"                           return LEA;
"sex"                           return SEX;

"push"                          return PUSH;
"pop"                           return POP;

"syscall"                       return SYSCALL;
"call"                          return CALL;
"ret"                           return RET;
"iret"                          return IRET;

"cmp"                           return CMP;
"jmp"                           return JMP;
"jle"                           return JLE;
"jl"                            return JL;
"jge"                           return JGE;
"jg"                            return JG;
"jleu"                          return JLEU;
"jlu"                           return JLU;
"jgeu"                          return JGEU;
"jgu"                           return JGU;
"je"                            return JE;
"jne"                           return JNE;
"jz"                            return JZ;
"jnz"                           return JNZ;
"jc"                            return JC;
"jnc"                           return JNC;
"jn"                            return JN;
"jnn"                           return JNN;
"jv"                            return JV;
"jnv"                           return JNV;

"ah"                            return AH;
"al"                            return AL;
"a"                             return A;
"x"                             return X;
"y"                             return Y;
"dp"                            return DP;
"sp"                            return SP;
"pc"                            return PC;
"msw"                           return MSW;

".db"                           return DB;
".dw"                           return DW;

".extern"                       return EXTERN;
".global"                       return GLOBAL;
".const"                        return CONST;

".text"                         return SEGTEXT;
".data"                         return SEGDATA;

{alpha}({alpha}|{digit})*       {
                                    yylval.str = strdup(yytext);
                                    return LABEL;
                                }
#{alpha}({alpha}|{digit})*      {
                                    yylval.str = strdup(yytext);
                                    return CONST_LABEL;
                                }                        
'(''|[^'])((''|[^']))+'         {   
                                    yylval.str = strdup(yytext);
                                    return STR_LITERAL;
                                }
'(''|[^'])'                     {
                                    yylval.ival = (char)(*(yytext+1));
                                    return CHAR_LITERAL;
                                }
0b{bin}{bin}{bin}{bin}{bin}{bin}{bin}{bin} {
                                    yylval.ival = (int)strtol(yytext+2, NULL, 2);
                                    return BIN8;
                                } 
0b{bin}{bin}{bin}{bin}{bin}{bin}{bin}{bin}{bin}{bin}{bin}{bin}{bin}{bin}{bin}{bin} {
                                    yylval.ival = (int)strtol(yytext+2, NULL, 2);
                                    return BIN16;
                                }                                                                
0x{hex}{hex}                    {
                                    yylval.ival = (int)strtol(yytext, NULL, 16);
                                    return HEX8;
                                }
0x{hex}{hex}{hex}{hex}          {
                                    yylval.ival = (int)strtol(yytext, NULL, 16);
                                    return HEX16;
                                }                                
{digit19}{digit}*               {
                                    yylval.ival = (int)strtol(yytext, NULL, 10);
                                    return DECI;
                                }
"0"                             {
                                    yylval.ival = (int)0;
                                    return DECI;
                                }                               
[+-/*,():]                      {
                                    return *yytext;
                                }
\n                              {
                                    ++yylineno;
                                }
";"|"#"                         BEGIN(comment); /* ignore comments */
<comment>[^\n]*                 ;
<comment>\n                     {
                                    ++yylineno;
                                    BEGIN(INITIAL);
                                }
<comment><<EOF>>                {
                                    BEGIN(INITIAL);
                                    yyterminate();
                                }
[ \t\r]+                        ;               /* ignore whitespace */
.                               {
                                    yyerror("Invalid character");
                                }

%%

int yywrap(void)
{
    return 1;
}
