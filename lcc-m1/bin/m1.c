
// Register declration enumeration here
enum { R_L0=0, R_L1=1, R_L2=2, R_L3=3, R_A=5, R_B=4 };
enum { R_F0=0, R_F1=1, R_F2=2, R_F3=3 };

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
static int isfptr(Node,int,int);

// Local vars here

static Symbol longreg[32];
static Symbol intreg[32];
static Symbol fltreg[32];

static Symbol longwldcrd;
static Symbol intwldcrd;
static Symbol fltwldcrd;

static int current_seg;

/*
generated at Sun Dec 20 12:48:32 2015
by $Id: lburg.c,v 2.10 2002/03/08 18:45:21 drh Exp $
*/
static void _kids(NODEPTR_TYPE, int, NODEPTR_TYPE[]);
static void _label(NODEPTR_TYPE);
static int _rule(void*, int);

#define _stmt_NT 1
#define _reg8_NT 2
#define _reg_NT 3
#define _con_NT 4
#define _c0_NT 5
#define _c1_NT 6
#define _c2_NT 7
#define _con1_NT 8
#define _con2_NT 9
#define _con4_NT 10
#define _addr_NT 11
#define _ar_NT 12

static char *_ntname[] = {
	0,
	"stmt",
	"reg8",
	"reg",
	"con",
	"c0",
	"c1",
	"c2",
	"con1",
	"con2",
	"con4",
	"addr",
	"ar",
	0
};

struct _state {
	short cost[13];
	struct {
		unsigned int _stmt:8;
		unsigned int _reg8:6;
		unsigned int _reg:8;
		unsigned int _con:3;
		unsigned int _c0:1;
		unsigned int _c1:1;
		unsigned int _c2:1;
		unsigned int _con1:2;
		unsigned int _con2:2;
		unsigned int _con4:2;
		unsigned int _addr:3;
		unsigned int _ar:2;
	} rule;
};

static short _nts_0[] = { _reg8_NT, 0 };
static short _nts_1[] = { _reg_NT, 0 };
static short _nts_2[] = { 0 };
static short _nts_3[] = { _con_NT, 0 };
static short _nts_4[] = { _con1_NT, 0 };
static short _nts_5[] = { _con2_NT, 0 };
static short _nts_6[] = { _con4_NT, 0 };
static short _nts_7[] = { _c0_NT, 0 };
static short _nts_8[] = { _c1_NT, 0 };
static short _nts_9[] = { _c2_NT, 0 };
static short _nts_10[] = { _reg_NT, _reg_NT, 0 };
static short _nts_11[] = { _reg_NT, _con_NT, 0 };
static short _nts_12[] = { _reg_NT, _addr_NT, 0 };
static short _nts_13[] = { _reg8_NT, _reg8_NT, 0 };
static short _nts_14[] = { _reg8_NT, _con_NT, 0 };
static short _nts_15[] = { _reg8_NT, _addr_NT, 0 };
static short _nts_16[] = { _addr_NT, 0 };
static short _nts_17[] = { _reg_NT, _c1_NT, 0 };
static short _nts_18[] = { _reg_NT, _c2_NT, 0 };
static short _nts_19[] = { _con_NT, _reg_NT, 0 };
static short _nts_20[] = { _addr_NT, _reg_NT, 0 };
static short _nts_21[] = { _con_NT, _reg8_NT, 0 };
static short _nts_22[] = { _addr_NT, _reg8_NT, 0 };
static short _nts_23[] = { _ar_NT, 0 };
static short _nts_24[] = { _ar_NT, _reg_NT, 0 };
static short _nts_25[] = { _reg_NT, _reg8_NT, 0 };
static short _nts_26[] = { _addr_NT, _con4_NT, 0 };
static short _nts_27[] = { _reg_NT, _con4_NT, 0 };

static short *_nts[] = {
	0,	/* 0 */
	_nts_0,	/* 1 */
	_nts_0,	/* 2 */
	_nts_1,	/* 3 */
	_nts_1,	/* 4 */
	_nts_1,	/* 5 */
	_nts_1,	/* 6 */
	_nts_1,	/* 7 */
	_nts_1,	/* 8 */
	_nts_2,	/* 9 */
	_nts_2,	/* 10 */
	_nts_2,	/* 11 */
	_nts_2,	/* 12 */
	_nts_2,	/* 13 */
	_nts_2,	/* 14 */
	_nts_2,	/* 15 */
	_nts_2,	/* 16 */
	_nts_0,	/* 17 */
	_nts_0,	/* 18 */
	_nts_1,	/* 19 */
	_nts_1,	/* 20 */
	_nts_1,	/* 21 */
	_nts_1,	/* 22 */
	_nts_1,	/* 23 */
	_nts_1,	/* 24 */
	_nts_1,	/* 25 */
	_nts_1,	/* 26 */
	_nts_1,	/* 27 */
	_nts_1,	/* 28 */
	_nts_0,	/* 29 */
	_nts_0,	/* 30 */
	_nts_1,	/* 31 */
	_nts_1,	/* 32 */
	_nts_1,	/* 33 */
	_nts_0,	/* 34 */
	_nts_1,	/* 35 */
	_nts_1,	/* 36 */
	_nts_1,	/* 37 */
	_nts_1,	/* 38 */
	_nts_0,	/* 39 */
	_nts_1,	/* 40 */
	_nts_1,	/* 41 */
	_nts_1,	/* 42 */
	_nts_1,	/* 43 */
	_nts_1,	/* 44 */
	_nts_0,	/* 45 */
	_nts_1,	/* 46 */
	_nts_3,	/* 47 */
	_nts_3,	/* 48 */
	_nts_2,	/* 49 */
	_nts_2,	/* 50 */
	_nts_2,	/* 51 */
	_nts_2,	/* 52 */
	_nts_2,	/* 53 */
	_nts_2,	/* 54 */
	_nts_2,	/* 55 */
	_nts_2,	/* 56 */
	_nts_2,	/* 57 */
	_nts_2,	/* 58 */
	_nts_4,	/* 59 */
	_nts_5,	/* 60 */
	_nts_6,	/* 61 */
	_nts_7,	/* 62 */
	_nts_8,	/* 63 */
	_nts_9,	/* 64 */
	_nts_4,	/* 65 */
	_nts_5,	/* 66 */
	_nts_6,	/* 67 */
	_nts_10,	/* 68 */
	_nts_11,	/* 69 */
	_nts_12,	/* 70 */
	_nts_10,	/* 71 */
	_nts_11,	/* 72 */
	_nts_12,	/* 73 */
	_nts_10,	/* 74 */
	_nts_11,	/* 75 */
	_nts_12,	/* 76 */
	_nts_13,	/* 77 */
	_nts_14,	/* 78 */
	_nts_15,	/* 79 */
	_nts_13,	/* 80 */
	_nts_14,	/* 81 */
	_nts_15,	/* 82 */
	_nts_10,	/* 83 */
	_nts_12,	/* 84 */
	_nts_10,	/* 85 */
	_nts_12,	/* 86 */
	_nts_10,	/* 87 */
	_nts_12,	/* 88 */
	_nts_10,	/* 89 */
	_nts_11,	/* 90 */
	_nts_12,	/* 91 */
	_nts_10,	/* 92 */
	_nts_11,	/* 93 */
	_nts_12,	/* 94 */
	_nts_10,	/* 95 */
	_nts_11,	/* 96 */
	_nts_12,	/* 97 */
	_nts_13,	/* 98 */
	_nts_14,	/* 99 */
	_nts_15,	/* 100 */
	_nts_13,	/* 101 */
	_nts_14,	/* 102 */
	_nts_15,	/* 103 */
	_nts_10,	/* 104 */
	_nts_12,	/* 105 */
	_nts_10,	/* 106 */
	_nts_12,	/* 107 */
	_nts_10,	/* 108 */
	_nts_12,	/* 109 */
	_nts_10,	/* 110 */
	_nts_11,	/* 111 */
	_nts_12,	/* 112 */
	_nts_10,	/* 113 */
	_nts_11,	/* 114 */
	_nts_12,	/* 115 */
	_nts_13,	/* 116 */
	_nts_14,	/* 117 */
	_nts_15,	/* 118 */
	_nts_13,	/* 119 */
	_nts_14,	/* 120 */
	_nts_15,	/* 121 */
	_nts_10,	/* 122 */
	_nts_12,	/* 123 */
	_nts_10,	/* 124 */
	_nts_12,	/* 125 */
	_nts_10,	/* 126 */
	_nts_11,	/* 127 */
	_nts_12,	/* 128 */
	_nts_10,	/* 129 */
	_nts_11,	/* 130 */
	_nts_12,	/* 131 */
	_nts_13,	/* 132 */
	_nts_14,	/* 133 */
	_nts_15,	/* 134 */
	_nts_13,	/* 135 */
	_nts_14,	/* 136 */
	_nts_15,	/* 137 */
	_nts_10,	/* 138 */
	_nts_12,	/* 139 */
	_nts_10,	/* 140 */
	_nts_12,	/* 141 */
	_nts_10,	/* 142 */
	_nts_10,	/* 143 */
	_nts_10,	/* 144 */
	_nts_12,	/* 145 */
	_nts_10,	/* 146 */
	_nts_12,	/* 147 */
	_nts_10,	/* 148 */
	_nts_10,	/* 149 */
	_nts_10,	/* 150 */
	_nts_12,	/* 151 */
	_nts_10,	/* 152 */
	_nts_12,	/* 153 */
	_nts_10,	/* 154 */
	_nts_12,	/* 155 */
	_nts_10,	/* 156 */
	_nts_10,	/* 157 */
	_nts_10,	/* 158 */
	_nts_12,	/* 159 */
	_nts_10,	/* 160 */
	_nts_12,	/* 161 */
	_nts_10,	/* 162 */
	_nts_12,	/* 163 */
	_nts_10,	/* 164 */
	_nts_10,	/* 165 */
	_nts_10,	/* 166 */
	_nts_12,	/* 167 */
	_nts_10,	/* 168 */
	_nts_12,	/* 169 */
	_nts_1,	/* 170 */
	_nts_1,	/* 171 */
	_nts_16,	/* 172 */
	_nts_1,	/* 173 */
	_nts_16,	/* 174 */
	_nts_17,	/* 175 */
	_nts_18,	/* 176 */
	_nts_11,	/* 177 */
	_nts_10,	/* 178 */
	_nts_17,	/* 179 */
	_nts_18,	/* 180 */
	_nts_11,	/* 181 */
	_nts_10,	/* 182 */
	_nts_10,	/* 183 */
	_nts_12,	/* 184 */
	_nts_10,	/* 185 */
	_nts_12,	/* 186 */
	_nts_17,	/* 187 */
	_nts_18,	/* 188 */
	_nts_11,	/* 189 */
	_nts_10,	/* 190 */
	_nts_17,	/* 191 */
	_nts_18,	/* 192 */
	_nts_11,	/* 193 */
	_nts_10,	/* 194 */
	_nts_10,	/* 195 */
	_nts_12,	/* 196 */
	_nts_10,	/* 197 */
	_nts_12,	/* 198 */
	_nts_10,	/* 199 */
	_nts_11,	/* 200 */
	_nts_12,	/* 201 */
	_nts_10,	/* 202 */
	_nts_11,	/* 203 */
	_nts_12,	/* 204 */
	_nts_13,	/* 205 */
	_nts_14,	/* 206 */
	_nts_15,	/* 207 */
	_nts_13,	/* 208 */
	_nts_14,	/* 209 */
	_nts_15,	/* 210 */
	_nts_10,	/* 211 */
	_nts_12,	/* 212 */
	_nts_10,	/* 213 */
	_nts_12,	/* 214 */
	_nts_10,	/* 215 */
	_nts_12,	/* 216 */
	_nts_10,	/* 217 */
	_nts_11,	/* 218 */
	_nts_12,	/* 219 */
	_nts_10,	/* 220 */
	_nts_11,	/* 221 */
	_nts_12,	/* 222 */
	_nts_13,	/* 223 */
	_nts_14,	/* 224 */
	_nts_15,	/* 225 */
	_nts_13,	/* 226 */
	_nts_14,	/* 227 */
	_nts_15,	/* 228 */
	_nts_10,	/* 229 */
	_nts_12,	/* 230 */
	_nts_10,	/* 231 */
	_nts_12,	/* 232 */
	_nts_10,	/* 233 */
	_nts_12,	/* 234 */
	_nts_10,	/* 235 */
	_nts_11,	/* 236 */
	_nts_12,	/* 237 */
	_nts_10,	/* 238 */
	_nts_11,	/* 239 */
	_nts_12,	/* 240 */
	_nts_13,	/* 241 */
	_nts_14,	/* 242 */
	_nts_15,	/* 243 */
	_nts_13,	/* 244 */
	_nts_14,	/* 245 */
	_nts_15,	/* 246 */
	_nts_10,	/* 247 */
	_nts_12,	/* 248 */
	_nts_10,	/* 249 */
	_nts_12,	/* 250 */
	_nts_10,	/* 251 */
	_nts_12,	/* 252 */
	_nts_10,	/* 253 */
	_nts_11,	/* 254 */
	_nts_12,	/* 255 */
	_nts_10,	/* 256 */
	_nts_11,	/* 257 */
	_nts_12,	/* 258 */
	_nts_13,	/* 259 */
	_nts_14,	/* 260 */
	_nts_15,	/* 261 */
	_nts_13,	/* 262 */
	_nts_14,	/* 263 */
	_nts_15,	/* 264 */
	_nts_10,	/* 265 */
	_nts_12,	/* 266 */
	_nts_10,	/* 267 */
	_nts_12,	/* 268 */
	_nts_10,	/* 269 */
	_nts_12,	/* 270 */
	_nts_10,	/* 271 */
	_nts_19,	/* 272 */
	_nts_20,	/* 273 */
	_nts_10,	/* 274 */
	_nts_19,	/* 275 */
	_nts_20,	/* 276 */
	_nts_13,	/* 277 */
	_nts_21,	/* 278 */
	_nts_22,	/* 279 */
	_nts_13,	/* 280 */
	_nts_21,	/* 281 */
	_nts_22,	/* 282 */
	_nts_10,	/* 283 */
	_nts_20,	/* 284 */
	_nts_10,	/* 285 */
	_nts_20,	/* 286 */
	_nts_10,	/* 287 */
	_nts_20,	/* 288 */
	_nts_10,	/* 289 */
	_nts_19,	/* 290 */
	_nts_20,	/* 291 */
	_nts_10,	/* 292 */
	_nts_19,	/* 293 */
	_nts_20,	/* 294 */
	_nts_13,	/* 295 */
	_nts_21,	/* 296 */
	_nts_22,	/* 297 */
	_nts_13,	/* 298 */
	_nts_21,	/* 299 */
	_nts_22,	/* 300 */
	_nts_10,	/* 301 */
	_nts_20,	/* 302 */
	_nts_10,	/* 303 */
	_nts_20,	/* 304 */
	_nts_10,	/* 305 */
	_nts_20,	/* 306 */
	_nts_2,	/* 307 */
	_nts_2,	/* 308 */
	_nts_2,	/* 309 */
	_nts_2,	/* 310 */
	_nts_1,	/* 311 */
	_nts_2,	/* 312 */
	_nts_2,	/* 313 */
	_nts_2,	/* 314 */
	_nts_2,	/* 315 */
	_nts_2,	/* 316 */
	_nts_1,	/* 317 */
	_nts_16,	/* 318 */
	_nts_1,	/* 319 */
	_nts_16,	/* 320 */
	_nts_1,	/* 321 */
	_nts_16,	/* 322 */
	_nts_1,	/* 323 */
	_nts_16,	/* 324 */
	_nts_1,	/* 325 */
	_nts_16,	/* 326 */
	_nts_1,	/* 327 */
	_nts_16,	/* 328 */
	_nts_1,	/* 329 */
	_nts_16,	/* 330 */
	_nts_1,	/* 331 */
	_nts_16,	/* 332 */
	_nts_1,	/* 333 */
	_nts_2,	/* 334 */
	_nts_23,	/* 335 */
	_nts_23,	/* 336 */
	_nts_23,	/* 337 */
	_nts_23,	/* 338 */
	_nts_23,	/* 339 */
	_nts_23,	/* 340 */
	_nts_23,	/* 341 */
	_nts_24,	/* 342 */
	_nts_1,	/* 343 */
	_nts_1,	/* 344 */
	_nts_1,	/* 345 */
	_nts_1,	/* 346 */
	_nts_1,	/* 347 */
	_nts_1,	/* 348 */
	_nts_1,	/* 349 */
	_nts_1,	/* 350 */
	_nts_1,	/* 351 */
	_nts_1,	/* 352 */
	_nts_1,	/* 353 */
	_nts_1,	/* 354 */
	_nts_1,	/* 355 */
	_nts_23,	/* 356 */
	_nts_25,	/* 357 */
	_nts_22,	/* 358 */
	_nts_25,	/* 359 */
	_nts_22,	/* 360 */
	_nts_10,	/* 361 */
	_nts_20,	/* 362 */
	_nts_10,	/* 363 */
	_nts_20,	/* 364 */
	_nts_10,	/* 365 */
	_nts_20,	/* 366 */
	_nts_10,	/* 367 */
	_nts_20,	/* 368 */
	_nts_26,	/* 369 */
	_nts_27,	/* 370 */
	_nts_10,	/* 371 */
	_nts_20,	/* 372 */
	_nts_26,	/* 373 */
	_nts_27,	/* 374 */
	_nts_10,	/* 375 */
	_nts_20,	/* 376 */
	_nts_26,	/* 377 */
	_nts_27,	/* 378 */
	_nts_10,	/* 379 */
	_nts_1,	/* 380 */
};

static char *_templates[] = {
/* 0 */	0,
/* 1 */	"\tcopy\t%c,%0\n",	/* reg8: LOADI1(reg8) */
/* 2 */	"\tcopy\t%c,%0\n",	/* reg8: LOADU1(reg8) */
/* 3 */	"\tcopy\t%c,%0\n",	/* reg: LOADI2(reg) */
/* 4 */	"\tcopy\t%c,%0\n",	/* reg: LOADU2(reg) */
/* 5 */	"\tcopy\t%c,%0\n",	/* reg: LOADP2(reg) */
/* 6 */	"\tCOPY32\t%c,%0\n",	/* reg: LOADI4(reg) */
/* 7 */	"\tCOPY32\t%c,%0\n",	/* reg: LOADU4(reg) */
/* 8 */	"\tCOPY32\t%c,%0\n",	/* reg: LOADF4(reg) */
/* 9 */	"# read register\n",	/* reg8: INDIRI1(VREGP) */
/* 10 */	"# read register\n",	/* reg8: INDIRU1(VREGP) */
/* 11 */	"# read register\n",	/* reg: INDIRI2(VREGP) */
/* 12 */	"# read register\n",	/* reg: INDIRU2(VREGP) */
/* 13 */	"# read register\n",	/* reg: INDIRI4(VREGP) */
/* 14 */	"# read register\n",	/* reg: INDIRU4(VREGP) */
/* 15 */	"# read register\n",	/* reg: INDIRP2(VREGP) */
/* 16 */	"# read register\n",	/* reg: INDIRF4(VREGP) */
/* 17 */	"# write register\n",	/* stmt: ASGNI1(VREGP,reg8) */
/* 18 */	"# write register\n",	/* stmt: ASGNU1(VREGP,reg8) */
/* 19 */	"# write register\n",	/* stmt: ASGNI2(VREGP,reg) */
/* 20 */	"# write register\n",	/* stmt: ASGNU2(VREGP,reg) */
/* 21 */	"# write register\n",	/* stmt: ASGNI4(VREGP,reg) */
/* 22 */	"# write register\n",	/* stmt: ASGNU4(VREGP,reg) */
/* 23 */	"# write register\n",	/* stmt: ASGNP2(VREGP,reg) */
/* 24 */	"# write register\n",	/* stmt: ASGNF4(VREGP,reg) */
/* 25 */	"\tCOPY32\t%c,%1\n",	/* reg: CVFF4(reg) */
/* 26 */	"\tCVTFI2\t%c,%0\n",	/* reg: CVFI2(reg) */
/* 27 */	"\tCVTFI4\t%c,%0\n",	/* reg: CVFI4(reg) */
/* 28 */	"\tCVTIF4\t%c,%0\n",	/* reg: CVIF4(reg) */
/* 29 */	"?\tcopy\t%c,%0\n\tsex\t%c\n",	/* reg: CVII2(reg8) */
/* 30 */	"%0",	/* reg8: CVII2(reg8) */
/* 31 */	"\tCVTII4\t%c,%0\n",	/* reg: CVII4(reg) */
/* 32 */	"\tcopy\t%c,%0\n",	/* reg8: CVIU1(reg) */
/* 33 */	"?\tcopy\t%c,%0\n\tand.16\t%c,0xff\n",	/* reg: CVIU2(reg) */
/* 34 */	"?\tcopy\t%c,%0\n\tand.16\t%c,0xff\n",	/* reg: CVIU2(reg8) */
/* 35 */	"\tCVTII4\t%c,%0\n",	/* reg: CVII4(reg) */
/* 36 */	"\tcopy\t%c,%0\n",	/* reg: CVPU2(reg) */
/* 37 */	"\tcopy\t%c,%0\n",	/* reg8: CVUI1(reg) */
/* 38 */	"?\tcopy\t%c,%0\n\tand.16\t%c,0xff\n",	/* reg: CVUI2(reg) */
/* 39 */	"?\tcopy\t%c,%0\n\tand.16\t%c,0xff\n",	/* reg: CVUI2(reg8) */
/* 40 */	"\tCVTUI4\t%c,%0\n",	/* reg: CVUI4(reg) */
/* 41 */	"\tcopy\t%c,%0\n",	/* reg: CVUP2(reg) */
/* 42 */	"\tcopy\t%c,%0\n",	/* reg: CVUU1(reg) */
/* 43 */	"\tcopy\t%c,%0\n",	/* reg8: CVUU1(reg) */
/* 44 */	"?\tcopy\t%c,%0\n\tand.16\t%c,0xff\n",	/* reg: CVUU2(reg) */
/* 45 */	"%0",	/* reg8: CVUU2(reg8) */
/* 46 */	"\tCVTUU4\t%c,%0\n",	/* reg: CVUU4(reg) */
/* 47 */	"\tld.16\t%c,%0\n",	/* reg: con */
/* 48 */	"\tld.8\t%c,%0\n",	/* reg8: con */
/* 49 */	"0",	/* c0: CNSTI2 */
/* 50 */	"1",	/* c1: CNSTI2 */
/* 51 */	"2",	/* c2: CNSTI2 */
/* 52 */	"%a",	/* con1: CNSTI1 */
/* 53 */	"%a",	/* con1: CNSTU1 */
/* 54 */	"%a",	/* con2: CNSTI2 */
/* 55 */	"%a",	/* con2: CNSTU2 */
/* 56 */	"%a",	/* con4: CNSTI4 */
/* 57 */	"%a",	/* con4: CNSTU4 */
/* 58 */	"%a",	/* con4: CNSTP2 */
/* 59 */	"%0",	/* con: con1 */
/* 60 */	"%0",	/* con: con2 */
/* 61 */	"%0",	/* con: con4 */
/* 62 */	"%0",	/* con: c0 */
/* 63 */	"%0",	/* con: c1 */
/* 64 */	"%0",	/* con: c2 */
/* 65 */	"\tld.8\t%c,%0\n",	/* reg: con1 */
/* 66 */	"\tld.16\t%c,%0\n",	/* reg: con2 */
/* 67 */	"\tCON32\t%c,%0\n",	/* reg: con4 */
/* 68 */	"?\tcopy\t%c,%0\n\tadd.16\t%c,%1\n",	/* reg: ADDI2(reg,reg) */
/* 69 */	"?\tcopy\t%c,%0\n\tadd.16\t%c,%1\n",	/* reg: ADDI2(reg,con) */
/* 70 */	"?\tcopy\t%c,%0\n\tadd.16\t%c,%1\n",	/* reg: ADDI2(reg,INDIRI2(addr)) */
/* 71 */	"?\tcopy\t%c,%0\n\tadd.16\t%c,%1\n",	/* reg: ADDU2(reg,reg) */
/* 72 */	"?\tcopy\t%c,%0\n\tadd.16\t%c,%1\n",	/* reg: ADDU2(reg,con) */
/* 73 */	"?\tcopy\t%c,%0\n\tadd.16\t%c,%1\n",	/* reg: ADDU2(reg,INDIRI2(addr)) */
/* 74 */	"?\tcopy\t%c,%0\n\tadd.16\t%c,%1\n",	/* reg: ADDP2(reg,reg) */
/* 75 */	"?\tcopy\t%c,%0\n\tadd.16\t%c,%1\n",	/* reg: ADDP2(reg,con) */
/* 76 */	"?\tcopy\t%c,%0\n\tadd.16\t%c,%1\n",	/* reg: ADDP2(reg,INDIRI2(addr)) */
/* 77 */	"?\tcopy\t%c,%0\n\tadd.8\t%c,%1\n",	/* reg8: ADDI2(reg8,reg8) */
/* 78 */	"?\tcopy\t%c,%0\n\tadd.8\t%c,%1\n",	/* reg8: ADDI2(reg8,con) */
/* 79 */	"?\tcopy\t%c,%0\n\tadd.8\t%c,%1\n",	/* reg8: ADDI2(reg8,CVII2(INDIRI1(addr))) */
/* 80 */	"?\tcopy\t%c,%0\n\tadd.8\t%c,%1\n",	/* reg8: ADDU2(reg8,reg8) */
/* 81 */	"?\tcopy\t%c,%0\n\tadd.8\t%c,%1\n",	/* reg8: ADDU2(reg8,con) */
/* 82 */	"?\tcopy\t%c,%0\n\tadd.8\t%c,%1\n",	/* reg8: ADDU2(reg8,CVUU2(INDIRU1(addr))) */
/* 83 */	"?\tTCOPY\t%c,%0\n\tADD32\t%c,%1\n",	/* reg: ADDI4(reg,reg) */
/* 84 */	"?\tTCOPY\t%c,%0\n\tADD32\t%c,%1\n",	/* reg: ADDI4(reg,INDIRI4(addr)) */
/* 85 */	"?\tTCOPY\t%c,%0\n\tADD32\t%c,%1\n",	/* reg: ADDU4(reg,reg) */
/* 86 */	"?\tTCOPY\t%c,%0\n\tADD32\t%c,%1\n",	/* reg: ADDU4(reg,INDIRU4(addr)) */
/* 87 */	"?\tTCOPY\t%c,%0\n\tFADD32\t%c,%1\n",	/* reg: ADDF4(reg,reg) */
/* 88 */	"?\tTCOPY\t%c,%0\n\tFADD32\t%c,%1\n",	/* reg: ADDF4(reg,INDIRF4(addr)) */
/* 89 */	"?\tcopy\t%c,%0\n\tsub.16\t%c,%1\n",	/* reg: SUBI2(reg,reg) */
/* 90 */	"?\tcopy\t%c,%0\n\tsub.16\t%c,%1\n",	/* reg: SUBI2(reg,con) */
/* 91 */	"?\tcopy\t%c,%0\n\tsub.16\t%c,%1\n",	/* reg: SUBI2(reg,INDIRI2(addr)) */
/* 92 */	"?\tcopy\t%c,%0\n\tsub.16\t%c,%1\n",	/* reg: SUBU2(reg,reg) */
/* 93 */	"?\tcopy\t%c,%0\n\tsub.16\t%c,%1\n",	/* reg: SUBU2(reg,con) */
/* 94 */	"?\tcopy\t%c,%0\n\tsub.16\t%c,%1\n",	/* reg: SUBU2(reg,INDIRI2(addr)) */
/* 95 */	"?\tcopy\t%c,%0\n\tsub.16\t%c,%1\n",	/* reg: SUBP2(reg,reg) */
/* 96 */	"?\tcopy\t%c,%0\n\tsub.16\t%c,%1\n",	/* reg: SUBP2(reg,con) */
/* 97 */	"?\tcopy\t%c,%0\n\tsub.16\t%c,%1\n",	/* reg: SUBP2(reg,INDIRI2(addr)) */
/* 98 */	"?\tcopy\t%c,%0\n\tsub.8\t%c,%1\n",	/* reg8: SUBI2(reg8,reg8) */
/* 99 */	"?\tcopy\t%c,%0\n\tsub.8\t%c,%1\n",	/* reg8: SUBI2(reg8,con) */
/* 100 */	"?\tcopy\t%c,%0\n\tsub.8\t%c,%1\n",	/* reg8: SUBI2(reg8,CVII2(INDIRI2(addr))) */
/* 101 */	"?\tcopy\t%c,%0\n\tsub.8\t%c,%1\n",	/* reg8: SUBU2(reg8,reg8) */
/* 102 */	"?\tcopy\t%c,%0\n\tsub.8\t%c,%1\n",	/* reg8: SUBU2(reg8,con) */
/* 103 */	"?\tcopy\t%c,%0\n\tsub.8\t%c,%1\n",	/* reg8: SUBU2(reg8,CVUU2(INDIRU2(addr))) */
/* 104 */	"?\tTCOPY\t%c,%0\n\tSUB32\t%c,%1\n",	/* reg: SUBI4(reg,reg) */
/* 105 */	"?\tTCOPY\t%c,%0\n\tSUB32\t%c,%1\n",	/* reg: SUBI4(reg,INDIRI4(addr)) */
/* 106 */	"?\tTCOPY\t%c,%0\n\tSUB32\t%c,%1\n",	/* reg: SUBU4(reg,reg) */
/* 107 */	"?\tTCOPY\t%c,%0\n\tSUB32\t%c,%1\n",	/* reg: SUBU4(reg,INDIRU4(addr)) */
/* 108 */	"?\tTCOPY\t%c,%0\n\tFSUB32\t%c,%1\n",	/* reg: SUBF4(reg,reg) */
/* 109 */	"?\tTCOPY\t%c,%0\n\tFSUB32\t%c,%1\n",	/* reg: SUBF4(reg,INDIRF4(addr)) */
/* 110 */	"?\tcopy\t%c,%0\n\tand.16\t%c,%1\n",	/* reg: BANDI2(reg,reg) */
/* 111 */	"?\tcopy\t%c,%0\n\tand.16\t%c,%1\n",	/* reg: BANDI2(reg,con) */
/* 112 */	"?\tcopy\t%c,%0\n\tand.16\t%c,%1\n",	/* reg: BANDI2(reg,INDIRI2(addr)) */
/* 113 */	"?\tcopy\t%c,%0\n\tand.16\t%c,%1\n",	/* reg: BANDU2(reg,reg) */
/* 114 */	"?\tcopy\t%c,%0\n\tand.16\t%c,%1\n",	/* reg: BANDU2(reg,con) */
/* 115 */	"?\tcopy\t%c,%0\n\tand.16\t%c,%1\n",	/* reg: BANDU2(reg,INDIRI2(addr)) */
/* 116 */	"?\tcopy\t%c,%0\n\tand.8\t%c,%1\n",	/* reg8: BANDI2(reg8,reg8) */
/* 117 */	"?\tcopy\t%c,%0\n\tand.8\t%c,%1\n",	/* reg8: BANDI2(reg8,con) */
/* 118 */	"?\tcopy\t%c,%0\n\tand.8\t%c,%1\n",	/* reg8: BANDI2(reg8,CVII2(INDIRI2(addr))) */
/* 119 */	"?\tcopy\t%c,%0\n\tand.8\t%c,%1\n",	/* reg8: BANDU2(reg8,reg8) */
/* 120 */	"?\tcopy\t%c,%0\n\tand.8\t%c,%1\n",	/* reg8: BANDU2(reg8,con) */
/* 121 */	"?\tcopy\t%c,%0\n\tand.8\t%c,%1\n",	/* reg8: BANDU2(reg8,CVUU2(INDIRU2(addr))) */
/* 122 */	"?\tTCOPY\t%c,%0\n\tAND32\t%c,%1\n",	/* reg: BANDI4(reg,reg) */
/* 123 */	"?\tTCOPY\t%c,%0\n\tAND32\t%c,%1\n",	/* reg: BANDI4(reg,INDIRI4(addr)) */
/* 124 */	"?\tTCOPY\t%c,%0\n\tAND32\t%c,%1\n",	/* reg: BANDU4(reg,reg) */
/* 125 */	"?\tTCOPY\t%c,%0\n\tAND32\t%c,%1\n",	/* reg: BANDU4(reg,INDIRU4(addr)) */
/* 126 */	"?\tcopy\t%c,%0\n\tor.16\t%c,%1\n",	/* reg: BORI2(reg,reg) */
/* 127 */	"?\tcopy\t%c,%0\n\tor.16\t%c,%1\n",	/* reg: BORI2(reg,con) */
/* 128 */	"?\tcopy\t%c,%0\n\tor.16\t%c,%1\n",	/* reg: BORI2(reg,INDIRI2(addr)) */
/* 129 */	"?\tcopy\t%c,%0\n\tor.16\t%c,%1\n",	/* reg: BORU2(reg,reg) */
/* 130 */	"?\tcopy\t%c,%0\n\tor.16\t%c,%1\n",	/* reg: BORU2(reg,con) */
/* 131 */	"?\tcopy\t%c,%0\n\tor.16\t%c,%1\n",	/* reg: BORU2(reg,INDIRI2(addr)) */
/* 132 */	"?\tcopy\t%c,%0\n\tor.8\t%c,%1\n",	/* reg8: BORI2(reg8,reg8) */
/* 133 */	"?\tcopy\t%c,%0\n\tor.8\t%c,%1\n",	/* reg8: BORI2(reg8,con) */
/* 134 */	"?\tcopy\t%c,%0\n\tor.8\t%c,%1\n",	/* reg8: BORI2(reg8,CVII2(INDIRI2(addr))) */
/* 135 */	"?\tcopy\t%c,%0\n\tor.8\t%c,%1\n",	/* reg8: BORU2(reg8,reg8) */
/* 136 */	"?\tcopy\t%c,%0\n\tor.8\t%c,%1\n",	/* reg8: BORU2(reg8,con) */
/* 137 */	"?\tcopy\t%c,%0\n\tor.8\t%c,%1\n",	/* reg8: BORU2(reg8,CVUU2(INDIRU2(addr))) */
/* 138 */	"?\tTCOPY\t%c,%0\n\tOR32\t%c,%1\n",	/* reg: BORI4(reg,reg) */
/* 139 */	"?\tTCOPY\t%c,%0\n\tOR32\t%c,%1\n",	/* reg: BORI4(reg,INDIRI4(addr)) */
/* 140 */	"?\tTCOPY\t%c,%0\n\tOR32\t%c,%1\n",	/* reg: BORU4(reg,reg) */
/* 141 */	"?\tTCOPY\t%c,%0\n\tOR32\t%c,%1\n",	/* reg: BORU4(reg,INDIRU4(addr)) */
/* 142 */	"?\tcopy\t%c,%0\n\txor.16\t%c,%1\n",	/* reg: BXORI2(reg,reg) */
/* 143 */	"?\tcopy\t%c,%0\n\txor.16\t%c,%1\n",	/* reg: BXORU2(reg,reg) */
/* 144 */	"?\tTCOPY\t%c,%0\n\tXOR32\t%c,%1\n",	/* reg: BXORI4(reg,reg) */
/* 145 */	"?\tTCOPY\t%c,%0\n\tXOR32\t%c,%1\n",	/* reg: BXORI4(reg,INDIRI4(addr)) */
/* 146 */	"?\tTCOPY\t%c,%0\n\tXOR32\t%c,%1\n",	/* reg: BXORU4(reg,reg) */
/* 147 */	"?\tTCOPY\t%c,%0\n\tXOR32\t%c,%1\n",	/* reg: BXORU4(reg,INDIRU4(addr)) */
/* 148 */	"?\tcopy\t%c,%0\n\tcall\t$muli16\n",	/* reg: MULI2(reg,reg) */
/* 149 */	"?\tcopy\t%c,%0\n\tcall\t$mulu16\n",	/* reg: MULU2(reg,reg) */
/* 150 */	"?\tCOPY32\t%c,%0\n\tcall\t$muli32\n",	/* reg: MULI4(reg,reg) */
/* 151 */	"?\tCOPY32\t%c,%0\n\tMULI32\t%c,%1\n",	/* reg: MULI4(reg,INDIRI4(addr)) */
/* 152 */	"?\tCOPY32\t%c,%0\n\tcall\t$mulu32\n",	/* reg: MULU4(reg,reg) */
/* 153 */	"?\tCOPY32\t%c,%0\n\tcall\t$mulu32\n",	/* reg: MULU4(reg,INDIRU4(addr)) */
/* 154 */	"?\tCOPY32\t%c,%0\n\tcall\t$mulf32\n",	/* reg: MULF4(reg,reg) */
/* 155 */	"?\tCOPY32\t%c,%0\n\tcall\t$mulf32\n",	/* reg: MULU4(reg,INDIRU4(addr)) */
/* 156 */	"?\tcopy\t%c,%0\n\tcall\t$divi16\n",	/* reg: DIVI2(reg,reg) */
/* 157 */	"?\tcopy\t%c,%0\n\tcall\t$divu16\n",	/* reg: DIVU2(reg,reg) */
/* 158 */	"?\tCOPY32\t%c,%0\n\tcall\t$divi32\n",	/* reg: DIVI4(reg,reg) */
/* 159 */	"?\tCOPY32\t%c,%0\n\tcall\t$divi32\n",	/* reg: DIVI4(reg,INDIRI4(addr)) */
/* 160 */	"?\tCOPY32\t%c,%0\n\tcall\t$divu32\n",	/* reg: DIVU4(reg,reg) */
/* 161 */	"?\tCOPY32\t%c,%0\n\tcall\t$divu32\n",	/* reg: DIVU4(reg,INDIRU4(addr)) */
/* 162 */	"?\tCOPY32\t%c,%0\n\tcall\t$divf32\n",	/* reg: DIVF4(reg,reg) */
/* 163 */	"?\tCOPY32\t%c,%0\n\tcall\t$divf32\n",	/* reg: DIVF4(reg,INDIRF4(addr)) */
/* 164 */	"?\tcopy\t%c,%0\n\tcall\t$modi16\n",	/* reg: MODI2(reg,reg) */
/* 165 */	"?\tcopy\t%c,%0\n\tcall\t$modu16\n",	/* reg: MODU2(reg,reg) */
/* 166 */	"?\tCOPY32\t%c,%0\n\tcall\t$modi32\n",	/* reg: MODI4(reg,reg) */
/* 167 */	"?\tCOPY32\t%c,%0\n\tcall\t$modi32\n",	/* reg: MODI4(reg,INDIRI4(addr)) */
/* 168 */	"?\tCOPY32\t%c,%0\n\tcall\t$modu32\n",	/* reg: MODU4(reg,reg) */
/* 169 */	"?\tCOPY32\t%c,%0\n\tcall\t$modu32\n",	/* reg: MODU4(reg,INDIRU4(addr)) */
/* 170 */	"\tld.16\t%c,0\n\tsub.16\t%c,%0\n",	/* reg: NEGI2(reg) */
/* 171 */	"tNEGI32\t%c,%0\n",	/* reg: NEGI4(reg) */
/* 172 */	"\tNEGI32\t%c,%0\n",	/* reg: NEGI4(INDIRI4(addr)) */
/* 173 */	"\tNEGF32\t%c,%0\n",	/* reg: NEGF4(reg) */
/* 174 */	"\tNEGF32\t%c,%0\n",	/* reg: NEGF4(INDIRF4(addr)) */
/* 175 */	"?\tcopy\t%c,%0\n\tshl.16\t%c,%c\n",	/* reg: LSHI2(reg,c1) */
/* 176 */	"?\tcopy\t%c,%0\n\tshl.16\t%c,%c\n\tshl.16\t%c,%c\n",	/* reg: LSHI2(reg,c2) */
/* 177 */	"?\tcopy\t%c,%0\n\tld.16\tc,%1\n\tvshl.16\t%c\n",	/* reg: LSHI2(reg,con) */
/* 178 */	"?\tcopy\t%c,%0\n\tcopy\tc,%1\n\tvshl.16\t%c\n",	/* reg: LSHI2(reg,reg) */
/* 179 */	"?\tcopy\t%c,%0\n\tshl.16\t%c,%c\n",	/* reg: LSHU2(reg,c1) */
/* 180 */	"?\tcopy\t%c,%0\n\tshl.16\t%c,%c\n\tshl.16\t%c,%c\n",	/* reg: LSHU2(reg,c2) */
/* 181 */	"?\tcopy\t%c,%0\n\tld.16\tc,%1\n\tvshl.16\t%c\n",	/* reg: LSHU2(reg,con) */
/* 182 */	"?\tcopy\t%c,%0\n\tcopy\tc,%1\n\tvshl.16\t%c\n",	/* reg: LSHU2(reg,reg) */
/* 183 */	"?\tCOPY32\t%c,%0\n\tLSH32\t%c,%1\n",	/* reg: LSHI4(reg,reg) */
/* 184 */	"?\tCOPY32\t%c,%0\n\tLSH32\t%c,%1\n",	/* reg: LSHI4(reg,INDIRI4(addr)) */
/* 185 */	"?\tCOPY32\t%c,%0\n\tLSH32\t%c,%1\n",	/* reg: LSHU4(reg,reg) */
/* 186 */	"?\tCOPY32\t%c,%0\n\tLSH32\t%c,%1\n",	/* reg: LSHU4(reg,INDIRU4(addr)) */
/* 187 */	"?\tcopy\t%c,%0\n\tshr.16\t%c,%c\n",	/* reg: RSHI2(reg,c1) */
/* 188 */	"?\tcopy\t%c,%0\n\tshr.16\t%c,%c\n\tshr.16\t%c,%c\n",	/* reg: RSHI2(reg,c2) */
/* 189 */	"?\tcopy\t%c,%0\n\tld.16\tc,%1\n\tvshr.16\t%c\n",	/* reg: RSHI2(reg,con) */
/* 190 */	"?\tcopy\t%c,%0\n\tcopy\tc,%1\n\tvshr.16\t%c\n",	/* reg: RSHI2(reg,reg) */
/* 191 */	"?\tcopy\t%c,%0\n\tshr.16\t%c,%c\n",	/* reg: RSHU2(reg,c1) */
/* 192 */	"?\tcopy\t%c,%0\n\tshr.16\t%c,%c\n\tshr.16\t%c,%c\n",	/* reg: RSHU2(reg,c2) */
/* 193 */	"?\tcopy\t%c,%0\n\tld.16\tc,%1\n\tvshr.16\t%c\n",	/* reg: RSHU2(reg,con) */
/* 194 */	"?\tcopy\t%c,%0\n\tcopy\tc,%1\n\tvshr.16\t%c\n",	/* reg: RSHU2(reg,reg) */
/* 195 */	"?\tCOPY32\t%c,%0\n\tRSH32\t%c,%1\n",	/* reg: RSHI4(reg,reg) */
/* 196 */	"?\tCOPY32\t%c,%0\n\tRSH32\t%c,%1\n",	/* reg: RSHI4(reg,INDIRI4(addr)) */
/* 197 */	"?\tCOPY32\t%c,%0\n\tRSH32\t%c,%1\n",	/* reg: RSHU4(reg,reg) */
/* 198 */	"?\tCOPY32\t%c,%0\n\tRSH32\t%c,%1\n",	/* reg: RSHU4(reg,INDIRU4(addr)) */
/* 199 */	"\tcmpb.eq.16\t%0,%1,%a\n",	/* stmt: EQI2(reg,reg) */
/* 200 */	"\tcmpb.eq.16\t%0,%1,%a\n",	/* stmt: EQI2(reg,con) */
/* 201 */	"\tcmpb.eq.16\t%0,%1,%a\n",	/* stmt: EQI2(reg,INDIRI2(addr)) */
/* 202 */	"\tcmpb.eq.16\t%0,%1,%a\n",	/* stmt: EQU2(reg,reg) */
/* 203 */	"\tcmpb.eq.16\t%0,%1,%a\n",	/* stmt: EQU2(reg,con) */
/* 204 */	"\tcmpb.eq.16\t%0,%1,%a\n",	/* stmt: EQU2(reg,INDIRU2(addr)) */
/* 205 */	"\tcmpb.eq.8\t%0,%1,%a\n",	/* stmt: EQI2(reg8,reg8) */
/* 206 */	"\tcmpb.eq.8\t%0,%1,%a\n",	/* stmt: EQI2(reg8,con) */
/* 207 */	"\tcmpb.eq.8\t%0,%1,%a\n",	/* stmt: EQI2(reg8,CVII2(INDIRI1(addr))) */
/* 208 */	"\tcmpb.eq.8\t%0,%1,%a\n",	/* stmt: EQU2(reg8,reg8) */
/* 209 */	"\tcmpb.eq.8\t%0,%1,%a\n",	/* stmt: EQU2(reg8,con) */
/* 210 */	"\tcmpb.eq.8\t%0,%1,%a\n",	/* stmt: EQU2(reg8,CVUU2(INDIRU1(addr))) */
/* 211 */	"\tCMPBEQ32\t%0,%1,%a\n",	/* stmt: EQI4(reg,reg) */
/* 212 */	"\tCMPBEQ32\t%0,%1,%a\n",	/* stmt: EQI4(reg,INDIRI4(addr)) */
/* 213 */	"\tCMPBEQ32\t%0,%1,%a\n",	/* stmt: EQU4(reg,reg) */
/* 214 */	"\tCMPBEQ32\t%0,%1,%a\n",	/* stmt: EQU4(reg,INDIRU4(addr)) */
/* 215 */	"\tCMPBEQF\t%0,%1,%a\n",	/* stmt: EQF4(reg,reg) */
/* 216 */	"\tCMPBEQF\t%0,%1,%a\n",	/* stmt: EQF4(reg,INDIRF4(addr)) */
/* 217 */	"\tcmpb.ne.16\t%0,%1,%a\n",	/* stmt: NEI2(reg,reg) */
/* 218 */	"\tcmpb.ne.16\t%0,%1,%a\n",	/* stmt: NEI2(reg,con) */
/* 219 */	"\tcmpb.ne.16\t%0,%1,%a\n",	/* stmt: NEI2(reg,INDIRI2(addr)) */
/* 220 */	"\tcmpb.ne.16\t%0,%1,%a\n",	/* stmt: NEU2(reg,reg) */
/* 221 */	"\tcmpb.ne.16\t%0,%1,%a\n",	/* stmt: NEU2(reg,con) */
/* 222 */	"\tcmpb.ne.16\t%0,%1,%a\n",	/* stmt: NEU2(reg,INDIRU2(addr)) */
/* 223 */	"\tcmpb.ne.8\t%0,%1,%a\n",	/* stmt: NEI2(reg8,reg8) */
/* 224 */	"\tcmpb.ne.8\t%0,%1,%a\n",	/* stmt: NEI2(reg8,con) */
/* 225 */	"\tcmpb.ne.8\t%0,%1,%a\n",	/* stmt: NEI2(reg8,CVII2(INDIRI1(addr))) */
/* 226 */	"\tcmpb.ne.8\t%0,%1,%a\n",	/* stmt: NEU2(reg8,reg8) */
/* 227 */	"\tcmpb.ne.8\t%0,%1,%a\n",	/* stmt: NEU2(reg8,con) */
/* 228 */	"\tcmpb.ne.8\t%0,%1,%a\n",	/* stmt: NEU2(reg8,CVUU2(INDIRU1(addr))) */
/* 229 */	"\tCMPBNE32\t%0,%1,%a\n",	/* stmt: NEI4(reg,reg) */
/* 230 */	"\tCMPBNE32\t%0,%1,%a\n",	/* stmt: NEI4(reg,INDIRU4(addr)) */
/* 231 */	"\tCMPBNE32\t%0,%1,%a\n",	/* stmt: NEU4(reg,reg) */
/* 232 */	"\tCMPBNE32\t%0,%1,%a\n",	/* stmt: NEU4(reg,INDIRU4(addr)) */
/* 233 */	"\tCMPBNEF\t%0,%1,%a\n",	/* stmt: NEF4(reg,reg) */
/* 234 */	"\tCMPBNEF\t%0,%1,%a\n",	/* stmt: NEF4(reg,INDIRF4(addr)) */
/* 235 */	"\tcmpb.lt.16\t%0,%1,%a\n",	/* stmt: LTI2(reg,reg) */
/* 236 */	"\tcmpb.lt.16\t%0,%1,%a\n",	/* stmt: LTI2(reg,con) */
/* 237 */	"\tcmpb.lt.16\t%0,%1,%a\n",	/* stmt: LTI2(reg,INDIRI2(addr)) */
/* 238 */	"\tcmpb.ltu.16\t%0,%1,%a\n",	/* stmt: LTU2(reg,reg) */
/* 239 */	"\tcmpb.ltu.16\t%0,%1,%a\n",	/* stmt: LTU2(reg,con) */
/* 240 */	"\tcmpb.ltu.16\t%0,%1,%a\n",	/* stmt: LTU2(reg,INDIRU2(addr)) */
/* 241 */	"\tcmpb.lt.8\t%0,%1,%a\n",	/* stmt: LTI2(reg8,reg8) */
/* 242 */	"\tcmpb.lt.8\t%0,%1,%a\n",	/* stmt: LTI2(reg8,con) */
/* 243 */	"\tcmpb.lt.8\t%0,%1,%a\n",	/* stmt: LTI2(reg8,CVII2(INDIRI1(addr))) */
/* 244 */	"\tcmpb.ltu.8\t%0,%1,%a\n",	/* stmt: LTU2(reg8,reg8) */
/* 245 */	"\tcmpb.ltu.8\t%0,%1,%a\n",	/* stmt: LTU2(reg8,con) */
/* 246 */	"\tcmpb.ltu.8\t%0,%1,%a\n",	/* stmt: LTU2(reg8,CVUU2(INDIRU1(addr))) */
/* 247 */	"\tCMPBLT32\t%0,%1,%a\n",	/* stmt: LTI4(reg,reg) */
/* 248 */	"\tCMPBLT32\t%0,%1,%a\n",	/* stmt: LTI4(reg,INDIRI4(addr)) */
/* 249 */	"\tCMPBLTU32\t%0,%1,%a\n",	/* stmt: LTU4(reg,reg) */
/* 250 */	"\tCMPBLTU32\t%0,%1,%a\n",	/* stmt: LTU4(reg,INDIRU4(addr)) */
/* 251 */	"\tCMPBLTF\t%0,%1,%a\n",	/* stmt: LTF4(reg,reg) */
/* 252 */	"\tCMPBLTF\t%0,%1,%a\n",	/* stmt: LTF4(reg,INDIRF4(addr)) */
/* 253 */	"\tcmpb.le.16\t%0,%1,%a\n",	/* stmt: LEI2(reg,reg) */
/* 254 */	"\tcmpb.le.16\t%0,%1,%a\n",	/* stmt: LEI2(reg,con) */
/* 255 */	"\tcmpb.le.16\t%0,%1,%a\n",	/* stmt: LEI2(reg,INDIRI2(addr)) */
/* 256 */	"\tcmpb.leu.16\t%0,%1,%a\n",	/* stmt: LEU2(reg,reg) */
/* 257 */	"\tcmpb.leu.16\t%0,%1,%a\n",	/* stmt: LEU2(reg,con) */
/* 258 */	"\tcmpb.leu.16\t%0,%1,%a\n",	/* stmt: LEU2(reg,INDIRU2(addr)) */
/* 259 */	"\tcmpb.le.8\t%0,%1,%a\n",	/* stmt: LEI2(reg8,reg8) */
/* 260 */	"\tcmpb.le.8\t%0,%1,%a\n",	/* stmt: LEI2(reg8,con) */
/* 261 */	"\tcmpb.le.8\t%0,%1,%a\n",	/* stmt: LEI2(reg8,CVII2(INDIRI1(addr))) */
/* 262 */	"\tcmpb.leu.8\t%0,%1,%a\n",	/* stmt: LEU2(reg8,reg8) */
/* 263 */	"\tcmpb.leu.8\t%0,%1,%a\n",	/* stmt: LEU2(reg8,con) */
/* 264 */	"\tcmpb.leu.8\t%0,%1,%a\n",	/* stmt: LEU2(reg8,CVUU2(INDIRU1(addr))) */
/* 265 */	"\tCMPBLE32\t%0,%1,%a\n",	/* stmt: LEI4(reg,reg) */
/* 266 */	"\tCMPBLE32\t%0,%1,%a\n",	/* stmt: LEI4(reg,INDIRI4(addr)) */
/* 267 */	"\tCMPBLEU32\t%0,%1,%a\n",	/* stmt: LEU4(reg,reg) */
/* 268 */	"\tCMPBLEU32\t%0,%1,%a\n",	/* stmt: LEU4(reg,INDIRU4(addr)) */
/* 269 */	"\tCMPBLEF\t%0,%1,%a\n",	/* stmt: LEF4(reg,reg) */
/* 270 */	"\tCMPBLEF\t%0,%1,%a\n",	/* stmt: LEF4(reg,INDIRF4(addr)) */
/* 271 */	"\tcmpb.lt.16\t%1,%0,%a\n",	/* stmt: GTI2(reg,reg) */
/* 272 */	"\tcmpb.lt.16\t%1,%0,%a\n",	/* stmt: GTI2(con,reg) */
/* 273 */	"\tcmpb.lt.16\t%1,%0,%a\n",	/* stmt: GTI2(INDIRI2(addr),reg) */
/* 274 */	"\tcmpb.ltu.16\t%1,%0,%a\n",	/* stmt: GTU2(reg,reg) */
/* 275 */	"\tcmpb.ltu.16\t%1,%0,%a\n",	/* stmt: GTU2(con,reg) */
/* 276 */	"\tcmpb.ltu.16\t%1,%0,%a\n",	/* stmt: GTU2(INDIRU2(addr),reg) */
/* 277 */	"\tcmpb.lt.8\t%1,%0,%a\n",	/* stmt: GTI2(reg8,reg8) */
/* 278 */	"\tcmpb.lt.8\t%1,%0,%a\n",	/* stmt: GTI2(con,reg8) */
/* 279 */	"\tcmpb.lt.8\t%1,%0,%a\n",	/* stmt: GTI2(CVII2(INDIRI1(addr)),reg8) */
/* 280 */	"\tcmpb.ltu.8\t%1,%0,%a\n",	/* stmt: GTU2(reg8,reg8) */
/* 281 */	"\tcmpb.ltu.8\t%1,%0,%a\n",	/* stmt: GTU2(con,reg8) */
/* 282 */	"\tcmpb.ltu.8\t%1,%0,%a\n",	/* stmt: GTU2(CVUU2(INDIRU1(addr)),reg8) */
/* 283 */	"\tCMPBLT32\t%1,%0,%a\n",	/* stmt: GTI4(reg,reg) */
/* 284 */	"\tCMPBLT32\t%1,%0,%a\n",	/* stmt: GTI4(INDIRI4(addr),reg) */
/* 285 */	"\tCMPBLTU32\t%1,%0,%a\n",	/* stmt: GTU4(reg,reg) */
/* 286 */	"\tCMPBLTU32\t%1,%0,%a\n",	/* stmt: GTU4(INDIRU4(addr),reg) */
/* 287 */	"\tCMPBLTF\t%1,%0,%a\n",	/* stmt: GTF4(reg,reg) */
/* 288 */	"\tCMPBLTF\t%1,%0,%a\n",	/* stmt: GTF4(INDIRF4(addr),reg) */
/* 289 */	"\tcmpb.le.16\t%1,%0,%a\n",	/* stmt: GEI2(reg,reg) */
/* 290 */	"\tcmpb.le.16\t%1,%0,%a\n",	/* stmt: GEI2(con,reg) */
/* 291 */	"\tcmpb.le.16\t%1,%0,%a\n",	/* stmt: GEI2(INDIRI2(addr),reg) */
/* 292 */	"\tcmpb.leu.16\t%1,%0,%a\n",	/* stmt: GEU2(reg,reg) */
/* 293 */	"\tcmpb.leu.16\t%1,%0,%a\n",	/* stmt: GEU2(con,reg) */
/* 294 */	"\tcmpb.leu.16\t%1,%0,%a\n",	/* stmt: GEU2(INDIRU2(addr),reg) */
/* 295 */	"\tcmpb.le.8\t%1,%0,%a\n",	/* stmt: GEI2(reg8,reg8) */
/* 296 */	"\tcmpb.le.8\t%1,%0,%a\n",	/* stmt: GEI2(con,reg8) */
/* 297 */	"\tcmpb.le.8\t%1,%0,%a\n",	/* stmt: GEI2(CVII2(INDIRI1(addr)),reg8) */
/* 298 */	"\tcmpb.leu.8\t%1,%0,%a\n",	/* stmt: GEU2(reg8,reg8) */
/* 299 */	"\tcmpb.leu.8\t%1,%0,%a\n",	/* stmt: GEU2(con,reg8) */
/* 300 */	"\tcmpb.leu.8\t%1,%0,%a\n",	/* stmt: GEU2(CVUU2(INDIRU1(addr)),reg8) */
/* 301 */	"\tCMPBLE32\t%1,%0,%a\n",	/* stmt: GEI4(reg,reg) */
/* 302 */	"\tCMPBLE32\t%1,%0,%a\n",	/* stmt: GEI4(INDIRI4(addr),reg) */
/* 303 */	"\tCMPBLEU32\t%1,%0,%a\n",	/* stmt: GEU4(reg,reg) */
/* 304 */	"\tCMPBLEU32\t%1,%0,%a\n",	/* stmt: GEU4(INDIRU4(addr),reg) */
/* 305 */	"\tCMPBLEF\t%1,%0,%a\n",	/* stmt: GEF4(reg,reg) */
/* 306 */	"\tCMPBLEF\t%1,%0,%a\n",	/* stmt: GEF4(INDIRF4(addr),reg) */
/* 307 */	"%a(pc)",	/* addr: ADDRGP2 */
/* 308 */	"%a(dp)",	/* addr: ADDRGP2 */
/* 309 */	"%a+%F(sp)",	/* addr: ADDRLP2 */
/* 310 */	"%a+4+%F(sp)",	/* addr: ADDRFP2 */
/* 311 */	"",	/* stmt: reg */
/* 312 */	"%a:\n",	/* stmt: LABELV */
/* 313 */	"\tlea\t%c,%a(pc)\n",	/* reg: ADDRGP2 */
/* 314 */	"\tlea\t%c,%a(dp)\n",	/* reg: ADDRGP2 */
/* 315 */	"\tlea\t%c,%a+%F(sp)\n",	/* reg: ADDRLP2 */
/* 316 */	"\tlea\t%c,%a+2+%F(sp)\n",	/* reg: ADDRFP2 */
/* 317 */	"\tld.8\t%c,0(%0)\n",	/* reg8: INDIRI1(reg) */
/* 318 */	"\tld.8\t%c,%0\n",	/* reg8: INDIRI1(addr) */
/* 319 */	"\tld.8\t%c,0(%0)\n",	/* reg8: INDIRU1(reg) */
/* 320 */	"\tld.8\t%c,%0\n",	/* reg8: INDIRU1(addr) */
/* 321 */	"\tld.16\t%c,0(%0)\n",	/* reg: INDIRI2(reg) */
/* 322 */	"\tld.16\t%c,%0\n",	/* reg: INDIRI2(addr) */
/* 323 */	"\tld.16\t%c,0(%0)\n",	/* reg: INDIRU2(reg) */
/* 324 */	"\tld.16\t%c,%0\n",	/* reg: INDIRU2(addr) */
/* 325 */	"\tld.16\t%c,0(%0)\n",	/* reg: INDIRP2(reg) */
/* 326 */	"\tld.16\t%c,%0\n",	/* reg: INDIRP2(addr) */
/* 327 */	"\tCOPY32\t%c,0(%0)\n",	/* reg: INDIRI4(reg) */
/* 328 */	"\tCOPY32\t%c,%0\n",	/* reg: INDIRI4(addr) */
/* 329 */	"\tCOPY32\t%c,0(%0)\n",	/* reg: INDIRU4(reg) */
/* 330 */	"\tCOPY32\t%c,%0\n",	/* reg: INDIRU4(addr) */
/* 331 */	"\tCOPY32\t%c,0(%0)\n",	/* reg: INDIRF4(reg) */
/* 332 */	"\tCOPY32\t%c,%0\n",	/* reg: INDIRF4(addr) */
/* 333 */	"%0",	/* ar: reg */
/* 334 */	"%a",	/* ar: ADDRGP2 */
/* 335 */	"\tcall\t%0\n",	/* reg: CALLI2(ar) */
/* 336 */	"\tcall\t%0\n",	/* reg: CALLU2(ar) */
/* 337 */	"\tcall\t%0\n",	/* reg: CALLP2(ar) */
/* 338 */	"\tcall\t%0\n\tst.16\t%c,a\n\tst.16\t2+%c,b\n",	/* reg: CALLI4(ar) */
/* 339 */	"\tcall\t%0\n\tst.16\t%c,a\n\tst.16\t2+%c,b\n",	/* reg: CALLU4(ar) */
/* 340 */	"\tcall\t%0\n\tst.16\t%c,a\n\tst.16\t2+%c,b\n",	/* reg: CALLF4(ar) */
/* 341 */	"\tcall\t%0\n",	/* stmt: CALLV(ar) */
/* 342 */	"\tcall\t%0\n",	/* stmt: CALLB(ar,reg) */
/* 343 */	"# rtarget should have handled it\n",	/* stmt: RETI2(reg) */
/* 344 */	"# rtarget should have handled it\n",	/* stmt: RETU2(reg) */
/* 345 */	"# rtarget should have handled it\n",	/* stmt: RETP2(reg) */
/* 346 */	"# emit2 needs to return in a/b regpair\n",	/* stmt: RETI4(reg) */
/* 347 */	"# emit2 needs to return in a/b regpair\n",	/* stmt: RETU4(reg) */
/* 348 */	"# emit2 needs to return in a/b regpair\n",	/* stmt: RETF4(reg) */
/* 349 */	"# ret\n",	/* stmt: RETV(reg) */
/* 350 */	"# Let emit2 handle args\n",	/* stmt: ARGP2(reg) */
/* 351 */	"# Let emit2 handle args\n",	/* stmt: ARGI2(reg) */
/* 352 */	"# Let emit2 handle args\n",	/* stmt: ARGU2(reg) */
/* 353 */	"# Let emit2 handle args\n",	/* stmt: ARGI4(reg) */
/* 354 */	"# Let emit2 handle args\n",	/* stmt: ARGU4(reg) */
/* 355 */	"# Let emit2 handle args\n",	/* stmt: ARGF4(reg) */
/* 356 */	"\tbr\t%0\n",	/* stmt: JUMPV(ar) */
/* 357 */	"\tst.8\t0(%0),%1\n",	/* stmt: ASGNI1(reg,reg8) */
/* 358 */	"\tst.8\t%0,%1\n",	/* stmt: ASGNI1(addr,reg8) */
/* 359 */	"\tst.8\t0(%0),%1\n",	/* stmt: ASGNU1(reg,reg8) */
/* 360 */	"\tst.8\t%0,%1\n",	/* stmt: ASGNU1(addr,reg8) */
/* 361 */	"\tst.16\t0(%0),%1\n",	/* stmt: ASGNI2(reg,reg) */
/* 362 */	"\tst.16\t%0,%1\n",	/* stmt: ASGNI2(addr,reg) */
/* 363 */	"\tst.16\t0(%0),%1\n",	/* stmt: ASGNU2(reg,reg) */
/* 364 */	"\tst.16\t%0,%1\n",	/* stmt: ASGNU2(addr,reg) */
/* 365 */	"\tst.16\t0(%0),%1\n",	/* stmt: ASGNP2(reg,reg) */
/* 366 */	"\tst.16\t%0,%1\n",	/* stmt: ASGNP2(addr,reg) */
/* 367 */	"\tCOPY32\t0(%0),%1\n",	/* stmt: ASGNI4(reg,reg) */
/* 368 */	"\tCOPY32\t%0,%1\n",	/* stmt: ASGNI4(addr,reg) */
/* 369 */	"\tCOPY32\t%0,%1\n",	/* stmt: ASGNI4(addr,con4) */
/* 370 */	"\tCOPY32\t%0,%1\n",	/* stmt: ASGNI4(reg,con4) */
/* 371 */	"\tCOPY32\t0(%0),%1\n",	/* stmt: ASGNU4(reg,reg) */
/* 372 */	"\tCOPY32\t%0,%1\n",	/* stmt: ASGNU4(addr,reg) */
/* 373 */	"\tCOPY32\t%0,%1\n",	/* stmt: ASGNU4(addr,con4) */
/* 374 */	"\tCOPY32\t%0,%1\n",	/* stmt: ASGNU4(reg,con4) */
/* 375 */	"\tCOPY32\t0(%0),%1\n",	/* stmt: ASGNF4(reg,reg) */
/* 376 */	"\tCOPY32\t%0,%1\n",	/* stmt: ASGNF4(addr,reg) */
/* 377 */	"\tCOPY32\t%0,%1\n",	/* stmt: ASGNF4(addr,con4) */
/* 378 */	"\tCOPY32\t%0,%1\n",	/* stmt: ASGNF4(reg,con4) */
/* 379 */	"\tld.16\tc,%a\n\tmemcopy\n",	/* stmt: ASGNB(reg,INDIRB(reg)) */
/* 380 */	"# let emit2 handle %0\n",	/* stmt: ARGB(INDIRB(reg)) */
};

static char _isinstruction[] = {
/* 0 */	0,
/* 1 */	1,	/* \tcopy\t%c,%0\n */
/* 2 */	1,	/* \tcopy\t%c,%0\n */
/* 3 */	1,	/* \tcopy\t%c,%0\n */
/* 4 */	1,	/* \tcopy\t%c,%0\n */
/* 5 */	1,	/* \tcopy\t%c,%0\n */
/* 6 */	1,	/* \tCOPY32\t%c,%0\n */
/* 7 */	1,	/* \tCOPY32\t%c,%0\n */
/* 8 */	1,	/* \tCOPY32\t%c,%0\n */
/* 9 */	1,	/* # read register\n */
/* 10 */	1,	/* # read register\n */
/* 11 */	1,	/* # read register\n */
/* 12 */	1,	/* # read register\n */
/* 13 */	1,	/* # read register\n */
/* 14 */	1,	/* # read register\n */
/* 15 */	1,	/* # read register\n */
/* 16 */	1,	/* # read register\n */
/* 17 */	1,	/* # write register\n */
/* 18 */	1,	/* # write register\n */
/* 19 */	1,	/* # write register\n */
/* 20 */	1,	/* # write register\n */
/* 21 */	1,	/* # write register\n */
/* 22 */	1,	/* # write register\n */
/* 23 */	1,	/* # write register\n */
/* 24 */	1,	/* # write register\n */
/* 25 */	1,	/* \tCOPY32\t%c,%1\n */
/* 26 */	1,	/* \tCVTFI2\t%c,%0\n */
/* 27 */	1,	/* \tCVTFI4\t%c,%0\n */
/* 28 */	1,	/* \tCVTIF4\t%c,%0\n */
/* 29 */	1,	/* ?\tcopy\t%c,%0\n\tsex\t%c\n */
/* 30 */	0,	/* %0 */
/* 31 */	1,	/* \tCVTII4\t%c,%0\n */
/* 32 */	1,	/* \tcopy\t%c,%0\n */
/* 33 */	1,	/* ?\tcopy\t%c,%0\n\tand.16\t%c,0xff\n */
/* 34 */	1,	/* ?\tcopy\t%c,%0\n\tand.16\t%c,0xff\n */
/* 35 */	1,	/* \tCVTII4\t%c,%0\n */
/* 36 */	1,	/* \tcopy\t%c,%0\n */
/* 37 */	1,	/* \tcopy\t%c,%0\n */
/* 38 */	1,	/* ?\tcopy\t%c,%0\n\tand.16\t%c,0xff\n */
/* 39 */	1,	/* ?\tcopy\t%c,%0\n\tand.16\t%c,0xff\n */
/* 40 */	1,	/* \tCVTUI4\t%c,%0\n */
/* 41 */	1,	/* \tcopy\t%c,%0\n */
/* 42 */	1,	/* \tcopy\t%c,%0\n */
/* 43 */	1,	/* \tcopy\t%c,%0\n */
/* 44 */	1,	/* ?\tcopy\t%c,%0\n\tand.16\t%c,0xff\n */
/* 45 */	0,	/* %0 */
/* 46 */	1,	/* \tCVTUU4\t%c,%0\n */
/* 47 */	1,	/* \tld.16\t%c,%0\n */
/* 48 */	1,	/* \tld.8\t%c,%0\n */
/* 49 */	0,	/* 0 */
/* 50 */	0,	/* 1 */
/* 51 */	0,	/* 2 */
/* 52 */	0,	/* %a */
/* 53 */	0,	/* %a */
/* 54 */	0,	/* %a */
/* 55 */	0,	/* %a */
/* 56 */	0,	/* %a */
/* 57 */	0,	/* %a */
/* 58 */	0,	/* %a */
/* 59 */	0,	/* %0 */
/* 60 */	0,	/* %0 */
/* 61 */	0,	/* %0 */
/* 62 */	0,	/* %0 */
/* 63 */	0,	/* %0 */
/* 64 */	0,	/* %0 */
/* 65 */	1,	/* \tld.8\t%c,%0\n */
/* 66 */	1,	/* \tld.16\t%c,%0\n */
/* 67 */	1,	/* \tCON32\t%c,%0\n */
/* 68 */	1,	/* ?\tcopy\t%c,%0\n\tadd.16\t%c,%1\n */
/* 69 */	1,	/* ?\tcopy\t%c,%0\n\tadd.16\t%c,%1\n */
/* 70 */	1,	/* ?\tcopy\t%c,%0\n\tadd.16\t%c,%1\n */
/* 71 */	1,	/* ?\tcopy\t%c,%0\n\tadd.16\t%c,%1\n */
/* 72 */	1,	/* ?\tcopy\t%c,%0\n\tadd.16\t%c,%1\n */
/* 73 */	1,	/* ?\tcopy\t%c,%0\n\tadd.16\t%c,%1\n */
/* 74 */	1,	/* ?\tcopy\t%c,%0\n\tadd.16\t%c,%1\n */
/* 75 */	1,	/* ?\tcopy\t%c,%0\n\tadd.16\t%c,%1\n */
/* 76 */	1,	/* ?\tcopy\t%c,%0\n\tadd.16\t%c,%1\n */
/* 77 */	1,	/* ?\tcopy\t%c,%0\n\tadd.8\t%c,%1\n */
/* 78 */	1,	/* ?\tcopy\t%c,%0\n\tadd.8\t%c,%1\n */
/* 79 */	1,	/* ?\tcopy\t%c,%0\n\tadd.8\t%c,%1\n */
/* 80 */	1,	/* ?\tcopy\t%c,%0\n\tadd.8\t%c,%1\n */
/* 81 */	1,	/* ?\tcopy\t%c,%0\n\tadd.8\t%c,%1\n */
/* 82 */	1,	/* ?\tcopy\t%c,%0\n\tadd.8\t%c,%1\n */
/* 83 */	1,	/* ?\tTCOPY\t%c,%0\n\tADD32\t%c,%1\n */
/* 84 */	1,	/* ?\tTCOPY\t%c,%0\n\tADD32\t%c,%1\n */
/* 85 */	1,	/* ?\tTCOPY\t%c,%0\n\tADD32\t%c,%1\n */
/* 86 */	1,	/* ?\tTCOPY\t%c,%0\n\tADD32\t%c,%1\n */
/* 87 */	1,	/* ?\tTCOPY\t%c,%0\n\tFADD32\t%c,%1\n */
/* 88 */	1,	/* ?\tTCOPY\t%c,%0\n\tFADD32\t%c,%1\n */
/* 89 */	1,	/* ?\tcopy\t%c,%0\n\tsub.16\t%c,%1\n */
/* 90 */	1,	/* ?\tcopy\t%c,%0\n\tsub.16\t%c,%1\n */
/* 91 */	1,	/* ?\tcopy\t%c,%0\n\tsub.16\t%c,%1\n */
/* 92 */	1,	/* ?\tcopy\t%c,%0\n\tsub.16\t%c,%1\n */
/* 93 */	1,	/* ?\tcopy\t%c,%0\n\tsub.16\t%c,%1\n */
/* 94 */	1,	/* ?\tcopy\t%c,%0\n\tsub.16\t%c,%1\n */
/* 95 */	1,	/* ?\tcopy\t%c,%0\n\tsub.16\t%c,%1\n */
/* 96 */	1,	/* ?\tcopy\t%c,%0\n\tsub.16\t%c,%1\n */
/* 97 */	1,	/* ?\tcopy\t%c,%0\n\tsub.16\t%c,%1\n */
/* 98 */	1,	/* ?\tcopy\t%c,%0\n\tsub.8\t%c,%1\n */
/* 99 */	1,	/* ?\tcopy\t%c,%0\n\tsub.8\t%c,%1\n */
/* 100 */	1,	/* ?\tcopy\t%c,%0\n\tsub.8\t%c,%1\n */
/* 101 */	1,	/* ?\tcopy\t%c,%0\n\tsub.8\t%c,%1\n */
/* 102 */	1,	/* ?\tcopy\t%c,%0\n\tsub.8\t%c,%1\n */
/* 103 */	1,	/* ?\tcopy\t%c,%0\n\tsub.8\t%c,%1\n */
/* 104 */	1,	/* ?\tTCOPY\t%c,%0\n\tSUB32\t%c,%1\n */
/* 105 */	1,	/* ?\tTCOPY\t%c,%0\n\tSUB32\t%c,%1\n */
/* 106 */	1,	/* ?\tTCOPY\t%c,%0\n\tSUB32\t%c,%1\n */
/* 107 */	1,	/* ?\tTCOPY\t%c,%0\n\tSUB32\t%c,%1\n */
/* 108 */	1,	/* ?\tTCOPY\t%c,%0\n\tFSUB32\t%c,%1\n */
/* 109 */	1,	/* ?\tTCOPY\t%c,%0\n\tFSUB32\t%c,%1\n */
/* 110 */	1,	/* ?\tcopy\t%c,%0\n\tand.16\t%c,%1\n */
/* 111 */	1,	/* ?\tcopy\t%c,%0\n\tand.16\t%c,%1\n */
/* 112 */	1,	/* ?\tcopy\t%c,%0\n\tand.16\t%c,%1\n */
/* 113 */	1,	/* ?\tcopy\t%c,%0\n\tand.16\t%c,%1\n */
/* 114 */	1,	/* ?\tcopy\t%c,%0\n\tand.16\t%c,%1\n */
/* 115 */	1,	/* ?\tcopy\t%c,%0\n\tand.16\t%c,%1\n */
/* 116 */	1,	/* ?\tcopy\t%c,%0\n\tand.8\t%c,%1\n */
/* 117 */	1,	/* ?\tcopy\t%c,%0\n\tand.8\t%c,%1\n */
/* 118 */	1,	/* ?\tcopy\t%c,%0\n\tand.8\t%c,%1\n */
/* 119 */	1,	/* ?\tcopy\t%c,%0\n\tand.8\t%c,%1\n */
/* 120 */	1,	/* ?\tcopy\t%c,%0\n\tand.8\t%c,%1\n */
/* 121 */	1,	/* ?\tcopy\t%c,%0\n\tand.8\t%c,%1\n */
/* 122 */	1,	/* ?\tTCOPY\t%c,%0\n\tAND32\t%c,%1\n */
/* 123 */	1,	/* ?\tTCOPY\t%c,%0\n\tAND32\t%c,%1\n */
/* 124 */	1,	/* ?\tTCOPY\t%c,%0\n\tAND32\t%c,%1\n */
/* 125 */	1,	/* ?\tTCOPY\t%c,%0\n\tAND32\t%c,%1\n */
/* 126 */	1,	/* ?\tcopy\t%c,%0\n\tor.16\t%c,%1\n */
/* 127 */	1,	/* ?\tcopy\t%c,%0\n\tor.16\t%c,%1\n */
/* 128 */	1,	/* ?\tcopy\t%c,%0\n\tor.16\t%c,%1\n */
/* 129 */	1,	/* ?\tcopy\t%c,%0\n\tor.16\t%c,%1\n */
/* 130 */	1,	/* ?\tcopy\t%c,%0\n\tor.16\t%c,%1\n */
/* 131 */	1,	/* ?\tcopy\t%c,%0\n\tor.16\t%c,%1\n */
/* 132 */	1,	/* ?\tcopy\t%c,%0\n\tor.8\t%c,%1\n */
/* 133 */	1,	/* ?\tcopy\t%c,%0\n\tor.8\t%c,%1\n */
/* 134 */	1,	/* ?\tcopy\t%c,%0\n\tor.8\t%c,%1\n */
/* 135 */	1,	/* ?\tcopy\t%c,%0\n\tor.8\t%c,%1\n */
/* 136 */	1,	/* ?\tcopy\t%c,%0\n\tor.8\t%c,%1\n */
/* 137 */	1,	/* ?\tcopy\t%c,%0\n\tor.8\t%c,%1\n */
/* 138 */	1,	/* ?\tTCOPY\t%c,%0\n\tOR32\t%c,%1\n */
/* 139 */	1,	/* ?\tTCOPY\t%c,%0\n\tOR32\t%c,%1\n */
/* 140 */	1,	/* ?\tTCOPY\t%c,%0\n\tOR32\t%c,%1\n */
/* 141 */	1,	/* ?\tTCOPY\t%c,%0\n\tOR32\t%c,%1\n */
/* 142 */	1,	/* ?\tcopy\t%c,%0\n\txor.16\t%c,%1\n */
/* 143 */	1,	/* ?\tcopy\t%c,%0\n\txor.16\t%c,%1\n */
/* 144 */	1,	/* ?\tTCOPY\t%c,%0\n\tXOR32\t%c,%1\n */
/* 145 */	1,	/* ?\tTCOPY\t%c,%0\n\tXOR32\t%c,%1\n */
/* 146 */	1,	/* ?\tTCOPY\t%c,%0\n\tXOR32\t%c,%1\n */
/* 147 */	1,	/* ?\tTCOPY\t%c,%0\n\tXOR32\t%c,%1\n */
/* 148 */	1,	/* ?\tcopy\t%c,%0\n\tcall\t$muli16\n */
/* 149 */	1,	/* ?\tcopy\t%c,%0\n\tcall\t$mulu16\n */
/* 150 */	1,	/* ?\tCOPY32\t%c,%0\n\tcall\t$muli32\n */
/* 151 */	1,	/* ?\tCOPY32\t%c,%0\n\tMULI32\t%c,%1\n */
/* 152 */	1,	/* ?\tCOPY32\t%c,%0\n\tcall\t$mulu32\n */
/* 153 */	1,	/* ?\tCOPY32\t%c,%0\n\tcall\t$mulu32\n */
/* 154 */	1,	/* ?\tCOPY32\t%c,%0\n\tcall\t$mulf32\n */
/* 155 */	1,	/* ?\tCOPY32\t%c,%0\n\tcall\t$mulf32\n */
/* 156 */	1,	/* ?\tcopy\t%c,%0\n\tcall\t$divi16\n */
/* 157 */	1,	/* ?\tcopy\t%c,%0\n\tcall\t$divu16\n */
/* 158 */	1,	/* ?\tCOPY32\t%c,%0\n\tcall\t$divi32\n */
/* 159 */	1,	/* ?\tCOPY32\t%c,%0\n\tcall\t$divi32\n */
/* 160 */	1,	/* ?\tCOPY32\t%c,%0\n\tcall\t$divu32\n */
/* 161 */	1,	/* ?\tCOPY32\t%c,%0\n\tcall\t$divu32\n */
/* 162 */	1,	/* ?\tCOPY32\t%c,%0\n\tcall\t$divf32\n */
/* 163 */	1,	/* ?\tCOPY32\t%c,%0\n\tcall\t$divf32\n */
/* 164 */	1,	/* ?\tcopy\t%c,%0\n\tcall\t$modi16\n */
/* 165 */	1,	/* ?\tcopy\t%c,%0\n\tcall\t$modu16\n */
/* 166 */	1,	/* ?\tCOPY32\t%c,%0\n\tcall\t$modi32\n */
/* 167 */	1,	/* ?\tCOPY32\t%c,%0\n\tcall\t$modi32\n */
/* 168 */	1,	/* ?\tCOPY32\t%c,%0\n\tcall\t$modu32\n */
/* 169 */	1,	/* ?\tCOPY32\t%c,%0\n\tcall\t$modu32\n */
/* 170 */	1,	/* \tld.16\t%c,0\n\tsub.16\t%c,%0\n */
/* 171 */	1,	/* tNEGI32\t%c,%0\n */
/* 172 */	1,	/* \tNEGI32\t%c,%0\n */
/* 173 */	1,	/* \tNEGF32\t%c,%0\n */
/* 174 */	1,	/* \tNEGF32\t%c,%0\n */
/* 175 */	1,	/* ?\tcopy\t%c,%0\n\tshl.16\t%c,%c\n */
/* 176 */	1,	/* ?\tcopy\t%c,%0\n\tshl.16\t%c,%c\n\tshl.16\t%c,%c\n */
/* 177 */	1,	/* ?\tcopy\t%c,%0\n\tld.16\tc,%1\n\tvshl.16\t%c\n */
/* 178 */	1,	/* ?\tcopy\t%c,%0\n\tcopy\tc,%1\n\tvshl.16\t%c\n */
/* 179 */	1,	/* ?\tcopy\t%c,%0\n\tshl.16\t%c,%c\n */
/* 180 */	1,	/* ?\tcopy\t%c,%0\n\tshl.16\t%c,%c\n\tshl.16\t%c,%c\n */
/* 181 */	1,	/* ?\tcopy\t%c,%0\n\tld.16\tc,%1\n\tvshl.16\t%c\n */
/* 182 */	1,	/* ?\tcopy\t%c,%0\n\tcopy\tc,%1\n\tvshl.16\t%c\n */
/* 183 */	1,	/* ?\tCOPY32\t%c,%0\n\tLSH32\t%c,%1\n */
/* 184 */	1,	/* ?\tCOPY32\t%c,%0\n\tLSH32\t%c,%1\n */
/* 185 */	1,	/* ?\tCOPY32\t%c,%0\n\tLSH32\t%c,%1\n */
/* 186 */	1,	/* ?\tCOPY32\t%c,%0\n\tLSH32\t%c,%1\n */
/* 187 */	1,	/* ?\tcopy\t%c,%0\n\tshr.16\t%c,%c\n */
/* 188 */	1,	/* ?\tcopy\t%c,%0\n\tshr.16\t%c,%c\n\tshr.16\t%c,%c\n */
/* 189 */	1,	/* ?\tcopy\t%c,%0\n\tld.16\tc,%1\n\tvshr.16\t%c\n */
/* 190 */	1,	/* ?\tcopy\t%c,%0\n\tcopy\tc,%1\n\tvshr.16\t%c\n */
/* 191 */	1,	/* ?\tcopy\t%c,%0\n\tshr.16\t%c,%c\n */
/* 192 */	1,	/* ?\tcopy\t%c,%0\n\tshr.16\t%c,%c\n\tshr.16\t%c,%c\n */
/* 193 */	1,	/* ?\tcopy\t%c,%0\n\tld.16\tc,%1\n\tvshr.16\t%c\n */
/* 194 */	1,	/* ?\tcopy\t%c,%0\n\tcopy\tc,%1\n\tvshr.16\t%c\n */
/* 195 */	1,	/* ?\tCOPY32\t%c,%0\n\tRSH32\t%c,%1\n */
/* 196 */	1,	/* ?\tCOPY32\t%c,%0\n\tRSH32\t%c,%1\n */
/* 197 */	1,	/* ?\tCOPY32\t%c,%0\n\tRSH32\t%c,%1\n */
/* 198 */	1,	/* ?\tCOPY32\t%c,%0\n\tRSH32\t%c,%1\n */
/* 199 */	1,	/* \tcmpb.eq.16\t%0,%1,%a\n */
/* 200 */	1,	/* \tcmpb.eq.16\t%0,%1,%a\n */
/* 201 */	1,	/* \tcmpb.eq.16\t%0,%1,%a\n */
/* 202 */	1,	/* \tcmpb.eq.16\t%0,%1,%a\n */
/* 203 */	1,	/* \tcmpb.eq.16\t%0,%1,%a\n */
/* 204 */	1,	/* \tcmpb.eq.16\t%0,%1,%a\n */
/* 205 */	1,	/* \tcmpb.eq.8\t%0,%1,%a\n */
/* 206 */	1,	/* \tcmpb.eq.8\t%0,%1,%a\n */
/* 207 */	1,	/* \tcmpb.eq.8\t%0,%1,%a\n */
/* 208 */	1,	/* \tcmpb.eq.8\t%0,%1,%a\n */
/* 209 */	1,	/* \tcmpb.eq.8\t%0,%1,%a\n */
/* 210 */	1,	/* \tcmpb.eq.8\t%0,%1,%a\n */
/* 211 */	1,	/* \tCMPBEQ32\t%0,%1,%a\n */
/* 212 */	1,	/* \tCMPBEQ32\t%0,%1,%a\n */
/* 213 */	1,	/* \tCMPBEQ32\t%0,%1,%a\n */
/* 214 */	1,	/* \tCMPBEQ32\t%0,%1,%a\n */
/* 215 */	1,	/* \tCMPBEQF\t%0,%1,%a\n */
/* 216 */	1,	/* \tCMPBEQF\t%0,%1,%a\n */
/* 217 */	1,	/* \tcmpb.ne.16\t%0,%1,%a\n */
/* 218 */	1,	/* \tcmpb.ne.16\t%0,%1,%a\n */
/* 219 */	1,	/* \tcmpb.ne.16\t%0,%1,%a\n */
/* 220 */	1,	/* \tcmpb.ne.16\t%0,%1,%a\n */
/* 221 */	1,	/* \tcmpb.ne.16\t%0,%1,%a\n */
/* 222 */	1,	/* \tcmpb.ne.16\t%0,%1,%a\n */
/* 223 */	1,	/* \tcmpb.ne.8\t%0,%1,%a\n */
/* 224 */	1,	/* \tcmpb.ne.8\t%0,%1,%a\n */
/* 225 */	1,	/* \tcmpb.ne.8\t%0,%1,%a\n */
/* 226 */	1,	/* \tcmpb.ne.8\t%0,%1,%a\n */
/* 227 */	1,	/* \tcmpb.ne.8\t%0,%1,%a\n */
/* 228 */	1,	/* \tcmpb.ne.8\t%0,%1,%a\n */
/* 229 */	1,	/* \tCMPBNE32\t%0,%1,%a\n */
/* 230 */	1,	/* \tCMPBNE32\t%0,%1,%a\n */
/* 231 */	1,	/* \tCMPBNE32\t%0,%1,%a\n */
/* 232 */	1,	/* \tCMPBNE32\t%0,%1,%a\n */
/* 233 */	1,	/* \tCMPBNEF\t%0,%1,%a\n */
/* 234 */	1,	/* \tCMPBNEF\t%0,%1,%a\n */
/* 235 */	1,	/* \tcmpb.lt.16\t%0,%1,%a\n */
/* 236 */	1,	/* \tcmpb.lt.16\t%0,%1,%a\n */
/* 237 */	1,	/* \tcmpb.lt.16\t%0,%1,%a\n */
/* 238 */	1,	/* \tcmpb.ltu.16\t%0,%1,%a\n */
/* 239 */	1,	/* \tcmpb.ltu.16\t%0,%1,%a\n */
/* 240 */	1,	/* \tcmpb.ltu.16\t%0,%1,%a\n */
/* 241 */	1,	/* \tcmpb.lt.8\t%0,%1,%a\n */
/* 242 */	1,	/* \tcmpb.lt.8\t%0,%1,%a\n */
/* 243 */	1,	/* \tcmpb.lt.8\t%0,%1,%a\n */
/* 244 */	1,	/* \tcmpb.ltu.8\t%0,%1,%a\n */
/* 245 */	1,	/* \tcmpb.ltu.8\t%0,%1,%a\n */
/* 246 */	1,	/* \tcmpb.ltu.8\t%0,%1,%a\n */
/* 247 */	1,	/* \tCMPBLT32\t%0,%1,%a\n */
/* 248 */	1,	/* \tCMPBLT32\t%0,%1,%a\n */
/* 249 */	1,	/* \tCMPBLTU32\t%0,%1,%a\n */
/* 250 */	1,	/* \tCMPBLTU32\t%0,%1,%a\n */
/* 251 */	1,	/* \tCMPBLTF\t%0,%1,%a\n */
/* 252 */	1,	/* \tCMPBLTF\t%0,%1,%a\n */
/* 253 */	1,	/* \tcmpb.le.16\t%0,%1,%a\n */
/* 254 */	1,	/* \tcmpb.le.16\t%0,%1,%a\n */
/* 255 */	1,	/* \tcmpb.le.16\t%0,%1,%a\n */
/* 256 */	1,	/* \tcmpb.leu.16\t%0,%1,%a\n */
/* 257 */	1,	/* \tcmpb.leu.16\t%0,%1,%a\n */
/* 258 */	1,	/* \tcmpb.leu.16\t%0,%1,%a\n */
/* 259 */	1,	/* \tcmpb.le.8\t%0,%1,%a\n */
/* 260 */	1,	/* \tcmpb.le.8\t%0,%1,%a\n */
/* 261 */	1,	/* \tcmpb.le.8\t%0,%1,%a\n */
/* 262 */	1,	/* \tcmpb.leu.8\t%0,%1,%a\n */
/* 263 */	1,	/* \tcmpb.leu.8\t%0,%1,%a\n */
/* 264 */	1,	/* \tcmpb.leu.8\t%0,%1,%a\n */
/* 265 */	1,	/* \tCMPBLE32\t%0,%1,%a\n */
/* 266 */	1,	/* \tCMPBLE32\t%0,%1,%a\n */
/* 267 */	1,	/* \tCMPBLEU32\t%0,%1,%a\n */
/* 268 */	1,	/* \tCMPBLEU32\t%0,%1,%a\n */
/* 269 */	1,	/* \tCMPBLEF\t%0,%1,%a\n */
/* 270 */	1,	/* \tCMPBLEF\t%0,%1,%a\n */
/* 271 */	1,	/* \tcmpb.lt.16\t%1,%0,%a\n */
/* 272 */	1,	/* \tcmpb.lt.16\t%1,%0,%a\n */
/* 273 */	1,	/* \tcmpb.lt.16\t%1,%0,%a\n */
/* 274 */	1,	/* \tcmpb.ltu.16\t%1,%0,%a\n */
/* 275 */	1,	/* \tcmpb.ltu.16\t%1,%0,%a\n */
/* 276 */	1,	/* \tcmpb.ltu.16\t%1,%0,%a\n */
/* 277 */	1,	/* \tcmpb.lt.8\t%1,%0,%a\n */
/* 278 */	1,	/* \tcmpb.lt.8\t%1,%0,%a\n */
/* 279 */	1,	/* \tcmpb.lt.8\t%1,%0,%a\n */
/* 280 */	1,	/* \tcmpb.ltu.8\t%1,%0,%a\n */
/* 281 */	1,	/* \tcmpb.ltu.8\t%1,%0,%a\n */
/* 282 */	1,	/* \tcmpb.ltu.8\t%1,%0,%a\n */
/* 283 */	1,	/* \tCMPBLT32\t%1,%0,%a\n */
/* 284 */	1,	/* \tCMPBLT32\t%1,%0,%a\n */
/* 285 */	1,	/* \tCMPBLTU32\t%1,%0,%a\n */
/* 286 */	1,	/* \tCMPBLTU32\t%1,%0,%a\n */
/* 287 */	1,	/* \tCMPBLTF\t%1,%0,%a\n */
/* 288 */	1,	/* \tCMPBLTF\t%1,%0,%a\n */
/* 289 */	1,	/* \tcmpb.le.16\t%1,%0,%a\n */
/* 290 */	1,	/* \tcmpb.le.16\t%1,%0,%a\n */
/* 291 */	1,	/* \tcmpb.le.16\t%1,%0,%a\n */
/* 292 */	1,	/* \tcmpb.leu.16\t%1,%0,%a\n */
/* 293 */	1,	/* \tcmpb.leu.16\t%1,%0,%a\n */
/* 294 */	1,	/* \tcmpb.leu.16\t%1,%0,%a\n */
/* 295 */	1,	/* \tcmpb.le.8\t%1,%0,%a\n */
/* 296 */	1,	/* \tcmpb.le.8\t%1,%0,%a\n */
/* 297 */	1,	/* \tcmpb.le.8\t%1,%0,%a\n */
/* 298 */	1,	/* \tcmpb.leu.8\t%1,%0,%a\n */
/* 299 */	1,	/* \tcmpb.leu.8\t%1,%0,%a\n */
/* 300 */	1,	/* \tcmpb.leu.8\t%1,%0,%a\n */
/* 301 */	1,	/* \tCMPBLE32\t%1,%0,%a\n */
/* 302 */	1,	/* \tCMPBLE32\t%1,%0,%a\n */
/* 303 */	1,	/* \tCMPBLEU32\t%1,%0,%a\n */
/* 304 */	1,	/* \tCMPBLEU32\t%1,%0,%a\n */
/* 305 */	1,	/* \tCMPBLEF\t%1,%0,%a\n */
/* 306 */	1,	/* \tCMPBLEF\t%1,%0,%a\n */
/* 307 */	0,	/* %a(pc) */
/* 308 */	0,	/* %a(dp) */
/* 309 */	0,	/* %a+%F(sp) */
/* 310 */	0,	/* %a+4+%F(sp) */
/* 311 */	0,	/*  */
/* 312 */	1,	/* %a:\n */
/* 313 */	1,	/* \tlea\t%c,%a(pc)\n */
/* 314 */	1,	/* \tlea\t%c,%a(dp)\n */
/* 315 */	1,	/* \tlea\t%c,%a+%F(sp)\n */
/* 316 */	1,	/* \tlea\t%c,%a+2+%F(sp)\n */
/* 317 */	1,	/* \tld.8\t%c,0(%0)\n */
/* 318 */	1,	/* \tld.8\t%c,%0\n */
/* 319 */	1,	/* \tld.8\t%c,0(%0)\n */
/* 320 */	1,	/* \tld.8\t%c,%0\n */
/* 321 */	1,	/* \tld.16\t%c,0(%0)\n */
/* 322 */	1,	/* \tld.16\t%c,%0\n */
/* 323 */	1,	/* \tld.16\t%c,0(%0)\n */
/* 324 */	1,	/* \tld.16\t%c,%0\n */
/* 325 */	1,	/* \tld.16\t%c,0(%0)\n */
/* 326 */	1,	/* \tld.16\t%c,%0\n */
/* 327 */	1,	/* \tCOPY32\t%c,0(%0)\n */
/* 328 */	1,	/* \tCOPY32\t%c,%0\n */
/* 329 */	1,	/* \tCOPY32\t%c,0(%0)\n */
/* 330 */	1,	/* \tCOPY32\t%c,%0\n */
/* 331 */	1,	/* \tCOPY32\t%c,0(%0)\n */
/* 332 */	1,	/* \tCOPY32\t%c,%0\n */
/* 333 */	0,	/* %0 */
/* 334 */	0,	/* %a */
/* 335 */	1,	/* \tcall\t%0\n */
/* 336 */	1,	/* \tcall\t%0\n */
/* 337 */	1,	/* \tcall\t%0\n */
/* 338 */	1,	/* \tcall\t%0\n\tst.16\t%c,a\n\tst.16\t2+%c,b\n */
/* 339 */	1,	/* \tcall\t%0\n\tst.16\t%c,a\n\tst.16\t2+%c,b\n */
/* 340 */	1,	/* \tcall\t%0\n\tst.16\t%c,a\n\tst.16\t2+%c,b\n */
/* 341 */	1,	/* \tcall\t%0\n */
/* 342 */	1,	/* \tcall\t%0\n */
/* 343 */	1,	/* # rtarget should have handled it\n */
/* 344 */	1,	/* # rtarget should have handled it\n */
/* 345 */	1,	/* # rtarget should have handled it\n */
/* 346 */	1,	/* # emit2 needs to return in a/b regpair\n */
/* 347 */	1,	/* # emit2 needs to return in a/b regpair\n */
/* 348 */	1,	/* # emit2 needs to return in a/b regpair\n */
/* 349 */	1,	/* # ret\n */
/* 350 */	1,	/* # Let emit2 handle args\n */
/* 351 */	1,	/* # Let emit2 handle args\n */
/* 352 */	1,	/* # Let emit2 handle args\n */
/* 353 */	1,	/* # Let emit2 handle args\n */
/* 354 */	1,	/* # Let emit2 handle args\n */
/* 355 */	1,	/* # Let emit2 handle args\n */
/* 356 */	1,	/* \tbr\t%0\n */
/* 357 */	1,	/* \tst.8\t0(%0),%1\n */
/* 358 */	1,	/* \tst.8\t%0,%1\n */
/* 359 */	1,	/* \tst.8\t0(%0),%1\n */
/* 360 */	1,	/* \tst.8\t%0,%1\n */
/* 361 */	1,	/* \tst.16\t0(%0),%1\n */
/* 362 */	1,	/* \tst.16\t%0,%1\n */
/* 363 */	1,	/* \tst.16\t0(%0),%1\n */
/* 364 */	1,	/* \tst.16\t%0,%1\n */
/* 365 */	1,	/* \tst.16\t0(%0),%1\n */
/* 366 */	1,	/* \tst.16\t%0,%1\n */
/* 367 */	1,	/* \tCOPY32\t0(%0),%1\n */
/* 368 */	1,	/* \tCOPY32\t%0,%1\n */
/* 369 */	1,	/* \tCOPY32\t%0,%1\n */
/* 370 */	1,	/* \tCOPY32\t%0,%1\n */
/* 371 */	1,	/* \tCOPY32\t0(%0),%1\n */
/* 372 */	1,	/* \tCOPY32\t%0,%1\n */
/* 373 */	1,	/* \tCOPY32\t%0,%1\n */
/* 374 */	1,	/* \tCOPY32\t%0,%1\n */
/* 375 */	1,	/* \tCOPY32\t0(%0),%1\n */
/* 376 */	1,	/* \tCOPY32\t%0,%1\n */
/* 377 */	1,	/* \tCOPY32\t%0,%1\n */
/* 378 */	1,	/* \tCOPY32\t%0,%1\n */
/* 379 */	1,	/* \tld.16\tc,%a\n\tmemcopy\n */
/* 380 */	1,	/* # let emit2 handle %0\n */
};

static char *_string[] = {
/* 0 */	0,
/* 1 */	"reg8: LOADI1(reg8)",
/* 2 */	"reg8: LOADU1(reg8)",
/* 3 */	"reg: LOADI2(reg)",
/* 4 */	"reg: LOADU2(reg)",
/* 5 */	"reg: LOADP2(reg)",
/* 6 */	"reg: LOADI4(reg)",
/* 7 */	"reg: LOADU4(reg)",
/* 8 */	"reg: LOADF4(reg)",
/* 9 */	"reg8: INDIRI1(VREGP)",
/* 10 */	"reg8: INDIRU1(VREGP)",
/* 11 */	"reg: INDIRI2(VREGP)",
/* 12 */	"reg: INDIRU2(VREGP)",
/* 13 */	"reg: INDIRI4(VREGP)",
/* 14 */	"reg: INDIRU4(VREGP)",
/* 15 */	"reg: INDIRP2(VREGP)",
/* 16 */	"reg: INDIRF4(VREGP)",
/* 17 */	"stmt: ASGNI1(VREGP,reg8)",
/* 18 */	"stmt: ASGNU1(VREGP,reg8)",
/* 19 */	"stmt: ASGNI2(VREGP,reg)",
/* 20 */	"stmt: ASGNU2(VREGP,reg)",
/* 21 */	"stmt: ASGNI4(VREGP,reg)",
/* 22 */	"stmt: ASGNU4(VREGP,reg)",
/* 23 */	"stmt: ASGNP2(VREGP,reg)",
/* 24 */	"stmt: ASGNF4(VREGP,reg)",
/* 25 */	"reg: CVFF4(reg)",
/* 26 */	"reg: CVFI2(reg)",
/* 27 */	"reg: CVFI4(reg)",
/* 28 */	"reg: CVIF4(reg)",
/* 29 */	"reg: CVII2(reg8)",
/* 30 */	"reg8: CVII2(reg8)",
/* 31 */	"reg: CVII4(reg)",
/* 32 */	"reg8: CVIU1(reg)",
/* 33 */	"reg: CVIU2(reg)",
/* 34 */	"reg: CVIU2(reg8)",
/* 35 */	"reg: CVII4(reg)",
/* 36 */	"reg: CVPU2(reg)",
/* 37 */	"reg8: CVUI1(reg)",
/* 38 */	"reg: CVUI2(reg)",
/* 39 */	"reg: CVUI2(reg8)",
/* 40 */	"reg: CVUI4(reg)",
/* 41 */	"reg: CVUP2(reg)",
/* 42 */	"reg: CVUU1(reg)",
/* 43 */	"reg8: CVUU1(reg)",
/* 44 */	"reg: CVUU2(reg)",
/* 45 */	"reg8: CVUU2(reg8)",
/* 46 */	"reg: CVUU4(reg)",
/* 47 */	"reg: con",
/* 48 */	"reg8: con",
/* 49 */	"c0: CNSTI2",
/* 50 */	"c1: CNSTI2",
/* 51 */	"c2: CNSTI2",
/* 52 */	"con1: CNSTI1",
/* 53 */	"con1: CNSTU1",
/* 54 */	"con2: CNSTI2",
/* 55 */	"con2: CNSTU2",
/* 56 */	"con4: CNSTI4",
/* 57 */	"con4: CNSTU4",
/* 58 */	"con4: CNSTP2",
/* 59 */	"con: con1",
/* 60 */	"con: con2",
/* 61 */	"con: con4",
/* 62 */	"con: c0",
/* 63 */	"con: c1",
/* 64 */	"con: c2",
/* 65 */	"reg: con1",
/* 66 */	"reg: con2",
/* 67 */	"reg: con4",
/* 68 */	"reg: ADDI2(reg,reg)",
/* 69 */	"reg: ADDI2(reg,con)",
/* 70 */	"reg: ADDI2(reg,INDIRI2(addr))",
/* 71 */	"reg: ADDU2(reg,reg)",
/* 72 */	"reg: ADDU2(reg,con)",
/* 73 */	"reg: ADDU2(reg,INDIRI2(addr))",
/* 74 */	"reg: ADDP2(reg,reg)",
/* 75 */	"reg: ADDP2(reg,con)",
/* 76 */	"reg: ADDP2(reg,INDIRI2(addr))",
/* 77 */	"reg8: ADDI2(reg8,reg8)",
/* 78 */	"reg8: ADDI2(reg8,con)",
/* 79 */	"reg8: ADDI2(reg8,CVII2(INDIRI1(addr)))",
/* 80 */	"reg8: ADDU2(reg8,reg8)",
/* 81 */	"reg8: ADDU2(reg8,con)",
/* 82 */	"reg8: ADDU2(reg8,CVUU2(INDIRU1(addr)))",
/* 83 */	"reg: ADDI4(reg,reg)",
/* 84 */	"reg: ADDI4(reg,INDIRI4(addr))",
/* 85 */	"reg: ADDU4(reg,reg)",
/* 86 */	"reg: ADDU4(reg,INDIRU4(addr))",
/* 87 */	"reg: ADDF4(reg,reg)",
/* 88 */	"reg: ADDF4(reg,INDIRF4(addr))",
/* 89 */	"reg: SUBI2(reg,reg)",
/* 90 */	"reg: SUBI2(reg,con)",
/* 91 */	"reg: SUBI2(reg,INDIRI2(addr))",
/* 92 */	"reg: SUBU2(reg,reg)",
/* 93 */	"reg: SUBU2(reg,con)",
/* 94 */	"reg: SUBU2(reg,INDIRI2(addr))",
/* 95 */	"reg: SUBP2(reg,reg)",
/* 96 */	"reg: SUBP2(reg,con)",
/* 97 */	"reg: SUBP2(reg,INDIRI2(addr))",
/* 98 */	"reg8: SUBI2(reg8,reg8)",
/* 99 */	"reg8: SUBI2(reg8,con)",
/* 100 */	"reg8: SUBI2(reg8,CVII2(INDIRI2(addr)))",
/* 101 */	"reg8: SUBU2(reg8,reg8)",
/* 102 */	"reg8: SUBU2(reg8,con)",
/* 103 */	"reg8: SUBU2(reg8,CVUU2(INDIRU2(addr)))",
/* 104 */	"reg: SUBI4(reg,reg)",
/* 105 */	"reg: SUBI4(reg,INDIRI4(addr))",
/* 106 */	"reg: SUBU4(reg,reg)",
/* 107 */	"reg: SUBU4(reg,INDIRU4(addr))",
/* 108 */	"reg: SUBF4(reg,reg)",
/* 109 */	"reg: SUBF4(reg,INDIRF4(addr))",
/* 110 */	"reg: BANDI2(reg,reg)",
/* 111 */	"reg: BANDI2(reg,con)",
/* 112 */	"reg: BANDI2(reg,INDIRI2(addr))",
/* 113 */	"reg: BANDU2(reg,reg)",
/* 114 */	"reg: BANDU2(reg,con)",
/* 115 */	"reg: BANDU2(reg,INDIRI2(addr))",
/* 116 */	"reg8: BANDI2(reg8,reg8)",
/* 117 */	"reg8: BANDI2(reg8,con)",
/* 118 */	"reg8: BANDI2(reg8,CVII2(INDIRI2(addr)))",
/* 119 */	"reg8: BANDU2(reg8,reg8)",
/* 120 */	"reg8: BANDU2(reg8,con)",
/* 121 */	"reg8: BANDU2(reg8,CVUU2(INDIRU2(addr)))",
/* 122 */	"reg: BANDI4(reg,reg)",
/* 123 */	"reg: BANDI4(reg,INDIRI4(addr))",
/* 124 */	"reg: BANDU4(reg,reg)",
/* 125 */	"reg: BANDU4(reg,INDIRU4(addr))",
/* 126 */	"reg: BORI2(reg,reg)",
/* 127 */	"reg: BORI2(reg,con)",
/* 128 */	"reg: BORI2(reg,INDIRI2(addr))",
/* 129 */	"reg: BORU2(reg,reg)",
/* 130 */	"reg: BORU2(reg,con)",
/* 131 */	"reg: BORU2(reg,INDIRI2(addr))",
/* 132 */	"reg8: BORI2(reg8,reg8)",
/* 133 */	"reg8: BORI2(reg8,con)",
/* 134 */	"reg8: BORI2(reg8,CVII2(INDIRI2(addr)))",
/* 135 */	"reg8: BORU2(reg8,reg8)",
/* 136 */	"reg8: BORU2(reg8,con)",
/* 137 */	"reg8: BORU2(reg8,CVUU2(INDIRU2(addr)))",
/* 138 */	"reg: BORI4(reg,reg)",
/* 139 */	"reg: BORI4(reg,INDIRI4(addr))",
/* 140 */	"reg: BORU4(reg,reg)",
/* 141 */	"reg: BORU4(reg,INDIRU4(addr))",
/* 142 */	"reg: BXORI2(reg,reg)",
/* 143 */	"reg: BXORU2(reg,reg)",
/* 144 */	"reg: BXORI4(reg,reg)",
/* 145 */	"reg: BXORI4(reg,INDIRI4(addr))",
/* 146 */	"reg: BXORU4(reg,reg)",
/* 147 */	"reg: BXORU4(reg,INDIRU4(addr))",
/* 148 */	"reg: MULI2(reg,reg)",
/* 149 */	"reg: MULU2(reg,reg)",
/* 150 */	"reg: MULI4(reg,reg)",
/* 151 */	"reg: MULI4(reg,INDIRI4(addr))",
/* 152 */	"reg: MULU4(reg,reg)",
/* 153 */	"reg: MULU4(reg,INDIRU4(addr))",
/* 154 */	"reg: MULF4(reg,reg)",
/* 155 */	"reg: MULU4(reg,INDIRU4(addr))",
/* 156 */	"reg: DIVI2(reg,reg)",
/* 157 */	"reg: DIVU2(reg,reg)",
/* 158 */	"reg: DIVI4(reg,reg)",
/* 159 */	"reg: DIVI4(reg,INDIRI4(addr))",
/* 160 */	"reg: DIVU4(reg,reg)",
/* 161 */	"reg: DIVU4(reg,INDIRU4(addr))",
/* 162 */	"reg: DIVF4(reg,reg)",
/* 163 */	"reg: DIVF4(reg,INDIRF4(addr))",
/* 164 */	"reg: MODI2(reg,reg)",
/* 165 */	"reg: MODU2(reg,reg)",
/* 166 */	"reg: MODI4(reg,reg)",
/* 167 */	"reg: MODI4(reg,INDIRI4(addr))",
/* 168 */	"reg: MODU4(reg,reg)",
/* 169 */	"reg: MODU4(reg,INDIRU4(addr))",
/* 170 */	"reg: NEGI2(reg)",
/* 171 */	"reg: NEGI4(reg)",
/* 172 */	"reg: NEGI4(INDIRI4(addr))",
/* 173 */	"reg: NEGF4(reg)",
/* 174 */	"reg: NEGF4(INDIRF4(addr))",
/* 175 */	"reg: LSHI2(reg,c1)",
/* 176 */	"reg: LSHI2(reg,c2)",
/* 177 */	"reg: LSHI2(reg,con)",
/* 178 */	"reg: LSHI2(reg,reg)",
/* 179 */	"reg: LSHU2(reg,c1)",
/* 180 */	"reg: LSHU2(reg,c2)",
/* 181 */	"reg: LSHU2(reg,con)",
/* 182 */	"reg: LSHU2(reg,reg)",
/* 183 */	"reg: LSHI4(reg,reg)",
/* 184 */	"reg: LSHI4(reg,INDIRI4(addr))",
/* 185 */	"reg: LSHU4(reg,reg)",
/* 186 */	"reg: LSHU4(reg,INDIRU4(addr))",
/* 187 */	"reg: RSHI2(reg,c1)",
/* 188 */	"reg: RSHI2(reg,c2)",
/* 189 */	"reg: RSHI2(reg,con)",
/* 190 */	"reg: RSHI2(reg,reg)",
/* 191 */	"reg: RSHU2(reg,c1)",
/* 192 */	"reg: RSHU2(reg,c2)",
/* 193 */	"reg: RSHU2(reg,con)",
/* 194 */	"reg: RSHU2(reg,reg)",
/* 195 */	"reg: RSHI4(reg,reg)",
/* 196 */	"reg: RSHI4(reg,INDIRI4(addr))",
/* 197 */	"reg: RSHU4(reg,reg)",
/* 198 */	"reg: RSHU4(reg,INDIRU4(addr))",
/* 199 */	"stmt: EQI2(reg,reg)",
/* 200 */	"stmt: EQI2(reg,con)",
/* 201 */	"stmt: EQI2(reg,INDIRI2(addr))",
/* 202 */	"stmt: EQU2(reg,reg)",
/* 203 */	"stmt: EQU2(reg,con)",
/* 204 */	"stmt: EQU2(reg,INDIRU2(addr))",
/* 205 */	"stmt: EQI2(reg8,reg8)",
/* 206 */	"stmt: EQI2(reg8,con)",
/* 207 */	"stmt: EQI2(reg8,CVII2(INDIRI1(addr)))",
/* 208 */	"stmt: EQU2(reg8,reg8)",
/* 209 */	"stmt: EQU2(reg8,con)",
/* 210 */	"stmt: EQU2(reg8,CVUU2(INDIRU1(addr)))",
/* 211 */	"stmt: EQI4(reg,reg)",
/* 212 */	"stmt: EQI4(reg,INDIRI4(addr))",
/* 213 */	"stmt: EQU4(reg,reg)",
/* 214 */	"stmt: EQU4(reg,INDIRU4(addr))",
/* 215 */	"stmt: EQF4(reg,reg)",
/* 216 */	"stmt: EQF4(reg,INDIRF4(addr))",
/* 217 */	"stmt: NEI2(reg,reg)",
/* 218 */	"stmt: NEI2(reg,con)",
/* 219 */	"stmt: NEI2(reg,INDIRI2(addr))",
/* 220 */	"stmt: NEU2(reg,reg)",
/* 221 */	"stmt: NEU2(reg,con)",
/* 222 */	"stmt: NEU2(reg,INDIRU2(addr))",
/* 223 */	"stmt: NEI2(reg8,reg8)",
/* 224 */	"stmt: NEI2(reg8,con)",
/* 225 */	"stmt: NEI2(reg8,CVII2(INDIRI1(addr)))",
/* 226 */	"stmt: NEU2(reg8,reg8)",
/* 227 */	"stmt: NEU2(reg8,con)",
/* 228 */	"stmt: NEU2(reg8,CVUU2(INDIRU1(addr)))",
/* 229 */	"stmt: NEI4(reg,reg)",
/* 230 */	"stmt: NEI4(reg,INDIRU4(addr))",
/* 231 */	"stmt: NEU4(reg,reg)",
/* 232 */	"stmt: NEU4(reg,INDIRU4(addr))",
/* 233 */	"stmt: NEF4(reg,reg)",
/* 234 */	"stmt: NEF4(reg,INDIRF4(addr))",
/* 235 */	"stmt: LTI2(reg,reg)",
/* 236 */	"stmt: LTI2(reg,con)",
/* 237 */	"stmt: LTI2(reg,INDIRI2(addr))",
/* 238 */	"stmt: LTU2(reg,reg)",
/* 239 */	"stmt: LTU2(reg,con)",
/* 240 */	"stmt: LTU2(reg,INDIRU2(addr))",
/* 241 */	"stmt: LTI2(reg8,reg8)",
/* 242 */	"stmt: LTI2(reg8,con)",
/* 243 */	"stmt: LTI2(reg8,CVII2(INDIRI1(addr)))",
/* 244 */	"stmt: LTU2(reg8,reg8)",
/* 245 */	"stmt: LTU2(reg8,con)",
/* 246 */	"stmt: LTU2(reg8,CVUU2(INDIRU1(addr)))",
/* 247 */	"stmt: LTI4(reg,reg)",
/* 248 */	"stmt: LTI4(reg,INDIRI4(addr))",
/* 249 */	"stmt: LTU4(reg,reg)",
/* 250 */	"stmt: LTU4(reg,INDIRU4(addr))",
/* 251 */	"stmt: LTF4(reg,reg)",
/* 252 */	"stmt: LTF4(reg,INDIRF4(addr))",
/* 253 */	"stmt: LEI2(reg,reg)",
/* 254 */	"stmt: LEI2(reg,con)",
/* 255 */	"stmt: LEI2(reg,INDIRI2(addr))",
/* 256 */	"stmt: LEU2(reg,reg)",
/* 257 */	"stmt: LEU2(reg,con)",
/* 258 */	"stmt: LEU2(reg,INDIRU2(addr))",
/* 259 */	"stmt: LEI2(reg8,reg8)",
/* 260 */	"stmt: LEI2(reg8,con)",
/* 261 */	"stmt: LEI2(reg8,CVII2(INDIRI1(addr)))",
/* 262 */	"stmt: LEU2(reg8,reg8)",
/* 263 */	"stmt: LEU2(reg8,con)",
/* 264 */	"stmt: LEU2(reg8,CVUU2(INDIRU1(addr)))",
/* 265 */	"stmt: LEI4(reg,reg)",
/* 266 */	"stmt: LEI4(reg,INDIRI4(addr))",
/* 267 */	"stmt: LEU4(reg,reg)",
/* 268 */	"stmt: LEU4(reg,INDIRU4(addr))",
/* 269 */	"stmt: LEF4(reg,reg)",
/* 270 */	"stmt: LEF4(reg,INDIRF4(addr))",
/* 271 */	"stmt: GTI2(reg,reg)",
/* 272 */	"stmt: GTI2(con,reg)",
/* 273 */	"stmt: GTI2(INDIRI2(addr),reg)",
/* 274 */	"stmt: GTU2(reg,reg)",
/* 275 */	"stmt: GTU2(con,reg)",
/* 276 */	"stmt: GTU2(INDIRU2(addr),reg)",
/* 277 */	"stmt: GTI2(reg8,reg8)",
/* 278 */	"stmt: GTI2(con,reg8)",
/* 279 */	"stmt: GTI2(CVII2(INDIRI1(addr)),reg8)",
/* 280 */	"stmt: GTU2(reg8,reg8)",
/* 281 */	"stmt: GTU2(con,reg8)",
/* 282 */	"stmt: GTU2(CVUU2(INDIRU1(addr)),reg8)",
/* 283 */	"stmt: GTI4(reg,reg)",
/* 284 */	"stmt: GTI4(INDIRI4(addr),reg)",
/* 285 */	"stmt: GTU4(reg,reg)",
/* 286 */	"stmt: GTU4(INDIRU4(addr),reg)",
/* 287 */	"stmt: GTF4(reg,reg)",
/* 288 */	"stmt: GTF4(INDIRF4(addr),reg)",
/* 289 */	"stmt: GEI2(reg,reg)",
/* 290 */	"stmt: GEI2(con,reg)",
/* 291 */	"stmt: GEI2(INDIRI2(addr),reg)",
/* 292 */	"stmt: GEU2(reg,reg)",
/* 293 */	"stmt: GEU2(con,reg)",
/* 294 */	"stmt: GEU2(INDIRU2(addr),reg)",
/* 295 */	"stmt: GEI2(reg8,reg8)",
/* 296 */	"stmt: GEI2(con,reg8)",
/* 297 */	"stmt: GEI2(CVII2(INDIRI1(addr)),reg8)",
/* 298 */	"stmt: GEU2(reg8,reg8)",
/* 299 */	"stmt: GEU2(con,reg8)",
/* 300 */	"stmt: GEU2(CVUU2(INDIRU1(addr)),reg8)",
/* 301 */	"stmt: GEI4(reg,reg)",
/* 302 */	"stmt: GEI4(INDIRI4(addr),reg)",
/* 303 */	"stmt: GEU4(reg,reg)",
/* 304 */	"stmt: GEU4(INDIRU4(addr),reg)",
/* 305 */	"stmt: GEF4(reg,reg)",
/* 306 */	"stmt: GEF4(INDIRF4(addr),reg)",
/* 307 */	"addr: ADDRGP2",
/* 308 */	"addr: ADDRGP2",
/* 309 */	"addr: ADDRLP2",
/* 310 */	"addr: ADDRFP2",
/* 311 */	"stmt: reg",
/* 312 */	"stmt: LABELV",
/* 313 */	"reg: ADDRGP2",
/* 314 */	"reg: ADDRGP2",
/* 315 */	"reg: ADDRLP2",
/* 316 */	"reg: ADDRFP2",
/* 317 */	"reg8: INDIRI1(reg)",
/* 318 */	"reg8: INDIRI1(addr)",
/* 319 */	"reg8: INDIRU1(reg)",
/* 320 */	"reg8: INDIRU1(addr)",
/* 321 */	"reg: INDIRI2(reg)",
/* 322 */	"reg: INDIRI2(addr)",
/* 323 */	"reg: INDIRU2(reg)",
/* 324 */	"reg: INDIRU2(addr)",
/* 325 */	"reg: INDIRP2(reg)",
/* 326 */	"reg: INDIRP2(addr)",
/* 327 */	"reg: INDIRI4(reg)",
/* 328 */	"reg: INDIRI4(addr)",
/* 329 */	"reg: INDIRU4(reg)",
/* 330 */	"reg: INDIRU4(addr)",
/* 331 */	"reg: INDIRF4(reg)",
/* 332 */	"reg: INDIRF4(addr)",
/* 333 */	"ar: reg",
/* 334 */	"ar: ADDRGP2",
/* 335 */	"reg: CALLI2(ar)",
/* 336 */	"reg: CALLU2(ar)",
/* 337 */	"reg: CALLP2(ar)",
/* 338 */	"reg: CALLI4(ar)",
/* 339 */	"reg: CALLU4(ar)",
/* 340 */	"reg: CALLF4(ar)",
/* 341 */	"stmt: CALLV(ar)",
/* 342 */	"stmt: CALLB(ar,reg)",
/* 343 */	"stmt: RETI2(reg)",
/* 344 */	"stmt: RETU2(reg)",
/* 345 */	"stmt: RETP2(reg)",
/* 346 */	"stmt: RETI4(reg)",
/* 347 */	"stmt: RETU4(reg)",
/* 348 */	"stmt: RETF4(reg)",
/* 349 */	"stmt: RETV(reg)",
/* 350 */	"stmt: ARGP2(reg)",
/* 351 */	"stmt: ARGI2(reg)",
/* 352 */	"stmt: ARGU2(reg)",
/* 353 */	"stmt: ARGI4(reg)",
/* 354 */	"stmt: ARGU4(reg)",
/* 355 */	"stmt: ARGF4(reg)",
/* 356 */	"stmt: JUMPV(ar)",
/* 357 */	"stmt: ASGNI1(reg,reg8)",
/* 358 */	"stmt: ASGNI1(addr,reg8)",
/* 359 */	"stmt: ASGNU1(reg,reg8)",
/* 360 */	"stmt: ASGNU1(addr,reg8)",
/* 361 */	"stmt: ASGNI2(reg,reg)",
/* 362 */	"stmt: ASGNI2(addr,reg)",
/* 363 */	"stmt: ASGNU2(reg,reg)",
/* 364 */	"stmt: ASGNU2(addr,reg)",
/* 365 */	"stmt: ASGNP2(reg,reg)",
/* 366 */	"stmt: ASGNP2(addr,reg)",
/* 367 */	"stmt: ASGNI4(reg,reg)",
/* 368 */	"stmt: ASGNI4(addr,reg)",
/* 369 */	"stmt: ASGNI4(addr,con4)",
/* 370 */	"stmt: ASGNI4(reg,con4)",
/* 371 */	"stmt: ASGNU4(reg,reg)",
/* 372 */	"stmt: ASGNU4(addr,reg)",
/* 373 */	"stmt: ASGNU4(addr,con4)",
/* 374 */	"stmt: ASGNU4(reg,con4)",
/* 375 */	"stmt: ASGNF4(reg,reg)",
/* 376 */	"stmt: ASGNF4(addr,reg)",
/* 377 */	"stmt: ASGNF4(addr,con4)",
/* 378 */	"stmt: ASGNF4(reg,con4)",
/* 379 */	"stmt: ASGNB(reg,INDIRB(reg))",
/* 380 */	"stmt: ARGB(INDIRB(reg))",
};

static short _decode_stmt[] = {
	0,
	17,
	18,
	19,
	20,
	21,
	22,
	23,
	24,
	199,
	200,
	201,
	202,
	203,
	204,
	205,
	206,
	207,
	208,
	209,
	210,
	211,
	212,
	213,
	214,
	215,
	216,
	217,
	218,
	219,
	220,
	221,
	222,
	223,
	224,
	225,
	226,
	227,
	228,
	229,
	230,
	231,
	232,
	233,
	234,
	235,
	236,
	237,
	238,
	239,
	240,
	241,
	242,
	243,
	244,
	245,
	246,
	247,
	248,
	249,
	250,
	251,
	252,
	253,
	254,
	255,
	256,
	257,
	258,
	259,
	260,
	261,
	262,
	263,
	264,
	265,
	266,
	267,
	268,
	269,
	270,
	271,
	272,
	273,
	274,
	275,
	276,
	277,
	278,
	279,
	280,
	281,
	282,
	283,
	284,
	285,
	286,
	287,
	288,
	289,
	290,
	291,
	292,
	293,
	294,
	295,
	296,
	297,
	298,
	299,
	300,
	301,
	302,
	303,
	304,
	305,
	306,
	311,
	312,
	341,
	342,
	343,
	344,
	345,
	346,
	347,
	348,
	349,
	350,
	351,
	352,
	353,
	354,
	355,
	356,
	357,
	358,
	359,
	360,
	361,
	362,
	363,
	364,
	365,
	366,
	367,
	368,
	369,
	370,
	371,
	372,
	373,
	374,
	375,
	376,
	377,
	378,
	379,
	380,
};

static short _decode_reg8[] = {
	0,
	1,
	2,
	9,
	10,
	30,
	32,
	37,
	43,
	45,
	48,
	77,
	78,
	79,
	80,
	81,
	82,
	98,
	99,
	100,
	101,
	102,
	103,
	116,
	117,
	118,
	119,
	120,
	121,
	132,
	133,
	134,
	135,
	136,
	137,
	317,
	318,
	319,
	320,
};

static short _decode_reg[] = {
	0,
	3,
	4,
	5,
	6,
	7,
	8,
	11,
	12,
	13,
	14,
	15,
	16,
	25,
	26,
	27,
	28,
	29,
	31,
	33,
	34,
	35,
	36,
	38,
	39,
	40,
	41,
	42,
	44,
	46,
	47,
	65,
	66,
	67,
	68,
	69,
	70,
	71,
	72,
	73,
	74,
	75,
	76,
	83,
	84,
	85,
	86,
	87,
	88,
	89,
	90,
	91,
	92,
	93,
	94,
	95,
	96,
	97,
	104,
	105,
	106,
	107,
	108,
	109,
	110,
	111,
	112,
	113,
	114,
	115,
	122,
	123,
	124,
	125,
	126,
	127,
	128,
	129,
	130,
	131,
	138,
	139,
	140,
	141,
	142,
	143,
	144,
	145,
	146,
	147,
	148,
	149,
	150,
	151,
	152,
	153,
	154,
	155,
	156,
	157,
	158,
	159,
	160,
	161,
	162,
	163,
	164,
	165,
	166,
	167,
	168,
	169,
	170,
	171,
	172,
	173,
	174,
	175,
	176,
	177,
	178,
	179,
	180,
	181,
	182,
	183,
	184,
	185,
	186,
	187,
	188,
	189,
	190,
	191,
	192,
	193,
	194,
	195,
	196,
	197,
	198,
	313,
	314,
	315,
	316,
	321,
	322,
	323,
	324,
	325,
	326,
	327,
	328,
	329,
	330,
	331,
	332,
	335,
	336,
	337,
	338,
	339,
	340,
};

static short _decode_con[] = {
	0,
	59,
	60,
	61,
	62,
	63,
	64,
};

static short _decode_c0[] = {
	0,
	49,
};

static short _decode_c1[] = {
	0,
	50,
};

static short _decode_c2[] = {
	0,
	51,
};

static short _decode_con1[] = {
	0,
	52,
	53,
};

static short _decode_con2[] = {
	0,
	54,
	55,
};

static short _decode_con4[] = {
	0,
	56,
	57,
	58,
};

static short _decode_addr[] = {
	0,
	307,
	308,
	309,
	310,
};

static short _decode_ar[] = {
	0,
	333,
	334,
};

static int _rule(void *state, int goalnt) {
	if (goalnt < 1 || goalnt > 12)
		fatal("_rule", "Bad goal nonterminal %d\n", goalnt);
	if (!state)
		return 0;
	switch (goalnt) {
	case _stmt_NT:	return _decode_stmt[((struct _state *)state)->rule._stmt];
	case _reg8_NT:	return _decode_reg8[((struct _state *)state)->rule._reg8];
	case _reg_NT:	return _decode_reg[((struct _state *)state)->rule._reg];
	case _con_NT:	return _decode_con[((struct _state *)state)->rule._con];
	case _c0_NT:	return _decode_c0[((struct _state *)state)->rule._c0];
	case _c1_NT:	return _decode_c1[((struct _state *)state)->rule._c1];
	case _c2_NT:	return _decode_c2[((struct _state *)state)->rule._c2];
	case _con1_NT:	return _decode_con1[((struct _state *)state)->rule._con1];
	case _con2_NT:	return _decode_con2[((struct _state *)state)->rule._con2];
	case _con4_NT:	return _decode_con4[((struct _state *)state)->rule._con4];
	case _addr_NT:	return _decode_addr[((struct _state *)state)->rule._addr];
	case _ar_NT:	return _decode_ar[((struct _state *)state)->rule._ar];
	default:
		fatal("_rule", "Bad goal nonterminal %d\n", goalnt);
		return 0;
	}
}

static void _closure_reg(NODEPTR_TYPE, int);
static void _closure_con(NODEPTR_TYPE, int);
static void _closure_c0(NODEPTR_TYPE, int);
static void _closure_c1(NODEPTR_TYPE, int);
static void _closure_c2(NODEPTR_TYPE, int);
static void _closure_con1(NODEPTR_TYPE, int);
static void _closure_con2(NODEPTR_TYPE, int);
static void _closure_con4(NODEPTR_TYPE, int);

static void _closure_reg(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 0 < p->cost[_ar_NT]) {
		p->cost[_ar_NT] = c + 0;
		p->rule._ar = 1;
	}
	if (c + 0 < p->cost[_stmt_NT]) {
		p->cost[_stmt_NT] = c + 0;
		p->rule._stmt = 117;
	}
}

static void _closure_con(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 1 < p->cost[_reg8_NT]) {
		p->cost[_reg8_NT] = c + 1;
		p->rule._reg8 = 10;
	}
	if (c + 1 < p->cost[_reg_NT]) {
		p->cost[_reg_NT] = c + 1;
		p->rule._reg = 30;
		_closure_reg(a, c + 1);
	}
}

static void _closure_c0(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 0 < p->cost[_con_NT]) {
		p->cost[_con_NT] = c + 0;
		p->rule._con = 4;
		_closure_con(a, c + 0);
	}
}

static void _closure_c1(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 0 < p->cost[_con_NT]) {
		p->cost[_con_NT] = c + 0;
		p->rule._con = 5;
		_closure_con(a, c + 0);
	}
}

static void _closure_c2(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 0 < p->cost[_con_NT]) {
		p->cost[_con_NT] = c + 0;
		p->rule._con = 6;
		_closure_con(a, c + 0);
	}
}

static void _closure_con1(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 1 < p->cost[_reg_NT]) {
		p->cost[_reg_NT] = c + 1;
		p->rule._reg = 31;
		_closure_reg(a, c + 1);
	}
	if (c + 0 < p->cost[_con_NT]) {
		p->cost[_con_NT] = c + 0;
		p->rule._con = 1;
		_closure_con(a, c + 0);
	}
}

static void _closure_con2(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 1 < p->cost[_reg_NT]) {
		p->cost[_reg_NT] = c + 1;
		p->rule._reg = 32;
		_closure_reg(a, c + 1);
	}
	if (c + 0 < p->cost[_con_NT]) {
		p->cost[_con_NT] = c + 0;
		p->rule._con = 2;
		_closure_con(a, c + 0);
	}
}

static void _closure_con4(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 2 < p->cost[_reg_NT]) {
		p->cost[_reg_NT] = c + 2;
		p->rule._reg = 33;
		_closure_reg(a, c + 2);
	}
	if (c + 0 < p->cost[_con_NT]) {
		p->cost[_con_NT] = c + 0;
		p->rule._con = 3;
		_closure_con(a, c + 0);
	}
}

static void _label(NODEPTR_TYPE a) {
	int c;
	struct _state *p;

	if (!a)
		fatal("_label", "Null tree\n", 0);
	STATE_LABEL(a) = p = allocate(sizeof *p, FUNC);
	p->rule._stmt = 0;
	p->cost[1] =
	p->cost[2] =
	p->cost[3] =
	p->cost[4] =
	p->cost[5] =
	p->cost[6] =
	p->cost[7] =
	p->cost[8] =
	p->cost[9] =
	p->cost[10] =
	p->cost[11] =
	p->cost[12] =
		0x7fff;
	switch (OP_LABEL(a)) {
	case 41: /* ARGB */
		_label(LEFT_CHILD(a));
		if (	/* stmt: ARGB(INDIRB(reg)) */
			LEFT_CHILD(a)->op == 73 /* INDIRB */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 158;
			}
		}
		break;
	case 57: /* ASGNB */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNB(reg,INDIRB(reg)) */
			RIGHT_CHILD(a)->op == 73 /* INDIRB */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 157;
			}
		}
		break;
	case 73: /* INDIRB */
		_label(LEFT_CHILD(a));
		break;
	case 216: /* CALLV */
		_label(LEFT_CHILD(a));
		/* stmt: CALLV(ar) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_ar_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 119;
		}
		break;
	case 217: /* CALLB */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: CALLB(ar,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_ar_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 120;
		}
		break;
	case 233: /* LOADB */
		break;
	case 248: /* RETV */
		_label(LEFT_CHILD(a));
		/* stmt: RETV(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 127;
		}
		break;
	case 584: /* JUMPV */
		_label(LEFT_CHILD(a));
		/* stmt: JUMPV(ar) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_ar_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 134;
		}
		break;
	case 600: /* LABELV */
		/* stmt: LABELV */
		if (0 + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = 0 + 0;
			p->rule._stmt = 118;
		}
		break;
	case 711: /* VREGP */
		break;
	case 1045: /* CNSTI1 */
		/* con1: CNSTI1 */
		if (0 + 0 < p->cost[_con1_NT]) {
			p->cost[_con1_NT] = 0 + 0;
			p->rule._con1 = 1;
			_closure_con1(a, 0 + 0);
		}
		break;
	case 1046: /* CNSTU1 */
		/* con1: CNSTU1 */
		if (0 + 0 < p->cost[_con1_NT]) {
			p->cost[_con1_NT] = 0 + 0;
			p->rule._con1 = 2;
			_closure_con1(a, 0 + 0);
		}
		break;
	case 1077: /* ASGNI1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNI1(VREGP,reg8) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 1;
			}
		}
		/* stmt: ASGNI1(reg,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 135;
		}
		/* stmt: ASGNI1(addr,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 136;
		}
		break;
	case 1078: /* ASGNU1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNU1(VREGP,reg8) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 2;
			}
		}
		/* stmt: ASGNU1(reg,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 137;
		}
		/* stmt: ASGNU1(addr,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 138;
		}
		break;
	case 1093: /* INDIRI1 */
		_label(LEFT_CHILD(a));
		if (	/* reg8: INDIRI1(VREGP) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			if (mayrecalc(a)) {
				struct _state *q = a->syms[RX]->u.t.cse->x.state;
				if (q->cost[_stmt_NT] == 0) {
					p->cost[_stmt_NT] = 0;
					p->rule._stmt = q->rule._stmt;
				}
				if (q->cost[_reg8_NT] == 0) {
					p->cost[_reg8_NT] = 0;
					p->rule._reg8 = q->rule._reg8;
				}
				if (q->cost[_reg_NT] == 0) {
					p->cost[_reg_NT] = 0;
					p->rule._reg = q->rule._reg;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_c0_NT] == 0) {
					p->cost[_c0_NT] = 0;
					p->rule._c0 = q->rule._c0;
				}
				if (q->cost[_c1_NT] == 0) {
					p->cost[_c1_NT] = 0;
					p->rule._c1 = q->rule._c1;
				}
				if (q->cost[_c2_NT] == 0) {
					p->cost[_c2_NT] = 0;
					p->rule._c2 = q->rule._c2;
				}
				if (q->cost[_con1_NT] == 0) {
					p->cost[_con1_NT] = 0;
					p->rule._con1 = q->rule._con1;
				}
				if (q->cost[_con2_NT] == 0) {
					p->cost[_con2_NT] = 0;
					p->rule._con2 = q->rule._con2;
				}
				if (q->cost[_con4_NT] == 0) {
					p->cost[_con4_NT] = 0;
					p->rule._con4 = q->rule._con4;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_ar_NT] == 0) {
					p->cost[_ar_NT] = 0;
					p->rule._ar = q->rule._ar;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 3;
			}
		}
		/* reg8: INDIRI1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 35;
		}
		/* reg8: INDIRI1(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 36;
		}
		break;
	case 1094: /* INDIRU1 */
		_label(LEFT_CHILD(a));
		if (	/* reg8: INDIRU1(VREGP) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			if (mayrecalc(a)) {
				struct _state *q = a->syms[RX]->u.t.cse->x.state;
				if (q->cost[_stmt_NT] == 0) {
					p->cost[_stmt_NT] = 0;
					p->rule._stmt = q->rule._stmt;
				}
				if (q->cost[_reg8_NT] == 0) {
					p->cost[_reg8_NT] = 0;
					p->rule._reg8 = q->rule._reg8;
				}
				if (q->cost[_reg_NT] == 0) {
					p->cost[_reg_NT] = 0;
					p->rule._reg = q->rule._reg;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_c0_NT] == 0) {
					p->cost[_c0_NT] = 0;
					p->rule._c0 = q->rule._c0;
				}
				if (q->cost[_c1_NT] == 0) {
					p->cost[_c1_NT] = 0;
					p->rule._c1 = q->rule._c1;
				}
				if (q->cost[_c2_NT] == 0) {
					p->cost[_c2_NT] = 0;
					p->rule._c2 = q->rule._c2;
				}
				if (q->cost[_con1_NT] == 0) {
					p->cost[_con1_NT] = 0;
					p->rule._con1 = q->rule._con1;
				}
				if (q->cost[_con2_NT] == 0) {
					p->cost[_con2_NT] = 0;
					p->rule._con2 = q->rule._con2;
				}
				if (q->cost[_con4_NT] == 0) {
					p->cost[_con4_NT] = 0;
					p->rule._con4 = q->rule._con4;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_ar_NT] == 0) {
					p->cost[_ar_NT] = 0;
					p->rule._ar = q->rule._ar;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 4;
			}
		}
		/* reg8: INDIRU1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 37;
		}
		/* reg8: INDIRU1(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 38;
		}
		break;
	case 1157: /* CVII1 */
		break;
	case 1158: /* CVIU1 */
		_label(LEFT_CHILD(a));
		/* reg8: CVIU1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 6;
		}
		break;
	case 1205: /* CVUI1 */
		_label(LEFT_CHILD(a));
		/* reg8: CVUI1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 7;
		}
		break;
	case 1206: /* CVUU1 */
		_label(LEFT_CHILD(a));
		/* reg: CVUU1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 27;
			_closure_reg(a, c + 0);
		}
		/* reg8: CVUU1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 8;
		}
		break;
	case 1253: /* LOADI1 */
		_label(LEFT_CHILD(a));
		/* reg8: LOADI1(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + (move(a));
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 1;
		}
		break;
	case 1254: /* LOADU1 */
		_label(LEFT_CHILD(a));
		/* reg8: LOADU1(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + (move(a));
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 2;
		}
		break;
	case 2069: /* CNSTI2 */
		/* c0: CNSTI2 */
		c = (range(a,0,0));
		if (c + 0 < p->cost[_c0_NT]) {
			p->cost[_c0_NT] = c + 0;
			p->rule._c0 = 1;
			_closure_c0(a, c + 0);
		}
		/* c1: CNSTI2 */
		c = (range(a,1,1));
		if (c + 0 < p->cost[_c1_NT]) {
			p->cost[_c1_NT] = c + 0;
			p->rule._c1 = 1;
			_closure_c1(a, c + 0);
		}
		/* c2: CNSTI2 */
		c = (range(a,2,2));
		if (c + 0 < p->cost[_c2_NT]) {
			p->cost[_c2_NT] = c + 0;
			p->rule._c2 = 1;
			_closure_c2(a, c + 0);
		}
		/* con2: CNSTI2 */
		if (0 + 0 < p->cost[_con2_NT]) {
			p->cost[_con2_NT] = 0 + 0;
			p->rule._con2 = 1;
			_closure_con2(a, 0 + 0);
		}
		break;
	case 2070: /* CNSTU2 */
		/* con2: CNSTU2 */
		if (0 + 0 < p->cost[_con2_NT]) {
			p->cost[_con2_NT] = 0 + 0;
			p->rule._con2 = 2;
			_closure_con2(a, 0 + 0);
		}
		break;
	case 2071: /* CNSTP2 */
		/* con4: CNSTP2 */
		if (0 + 0 < p->cost[_con4_NT]) {
			p->cost[_con4_NT] = 0 + 0;
			p->rule._con4 = 3;
			_closure_con4(a, 0 + 0);
		}
		break;
	case 2085: /* ARGI2 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 129;
		}
		break;
	case 2086: /* ARGU2 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 130;
		}
		break;
	case 2087: /* ARGP2 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGP2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 128;
		}
		break;
	case 2101: /* ASGNI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNI2(VREGP,reg) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 3;
			}
		}
		/* stmt: ASGNI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 139;
		}
		/* stmt: ASGNI2(addr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 140;
		}
		break;
	case 2102: /* ASGNU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNU2(VREGP,reg) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 4;
			}
		}
		/* stmt: ASGNU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 141;
		}
		/* stmt: ASGNU2(addr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 142;
		}
		break;
	case 2103: /* ASGNP2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNP2(VREGP,reg) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 7;
			}
		}
		/* stmt: ASGNP2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 143;
		}
		/* stmt: ASGNP2(addr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 144;
		}
		break;
	case 2117: /* INDIRI2 */
		_label(LEFT_CHILD(a));
		if (	/* reg: INDIRI2(VREGP) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			if (mayrecalc(a)) {
				struct _state *q = a->syms[RX]->u.t.cse->x.state;
				if (q->cost[_stmt_NT] == 0) {
					p->cost[_stmt_NT] = 0;
					p->rule._stmt = q->rule._stmt;
				}
				if (q->cost[_reg8_NT] == 0) {
					p->cost[_reg8_NT] = 0;
					p->rule._reg8 = q->rule._reg8;
				}
				if (q->cost[_reg_NT] == 0) {
					p->cost[_reg_NT] = 0;
					p->rule._reg = q->rule._reg;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_c0_NT] == 0) {
					p->cost[_c0_NT] = 0;
					p->rule._c0 = q->rule._c0;
				}
				if (q->cost[_c1_NT] == 0) {
					p->cost[_c1_NT] = 0;
					p->rule._c1 = q->rule._c1;
				}
				if (q->cost[_c2_NT] == 0) {
					p->cost[_c2_NT] = 0;
					p->rule._c2 = q->rule._c2;
				}
				if (q->cost[_con1_NT] == 0) {
					p->cost[_con1_NT] = 0;
					p->rule._con1 = q->rule._con1;
				}
				if (q->cost[_con2_NT] == 0) {
					p->cost[_con2_NT] = 0;
					p->rule._con2 = q->rule._con2;
				}
				if (q->cost[_con4_NT] == 0) {
					p->cost[_con4_NT] = 0;
					p->rule._con4 = q->rule._con4;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_ar_NT] == 0) {
					p->cost[_ar_NT] = 0;
					p->rule._ar = q->rule._ar;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 7;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: INDIRI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 145;
			_closure_reg(a, c + 0);
		}
		/* reg: INDIRI2(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 146;
			_closure_reg(a, c + 0);
		}
		break;
	case 2118: /* INDIRU2 */
		_label(LEFT_CHILD(a));
		if (	/* reg: INDIRU2(VREGP) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			if (mayrecalc(a)) {
				struct _state *q = a->syms[RX]->u.t.cse->x.state;
				if (q->cost[_stmt_NT] == 0) {
					p->cost[_stmt_NT] = 0;
					p->rule._stmt = q->rule._stmt;
				}
				if (q->cost[_reg8_NT] == 0) {
					p->cost[_reg8_NT] = 0;
					p->rule._reg8 = q->rule._reg8;
				}
				if (q->cost[_reg_NT] == 0) {
					p->cost[_reg_NT] = 0;
					p->rule._reg = q->rule._reg;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_c0_NT] == 0) {
					p->cost[_c0_NT] = 0;
					p->rule._c0 = q->rule._c0;
				}
				if (q->cost[_c1_NT] == 0) {
					p->cost[_c1_NT] = 0;
					p->rule._c1 = q->rule._c1;
				}
				if (q->cost[_c2_NT] == 0) {
					p->cost[_c2_NT] = 0;
					p->rule._c2 = q->rule._c2;
				}
				if (q->cost[_con1_NT] == 0) {
					p->cost[_con1_NT] = 0;
					p->rule._con1 = q->rule._con1;
				}
				if (q->cost[_con2_NT] == 0) {
					p->cost[_con2_NT] = 0;
					p->rule._con2 = q->rule._con2;
				}
				if (q->cost[_con4_NT] == 0) {
					p->cost[_con4_NT] = 0;
					p->rule._con4 = q->rule._con4;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_ar_NT] == 0) {
					p->cost[_ar_NT] = 0;
					p->rule._ar = q->rule._ar;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 8;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: INDIRU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 147;
			_closure_reg(a, c + 0);
		}
		/* reg: INDIRU2(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 148;
			_closure_reg(a, c + 0);
		}
		break;
	case 2119: /* INDIRP2 */
		_label(LEFT_CHILD(a));
		if (	/* reg: INDIRP2(VREGP) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			if (mayrecalc(a)) {
				struct _state *q = a->syms[RX]->u.t.cse->x.state;
				if (q->cost[_stmt_NT] == 0) {
					p->cost[_stmt_NT] = 0;
					p->rule._stmt = q->rule._stmt;
				}
				if (q->cost[_reg8_NT] == 0) {
					p->cost[_reg8_NT] = 0;
					p->rule._reg8 = q->rule._reg8;
				}
				if (q->cost[_reg_NT] == 0) {
					p->cost[_reg_NT] = 0;
					p->rule._reg = q->rule._reg;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_c0_NT] == 0) {
					p->cost[_c0_NT] = 0;
					p->rule._c0 = q->rule._c0;
				}
				if (q->cost[_c1_NT] == 0) {
					p->cost[_c1_NT] = 0;
					p->rule._c1 = q->rule._c1;
				}
				if (q->cost[_c2_NT] == 0) {
					p->cost[_c2_NT] = 0;
					p->rule._c2 = q->rule._c2;
				}
				if (q->cost[_con1_NT] == 0) {
					p->cost[_con1_NT] = 0;
					p->rule._con1 = q->rule._con1;
				}
				if (q->cost[_con2_NT] == 0) {
					p->cost[_con2_NT] = 0;
					p->rule._con2 = q->rule._con2;
				}
				if (q->cost[_con4_NT] == 0) {
					p->cost[_con4_NT] = 0;
					p->rule._con4 = q->rule._con4;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_ar_NT] == 0) {
					p->cost[_ar_NT] = 0;
					p->rule._ar = q->rule._ar;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 11;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: INDIRP2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 149;
			_closure_reg(a, c + 0);
		}
		/* reg: INDIRP2(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 150;
			_closure_reg(a, c + 0);
		}
		break;
	case 2165: /* CVFI2 */
		_label(LEFT_CHILD(a));
		/* reg: CVFI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 14;
			_closure_reg(a, c + 0);
		}
		break;
	case 2181: /* CVII2 */
		_label(LEFT_CHILD(a));
		/* reg: CVII2(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 17;
			_closure_reg(a, c + 0);
		}
		/* reg8: CVII2(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + (move(a));
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 5;
		}
		break;
	case 2182: /* CVIU2 */
		_label(LEFT_CHILD(a));
		/* reg: CVIU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 19;
			_closure_reg(a, c + 0);
		}
		/* reg: CVIU2(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 20;
			_closure_reg(a, c + 0);
		}
		break;
	case 2198: /* CVPU2 */
		_label(LEFT_CHILD(a));
		/* reg: CVPU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 22;
			_closure_reg(a, c + 0);
		}
		break;
	case 2229: /* CVUI2 */
		_label(LEFT_CHILD(a));
		/* reg: CVUI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 23;
			_closure_reg(a, c + 0);
		}
		/* reg: CVUI2(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 24;
			_closure_reg(a, c + 0);
		}
		break;
	case 2230: /* CVUU2 */
		_label(LEFT_CHILD(a));
		/* reg: CVUU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 28;
			_closure_reg(a, c + 0);
		}
		/* reg8: CVUU2(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + (move(a));
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 9;
		}
		break;
	case 2231: /* CVUP2 */
		_label(LEFT_CHILD(a));
		/* reg: CVUP2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 26;
			_closure_reg(a, c + 0);
		}
		break;
	case 2245: /* NEGI2 */
		_label(LEFT_CHILD(a));
		/* reg: NEGI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 112;
			_closure_reg(a, c + 0);
		}
		break;
	case 2261: /* CALLI2 */
		_label(LEFT_CHILD(a));
		/* reg: CALLI2(ar) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_ar_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 157;
			_closure_reg(a, c + 0);
		}
		break;
	case 2262: /* CALLU2 */
		_label(LEFT_CHILD(a));
		/* reg: CALLU2(ar) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_ar_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 158;
			_closure_reg(a, c + 0);
		}
		break;
	case 2263: /* CALLP2 */
		_label(LEFT_CHILD(a));
		/* reg: CALLP2(ar) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_ar_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 159;
			_closure_reg(a, c + 0);
		}
		break;
	case 2277: /* LOADI2 */
		_label(LEFT_CHILD(a));
		/* reg: LOADI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 1;
			_closure_reg(a, c + 0);
		}
		break;
	case 2278: /* LOADU2 */
		_label(LEFT_CHILD(a));
		/* reg: LOADU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 2;
			_closure_reg(a, c + 0);
		}
		break;
	case 2279: /* LOADP2 */
		_label(LEFT_CHILD(a));
		/* reg: LOADP2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 3;
			_closure_reg(a, c + 0);
		}
		break;
	case 2293: /* RETI2 */
		_label(LEFT_CHILD(a));
		/* stmt: RETI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 121;
		}
		break;
	case 2294: /* RETU2 */
		_label(LEFT_CHILD(a));
		/* stmt: RETU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 122;
		}
		break;
	case 2295: /* RETP2 */
		_label(LEFT_CHILD(a));
		/* stmt: RETP2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 123;
		}
		break;
	case 2311: /* ADDRGP2 */
		/* addr: ADDRGP2 */
		c = (isfptr(a,0,LBURG_MAX));
		if (c + 0 < p->cost[_addr_NT]) {
			p->cost[_addr_NT] = c + 0;
			p->rule._addr = 1;
		}
		/* addr: ADDRGP2 */
		c = (isfptr(a,LBURG_MAX,0));
		if (c + 0 < p->cost[_addr_NT]) {
			p->cost[_addr_NT] = c + 0;
			p->rule._addr = 2;
		}
		/* reg: ADDRGP2 */
		c = (isfptr(a,1,LBURG_MAX));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 141;
			_closure_reg(a, c + 0);
		}
		/* reg: ADDRGP2 */
		c = (isfptr(a,LBURG_MAX,1));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 142;
			_closure_reg(a, c + 0);
		}
		/* ar: ADDRGP2 */
		if (0 + 0 < p->cost[_ar_NT]) {
			p->cost[_ar_NT] = 0 + 0;
			p->rule._ar = 2;
		}
		break;
	case 2327: /* ADDRFP2 */
		/* addr: ADDRFP2 */
		if (0 + 0 < p->cost[_addr_NT]) {
			p->cost[_addr_NT] = 0 + 0;
			p->rule._addr = 4;
		}
		/* reg: ADDRFP2 */
		if (1 + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = 1 + 0;
			p->rule._reg = 144;
			_closure_reg(a, 1 + 0);
		}
		break;
	case 2343: /* ADDRLP2 */
		/* addr: ADDRLP2 */
		if (0 + 0 < p->cost[_addr_NT]) {
			p->cost[_addr_NT] = 0 + 0;
			p->rule._addr = 3;
		}
		/* reg: ADDRLP2 */
		if (1 + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = 1 + 0;
			p->rule._reg = 143;
			_closure_reg(a, 1 + 0);
		}
		break;
	case 2357: /* ADDI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: ADDI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 34;
			_closure_reg(a, c + 0);
		}
		/* reg: ADDI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 35;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: ADDI2(reg,INDIRI2(addr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 36;
				_closure_reg(a, c + 0);
			}
		}
		/* reg8: ADDI2(reg8,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 2;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 11;
		}
		/* reg8: ADDI2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 12;
		}
		if (	/* reg8: ADDI2(reg8,CVII2(INDIRI1(addr))) */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 13;
			}
		}
		break;
	case 2358: /* ADDU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: ADDU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 37;
			_closure_reg(a, c + 0);
		}
		/* reg: ADDU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 38;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: ADDU2(reg,INDIRI2(addr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 39;
				_closure_reg(a, c + 0);
			}
		}
		/* reg8: ADDU2(reg8,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 2;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 14;
		}
		/* reg8: ADDU2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 15;
		}
		if (	/* reg8: ADDU2(reg8,CVUU2(INDIRU1(addr))) */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 16;
			}
		}
		break;
	case 2359: /* ADDP2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: ADDP2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 40;
			_closure_reg(a, c + 0);
		}
		/* reg: ADDP2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 41;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: ADDP2(reg,INDIRI2(addr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 42;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 2373: /* SUBI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: SUBI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 49;
			_closure_reg(a, c + 0);
		}
		/* reg: SUBI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 50;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: SUBI2(reg,INDIRI2(addr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 51;
				_closure_reg(a, c + 0);
			}
		}
		/* reg8: SUBI2(reg8,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 2;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 17;
		}
		/* reg8: SUBI2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 18;
		}
		if (	/* reg8: SUBI2(reg8,CVII2(INDIRI2(addr))) */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 19;
			}
		}
		break;
	case 2374: /* SUBU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: SUBU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 52;
			_closure_reg(a, c + 0);
		}
		/* reg: SUBU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 53;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: SUBU2(reg,INDIRI2(addr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 54;
				_closure_reg(a, c + 0);
			}
		}
		/* reg8: SUBU2(reg8,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 2;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 20;
		}
		/* reg8: SUBU2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 21;
		}
		if (	/* reg8: SUBU2(reg8,CVUU2(INDIRU2(addr))) */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 22;
			}
		}
		break;
	case 2375: /* SUBP2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: SUBP2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 55;
			_closure_reg(a, c + 0);
		}
		/* reg: SUBP2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 56;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: SUBP2(reg,INDIRI2(addr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 57;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 2389: /* LSHI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: LSHI2(reg,c1) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_c1_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 117;
			_closure_reg(a, c + 0);
		}
		/* reg: LSHI2(reg,c2) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_c2_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 118;
			_closure_reg(a, c + 0);
		}
		/* reg: LSHI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 119;
			_closure_reg(a, c + 0);
		}
		/* reg: LSHI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 120;
			_closure_reg(a, c + 0);
		}
		break;
	case 2390: /* LSHU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: LSHU2(reg,c1) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_c1_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 121;
			_closure_reg(a, c + 0);
		}
		/* reg: LSHU2(reg,c2) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_c2_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 122;
			_closure_reg(a, c + 0);
		}
		/* reg: LSHU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 123;
			_closure_reg(a, c + 0);
		}
		/* reg: LSHU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 124;
			_closure_reg(a, c + 0);
		}
		break;
	case 2405: /* MODI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MODI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 106;
			_closure_reg(a, c + 0);
		}
		break;
	case 2406: /* MODU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MODU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 107;
			_closure_reg(a, c + 0);
		}
		break;
	case 2421: /* RSHI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: RSHI2(reg,c1) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_c1_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 129;
			_closure_reg(a, c + 0);
		}
		/* reg: RSHI2(reg,c2) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_c2_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 130;
			_closure_reg(a, c + 0);
		}
		/* reg: RSHI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 131;
			_closure_reg(a, c + 0);
		}
		/* reg: RSHI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 132;
			_closure_reg(a, c + 0);
		}
		break;
	case 2422: /* RSHU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: RSHU2(reg,c1) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_c1_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 133;
			_closure_reg(a, c + 0);
		}
		/* reg: RSHU2(reg,c2) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_c2_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 134;
			_closure_reg(a, c + 0);
		}
		/* reg: RSHU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 135;
			_closure_reg(a, c + 0);
		}
		/* reg: RSHU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 136;
			_closure_reg(a, c + 0);
		}
		break;
	case 2437: /* BANDI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BANDI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 64;
			_closure_reg(a, c + 0);
		}
		/* reg: BANDI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 65;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: BANDI2(reg,INDIRI2(addr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 66;
				_closure_reg(a, c + 0);
			}
		}
		/* reg8: BANDI2(reg8,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 2;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 23;
		}
		/* reg8: BANDI2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 24;
		}
		if (	/* reg8: BANDI2(reg8,CVII2(INDIRI2(addr))) */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 25;
			}
		}
		break;
	case 2438: /* BANDU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BANDU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 67;
			_closure_reg(a, c + 0);
		}
		/* reg: BANDU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 68;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: BANDU2(reg,INDIRI2(addr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 69;
				_closure_reg(a, c + 0);
			}
		}
		/* reg8: BANDU2(reg8,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 2;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 26;
		}
		/* reg8: BANDU2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 27;
		}
		if (	/* reg8: BANDU2(reg8,CVUU2(INDIRU2(addr))) */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 28;
			}
		}
		break;
	case 2453: /* BCOMI2 */
		break;
	case 2454: /* BCOMU2 */
		break;
	case 2469: /* BORI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BORI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 74;
			_closure_reg(a, c + 0);
		}
		/* reg: BORI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 75;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: BORI2(reg,INDIRI2(addr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 76;
				_closure_reg(a, c + 0);
			}
		}
		/* reg8: BORI2(reg8,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 2;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 29;
		}
		/* reg8: BORI2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 30;
		}
		if (	/* reg8: BORI2(reg8,CVII2(INDIRI2(addr))) */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 31;
			}
		}
		break;
	case 2470: /* BORU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BORU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 77;
			_closure_reg(a, c + 0);
		}
		/* reg: BORU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 78;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: BORU2(reg,INDIRI2(addr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 79;
				_closure_reg(a, c + 0);
			}
		}
		/* reg8: BORU2(reg8,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 2;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 32;
		}
		/* reg8: BORU2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 33;
		}
		if (	/* reg8: BORU2(reg8,CVUU2(INDIRU2(addr))) */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 34;
			}
		}
		break;
	case 2485: /* BXORI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BXORI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 84;
			_closure_reg(a, c + 0);
		}
		break;
	case 2486: /* BXORU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BXORU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 85;
			_closure_reg(a, c + 0);
		}
		break;
	case 2501: /* DIVI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: DIVI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 98;
			_closure_reg(a, c + 0);
		}
		break;
	case 2502: /* DIVU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: DIVU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 99;
			_closure_reg(a, c + 0);
		}
		break;
	case 2517: /* MULI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MULI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 90;
			_closure_reg(a, c + 0);
		}
		break;
	case 2518: /* MULU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MULU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 91;
			_closure_reg(a, c + 0);
		}
		break;
	case 2533: /* EQI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: EQI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 9;
		}
		/* stmt: EQI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 10;
		}
		if (	/* stmt: EQI2(reg,INDIRI2(addr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 11;
			}
		}
		/* stmt: EQI2(reg8,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 15;
		}
		/* stmt: EQI2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 16;
		}
		if (	/* stmt: EQI2(reg8,CVII2(INDIRI1(addr))) */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 17;
			}
		}
		break;
	case 2534: /* EQU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: EQU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 12;
		}
		/* stmt: EQU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 13;
		}
		if (	/* stmt: EQU2(reg,INDIRU2(addr)) */
			RIGHT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 14;
			}
		}
		/* stmt: EQU2(reg8,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 18;
		}
		/* stmt: EQU2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 19;
		}
		if (	/* stmt: EQU2(reg8,CVUU2(INDIRU1(addr))) */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 20;
			}
		}
		break;
	case 2549: /* GEI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GEI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 99;
		}
		/* stmt: GEI2(con,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_con_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 100;
		}
		if (	/* stmt: GEI2(INDIRI2(addr),reg) */
			LEFT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 101;
			}
		}
		/* stmt: GEI2(reg8,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 105;
		}
		/* stmt: GEI2(con,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_con_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 106;
		}
		if (	/* stmt: GEI2(CVII2(INDIRI1(addr)),reg8) */
			LEFT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(LEFT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(LEFT_CHILD(a)))->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 107;
			}
		}
		break;
	case 2550: /* GEU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GEU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 102;
		}
		/* stmt: GEU2(con,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_con_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 103;
		}
		if (	/* stmt: GEU2(INDIRU2(addr),reg) */
			LEFT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 104;
			}
		}
		/* stmt: GEU2(reg8,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 108;
		}
		/* stmt: GEU2(con,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_con_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 109;
		}
		if (	/* stmt: GEU2(CVUU2(INDIRU1(addr)),reg8) */
			LEFT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(LEFT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(LEFT_CHILD(a)))->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 110;
			}
		}
		break;
	case 2565: /* GTI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GTI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 81;
		}
		/* stmt: GTI2(con,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_con_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 82;
		}
		if (	/* stmt: GTI2(INDIRI2(addr),reg) */
			LEFT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 83;
			}
		}
		/* stmt: GTI2(reg8,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 87;
		}
		/* stmt: GTI2(con,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_con_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 88;
		}
		if (	/* stmt: GTI2(CVII2(INDIRI1(addr)),reg8) */
			LEFT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(LEFT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(LEFT_CHILD(a)))->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 89;
			}
		}
		break;
	case 2566: /* GTU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GTU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 84;
		}
		/* stmt: GTU2(con,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_con_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 85;
		}
		if (	/* stmt: GTU2(INDIRU2(addr),reg) */
			LEFT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 86;
			}
		}
		/* stmt: GTU2(reg8,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 90;
		}
		/* stmt: GTU2(con,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_con_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 91;
		}
		if (	/* stmt: GTU2(CVUU2(INDIRU1(addr)),reg8) */
			LEFT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(LEFT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(LEFT_CHILD(a)))->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 92;
			}
		}
		break;
	case 2581: /* LEI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LEI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 63;
		}
		/* stmt: LEI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 64;
		}
		if (	/* stmt: LEI2(reg,INDIRI2(addr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 65;
			}
		}
		/* stmt: LEI2(reg8,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 69;
		}
		/* stmt: LEI2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 70;
		}
		if (	/* stmt: LEI2(reg8,CVII2(INDIRI1(addr))) */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 71;
			}
		}
		break;
	case 2582: /* LEU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LEU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 66;
		}
		/* stmt: LEU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 67;
		}
		if (	/* stmt: LEU2(reg,INDIRU2(addr)) */
			RIGHT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 68;
			}
		}
		/* stmt: LEU2(reg8,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 72;
		}
		/* stmt: LEU2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 73;
		}
		if (	/* stmt: LEU2(reg8,CVUU2(INDIRU1(addr))) */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 74;
			}
		}
		break;
	case 2597: /* LTI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LTI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 45;
		}
		/* stmt: LTI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 46;
		}
		if (	/* stmt: LTI2(reg,INDIRI2(addr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 47;
			}
		}
		/* stmt: LTI2(reg8,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 51;
		}
		/* stmt: LTI2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 52;
		}
		if (	/* stmt: LTI2(reg8,CVII2(INDIRI1(addr))) */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 53;
			}
		}
		break;
	case 2598: /* LTU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LTU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 48;
		}
		/* stmt: LTU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 49;
		}
		if (	/* stmt: LTU2(reg,INDIRU2(addr)) */
			RIGHT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 50;
			}
		}
		/* stmt: LTU2(reg8,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 54;
		}
		/* stmt: LTU2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 55;
		}
		if (	/* stmt: LTU2(reg8,CVUU2(INDIRU1(addr))) */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 56;
			}
		}
		break;
	case 2613: /* NEI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: NEI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 27;
		}
		/* stmt: NEI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 28;
		}
		if (	/* stmt: NEI2(reg,INDIRI2(addr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 29;
			}
		}
		/* stmt: NEI2(reg8,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 33;
		}
		/* stmt: NEI2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 34;
		}
		if (	/* stmt: NEI2(reg8,CVII2(INDIRI1(addr))) */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 35;
			}
		}
		break;
	case 2614: /* NEU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: NEU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 30;
		}
		/* stmt: NEU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 31;
		}
		if (	/* stmt: NEU2(reg,INDIRU2(addr)) */
			RIGHT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 32;
			}
		}
		/* stmt: NEU2(reg8,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 36;
		}
		/* stmt: NEU2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 37;
		}
		if (	/* stmt: NEU2(reg8,CVUU2(INDIRU1(addr))) */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 38;
			}
		}
		break;
	case 4113: /* CNSTF4 */
		break;
	case 4117: /* CNSTI4 */
		/* con4: CNSTI4 */
		if (0 + 0 < p->cost[_con4_NT]) {
			p->cost[_con4_NT] = 0 + 0;
			p->rule._con4 = 1;
			_closure_con4(a, 0 + 0);
		}
		break;
	case 4118: /* CNSTU4 */
		/* con4: CNSTU4 */
		if (0 + 0 < p->cost[_con4_NT]) {
			p->cost[_con4_NT] = 0 + 0;
			p->rule._con4 = 2;
			_closure_con4(a, 0 + 0);
		}
		break;
	case 4129: /* ARGF4 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGF4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 133;
		}
		break;
	case 4133: /* ARGI4 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGI4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 131;
		}
		break;
	case 4134: /* ARGU4 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGU4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 132;
		}
		break;
	case 4145: /* ASGNF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNF4(VREGP,reg) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 8;
			}
		}
		/* stmt: ASGNF4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 153;
		}
		/* stmt: ASGNF4(addr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 154;
		}
		/* stmt: ASGNF4(addr,con4) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con4_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 155;
		}
		/* stmt: ASGNF4(reg,con4) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con4_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 156;
		}
		break;
	case 4149: /* ASGNI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNI4(VREGP,reg) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 5;
			}
		}
		/* stmt: ASGNI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 145;
		}
		/* stmt: ASGNI4(addr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 146;
		}
		/* stmt: ASGNI4(addr,con4) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con4_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 147;
		}
		/* stmt: ASGNI4(reg,con4) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con4_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 148;
		}
		break;
	case 4150: /* ASGNU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNU4(VREGP,reg) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 6;
			}
		}
		/* stmt: ASGNU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 149;
		}
		/* stmt: ASGNU4(addr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 150;
		}
		/* stmt: ASGNU4(addr,con4) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con4_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 151;
		}
		/* stmt: ASGNU4(reg,con4) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con4_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 152;
		}
		break;
	case 4161: /* INDIRF4 */
		_label(LEFT_CHILD(a));
		if (	/* reg: INDIRF4(VREGP) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			if (mayrecalc(a)) {
				struct _state *q = a->syms[RX]->u.t.cse->x.state;
				if (q->cost[_stmt_NT] == 0) {
					p->cost[_stmt_NT] = 0;
					p->rule._stmt = q->rule._stmt;
				}
				if (q->cost[_reg8_NT] == 0) {
					p->cost[_reg8_NT] = 0;
					p->rule._reg8 = q->rule._reg8;
				}
				if (q->cost[_reg_NT] == 0) {
					p->cost[_reg_NT] = 0;
					p->rule._reg = q->rule._reg;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_c0_NT] == 0) {
					p->cost[_c0_NT] = 0;
					p->rule._c0 = q->rule._c0;
				}
				if (q->cost[_c1_NT] == 0) {
					p->cost[_c1_NT] = 0;
					p->rule._c1 = q->rule._c1;
				}
				if (q->cost[_c2_NT] == 0) {
					p->cost[_c2_NT] = 0;
					p->rule._c2 = q->rule._c2;
				}
				if (q->cost[_con1_NT] == 0) {
					p->cost[_con1_NT] = 0;
					p->rule._con1 = q->rule._con1;
				}
				if (q->cost[_con2_NT] == 0) {
					p->cost[_con2_NT] = 0;
					p->rule._con2 = q->rule._con2;
				}
				if (q->cost[_con4_NT] == 0) {
					p->cost[_con4_NT] = 0;
					p->rule._con4 = q->rule._con4;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_ar_NT] == 0) {
					p->cost[_ar_NT] = 0;
					p->rule._ar = q->rule._ar;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 12;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: INDIRF4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 155;
			_closure_reg(a, c + 0);
		}
		/* reg: INDIRF4(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 156;
			_closure_reg(a, c + 0);
		}
		break;
	case 4165: /* INDIRI4 */
		_label(LEFT_CHILD(a));
		if (	/* reg: INDIRI4(VREGP) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			if (mayrecalc(a)) {
				struct _state *q = a->syms[RX]->u.t.cse->x.state;
				if (q->cost[_stmt_NT] == 0) {
					p->cost[_stmt_NT] = 0;
					p->rule._stmt = q->rule._stmt;
				}
				if (q->cost[_reg8_NT] == 0) {
					p->cost[_reg8_NT] = 0;
					p->rule._reg8 = q->rule._reg8;
				}
				if (q->cost[_reg_NT] == 0) {
					p->cost[_reg_NT] = 0;
					p->rule._reg = q->rule._reg;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_c0_NT] == 0) {
					p->cost[_c0_NT] = 0;
					p->rule._c0 = q->rule._c0;
				}
				if (q->cost[_c1_NT] == 0) {
					p->cost[_c1_NT] = 0;
					p->rule._c1 = q->rule._c1;
				}
				if (q->cost[_c2_NT] == 0) {
					p->cost[_c2_NT] = 0;
					p->rule._c2 = q->rule._c2;
				}
				if (q->cost[_con1_NT] == 0) {
					p->cost[_con1_NT] = 0;
					p->rule._con1 = q->rule._con1;
				}
				if (q->cost[_con2_NT] == 0) {
					p->cost[_con2_NT] = 0;
					p->rule._con2 = q->rule._con2;
				}
				if (q->cost[_con4_NT] == 0) {
					p->cost[_con4_NT] = 0;
					p->rule._con4 = q->rule._con4;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_ar_NT] == 0) {
					p->cost[_ar_NT] = 0;
					p->rule._ar = q->rule._ar;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 9;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: INDIRI4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 151;
			_closure_reg(a, c + 0);
		}
		/* reg: INDIRI4(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 152;
			_closure_reg(a, c + 0);
		}
		break;
	case 4166: /* INDIRU4 */
		_label(LEFT_CHILD(a));
		if (	/* reg: INDIRU4(VREGP) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			if (mayrecalc(a)) {
				struct _state *q = a->syms[RX]->u.t.cse->x.state;
				if (q->cost[_stmt_NT] == 0) {
					p->cost[_stmt_NT] = 0;
					p->rule._stmt = q->rule._stmt;
				}
				if (q->cost[_reg8_NT] == 0) {
					p->cost[_reg8_NT] = 0;
					p->rule._reg8 = q->rule._reg8;
				}
				if (q->cost[_reg_NT] == 0) {
					p->cost[_reg_NT] = 0;
					p->rule._reg = q->rule._reg;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_c0_NT] == 0) {
					p->cost[_c0_NT] = 0;
					p->rule._c0 = q->rule._c0;
				}
				if (q->cost[_c1_NT] == 0) {
					p->cost[_c1_NT] = 0;
					p->rule._c1 = q->rule._c1;
				}
				if (q->cost[_c2_NT] == 0) {
					p->cost[_c2_NT] = 0;
					p->rule._c2 = q->rule._c2;
				}
				if (q->cost[_con1_NT] == 0) {
					p->cost[_con1_NT] = 0;
					p->rule._con1 = q->rule._con1;
				}
				if (q->cost[_con2_NT] == 0) {
					p->cost[_con2_NT] = 0;
					p->rule._con2 = q->rule._con2;
				}
				if (q->cost[_con4_NT] == 0) {
					p->cost[_con4_NT] = 0;
					p->rule._con4 = q->rule._con4;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_ar_NT] == 0) {
					p->cost[_ar_NT] = 0;
					p->rule._ar = q->rule._ar;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 10;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: INDIRU4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 153;
			_closure_reg(a, c + 0);
		}
		/* reg: INDIRU4(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 154;
			_closure_reg(a, c + 0);
		}
		break;
	case 4209: /* CVFF4 */
		_label(LEFT_CHILD(a));
		/* reg: CVFF4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 13;
			_closure_reg(a, c + 0);
		}
		break;
	case 4213: /* CVFI4 */
		_label(LEFT_CHILD(a));
		/* reg: CVFI4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 15;
			_closure_reg(a, c + 0);
		}
		break;
	case 4225: /* CVIF4 */
		_label(LEFT_CHILD(a));
		/* reg: CVIF4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 16;
			_closure_reg(a, c + 0);
		}
		break;
	case 4229: /* CVII4 */
		_label(LEFT_CHILD(a));
		/* reg: CVII4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 18;
			_closure_reg(a, c + 0);
		}
		/* reg: CVII4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 21;
			_closure_reg(a, c + 0);
		}
		break;
	case 4230: /* CVIU4 */
		break;
	case 4277: /* CVUI4 */
		_label(LEFT_CHILD(a));
		/* reg: CVUI4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 25;
			_closure_reg(a, c + 0);
		}
		break;
	case 4278: /* CVUU4 */
		_label(LEFT_CHILD(a));
		/* reg: CVUU4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 29;
			_closure_reg(a, c + 0);
		}
		break;
	case 4289: /* NEGF4 */
		_label(LEFT_CHILD(a));
		/* reg: NEGF4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 115;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: NEGF4(INDIRF4(addr)) */
			LEFT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 116;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 4293: /* NEGI4 */
		_label(LEFT_CHILD(a));
		/* reg: NEGI4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 113;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: NEGI4(INDIRI4(addr)) */
			LEFT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 114;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 4305: /* CALLF4 */
		_label(LEFT_CHILD(a));
		/* reg: CALLF4(ar) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_ar_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 162;
			_closure_reg(a, c + 0);
		}
		break;
	case 4309: /* CALLI4 */
		_label(LEFT_CHILD(a));
		/* reg: CALLI4(ar) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_ar_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 160;
			_closure_reg(a, c + 0);
		}
		break;
	case 4310: /* CALLU4 */
		_label(LEFT_CHILD(a));
		/* reg: CALLU4(ar) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_ar_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 161;
			_closure_reg(a, c + 0);
		}
		break;
	case 4321: /* LOADF4 */
		_label(LEFT_CHILD(a));
		/* reg: LOADF4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 6;
			_closure_reg(a, c + 0);
		}
		break;
	case 4325: /* LOADI4 */
		_label(LEFT_CHILD(a));
		/* reg: LOADI4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 4;
			_closure_reg(a, c + 0);
		}
		break;
	case 4326: /* LOADU4 */
		_label(LEFT_CHILD(a));
		/* reg: LOADU4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 5;
			_closure_reg(a, c + 0);
		}
		break;
	case 4337: /* RETF4 */
		_label(LEFT_CHILD(a));
		/* stmt: RETF4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 126;
		}
		break;
	case 4341: /* RETI4 */
		_label(LEFT_CHILD(a));
		/* stmt: RETI4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 124;
		}
		break;
	case 4342: /* RETU4 */
		_label(LEFT_CHILD(a));
		/* stmt: RETU4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 125;
		}
		break;
	case 4401: /* ADDF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: ADDF4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 47;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: ADDF4(reg,INDIRF4(addr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 48;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 4405: /* ADDI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: ADDI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 43;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: ADDI4(reg,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 44;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 4406: /* ADDU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: ADDU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 45;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: ADDU4(reg,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 46;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 4417: /* SUBF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: SUBF4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 62;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: SUBF4(reg,INDIRF4(addr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 63;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 4421: /* SUBI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: SUBI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 58;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: SUBI4(reg,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 59;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 4422: /* SUBU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: SUBU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 60;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: SUBU4(reg,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 61;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 4437: /* LSHI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: LSHI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 125;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: LSHI4(reg,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 126;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 4438: /* LSHU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: LSHU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 127;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: LSHU4(reg,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 128;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 4453: /* MODI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MODI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 108;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: MODI4(reg,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 109;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 4454: /* MODU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MODU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 110;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: MODU4(reg,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 111;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 4469: /* RSHI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: RSHI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 137;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: RSHI4(reg,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 138;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 4470: /* RSHU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: RSHU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 139;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: RSHU4(reg,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 140;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 4485: /* BANDI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BANDI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 70;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: BANDI4(reg,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 71;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 4486: /* BANDU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BANDU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 72;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: BANDU4(reg,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 73;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 4501: /* BCOMI4 */
		break;
	case 4502: /* BCOMU4 */
		break;
	case 4517: /* BORI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BORI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 80;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: BORI4(reg,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 81;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 4518: /* BORU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BORU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 82;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: BORU4(reg,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 83;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 4533: /* BXORI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BXORI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 86;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: BXORI4(reg,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 87;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 4534: /* BXORU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BXORU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 88;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: BXORU4(reg,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 89;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 4545: /* DIVF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: DIVF4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 104;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: DIVF4(reg,INDIRF4(addr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 105;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 4549: /* DIVI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: DIVI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 100;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: DIVI4(reg,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 101;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 4550: /* DIVU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: DIVU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 102;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: DIVU4(reg,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 103;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 4561: /* MULF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MULF4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 96;
			_closure_reg(a, c + 0);
		}
		break;
	case 4565: /* MULI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MULI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 92;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: MULI4(reg,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 93;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 4566: /* MULU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MULU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 94;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: MULU4(reg,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 95;
				_closure_reg(a, c + 0);
			}
		}
		if (	/* reg: MULU4(reg,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 97;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 4577: /* EQF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: EQF4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 25;
		}
		if (	/* stmt: EQF4(reg,INDIRF4(addr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 26;
			}
		}
		break;
	case 4581: /* EQI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: EQI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 21;
		}
		if (	/* stmt: EQI4(reg,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 22;
			}
		}
		break;
	case 4582: /* EQU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: EQU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 23;
		}
		if (	/* stmt: EQU4(reg,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 24;
			}
		}
		break;
	case 4593: /* GEF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GEF4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 115;
		}
		if (	/* stmt: GEF4(INDIRF4(addr),reg) */
			LEFT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 116;
			}
		}
		break;
	case 4597: /* GEI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GEI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 111;
		}
		if (	/* stmt: GEI4(INDIRI4(addr),reg) */
			LEFT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 112;
			}
		}
		break;
	case 4598: /* GEU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GEU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 113;
		}
		if (	/* stmt: GEU4(INDIRU4(addr),reg) */
			LEFT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 114;
			}
		}
		break;
	case 4609: /* GTF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GTF4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 97;
		}
		if (	/* stmt: GTF4(INDIRF4(addr),reg) */
			LEFT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 98;
			}
		}
		break;
	case 4613: /* GTI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GTI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 93;
		}
		if (	/* stmt: GTI4(INDIRI4(addr),reg) */
			LEFT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 94;
			}
		}
		break;
	case 4614: /* GTU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GTU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 95;
		}
		if (	/* stmt: GTU4(INDIRU4(addr),reg) */
			LEFT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 96;
			}
		}
		break;
	case 4625: /* LEF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LEF4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 79;
		}
		if (	/* stmt: LEF4(reg,INDIRF4(addr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 80;
			}
		}
		break;
	case 4629: /* LEI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LEI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 75;
		}
		if (	/* stmt: LEI4(reg,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 76;
			}
		}
		break;
	case 4630: /* LEU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LEU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 77;
		}
		if (	/* stmt: LEU4(reg,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 78;
			}
		}
		break;
	case 4641: /* LTF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LTF4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 61;
		}
		if (	/* stmt: LTF4(reg,INDIRF4(addr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 62;
			}
		}
		break;
	case 4645: /* LTI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LTI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 57;
		}
		if (	/* stmt: LTI4(reg,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 58;
			}
		}
		break;
	case 4646: /* LTU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LTU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 59;
		}
		if (	/* stmt: LTU4(reg,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 60;
			}
		}
		break;
	case 4657: /* NEF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: NEF4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 43;
		}
		if (	/* stmt: NEF4(reg,INDIRF4(addr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 44;
			}
		}
		break;
	case 4661: /* NEI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: NEI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 39;
		}
		if (	/* stmt: NEI4(reg,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 40;
			}
		}
		break;
	case 4662: /* NEU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: NEU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 41;
		}
		if (	/* stmt: NEU4(reg,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 42;
			}
		}
		break;
	case 8417: /* LOADF8 */
		break;
	default:
		fatal("_label", "Bad terminal %d\n", OP_LABEL(a));
	}
}

static void _kids(NODEPTR_TYPE p, int eruleno, NODEPTR_TYPE kids[]) {
	if (!p)
		fatal("_kids", "Null tree\n", 0);
	if (!kids)
		fatal("_kids", "Null kids\n", 0);
	switch (eruleno) {
	case 356: /* stmt: JUMPV(ar) */
	case 355: /* stmt: ARGF4(reg) */
	case 354: /* stmt: ARGU4(reg) */
	case 353: /* stmt: ARGI4(reg) */
	case 352: /* stmt: ARGU2(reg) */
	case 351: /* stmt: ARGI2(reg) */
	case 350: /* stmt: ARGP2(reg) */
	case 349: /* stmt: RETV(reg) */
	case 348: /* stmt: RETF4(reg) */
	case 347: /* stmt: RETU4(reg) */
	case 346: /* stmt: RETI4(reg) */
	case 345: /* stmt: RETP2(reg) */
	case 344: /* stmt: RETU2(reg) */
	case 343: /* stmt: RETI2(reg) */
	case 341: /* stmt: CALLV(ar) */
	case 340: /* reg: CALLF4(ar) */
	case 339: /* reg: CALLU4(ar) */
	case 338: /* reg: CALLI4(ar) */
	case 337: /* reg: CALLP2(ar) */
	case 336: /* reg: CALLU2(ar) */
	case 335: /* reg: CALLI2(ar) */
	case 332: /* reg: INDIRF4(addr) */
	case 331: /* reg: INDIRF4(reg) */
	case 330: /* reg: INDIRU4(addr) */
	case 329: /* reg: INDIRU4(reg) */
	case 328: /* reg: INDIRI4(addr) */
	case 327: /* reg: INDIRI4(reg) */
	case 326: /* reg: INDIRP2(addr) */
	case 325: /* reg: INDIRP2(reg) */
	case 324: /* reg: INDIRU2(addr) */
	case 323: /* reg: INDIRU2(reg) */
	case 322: /* reg: INDIRI2(addr) */
	case 321: /* reg: INDIRI2(reg) */
	case 320: /* reg8: INDIRU1(addr) */
	case 319: /* reg8: INDIRU1(reg) */
	case 318: /* reg8: INDIRI1(addr) */
	case 317: /* reg8: INDIRI1(reg) */
	case 173: /* reg: NEGF4(reg) */
	case 171: /* reg: NEGI4(reg) */
	case 170: /* reg: NEGI2(reg) */
	case 46: /* reg: CVUU4(reg) */
	case 45: /* reg8: CVUU2(reg8) */
	case 44: /* reg: CVUU2(reg) */
	case 43: /* reg8: CVUU1(reg) */
	case 42: /* reg: CVUU1(reg) */
	case 41: /* reg: CVUP2(reg) */
	case 40: /* reg: CVUI4(reg) */
	case 39: /* reg: CVUI2(reg8) */
	case 38: /* reg: CVUI2(reg) */
	case 37: /* reg8: CVUI1(reg) */
	case 36: /* reg: CVPU2(reg) */
	case 35: /* reg: CVII4(reg) */
	case 34: /* reg: CVIU2(reg8) */
	case 33: /* reg: CVIU2(reg) */
	case 32: /* reg8: CVIU1(reg) */
	case 31: /* reg: CVII4(reg) */
	case 30: /* reg8: CVII2(reg8) */
	case 29: /* reg: CVII2(reg8) */
	case 28: /* reg: CVIF4(reg) */
	case 27: /* reg: CVFI4(reg) */
	case 26: /* reg: CVFI2(reg) */
	case 25: /* reg: CVFF4(reg) */
	case 8: /* reg: LOADF4(reg) */
	case 7: /* reg: LOADU4(reg) */
	case 6: /* reg: LOADI4(reg) */
	case 5: /* reg: LOADP2(reg) */
	case 4: /* reg: LOADU2(reg) */
	case 3: /* reg: LOADI2(reg) */
	case 2: /* reg8: LOADU1(reg8) */
	case 1: /* reg8: LOADI1(reg8) */
		kids[0] = LEFT_CHILD(p);
		break;
	case 334: /* ar: ADDRGP2 */
	case 316: /* reg: ADDRFP2 */
	case 315: /* reg: ADDRLP2 */
	case 314: /* reg: ADDRGP2 */
	case 313: /* reg: ADDRGP2 */
	case 312: /* stmt: LABELV */
	case 310: /* addr: ADDRFP2 */
	case 309: /* addr: ADDRLP2 */
	case 308: /* addr: ADDRGP2 */
	case 307: /* addr: ADDRGP2 */
	case 58: /* con4: CNSTP2 */
	case 57: /* con4: CNSTU4 */
	case 56: /* con4: CNSTI4 */
	case 55: /* con2: CNSTU2 */
	case 54: /* con2: CNSTI2 */
	case 53: /* con1: CNSTU1 */
	case 52: /* con1: CNSTI1 */
	case 51: /* c2: CNSTI2 */
	case 50: /* c1: CNSTI2 */
	case 49: /* c0: CNSTI2 */
	case 16: /* reg: INDIRF4(VREGP) */
	case 15: /* reg: INDIRP2(VREGP) */
	case 14: /* reg: INDIRU4(VREGP) */
	case 13: /* reg: INDIRI4(VREGP) */
	case 12: /* reg: INDIRU2(VREGP) */
	case 11: /* reg: INDIRI2(VREGP) */
	case 10: /* reg8: INDIRU1(VREGP) */
	case 9: /* reg8: INDIRI1(VREGP) */
		break;
	case 24: /* stmt: ASGNF4(VREGP,reg) */
	case 23: /* stmt: ASGNP2(VREGP,reg) */
	case 22: /* stmt: ASGNU4(VREGP,reg) */
	case 21: /* stmt: ASGNI4(VREGP,reg) */
	case 20: /* stmt: ASGNU2(VREGP,reg) */
	case 19: /* stmt: ASGNI2(VREGP,reg) */
	case 18: /* stmt: ASGNU1(VREGP,reg8) */
	case 17: /* stmt: ASGNI1(VREGP,reg8) */
		kids[0] = RIGHT_CHILD(p);
		break;
	case 333: /* ar: reg */
	case 311: /* stmt: reg */
	case 67: /* reg: con4 */
	case 66: /* reg: con2 */
	case 65: /* reg: con1 */
	case 64: /* con: c2 */
	case 63: /* con: c1 */
	case 62: /* con: c0 */
	case 61: /* con: con4 */
	case 60: /* con: con2 */
	case 59: /* con: con1 */
	case 48: /* reg8: con */
	case 47: /* reg: con */
		kids[0] = p;
		break;
	case 378: /* stmt: ASGNF4(reg,con4) */
	case 377: /* stmt: ASGNF4(addr,con4) */
	case 376: /* stmt: ASGNF4(addr,reg) */
	case 375: /* stmt: ASGNF4(reg,reg) */
	case 374: /* stmt: ASGNU4(reg,con4) */
	case 373: /* stmt: ASGNU4(addr,con4) */
	case 372: /* stmt: ASGNU4(addr,reg) */
	case 371: /* stmt: ASGNU4(reg,reg) */
	case 370: /* stmt: ASGNI4(reg,con4) */
	case 369: /* stmt: ASGNI4(addr,con4) */
	case 368: /* stmt: ASGNI4(addr,reg) */
	case 367: /* stmt: ASGNI4(reg,reg) */
	case 366: /* stmt: ASGNP2(addr,reg) */
	case 365: /* stmt: ASGNP2(reg,reg) */
	case 364: /* stmt: ASGNU2(addr,reg) */
	case 363: /* stmt: ASGNU2(reg,reg) */
	case 362: /* stmt: ASGNI2(addr,reg) */
	case 361: /* stmt: ASGNI2(reg,reg) */
	case 360: /* stmt: ASGNU1(addr,reg8) */
	case 359: /* stmt: ASGNU1(reg,reg8) */
	case 358: /* stmt: ASGNI1(addr,reg8) */
	case 357: /* stmt: ASGNI1(reg,reg8) */
	case 342: /* stmt: CALLB(ar,reg) */
	case 305: /* stmt: GEF4(reg,reg) */
	case 303: /* stmt: GEU4(reg,reg) */
	case 301: /* stmt: GEI4(reg,reg) */
	case 299: /* stmt: GEU2(con,reg8) */
	case 298: /* stmt: GEU2(reg8,reg8) */
	case 296: /* stmt: GEI2(con,reg8) */
	case 295: /* stmt: GEI2(reg8,reg8) */
	case 293: /* stmt: GEU2(con,reg) */
	case 292: /* stmt: GEU2(reg,reg) */
	case 290: /* stmt: GEI2(con,reg) */
	case 289: /* stmt: GEI2(reg,reg) */
	case 287: /* stmt: GTF4(reg,reg) */
	case 285: /* stmt: GTU4(reg,reg) */
	case 283: /* stmt: GTI4(reg,reg) */
	case 281: /* stmt: GTU2(con,reg8) */
	case 280: /* stmt: GTU2(reg8,reg8) */
	case 278: /* stmt: GTI2(con,reg8) */
	case 277: /* stmt: GTI2(reg8,reg8) */
	case 275: /* stmt: GTU2(con,reg) */
	case 274: /* stmt: GTU2(reg,reg) */
	case 272: /* stmt: GTI2(con,reg) */
	case 271: /* stmt: GTI2(reg,reg) */
	case 269: /* stmt: LEF4(reg,reg) */
	case 267: /* stmt: LEU4(reg,reg) */
	case 265: /* stmt: LEI4(reg,reg) */
	case 263: /* stmt: LEU2(reg8,con) */
	case 262: /* stmt: LEU2(reg8,reg8) */
	case 260: /* stmt: LEI2(reg8,con) */
	case 259: /* stmt: LEI2(reg8,reg8) */
	case 257: /* stmt: LEU2(reg,con) */
	case 256: /* stmt: LEU2(reg,reg) */
	case 254: /* stmt: LEI2(reg,con) */
	case 253: /* stmt: LEI2(reg,reg) */
	case 251: /* stmt: LTF4(reg,reg) */
	case 249: /* stmt: LTU4(reg,reg) */
	case 247: /* stmt: LTI4(reg,reg) */
	case 245: /* stmt: LTU2(reg8,con) */
	case 244: /* stmt: LTU2(reg8,reg8) */
	case 242: /* stmt: LTI2(reg8,con) */
	case 241: /* stmt: LTI2(reg8,reg8) */
	case 239: /* stmt: LTU2(reg,con) */
	case 238: /* stmt: LTU2(reg,reg) */
	case 236: /* stmt: LTI2(reg,con) */
	case 235: /* stmt: LTI2(reg,reg) */
	case 233: /* stmt: NEF4(reg,reg) */
	case 231: /* stmt: NEU4(reg,reg) */
	case 229: /* stmt: NEI4(reg,reg) */
	case 227: /* stmt: NEU2(reg8,con) */
	case 226: /* stmt: NEU2(reg8,reg8) */
	case 224: /* stmt: NEI2(reg8,con) */
	case 223: /* stmt: NEI2(reg8,reg8) */
	case 221: /* stmt: NEU2(reg,con) */
	case 220: /* stmt: NEU2(reg,reg) */
	case 218: /* stmt: NEI2(reg,con) */
	case 217: /* stmt: NEI2(reg,reg) */
	case 215: /* stmt: EQF4(reg,reg) */
	case 213: /* stmt: EQU4(reg,reg) */
	case 211: /* stmt: EQI4(reg,reg) */
	case 209: /* stmt: EQU2(reg8,con) */
	case 208: /* stmt: EQU2(reg8,reg8) */
	case 206: /* stmt: EQI2(reg8,con) */
	case 205: /* stmt: EQI2(reg8,reg8) */
	case 203: /* stmt: EQU2(reg,con) */
	case 202: /* stmt: EQU2(reg,reg) */
	case 200: /* stmt: EQI2(reg,con) */
	case 199: /* stmt: EQI2(reg,reg) */
	case 197: /* reg: RSHU4(reg,reg) */
	case 195: /* reg: RSHI4(reg,reg) */
	case 194: /* reg: RSHU2(reg,reg) */
	case 193: /* reg: RSHU2(reg,con) */
	case 192: /* reg: RSHU2(reg,c2) */
	case 191: /* reg: RSHU2(reg,c1) */
	case 190: /* reg: RSHI2(reg,reg) */
	case 189: /* reg: RSHI2(reg,con) */
	case 188: /* reg: RSHI2(reg,c2) */
	case 187: /* reg: RSHI2(reg,c1) */
	case 185: /* reg: LSHU4(reg,reg) */
	case 183: /* reg: LSHI4(reg,reg) */
	case 182: /* reg: LSHU2(reg,reg) */
	case 181: /* reg: LSHU2(reg,con) */
	case 180: /* reg: LSHU2(reg,c2) */
	case 179: /* reg: LSHU2(reg,c1) */
	case 178: /* reg: LSHI2(reg,reg) */
	case 177: /* reg: LSHI2(reg,con) */
	case 176: /* reg: LSHI2(reg,c2) */
	case 175: /* reg: LSHI2(reg,c1) */
	case 168: /* reg: MODU4(reg,reg) */
	case 166: /* reg: MODI4(reg,reg) */
	case 165: /* reg: MODU2(reg,reg) */
	case 164: /* reg: MODI2(reg,reg) */
	case 162: /* reg: DIVF4(reg,reg) */
	case 160: /* reg: DIVU4(reg,reg) */
	case 158: /* reg: DIVI4(reg,reg) */
	case 157: /* reg: DIVU2(reg,reg) */
	case 156: /* reg: DIVI2(reg,reg) */
	case 154: /* reg: MULF4(reg,reg) */
	case 152: /* reg: MULU4(reg,reg) */
	case 150: /* reg: MULI4(reg,reg) */
	case 149: /* reg: MULU2(reg,reg) */
	case 148: /* reg: MULI2(reg,reg) */
	case 146: /* reg: BXORU4(reg,reg) */
	case 144: /* reg: BXORI4(reg,reg) */
	case 143: /* reg: BXORU2(reg,reg) */
	case 142: /* reg: BXORI2(reg,reg) */
	case 140: /* reg: BORU4(reg,reg) */
	case 138: /* reg: BORI4(reg,reg) */
	case 136: /* reg8: BORU2(reg8,con) */
	case 135: /* reg8: BORU2(reg8,reg8) */
	case 133: /* reg8: BORI2(reg8,con) */
	case 132: /* reg8: BORI2(reg8,reg8) */
	case 130: /* reg: BORU2(reg,con) */
	case 129: /* reg: BORU2(reg,reg) */
	case 127: /* reg: BORI2(reg,con) */
	case 126: /* reg: BORI2(reg,reg) */
	case 124: /* reg: BANDU4(reg,reg) */
	case 122: /* reg: BANDI4(reg,reg) */
	case 120: /* reg8: BANDU2(reg8,con) */
	case 119: /* reg8: BANDU2(reg8,reg8) */
	case 117: /* reg8: BANDI2(reg8,con) */
	case 116: /* reg8: BANDI2(reg8,reg8) */
	case 114: /* reg: BANDU2(reg,con) */
	case 113: /* reg: BANDU2(reg,reg) */
	case 111: /* reg: BANDI2(reg,con) */
	case 110: /* reg: BANDI2(reg,reg) */
	case 108: /* reg: SUBF4(reg,reg) */
	case 106: /* reg: SUBU4(reg,reg) */
	case 104: /* reg: SUBI4(reg,reg) */
	case 102: /* reg8: SUBU2(reg8,con) */
	case 101: /* reg8: SUBU2(reg8,reg8) */
	case 99: /* reg8: SUBI2(reg8,con) */
	case 98: /* reg8: SUBI2(reg8,reg8) */
	case 96: /* reg: SUBP2(reg,con) */
	case 95: /* reg: SUBP2(reg,reg) */
	case 93: /* reg: SUBU2(reg,con) */
	case 92: /* reg: SUBU2(reg,reg) */
	case 90: /* reg: SUBI2(reg,con) */
	case 89: /* reg: SUBI2(reg,reg) */
	case 87: /* reg: ADDF4(reg,reg) */
	case 85: /* reg: ADDU4(reg,reg) */
	case 83: /* reg: ADDI4(reg,reg) */
	case 81: /* reg8: ADDU2(reg8,con) */
	case 80: /* reg8: ADDU2(reg8,reg8) */
	case 78: /* reg8: ADDI2(reg8,con) */
	case 77: /* reg8: ADDI2(reg8,reg8) */
	case 75: /* reg: ADDP2(reg,con) */
	case 74: /* reg: ADDP2(reg,reg) */
	case 72: /* reg: ADDU2(reg,con) */
	case 71: /* reg: ADDU2(reg,reg) */
	case 69: /* reg: ADDI2(reg,con) */
	case 68: /* reg: ADDI2(reg,reg) */
		kids[0] = LEFT_CHILD(p);
		kids[1] = RIGHT_CHILD(p);
		break;
	case 379: /* stmt: ASGNB(reg,INDIRB(reg)) */
	case 270: /* stmt: LEF4(reg,INDIRF4(addr)) */
	case 268: /* stmt: LEU4(reg,INDIRU4(addr)) */
	case 266: /* stmt: LEI4(reg,INDIRI4(addr)) */
	case 258: /* stmt: LEU2(reg,INDIRU2(addr)) */
	case 255: /* stmt: LEI2(reg,INDIRI2(addr)) */
	case 252: /* stmt: LTF4(reg,INDIRF4(addr)) */
	case 250: /* stmt: LTU4(reg,INDIRU4(addr)) */
	case 248: /* stmt: LTI4(reg,INDIRI4(addr)) */
	case 240: /* stmt: LTU2(reg,INDIRU2(addr)) */
	case 237: /* stmt: LTI2(reg,INDIRI2(addr)) */
	case 234: /* stmt: NEF4(reg,INDIRF4(addr)) */
	case 232: /* stmt: NEU4(reg,INDIRU4(addr)) */
	case 230: /* stmt: NEI4(reg,INDIRU4(addr)) */
	case 222: /* stmt: NEU2(reg,INDIRU2(addr)) */
	case 219: /* stmt: NEI2(reg,INDIRI2(addr)) */
	case 216: /* stmt: EQF4(reg,INDIRF4(addr)) */
	case 214: /* stmt: EQU4(reg,INDIRU4(addr)) */
	case 212: /* stmt: EQI4(reg,INDIRI4(addr)) */
	case 204: /* stmt: EQU2(reg,INDIRU2(addr)) */
	case 201: /* stmt: EQI2(reg,INDIRI2(addr)) */
	case 198: /* reg: RSHU4(reg,INDIRU4(addr)) */
	case 196: /* reg: RSHI4(reg,INDIRI4(addr)) */
	case 186: /* reg: LSHU4(reg,INDIRU4(addr)) */
	case 184: /* reg: LSHI4(reg,INDIRI4(addr)) */
	case 169: /* reg: MODU4(reg,INDIRU4(addr)) */
	case 167: /* reg: MODI4(reg,INDIRI4(addr)) */
	case 163: /* reg: DIVF4(reg,INDIRF4(addr)) */
	case 161: /* reg: DIVU4(reg,INDIRU4(addr)) */
	case 159: /* reg: DIVI4(reg,INDIRI4(addr)) */
	case 155: /* reg: MULU4(reg,INDIRU4(addr)) */
	case 153: /* reg: MULU4(reg,INDIRU4(addr)) */
	case 151: /* reg: MULI4(reg,INDIRI4(addr)) */
	case 147: /* reg: BXORU4(reg,INDIRU4(addr)) */
	case 145: /* reg: BXORI4(reg,INDIRI4(addr)) */
	case 141: /* reg: BORU4(reg,INDIRU4(addr)) */
	case 139: /* reg: BORI4(reg,INDIRI4(addr)) */
	case 131: /* reg: BORU2(reg,INDIRI2(addr)) */
	case 128: /* reg: BORI2(reg,INDIRI2(addr)) */
	case 125: /* reg: BANDU4(reg,INDIRU4(addr)) */
	case 123: /* reg: BANDI4(reg,INDIRI4(addr)) */
	case 115: /* reg: BANDU2(reg,INDIRI2(addr)) */
	case 112: /* reg: BANDI2(reg,INDIRI2(addr)) */
	case 109: /* reg: SUBF4(reg,INDIRF4(addr)) */
	case 107: /* reg: SUBU4(reg,INDIRU4(addr)) */
	case 105: /* reg: SUBI4(reg,INDIRI4(addr)) */
	case 97: /* reg: SUBP2(reg,INDIRI2(addr)) */
	case 94: /* reg: SUBU2(reg,INDIRI2(addr)) */
	case 91: /* reg: SUBI2(reg,INDIRI2(addr)) */
	case 88: /* reg: ADDF4(reg,INDIRF4(addr)) */
	case 86: /* reg: ADDU4(reg,INDIRU4(addr)) */
	case 84: /* reg: ADDI4(reg,INDIRI4(addr)) */
	case 76: /* reg: ADDP2(reg,INDIRI2(addr)) */
	case 73: /* reg: ADDU2(reg,INDIRI2(addr)) */
	case 70: /* reg: ADDI2(reg,INDIRI2(addr)) */
		kids[0] = LEFT_CHILD(p);
		kids[1] = LEFT_CHILD(RIGHT_CHILD(p));
		break;
	case 264: /* stmt: LEU2(reg8,CVUU2(INDIRU1(addr))) */
	case 261: /* stmt: LEI2(reg8,CVII2(INDIRI1(addr))) */
	case 246: /* stmt: LTU2(reg8,CVUU2(INDIRU1(addr))) */
	case 243: /* stmt: LTI2(reg8,CVII2(INDIRI1(addr))) */
	case 228: /* stmt: NEU2(reg8,CVUU2(INDIRU1(addr))) */
	case 225: /* stmt: NEI2(reg8,CVII2(INDIRI1(addr))) */
	case 210: /* stmt: EQU2(reg8,CVUU2(INDIRU1(addr))) */
	case 207: /* stmt: EQI2(reg8,CVII2(INDIRI1(addr))) */
	case 137: /* reg8: BORU2(reg8,CVUU2(INDIRU2(addr))) */
	case 134: /* reg8: BORI2(reg8,CVII2(INDIRI2(addr))) */
	case 121: /* reg8: BANDU2(reg8,CVUU2(INDIRU2(addr))) */
	case 118: /* reg8: BANDI2(reg8,CVII2(INDIRI2(addr))) */
	case 103: /* reg8: SUBU2(reg8,CVUU2(INDIRU2(addr))) */
	case 100: /* reg8: SUBI2(reg8,CVII2(INDIRI2(addr))) */
	case 82: /* reg8: ADDU2(reg8,CVUU2(INDIRU1(addr))) */
	case 79: /* reg8: ADDI2(reg8,CVII2(INDIRI1(addr))) */
		kids[0] = LEFT_CHILD(p);
		kids[1] = LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(p)));
		break;
	case 380: /* stmt: ARGB(INDIRB(reg)) */
	case 174: /* reg: NEGF4(INDIRF4(addr)) */
	case 172: /* reg: NEGI4(INDIRI4(addr)) */
		kids[0] = LEFT_CHILD(LEFT_CHILD(p));
		break;
	case 306: /* stmt: GEF4(INDIRF4(addr),reg) */
	case 304: /* stmt: GEU4(INDIRU4(addr),reg) */
	case 302: /* stmt: GEI4(INDIRI4(addr),reg) */
	case 294: /* stmt: GEU2(INDIRU2(addr),reg) */
	case 291: /* stmt: GEI2(INDIRI2(addr),reg) */
	case 288: /* stmt: GTF4(INDIRF4(addr),reg) */
	case 286: /* stmt: GTU4(INDIRU4(addr),reg) */
	case 284: /* stmt: GTI4(INDIRI4(addr),reg) */
	case 276: /* stmt: GTU2(INDIRU2(addr),reg) */
	case 273: /* stmt: GTI2(INDIRI2(addr),reg) */
		kids[0] = LEFT_CHILD(LEFT_CHILD(p));
		kids[1] = RIGHT_CHILD(p);
		break;
	case 300: /* stmt: GEU2(CVUU2(INDIRU1(addr)),reg8) */
	case 297: /* stmt: GEI2(CVII2(INDIRI1(addr)),reg8) */
	case 282: /* stmt: GTU2(CVUU2(INDIRU1(addr)),reg8) */
	case 279: /* stmt: GTI2(CVII2(INDIRI1(addr)),reg8) */
		kids[0] = LEFT_CHILD(LEFT_CHILD(LEFT_CHILD(p)));
		kids[1] = RIGHT_CHILD(p);
		break;
	default:
		fatal("_kids", "Bad rule number %d\n", eruleno);
	}
}


// Emitters
static void progbeg(int argc, char *argv[]) {
    {
	union {
	    char c;
	    int i;
	} u;
	u.i = 0;
	u.c = 1;
	swap = ((int)(u.i == 1)) != IR->little_endian;
    }
    parseflags(argc,argv);

    // Long reg symbols
    longreg[R_L0] = mkreg("L0",R_L0,1,IREG);
    longreg[R_L1] = mkreg("L1",R_L1,1,IREG);
    longreg[R_L2] = mkreg("L2",R_L2,1,IREG);
    longreg[R_L3] = mkreg("L3",R_L3,1,IREG);

    // Reg symbols
    intreg[R_A] = mkreg("a",R_A,1,IREG);
    intreg[R_B] = mkreg("b",R_B,1,IREG);

    // Float symbols
    fltreg[R_F0] = mkreg("F0",R_F0,1,FREG);
    fltreg[R_F1] = mkreg("F1",R_F1,1,FREG);
    fltreg[R_F2] = mkreg("F2",R_F2,1,FREG);
    fltreg[R_F3] = mkreg("F3",R_F3,1,FREG);

    // Set up sets
    longwldcrd = mkwildcard(longreg);
    intwldcrd = mkwildcard(intreg);
    fltwldcrd = mkwildcard(fltreg);

    // Set up temp regs
    tmask[IREG] = (1<<R_L0) | (1<<R_L1) | (1<<R_L2) | (1<<R_L3) | (1<<R_A) | (1<<R_B);
    // Set up register temps - none in our case
    vmask[IREG] = 0;

    // FP regs.
    tmask[FREG] = (1<<R_F0) | (1<<R_F1) | (1<<R_F2) | (1<<R_F3);
    // Set up register temps - none in our case
    vmask[FREG] = 0;
    
    print(";	Magic-1 assembly file, generated by lcc 4.2\n");
    print("_start:\n");
    print("	br	over_ivec\n");
    print("	defw	unhandled_exception	; Interrupt vector 1\n");
    print("	defw	unhandled_exception	; Interrupt vector 2\n");
    print("	defw	unhandled_exception	; Interrupt vector 3\n");
    print("	defw	unhandled_exception	; Interrupt vector 4\n");
    print("	defw	unhandled_exception	; Interrupt vector 5\n");
    print("	defw	unhandled_exception	; Interrupt vector 6\n");
    print("	defw	unhandled_exception	; Interrupt vector 7\n");
    print("	defw	unhandled_exception	; Interrupt vector 8\n");
    print("	defw	unhandled_exception	; Interrupt vector 9\n");
    print("	defw	unhandled_exception	; Interrupt vector a\n");
    print("	defw	unhandled_exception	; Interrupt vector b\n");
    print("	defw	unhandled_exception	; Interrupt vector c\n");
    print("	defw	unhandled_exception	; Interrupt vector d\n");
    print("	defw	unhandled_exception	; Interrupt vector e\n");
    print("	defw	unhandled_exception	; Interrupt vector f\n");
    print("unhandled_exception:\n");
    print("	halt\n");
    print("over_ivec:\n");
    print("	ld.16	a,0x8000\n");
    print("	copy	sp,a\n");
    print("	ld.16	a,0x4000\n");
    print("	copy	dp,a\n");
    print("	call	_main\n");
    print("	halt\n");
    
    current_seg = 0;
}

static Symbol rmap(int opk) {
    switch (optype(opk)) {
	case B:
	case P:
	    return intwldcrd;
	case I:
	case U:
	    if (opsize(opk) <= 2) {
	        return intwldcrd; 
	    } else {
		return longwldcrd;
	    }
	case F:
	    return fltwldcrd;
	default:
	    return 0;
    }
}

static void segment(int n) {
    if (n==current_seg)
	return;
    if (n == CODE)
	print("\tcseg\n");
    else if (n == LIT)
#if 1 // combine lit with dseg
	print("\tdseg\n");
#else
	print("\tlit\n");
#endif
    else if (n == DATA)
	print("\tdseg\n");
    else if (n == BSS)
	print("\tbss\n");
    else
	print("\tERROR - unknown segment %d\n",n);
    current_seg = n;
}

static void progend(void) {
    print("\tend\n");
}

int iscvt(Node p) {
    return ((generic(p->op)==CVI) || (generic(p->op)==CVU));
}

static void target(Node p) {
    assert(p);
    switch (specific(p->op)) {

	case NEG+I:
	case NEG+U:
	    if (opsize(p->op)<=2) {
		rtarget(p,0,intreg[R_B]);
		setreg(p,intreg[R_A]);
		if (iscvt(p->kids[0])) {
		    rtarget(p->kids[0],0,intreg[R_A]);
		}
	    }
	    break;

	case ADD+I:
	case ADD+U:
	case SUB+I:
	case SUB+U:
	case BOR+I:
	case BOR+U:
	case BAND+I:
	case BAND+U:
	case BXOR+I:
	case BXOR+U:
	case LSH+I:
	    if (opsize(p->op)<=2) {
	        rtarget(p,0,intreg[R_A]);
		if (iscvt(p->kids[0])) {
		    rtarget(p->kids[0],0,intreg[R_A]);
		}
	        setreg(p,intreg[R_A]);
	    }
	    break;
	
	case MUL+I:
	case MUL+U:
	case DIV+I:
	case DIV+U:
	case MOD+I:
	case MOD+U:
	    if (opsize(p->op)<=2) {
		rtarget(p,0,intreg[R_A]);
		if (iscvt(p->kids[0])) {
		    rtarget(p->kids[0],0,intreg[R_A]);
		}
		rtarget(p,1,intreg[R_B]);
		setreg(p,intreg[R_A]);
	    } 
	    break;

	case CALL+I:
	case CALL+U:
	case CALL+P:
	    if (opsize(p->op)<=2) {
   	        setreg(p,intreg[R_A]);
	    }
	    break;

	case EQ+I:
	case EQ+U:
	case NE+I:
	case NE+U:
	case LE+I:
	case LE+U:
	case LT+I:
	case LT+U:
	    if (opsize(p->op) <= 2) {
		rtarget(p,0,intreg[R_A]);
		if (iscvt(p->kids[0])) {
		    rtarget(p->kids[0],0,intreg[R_A]);
		}
		rtarget(p,1,intreg[R_B]);
	    } 
	    break;

	    // Swapping operands for these to normalize to LE & LT
	case GT+I:
	case GT+U:
        case GE+I:
	case GE+U:
	    if (opsize(p->op) <= 2) {
		rtarget(p,1,intreg[R_A]);
		if (iscvt(p->kids[1])) {
		    rtarget(p->kids[1],0,intreg[R_A]);
		}
		rtarget(p,0,intreg[R_B]);
	    }
	    break;
	
	case CALL+B:
	    rtarget(p,1,intreg[R_A]);
	    break;

	case RET+I:
	case RET+U:
	case RET+P:
	    if (opsize(p->op) <= 2) {
		rtarget(p,0,intreg[R_A]);
	    }
	    break;

        case CVI+U:
	case CVU+U:
	case CVU+I:
	case CVI+F:
	case CVF+I:
	    // Assumption here is that if result is 2, source can be any 4-byte pseudo reg
	    // If result is > 2, then source should be register A
	    if (opsize(p->op) == 2) {
		setreg(p,intreg[R_A]);
	    } else {
		rtarget(p,0,intreg[R_A]);
	    }
	    break;

	case ARG+B:
	    rtarget(p->kids[0],0,intreg[R_B]);
	    break;

	case ASGN+B:
	    rtarget(p,0,intreg[R_A]);
	    rtarget(p->kids[1],0,intreg[R_B]);
	    break;
        case INDIR+I:
        case INDIR+U:
        case INDIR+F:
	    if (opsize(p->op) > 2) {
		rtarget(p,0,intreg[R_A]);
	    }
	    break;
    }
}

static void clobber(Node p) {
    assert(p);
    switch(specific(p->op)) {
	case CALL+F:
	case CALL+I:
	case CALL+U:
	case CALL+V:
	    spill(1<<R_B,IREG,p);
	    break;
        case RET+I:
        case RET+U:
        case RET+F:
	    if (opsize(p->op) > 2) {
	        spill(1<<R_A,IREG,p);
	    }
	    break;
        case ARG+B:
	    // Already targeting B, so don't clobber it
	    spill(1<<R_A,IREG,p);
	    break;
	case INDIR+I:
	case INDIR+U:
	case INDIR+F:
	    if (opsize(p->op) >2) {
		spill(1<<R_B,IREG,p);
	    }
	    break;
	default:
	    if (opsize(p->op) > 2) {
		spill((1<<R_A)|(1<<R_B),IREG,p);
	    }
	    break;
    }
}


static void emit2(Node p) {
    int op = specific(p->op); 

    switch( op ) {
       case ARG+F: 
       case ARG+P: 
       case ARG+I: 
       case ARG+U: 
	   if (opsize(p->op) <= 2) {
	       print("\tst.16\t%d(sp),%s\n",p->syms[2]->u.c.v.i,p->kids[0]->syms[2]->x.name); 
	   }
           break;
	
        case ARG+B:
	       print("\tld.16\tc,%d\n\tlea\ta,%d(sp)\n\tmemcopy\n",p->syms[0]->u.c.v.i,p->syms[2]->u.c.v.i);
	   break;

        case RET+I:
	case RET+U:
	case RET+F:
	   if (opsize(p->op) > 2) {
	       print("\tld.16\ta,%s\n\tld.16\tb,4+%s\n",
		       p->kids[0]->syms[2]->x.name,p->kids[0]->syms[2]->x.name);
	   }
	   break;
    }
}

static void doarg(Node p) {
    static int argno;
    if (argoffset==0) {
	argoffset = 2;
	argno = 0;
    }
    p->x.argno=argno++;
    p->syms[2] = intconst(mkactual(1,p->syms[0]->u.c.v.i));
}

// Block operators not needed
static void blkfetch(int k, int off, int reg, int tmp) {}
static void blkstore(int k, int off, int reg, int tmp) {}
static void blkloop(int dreg, int doff, int sreg, int soff,int size, int tmps[]) {}

static void local(Symbol p) {
    if (isfloat(p->type)) {
	p->sclass = AUTO;
    }
    if (askregvar(p,(*IR->x.rmap)(ttob(p->type)))==0) {
	mkauto(p);
    }
}

static void function(Symbol f, Symbol caller[], Symbol callee[], int n) {
    int i;

    print("%s:\n",f->x.name);
    usedmask[0] = usedmask[1] = 0;
    freemask[0] = freemask[1] = ~(unsigned)0;

    offset = 0;
    for (i=0; callee[i]; i++) {
	Symbol p = callee[i];
	Symbol q = caller[i];
	assert(q);
	p->x.offset = q->x.offset = offset; /* + A_T0_STORE_SIZE; */
	p->x.name = q->x.name = stringf("%d",p->x.offset);
	p->sclass = q->sclass = AUTO;
	offset += roundup(q->type->size,2);
    }
    assert(caller[i] == 0);
    maxoffset = offset = 0;
    maxargoffset = 0;

    // Generate code
    gencode(caller,callee);

    // Allocate space for any pseudo regs we used
    for (i=R_L0;i<=R_L3;i++) {
	if (usedmask[0] & (1<<i)) {
	    maxoffset+=4;
	    longreg[i]->x.offset = -maxoffset;
	}
    }
    for (i=R_F0;i<=R_F3;i++) {
	if (usedmask[1] & (1<<i)) {
	    maxoffset+=4;
	    fltreg[i]->x.offset = -maxoffset;
	}
    }

    // Now, set the frame size
    framesize = maxoffset + maxargoffset + 2;

    // Rewrite names of used long and float regs now that we know framesize
    for (i=R_L0;i<=R_L3;i++) {
	if (usedmask[0] & (1<<i)) {
	    longreg[i]->x.name = stringf("%d(sp)",longreg[i]->x.offset+framesize);
	}
    }
    for (i=R_F0;i<=R_F3;i++) {
	if (usedmask[1] & (1<<i)) {
	    fltreg[i]->x.name = stringf("%d(sp)",fltreg[i]->x.offset+framesize);
	}
    }


    // Gen entry code
    print("\tenter\t%d\n",framesize-2);
    if (isstruct(freturn(f->type))) {
	print("\tst.16\t-2+%d(sp),a\n",framesize);
    }
    emitcode();
#if 0
    print("\tleave\n");
    printf("\tret\n");
#else
    print("\tpop\tsp\n");
    print("\tpop\tpc\n");
#endif
}

static void defsymbol(Symbol p) {
    if (p->scope >= LOCAL && p->sclass == STATIC)
	p->x.name = stringf("L%d", genlabel(1));
    else if (p->generated)
	p->x.name = stringf("L%s", p->name);
    else if (p->scope == GLOBAL || p->sclass == EXTERN)
	p->x.name = stringf("_%s",p->name);
    else if (p->scope == CONSTANTS
	    && (isint(p->type) || isptr(p->type))
	    && p->name[0] == '0' && p->name[1] == 'x')
	p->x.name = stringf("0%sH", &p->name[2]);
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
        if (suffix == I && size == 1)
                print("	defb 0%xH\n",   v.u & 0xff);
        else if (suffix == I && size == 2)
                print("	defw 0%xH\n",   v.i & 0xffff);
        else if (suffix == U && size == 1)
                print("	defb 0%xH\n", v.u & 0xff);
        else if (suffix == U && size == 2)
                print("	defw 0%xH\n",   v.i & 0xffff);
        else if (suffix == P && size == 2)
                print("	defw 0%xH\n", v.u & 0xffff);
        else if (suffix == F && size == 4) {
                float f = (float) v.d;
                print("	defw 0%xH\n", ((*(unsigned *)&f)>>16) & 0xffff);
                print("	defw 0%xH\n", (*(unsigned *)&f) & 0xffff);
        } else if (suffix == I && size == 4) {
                print("	defw 0%xH\n",   (v.i>>16) & 0xffff);
                print("	defw 0%xH\n",   v.i & 0xffff);
        } else if (suffix == U && size == 4) {
                print("	defw 0%xH\n",   (v.u>>16) & 0xffff);
                print("	defw 0%xH\n",   v.u & 0xffff);
	}
        else assert(0);
}
static void defaddress(Symbol p) {
        print("	defw %s\n", p->x.name);
}

static void defstring(int n, char *str) {
        char *s;
        for (s = str; s < str + n; s++)
                print("	defb %d\n", (*s)&0377);
}

static void export(Symbol p) {
    print("\tglobal %s\n", p->x.name);
}

static void import(Symbol p) {
    print("\textern %s\n", p->x.name);
}

static void global(Symbol p) {
        assert(p->type->align == 1);
        print("%s:\n", p->x.name);
        if (p->u.seg == BSS)
                print("	defs %d\n", p->type->size);
}

static void space(int n) {
        if (current_seg != BSS)
                print("db %d dup (0)\n", n);
}

static int isfptr(Node n , int iftrue , int iffalse) {
    if ( !n->syms[0]->generated && isfunc(n->syms[0]->type))
       return iftrue;
    else
       return iffalse;
}



Interface m1IR = {
        1, 1, 0,  /* char */
        2, 1, 0,  /* short */
        2, 1, 0,  /* int */
        4, 1, 1,  /* long */
        4, 1, 1,  /* long long */
        4, 1, 1,  /* float */
        4, 1, 1,  /* double */
        4, 1, 1,  /* long double */
        2, 1, 0,  /* T * */
        0, 1, 0,  /* struct */
        0,        /* little_endian */
        1,        /* mulops_calls */
        1,        /* wants_callb */
        1,        /* wants_argb */
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
        {1, rmap,
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
static char rcsid[] = "$Id: $";
