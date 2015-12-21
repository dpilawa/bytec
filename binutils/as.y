/* 
 * 
 *    as.y - this file is part of BYTEC/16 binutils (Assembler)
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
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "a.out.h"
#include "bytec.h"

#ifndef TMPDIR
#define TMPDIR "/tmp"
#endif

#ifndef M4
#define M4 "/usr/bin/m4"
#endif

#ifndef SEG_SIZE
#define SEG_SIZE 1024*64
#endif

#ifndef SEG_POS
#define SEG_POS (seg == SEG_TEXT ? tpos : dpos)
#endif

#ifndef SEG_POS_DISPL
#define SEG_POS_DISPL (seg == SEG_TEXT ? tposd : dposd)
#endif

#ifndef SEG_SEL
#define SEG_SEL seg
#endif

enum {SEG_UNKNOWN, SEG_TEXT, SEG_DATA};
enum {SYM_DEFINED, SYM_UNDEFINED};
enum {SYM_GLOBAL, SYM_LOCAL, SYM_EXTERN, SYM_CONST};
enum {REF_ABSOLUTE, REF_RELATIVE, REF_CONST};

extern int yylineno;
extern int yy_flex_debug;
extern int yylex(void);
extern void yyerror(char *);
extern FILE *yyin;

typedef unsigned short int uint16;
typedef unsigned char uint8;
typedef short int int16;

typedef struct symbol {
    char *name;
    int segment;
    int value;
    int defined;
    int class;
    int export;
} symbol_t;

typedef struct relocation {
    int segment;
    uint16 offset;
    int reftype;
    symbol_t *symbol_p;
} reloc_t;

typedef struct llist {
    union {
        symbol_t s;
        reloc_t r;
    } u;
    struct llist *next;
} llist_t;

llist_t *syms = NULL;
llist_t *relocs = NULL;

char *tmpdir = TMPDIR;
char *m4 = M4;
uint8 *tseg_p, *dseg_p, *seg_p;
int  seg = SEG_TEXT;
uint16 tpos=0, dpos=0;
uint16 tposd=0, dposd=0;
FILE *fin, *fout, *ftemp, *fm4;

void     emitstring();
void     emit8(uint8);
void     emit16(uint16);
void     emit8_16(uint8, uint8, uint16);

void     writeaout(FILE*);

void     setupsegs();
void     advancesegs();

symbol_t *symset(const char *, int, int, int, int);
void     symprint(const char*, symbol_t*, const char*);
int      symexists(const char *);
symbol_t *symget(const char *);
long     symgetnum(const char *);
uint16   symref(const char*, int);
int      symchk();
void     symdumptext();

void     rlcadd(symbol_t*, int, uint16, int);
void     rlcprint(const char*, reloc_t*, const char*); 

void     fixup();

void     error(const char *, ...);

extern int verbose;

const char usage[] = 
"Usage: as-b16 [options] file\n"
"Options:\n"
"  -o filename  Set output file name (required)\n"
"  -m macro     Specify m4 macro definition to unroll long-op calls (optional)\n"
"  -v           Set verbose output (optional)\n"
;

%}

%union
{
    int ival;
    char *str;
};

%type <ival> expr
%type <ival> labrefabs;
%type <ival> labrefrel;
%type <ival> lit;
%type <ival> litlabref;
%type <ival> constref;
%token HALT NOP MOV MOVL LD ST ADD SUB ADC SBC AND OR XOR SHL SHR POP PUSH LEA SEX
%token CMP JMP JL JLE JG JGE JLU JLEU JGU JGEU JE JNE JZ JNZ JC JNC JN JNN JV JNV
%token SYSCALL CALL RET IRET
%token DB DW
%token SEGTEXT SEGDATA
%token EXTERN GLOBAL CONST
%token <ival> CHAR_LITERAL
%token <ival> BIN8
%token <ival> BIN16
%token <ival> HEX8
%token <ival> HEX16
%token <ival> DECI
%token <str> LABEL
%token <str> CONST_LABEL
%token <str> STR_LITERAL
%token AH AL A X Y SP DP PC MSW
%left '+' '-'
%left '*'
%nonassoc UMINUS

%%

program:
        program line
        |
        ;

line:
        LABEL ':' { symset($1, SEG_SEL, SEG_POS, SYM_DEFINED, SYM_LOCAL); }
        |
        DB db { advancesegs(); }
        |
        DW dw { advancesegs(); }
        |
        instr { advancesegs(); }
        |
        EXTERN LABEL { symset($2, SEG_UNKNOWN, 0, SYM_UNDEFINED, SYM_EXTERN); }
        |        
        GLOBAL LABEL { symset($2, SEG_UNKNOWN, 0, SYM_UNDEFINED, SYM_GLOBAL); }
        | 
        CONST CONST_LABEL expr { symset($2, SEG_UNKNOWN, $3, SYM_DEFINED, SYM_CONST); }
        |        
        SEGTEXT { seg = SEG_TEXT; seg_p = tseg_p; }
        |
        SEGDATA { seg = SEG_DATA; seg_p = dseg_p; }
        ;

db:
        edb
        |
        db ',' edb
        ;

edb:
        expr { emit8($1); }
        |
        expr ':' expr { int m; for (m = 0; m < $3; m++) emit8($1); }
        |
        STR_LITERAL { emitstring($1); }
        ;

dw:
        edw
        |
        dw ',' edw
        ;

edw:
        expr { emit16($1); }
        |
        expr ':' expr { int m; for (m = 0; m < $3; m++) emit16($1); }
        |
        labrefabs
        ;

litlabref:
        expr
        |
        labrefabs
        ;

labrefabs:
        LABEL { $$ = symref($1, REF_ABSOLUTE); }
        ;

labrefrel:
        LABEL { $$ = symref($1, REF_RELATIVE); }
        ;

constref:
        CONST_LABEL { $$ = symref($1, REF_CONST); } 
        ;

lit:
        CHAR_LITERAL { $$ = $1; }
        |
        BIN8 { $$ = $1; }
        |
        BIN16 { $$ = $1; }
        |
        HEX8 { $$ = $1; }
        |
        HEX16 { $$ = $1; }
        |
        DECI { $$ = $1; }
        ;

expr:
        lit
        |
        constref
        |
        '-' expr %prec UMINUS { $$ = -$2; }
        |
        expr '+' expr { $$ = $1 + $3; }
        |
        expr '-' expr { $$ = $1 - $3; }
        |
        expr '*' expr { $$ = $1 * $3; }
        |
        '(' expr ')' { $$ = $2; }
        ;

instr:
        NOP { emit8(0x00); } |
        HALT { emit8(0x01); } |
        MOV A ',' X { emit8(0x02); } |
        MOV A ',' Y { emit8(0x03); } |
        MOV A ',' SP { emit8(0x04); } |
        MOV A ',' DP { emit8(0x05); } |
        MOV X ',' A { emit8(0x06); } |
        MOV X ',' Y { emit8(0x07); } |
        MOV Y ',' A { emit8(0x08); } |
        MOV Y ',' X { emit8(0x09); } |
        MOV SP ',' A { emit8(0x0A); } |
        MOV DP ',' A { emit8(0x0B); } |
        MOV AL ',' MSW { emit8(0x0C); } |
        MOV MSW ',' AL { emit8(0x0D); } |
        MOVL AL ',' X { emit8(0x0E); } |
        MOVL AL ',' Y { emit8(0x0F); } |
        PUSH A { emit8(0x10); } |
        PUSH X { emit8(0x11); } |
        PUSH Y { emit8(0x12); } |
        PUSH AH { emit8(0x13); } |
        PUSH AL { emit8(0x14); } |
        PUSH SP { emit8(0x15); } |
        PUSH DP { emit8(0x16); } |
        PUSH PC { emit8(0x17); } |
        POP A { emit8(0x18); } |
        POP X { emit8(0x19); } |
        POP Y { emit8(0x1A); } |
        POP AH { emit8(0x1B); } |
        POP AL { emit8(0x1C); } |
        POP SP { emit8(0x1D); } |
        POP DP { emit8(0x1E); } |
        JMP A { emit8(0x1F); } |
        JMP labrefrel { emit8(0x20); emit16($2); } |
        CALL labrefrel { emit8(0x21); emit16($2); } |
        RET { emit8(0x22); } |
        IRET { emit8(0x23); } |
        CALL A { emit8(0x24); } |
        LD A ',' litlabref { emit8(0x25); emit16($4); } |
        LD A ',' '(' SP ':' expr ')' { emit8_16(0x26, 0x27, $7); } |
        LD A ',' '(' DP ':' litlabref ')' { emit8(0x28); emit16($7); } |
        LD A ',' '(' A ':' expr ')' { emit8(0x29); emit16($7); } |
        LD A ',' '(' X ':' expr ')' { emit8(0x2A); emit16($7); } |
        LD A ',' '(' Y ':' expr ')' { emit8(0x2B); emit16($7); } |
        LD X ',' litlabref { emit8(0x2C); emit16($4); } |
        LD X ',' '(' SP ':' expr ')' { emit8_16(0x2D, 0x2E, $7); } |
        LD X ',' '(' DP ':' litlabref ')' { emit8(0x2F); emit16($7);} |
        LD X ',' '(' A ':' expr ')' { emit8(0x30); emit16($7);} |
        LD X ',' '(' X ':' expr ')' { emit8(0x31); emit16($7);} |
        LD X ',' '(' Y ':' expr ')' { emit8(0x32); emit16($7);} |
        LD Y ',' litlabref { emit8(0x33); emit16($4); } |
        LD Y ',' '(' SP ':' expr ')' { emit8_16(0x34, 0x35, $7); } |
        LD Y ',' '(' DP ':' litlabref ')' { emit8(0x36); emit16($7);} |
        LD Y ',' '(' A ':' expr ')' { emit8(0x37); emit16($7);} |
        LD Y ',' '(' X ':' expr ')' { emit8(0x38); emit16($7);} |
        LD Y ',' '(' Y ':' expr ')' { emit8(0x39); emit16($7);} |
        LD AH ',' expr { emit8(0x3A); emit8($4);} |
        LD AL ',' expr { emit8(0x3B); emit8($4);} |
        LD AH ',' '(' SP ':' expr ')' { emit8_16(0x3C, 0x3E, $7);} |
        LD AL ',' '(' SP ':' expr ')' { emit8_16(0x3D, 0x3F, $7);} |
        LD AH ',' '(' DP ':' litlabref ')' { emit8(0x40); emit16($7);} |
        LD AL ',' '(' DP ':' litlabref ')' { emit8(0x41); emit16($7);} |
        LD AH ',' '(' X ':' expr ')' { emit8(0x42); emit16($7);} |
        LD AL ',' '(' X ':' expr ')' { emit8(0x43); emit16($7);} |
        LD AH ',' '(' Y ':' expr ')' { emit8(0x44); emit16($7);} |
        LD AL ',' '(' Y ':' expr ')' { emit8(0x45); emit16($7);} |
        ST '(' SP ':' expr ')' ',' A { emit8_16(0x46, 0x47, $5);} |
        ST '(' DP ':' litlabref ')' ',' A { emit8(0x48); emit16($5);} |
        ST '(' A ':' expr ')' ',' A { emit8(0x49); emit16($5);} |
        ST '(' X ':' expr ')' ',' A { emit8(0x4A); emit16($5);} |
        ST '(' Y ':' expr ')' ',' A { emit8(0x4B); emit16($5);} |
        ST '(' SP ':' expr ')' ',' X { emit8_16(0x4C, 0x4D, $5);} |
        ST '(' DP ':' litlabref ')' ',' X { emit8(0x4E); emit16($5);} |
        ST '(' A ':' expr ')' ',' X { emit8(0x4F); emit16($5);} |
        ST '(' X ':' expr ')' ',' X { emit8(0x50); emit16($5);} |
        ST '(' Y ':' expr ')' ',' X { emit8(0x51); emit16($5);} |
        ST '(' SP ':' expr ')' ',' Y { emit8_16(0x52, 0x53, $5);} |
        ST '(' DP ':' litlabref ')' ',' Y { emit8(0x54); emit16($5);} |
        ST '(' A ':' expr ')' ',' Y { emit8(0x55); emit16($5);} |
        ST '(' X ':' expr ')' ',' Y { emit8(0x56); emit16($5);} |
        ST '(' Y ':' expr ')' ',' Y { emit8(0x57); emit16($5);} |
        ST '(' SP ':' expr ')' ',' AH { emit8_16(0x58, 0x5A, $5);} |
        ST '(' SP ':' expr ')' ',' AL { emit8_16(0x59, 0x5B, $5);} |
        ST '(' DP ':' litlabref ')' ',' AH { emit8(0x5C); emit16($5);} |
        ST '(' DP ':' litlabref ')' ',' AL { emit8(0x5D); emit16($5);} |
        ST '(' X ':' expr ')' ',' AH { emit8(0x5E); emit16($5);} |
        ST '(' X ':' expr ')' ',' AL { emit8(0x5F); emit16($5);} |
        ST '(' Y ':' expr ')' ',' AH { emit8(0x60); emit16($5);} |
        ST '(' Y ':' expr ')' ',' AL { emit8(0x61); emit16($5);} |
        ADD A ',' expr { emit8(0x62); emit16($4);} |
        ADD A ',' X { emit8(0x63); } |
        ADD A ',' Y { emit8(0x64); } |
        ADD A ',' '(' SP ':' expr ')' { emit8_16(0x65, 0x66, $7); } |
        ADD A ',' '(' DP ':' litlabref ')' { emit8(0x67); emit16($7);} |
        ADD A ',' '(' A ':' expr ')' { emit8(0x68); emit16($7);} |
        ADD A ',' '(' X ':' expr ')' { emit8(0x69); emit16($7);} |
        ADD A ',' '(' Y ':' expr ')' { emit8(0x6A); emit16($7);} |
        ADD X ',' expr { emit8(0x6B); emit16($4);} |
        ADD X ',' A { emit8(0x6C); } |
        ADD X ',' Y { emit8(0x6D); } |
        ADD X ',' '(' SP ':' expr ')' { emit8_16(0x6E, 0x6F, $7); } |
        ADD X ',' '(' DP ':' litlabref ')' { emit8(0x70); emit16($7);} |
        ADD X ',' '(' A ':' expr ')' { emit8(0x71); emit16($7);} |
        ADD X ',' '(' X ':' expr ')' { emit8(0x72); emit16($7);} |
        ADD X ',' '(' Y ':' expr ')' { emit8(0x73); emit16($7);} |
        ADD Y ',' expr { emit8(0x74); emit16($4);} |
        ADD Y ',' A { emit8(0x75); } |
        ADD Y ',' X { emit8(0x76); } |
        ADD Y ',' '(' SP ':' expr ')' { emit8_16(0x77, 0x78, $7); } |
        ADD Y ',' '(' DP ':' litlabref ')' { emit8(0x79); emit16($7);} |
        ADD Y ',' '(' A ':' expr ')' { emit8(0x7A); emit16($7);} |
        ADD Y ',' '(' X ':' expr ')' { emit8(0x7B); emit16($7);} |
        ADD Y ',' '(' Y ':' expr ')' { emit8(0x7C); emit16($7);} |
        ADD AH ',' expr { emit8(0x7D); emit8($4);} |
        ADD AL ',' expr { emit8(0x7E); emit8($4);} |
        ADD AH ',' '(' SP ':' expr ')' { emit8(0x7F); emit16($7);} |
        ADD AL ',' '(' SP ':' expr ')' { emit8(0x80); emit16($7);} |
        ADD AH ',' '(' DP ':' litlabref ')' { emit8(0x81); emit16($7);} |
        ADD AL ',' '(' DP ':' litlabref ')' { emit8(0x82); emit16($7);} |
        ADD AH ',' '(' X ':' expr ')' { emit8(0x83); emit16($7);} |
        ADD AL ',' '(' X ':' expr ')' { emit8(0x84); emit16($7);} |
        ADD AH ',' '(' Y ':' expr ')' { emit8(0x85); emit16($7);} |
        ADD AL ',' '(' Y ':' expr ')' { emit8(0x86); emit16($7);} |
        SUB A ',' expr { emit8(0x87); emit16($4); } |
        SUB A ',' X { emit8(0x88); } |
        SUB A ',' Y { emit8(0x89); } |
        SUB A ',' '(' SP ':' expr ')' { emit8_16(0x8A, 0x8B, $7); } |
        SUB A ',' '(' DP ':' litlabref ')' { emit8(0x8C); emit16($7);} |
        SUB A ',' '(' A ':' expr ')' { emit8(0x8D); emit16($7);} |
        SUB A ',' '(' X ':' expr ')' { emit8(0x8E); emit16($7);} |
        SUB A ',' '(' Y ':' expr ')' { emit8(0x8F); emit16($7);} |
        SUB X ',' expr { emit8(0x90); emit16($4);} |
        SUB X ',' A { emit8(0x91); } |
        SUB X ',' Y { emit8(0x92); } |
        SUB X ',' '(' SP ':' expr ')' { emit8_16(0x93, 0x94, $7); } |
        SUB X ',' '(' DP ':' litlabref ')' { emit8(0x95); emit16($7);} |
        SUB X ',' '(' A ':' expr ')' { emit8(0x96); emit16($7);} |
        SUB X ',' '(' X ':' expr ')' { emit8(0x97); emit16($7);} |
        SUB X ',' '(' Y ':' expr ')' { emit8(0x98); emit16($7);} |
        SUB Y ',' expr { emit8(0x99); emit16($4);} |
        SUB Y ',' A { emit8(0x9A); } |
        SUB Y ',' X { emit8(0x9B); } |
        SUB Y ',' '(' SP ':' expr ')' { emit8_16(0x9C, 0x9D, $7); } |
        SUB Y ',' '(' DP ':' litlabref ')' { emit8(0x9E); emit16($7);} |
        SUB Y ',' '(' A ':' expr ')' { emit8(0x9F); emit16($7);} |
        SUB Y ',' '(' X ':' expr ')' { emit8(0xA0); emit16($7);} |
        SUB Y ',' '(' Y ':' expr ')' { emit8(0xA1); emit16($7);} |
        SUB AH ',' expr { emit8(0xA2); emit8($4);} |
        SUB AL ',' expr { emit8(0xA3); emit8($4);} |
        SUB AH ',' '(' SP ':' expr ')' { emit8(0xA4); emit16($7);} |
        SUB AL ',' '(' SP ':' expr ')' { emit8(0xA5); emit16($7);} |
        SUB AH ',' '(' DP ':' litlabref ')' { emit8(0xA6); emit16($7);} |
        SUB AL ',' '(' DP ':' litlabref ')' { emit8(0xA7); emit16($7);} |
        SUB AH ',' '(' X ':' expr ')' { emit8(0xA8); emit16($7);} |
        SUB AL ',' '(' X ':' expr ')' { emit8(0xA9); emit16($7);} |
        SUB AH ',' '(' Y ':' expr ')' { emit8(0xAA); emit16($7);} |
        SUB AL ',' '(' Y ':' expr ')' { emit8(0xAB); emit16($7);} |
        AND A ',' expr { emit8(0xAC); emit16($4);} |
        AND A ',' X { emit8(0xAD); } |
        AND A ',' Y { emit8(0xAE); } |
        AND A ',' '(' SP ':' expr ')' { emit8(0xAF); emit16($7);} |
        AND A ',' '(' DP ':' litlabref ')' { emit8(0xB0); emit16($7);} |
        AND AH ',' expr { emit8(0xB1); emit8($4);} |
        AND AL ',' expr { emit8(0xB2); emit8($4);} |
        AND AH ',' '(' SP ':' expr ')' { emit8(0xB3); emit16($7);} |
        AND AL ',' '(' SP ':' expr ')' { emit8(0xB4); emit16($7);} |
        AND AH ',' '(' DP ':' litlabref ')' { emit8(0xB5); emit16($7);} |
        AND AL ',' '(' DP ':' litlabref ')' { emit8(0xB6); emit16($7);} |
        OR A ',' expr { emit8(0xB7); emit16($4);} |
        OR A ',' X { emit8(0xB8); } |
        OR A ',' Y { emit8(0xB9); } |
        OR A ',' '(' SP ':' expr ')' { emit8(0xBA); emit16($7);} |
        OR A ',' '(' DP ':' litlabref ')' { emit8(0xBB); emit16($7);} |
        OR AH ',' expr { emit8(0xBC); emit8($4);} |
        OR AL ',' expr { emit8(0xBD); emit8($4);} |
        OR AH ',' '(' SP ':' expr ')' { emit8(0xBE); emit16($7);} |
        OR AL ',' '(' SP ':' expr ')' { emit8(0xBF); emit16($7);} |
        OR AH ',' '(' DP ':' litlabref ')' { emit8(0xC0); emit16($7);} |
        OR AL ',' '(' DP ':' litlabref ')' { emit8(0xC1); emit16($7);} |
        XOR A ',' expr { emit8(0xC2); emit16($4);} |
        XOR A ',' X { emit8(0xC3); } |
        XOR A ',' Y { emit8(0xC4); } |
        XOR A ',' '(' SP ':' expr ')' { emit8(0xC5); emit16($7);} |
        XOR A ',' '(' DP ':' litlabref ')' { emit8(0xC6); emit16($7);} |
        XOR AH ',' expr { emit8(0xC7); emit8($4);} |
        XOR AL ',' expr { emit8(0xC8); emit8($4);} |
        XOR AH ',' '(' SP ':' expr ')' { emit8(0xC9); emit16($7);} |
        XOR AL ',' '(' SP ':' expr ')' { emit8(0xCA); emit16($7);} |
        XOR AH ',' '(' DP ':' litlabref ')' { emit8(0xCB); emit16($7);} |
        XOR AL ',' '(' DP ':' litlabref ')' { emit8(0xCC); emit16($7);} |
        SEX A { emit8(0xCD); } |
        SHL A { emit8(0xCE); } |
        SHR A { emit8(0xCF); } |
        SHL AH { emit8(0xD0); } |
        SHL AL { emit8(0xD1); } |
        SHR AH { emit8(0xD2); } |
        SHR AL { emit8(0xD3); } |
        ADC A ',' X { emit8(0xD4); } |
        ADC A ',' Y { emit8(0xD5); } |
        SBC A ',' X { emit8(0xD6); } |
        SBC A ',' Y { emit8(0xD7); } |
        ADD SP ',' expr { emit8(0xD8); emit16($4);} |
        CMP A ',' expr { emit8(0xD9); emit16($4);} |
        CMP A ',' X { emit8(0xDA); } |
        CMP A ',' Y { emit8(0xDB); } |
        CMP A ',' '(' SP ':' expr ')' { emit8(0xDC); emit16($7);} |
        CMP A ',' '(' DP ':' litlabref ')' { emit8(0xDD); emit16($7);} |
        CMP AH ',' expr { emit8(0xDE); emit8($4);} |
        CMP AH ',' '(' SP ':' expr ')' { emit8(0xDF); emit16($7);} |
        CMP AH ',' '(' DP ':' litlabref ')' { emit8(0xE0); emit16($7);} |
        CMP AL ',' expr { emit8(0xE1); emit8($4);} |        
        CMP AL ',' '(' SP ':' expr ')' { emit8(0xE2); emit16($7);} |
        CMP AL ',' '(' DP ':' litlabref ')' { emit8(0xE3); emit16($7);} |
        JE labrefrel { emit8(0xE4); emit16($2);} |
        JNE labrefrel { emit8(0xE5); emit16($2);} |
        JL labrefrel { emit8(0xE6); emit16($2);} |
        JLE labrefrel { emit8(0xE7); emit16($2);} |
        JG labrefrel { emit8(0xE8); emit16($2);} |
        JGE labrefrel { emit8(0xE9); emit16($2);} |
        JLU labrefrel { emit8(0xEA); emit16($2);} |
        JLEU labrefrel { emit8(0xEB); emit16($2);} |
        JGU labrefrel { emit8(0xEC); emit16($2);} |
        JGEU labrefrel { emit8(0xED); emit16($2);} |
        JZ labrefrel { emit8(0xEE); emit16($2);} |
        JNZ labrefrel { emit8(0xEF); emit16($2);} |
        JC labrefrel { emit8(0xF0); emit16($2);} |
        JNC labrefrel { emit8(0xF1); emit16($2);} |
        JN labrefrel { emit8(0xF2); emit16($2);} |
        JNN labrefrel { emit8(0xF3); emit16($2);} |
        JV labrefrel { emit8(0xF4); emit16($2);} |
        JNV labrefrel { emit8(0xF5); emit16($2);} |
        LEA A ',' '(' A ':' expr ')' { emit8(0xF6); emit16($7);} |
        LEA A ',' '(' SP ':' expr ')' { emit8(0xF7); emit16($7);} |
        LEA A ',' '(' DP ':' litlabref ')' { emit8(0xF8); emit16($7);} |
        LEA X ',' '(' A ':' expr ')' { emit8(0xF9); emit16($7);} |        
        LEA X ',' '(' SP ':' expr ')' { emit8(0xFA); emit16($7);} |
        LEA X ',' '(' DP ':' litlabref ')' { emit8(0xFB); emit16($7);} |
        LEA Y ',' '(' A ':' expr ')' { emit8(0xFC); emit16($7);} |          
        LEA Y ',' '(' SP ':' expr ')' { emit8(0xFD); emit16($7);} |
        LEA Y ',' '(' DP ':' litlabref ')' { emit8(0xFE); emit16($7);} | 
        SYSCALL expr { emit8(0xFF); emit8($2); }
        ;
%%

void setupsegs()
{
    tseg_p = malloc(SEG_SIZE);
    dseg_p = malloc(SEG_SIZE);
    tpos = 0;
    dpos = 0;
    seg = SEG_TEXT;
    seg_p = tseg_p;
}

void advancesegs()
{
    if (seg==SEG_TEXT)
        tpos=tpos+tposd;
    else
        dpos=dpos+dposd;
    tposd=dposd=0;
}

void cleanup()
{
    free(tseg_p);
    free(dseg_p);

    llist_t *slist = syms;
    while (slist)
    {
        syms=syms->next;
        free(slist->u.s.name);
        free(slist);
        slist=syms;
    }
    
    llist_t *rlist = relocs;
    while (rlist)
    {
        relocs=relocs->next;
        free(rlist);
        rlist=relocs;
    }    
}

int symexists(const char *name)
{
    llist_t *slist = syms;
    while (slist)
    {
        if (strcmp(slist->u.s.name, name) == 0)
        {
            return 1;
        }
        slist=slist->next;
    }
    return 0;
}

uint16 symref(const char *name, int reftype)
{
    symbol_t *sym;
    if (symexists(name)) {
        sym = symget(name);
        if ((sym->defined==SYM_DEFINED) && (sym->class!=SYM_CONST)) {
            switch (reftype) {
                case REF_ABSOLUTE:
                    /* local absolute refs also need a reloc for the linker */
                    rlcadd(sym, SEG_SEL, SEG_POS + 1, reftype);
                    return (uint16)(sym->value);
                    break;
                case REF_RELATIVE:
                    return (uint16)(sym->value - SEG_POS - 2 - 1);
                    break;
            }
        }
        else if (sym->class!=SYM_CONST) {
            /* consecutive forward reference to existing undefined symbol */
            rlcadd(sym, SEG_SEL, SEG_POS + 1, reftype);
            return 0;
        }
        else {
            /* constant reference */
            return (uint16)(sym->value);
        }
    }
    else {
        /* first forward reference to symbol */
        rlcadd(symset(name, SEG_UNKNOWN, 0, SYM_UNDEFINED, SYM_LOCAL), SEG_SEL, SEG_POS + 1, reftype);
    }
    return 0;
}

void symprint(const char *text, symbol_t *sym, const char *trail) {
    if (verbose) {
        printf("%s[", text);
        switch(sym->segment) {
            case SEG_TEXT:
                printf("text+");
                break;
            case SEG_DATA:
                printf("data+");
                break;
            case SEG_UNKNOWN:
                printf("????+");
                break;              
        }
        switch(sym->defined) {
            case SYM_DEFINED:
                printf("0x%04x] ", sym->value);
                break;
            case SYM_UNDEFINED:
                printf("??????] ");
                break;          
        }
        switch(sym->class) {
            case SYM_EXTERN:
                printf("extern");
                break;
            case SYM_GLOBAL:
                printf("global");
                break;
            case SYM_LOCAL:
                printf("local");
                break;
            case SYM_CONST:
                printf("const");
                break;
        }   
        printf(" %s", sym->name);
        /* print asterisk if symbol is exported to object file */ 
        if ((sym->class==SYM_GLOBAL) || (sym->export))
        {
            printf(" *");
        }  
        printf(trail);
    }
}

symbol_t* symset(const char *symname, int segm, int val, int def, int cls)
{
    symbol_t *s;
    llist_t *slistnew;
    
    if (symexists(symname)) {
        s = symget(symname);
        if (s->defined==SYM_DEFINED && def==SYM_DEFINED) {
            /* redefinition of defined symbol - error */
            error("Redefinition of symbol '%s'\n", symname);
        }
        else if ((s->defined==SYM_DEFINED && cls==SYM_EXTERN) || 
                 (s->class==SYM_EXTERN  && def==SYM_DEFINED)) {
            /* declaring an already defined symbol as extern - error */
            error("Defined symbol '%s' cannot be made extern\n", symname);
        }
        else {
            if (cls==SYM_LOCAL || cls==SYM_CONST) {
                /* define symbol */
                s->defined = SYM_DEFINED;
                s->value = val;
                s->segment = segm;
            }
            else { 
                /* (cls==SYM_GLOBAL || cls==SYM_EXTERN) { */
                s->class = cls;
                s->export = 1;
            }
        }
        symprint("Def ", s, "\n");
        return s;
    } else {
        /* simply add a new symbol */
        slistnew = malloc(sizeof(llist_t));
        slistnew -> u.s.segment = segm;
        slistnew -> u.s.value = val;
        slistnew -> u.s.defined = def;
        slistnew -> u.s.class = cls;
        slistnew -> u.s.name = strdup(symname); 
        slistnew -> u.s.export = 0;    
        slistnew -> next = syms;
        syms = slistnew;
        symprint("Add ", &(slistnew->u.s), "\n");
        return &(slistnew->u.s);
    }
}

symbol_t *symget(const char *symname)
{
    llist_t *slist = syms;

    while (slist)
    {
        if (strcmp(slist->u.s.name, symname) == 0)
        {
            return &(slist->u.s);
        }
        slist=slist->next;
    }
    error("Undefined symbol '%s'\n", symname);
    return NULL;
}

long symgetnum(const char *symname)
{
    llist_t *slist = syms;
    long symnum = 1;

    while (slist)
    {
        if (strcmp(slist->u.s.name, symname) == 0)
        {
            return symnum;
        }
        /* only GLOBAL and export labeled symbol names will be exported and need to be counted */
        if ((slist->u.s.class==SYM_GLOBAL) || (slist->u.s.export)) 
        {
            symnum = symnum + 1;
        }
        slist=slist->next;
    }
    error("Undefined symbol '%s'\n", symname);
    return (long)-1;
}

int symchk() 
{
    int res=1;
    llist_t *slist = syms;
    while (slist)
    {
        if (slist->u.s.defined==SYM_UNDEFINED && slist->u.s.class!=SYM_EXTERN) 
        {
            printf("Undefined symbol '%s'\n", slist->u.s.name);
            res=0;
        };
        slist=slist->next;
    }
    return res; 
}

void symdumptext()
{
    llist_t *slist = syms;
    while (slist)
    {
        symprint("", &slist->u.s, "\n");
        slist=slist->next;
    }
}

void rlcadd(symbol_t *sym, int segm, uint16 ofs, int reftype) {
    llist_t *rlistnew;
    rlistnew = malloc(sizeof(llist_t));
    rlistnew->next = relocs;
    rlistnew->u.r.symbol_p = sym;
    rlistnew->u.r.segment = segm;
    rlistnew->u.r.offset = ofs;
    rlistnew->u.r.reftype = reftype;
    relocs = rlistnew;
    /* if reference is absolute or referenced symbol is extern -> need to export */
    /* if ((reftype==REF_ABSOLUTE) || (sym->class==SYM_EXTERN)) */
    if (sym->class==SYM_EXTERN)
    {   
        sym->export = 1;
    }
    rlcprint("Rlc ", &(rlistnew->u.r), "\n");
}

void rlcprint(const char *text, reloc_t *rlc, const char *trail) {
    if (verbose) {
        printf("%s[", text);
        switch(rlc->segment) {
            case SEG_TEXT:
                printf("text+");
                break;
            case SEG_DATA:
                printf("data+");
                break;
        }
        printf("0x%04x]", rlc->offset);
        symprint(" <-     ", rlc->symbol_p, " ");
        switch(rlc->reftype) {
            case REF_ABSOLUTE:
                printf("(absolute)");
                break;
            case REF_RELATIVE:
                printf("(relative)");
                break;
        }
        printf(trail);
    }
}

void fixup() 
{
    llist_t *rlist = relocs;
    uint16 f_offset;
    uint16 f_value;
    uint8  *f_seg;
    while (rlist)
    {
        if (rlist->u.r.symbol_p->class==SYM_LOCAL || rlist->u.r.symbol_p->class==SYM_GLOBAL)
        {
        
            f_offset = rlist->u.r.offset;
        
            switch (rlist->u.r.segment)
            {
                case SEG_TEXT:
                    f_seg = tseg_p;
                    break;
                case SEG_DATA:
                    f_seg = dseg_p;
                    break;
                default:
                    rlcprint("Reloc ", &rlist->u.r, "");
                    error(" has undefined segment\n");
            }
        
            switch (rlist->u.r.reftype)
            {
                case REF_ABSOLUTE:
                    f_value = (uint16)(rlist->u.r.symbol_p->value);
                    break;
                case REF_RELATIVE:
                    f_value = (uint16)(rlist->u.r.symbol_p->value - f_offset - 2);
                    break;
                default:
                    rlcprint("Reloc ", &rlist->u.r, "");
                    error(" has undefined reference type\n");
            }
       
            *(f_seg+f_offset)=(char)((f_value&0xff00)>>8);
            *(f_seg+f_offset+1)=(char)(f_value&0x00ff);
            if (verbose) 
            {
                rlcprint("Applied local reloc ", &rlist->u.r, "\n");
            }
                
        }
        rlist=rlist->next;
    }
}

void emitstring(char* s)
{
    while (*++s)
    {
        if (*s=='\'')
        {
            if (*(s+1)=='\'') 
            {
                emit8(*s++);
            }
        }
        else
        {
            emit8(*s);
        }
    }
}

void emit8(uint8 b)
{
    if (seg==SEG_TEXT) {
        *(tseg_p+SEG_POS+SEG_POS_DISPL) = b;
        tposd++;
    }
    else {
        *(dseg_p+SEG_POS+SEG_POS_DISPL) = b;
        dposd++;
    }
}

void emit16(uint16 w)
{
    emit8((uint8)(w>>8));
    emit8((uint8)(w&0xff));
}

void emit8_16(uint8 t8, uint8 t16, uint16 i)
{
    if (((int)i>=CHAR_MIN)&&((int)i<CHAR_MAX)) {
        emit8(t8); 
        emit8((uint8)i);
    } else {
        emit8(t16);
        emit16(i);
    }
}

void yyerror(char *s)
{
    error("line %d: %s\n", yylineno, s);
}

long writeaout_reloc(FILE* f, int seg)
{
    llist_t *rlist = relocs;    
    long rsize = 0;  
    struct reloc re;    
    
    while (rlist)
    {
        if (rlist->u.r.segment==seg) {
            re.r_vaddr=(long)rlist->u.r.offset;
            switch (rlist->u.r.reftype)
            {
                case REF_ABSOLUTE:
                    re.r_type = R_ABBS;
                    break;
                case REF_RELATIVE:
                    re.r_type = R_PCRBYTE;
                    break;
                default:
                    error("Invalid reference type when creating a.out relocation table\n");
            }
            if (rlist->u.r.symbol_p->class==SYM_EXTERN)
            {
                re.r_symndx = (unsigned short)symgetnum(rlist->u.r.symbol_p->name);
                fwrite(&re, sizeof(struct reloc), 1, f);
                rsize += sizeof(struct reloc);
            }
            else /* SYM_LOCAL || SYM_GLOBAL */
            {
                /* only absolute references need to be reloc'd */
                if (rlist->u.r.reftype==REF_ABSOLUTE) 
                {
                    /* no need to export symbol, but only the symbol's segment for base addend */
                    switch (rlist->u.r.symbol_p->segment)
                    {
                        case SEG_TEXT:
                            re.r_symndx = S_TEXT;
                            break;
                        case SEG_DATA:
                            re.r_symndx = S_DATA;
                            break;
                        default:
                            error("Invalid segment when creating a.out relocation table\n");
                    }
                    fwrite(&re, sizeof(struct reloc), 1, f);
                    rsize += sizeof(struct reloc);
                }
            }
        }
        rlist=rlist->next;
    }
    
    return rsize;
          
}

long writeaout_symtab(FILE* f)
{
    llist_t *slist = syms;    
    long ssize = 0; 
    long n_strx = 0; 
    struct nlist2 sym;    
    
    while (slist)
    {
        /* export only GLOBAL symbols and symbols used in extern or absolute relocs */
        if ((slist->u.s.class==SYM_GLOBAL) || (slist->u.s.export))
        {
            sym.n_strx=n_strx;
            sym.n_value=(long)slist->u.s.value;
            sym.n_sclass=0;
            switch (slist->u.s.class)
            {
                case SYM_EXTERN:
                    sym.n_sclass|=C_EXT;
                    sym.n_sclass|=N_UNDF;          
                    break;                
                default:
                    sym.n_sclass|=C_STAT;
                    switch (slist->u.s.segment)
                        {
                            case SEG_TEXT:
                                sym.n_sclass|=N_TEXT;
                                break;
                            case SEG_DATA:
                                sym.n_sclass|=N_DATA;            
                                break;
                            default:
                                error("Invalid segment for '%s' when creating a.out symbol table\n", slist->u.s.name);
                        }
                    break;
            }
            n_strx=n_strx+strlen(slist->u.s.name)+1;
            ssize+=sizeof(sym);
            fwrite(&sym, sizeof(sym), 1, f);
        }
        slist=slist->next;
    }
    
    return ssize;
          
}

void writeaout_stringtab(FILE* f)
{
    llist_t *slist = syms;    
    long size = 0;

    /* calculate table size */
    while (slist)
    {
        /* export only GLOBAL symbols and symbols used in extern or absolute relocs */
        if ((slist->u.s.class==SYM_GLOBAL) || (slist->u.s.export))
        {
            size+=strlen(slist->u.s.name)+1;
        }
        slist=slist->next;
    }
    fwrite(&size, sizeof(size), 1, f);
    
    /* write symbol strings */
    slist = syms;
    while (slist)
    {
        /* export only GLOBAL symbols and symbols used in extern or absolute relocs */
        if ((slist->u.s.class==SYM_GLOBAL) || (slist->u.s.export))
        {
            fwrite(slist->u.s.name, strlen(slist->u.s.name)+1, 1, f);
        }
        slist=slist->next;
    }
      
}

void writeaout(FILE* f)
{
    struct exec ex;

    /* pre-write header */
    fwrite(&ex,sizeof(struct exec),1,f);

    /* write text and data segments */
    fwrite(tseg_p,tpos,1,f);
    fwrite(dseg_p,dpos,1,f);

    /* write relocation tables */
    ex.a_trsize=(long)writeaout_reloc(f, SEG_TEXT);
    ex.a_drsize=(long)writeaout_reloc(f, SEG_DATA);

    /* write symbol table */
    ex.a_syms=(long)writeaout_symtab(f);

    /* write string table */
    writeaout_stringtab(f);

    /* write proper a.out header */
    ex.a_magic[0]=A_MAGIC0;
    ex.a_magic[1]=A_MAGIC1;
    ex.a_flags=(char)0;
    ex.a_cpu=A_BYTEC16;
    ex.a_hdrlen=(unsigned char)sizeof(struct exec);
    ex.a_text=(long)tpos;
    ex.a_data=(long)dpos;
    ex.a_bss=(long)0;
    ex.a_entry=(long)0;
    ex.a_tbase=(long)0;
    ex.a_dbase=(long)0;

    fseek(f, 0, SEEK_SET);
    fwrite(&ex,sizeof(struct exec),1,f);

}

int main(int argc, char **argv)
{
    char *infile = NULL;
    char *outfile = NULL;
    char *m4file = NULL;
    char tmpfile[1024];
    int outset = 0, inset=0, macro = 0;
    char c;
    char cmd[1024];

    outfile = strdup("a.out");

    while ( (c = getopt(argc, argv, "-o:m:v")) != -1) 
    {
        switch(c)
        {
            case 1:
                if (inset) 
                {
                    error("Input filename already defined: %s\n", usage, infile);
                }
                infile = strdup(optarg);
                inset = 1;
                break;
            case 'o':
                free(outfile);
                outfile = strdup(optarg);
                outset = 1;
                break;
            case 'm':
                m4file = strdup(optarg);
                macro = 1;
                break;                
            case 'v':
                verbose = 1;
                break;
            case '?':
                error("%s", usage);
                exit(-1);
                break;                
            default:
                abort();
        }
    }

    if (!outset)
    {
        error("Missing output filename\n%s", usage);
    }

    if (!inset)
    {
        error("Missing input filename\n%s", usage);
    }

    yy_flex_debug = 1;

    /* step 1 - process macro definitions */
    if (macro) {
        sprintf(tmpfile, "%s/.as%d.tmp", tmpdir, getpid());
        sprintf(cmd,"%s %s %s > %s", m4, m4file, infile, tmpfile);
        if (system(cmd)==-1)
            exit(100);
    }

    /* step 2 - assemble */
    if (verbose) 
        printf("Assembling:\n");
    if (macro)
        fin = fopen(tmpfile, "r");
    else
        fin = fopen(infile, "r");
    if (!fin)
    {
        error("Unable to open '%s' for reading\n", infile);
    }
    setupsegs();
    yyin = fin;
    yyparse();
    fclose(fin);
    if (verbose) {
        printf("Symbol table:\n");
        symdumptext(stdout);
    }
    if (!symchk()) exit(-1);

    /* step 3 - apply local fixups */
    fixup();
    
    /* step 4 - write output */
    fout = fopen(outfile, "w");
    if (!fout)
    {
        error("Unable to open '%s' for writing\n", outfile);
    }
    writeaout(fout);
    fclose(fout);
    
    /* step 5 - clean up */
    if (infile) free(infile);
    if (outfile) free(outfile);
    if (m4file) free(m4file);
    cleanup();
    yylex_destroy();
    if (macro)
        remove(tmpfile);

    return 0;
}
