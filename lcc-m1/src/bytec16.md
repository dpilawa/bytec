%{

// LCC machine description for BYTEC/16
// January 19, 2013
// http://www.pilawa.org/computer

// Registers
enum { R_L0, R_L1, R_L2, R_L3, R_AH, R_AL, R_Y, R_X, R_A };

#include "c.h"

#define NODEPTR_TYPE Node
#define OP_LABEL(p) ((p)->op)
#define LEFT_CHILD(p) ((p)->kids[0])
#define RIGHT_CHILD(p) ((p)->kids[1])
#define STATE_LABEL(p) ((p)->x.state)

// Declare local routines to be used by IR record here
static void address(Symbol, Symbol, long);
static void blkfetch(int, int, int, int);
static void blkloop(int, int, int, int, int, int[]);
static void blkstore(int, int, int, int);
static void defaddress(Symbol);
static void defconst(int, int, Value);
static void defstring(int, char *);
static void defsymbol(Symbol);
static void doarg(Node);
static void emit2(Node);
static void export(Symbol);
static void clobber(Node);
static void function(Symbol, Symbol [], Symbol [], int);
static void global(Symbol);
static void import(Symbol);
static void local(Symbol);
static void progbeg(int, char **);
static void progend(void);
static void segment(int);
static void space(int);
static void target(Node);

static int memop(Node);
static int sametree(Node,Node);

// Local vars here

static Symbol charreg[32];
static Symbol intreg[32];
static Symbol floatreg[32];
static Symbol longreg[32];

static Symbol charwldcrd;
static Symbol intwldcrd;
static Symbol floatwldcrd;
static Symbol longwldcrd;

static int cseg;
static int used_longs;
static int used_floats;
static int ptr64;

%}
%start stmt

%term CNSTF4=4113
%term CNSTF8=8209
%term CNSTI1=1045
%term CNSTI2=2069
%term CNSTI4=4117
%term CNSTP2=2071
%term CNSTU1=1046
%term CNSTU2=2070
%term CNSTU4=4118

%term ARGB=41
%term ARGF4=4129
%term ARGF8=8225
%term ARGI2=2085
%term ARGI4=4133
%term ARGP2=2087
%term ARGU2=2086
%term ARGU4=4134

%term ASGNB=57
%term ASGNF4=4145
%term ASGNF8=8241
%term ASGNI1=1077
%term ASGNI2=2101
%term ASGNI4=4149
%term ASGNP2=2103
%term ASGNU1=1078
%term ASGNU2=2102
%term ASGNU4=4150

%term INDIRB=73
%term INDIRF4=4161
%term INDIRF8=8257
%term INDIRI1=1093
%term INDIRI2=2117
%term INDIRI4=4165
%term INDIRP2=2119
%term INDIRU1=1094
%term INDIRU2=2118
%term INDIRU4=4166

%term CVFF4=4209
%term CVFF8=8305
%term CVFI2=2165
%term CVFI4=4213

%term CVIF4=4225
%term CVIF8=8321
%term CVII1=1157
%term CVII2=2181
%term CVII4=4229
%term CVIU1=1158
%term CVIU2=2182
%term CVIU4=4230

%term CVPU2=2198

%term CVUI1=1205
%term CVUI2=2229
%term CVUI4=4277
%term CVUP2=2231
%term CVUU1=1206
%term CVUU2=2230
%term CVUU4=4278

%term NEGF4=4289
%term NEGF8=8385
%term NEGI2=2245
%term NEGI4=4293

%term CALLB=217
%term CALLF4=4305
%term CALLF8=8401
%term CALLI2=2261
%term CALLI4=4309
%term CALLP2=2263
%term CALLU2=2262
%term CALLU4=4310
%term CALLV=216

%term RETF4=4337
%term RETF8=8433
%term RETI2=2293
%term RETI4=4341
%term RETP2=2295
%term RETU2=2294
%term RETU4=4342
%term RETV=248

%term ADDRGP2=2311

%term ADDRFP2=2327

%term ADDRLP2=2343

%term ADDF4=4401
%term ADDF8=8497
%term ADDI2=2357
%term ADDI4=4405
%term ADDP2=2359
%term ADDU2=2358
%term ADDU4=4406

%term SUBF4=4417
%term SUBF8=8513
%term SUBI2=2373
%term SUBI4=4421
%term SUBP2=2375
%term SUBU2=2374
%term SUBU4=4422

%term LSHI2=2389
%term LSHI4=4437
%term LSHU2=2390
%term LSHU4=4438

%term MODI2=2405
%term MODI4=4453
%term MODU2=2406
%term MODU4=4454

%term RSHI2=2421
%term RSHI4=4469
%term RSHU2=2422
%term RSHU4=4470

%term BANDI2=2437
%term BANDI4=4485
%term BANDU2=2438
%term BANDU4=4486

%term BCOMI2=2453
%term BCOMI4=4501
%term BCOMU2=2454
%term BCOMU4=4502

%term BORI2=2469
%term BORI4=4517
%term BORU2=2470
%term BORU4=4518

%term BXORI2=2485
%term BXORI4=4533
%term BXORU2=2486
%term BXORU4=4534

%term DIVF4=4545
%term DIVF8=8641
%term DIVI2=2501
%term DIVI4=4549
%term DIVU2=2502
%term DIVU4=4550

%term MULF4=4561
%term MULF8=8657
%term MULI2=2517
%term MULI4=4565
%term MULU2=2518
%term MULU4=4566

%term EQF4=4577
%term EQF8=8673
%term EQI2=2533
%term EQI4=4581
%term EQU2=2534
%term EQU4=4582

%term GEF4=4593
%term GEF8=8689
%term GEI2=2549
%term GEI4=4597
%term GEU2=2550
%term GEU4=4598

%term GTF4=4609
%term GTF8=8705
%term GTI2=2565
%term GTI4=4613
%term GTU2=2566
%term GTU4=4614

%term LEF4=4625
%term LEF8=8721
%term LEI2=2581
%term LEI4=4629
%term LEU2=2582
%term LEU4=4630

%term LTF4=4641
%term LTF8=8737
%term LTI2=2597
%term LTI4=4645
%term LTU2=2598
%term LTU4=4646

%term NEF4=4657
%term NEF8=8753
%term NEI2=2613
%term NEI4=4661
%term NEU2=2614
%term NEU4=4662

%term JUMPV=584

%term LABELV=600

%term VREGP=711

%term LOADI4=4325
%term LOADU4=4326
%term LOADI2=2277
%term LOADU2=2278
%term LOADP2=2279
%term LOADF4=4321
%term LOADB=233
%term LOADF8=8417
%term LOADI1=1253
%term LOADU1=1254

%%

reg8:   INDIRI1(VREGP)     "# read register\n"
reg8:   INDIRU1(VREGP)     "# read register\n"
reg:    INDIRI2(VREGP)     "# read register\n"
reg:    INDIRU2(VREGP)     "# read register\n"
reg32:  INDIRI4(VREGP)     "# read register\n"
reg32:  INDIRU4(VREGP)     "# read register\n"
reg:    INDIRP2(VREGP)     "# read register\n"
regf: 	INDIRF4(VREGP)     "# read register\n"
regf: 	INDIRF8(VREGP)     "# read register\n"

stmt:   ASGNI1(VREGP,reg8)   "# write register\n"
stmt:   ASGNU1(VREGP,reg8)   "# write register\n"
stmt:   ASGNI2(VREGP,reg)    "# write register\n"
stmt:   ASGNU2(VREGP,reg)    "# write register\n"
stmt:   ASGNI4(VREGP,reg32)  "# write register\n"
stmt:   ASGNU4(VREGP,reg32)  "# write register\n"
stmt:   ASGNP2(VREGP,reg)    "# write register\n"
stmt:   ASGNF4(VREGP,regf) 	 "# write register\n"
stmt:   ASGNF8(VREGP,regf)   "# write register\n"

stmt:   reg                 ""

reg8:   LOADI1(reg8)        "\tpush\t%0\n\tpop\t%c\n" move(a)
reg8:   LOADI1(reg)         "# emit2\n" 1
reg8:   LOADU1(reg8)        "\tpush\t%0\n\tpop\t%c\n" move(a)
reg8:   LOADU1(reg)         "# emit2\n" 1
reg:    LOADI2(reg)         "\tmov\t%c,%0\n" move(a)
reg:    LOADU2(reg)         "\tmov\t%c,%0\n" move(a)
reg32:  LOADI4(reg32)       "\tCOPY32\t(%c,%0)\n" move(a)
reg32:  LOADU4(reg32)       "\tCOPY32\t(%c,%0)\n" move(a)
reg:    LOADP2(reg)         "\tmov\t%c,%0\n" move(a)
regf: 	LOADF4(regf)        "\tCOPY32\t(%c,%0)\n" move(a)
regf: 	LOADF8(regf)        "\tCOPY64\t(%c,%0)\n" move(a)

reg8:	LOADU1(LOADU2(CVII2(reg8)))	"%0"
reg8:	LOADI1(LOADI2(CVUU2(reg8)))	"%0"

con8:   CNSTI1              "%a"
con8:   CNSTU1              "%a"
con16:  CNSTI2              "%a"
con16:  CNSTU2              "%a"
con16:  CNSTP2              "%a"

con0:   CNSTI1              "%a"    range(a,0,0)
con0:   CNSTU1              "%a"    range(a,0,0)
con0:   CNSTI2              "%a"    range(a,0,0)
con0:   CNSTU2              "%a"    range(a,0,0)

con1:   CNSTI1              "%a"    range(a,1,1)
con1:   CNSTU1              "%a"    range(a,1,1)
con1:   CNSTI2              "%a"    range(a,1,1)
con1:   CNSTU2              "%a"    range(a,1,1)

con:	con8				"%a"
con:	con16				"%a"

reg:    con                 "\tld\t%c,%0\n" 2
reg:    con0                "\txor\t%c,%c\n" 1
reg8:   con8                "\tld\t%c,%0\n" 1

lgaddr: ADDRGP2             "(dp:%a)"
lgaddr: ADDRFP2             "(sp:%a+2+%F)"
lgaddr: ADDRLP2             "(sp:%a+%F)"
addr:	lgaddr				"%0"
albl:	ADDRGP2				"%a"
addr:   reg                 "(%0:0)"
addr:   ADDP2(reg,con)      "(%0:%1)"
addr:   SUBP2(reg,con)      "(%0:-%1)"

reg:	ADDP2(reg,con)	   "?\tmov\t%c,%0\n\tadd\t%c,%1\n" 2
reg:	SUBP2(reg,con)	   "?\tmov\t%c,%0\n\tsub\t%c,%1\n" 2

reg:	lgaddr				"\tlea\t%c,%0\n" 2

stmt:   ASGNI1(addr,reg8)   		"\tst\t%0,%1\n" 1
stmt:   ASGNU1(addr,reg8)   		"\tst\t%0,%1\n" 1
stmt:   ASGNI2(addr,reg)    		"\tst\t%0,%1\n" 2
stmt:   ASGNU2(addr,reg)    		"\tst\t%0,%1\n" 2
stmt:	ASGNP2(addr, reg)			"\tst\t%0,%1\n" 2
stmt:	ASGNB(reg,INDIRB(reg)) 		"# emit2\n" 1
stmt:	ASGNI4(addr,reg32)			"\tCOPY32\t(%0,%1)\n" 4
stmt:	ASGNI4(addr,INDIRI4(addr))	"\tCOPY32\t(%0,%1)\n" 4
stmt:	ASGNU4(addr,reg32)			"\tCOPY32\t(%0,%1)\n" 4
stmt:	ASGNU4(addr,INDIRU4(addr))	"\tCOPY32\t(%0,%1)\n" 4
stmt:	ASGNF4(addr,regf)			"\tCOPY32\t(%0,%1)\n" 4
stmt:	ASGNF4(addr,INDIRF4(addr))	"\tCOPY32\t(%0,%1)\n" 4
stmt:	ASGNF8(addr,regf)			"\tCOPY64\t(%0,%1)\n" 4
stmt:	ASGNF8(addr,INDIRF8(addr))	"\tCOPY64\t(%0,%1)\n" 4

reg8:   INDIRI1(addr)       "\tld\t%c,%0\n" 1
reg8:   INDIRU1(addr)       "\tld\t%c,%0\n" 1
reg:    INDIRI2(addr)       "\tld\t%c,%0\n" 2
reg:    INDIRU2(addr)       "\tld\t%c,%0\n" 2
reg:    INDIRP2(addr)       "\tld\t%c,%0\n" 2
reg32:	INDIRI4(addr)		"\tCOPY32\t(%c,%0)\n" 4
reg32:	INDIRU4(addr)		"\tCOPY32\t(%c,%0)\n" 4
regf:	INDIRF4(addr)		"\tCOPY32\t(%c,%0)\n" 4
regf:	INDIRF8(addr)		"\tCOPY64\t(%c,%0)\n" 4

reg8:   CVII1(reg)         	"\tmovb\t%c,%0\n" 2
reg8:   CVIU1(reg)         	"\tmovb\t%c,%0\n" 2
reg8:   CVUI1(reg)         	"\tmovb\t%c,%0\n" 2
reg8:   CVUU1(reg)         	"\tmovb\t%c,%0\n" 2
reg8:   CVII1(reg32)        "\tCVI4I1\t(%c,%0)\n" 4
reg8:   CVIU1(reg32)        "\tCVI4U1\t(%c,%0)\n" 4
reg8:   CVUI1(reg32)        "\tCVU4I1\t(%c,%0)\n" 4
reg8:   CVUU1(reg32)        "\tCVU4U1\t(%c,%0)\n" 4

reg:    CVII2(reg8)         "\tsex\t%c\n" 2
reg:    CVIU2(reg8)         "\tsex\t%c\n" 2
reg:    CVUI2(reg8)         "\tand\t%c,0x00ff\n" 2
reg:    CVUU2(reg8)         "\tand\t%c,0x00ff\n" 2
reg:    CVII2(reg32)        "\tCVI4I2\t(%c,%0)\n" 4
reg:    CVIU2(reg32)        "\tCVI4U2\t(%c,%0)\n" 4
reg:    CVUI2(reg32)        "\tCVU4I2\t(%c,%0)\n" 4
reg:    CVUU2(reg32)        "\tCVU4U2\t(%c,%0)\n" 4

reg32:  CVII4(reg8)         "\tCVI1I4\t(%c,%0)\n" 4
reg32:  CVIU4(reg8)         "\tCVI1U4\t(%c,%0)\n" 4
reg32:  CVUI4(reg8)         "\tCVU1I4\t(%c,%0)\n" 4
reg32:  CVUU4(reg8)         "\tCVU1U4\t(%c,%0)\n" 4
reg32:  CVII4(reg)        	"\tCVI2I4\t(%c,%0)\n" 4
reg32:  CVIU4(reg)        	"\tCVI2U4\t(%c,%0)\n" 4
reg32:  CVUI4(reg)        	"\tCVU2I4\t(%c,%0)\n" 4
reg32:  CVUU4(reg)        	"\tCVI2U4\t(%c,%0)\n" 4

regf:	CVIF4(reg8)			"\tCVTI1F4\t(%c,%0)\n" 4
regf:	CVIF4(reg)			"\tCVTI2F4\t(%c,%0)\n" 4
regf:	CVIF4(reg32)		"\tCVTI4F4\t(%c,%0)\n" 4

regf:	CVIF8(reg8)			"\tCVTI1F8\t(%c,%0)\n" 8
regf:	CVIF8(reg)			"\tCVTI2F8\t(%c,%0)\n" 8
regf:	CVIF8(reg32)		"\tCVTI4F8\t(%c,%0)\n" 8

reg: 	CVFI2(regf)			"\tCVTFI2\t(%c,%0)\n" 2
reg: 	CVFI4(regf)			"\tCVTFI4\t(%c,%0)\n" 2

regf: 	CVFF4(regf)			"\tCVTF8F4\t(%c,%0)\n" 4
regf: 	CVFF8(regf)			"\tCVTF4F8\t(%c,%0)\n" 4

reg: 	CVPU2(reg)			"\tmov\t%c,%0\n" move(a)
reg:	CVUP2(reg)			"\tmov\t%c,%0\n" move(a)

reg:    ADDI2(reg,reg)              "?\tmov\t%c,%0\n\tadd\t%c,%1\n" 2
reg:    ADDI2(reg,INDIRI2(addr))    "?\tmov\t%c,%0\n\tadd\t%c,%1\n" 2
reg:    ADDI2(reg,con)              "?\tmov\t%c,%0\n\tadd\t%c,%1\n" 2
reg:    ADDI2(reg,con1)             "?\tmov\t%c,%0\n\tinc\t%c\n" 	1
reg:    ADDU2(reg,reg)              "?\tmov\t%c,%0\n\tadd\t%c,%1\n" 2
reg:    ADDU2(reg,INDIRU2(addr))    "?\tmov\t%c,%0\n\tadd\t%c,%1\n" 2
reg:    ADDU2(reg,con)              "?\tmov\t%c,%0\n\tadd\t%c,%1\n" 2
reg:    ADDU2(reg,con1)             "?\tmov\t%c,%0\n\tinc\t%c\n" 	1
reg:    ADDP2(reg,reg)              "?\tmov\t%c,%0\n\tadd\t%c,%1\n" 2
reg:	ADDP2(reg,con)				"\tlea\t%c,(%0:%1)\n" 2

reg8:   ADDI2(reg8,CVII2(INDIRI1(addr)))            "# emit2 (use AH/AL instead of A)\n" 1
reg8:   ADDI2(CVII2(reg8),CVII2(INDIRI1(addr)))     "# emit2 (use AH/AL instead of A)\n" 1
reg8:   ADDI2(CVUI2(reg8),CVII2(INDIRI1(addr)))     "# emit2 (use AH/AL instead of A)\n" 1
reg8:   ADDI2(reg8,con)                             "# emit2 (use AH/AL instead of A)\n" 1
reg8:   ADDI2(CVII2(reg8),con)                      "# emit2 (use AH/AL instead of A)\n" 1
reg8:   ADDI2(CVUI2(reg8),con)                      "# emit2 (use AH/AL instead of A)\n" 1
reg8:   ADDU2(reg8,CVUU2(INDIRU1(addr)))            "# emit2 (use AH/AL instead of A)\n" 1
reg8:   ADDU2(CVUU2(reg8),CVUU2(INDIRU1(addr)))     "# emit2 (use AH/AL instead of A)\n" 1
reg8:   ADDU2(CVIU2(reg8),CVUU2(INDIRU1(addr)))     "# emit2 (use AH/AL instead of A)\n" 1
reg8:   ADDU2(reg8,con)                             "# emit2 (use AH/AL instead of A)\n" 1
reg8:   ADDU2(CVUU2(reg8),con)                      "# emit2 (use AH/AL instead of A)\n" 1
reg8:   ADDU2(CVIU2(reg8),con)                      "# emit2 (use AH/AL instead of A)\n" 1

reg32:	ADDI4(reg32,reg32)					"?\tCOPY32\t(%c,%0)\n\tADDI32\t(%c,%1)\n" 4
reg32:	ADDI4(reg32,INDIRI4(addr))			"?\tCOPY32\t(%c,%0)\n\tADDI32\t(%c,%1)\n" 4
reg32:	ADDU4(reg32,reg32)					"?\tCOPY32\t(%c,%0)\n\tADDU32\t(%c,%1)\n" 4
reg32:	ADDU4(reg32,INDIRU4(addr))			"?\tCOPY32\t(%c,%0)\n\tADDU32\t(%c,%1)\n" 4

regf:	ADDF4(regf,regf)					"?\tCOPY32\t(%c,%0)\n\tADDF32\t(%c,%1)\n" 4
regf:	ADDF4(regf,INDIRF4(addr))			"?\tCOPY32\t(%c,%0)\n\tADDF32\t(%c,%1)\n" 4
regf:	ADDF8(regf,regf)					"?\tCOPY64\t(%c,%0)\n\tADDF64\t(%c,%1)\n" 8
regf:	ADDF8(regf,INDIRF8(addr))			"?\tCOPY64\t(%c,%0)\n\tADDF64\t(%c,%1)\n" 8

stmt:	ASGNI4(addr, ADDI4(INDIRI4(addr),INDIRI4(addr)))	"\tCOPY32\t(%0,%1)\n\tADDI32(%0,%2)\n" 4
stmt:	ASGNI4(addr, ADDI4(INDIRI4(addr),INDIRI4(addr)))	"\tADDI32\t(%1,%2)\n" memop(a)
stmt:	ASGNF4(addr, ADDF4(INDIRF4(addr),INDIRF4(addr)))	"\tCOPY32\t(%0,%1)\n\tADDF32(%0,%2)\n" 4
stmt:	ASGNF4(addr, ADDF4(INDIRF4(addr),INDIRF4(addr)))	"\tADDF32\t(%1,%2)\n" memop(a)
stmt:	ASGNF8(addr, ADDF8(INDIRF8(addr),INDIRF8(addr)))	"\tCOPY64\t(%0,%1)\n\tADDF64(%0,%2)\n" 8
stmt:	ASGNF8(addr, ADDF8(INDIRF8(addr),INDIRF8(addr)))	"\tADDF64\t(%1,%2)\n" memop(a)

reg:    SUBI2(reg,reg)              "?\tmov\t%c,%0\n\tsub\t%c,%1\n" 2
reg:    SUBI2(reg,INDIRI2(addr))    "?\tmov\t%c,%0\n\tsub\t%c,%1\n" 2
reg:    SUBI2(reg,con)              "?\tmov\t%c,%0\n\tsub\t%c,%1\n" 2
reg:    SUBI2(reg,con1)             "?\tmov\t%c,%0\n\tdec\t%c\n" 	1
reg:    SUBU2(reg,reg)              "?\tmov\t%c,%0\n\tsub\t%c,%1\n" 2
reg:    SUBU2(reg,INDIRU2(addr))    "?\tmov\t%c,%0\n\tsub\t%c,%1\n" 2
reg:    SUBU2(reg,con)              "?\tmov\t%c,%0\n\tsub\t%c,%1\n" 2
reg:    SUBU2(reg,con1)             "?\tmov\t%c,%0\n\tdec\t%c\n" 	1
reg:    SUBP2(reg,reg)              "?\tmov\t%c,%0\n\tsub\t%c,%1\n" 2
reg:	ADDP2(reg,con)				"\tlea\t%c,(%0:-%1)\n" 2

reg8:   SUBI2(reg8,CVII2(INDIRI1(addr)))            "# emit2 (use AH/AL instead of A)\n" 1
reg8:   SUBI2(CVII2(reg8),CVII2(INDIRI1(addr)))     "# emit2 (use AH/AL instead of A)\n" 1
reg8:   SUBI2(CVUI2(reg8),CVII2(INDIRI1(addr)))     "# emit2 (use AH/AL instead of A)\n" 1
reg8:   SUBI2(reg8,con)                             "# emit2 (use AH/AL instead of A)\n" 1
reg8:   SUBI2(CVII2(reg8),con)                      "# emit2 (use AH/AL instead of A)\n" 1
reg8:   SUBI2(CVUI2(reg8),con)                      "# emit2 (use AH/AL instead of A)\n" 1
reg8:   SUBU2(reg8,CVUU2(INDIRU1(addr)))            "# emit2 (use AH/AL instead of A)\n" 1
reg8:   SUBU2(CVUU2(reg8),CVUU2(INDIRU1(addr)))     "# emit2 (use AH/AL instead of A)\n" 1
reg8:   SUBU2(CVIU2(reg8),CVUU2(INDIRU1(addr)))     "# emit2 (use AH/AL instead of A)\n" 1
reg8:   SUBU2(reg8,con)                             "# emit2 (use AH/AL instead of A)\n" 1
reg8:   SUBU2(CVUU2(reg8),con)                      "# emit2 (use AH/AL instead of A)\n" 1
reg8:   SUBU2(CVIU2(reg8),con)                      "# emit2 (use AH/AL instead of A)\n" 1

reg32:	SUBI4(reg32,reg32)					"?\tCOPY32\t(%c,%0)\n\tSUBI32\t(%c,%1)\n" 4
reg32:	SUBI4(reg32,INDIRI4(addr))			"?\tCOPY32\t(%c,%0)\n\tSUBI32\t(%c,%1)\n" 4
reg32:	SUBU4(reg32,reg32)					"?\tCOPY32\t(%c,%0)\n\tSUBU32\t(%c,%1)\n" 4
reg32:	SUBU4(reg32,INDIRU4(addr))			"?\tCOPY32\t(%c,%0)\n\tSUBU32\t(%c,%1)\n" 4

regf:	SUBF4(regf,regf)					"?\tCOPY32\t(%c,%0)\n\tSUBF32\t(%c,%1)\n" 4
regf:	SUBF4(regf,INDIRF4(addr))			"?\tCOPY32\t(%c,%0)\n\tSUBF32\t(%c,%1)\n" 4
regf:	SUBF8(regf,regf)					"?\tCOPY64\t(%c,%0)\n\tSUBF64\t(%c,%1)\n" 8
regf:	SUBF8(regf,INDIRF8(addr))			"?\tCOPY64\t(%c,%0)\n\tSUBF64\t(%c,%1)\n" 8

stmt:	ASGNI4(addr, SUBI4(INDIRI4(addr),INDIRI4(addr)))	"\tCOPY32\t(%0,%1)\n\tSUBI32(%0,%2)\n" 4
stmt:	ASGNI4(addr, SUBI4(INDIRI4(addr),INDIRI4(addr)))	"\tSUBI32\t(%1,%2)\n" memop(a)
stmt:	ASGNF4(addr, SUBF4(INDIRF4(addr),INDIRF4(addr)))	"\tCOPY32\t(%0,%1)\n\tSUBF32(%0,%2)\n" 4
stmt:	ASGNF4(addr, SUBF4(INDIRF4(addr),INDIRF4(addr)))	"\tSUBF32\t(%1,%2)\n" memop(a)
stmt:	ASGNF8(addr, SUBF8(INDIRF8(addr),INDIRF8(addr)))	"\tCOPY64\t(%0,%1)\n\tSUBF64(%0,%2)\n" 8
stmt:	ASGNF8(addr, SUBF8(INDIRF8(addr),INDIRF8(addr)))	"\tSUBF64\t(%1,%2)\n" memop(a)

reg:	NEGI2(reg)					"\txor\t%c,%c\n\tsub\t%c,%0\n" 2
reg:	NEGI2(INDIRI2(addr))		"\txor\t%c,%c\n\tsub\t%c,%0\n" 2
reg32:	NEGI4(reg32)				"\tNEGI32\t(%c,%0)\n" 4
reg32:	NEGI4(INDIRI4(addr))		"\tNEGI32\t(%c,%0)\n" 4

regf:	NEGF4(regf)					"\tNEGF32\t(%c,%0)\n" 4
regf:	NEGF4(INDIRF4(addr))		"\tNEGF32\t(%c,%0)\n" 4
regf:	NEGF8(regf)					"\tNEGF64\t(%c,%0)\n" 8
regf:	NEGF8(INDIRF8(addr))		"\tNEGF64\t(%c,%0)\n" 8

reg:    BANDI2(reg,reg)              "?\tmov\t%c,%0\n\tand\t%c,%1\n" 2
reg:    BANDI2(reg,INDIRI2(lgaddr))  "?\tmov\t%c,%0\n\tand\t%c,%1\n" 2
reg:    BANDI2(reg,con)              "?\tmov\t%c,%0\n\tand\t%c,%1\n" 2
reg:    BANDU2(reg,reg)              "?\tmov\t%c,%0\n\tand\t%c,%1\n" 2
reg:    BANDU2(reg,INDIRU2(lgaddr))  "?\tmov\t%c,%0\n\tand\t%c,%1\n" 2
reg:    BANDU2(reg,con)              "?\tmov\t%c,%0\n\tand\t%c,%1\n" 2

reg8:   BANDI2(reg8,CVII2(INDIRI1(lgaddr)))          "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BANDI2(CVII2(reg8),CVII2(INDIRI1(lgaddr)))   "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BANDI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))   "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BANDI2(reg8,con)                             "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BANDI2(CVII2(reg8),con)                      "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BANDI2(CVUI2(reg8),con)                      "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BANDU2(reg8,CVUU2(INDIRU1(lgaddr)))          "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BANDU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))   "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BANDU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))   "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BANDU2(reg8,con)                             "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BANDU2(CVUU2(reg8),con)                      "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BANDU2(CVIU2(reg8),con)                      "# emit2 (use AH/AL instead of A)\n" 1

reg32:  BANDI4(reg32,reg32)            "?\tCOPY32\t%(c,%0)\n\tBANDI32\t(%c,%1)\n" 4
reg32:  BANDI4(reg32,INDIRI4(addr))    "?\tCOPY32\t%(c,%0)\n\tBANDI32\t(%c,%1)\n" 4
reg32:  BANDU4(reg32,reg32)            "?\tCOPY32\t%(c,%0)\n\tBANDI32\t(%c,%1)\n" 4
reg32:  BANDU4(reg32,INDIRU4(addr))    "?\tCOPY32\t%(c,%0)\n\tBANDI32\t(%c,%1)\n" 4

reg:    BCOMI2(reg)              	"\tmov\t%c,-1\n\txor\t%c,%0\n" 2
reg:    BCOMU2(reg)              	"\tmov\t%c,-1\n\txor\t%c,%0\n" 2
reg32:	BCOMI4(reg32)				"\tBCOMI4\t(%c,%0)\n" 4
reg32:	BCOMU4(reg32)				"\tBCOMI4\t(%c,%0)\n" 4

reg:    BORI2(reg,reg)              "?\tmov\t%c,%0\n\tor\t%c,%1\n" 2
reg:    BORI2(reg,INDIRI2(lgaddr))  "?\tmov\t%c,%0\n\tor\t%c,%1\n" 2
reg:    BORI2(reg,con)              "?\tmov\t%c,%0\n\tor\t%c,%1\n" 2
reg:    BORU2(reg,reg)              "?\tmov\t%c,%0\n\tor\t%c,%1\n" 2
reg:    BORU2(reg,INDIRU2(lgaddr))  "?\tmov\t%c,%0\n\tor\t%c,%1\n" 2
reg:    BORU2(reg,con)              "?\tmov\t%c,%0\n\tor\t%c,%1\n" 2

reg8:   BORI2(reg8,CVII2(INDIRI1(lgaddr)))          "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BORI2(CVII2(reg8),CVII2(INDIRI1(lgaddr)))   "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BORI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))   "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BORI2(reg8,con)                             "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BORI2(CVII2(reg8),con)                      "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BORI2(CVUI2(reg8),con)                      "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BORU2(reg8,CVUU2(INDIRU1(lgaddr)))          "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BORU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))   "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BORU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))   "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BORU2(reg8,con)                             "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BORU2(CVUU2(reg8),con)                      "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BORU2(CVIU2(reg8),con)                      "# emit2 (use AH/AL instead of A)\n" 1

reg32:  BORI4(reg32,reg32)            "?\tCOPY32\t%(c,%0)\n\tBORI32\t(%c,%1)\n" 4
reg32:  BORI4(reg32,INDIRI4(addr))    "?\tCOPY32\t%(c,%0)\n\tBORI32\t(%c,%1)\n" 4
reg32:  BORU4(reg32,reg32)            "?\tCOPY32\t%(c,%0)\n\tBORI32\t(%c,%1)\n" 4
reg32:  BORU4(reg32,INDIRU4(addr))    "?\tCOPY32\t%(c,%0)\n\tBORI32\t(%c,%1)\n" 4

reg:    BXORI2(reg,reg)              "?\tmov\t%c,%0\n\txor\t%c,%1\n" 2
reg:    BXORI2(reg,INDIRI2(lgaddr))  "?\tmov\t%c,%0\n\txor\t%c,%1\n" 2
reg:    BXORI2(reg,con)              "?\tmov\t%c,%0\n\txor\t%c,%1\n" 2
reg:    BXORU2(reg,reg)              "?\tmov\t%c,%0\n\txor\t%c,%1\n" 2
reg:    BXORU2(reg,INDIRU2(lgaddr))  "?\tmov\t%c,%0\n\txor\t%c,%1\n" 2
reg:    BXORU2(reg,con)              "?\tmov\t%c,%0\n\txor\t%c,%1\n" 2

reg8:   BXORI2(reg8,CVII2(INDIRI1(lgaddr)))          "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BXORI2(CVII2(reg8),CVII2(INDIRI1(lgaddr)))   "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BXORI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))   "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BXORI2(reg8,con)                             "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BXORI2(CVII2(reg8),con)                      "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BXORI2(CVUI2(reg8),con)                      "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BXORU2(reg8,CVUU2(INDIRU1(lgaddr)))          "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BXORU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))   "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BXORU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))   "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BXORU2(reg8,con)                             "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BXORU2(CVUU2(reg8),con)                      "# emit2 (use AH/AL instead of A)\n" 1
reg8:   BXORU2(CVIU2(reg8),con)                      "# emit2 (use AH/AL instead of A)\n" 1


reg32:  BXORI4(reg32,reg32)            "?\tCOPY32\t%(c,%0)\n\tBXORI32\t(%c,%1)\n" 4
reg32:  BXORI4(reg32,INDIRI4(addr))    "?\tCOPY32\t%(c,%0)\n\tBXORI32\t(%c,%1)\n" 4
reg32:  BXORU4(reg32,reg32)            "?\tCOPY32\t%(c,%0)\n\tBXORI32\t(%c,%1)\n" 4
reg32:  BXORU4(reg32,INDIRU4(addr))    "?\tCOPY32\t%(c,%0)\n\tBXORI32\t(%c,%1)\n" 4

reg:	MULI2(reg,reg)								 "?\tmov\t%c,%0\n\tcall\t__muli2\n" 4
reg:	MULU2(reg,reg)								 "?\tmov\t%c,%0\n\tcall\t__mulu2\n" 4
reg:	DIVI2(reg,reg)								 "?\tmov\t%c,%0\n\tcall\t__divi2\n" 4
reg:	DIVU2(reg,reg)								 "?\tmov\t%c,%0\n\tcall\t__divu2\n" 4
reg:	MODI2(reg,reg)								 "?\tmov\t%c,%0\n\tcall\t__modi2\n" 4
reg:	MODU2(reg,reg)								 "?\tmov\t%c,%0\n\tcall\t__modu2\n" 4

reg32:	MULI4(reg32,reg32)							 "?\tCOPY32\t%(c,%0)\n\tMULI32\t(%c,%1)\n" 4
reg32:	MULI4(reg32,INDIRI4(addr))					 "?\tCOPY32\t%(c,%0)\n\tMULI32\t(%c,%1)\n" 4
reg32:	MULU4(reg32,reg32)							 "?\tCOPY32\t%(c,%0)\n\tMULU32\t(%c,%1)\n" 4
reg32:	MULU4(reg32,INDIRU4(addr))					 "?\tCOPY32\t%(c,%0)\n\tMULU32\t(%c,%1)\n" 4
reg32:	DIVI4(reg32,reg32)							 "?\tCOPY32\t%(c,%0)\n\tDIVI32\t(%c,%1)\n" 4
reg32:	DIVI4(reg32,INDIRI4(addr))					 "?\tCOPY32\t%(c,%0)\n\tDIVI32\t(%c,%1)\n" 4
reg32:	DIVU4(reg32,reg32)							 "?\tCOPY32\t%(c,%0)\n\tDIVU32\t(%c,%1)\n" 4
reg32:	DIVU4(reg32,INDIRU4(addr))					 "?\tCOPY32\t%(c,%0)\n\tDIVU32\t(%c,%1)\n" 4
reg32:	MODI4(reg32,reg32)							 "?\tCOPY32\t%(c,%0)\n\tMODI32\t(%c,%1)\n" 4
reg32:	MODI4(reg32,INDIRI4(addr))					 "?\tCOPY32\t%(c,%0)\n\tMODI32\t(%c,%1)\n" 4
reg32:	MODU4(reg32,reg32)							 "?\tCOPY32\t%(c,%0)\n\tMODU32\t(%c,%1)\n" 4
reg32:	MODU4(reg32,INDIRU4(addr))					 "?\tCOPY32\t%(c,%0)\n\tMODU32\t(%c,%1)\n" 4

regf:	MULF4(regf,regf)							"?\tCOPY32\t%(c,%0)\n\tMULF32\t(%c,%1)\n" 4
regf:	MULF4(regf,INDIRF4(addr))					"?\tCOPY32\t%(c,%0)\n\tMULF32\t(%c,%1)\n" 4
regf:	MULF8(regf,regf)							"?\tCOPY64\t%(c,%0)\n\tMULF64\t(%c,%1)\n" 4
regf:	MULF8(regf,INDIRF8(addr))					"?\tCOPY64\t%(c,%0)\n\tMULF64\t(%c,%1)\n" 4
regf:	DIVF4(regf,regf)							"?\tCOPY32\t%(c,%0)\n\tDIVF32\t(%c,%1)\n" 4
regf:	DIVF4(regf,INDIRF4(addr))					"?\tCOPY32\t%(c,%0)\n\tDIVF32\t(%c,%1)\n" 4
regf:	DIVF8(regf,regf)							"?\tCOPY64\t%(c,%0)\n\tDIVF64\t(%c,%1)\n" 4
regf:	DIVF8(regf,INDIRF8(addr))					"?\tCOPY64\t%(c,%0)\n\tDIVF64\t(%c,%1)\n" 4

reg:	LSHI2(reg,con1)							"?\tmov\t%c,%0\n\tshl\t%0\n" 2
reg:	LSHU2(reg,con1)							"?\tmov\t%c,%0\n\tshl\t%0\n" 2
reg:	RSHI2(reg,con1)							"?\tmov\t%c,%0\n\tshr\t%0\n" 2
reg:	RSHU2(reg,con1)							"?\tmov\t%c,%0\n\tshr\t%0\n" 2

reg8:   LSHI2(reg8,con)                         "# emit2 (use AH/AL instead of A)\n" 1
reg8:   LSHI2(CVII2(reg8),con)                  "# emit2 (use AH/AL instead of A)\n" 1
reg8:   LSHI2(CVUI2(reg8),con)                  "# emit2 (use AH/AL instead of A)\n" 1
reg8:   LSHU2(reg8,con)                         "# emit2 (use AH/AL instead of A)\n" 1
reg8:   LSHU2(CVUU2(reg8),con)                  "# emit2 (use AH/AL instead of A)\n" 1
reg8:   LSHU2(CVIU2(reg8),con)                  "# emit2 (use AH/AL instead of A)\n" 1
reg8:   RSHI2(reg8,con)                         "# emit2 (use AH/AL instead of A)\n" 1
reg8:   RSHI2(CVII2(reg8),con)                  "# emit2 (use AH/AL instead of A)\n" 1
reg8:   RSHI2(CVUI2(reg8),con)                  "# emit2 (use AH/AL instead of A)\n" 1
reg8:   RSHU2(reg8,con)                         "# emit2 (use AH/AL instead of A)\n" 1
reg8:   RSHU2(CVUU2(reg8),con)                  "# emit2 (use AH/AL instead of A)\n" 1
reg8:   RSHU2(CVIU2(reg8),con)                  "# emit2 (use AH/AL instead of A)\n" 1

reg32:	RSHI4(reg32,con1)						"?\tCOPY32\t(%c,%0)\n\tRSHI32\t(%0)\n" 2
reg32:	RSHU4(reg32,con1)						"?\tCOPY32\t(%c,%0)\n\tRSHU32\t(%0)\n" 2

stmt:   EQI2(reg,reg)                           	"\tcmp\t%0,%1\n\tje\t%a\n" 2
stmt:   EQI2(reg,INDIRI2(lgaddr))               	"\tcmp\t%0,%1\n\tje\t%a\n" 2
stmt:   EQI2(reg,con)                           	"\tcmp\t%0,%1\n\tje\t%a\n" 2
stmt:   EQI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) 	"\tcmp\t%0,%1\n\tje\t%a\n" 1
stmt:   EQI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))  	"\tcmp\t%0,%1\n\tje\t%a\n" 1
stmt:   EQI2(CVII2(reg8),con)                   	"\tcmp\t%0,%1\n\tje\t%a\n" 1
stmt:   EQI2(CVUI2(reg8),con)                   	"\tcmp\t%0,%1\n\tje\t%a\n" 1
stmt:   EQU2(reg,reg)                           	"\tcmp\t%0,%1\n\tje\t%a\n" 2
stmt:   EQU2(reg,INDIRU2(lgaddr))               	"\tcmp\t%0,%1\n\tje\t%a\n" 2
stmt:   EQU2(reg,con)                           	"\tcmp\t%0,%1\n\tje\t%a\n" 2
stmt:   EQU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))  	"\tcmp\t%0,%1\n\tje\t%a\n" 1
stmt:   EQU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))  	"\tcmp\t%0,%1\n\tje\t%a\n" 1
stmt:   EQU2(CVUU2(reg8),con)                   	"\tcmp\t%0,%1\n\tje\t%a\n" 1
stmt:   EQU2(CVIU2(reg8),con)                   	"\tcmp\t%0,%1\n\tje\t%a\n" 1

stmt:	EQI4(reg32,reg32)						"\tCMP32\t(%0,%1)\n\tje\t%a\n" 4
stmt:	EQI4(reg32,INDIRI4(addr))				"\tCMP32\t(%0,%1)\n\tje\t%a\n" 4
stmt:	EQU4(reg32,reg32)						"\tCMP32\t(%0,%1)\n\tje\t%a\n" 4
stmt:	EQU4(reg32,INDIRU4(addr))				"\tCMP32\t(%0,%1)\n\tje\t%a\n" 4
stmt:	EQF4(regf,regf)							"\tCMP32\t(%0,%1)\n\tje\t%a\n" 4
stmt:	EQF4(regf,INDIRF4(addr))				"\tCMP32\t(%0,%1)\n\tje\t%a\n" 4
stmt:	EQF8(regf,regf)							"\tCMP64\t(%0,%1)\n\tje\t%a\n" 8
stmt:	EQF8(regf,INDIRF8(addr))				"\tCMP64\t(%0,%1)\n\tje\t%a\n" 8

stmt:   NEI2(reg,reg)                           	"\tcmp\t%0,%1\n\tjne\t%a\n" 2
stmt:   NEI2(reg,INDIRI2(reg))                  	"\tcmp\t%0,%1\n\tjne\t%a\n" 2
stmt:   NEI2(reg,con)                           	"\tcmp\t%0,%1\n\tjne\t%a\n" 2
stmt:   NEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr)))  	"\tcmp\t%0,%1\n\tjne\t%a\n" 1
stmt:   NEI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))  	"\tcmp\t%0,%1\n\tjne\t%a\n" 1
stmt:   NEI2(CVII2(reg8),con)                   	"\tcmp\t%0,%1\n\tjne\t%a\n" 1
stmt:   NEI2(CVUI2(reg8),con)                   	"\tcmp\t%0,%1\n\tjne\t%a\n" 1
stmt:   NEU2(reg,reg)                           	"\tcmp\t%0,%1\n\tjne\t%a\n" 2
stmt:   NEU2(reg,INDIRU2(reg))                  	"\tcmp\t%0,%1\n\tjne\t%a\n" 2
stmt:   NEU2(reg,con)                           	"\tcmp\t%0,%1\n\tjne\t%a\n" 2
stmt:   NEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))  	"\tcmp\t%0,%1\n\tjne\t%a\n" 1
stmt:   NEU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))  	"\tcmp\t%0,%1\n\tjne\t%a\n" 1
stmt:   NEU2(CVUU2(reg8),con)                   	"\tcmp\t%0,%1\n\tjne\t%a\n" 1
stmt:   NEU2(CVIU2(reg8),con)                   	"\tcmp\t%0,%1\n\tjne\t%a\n" 1

stmt:	NEI4(reg32,reg32)						"\tCMP32\t(%0,%1)\n\tjne\t%a\n" 4
stmt:	NEI4(reg32,INDIRI4(addr))				"\tCMP32\t(%0,%1)\n\tjne\t%a\n" 4
stmt:	NEU4(reg32,reg32)						"\tCMP32\t(%0,%1)\n\tjne\t%a\n" 4
stmt:	NEU4(reg32,INDIRU4(addr))				"\tCMP32\t(%0,%1)\n\tjne\t%a\n" 4
stmt:	NEF4(regf,regf)							"\tCMP32\t(%0,%1)\n\tjne\t%a\n" 4
stmt:	NEF4(regf,INDIRF4(addr))				"\tCMP32\t(%0,%1)\n\tjne\t%a\n" 4
stmt:	NEF8(regf,regf)							"\tCMP64\t(%0,%1)\n\tjne\t%a\n" 8
stmt:	NEF8(regf,INDIRF8(addr))				"\tCMP64\t(%0,%1)\n\tjne\t%a\n" 8

stmt:   LEI2(reg,reg)                           	"\tcmp\t%0,%1\n\tjle\t%a\n" 2
stmt:   LEI2(reg,INDIRI2(reg))                   	"\tcmp\t%0,%1\n\tjle\t%a\n" 2
stmt:   LEI2(reg,con)                           	"\tcmp\t%0,%1\n\tjle\t%a\n" 2
stmt:   LEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr)))  	"\tcmp\t%0,%1\n\tjle\t%a\n" 1
stmt:   LEI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))  	"\tcmp\t%0,%1\n\tjle\t%a\n" 1
stmt:   LEI2(CVII2(reg8),con)                   	"\tcmp\t%0,%1\n\tjle\t%a\n" 1
stmt:   LEI2(CVUI2(reg8),con)                   	"\tcmp\t%0,%1\n\tjle\t%a\n" 1
stmt:   LEU2(reg,reg)                           	"\tcmp\t%0,%1\n\tjleu\t%a\n" 2
stmt:   LEU2(reg,INDIRU2(reg))                   	"\tcmp\t%0,%1\n\tjleu\t%a\n" 2
stmt:   LEU2(reg,con)                           	"\tcmp\t%0,%1\n\tjleu\t%a\n" 2
stmt:   LEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))  	"\tcmp\t%0,%1\n\tjleu\t%a\n" 1
stmt:   LEU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))  	"\tcmp\t%0,%1\n\tjleu\t%a\n" 1
stmt:   LEU2(CVUU2(reg8),con)                   	"\tcmp\t%0,%1\n\tjleu\t%a\n" 1
stmt:   LEU2(CVIU2(reg8),con)                   	"\tcmp\t%0,%1\n\tjleu\t%a\n" 1

stmt:	LEI4(reg32,reg32)						"\tCMP32\t(%0,%1)\n\tjle\t%a\n" 4
stmt:	LEI4(reg32,INDIRI4(addr))				"\tCMP32\t(%0,%1)\n\tjle\t%a\n" 4
stmt:	LEU4(reg32,reg32)						"\tCMP32\t(%0,%1)\n\tjleu\t%a\n" 4
stmt:	LEU4(reg32,INDIRU4(addr))				"\tCMP32\t(%0,%1)\n\tjleu\t%a\n" 4
stmt:	LEF4(regf,regf)							"\tCMP32\t(%0,%1)\n\tjle\t%a\n" 4
stmt:	LEF4(regf,INDIRF4(addr))				"\tCMP32\t(%0,%1)\n\tjle\t%a\n" 4
stmt:	LEF8(regf,regf)							"\tCMP64\t(%0,%1)\n\tjle\t%a\n" 8
stmt:	LEF8(regf,INDIRF8(addr))				"\tCMP64\t(%0,%1)\n\tjle\t%a\n" 8

stmt:   LTI2(reg,reg)                           	"\tcmp\t%0,%1\n\tjl\t%a\n" 2
stmt:   LTI2(reg,INDIRI2(reg))                   	"\tcmp\t%0,%1\n\tjl\t%a\n" 2
stmt:   LTI2(reg,con)                           	"\tcmp\t%0,%1\n\tjl\t%a\n" 2
stmt:   LTI2(CVII2(reg8),CVII2(INDIRI1(lgaddr)))  	"\tcmp\t%0,%1\n\tjl\t%a\n" 1
stmt:   LTI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))  	"\tcmp\t%0,%1\n\tjl\t%a\n" 1
stmt:   LTI2(CVII2(reg8),con)                   	"\tcmp\t%0,%1\n\tjl\t%a\n" 1
stmt:   LTI2(CVUI2(reg8),con)                   	"\tcmp\t%0,%1\n\tjl\t%a\n" 1
stmt:   LTU2(reg,reg)                           	"\tcmp\t%0,%1\n\tjlu\t%a\n" 2
stmt:   LTU2(reg,INDIRU2(reg))                  	"\tcmp\t%0,%1\n\tjlu\t%a\n" 2
stmt:   LTU2(reg,con)                           	"\tcmp\t%0,%1\n\tjlu\t%a\n" 2
stmt:   LTU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))  	"\tcmp\t%0,%1\n\tjlu\t%a\n" 1
stmt:   LTU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))  	"\tcmp\t%0,%1\n\tjlu\t%a\n" 1
stmt:   LTU2(CVUU2(reg8),con)                   	"\tcmp\t%0,%1\n\tjlu\t%a\n" 1
stmt:   LTU2(CVIU2(reg8),con)                   	"\tcmp\t%0,%1\n\tjlu\t%a\n" 1

stmt:	LTI4(reg32,reg32)						"\tCMP32\t(%0,%1)\n\tjlt\t%a\n" 4
stmt:	LTI4(reg32,INDIRI4(addr))				"\tCMP32\t(%0,%1)\n\tjlt\t%a\n" 4
stmt:	LTU4(reg32,reg32)						"\tCMP32\t(%0,%1)\n\tjltu\t%a\n" 4
stmt:	LTU4(reg32,INDIRU4(addr))				"\tCMP32\t(%0,%1)\n\tjltu\t%a\n" 4
stmt:	LTF4(regf,regf)							"\tCMP32\t(%0,%1)\n\tjlt\t%a\n" 4
stmt:	LTF4(regf,INDIRF4(addr))				"\tCMP32\t(%0,%1)\n\tjlt\t%a\n" 4
stmt:	LTF8(regf,regf)							"\tCMP64\t(%0,%1)\n\tjlt\t%a\n" 8
stmt:	LTF8(regf,INDIRF8(addr))				"\tCMP64\t(%0,%1)\n\tjlt\t%a\n" 8

stmt:   GEI2(reg,reg)                           	"\tcmp\t%0,%1\n\tjge\t%a\n" 2
stmt:   GEI2(reg,INDIRI2(reg))                   	"\tcmp\t%0,%1\n\tjge\t%a\n" 2
stmt:   GEI2(reg,con)                           	"\tcmp\t%0,%1\n\tjge\t%a\n" 2
stmt:   GEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr)))  	"\tcmp\t%0,%1\n\tjge\t%a\n" 1
stmt:   GEI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))  	"\tcmp\t%0,%1\n\tjge\t%a\n" 1
stmt:   GEI2(CVII2(reg8),con)                   	"\tcmp\t%0,%1\n\tjge\t%a\n" 1
stmt:   GEI2(CVUI2(reg8),con)                   	"\tcmp\t%0,%1\n\tjge\t%a\n" 1
stmt:   GEU2(reg,reg)                           	"\tcmp\t%0,%1\n\tjgeu\t%a\n" 2
stmt:   GEU2(reg,INDIRU2(reg))                   	"\tcmp\t%0,%1\n\tjgeu\t%a\n" 2
stmt:   GEU2(reg,con)                           	"\tcmp\t%0,%1\n\tjgeu\t%a\n" 2
stmt:   GEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))  	"\tcmp\t%0,%1\n\tjgeu\t%a\n" 1
stmt:   GEU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))  	"\tcmp\t%0,%1\n\tjgeu\t%a\n" 1
stmt:   GEU2(CVUU2(reg8),con)                   	"\tcmp\t%0,%1\n\tjgeu\t%a\n" 1
stmt:   GEU2(CVIU2(reg8),con)                   	"\tcmp\t%0,%1\n\tjgeu\t%a\n" 1

stmt:	GEI4(reg32,reg32)						"\tCMP32\t(%0,%1)\n\tjge\t%a\n" 4
stmt:	GEI4(reg32,INDIRI4(addr))				"\tCMP32\t(%0,%1)\n\tjge\t%a\n" 4
stmt:	GEU4(reg32,reg32)						"\tCMP32\t(%0,%1)\n\tjgeu\t%a\n" 4
stmt:	GEU4(reg32,INDIRU4(addr))				"\tCMP32\t(%0,%1)\n\tjgeu\t%a\n" 4
stmt:	GEF4(regf,regf)							"\tCMP32\t(%0,%1)\n\tjge\t%a\n" 4
stmt:	GEF4(regf,INDIRF4(addr))				"\tCMP32\t(%0,%1)\n\tjge\t%a\n" 4
stmt:	GEF8(regf,regf)							"\tCMP64\t(%0,%1)\n\tjge\t%a\n" 8
stmt:	GEF8(regf,INDIRF8(addr))				"\tCMP64\t(%0,%1)\n\tjge\t%a\n" 8

stmt:   GTI2(reg,reg)                           	"\tcmp\t%0,%1\n\tjg\t%a\n" 2
stmt:   GTI2(reg,INDIRI2(reg))                      "\tcmp\t%0,%1\n\tjg\t%a\n" 2
stmt:   GTI2(reg,con)                           	"\tcmp\t%0,%1\n\tjg\t%a\n" 2
stmt:   GTI2(CVII2(reg8),CVII2(INDIRI1(lgaddr)))  	"\tcmp\t%0,%1\n\tjg\t%a\n" 1
stmt:   GTI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))  	"\tcmp\t%0,%1\n\tjg\t%a\n" 1
stmt:   GTI2(CVII2(reg8),con)                   	"\tcmp\t%0,%1\n\tjg\t%a\n" 1
stmt:   GTI2(CVUI2(reg8),con)                   	"\tcmp\t%0,%1\n\tjg\t%a\n" 1
stmt:   GTU2(reg,reg)                           	"\tcmp\t%0,%1\n\tjgu\t%a\n" 2
stmt:   GTU2(reg,INDIRU2(reg))                   	"\tcmp\t%0,%1\n\tjgu\t%a\n" 2
stmt:   GTU2(reg,con)                           	"\tcmp\t%0,%1\n\tjgu\t%a\n" 2
stmt:   GTU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))  	"\tcmp\t%0,%1\n\tjgu\t%a\n" 1
stmt:   GTU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))  	"\tcmp\t%0,%1\n\tjgu\t%a\n" 1
stmt:   GTU2(CVUU2(reg8),con)                   	"\tcmp\t%0,%1\n\tjgu\t%a\n" 1
stmt:   GTU2(CVIU2(reg8),con)                   	"\tcmp\t%0,%1\n\tjgu\t%a\n" 1

stmt:	GTI4(reg32,reg32)						"\tCMP32\t(%0,%1)\n\tjg\t%a\n" 4
stmt:	GTI4(reg32,INDIRI4(addr))				"\tCMP32\t(%0,%1)\n\tjg\t%a\n" 4
stmt:	GTU4(reg32,reg32)						"\tCMP32\t(%0,%1)\n\tjgu\t%a\n" 4
stmt:	GTU4(reg32,INDIRU4(addr))				"\tCMP32\t(%0,%1)\n\tjgu\t%a\n" 4
stmt:	GTF4(regf,regf)							"\tCMP32\t(%0,%1)\n\tjg\t%a\n" 4
stmt:	GTF4(regf,INDIRF4(addr))				"\tCMP32\t(%0,%1)\n\tjg\t%a\n" 4
stmt:	GTF8(regf,regf)							"\tCMP64\t(%0,%1)\n\tjg\t%a\n" 8
stmt:	GTF8(regf,INDIRF8(addr))				"\tCMP64\t(%0,%1)\n\tjg\t%a\n" 8

stmt:   ARGI2(reg)          "# emit2\n" 2
stmt:   ARGU2(reg)          "# emit2\n" 2
stmt:   ARGP2(reg)	        "# emit2\n" 2
stmt:   ARGI4(reg32)        "# emit2\n" 4
stmt:   ARGU4(reg32)        "# emit2\n" 4
stmt:   ARGF4(regf)        	"# emit2\n" 4
stmt:   ARGF8(regf)        	"# emit2\n" 8

reg:    CALLI2(albl)        "\tcall\t%0\n" 2
reg:    CALLU2(albl)        "\tcall\t%0\n" 2
reg:    CALLP2(albl)        "\tcall\t%0\n" 2
stmt:	CALLV(albl)	        "\tcall\t%0\n" 2
reg32:  CALLI4(albl)        "# emit2\n" 4
reg32:  CALLU4(albl)        "# emit2\n" 4
regf:  	CALLF4(albl)        "# emit2\n" 4
regf:  	CALLF8(albl)        "\tlea\ta,%c\n\tcall\t%0\n" 8

stmt:   RETI2(reg)          "# return\n" 1
stmt:   RETU2(reg)          "# return\n" 1
stmt:   RETP2(reg)          "# return\n" 1
stmt:	RETV				"# return\n" 1
stmt:	RETI4(reg32)		"# return\n" 1
stmt:	RETU4(reg32)		"# return\n" 1
stmt:	RETF4(regf)			"# return\n" 1
stmt:	RETF8(regf)			"# return\n" 1

stmt:   JUMPV(albl)         "\tjmp\t%0\n" 1
stmt:   LABELV              "%a:\n"


%%

static void progbeg(int argc, char *argv[]) {

	int i;

    parseflags(argc,argv);

    // Reg symbols
    intreg[R_Y] = mkreg("y",R_Y,1,IREG);
    intreg[R_X] = mkreg("x",R_X,1,IREG);
    intreg[R_A] = mkreg("a",R_A,1,IREG);

    charreg[R_AH] = mkreg("ah", R_AH, 1, IREG);
    charreg[R_AL] = mkreg("al", R_AL, 1, IREG); 

	intreg[R_A]->x.regnode->mask |= 1<<R_AH;
    intreg[R_A]->x.regnode->mask |= 1<<R_AL;      
		
	for (i = R_L0; i <= R_L3; i++)
		longreg[i]  = mkreg("$L%d", i, 1, IREG);
    
	for (i = 0; i < 32; i++)
		floatreg[i]  = mkreg("$F%d", i, 1, FREG);

    // Set up sets
    intwldcrd = mkwildcard(intreg);
    charwldcrd = mkwildcard(charreg);
    floatwldcrd = mkwildcard(floatreg);
    longwldcrd = mkwildcard(longreg);

    // Set up integral registers for temporaries
    tmask[IREG] = ~(unsigned)0;
    // Set up registers for variables
    vmask[IREG] = 0;

    tmask[FREG] = ~(unsigned)0;
    vmask[FREG] = 0;
    
    print(";    BYTEC/16 assembly, generated by lcc 4.2\n\n");
	    	
    cseg = 0;
}

static Symbol rmap(int opk) {
    switch (optype(opk)) {
    case B:
    case P:
        return intwldcrd;
    case I:
    case U:
        if (opsize(opk) == 1) {
            return charwldcrd;
        }
        else if (opsize(opk) == 2) {
            return intwldcrd; 
        } else {
			used_longs = 1;
            return longwldcrd;
        }
    case F:
		used_floats = 1;
        return floatwldcrd;
    default:
        return 0;
    }
}

static void segment(int n) {
    if (n==cseg)
		return;
    if (n == CODE)
		print("\t.text\n");
    else if (n == LIT)
		print("\t.data\n");
    else if (n == DATA)
		print("\t.data\n");
    else if (n == BSS)
		print("\t.data\n");
    else
		print("\tERROR - invalid segment %d\n",n);
    cseg = n;
}

static void progend(void) {
}

static void target(Node p) {
    assert(p);
    switch (specific(p->op)) {

        case BOR+I:
        case BOR+U:
        case BAND+I:
        case BAND+U:
        case BXOR+I:
        case BXOR+U:
		case LSH+I:
		case LSH+U:
		case RSH+I:
		case RSH+U:
			if (opsize(p->op)<=2) {
				rtarget(p,0,intreg[R_A]);
				setreg(p,intreg[R_A]);
			}
            break;      

        case NEG+I:
			// we do sub X from zero (A) so target X
			rtarget(p,0,intreg[R_X]);
			setreg(p,intreg[R_A]);
			break;

        case BCOM+I:
        case BCOM+U:
			setreg(p,intreg[R_A]);
			break;

        case MUL+I:
        case MUL+U:
        case DIV+I:
        case DIV+U:
        case MOD+I:
        case MOD+U:        
			if (opsize(p->op)<=2) {
				rtarget(p,0,intreg[R_A]);
				rtarget(p,1,intreg[R_X]);
				setreg(p,intreg[R_A]);
			}
            break; 

        case LOAD+I:
        case LOAD+U:
            if (opsize(p->op)==1) {
                setreg(p,charreg[R_AL]);          
            }
            break;
            
        case CVI+I:
        case CVI+U:
        case CVU+I:
        case CVU+U:
            if (opsize(p->kids[0]->op)==1) {
                rtarget(p,0,charreg[R_AL]);
				setreg(p,intreg[R_A]);
            }
            break;

        case EQ+I:
        case NE+I:
        case LE+I:
        case LT+I:
        case GE+I:
        case GT+I:
        case EQ+U:
        case NE+U:
        case LE+U:
        case LT+U:
        case GE+U:
        case GT+U:
			if (opsize(p->op)<=2) {
				rtarget(p,0,intreg[R_A]);
			}
        break;

		case ASGN+B:
			// ASGNB(addr,INDIRB(addr))
			rtarget(p,0,intreg[R_X]);
			rtarget(p->kids[1],0,intreg[R_Y]);
		break;
		
		case ASGN+I:
		case ASGN+U:		
		case INDIR+I:
		case INDIR+U:
			if (opsize(p->op)==1) {
				// prevent A and AL/AH conflict when address in A
				// FIXME: how to target X or Y?
				if (specific(p->kids[0]->op)==ADD+P) {
					rtarget(p->kids[0],0,intreg[R_Y]);
				} else {
					rtarget(p,0,intreg[R_Y]);
				}
			}
		break;

        case RET+I:
        case RET+U:
        case RET+P:
			if (opsize(p->op)<=2) {
				rtarget(p,0,intreg[R_A]);
			}
			else if (opsize(p->op)==4) {
				rtarget(p,0,longreg[0]); // R_L0
			}
        break;

        case RET+F:
			rtarget(p,0,floatreg[0]); // R_F0
			if (opsize(p->op)==8) {
				ptr64 = 1;
			}
        break;

    }
}

static void clobber(Node p) {
    assert(p);
	switch(specific(p->op)) {
		
		case MUL+I:
		case MUL+U:
		case DIV+I:
		case DIV+U:
			if (opsize(p->op)==2) {
				// spill only X and Y for 16-bit mul/div (A is already setreg'ed)
				spill(1<<R_X|1<<R_Y,IREG,p);
			}			
			if (opsize(p->op)>2) {
				// spill all because 32/64-bit routines will do the job
				spill(1<<R_A|1<<R_X|1<<R_Y,IREG,p);
			}
		break;

		case MUL+F:
		case DIV+F:
		case ADD+I:
		case ADD+U:
		case ADD+F:
		case SUB+I:
		case SUB+U:
		case SUB+F:		
		case NEG+I:
		case NEG+U:
		case NEG+F:	
		case BAND+I:
		case BAND+U:
		case BAND+F:
		case BOR+I:
		case BOR+U:
		case BOR+F:	
		case BXOR+I:
		case BXOR+U:
		case BXOR+F:
		case BCOM+I:
		case BCOM+U:
			if (opsize(p->op)>2) {
				// spill all because 32/64-bit routines will do the job
				spill(1<<R_A|1<<R_X|1<<R_Y,IREG,p);
			}
		break;

		case CALL+I:
		case CALL+U:
		case CALL+F:
			if (opsize(p->op)==4) {
				// spill A (holds pointer to 64-bit temp for return value)
				spill(1<<R_A,IREG,p);
			}
			else if (opsize(p->op)==4) {
				// spill X and Y (will hold 32-bit return value)
				spill(1<<R_X|1<<R_Y,IREG,p);
			}		
		break;

		case CALL+B:
			// spill A (used as tmp reg in blkcpy)
			spill(1<<R_A,IREG,p);	
		break;
		
		default:
		break;
	}
}

int memop(Node p) {
        assert(p);
        assert(generic(p->op) == ASGN);
        assert(p->kids[0]);
        assert(p->kids[1]);
        if (generic(p->kids[1]->kids[0]->op) == INDIR
        && sametree(p->kids[0], p->kids[1]->kids[0]->kids[0]))
                return 3;
        else
                return LBURG_MAX;
}

int sametree(Node p, Node q) {
        return p == NULL && q == NULL
        || p && q && p->op == q->op && p->syms[0] == q->syms[0]
                && sametree(p->kids[0], q->kids[0])
                && sametree(p->kids[1], q->kids[1]);
}

static void emit2(Node p) {

    Symbol src, dst;
    int srnum, drnum;
    int lbl;
    
    switch (specific(p->op)) {

        case ADD+I:
        case ADD+U:
        case SUB+I:
        case SUB+U:
        case BAND+I:
        case BAND+U:
        case BOR+I:
        case BOR+U:
        case BXOR+I:
        case BXOR+U:
        case LSH+I:
        case LSH+U:
        case RSH+I:
        case RSH+U:
			if (generic(p->kids[0]->op)==CVI || generic(p->kids[0]->op)==CVU) {
				drnum = getregnum(p->kids[0]->kids[0]);
			} 
			else {
				drnum = getregnum(p->kids[0]);
			}
            dst = charreg[drnum];
			switch (generic(p->op)) {
				case ADD: print("\tadd\t%s,", dst->x.name); break;
				case SUB: print("\tsub\t%s,", dst->x.name); break;
				case BAND: print("\tand\t%s,", dst->x.name); break;
				case BOR: print("\tor\t%s,", dst->x.name); break;
				case BXOR: print("\txor\t%s,", dst->x.name); break;
			}
            if (generic(p->kids[1]->op)==CVI || generic(p->kids[1]->op)==CVU) {
                emitasm(p->kids[1]->kids[0]->kids[0], _addr_NT);
            }
            else {
                emitasm(p->kids[1], _con_NT);
            }
			/* this setreg is the real reason for using emit2 */
            setreg(p,charreg[drnum]);
            print("\t; emit2\n");
        break;

		case LOAD+I:
		case LOAD+U:
			assert(opsize(p->op)==1);
			drnum = getregnum(p->kids[0]);
			// prune movb al,a
			if (drnum!=R_A) {
				// safe to assume target is in al beacause we target so
				print("\tmovb\tal,%s\t;emit2\n",intreg[drnum]->x.name);
			}
		break;

        case ARG+I:
        case ARG+U:
        case ARG+P:
        case ARG+F:
			if (opsize(p->op)<=2) {
				print("\tst\t(sp:%d),%s\n",p->syms[2]->u.c.v.i,p->kids[0]->syms[2]->x.name); 
			}
			else if (opsize(p->op)==4) {
				print("\tCOPY32\t((sp:%d),%s)\n",p->syms[2]->u.c.v.i,p->kids[0]->syms[2]->x.name); 
			}
			else if (opsize(p->op)==8) {
				print("\tCOPY64\t((sp:%d),%s)\n",p->syms[2]->u.c.v.i,p->kids[0]->syms[2]->x.name); 
			}
		break;

        case CALL+I:
        case CALL+U:
        case CALL+F:
			if (opsize(p->op)==4) {
				print("\tcall\t%s\n",p->kids[0]->syms[0]->x.name);
				char *s = p->syms[2]->x.name;
				print("\tst\t%s+2),x\n",stringn(s,strlen(s)-1));
				print("\tst\t%s,y\n",s);
			}
		break;

        case RET+I:
        case RET+U:
        case RET+F:
			if (opsize(p->op)==4) {
				char *s = p->kids[0]->syms[2]->x.name;
				print("\tld\tx,%s+2)\n",stringn(s,strlen(s)-1));
				print("\tld\ty,%s\n",s);
			}
			else if (opsize(p->op)==8) {
				print("\tld\ta,(sp:%d+%d)\n",ptr64,framesize);
				print("\tCOPY64((a:0),%s)\n",floatreg[0]->x.name);
			}
		break;

		case ASGN+B: {
			// ASGNB(addr,INDIRB(addr))
			static int tmpregs[] = {R_A};
			dalign = salign = p->syms[1]->u.c.v.i;
            blkcopy(getregnum(p->x.kids[0]), 0,
                    getregnum(p->x.kids[1]), 0,
                    p->syms[0]->u.c.v.i, tmpregs);
		break;
		}

    }
}

static void doarg(Node p) {
    static int argno;
    if (argoffset==0) {
		argno = 0;
    }
    p->x.argno=argno++;
    p->syms[2] = intconst(mkactual(2,p->syms[0]->u.c.v.i));
}

static void blkloop(int dreg, int doff, int sreg, int soff, int size, int tmps[]) {
        Symbol s, d, t;
		s = intreg[sreg];
		d = intreg[dreg];
		t = intreg[tmps[0]];
        int lab = genlabel(1);

        print("\tpush\t%s\n", d->x.name);
        print("\tadd\t%s,%d\n", s->x.name, size&~7);
        print("\tadd\t%s,%d\n", d->x.name, size&~7);
        blkcopy(dreg, doff, sreg, soff, size&7, tmps);      
        
        print("L%d:\n", lab);
        print("\tsub\t%s,%d\n", s->x.name, 8);
        print("\tsub\t%s,%d\n", d->x.name, 8);
        blkcopy(dreg, doff, sreg, soff, 8, tmps);
        print("\tmov\t%s,%s\n", t->x.name, d->x.name);
        print("\tcmp\t%s,(sp:0)\n", t->x.name);
        print("\tjne\tL%d\n", lab);
        print("\tpop\t%s\n", d->x.name);
}

static void blkfetch(int size, int off, int reg, int tmp) {
        Symbol r, t;
		r = intreg[reg];
		t = intreg[tmp];
        
        assert(size == 1 || size == 2);
        if (size == 1) {
				t = charreg[R_AL];
                print("\tld\t%s,(%s:%d)\n",  t->x.name, r->x.name, off);
        } else {
                print("\tld\t%s,(%s:%d)\n",  t->x.name, r->x.name, off);
        }
}

static void blkstore(int size, int off, int reg, int tmp) {
        Symbol r, t;
		r = intreg[reg];
		t = intreg[tmp];
        
        assert(size == 1 || size == 2);
        if (size == 1) {
				t = charreg[R_AL];
                print("\tst\t(%s:%d),%s\n",  r->x.name, off, t->x.name);
        } else {
                print("\tst\t(%s:%d),%s\n",  r->x.name, off, t->x.name);
        }
}

static void local(Symbol p) {
    if (askregvar(p,(*IR->x.rmap)(ttob(p->type)))==0) {
        mkauto(p);
    }
}

static void function(Symbol f, Symbol caller[], Symbol callee[], int n) {

	ptr64 = used_longs = used_floats = 0;

    print("%s:\n",f->x.name);

    int i;
    usedmask[0] = usedmask[1] = 0;
    freemask[0] = freemask[1] = ~(unsigned)0;
    offset = 0;
    for (i = 0; callee[i]; i++) {
            Symbol p = callee[i];
            Symbol q = caller[i];
            assert(q);
            p->x.offset = q->x.offset = offset;
            p->x.name = q->x.name = stringf("%d", p->x.offset);
            p->sclass = q->sclass = AUTO;
            offset += q->type->size;
    }
    assert(caller[i] == 0);
    
    offset = maxoffset = maxargoffset = 0;
    gencode(caller, callee);

    // Allocate frame space for pseudo regs
    if (used_longs) {
        for (i=R_L0;i<=R_L3;i++) {
	    if (usedmask[0] & (1<<i)) {
	        maxoffset+=4;
	        longreg[i]->x.offset = -maxoffset;
	    }
        }
    }
    if (used_floats) {
        for (i=0;i<32;i++) {
	    if (usedmask[1] & (1<<i)) {
	        maxoffset+=8;
	        floatreg[i]->x.offset = -maxoffset;
	    }
        }
    }
    if (ptr64) {
		maxoffset+=2;
		ptr64 = -maxoffset;
	}
    
    framesize = maxoffset + maxargoffset;
    
    // Rewrite names of pseudo regs
    if (used_longs) {
        for (i=R_L0;i<=R_L3;i++) {
	    if (usedmask[0] & (1<<i)) {
	        longreg[i]->x.name = stringf("(sp:%d)",longreg[i]->x.offset+framesize);
			printf("; equating L%d to (sp:%d)\n",i,longreg[i]->x.offset+framesize);
	    }
        }
    }
    if (used_floats) {
        for (i=0;i<32;i++) {
	    if (usedmask[1] & (1<<i)) {
	        floatreg[i]->x.name = stringf("(sp:%d)",floatreg[i]->x.offset+framesize);
			printf("; equating F%d to (sp:%d)\n",i,floatreg[i]->x.offset+framesize);
	    }
        }
    }
    
    if (framesize > 0) {
        print("\tadd\tsp,-%d\n",framesize);
    }
    
    if (ptr64) {
		print("\tst\t(sp:%d+%d),a\n",ptr64,framesize);
    }
    
    emitcode();
    
    if (framesize > 0) {
        print("\tadd\tsp,%d\n",framesize);
    }
    print("\tret\n\n");
}

static void defsymbol(Symbol p) {
        if (p->scope >= LOCAL && p->sclass == STATIC)
                p->x.name = stringf("L%d", genlabel(1));
        else if (p->generated)
                p->x.name = stringf("L%s", p->name);
        else if (p->scope == GLOBAL || p->sclass == EXTERN)
                p->x.name = stringf("_%s", p->name);
        else if (p->scope == CONSTANTS
        && (isint(p->type) || isptr(p->type))
        && p->name[0] == '0' && p->name[1] == 'x')
                /*p->x.name = stringf("0%sH", &p->name[2]);*/
                p->x.name = p->name;
        else
                p->x.name = p->name;
}

static void address(Symbol q, Symbol p, long n) {
        if (p->scope == GLOBAL
        || p->sclass == STATIC || p->sclass == EXTERN)
                q->x.name = stringf("%s%s%D",
                        p->x.name, n >= 0 ? "+" : "", n);
        else {
                assert(n <= INT_MAX && n >= INT_MIN);
                q->x.offset = p->x.offset + n;
                q->x.name = stringd(q->x.offset);
        }
}

static void defconst(int suffix, int size, Value v) {
		
		char s0[5];
		char s1[5];
		char s2[5];
		char s3[5];
	
        if (suffix == I && size == 1)
                print("\tdb\t0x%x\n", v.i&0xff);
        else if (suffix == I && size == 2) {
                sprintf(s0,"%4x",v.i&0xffff);
                print("\tdw\t0x%s\n", s0);
        }
        else if (suffix == I && size == 4) {
                sprintf(s0,"%04x",(v.i>>16)&0xffff);
                sprintf(s1,"%04x",v.i&0xffff);          
                print("\tdw\t0x%s,0x%s\n", s0, s1);
        }
        else if (suffix == U && size == 1)
                print("\tdb\t0x%x\n", v.u&0xff);
        else if (suffix == U && size == 2) {
				sprintf(s0,"%04x",v.u&0xffff);  
                print("\tdw\t0x%s\n", s0);
        }
        else if (suffix == U && size == 4) {
                sprintf(s0,"%04x",(v.u>>16)&0xffff);
                sprintf(s1,"%04x",v.u&0xffff);          
                print("\tdw\t0x%s,0x%s\n", s0, s1);
        }
        else if (suffix == P && size == 2) {
                sprintf(s0,"%04x",((unsigned)v.p)&0xffff);
                print("\tdw\t0x%s\n", s0);
        }
        else if (suffix == F && size == 4) {
				float d = (float)v.d;
                unsigned short *f = (unsigned short *)&d;
                sprintf(s0,"%04x",f[0]);
                sprintf(s1,"%04x",f[1]);                
                print("\tdw\t0x%s,0x%s\n", s1, s0);
        }
        else if (suffix == F && size == 8) {
                unsigned long *f = (unsigned long *)&v.d;
                sprintf(s0,"%04x",f[0]);
                sprintf(s1,"%04x",f[1]);
                sprintf(s2,"%04x",f[2]);
                sprintf(s3,"%04x",f[3]);
                print("\tdw\t0x%s,0x%s,0x%s,0x%s\n", s3, s2, s1, s0);
        }
        else assert(0);
}

static void defaddress(Symbol p) {
	print("\tdw\t%s\n", p->x.name);
}

static void defstring(int n, char *str) {
	char *s;
	char s0[3];
	for (s = str; s < str + n; s++) {
        sprintf(s0,"%02x",((*s)&0377) & 0xff);
		print("\tdb\t0x%s\n", s0);
	}
         
}

static void export(Symbol p) {
    print("\t.global\t%s\n", p->x.name);
}

static void import(Symbol p) {
    print("\t.extern\t%s\n", p->x.name);
}

static void global(Symbol p) {
	print("%s:\n", p->x.name);
}

static void space(int n) {
	print("\tdb\t0x00:%d\n", n);
}


Interface bytec16IR = {
        1, 1, 0,  /* char */
        2, 1, 0,  /* short */
        2, 1, 0,  /* int */
        4, 1, 1,  /* long */
        4, 1, 1,  /* long long */
        4, 1, 1,  /* float */
        8, 1, 1,  /* double */
        8, 1, 1,  /* long double */
        2, 1, 0,  /* T * */
        0, 1, 0,  /* struct */
        0,        /* little_endian */
        1,        /* mulops_calls */
        0,        /* wants_callb */
        0,        /* wants_argb */
        1,        /* left_to_right */
        0,        /* wants_dag */
        0,        /* unsigned_char */
        address,
        blockbeg,
        blockend,
        defaddress,
        defconst,
        defstring,
        defsymbol,
        emit,
        export,
        function,
        gen,
        global,
        import,
        local,
        progbeg,
        progend,
        segment,
        space,
        0, 0, 0, 0, 0, 0, 0,
        {2 /* max_unaligned_load */, rmap,
            blkfetch, blkstore, blkloop,
            _label,
            _rule,
            _nts,
            _kids,
            _string,
            _templates,
            _isinstruction,
            _ntname,
            emit2,
            doarg,
            target,
            clobber,
}
};
