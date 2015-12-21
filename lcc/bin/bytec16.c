
// LCC machine description for BYTEC/16
// July 2015
// http://www.pilawa.org/computer

// Registers
enum { R_L0, R_L1, R_L2, R_L3, R_AH, R_AL, R_A, R_Y, R_X };

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
static int ever_used_muldiv16;
static int ptr64;

/*
generated at Thu Dec 10 23:41:48 2015
by $Id: lburg.c,v 2.10 2002/03/08 18:45:21 drh Exp $
*/
static void _kids(NODEPTR_TYPE, int, NODEPTR_TYPE[]);
static void _label(NODEPTR_TYPE);
static int _rule(void*, int);

#define _stmt_NT 1
#define _reg8_NT 2
#define _reg_NT 3
#define _reg32_NT 4
#define _regf_NT 5
#define _con8_NT 6
#define _con16_NT 7
#define _con0_NT 8
#define _con1_NT 9
#define _con2_NT 10
#define _con_NT 11
#define _lgaddr_NT 12
#define _addr_NT 13
#define _albl_NT 14
#define _ar_NT 15

static char *_ntname[] = {
	0,
	"stmt",
	"reg8",
	"reg",
	"reg32",
	"regf",
	"con8",
	"con16",
	"con0",
	"con1",
	"con2",
	"con",
	"lgaddr",
	"addr",
	"albl",
	"ar",
	0
};

struct _state {
	short cost[16];
	struct {
		unsigned int _stmt:8;
		unsigned int _reg8:7;
		unsigned int _reg:7;
		unsigned int _reg32:6;
		unsigned int _regf:6;
		unsigned int _con8:2;
		unsigned int _con16:2;
		unsigned int _con0:3;
		unsigned int _con1:3;
		unsigned int _con2:3;
		unsigned int _con:2;
		unsigned int _lgaddr:2;
		unsigned int _addr:3;
		unsigned int _albl:1;
		unsigned int _ar:2;
	} rule;
};

static short _nts_0[] = { 0 };
static short _nts_1[] = { _reg8_NT, 0 };
static short _nts_2[] = { _reg_NT, 0 };
static short _nts_3[] = { _reg32_NT, 0 };
static short _nts_4[] = { _regf_NT, 0 };
static short _nts_5[] = { _con8_NT, 0 };
static short _nts_6[] = { _con16_NT, 0 };
static short _nts_7[] = { _con_NT, 0 };
static short _nts_8[] = { _con0_NT, 0 };
static short _nts_9[] = { _lgaddr_NT, 0 };
static short _nts_10[] = { _reg_NT, _con_NT, 0 };
static short _nts_11[] = { _albl_NT, 0 };
static short _nts_12[] = { _addr_NT, _reg8_NT, 0 };
static short _nts_13[] = { _addr_NT, _reg_NT, 0 };
static short _nts_14[] = { _reg_NT, _reg_NT, 0 };
static short _nts_15[] = { _lgaddr_NT, _reg32_NT, 0 };
static short _nts_16[] = { _lgaddr_NT, _lgaddr_NT, 0 };
static short _nts_17[] = { _lgaddr_NT, _regf_NT, 0 };
static short _nts_18[] = { _addr_NT, 0 };
static short _nts_19[] = { _reg_NT, _addr_NT, 0 };
static short _nts_20[] = { _reg8_NT, _addr_NT, 0 };
static short _nts_21[] = { _reg8_NT, _con_NT, 0 };
static short _nts_22[] = { _reg32_NT, _reg32_NT, 0 };
static short _nts_23[] = { _reg32_NT, _lgaddr_NT, 0 };
static short _nts_24[] = { _regf_NT, _regf_NT, 0 };
static short _nts_25[] = { _regf_NT, _lgaddr_NT, 0 };
static short _nts_26[] = { _lgaddr_NT, _lgaddr_NT, _lgaddr_NT, 0 };
static short _nts_27[] = { _reg_NT, _lgaddr_NT, 0 };
static short _nts_28[] = { _reg8_NT, _lgaddr_NT, 0 };
static short _nts_29[] = { _reg_NT, _con1_NT, 0 };
static short _nts_30[] = { _reg_NT, _con2_NT, 0 };
static short _nts_31[] = { _reg32_NT, _con1_NT, 0 };
static short _nts_32[] = { _ar_NT, 0 };

static short *_nts[] = {
	0,	/* 0 */
	_nts_0,	/* 1 */
	_nts_0,	/* 2 */
	_nts_0,	/* 3 */
	_nts_0,	/* 4 */
	_nts_0,	/* 5 */
	_nts_0,	/* 6 */
	_nts_0,	/* 7 */
	_nts_0,	/* 8 */
	_nts_0,	/* 9 */
	_nts_1,	/* 10 */
	_nts_1,	/* 11 */
	_nts_2,	/* 12 */
	_nts_2,	/* 13 */
	_nts_3,	/* 14 */
	_nts_3,	/* 15 */
	_nts_2,	/* 16 */
	_nts_4,	/* 17 */
	_nts_4,	/* 18 */
	_nts_1,	/* 19 */
	_nts_2,	/* 20 */
	_nts_3,	/* 21 */
	_nts_4,	/* 22 */
	_nts_1,	/* 23 */
	_nts_1,	/* 24 */
	_nts_2,	/* 25 */
	_nts_2,	/* 26 */
	_nts_2,	/* 27 */
	_nts_2,	/* 28 */
	_nts_2,	/* 29 */
	_nts_3,	/* 30 */
	_nts_3,	/* 31 */
	_nts_4,	/* 32 */
	_nts_4,	/* 33 */
	_nts_1,	/* 34 */
	_nts_1,	/* 35 */
	_nts_3,	/* 36 */
	_nts_3,	/* 37 */
	_nts_3,	/* 38 */
	_nts_3,	/* 39 */
	_nts_0,	/* 40 */
	_nts_0,	/* 41 */
	_nts_0,	/* 42 */
	_nts_0,	/* 43 */
	_nts_0,	/* 44 */
	_nts_0,	/* 45 */
	_nts_0,	/* 46 */
	_nts_0,	/* 47 */
	_nts_0,	/* 48 */
	_nts_0,	/* 49 */
	_nts_0,	/* 50 */
	_nts_0,	/* 51 */
	_nts_0,	/* 52 */
	_nts_0,	/* 53 */
	_nts_0,	/* 54 */
	_nts_0,	/* 55 */
	_nts_0,	/* 56 */
	_nts_5,	/* 57 */
	_nts_6,	/* 58 */
	_nts_7,	/* 59 */
	_nts_8,	/* 60 */
	_nts_5,	/* 61 */
	_nts_0,	/* 62 */
	_nts_0,	/* 63 */
	_nts_0,	/* 64 */
	_nts_9,	/* 65 */
	_nts_2,	/* 66 */
	_nts_10,	/* 67 */
	_nts_10,	/* 68 */
	_nts_0,	/* 69 */
	_nts_2,	/* 70 */
	_nts_11,	/* 71 */
	_nts_9,	/* 72 */
	_nts_12,	/* 73 */
	_nts_12,	/* 74 */
	_nts_13,	/* 75 */
	_nts_13,	/* 76 */
	_nts_13,	/* 77 */
	_nts_14,	/* 78 */
	_nts_15,	/* 79 */
	_nts_16,	/* 80 */
	_nts_15,	/* 81 */
	_nts_16,	/* 82 */
	_nts_17,	/* 83 */
	_nts_16,	/* 84 */
	_nts_17,	/* 85 */
	_nts_16,	/* 86 */
	_nts_18,	/* 87 */
	_nts_18,	/* 88 */
	_nts_18,	/* 89 */
	_nts_18,	/* 90 */
	_nts_18,	/* 91 */
	_nts_9,	/* 92 */
	_nts_9,	/* 93 */
	_nts_9,	/* 94 */
	_nts_9,	/* 95 */
	_nts_2,	/* 96 */
	_nts_2,	/* 97 */
	_nts_2,	/* 98 */
	_nts_2,	/* 99 */
	_nts_3,	/* 100 */
	_nts_3,	/* 101 */
	_nts_3,	/* 102 */
	_nts_3,	/* 103 */
	_nts_1,	/* 104 */
	_nts_1,	/* 105 */
	_nts_1,	/* 106 */
	_nts_1,	/* 107 */
	_nts_1,	/* 108 */
	_nts_1,	/* 109 */
	_nts_1,	/* 110 */
	_nts_1,	/* 111 */
	_nts_2,	/* 112 */
	_nts_2,	/* 113 */
	_nts_2,	/* 114 */
	_nts_2,	/* 115 */
	_nts_1,	/* 116 */
	_nts_2,	/* 117 */
	_nts_3,	/* 118 */
	_nts_1,	/* 119 */
	_nts_2,	/* 120 */
	_nts_3,	/* 121 */
	_nts_4,	/* 122 */
	_nts_4,	/* 123 */
	_nts_4,	/* 124 */
	_nts_4,	/* 125 */
	_nts_2,	/* 126 */
	_nts_2,	/* 127 */
	_nts_14,	/* 128 */
	_nts_19,	/* 129 */
	_nts_10,	/* 130 */
	_nts_14,	/* 131 */
	_nts_19,	/* 132 */
	_nts_10,	/* 133 */
	_nts_14,	/* 134 */
	_nts_10,	/* 135 */
	_nts_20,	/* 136 */
	_nts_20,	/* 137 */
	_nts_20,	/* 138 */
	_nts_21,	/* 139 */
	_nts_21,	/* 140 */
	_nts_21,	/* 141 */
	_nts_20,	/* 142 */
	_nts_20,	/* 143 */
	_nts_20,	/* 144 */
	_nts_21,	/* 145 */
	_nts_21,	/* 146 */
	_nts_21,	/* 147 */
	_nts_22,	/* 148 */
	_nts_23,	/* 149 */
	_nts_22,	/* 150 */
	_nts_23,	/* 151 */
	_nts_24,	/* 152 */
	_nts_25,	/* 153 */
	_nts_24,	/* 154 */
	_nts_25,	/* 155 */
	_nts_26,	/* 156 */
	_nts_26,	/* 157 */
	_nts_26,	/* 158 */
	_nts_26,	/* 159 */
	_nts_26,	/* 160 */
	_nts_26,	/* 161 */
	_nts_26,	/* 162 */
	_nts_26,	/* 163 */
	_nts_14,	/* 164 */
	_nts_19,	/* 165 */
	_nts_10,	/* 166 */
	_nts_14,	/* 167 */
	_nts_19,	/* 168 */
	_nts_10,	/* 169 */
	_nts_14,	/* 170 */
	_nts_10,	/* 171 */
	_nts_20,	/* 172 */
	_nts_20,	/* 173 */
	_nts_20,	/* 174 */
	_nts_21,	/* 175 */
	_nts_21,	/* 176 */
	_nts_21,	/* 177 */
	_nts_20,	/* 178 */
	_nts_20,	/* 179 */
	_nts_20,	/* 180 */
	_nts_21,	/* 181 */
	_nts_21,	/* 182 */
	_nts_21,	/* 183 */
	_nts_22,	/* 184 */
	_nts_23,	/* 185 */
	_nts_22,	/* 186 */
	_nts_23,	/* 187 */
	_nts_24,	/* 188 */
	_nts_25,	/* 189 */
	_nts_24,	/* 190 */
	_nts_25,	/* 191 */
	_nts_26,	/* 192 */
	_nts_26,	/* 193 */
	_nts_26,	/* 194 */
	_nts_26,	/* 195 */
	_nts_26,	/* 196 */
	_nts_26,	/* 197 */
	_nts_26,	/* 198 */
	_nts_26,	/* 199 */
	_nts_2,	/* 200 */
	_nts_9,	/* 201 */
	_nts_3,	/* 202 */
	_nts_9,	/* 203 */
	_nts_4,	/* 204 */
	_nts_9,	/* 205 */
	_nts_4,	/* 206 */
	_nts_9,	/* 207 */
	_nts_14,	/* 208 */
	_nts_27,	/* 209 */
	_nts_10,	/* 210 */
	_nts_14,	/* 211 */
	_nts_27,	/* 212 */
	_nts_10,	/* 213 */
	_nts_28,	/* 214 */
	_nts_28,	/* 215 */
	_nts_28,	/* 216 */
	_nts_21,	/* 217 */
	_nts_21,	/* 218 */
	_nts_21,	/* 219 */
	_nts_28,	/* 220 */
	_nts_28,	/* 221 */
	_nts_28,	/* 222 */
	_nts_21,	/* 223 */
	_nts_21,	/* 224 */
	_nts_21,	/* 225 */
	_nts_22,	/* 226 */
	_nts_23,	/* 227 */
	_nts_22,	/* 228 */
	_nts_23,	/* 229 */
	_nts_2,	/* 230 */
	_nts_2,	/* 231 */
	_nts_3,	/* 232 */
	_nts_3,	/* 233 */
	_nts_14,	/* 234 */
	_nts_27,	/* 235 */
	_nts_10,	/* 236 */
	_nts_14,	/* 237 */
	_nts_27,	/* 238 */
	_nts_10,	/* 239 */
	_nts_28,	/* 240 */
	_nts_28,	/* 241 */
	_nts_28,	/* 242 */
	_nts_21,	/* 243 */
	_nts_21,	/* 244 */
	_nts_21,	/* 245 */
	_nts_28,	/* 246 */
	_nts_28,	/* 247 */
	_nts_28,	/* 248 */
	_nts_21,	/* 249 */
	_nts_21,	/* 250 */
	_nts_21,	/* 251 */
	_nts_22,	/* 252 */
	_nts_23,	/* 253 */
	_nts_22,	/* 254 */
	_nts_23,	/* 255 */
	_nts_14,	/* 256 */
	_nts_27,	/* 257 */
	_nts_10,	/* 258 */
	_nts_14,	/* 259 */
	_nts_27,	/* 260 */
	_nts_10,	/* 261 */
	_nts_28,	/* 262 */
	_nts_28,	/* 263 */
	_nts_28,	/* 264 */
	_nts_21,	/* 265 */
	_nts_21,	/* 266 */
	_nts_21,	/* 267 */
	_nts_28,	/* 268 */
	_nts_28,	/* 269 */
	_nts_28,	/* 270 */
	_nts_21,	/* 271 */
	_nts_21,	/* 272 */
	_nts_21,	/* 273 */
	_nts_22,	/* 274 */
	_nts_23,	/* 275 */
	_nts_22,	/* 276 */
	_nts_23,	/* 277 */
	_nts_14,	/* 278 */
	_nts_14,	/* 279 */
	_nts_14,	/* 280 */
	_nts_14,	/* 281 */
	_nts_14,	/* 282 */
	_nts_14,	/* 283 */
	_nts_22,	/* 284 */
	_nts_23,	/* 285 */
	_nts_22,	/* 286 */
	_nts_23,	/* 287 */
	_nts_22,	/* 288 */
	_nts_23,	/* 289 */
	_nts_22,	/* 290 */
	_nts_23,	/* 291 */
	_nts_22,	/* 292 */
	_nts_23,	/* 293 */
	_nts_22,	/* 294 */
	_nts_23,	/* 295 */
	_nts_24,	/* 296 */
	_nts_25,	/* 297 */
	_nts_24,	/* 298 */
	_nts_25,	/* 299 */
	_nts_24,	/* 300 */
	_nts_25,	/* 301 */
	_nts_24,	/* 302 */
	_nts_25,	/* 303 */
	_nts_29,	/* 304 */
	_nts_29,	/* 305 */
	_nts_29,	/* 306 */
	_nts_29,	/* 307 */
	_nts_30,	/* 308 */
	_nts_30,	/* 309 */
	_nts_30,	/* 310 */
	_nts_30,	/* 311 */
	_nts_14,	/* 312 */
	_nts_14,	/* 313 */
	_nts_14,	/* 314 */
	_nts_14,	/* 315 */
	_nts_31,	/* 316 */
	_nts_31,	/* 317 */
	_nts_31,	/* 318 */
	_nts_31,	/* 319 */
	_nts_14,	/* 320 */
	_nts_27,	/* 321 */
	_nts_10,	/* 322 */
	_nts_28,	/* 323 */
	_nts_28,	/* 324 */
	_nts_21,	/* 325 */
	_nts_21,	/* 326 */
	_nts_14,	/* 327 */
	_nts_27,	/* 328 */
	_nts_10,	/* 329 */
	_nts_28,	/* 330 */
	_nts_28,	/* 331 */
	_nts_21,	/* 332 */
	_nts_21,	/* 333 */
	_nts_22,	/* 334 */
	_nts_23,	/* 335 */
	_nts_22,	/* 336 */
	_nts_23,	/* 337 */
	_nts_24,	/* 338 */
	_nts_25,	/* 339 */
	_nts_24,	/* 340 */
	_nts_25,	/* 341 */
	_nts_14,	/* 342 */
	_nts_27,	/* 343 */
	_nts_10,	/* 344 */
	_nts_28,	/* 345 */
	_nts_28,	/* 346 */
	_nts_21,	/* 347 */
	_nts_21,	/* 348 */
	_nts_14,	/* 349 */
	_nts_27,	/* 350 */
	_nts_10,	/* 351 */
	_nts_28,	/* 352 */
	_nts_28,	/* 353 */
	_nts_21,	/* 354 */
	_nts_21,	/* 355 */
	_nts_22,	/* 356 */
	_nts_23,	/* 357 */
	_nts_22,	/* 358 */
	_nts_23,	/* 359 */
	_nts_24,	/* 360 */
	_nts_25,	/* 361 */
	_nts_24,	/* 362 */
	_nts_25,	/* 363 */
	_nts_14,	/* 364 */
	_nts_27,	/* 365 */
	_nts_10,	/* 366 */
	_nts_28,	/* 367 */
	_nts_28,	/* 368 */
	_nts_21,	/* 369 */
	_nts_21,	/* 370 */
	_nts_14,	/* 371 */
	_nts_27,	/* 372 */
	_nts_10,	/* 373 */
	_nts_28,	/* 374 */
	_nts_28,	/* 375 */
	_nts_21,	/* 376 */
	_nts_21,	/* 377 */
	_nts_22,	/* 378 */
	_nts_23,	/* 379 */
	_nts_22,	/* 380 */
	_nts_23,	/* 381 */
	_nts_24,	/* 382 */
	_nts_25,	/* 383 */
	_nts_24,	/* 384 */
	_nts_25,	/* 385 */
	_nts_14,	/* 386 */
	_nts_27,	/* 387 */
	_nts_10,	/* 388 */
	_nts_28,	/* 389 */
	_nts_28,	/* 390 */
	_nts_21,	/* 391 */
	_nts_21,	/* 392 */
	_nts_14,	/* 393 */
	_nts_27,	/* 394 */
	_nts_10,	/* 395 */
	_nts_28,	/* 396 */
	_nts_28,	/* 397 */
	_nts_21,	/* 398 */
	_nts_21,	/* 399 */
	_nts_22,	/* 400 */
	_nts_23,	/* 401 */
	_nts_22,	/* 402 */
	_nts_23,	/* 403 */
	_nts_24,	/* 404 */
	_nts_25,	/* 405 */
	_nts_24,	/* 406 */
	_nts_25,	/* 407 */
	_nts_14,	/* 408 */
	_nts_27,	/* 409 */
	_nts_10,	/* 410 */
	_nts_28,	/* 411 */
	_nts_28,	/* 412 */
	_nts_21,	/* 413 */
	_nts_21,	/* 414 */
	_nts_14,	/* 415 */
	_nts_27,	/* 416 */
	_nts_10,	/* 417 */
	_nts_28,	/* 418 */
	_nts_28,	/* 419 */
	_nts_21,	/* 420 */
	_nts_21,	/* 421 */
	_nts_22,	/* 422 */
	_nts_23,	/* 423 */
	_nts_22,	/* 424 */
	_nts_23,	/* 425 */
	_nts_24,	/* 426 */
	_nts_25,	/* 427 */
	_nts_24,	/* 428 */
	_nts_25,	/* 429 */
	_nts_14,	/* 430 */
	_nts_27,	/* 431 */
	_nts_10,	/* 432 */
	_nts_28,	/* 433 */
	_nts_28,	/* 434 */
	_nts_21,	/* 435 */
	_nts_21,	/* 436 */
	_nts_14,	/* 437 */
	_nts_27,	/* 438 */
	_nts_10,	/* 439 */
	_nts_28,	/* 440 */
	_nts_28,	/* 441 */
	_nts_21,	/* 442 */
	_nts_21,	/* 443 */
	_nts_22,	/* 444 */
	_nts_23,	/* 445 */
	_nts_22,	/* 446 */
	_nts_23,	/* 447 */
	_nts_24,	/* 448 */
	_nts_25,	/* 449 */
	_nts_24,	/* 450 */
	_nts_25,	/* 451 */
	_nts_2,	/* 452 */
	_nts_2,	/* 453 */
	_nts_2,	/* 454 */
	_nts_3,	/* 455 */
	_nts_3,	/* 456 */
	_nts_4,	/* 457 */
	_nts_4,	/* 458 */
	_nts_32,	/* 459 */
	_nts_32,	/* 460 */
	_nts_32,	/* 461 */
	_nts_32,	/* 462 */
	_nts_32,	/* 463 */
	_nts_32,	/* 464 */
	_nts_32,	/* 465 */
	_nts_32,	/* 466 */
	_nts_2,	/* 467 */
	_nts_2,	/* 468 */
	_nts_2,	/* 469 */
	_nts_0,	/* 470 */
	_nts_3,	/* 471 */
	_nts_3,	/* 472 */
	_nts_4,	/* 473 */
	_nts_4,	/* 474 */
	_nts_11,	/* 475 */
	_nts_2,	/* 476 */
	_nts_0,	/* 477 */
};

static char *_templates[] = {
/* 0 */	0,
/* 1 */	"# read register\n",	/* reg8: INDIRI1(VREGP) */
/* 2 */	"# read register\n",	/* reg8: INDIRU1(VREGP) */
/* 3 */	"# read register\n",	/* reg: INDIRI2(VREGP) */
/* 4 */	"# read register\n",	/* reg: INDIRU2(VREGP) */
/* 5 */	"# read register\n",	/* reg32: INDIRI4(VREGP) */
/* 6 */	"# read register\n",	/* reg32: INDIRU4(VREGP) */
/* 7 */	"# read register\n",	/* reg: INDIRP2(VREGP) */
/* 8 */	"# read register\n",	/* regf: INDIRF4(VREGP) */
/* 9 */	"# read register\n",	/* regf: INDIRF8(VREGP) */
/* 10 */	"# write register\n",	/* stmt: ASGNI1(VREGP,reg8) */
/* 11 */	"# write register\n",	/* stmt: ASGNU1(VREGP,reg8) */
/* 12 */	"# write register\n",	/* stmt: ASGNI2(VREGP,reg) */
/* 13 */	"# write register\n",	/* stmt: ASGNU2(VREGP,reg) */
/* 14 */	"# write register\n",	/* stmt: ASGNI4(VREGP,reg32) */
/* 15 */	"# write register\n",	/* stmt: ASGNU4(VREGP,reg32) */
/* 16 */	"# write register\n",	/* stmt: ASGNP2(VREGP,reg) */
/* 17 */	"# write register\n",	/* stmt: ASGNF4(VREGP,regf) */
/* 18 */	"# write register\n",	/* stmt: ASGNF8(VREGP,regf) */
/* 19 */	"",	/* stmt: reg8 */
/* 20 */	"",	/* stmt: reg */
/* 21 */	"",	/* stmt: reg32 */
/* 22 */	"",	/* stmt: regf */
/* 23 */	"\tpush\t%0\n\tpop\t%c\n",	/* reg8: LOADI1(reg8) */
/* 24 */	"\tpush\t%0\n\tpop\t%c\n",	/* reg8: LOADU1(reg8) */
/* 25 */	"# emit2\n",	/* reg8: LOADI1(reg) */
/* 26 */	"# emit2\n",	/* reg8: LOADU1(reg) */
/* 27 */	"?\tmov\t%c,%0\n",	/* reg: LOADI2(reg) */
/* 28 */	"?\tmov\t%c,%0\n",	/* reg: LOADU2(reg) */
/* 29 */	"?\tmov\t%c,%0\n",	/* reg: LOADP2(reg) */
/* 30 */	"\tld\ta,(%0)\n\tst\t(%c),a\n\tld\ta,(%0+2)\n\tst\t(%c+2),a\n",	/* reg32: LOADI4(reg32) */
/* 31 */	"\tld\ta,(%0)\n\tst\t(%c),a\n\tld\ta,(%0+2)\n\tst\t(%c+2),a\n",	/* reg32: LOADU4(reg32) */
/* 32 */	"\tCOPY32(%c,%0)\n",	/* regf: LOADF4(regf) */
/* 33 */	"\tCOPY32(%c,%0)\n",	/* regf: LOADF8(regf) */
/* 34 */	"%0",	/* reg8: LOADU1(LOADU2(CVII2(reg8))) */
/* 35 */	"%0",	/* reg8: LOADI1(LOADI2(CVUU2(reg8))) */
/* 36 */	"# emit2\n",	/* reg8: LOADI1(reg32) */
/* 37 */	"# emit2\n",	/* reg8: LOADU1(reg32) */
/* 38 */	"\tld\t%c,(%0+2)\n",	/* reg: LOADI2(reg32) */
/* 39 */	"\tld\t%c,(%0+2)\n",	/* reg: LOADU2(reg32) */
/* 40 */	"%a",	/* con8: CNSTI1 */
/* 41 */	"%a",	/* con8: CNSTU1 */
/* 42 */	"%a",	/* con16: CNSTI2 */
/* 43 */	"%a",	/* con16: CNSTU2 */
/* 44 */	"%a",	/* con16: CNSTP2 */
/* 45 */	"%a",	/* con0: CNSTI1 */
/* 46 */	"%a",	/* con0: CNSTU1 */
/* 47 */	"%a",	/* con0: CNSTI2 */
/* 48 */	"%a",	/* con0: CNSTU2 */
/* 49 */	"%a",	/* con1: CNSTI1 */
/* 50 */	"%a",	/* con1: CNSTU1 */
/* 51 */	"%a",	/* con1: CNSTI2 */
/* 52 */	"%a",	/* con1: CNSTU2 */
/* 53 */	"%a",	/* con2: CNSTI1 */
/* 54 */	"%a",	/* con2: CNSTU1 */
/* 55 */	"%a",	/* con2: CNSTI2 */
/* 56 */	"%a",	/* con2: CNSTU2 */
/* 57 */	"%a",	/* con: con8 */
/* 58 */	"%a",	/* con: con16 */
/* 59 */	"\tld\t%c,%0\n",	/* reg: con */
/* 60 */	"\tld\t%c,0\n",	/* reg: con0 */
/* 61 */	"\tld\t%c,%0\n",	/* reg8: con8 */
/* 62 */	"dp:%a",	/* lgaddr: ADDRGP2 */
/* 63 */	"sp:%a+2+%F",	/* lgaddr: ADDRFP2 */
/* 64 */	"sp:%a+%F",	/* lgaddr: ADDRLP2 */
/* 65 */	"%0",	/* addr: lgaddr */
/* 66 */	"%0:0",	/* addr: reg */
/* 67 */	"%0:%1",	/* addr: ADDP2(reg,con) */
/* 68 */	"%0:-%1",	/* addr: SUBP2(reg,con) */
/* 69 */	"%a",	/* albl: ADDRGP2 */
/* 70 */	"%0",	/* ar: reg */
/* 71 */	"%0",	/* ar: albl */
/* 72 */	"\tlea\t%c,(%0)\n",	/* reg: lgaddr */
/* 73 */	"\tst\t(%0),%1\n",	/* stmt: ASGNI1(addr,reg8) */
/* 74 */	"\tst\t(%0),%1\n",	/* stmt: ASGNU1(addr,reg8) */
/* 75 */	"\tst\t(%0),%1\n",	/* stmt: ASGNI2(addr,reg) */
/* 76 */	"\tst\t(%0),%1\n",	/* stmt: ASGNU2(addr,reg) */
/* 77 */	"\tst\t(%0),%1\n",	/* stmt: ASGNP2(addr,reg) */
/* 78 */	"# emit2\n",	/* stmt: ASGNB(reg,INDIRB(reg)) */
/* 79 */	"\tCOPY32(%0,%1)\n",	/* stmt: ASGNI4(lgaddr,reg32) */
/* 80 */	"\tCOPY32(%0,%1)\n",	/* stmt: ASGNI4(lgaddr,INDIRI4(lgaddr)) */
/* 81 */	"\tCOPY32(%0,%1)\n",	/* stmt: ASGNU4(lgaddr,reg32) */
/* 82 */	"\tCOPY32(%0,%1)\n",	/* stmt: ASGNU4(lgaddr,INDIRU4(lgaddr)) */
/* 83 */	"\tCOPY32(%0,%1)\n",	/* stmt: ASGNF4(lgaddr,regf) */
/* 84 */	"\tCOPY32(%0,%1)\n",	/* stmt: ASGNF4(lgaddr,INDIRF4(lgaddr)) */
/* 85 */	"\tCOPY32(%0,%1)\n",	/* stmt: ASGNF8(lgaddr,regf) */
/* 86 */	"\tCOPY32(%0,%1)\n",	/* stmt: ASGNF8(lgaddr,INDIRF8(lgaddr)) */
/* 87 */	"\tld\t%c,(%0)\n",	/* reg8: INDIRI1(addr) */
/* 88 */	"\tld\t%c,(%0)\n",	/* reg8: INDIRU1(addr) */
/* 89 */	"\tld\t%c,(%0)\n",	/* reg: INDIRI2(addr) */
/* 90 */	"\tld\t%c,(%0)\n",	/* reg: INDIRU2(addr) */
/* 91 */	"\tld\t%c,(%0)\n",	/* reg: INDIRP2(addr) */
/* 92 */	"\tCOPY32(%c,%0)\n",	/* reg32: INDIRI4(lgaddr) */
/* 93 */	"\tld\ta,(%0)\n\tst\t(%c),a\n\tlea\ta,(%0)\n\tld\ta,(a:2)\n\tst\t(%c+2),a\n",	/* reg32: INDIRU4(lgaddr) */
/* 94 */	"\tCOPY32(%c,%0)\n",	/* regf: INDIRF4(lgaddr) */
/* 95 */	"\tCOPY32(%c,%0)\n",	/* regf: INDIRF8(lgaddr) */
/* 96 */	"\tCOPY32(%c,%0)\n",	/* reg32: INDIRI4(reg) */
/* 97 */	"\tCOPY32(%c,%0)\n",	/* reg32: INDIRU4(reg) */
/* 98 */	"\tCOPY32(%c,%0)\n",	/* regf: INDIRF4(reg) */
/* 99 */	"\tCOPY32(%c,%0)\n",	/* regf: INDIRF8(reg) */
/* 100 */	"\tCVI32I8(%c,%0)\n",	/* reg8: CVII1(reg32) */
/* 101 */	"\tCVI32U8(%c,%0)\n",	/* reg8: CVIU1(reg32) */
/* 102 */	"\tCVU32I8(%c,%0)\n",	/* reg8: CVUI1(reg32) */
/* 103 */	"\tCVU32U8(%c,%0)\n",	/* reg8: CVUU1(reg32) */
/* 104 */	"\tsex\t%c\n",	/* reg: CVII2(reg8) */
/* 105 */	"\tand\t%c,0x00ff\n",	/* reg: CVIU2(reg8) */
/* 106 */	"\tand\t%c,0x00ff\n",	/* reg: CVUI2(reg8) */
/* 107 */	"\tand\t%c,0x00ff\n",	/* reg: CVUU2(reg8) */
/* 108 */	"\tCVI8I32(%c,%0)\n",	/* reg32: CVII4(reg8) */
/* 109 */	"\tCVI8U32(%c,%0)\n",	/* reg32: CVIU4(reg8) */
/* 110 */	"\tCVU8I32(%c,%0)\n",	/* reg32: CVUI4(reg8) */
/* 111 */	"\tCVU8U32(%c,%0)\n",	/* reg32: CVUU4(reg8) */
/* 112 */	"\tCVI16I32(%c,%0)\n",	/* reg32: CVII4(reg) */
/* 113 */	"\tst\t(%c+2),%0\n\tld\ta,0\n\tst\t(%c),a\n",	/* reg32: CVIU4(reg) */
/* 114 */	"\tst\t(%c+2),%0\n\tld\ta,0\n\tst\t(%c),a\n",	/* reg32: CVUI4(reg) */
/* 115 */	"\tst\t(%c+2),%0\n\tld\ta,0\n\tst\t(%c),a\n",	/* reg32: CVUU4(reg) */
/* 116 */	"\tCVTI8F32(%c,%0)\n",	/* regf: CVIF4(reg8) */
/* 117 */	"\tCVTI16F32(%c,%0)\n",	/* regf: CVIF4(reg) */
/* 118 */	"\tCVTI32F32(%c,%0)\n",	/* regf: CVIF4(reg32) */
/* 119 */	"\tCVTI8F64(%c,%0)\n",	/* regf: CVIF8(reg8) */
/* 120 */	"\tCVTI16F64(%c,%0)\n",	/* regf: CVIF8(reg) */
/* 121 */	"\tCVTI32F64(%c,%0)\n",	/* regf: CVIF8(reg32) */
/* 122 */	"\tCVTFI16(%c,%0)\n",	/* reg: CVFI2(regf) */
/* 123 */	"\tCVTFI32(%c,%0)\n",	/* reg: CVFI4(regf) */
/* 124 */	"\tCVTF64F32(%c,%0)\n",	/* regf: CVFF4(regf) */
/* 125 */	"\tCVTF32F64(%c,%0)\n",	/* regf: CVFF8(regf) */
/* 126 */	"\tmov\t%c,%0\n",	/* reg: CVPU2(reg) */
/* 127 */	"\tmov\t%c,%0\n",	/* reg: CVUP2(reg) */
/* 128 */	"?\tmov\t%c,%0\n\tadd\t%c,%1\n",	/* reg: ADDI2(reg,reg) */
/* 129 */	"?\tmov\t%c,%0\n\tadd\t%c,(%1)\n",	/* reg: ADDI2(reg,INDIRI2(addr)) */
/* 130 */	"?\tmov\t%c,%0\n\tadd\t%c,%1\n",	/* reg: ADDI2(reg,con) */
/* 131 */	"?\tmov\t%c,%0\n\tadd\t%c,%1\n",	/* reg: ADDU2(reg,reg) */
/* 132 */	"?\tmov\t%c,%0\n\tadd\t%c,(%1)\n",	/* reg: ADDU2(reg,INDIRU2(addr)) */
/* 133 */	"?\tmov\t%c,%0\n\tadd\t%c,%1\n",	/* reg: ADDU2(reg,con) */
/* 134 */	"?\tmov\t%c,%0\n\tadd\t%c,%1\n",	/* reg: ADDP2(reg,reg) */
/* 135 */	"?\tmov\t%c,%0\n\tadd\t%c,%1\n",	/* reg: ADDP2(reg,con) */
/* 136 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: ADDI2(reg8,CVII2(INDIRI1(addr))) */
/* 137 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: ADDI2(CVII2(reg8),CVII2(INDIRI1(addr))) */
/* 138 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: ADDI2(CVUI2(reg8),CVII2(INDIRI1(addr))) */
/* 139 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: ADDI2(reg8,con) */
/* 140 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: ADDI2(CVII2(reg8),con) */
/* 141 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: ADDI2(CVUI2(reg8),con) */
/* 142 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: ADDU2(reg8,CVUU2(INDIRU1(addr))) */
/* 143 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: ADDU2(CVUU2(reg8),CVUU2(INDIRU1(addr))) */
/* 144 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: ADDU2(CVIU2(reg8),CVUU2(INDIRU1(addr))) */
/* 145 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: ADDU2(reg8,con) */
/* 146 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: ADDU2(CVUU2(reg8),con) */
/* 147 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: ADDU2(CVIU2(reg8),con) */
/* 148 */	"?\tCOPY32(%c,%0)\n\tADDI32(%c,%1)\n",	/* reg32: ADDI4(reg32,reg32) */
/* 149 */	"?\tCOPY32(%c,%0)\n\tADDI32(%c,%1)\n",	/* reg32: ADDI4(reg32,INDIRI4(lgaddr)) */
/* 150 */	"?\tld\ta,(%0)\tst\t(%c),a\tld\ta,(%0+2)\tst\t(%c+2),a\n\tld\ta,(%c+2)\n\tadd\ta,(%1+2)\n\tst\t(%c+2),a\n\tld\ta,(%c)\n\tld\ty,(%1)\n\tadc\ta,y\n\tst\t(%c),a\n",	/* reg32: ADDU4(reg32,reg32) */
/* 151 */	"?\tld\ta,(%0)\tst\t(%c),a\tld\ta,(%0+2)\tst\t(%c+2),a\n\tlea\ty,(%1)\n\tld\ta,(%c+2)\n\tadd\ta,(y:2)\n\tst\t(%c+2),a\n\tld\ta,(%c)\n\tld\ty,(y:0)\n\tadc\ta,y\n\tst\t(%c),a\n",	/* reg32: ADDU4(reg32,INDIRU4(lgaddr)) */
/* 152 */	"?\tCOPY32(%c,%0)\n\tADDF32(%c,%1)\n",	/* regf: ADDF4(regf,regf) */
/* 153 */	"?\tCOPY32(%c,%0)\n\tADDF32(%c,%1)\n",	/* regf: ADDF4(regf,INDIRF4(lgaddr)) */
/* 154 */	"?\tCOPY32(%c,%0)\n\tADDF64(%c,%1)\n",	/* regf: ADDF8(regf,regf) */
/* 155 */	"?\tCOPY32(%c,%0)\n\tADDF64(%c,%1)\n",	/* regf: ADDF8(regf,INDIRF8(lgaddr)) */
/* 156 */	"\tCOPY32(%0,%1)\n\tADDI32(%0,%2)\n",	/* stmt: ASGNI4(lgaddr,ADDI4(INDIRI4(lgaddr),INDIRI4(lgaddr))) */
/* 157 */	"\tADDI32(%1,%2)\n",	/* stmt: ASGNI4(lgaddr,ADDI4(INDIRI4(lgaddr),INDIRI4(lgaddr))) */
/* 158 */	"\tCOPY32(%0,%1)\n\tADDU32(%0,%2)\n",	/* stmt: ASGNU4(lgaddr,ADDU4(INDIRU4(lgaddr),INDIRU4(lgaddr))) */
/* 159 */	"\tADDU32(%1,%2)\n",	/* stmt: ASGNU4(lgaddr,ADDU4(INDIRU4(lgaddr),INDIRU4(lgaddr))) */
/* 160 */	"\tCOPY32(%0,%1)\n\tADDF32(%0,%2)\n",	/* stmt: ASGNF4(lgaddr,ADDF4(INDIRF4(lgaddr),INDIRF4(lgaddr))) */
/* 161 */	"\tADDF32(%1,%2)\n",	/* stmt: ASGNF4(lgaddr,ADDF4(INDIRF4(lgaddr),INDIRF4(lgaddr))) */
/* 162 */	"\tCOPY32(%0,%1)\n\tADDF64(%0,%2)\n",	/* stmt: ASGNF8(lgaddr,ADDF8(INDIRF8(lgaddr),INDIRF8(lgaddr))) */
/* 163 */	"\tADDF64(%1,%2)\n",	/* stmt: ASGNF8(lgaddr,ADDF8(INDIRF8(lgaddr),INDIRF8(lgaddr))) */
/* 164 */	"?\tmov\t%c,%0\n\tsub\t%c,%1\n",	/* reg: SUBI2(reg,reg) */
/* 165 */	"?\tmov\t%c,%0\n\tsub\t%c,(%1)\n",	/* reg: SUBI2(reg,INDIRI2(addr)) */
/* 166 */	"?\tmov\t%c,%0\n\tsub\t%c,%1\n",	/* reg: SUBI2(reg,con) */
/* 167 */	"?\tmov\t%c,%0\n\tsub\t%c,%1\n",	/* reg: SUBU2(reg,reg) */
/* 168 */	"?\tmov\t%c,%0\n\tsub\t%c,(%1)\n",	/* reg: SUBU2(reg,INDIRU2(addr)) */
/* 169 */	"?\tmov\t%c,%0\n\tsub\t%c,%1\n",	/* reg: SUBU2(reg,con) */
/* 170 */	"?\tmov\t%c,%0\n\tsub\t%c,%1\n",	/* reg: SUBP2(reg,reg) */
/* 171 */	"?\tmov\t%c,%0\n\tsub\t%c,%1\n",	/* reg: SUBP2(reg,con) */
/* 172 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: SUBI2(reg8,CVII2(INDIRI1(addr))) */
/* 173 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: SUBI2(CVII2(reg8),CVII2(INDIRI1(addr))) */
/* 174 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: SUBI2(CVUI2(reg8),CVII2(INDIRI1(addr))) */
/* 175 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: SUBI2(reg8,con) */
/* 176 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: SUBI2(CVII2(reg8),con) */
/* 177 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: SUBI2(CVUI2(reg8),con) */
/* 178 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: SUBU2(reg8,CVUU2(INDIRU1(addr))) */
/* 179 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: SUBU2(CVUU2(reg8),CVUU2(INDIRU1(addr))) */
/* 180 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: SUBU2(CVIU2(reg8),CVUU2(INDIRU1(addr))) */
/* 181 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: SUBU2(reg8,con) */
/* 182 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: SUBU2(CVUU2(reg8),con) */
/* 183 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: SUBU2(CVIU2(reg8),con) */
/* 184 */	"?\tCOPY32(%c,%0)\n\tSUBI32(%c,%1)\n",	/* reg32: SUBI4(reg32,reg32) */
/* 185 */	"?\tCOPY32(%c,%0)\n\tSUBI32(%c,%1)\n",	/* reg32: SUBI4(reg32,INDIRI4(lgaddr)) */
/* 186 */	"?\tld\ta,(%0)\tst\t(%c),a\tld\ta,(%0+2)\tst\t(%c+2),a\n\tld\ta,(%c+2)\n\tsub\ta,(%1+2)\n\tst\t(%c+2),a\n\tld\ta,(%c)\n\tld\ty,(%1)\n\tsbc\ta,y\n\tst\t(%c),a\n",	/* reg32: SUBU4(reg32,reg32) */
/* 187 */	"?\tld\ta,(%0)\tst\t(%c),a\tld\ta,(%0+2)\tst\t(%c+2),a\n\tlea\ty,(%1)\n\tld\ta,(%c+2)\n\tsub\ta,(y:2)\n\tst\t(%c+2),a\n\tld\ta,(%c)\n\tld\ty,(y:0)\n\tsbc\ta,y\n\tst\t(%c),a\n",	/* reg32: SUBU4(reg32,INDIRU4(lgaddr)) */
/* 188 */	"?\tCOPY32(%c,%0)\n\tSUBF32(%c,%1)\n",	/* regf: SUBF4(regf,regf) */
/* 189 */	"?\tCOPY32(%c,%0)\n\tSUBF32(%c,%1)\n",	/* regf: SUBF4(regf,INDIRF4(lgaddr)) */
/* 190 */	"?\tCOPY32(%c,%0)\n\tSUBF64(%c,%1)\n",	/* regf: SUBF8(regf,regf) */
/* 191 */	"?\tCOPY32(%c,%0)\n\tSUBF64(%c,%1)\n",	/* regf: SUBF8(regf,INDIRF8(lgaddr)) */
/* 192 */	"\tCOPY32(%0,%1)\n\tSUBI32(%0,%2)\n",	/* stmt: ASGNI4(lgaddr,SUBI4(INDIRI4(lgaddr),INDIRI4(lgaddr))) */
/* 193 */	"\tSUBI32(%1,%2)\n",	/* stmt: ASGNI4(lgaddr,SUBI4(INDIRI4(lgaddr),INDIRI4(lgaddr))) */
/* 194 */	"\tCOPY32(%0,%1)\n\tSUBU32(%0,%2)\n",	/* stmt: ASGNU4(lgaddr,SUBU4(INDIRU4(lgaddr),INDIRU4(lgaddr))) */
/* 195 */	"\tSUBU32(%1,%2)\n",	/* stmt: ASGNU4(lgaddr,SUBU4(INDIRU4(lgaddr),INDIRU4(lgaddr))) */
/* 196 */	"\tCOPY32(%0,%1)\n\tSUBF32(%0,%2)\n",	/* stmt: ASGNF4(lgaddr,SUBF4(INDIRF4(lgaddr),INDIRF4(lgaddr))) */
/* 197 */	"\tSUBF32(%1,%2)\n",	/* stmt: ASGNF4(lgaddr,SUBF4(INDIRF4(lgaddr),INDIRF4(lgaddr))) */
/* 198 */	"\tCOPY32(%0,%1)\n\tSUBF64(%0,%2)\n",	/* stmt: ASGNF8(lgaddr,SUBF8(INDIRF8(lgaddr),INDIRF8(lgaddr))) */
/* 199 */	"\tSUBF64(%1,%2)\n",	/* stmt: ASGNF8(lgaddr,SUBF8(INDIRF8(lgaddr),INDIRF8(lgaddr))) */
/* 200 */	"\tld\t%c,0\n\tsub\t%c,%0\n",	/* reg: NEGI2(reg) */
/* 201 */	"\tld\t%c,0\n\tsub\t%c,(%0)\n",	/* reg: NEGI2(INDIRI2(lgaddr)) */
/* 202 */	"\tNEGI32(%c,%0)\n",	/* reg32: NEGI4(reg32) */
/* 203 */	"\tNEGI32(%c,%0)\n",	/* reg32: NEGI4(INDIRI4(lgaddr)) */
/* 204 */	"\tNEGF32(%c,%0)\n",	/* regf: NEGF4(regf) */
/* 205 */	"\tNEGF32(%c,%0)\n",	/* regf: NEGF4(INDIRF4(lgaddr)) */
/* 206 */	"\tNEGF64(%c,%0)\n",	/* regf: NEGF8(regf) */
/* 207 */	"\tNEGF64(%c,%0)\n",	/* regf: NEGF8(INDIRF8(lgaddr)) */
/* 208 */	"?\tmov\t%c,%0\n\tand\t%c,%1\n",	/* reg: BANDI2(reg,reg) */
/* 209 */	"?\tmov\t%c,%0\n\tand\t%c,(%1)\n",	/* reg: BANDI2(reg,INDIRI2(lgaddr)) */
/* 210 */	"?\tmov\t%c,%0\n\tand\t%c,%1\n",	/* reg: BANDI2(reg,con) */
/* 211 */	"?\tmov\t%c,%0\n\tand\t%c,%1\n",	/* reg: BANDU2(reg,reg) */
/* 212 */	"?\tmov\t%c,%0\n\tand\t%c,(%1)\n",	/* reg: BANDU2(reg,INDIRU2(lgaddr)) */
/* 213 */	"?\tmov\t%c,%0\n\tand\t%c,%1\n",	/* reg: BANDU2(reg,con) */
/* 214 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BANDI2(reg8,CVII2(INDIRI1(lgaddr))) */
/* 215 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BANDI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 216 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BANDI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 217 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BANDI2(reg8,con) */
/* 218 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BANDI2(CVII2(reg8),con) */
/* 219 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BANDI2(CVUI2(reg8),con) */
/* 220 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BANDU2(reg8,CVUU2(INDIRU1(lgaddr))) */
/* 221 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BANDU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 222 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BANDU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 223 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BANDU2(reg8,con) */
/* 224 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BANDU2(CVUU2(reg8),con) */
/* 225 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BANDU2(CVIU2(reg8),con) */
/* 226 */	"?\tCOPY32(%c,%0)\n\tBANDI32(%c,%1)\n",	/* reg32: BANDI4(reg32,reg32) */
/* 227 */	"?\tCOPY32(%c,%0)\n\tBANDI32(%c,%1)\n",	/* reg32: BANDI4(reg32,INDIRI4(lgaddr)) */
/* 228 */	"?\tCOPY32(%c,%0)\n\tBANDI32(%c,%1)\n",	/* reg32: BANDU4(reg32,reg32) */
/* 229 */	"?\tCOPY32(%c,%0)\n\tBANDI32(%c,%1)\n",	/* reg32: BANDU4(reg32,INDIRU4(lgaddr)) */
/* 230 */	"\tmov\t%c,-1\n\txor\t%c,%0\n",	/* reg: BCOMI2(reg) */
/* 231 */	"\tmov\t%c,-1\n\txor\t%c,%0\n",	/* reg: BCOMU2(reg) */
/* 232 */	"\tBCOMI32(%c,%0)\n",	/* reg32: BCOMI4(reg32) */
/* 233 */	"\tBCOMI32(%c,%0)\n",	/* reg32: BCOMU4(reg32) */
/* 234 */	"?\tmov\t%c,%0\n\tor\t%c,%1\n",	/* reg: BORI2(reg,reg) */
/* 235 */	"?\tmov\t%c,%0\n\tor\t%c,(%1)\n",	/* reg: BORI2(reg,INDIRI2(lgaddr)) */
/* 236 */	"?\tmov\t%c,%0\n\tor\t%c,%1\n",	/* reg: BORI2(reg,con) */
/* 237 */	"?\tmov\t%c,%0\n\tor\t%c,%1\n",	/* reg: BORU2(reg,reg) */
/* 238 */	"?\tmov\t%c,%0\n\tor\t%c,(%1)\n",	/* reg: BORU2(reg,INDIRU2(lgaddr)) */
/* 239 */	"?\tmov\t%c,%0\n\tor\t%c,%1\n",	/* reg: BORU2(reg,con) */
/* 240 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BORI2(reg8,CVII2(INDIRI1(lgaddr))) */
/* 241 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BORI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 242 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BORI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 243 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BORI2(reg8,con) */
/* 244 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BORI2(CVII2(reg8),con) */
/* 245 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BORI2(CVUI2(reg8),con) */
/* 246 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BORU2(reg8,CVUU2(INDIRU1(lgaddr))) */
/* 247 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BORU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 248 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BORU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 249 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BORU2(reg8,con) */
/* 250 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BORU2(CVUU2(reg8),con) */
/* 251 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BORU2(CVIU2(reg8),con) */
/* 252 */	"?\tCOPY32(%c,%0)\n\tBORI32(%c,%1)\n",	/* reg32: BORI4(reg32,reg32) */
/* 253 */	"?\tCOPY32(%c,%0)\n\tBORI32(%c,%1)\n",	/* reg32: BORI4(reg32,INDIRI4(lgaddr)) */
/* 254 */	"?\tCOPY32(%c,%0)\n\tBORI32(%c,%1)\n",	/* reg32: BORU4(reg32,reg32) */
/* 255 */	"?\tCOPY32(%c,%0)\n\tBORI32(%c,%1)\n",	/* reg32: BORU4(reg32,INDIRU4(lgaddr)) */
/* 256 */	"?\tmov\t%c,%0\n\txor\t%c,%1\n",	/* reg: BXORI2(reg,reg) */
/* 257 */	"?\tmov\t%c,%0\n\txor\t%c,(%1)\n",	/* reg: BXORI2(reg,INDIRI2(lgaddr)) */
/* 258 */	"?\tmov\t%c,%0\n\txor\t%c,%1\n",	/* reg: BXORI2(reg,con) */
/* 259 */	"?\tmov\t%c,%0\n\txor\t%c,%1\n",	/* reg: BXORU2(reg,reg) */
/* 260 */	"?\tmov\t%c,%0\n\txor\t%c,(%1)\n",	/* reg: BXORU2(reg,INDIRU2(lgaddr)) */
/* 261 */	"?\tmov\t%c,%0\n\txor\t%c,%1\n",	/* reg: BXORU2(reg,con) */
/* 262 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BXORI2(reg8,CVII2(INDIRI1(lgaddr))) */
/* 263 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BXORI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 264 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BXORI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 265 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BXORI2(reg8,con) */
/* 266 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BXORI2(CVII2(reg8),con) */
/* 267 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BXORI2(CVUI2(reg8),con) */
/* 268 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BXORU2(reg8,CVUU2(INDIRU1(lgaddr))) */
/* 269 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BXORU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 270 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BXORU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 271 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BXORU2(reg8,con) */
/* 272 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BXORU2(CVUU2(reg8),con) */
/* 273 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BXORU2(CVIU2(reg8),con) */
/* 274 */	"?\tCOPY32(%c,%0)\n\tBXORI32(%c,%1)\n",	/* reg32: BXORI4(reg32,reg32) */
/* 275 */	"?\tCOPY32(%c,%0)\n\tBXORI32(%c,%1)\n",	/* reg32: BXORI4(reg32,INDIRI4(lgaddr)) */
/* 276 */	"?\tCOPY32(%c,%0)\n\tBXORI32(%c,%1)\n",	/* reg32: BXORU4(reg32,reg32) */
/* 277 */	"?\tCOPY32(%c,%0)\n\tBXORI32(%c,%1)\n",	/* reg32: BXORU4(reg32,INDIRU4(lgaddr)) */
/* 278 */	"?\tmov\t%c,%0\n\tcall\t__muli16\n",	/* reg: MULI2(reg,reg) */
/* 279 */	"?\tmov\t%c,%0\n\tcall\t__mulu16\n",	/* reg: MULU2(reg,reg) */
/* 280 */	"?\tmov\t%c,%0\n\tcall\t__divi16\n",	/* reg: DIVI2(reg,reg) */
/* 281 */	"?\tmov\t%c,%0\n\tcall\t__divu16\n",	/* reg: DIVU2(reg,reg) */
/* 282 */	"?\tmov\t%c,%0\n\tcall\t__modi16\n",	/* reg: MODI2(reg,reg) */
/* 283 */	"?\tmov\t%c,%0\n\tcall\t__modu16\n",	/* reg: MODU2(reg,reg) */
/* 284 */	"?\tCOPY32(%c,%0)\n\tMULI32(%c,%1)\n",	/* reg32: MULI4(reg32,reg32) */
/* 285 */	"?\tCOPY32(%c,%0)\n\tMULI32(%c,%1)\n",	/* reg32: MULI4(reg32,INDIRI4(lgaddr)) */
/* 286 */	"?\tCOPY32(%c,%0)\n\tMULU32(%c,%1)\n",	/* reg32: MULU4(reg32,reg32) */
/* 287 */	"?\tCOPY32(%c,%0)\n\tMULU32(%c,%1)\n",	/* reg32: MULU4(reg32,INDIRU4(lgaddr)) */
/* 288 */	"?\tCOPY32(%c,%0)\n\tDIVI32(%c,%1)\n",	/* reg32: DIVI4(reg32,reg32) */
/* 289 */	"?\tCOPY32(%c,%0)\n\tDIVI32(%c,%1)\n",	/* reg32: DIVI4(reg32,INDIRI4(lgaddr)) */
/* 290 */	"?\tCOPY32(%c,%0)\n\tDIVU32(%c,%1)\n",	/* reg32: DIVU4(reg32,reg32) */
/* 291 */	"?\tCOPY32(%c,%0)\n\tDIVU32(%c,%1)\n",	/* reg32: DIVU4(reg32,INDIRU4(lgaddr)) */
/* 292 */	"?\tCOPY32(%c,%0)\n\tMODI32(%c,%1)\n",	/* reg32: MODI4(reg32,reg32) */
/* 293 */	"?\tCOPY32(%c,%0)\n\tMODI32(%c,%1)\n",	/* reg32: MODI4(reg32,INDIRI4(lgaddr)) */
/* 294 */	"?\tCOPY32(%c,%0)\n\tMODU32(%c,%1)\n",	/* reg32: MODU4(reg32,reg32) */
/* 295 */	"?\tCOPY32(%c,%0)\n\tMODU32(%c,%1)\n",	/* reg32: MODU4(reg32,INDIRU4(lgaddr)) */
/* 296 */	"?\tCOPY32(%c,%0)\n\tMULF32(%c,%1)\n",	/* regf: MULF4(regf,regf) */
/* 297 */	"?\tCOPY32(%c,%0)\n\tMULF32(%c,%1)\n",	/* regf: MULF4(regf,INDIRF4(lgaddr)) */
/* 298 */	"?\tCOPY32(%c,%0)\n\tMULF64(%c,%1)\n",	/* regf: MULF8(regf,regf) */
/* 299 */	"?\tCOPY32(%c,%0)\n\tMULF64(%c,%1)\n",	/* regf: MULF8(regf,INDIRF8(lgaddr)) */
/* 300 */	"?\tCOPY32(%c,%0)\n\tDIVF32(%c,%1)\n",	/* regf: DIVF4(regf,regf) */
/* 301 */	"?\tCOPY32(%c,%0)\n\tDIVF32(%c,%1)\n",	/* regf: DIVF4(regf,INDIRF4(lgaddr)) */
/* 302 */	"?\tCOPY32(%c,%0)\n\tDIVF64(%c,%1)\n",	/* regf: DIVF8(regf,regf) */
/* 303 */	"?\tCOPY32(%c,%0)\n\tDIVF64(%c,%1)\n",	/* regf: DIVF8(regf,INDIRF8(lgaddr)) */
/* 304 */	"?\tmov\t%c,%0\n\tshl\t%c\n",	/* reg: LSHI2(reg,con1) */
/* 305 */	"?\tmov\t%c,%0\n\tshl\t%c\n",	/* reg: LSHU2(reg,con1) */
/* 306 */	"?\tmov\t%c,%0\n\tshr\t%c\n",	/* reg: RSHI2(reg,con1) */
/* 307 */	"?\tmov\t%c,%0\n\tshr\t%c\n",	/* reg: RSHU2(reg,con1) */
/* 308 */	"?\tmov\t%c,%0\n\tshl\t%c\n\tshl\t%c\n",	/* reg: LSHI2(reg,con2) */
/* 309 */	"?\tmov\t%c,%0\n\tshl\t%c\n\tshl\t%c\n",	/* reg: LSHU2(reg,con2) */
/* 310 */	"?\tmov\t%c,%0\n\tshr\t%c\n\tshr\t%c\n",	/* reg: RSHI2(reg,con2) */
/* 311 */	"?\tmov\t%c,%0\n\tshr\t%c\n\tshr\t%c\n",	/* reg: RSHU2(reg,con2) */
/* 312 */	"# emit2 (loop)\n",	/* reg: LSHI2(reg,reg) */
/* 313 */	"# emit2 (loop)\n",	/* reg: LSHU2(reg,reg) */
/* 314 */	"# emit2 (loop)\n",	/* reg: RSHI2(reg,reg) */
/* 315 */	"# emit2 (loop)\n",	/* reg: RSHU2(reg,reg) */
/* 316 */	"?\tCOPY32(%c,%0)\n\tLSHI32(%0)\n",	/* reg32: LSHI4(reg32,con1) */
/* 317 */	"?\tld\ta,(%0)\tst\t(%c),a\tld\ta,(%0+2)\tst\t(%c+2),a\n\tld\ta,(%c)\n\tshl\ta\nst\t(%c),a\n\tld\ta,(%c+2)\n\tshl\ta\nst\t(%c+2),a\n\tld\ta,(%c)\n\tld\ty,0\n\tadc\ta,y\n\tst\t(%c),a\n",	/* reg32: LSHU4(reg32,con1) */
/* 318 */	"?\tCOPY32(%c,%0)\n\tRSHI32(%0)\n",	/* reg32: RSHI4(reg32,con1) */
/* 319 */	"?\tCOPY32(%c,%0)\n\tRSHU32(%0)\n",	/* reg32: RSHU4(reg32,con1) */
/* 320 */	"\tcmp\t%0,%1\n\tje\t%a\n",	/* stmt: EQI2(reg,reg) */
/* 321 */	"\tcmp\t%0,(%1)\n\tje\t%a\n",	/* stmt: EQI2(reg,INDIRI2(lgaddr)) */
/* 322 */	"\tcmp\t%0,%1\n\tje\t%a\n",	/* stmt: EQI2(reg,con) */
/* 323 */	"\tcmp\t%0,(%1)\n\tje\t%a\n",	/* stmt: EQI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 324 */	"\tcmp\t%0,(%1)\n\tje\t%a\n",	/* stmt: EQI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 325 */	"\tcmp\t%0,%1\n\tje\t%a\n",	/* stmt: EQI2(CVII2(reg8),con) */
/* 326 */	"\tcmp\t%0,%1\n\tje\t%a\n",	/* stmt: EQI2(CVUI2(reg8),con) */
/* 327 */	"\tcmp\t%0,%1\n\tje\t%a\n",	/* stmt: EQU2(reg,reg) */
/* 328 */	"\tcmp\t%0,(%1)\n\tje\t%a\n",	/* stmt: EQU2(reg,INDIRU2(lgaddr)) */
/* 329 */	"\tcmp\t%0,%1\n\tje\t%a\n",	/* stmt: EQU2(reg,con) */
/* 330 */	"\tcmp\t%0,(%1)\n\tje\t%a\n",	/* stmt: EQU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 331 */	"\tcmp\t%0,(%1)\n\tje\t%a\n",	/* stmt: EQU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 332 */	"\tcmp\t%0,%1\n\tje\t%a\n",	/* stmt: EQU2(CVUU2(reg8),con) */
/* 333 */	"\tcmp\t%0,%1\n\tje\t%a\n",	/* stmt: EQU2(CVIU2(reg8),con) */
/* 334 */	"\tCMP32(%0,%1)\n\tje\t%a\n",	/* stmt: EQI4(reg32,reg32) */
/* 335 */	"\tCMP32(%0,%1)\n\tje\t%a\n",	/* stmt: EQI4(reg32,INDIRI4(lgaddr)) */
/* 336 */	"\tCMP32(%0,%1)\n\tje\t%a\n",	/* stmt: EQU4(reg32,reg32) */
/* 337 */	"\tCMP32(%0,%1)\n\tje\t%a\n",	/* stmt: EQU4(reg32,INDIRU4(lgaddr)) */
/* 338 */	"\tCMP32(%0,%1)\n\tje\t%a\n",	/* stmt: EQF4(regf,regf) */
/* 339 */	"\tCMP32(%0,%1)\n\tje\t%a\n",	/* stmt: EQF4(regf,INDIRF4(lgaddr)) */
/* 340 */	"\tCMP64(%0,%1)\n\tje\t%a\n",	/* stmt: EQF8(regf,regf) */
/* 341 */	"\tCMP64(%0,%1)\n\tje\t%a\n",	/* stmt: EQF8(regf,INDIRF8(lgaddr)) */
/* 342 */	"\tcmp\t%0,%1\n\tjne\t%a\n",	/* stmt: NEI2(reg,reg) */
/* 343 */	"\tcmp\t%0,(%1)\n\tjne\t%a\n",	/* stmt: NEI2(reg,INDIRI2(lgaddr)) */
/* 344 */	"\tcmp\t%0,%1\n\tjne\t%a\n",	/* stmt: NEI2(reg,con) */
/* 345 */	"\tcmp\t%0,(%1)\n\tjne\t%a\n",	/* stmt: NEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 346 */	"\tcmp\t%0,(%1)\n\tjne\t%a\n",	/* stmt: NEI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 347 */	"\tcmp\t%0,%1\n\tjne\t%a\n",	/* stmt: NEI2(CVII2(reg8),con) */
/* 348 */	"\tcmp\t%0,%1\n\tjne\t%a\n",	/* stmt: NEI2(CVUI2(reg8),con) */
/* 349 */	"\tcmp\t%0,%1\n\tjne\t%a\n",	/* stmt: NEU2(reg,reg) */
/* 350 */	"\tcmp\t%0,(%1)\n\tjne\t%a\n",	/* stmt: NEU2(reg,INDIRU2(lgaddr)) */
/* 351 */	"\tcmp\t%0,%1\n\tjne\t%a\n",	/* stmt: NEU2(reg,con) */
/* 352 */	"\tcmp\t%0,(%1)\n\tjne\t%a\n",	/* stmt: NEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 353 */	"\tcmp\t%0,(%1)\n\tjne\t%a\n",	/* stmt: NEU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 354 */	"\tcmp\t%0,%1\n\tjne\t%a\n",	/* stmt: NEU2(CVUU2(reg8),con) */
/* 355 */	"\tcmp\t%0,%1\n\tjne\t%a\n",	/* stmt: NEU2(CVIU2(reg8),con) */
/* 356 */	"\tCMP32(%0,%1)\n\tjne\t%a\n",	/* stmt: NEI4(reg32,reg32) */
/* 357 */	"\tCMP32(%0,%1)\n\tjne\t%a\n",	/* stmt: NEI4(reg32,INDIRI4(lgaddr)) */
/* 358 */	"\tCMP32(%0,%1)\n\tjne\t%a\n",	/* stmt: NEU4(reg32,reg32) */
/* 359 */	"\tCMP32(%0,%1)\n\tjne\t%a\n",	/* stmt: NEU4(reg32,INDIRU4(lgaddr)) */
/* 360 */	"\tCMP32(%0,%1)\n\tjne\t%a\n",	/* stmt: NEF4(regf,regf) */
/* 361 */	"\tCMP32(%0,%1)\n\tjne\t%a\n",	/* stmt: NEF4(regf,INDIRF4(lgaddr)) */
/* 362 */	"\tCMP64(%0,%1)\n\tjne\t%a\n",	/* stmt: NEF8(regf,regf) */
/* 363 */	"\tCMP64(%0,%1)\n\tjne\t%a\n",	/* stmt: NEF8(regf,INDIRF8(lgaddr)) */
/* 364 */	"\tcmp\t%0,%1\n\tjle\t%a\n",	/* stmt: LEI2(reg,reg) */
/* 365 */	"\tcmp\t%0,(%1)\n\tjle\t%a\n",	/* stmt: LEI2(reg,INDIRI2(lgaddr)) */
/* 366 */	"\tcmp\t%0,%1\n\tjle\t%a\n",	/* stmt: LEI2(reg,con) */
/* 367 */	"\tcmp\t%0,(%1)\n\tjle\t%a\n",	/* stmt: LEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 368 */	"\tcmp\t%0,(%1)\n\tjle\t%a\n",	/* stmt: LEI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 369 */	"\tcmp\t%0,%1\n\tjle\t%a\n",	/* stmt: LEI2(CVII2(reg8),con) */
/* 370 */	"\tcmp\t%0,%1\n\tjle\t%a\n",	/* stmt: LEI2(CVUI2(reg8),con) */
/* 371 */	"\tcmp\t%0,%1\n\tjleu\t%a\n",	/* stmt: LEU2(reg,reg) */
/* 372 */	"\tcmp\t%0,(%1)\n\tjleu\t%a\n",	/* stmt: LEU2(reg,INDIRU2(lgaddr)) */
/* 373 */	"\tcmp\t%0,%1\n\tjleu\t%a\n",	/* stmt: LEU2(reg,con) */
/* 374 */	"\tcmp\t%0,(%1)\n\tjleu\t%a\n",	/* stmt: LEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 375 */	"\tcmp\t%0,(%1)\n\tjleu\t%a\n",	/* stmt: LEU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 376 */	"\tcmp\t%0,%1\n\tjleu\t%a\n",	/* stmt: LEU2(CVUU2(reg8),con) */
/* 377 */	"\tcmp\t%0,%1\n\tjleu\t%a\n",	/* stmt: LEU2(CVIU2(reg8),con) */
/* 378 */	"\tCMP32(%0,%1)\n\tjle\t%a\n",	/* stmt: LEI4(reg32,reg32) */
/* 379 */	"\tCMP32(%0,%1)\n\tjle\t%a\n",	/* stmt: LEI4(reg32,INDIRI4(lgaddr)) */
/* 380 */	"\tCMP32(%0,%1)\n\tjleu\t%a\n",	/* stmt: LEU4(reg32,reg32) */
/* 381 */	"\tCMP32(%0,%1)\n\tjleu\t%a\n",	/* stmt: LEU4(reg32,INDIRU4(lgaddr)) */
/* 382 */	"\tCMP32(%0,%1)\n\tjle\t%a\n",	/* stmt: LEF4(regf,regf) */
/* 383 */	"\tCMP32(%0,%1)\n\tjle\t%a\n",	/* stmt: LEF4(regf,INDIRF4(lgaddr)) */
/* 384 */	"\tCMP64(%0,%1)\n\tjle\t%a\n",	/* stmt: LEF8(regf,regf) */
/* 385 */	"\tCMP64(%0,%1)\n\tjle\t%a\n",	/* stmt: LEF8(regf,INDIRF8(lgaddr)) */
/* 386 */	"\tcmp\t%0,%1\n\tjl\t%a\n",	/* stmt: LTI2(reg,reg) */
/* 387 */	"\tcmp\t%0,(%1)\n\tjl\t%a\n",	/* stmt: LTI2(reg,INDIRI2(lgaddr)) */
/* 388 */	"\tcmp\t%0,%1\n\tjl\t%a\n",	/* stmt: LTI2(reg,con) */
/* 389 */	"\tcmp\t%0,(%1)\n\tjl\t%a\n",	/* stmt: LTI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 390 */	"\tcmp\t%0,(%1)\n\tjl\t%a\n",	/* stmt: LTI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 391 */	"\tcmp\t%0,%1\n\tjl\t%a\n",	/* stmt: LTI2(CVII2(reg8),con) */
/* 392 */	"\tcmp\t%0,%1\n\tjl\t%a\n",	/* stmt: LTI2(CVUI2(reg8),con) */
/* 393 */	"\tcmp\t%0,%1\n\tjlu\t%a\n",	/* stmt: LTU2(reg,reg) */
/* 394 */	"\tcmp\t%0,(%1)\n\tjlu\t%a\n",	/* stmt: LTU2(reg,INDIRU2(lgaddr)) */
/* 395 */	"\tcmp\t%0,%1\n\tjlu\t%a\n",	/* stmt: LTU2(reg,con) */
/* 396 */	"\tcmp\t%0,(%1)\n\tjlu\t%a\n",	/* stmt: LTU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 397 */	"\tcmp\t%0,(%1)\n\tjlu\t%a\n",	/* stmt: LTU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 398 */	"\tcmp\t%0,%1\n\tjlu\t%a\n",	/* stmt: LTU2(CVUU2(reg8),con) */
/* 399 */	"\tcmp\t%0,%1\n\tjlu\t%a\n",	/* stmt: LTU2(CVIU2(reg8),con) */
/* 400 */	"\tCMP32(%0,%1)\n\tjl\t%a\n",	/* stmt: LTI4(reg32,reg32) */
/* 401 */	"\tCMP32(%0,%1)\n\tjl\t%a\n",	/* stmt: LTI4(reg32,INDIRI4(lgaddr)) */
/* 402 */	"\tCMP32(%0,%1)\n\tjlu\t%a\n",	/* stmt: LTU4(reg32,reg32) */
/* 403 */	"\tCMP32(%0,%1)\n\tjlu\t%a\n",	/* stmt: LTU4(reg32,INDIRU4(lgaddr)) */
/* 404 */	"\tCMP32(%0,%1)\n\tjl\t%a\n",	/* stmt: LTF4(regf,regf) */
/* 405 */	"\tCMP32(%0,%1)\n\tjl\t%a\n",	/* stmt: LTF4(regf,INDIRF4(lgaddr)) */
/* 406 */	"\tCMP64(%0,%1)\n\tjl\t%a\n",	/* stmt: LTF8(regf,regf) */
/* 407 */	"\tCMP64(%0,%1)\n\tjl\t%a\n",	/* stmt: LTF8(regf,INDIRF8(lgaddr)) */
/* 408 */	"\tcmp\t%0,%1\n\tjge\t%a\n",	/* stmt: GEI2(reg,reg) */
/* 409 */	"\tcmp\t%0,(%1)\n\tjge\t%a\n",	/* stmt: GEI2(reg,INDIRI2(lgaddr)) */
/* 410 */	"\tcmp\t%0,%1\n\tjge\t%a\n",	/* stmt: GEI2(reg,con) */
/* 411 */	"\tcmp\t%0,(%1)\n\tjge\t%a\n",	/* stmt: GEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 412 */	"\tcmp\t%0,(%1)\n\tjge\t%a\n",	/* stmt: GEI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 413 */	"\tcmp\t%0,%1\n\tjge\t%a\n",	/* stmt: GEI2(CVII2(reg8),con) */
/* 414 */	"\tcmp\t%0,%1\n\tjge\t%a\n",	/* stmt: GEI2(CVUI2(reg8),con) */
/* 415 */	"\tcmp\t%0,%1\n\tjgeu\t%a\n",	/* stmt: GEU2(reg,reg) */
/* 416 */	"\tcmp\t%0,(%1)\n\tjgeu\t%a\n",	/* stmt: GEU2(reg,INDIRU2(lgaddr)) */
/* 417 */	"\tcmp\t%0,%1\n\tjgeu\t%a\n",	/* stmt: GEU2(reg,con) */
/* 418 */	"\tcmp\t%0,(%1)\n\tjgeu\t%a\n",	/* stmt: GEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 419 */	"\tcmp\t%0,(%1)\n\tjgeu\t%a\n",	/* stmt: GEU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 420 */	"\tcmp\t%0,%1\n\tjgeu\t%a\n",	/* stmt: GEU2(CVUU2(reg8),con) */
/* 421 */	"\tcmp\t%0,%1\n\tjgeu\t%a\n",	/* stmt: GEU2(CVIU2(reg8),con) */
/* 422 */	"\tCMP32(%0,%1)\n\tjge\t%a\n",	/* stmt: GEI4(reg32,reg32) */
/* 423 */	"\tCMP32(%0,%1)\n\tjge\t%a\n",	/* stmt: GEI4(reg32,INDIRI4(lgaddr)) */
/* 424 */	"\tCMP32(%0,%1)\n\tjgeu\t%a\n",	/* stmt: GEU4(reg32,reg32) */
/* 425 */	"\tCMP32(%0,%1)\n\tjgeu\t%a\n",	/* stmt: GEU4(reg32,INDIRU4(lgaddr)) */
/* 426 */	"\tCMP32(%0,%1)\n\tjge\t%a\n",	/* stmt: GEF4(regf,regf) */
/* 427 */	"\tCMP32(%0,%1)\n\tjge\t%a\n",	/* stmt: GEF4(regf,INDIRF4(lgaddr)) */
/* 428 */	"\tCMP64(%0,%1)\n\tjge\t%a\n",	/* stmt: GEF8(regf,regf) */
/* 429 */	"\tCMP64(%0,%1)\n\tjge\t%a\n",	/* stmt: GEF8(regf,INDIRF8(lgaddr)) */
/* 430 */	"\tcmp\t%0,%1\n\tjg\t%a\n",	/* stmt: GTI2(reg,reg) */
/* 431 */	"\tcmp\t%0,(%1)\n\tjg\t%a\n",	/* stmt: GTI2(reg,INDIRI2(lgaddr)) */
/* 432 */	"\tcmp\t%0,%1\n\tjg\t%a\n",	/* stmt: GTI2(reg,con) */
/* 433 */	"\tcmp\t%0,(%1)\n\tjg\t%a\n",	/* stmt: GTI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 434 */	"\tcmp\t%0,(%1)\n\tjg\t%a\n",	/* stmt: GTI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 435 */	"\tcmp\t%0,%1\n\tjg\t%a\n",	/* stmt: GTI2(CVII2(reg8),con) */
/* 436 */	"\tcmp\t%0,%1\n\tjg\t%a\n",	/* stmt: GTI2(CVUI2(reg8),con) */
/* 437 */	"\tcmp\t%0,%1\n\tjgu\t%a\n",	/* stmt: GTU2(reg,reg) */
/* 438 */	"\tcmp\t%0,(%1)\n\tjgu\t%a\n",	/* stmt: GTU2(reg,INDIRU2(lgaddr)) */
/* 439 */	"\tcmp\t%0,%1\n\tjgu\t%a\n",	/* stmt: GTU2(reg,con) */
/* 440 */	"\tcmp\t%0,(%1)\n\tjgu\t%a\n",	/* stmt: GTU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 441 */	"\tcmp\t%0,(%1)\n\tjgu\t%a\n",	/* stmt: GTU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 442 */	"\tcmp\t%0,%1\n\tjgu\t%a\n",	/* stmt: GTU2(CVUU2(reg8),con) */
/* 443 */	"\tcmp\t%0,%1\n\tjgu\t%a\n",	/* stmt: GTU2(CVIU2(reg8),con) */
/* 444 */	"\tCMP32(%0,%1)\n\tjg\t%a\n",	/* stmt: GTI4(reg32,reg32) */
/* 445 */	"\tCMP32(%0,%1)\n\tjg\t%a\n",	/* stmt: GTI4(reg32,INDIRI4(lgaddr)) */
/* 446 */	"\tCMP32(%0,%1)\n\tjgu\t%a\n",	/* stmt: GTU4(reg32,reg32) */
/* 447 */	"\tCMP32(%0,%1)\n\tjgu\t%a\n",	/* stmt: GTU4(reg32,INDIRU4(lgaddr)) */
/* 448 */	"\tCMP32(%0,%1)\n\tjg\t%a\n",	/* stmt: GTF4(regf,regf) */
/* 449 */	"\tCMP32(%0,%1)\n\tjg\t%a\n",	/* stmt: GTF4(regf,INDIRF4(lgaddr)) */
/* 450 */	"\tCMP64(%0,%1)\n\tjg\t%a\n",	/* stmt: GTF8(regf,regf) */
/* 451 */	"\tCMP64(%0,%1)\n\tjg\t%a\n",	/* stmt: GTF8(regf,INDIRF8(lgaddr)) */
/* 452 */	"# emit2\n",	/* stmt: ARGI2(reg) */
/* 453 */	"# emit2\n",	/* stmt: ARGU2(reg) */
/* 454 */	"# emit2\n",	/* stmt: ARGP2(reg) */
/* 455 */	"# emit2\n",	/* stmt: ARGI4(reg32) */
/* 456 */	"# emit2\n",	/* stmt: ARGU4(reg32) */
/* 457 */	"# emit2\n",	/* stmt: ARGF4(regf) */
/* 458 */	"# emit2\n",	/* stmt: ARGF8(regf) */
/* 459 */	"\tcall\t%0\n",	/* reg: CALLI2(ar) */
/* 460 */	"\tcall\t%0\n",	/* reg: CALLU2(ar) */
/* 461 */	"\tcall\t%0\n",	/* reg: CALLP2(ar) */
/* 462 */	"\tcall\t%0\n",	/* stmt: CALLV(ar) */
/* 463 */	"# emit2\n",	/* reg32: CALLI4(ar) */
/* 464 */	"# emit2\n",	/* reg32: CALLU4(ar) */
/* 465 */	"# emit2\n",	/* regf: CALLF4(ar) */
/* 466 */	"\tlea\tx,%c\n\tcall\t%0\n",	/* regf: CALLF8(ar) */
/* 467 */	"# return\n",	/* stmt: RETI2(reg) */
/* 468 */	"# return\n",	/* stmt: RETU2(reg) */
/* 469 */	"# return\n",	/* stmt: RETP2(reg) */
/* 470 */	"# return\n",	/* stmt: RETV */
/* 471 */	"# return\n",	/* stmt: RETI4(reg32) */
/* 472 */	"# return\n",	/* stmt: RETU4(reg32) */
/* 473 */	"# return\n",	/* stmt: RETF4(regf) */
/* 474 */	"# return\n",	/* stmt: RETF8(regf) */
/* 475 */	"\tjmp\t%0\n",	/* stmt: JUMPV(albl) */
/* 476 */	"\tjmp\t%0\n",	/* stmt: JUMPV(reg) */
/* 477 */	"%a:\n",	/* stmt: LABELV */
};

static char _isinstruction[] = {
/* 0 */	0,
/* 1 */	1,	/* # read register\n */
/* 2 */	1,	/* # read register\n */
/* 3 */	1,	/* # read register\n */
/* 4 */	1,	/* # read register\n */
/* 5 */	1,	/* # read register\n */
/* 6 */	1,	/* # read register\n */
/* 7 */	1,	/* # read register\n */
/* 8 */	1,	/* # read register\n */
/* 9 */	1,	/* # read register\n */
/* 10 */	1,	/* # write register\n */
/* 11 */	1,	/* # write register\n */
/* 12 */	1,	/* # write register\n */
/* 13 */	1,	/* # write register\n */
/* 14 */	1,	/* # write register\n */
/* 15 */	1,	/* # write register\n */
/* 16 */	1,	/* # write register\n */
/* 17 */	1,	/* # write register\n */
/* 18 */	1,	/* # write register\n */
/* 19 */	0,	/*  */
/* 20 */	0,	/*  */
/* 21 */	0,	/*  */
/* 22 */	0,	/*  */
/* 23 */	1,	/* \tpush\t%0\n\tpop\t%c\n */
/* 24 */	1,	/* \tpush\t%0\n\tpop\t%c\n */
/* 25 */	1,	/* # emit2\n */
/* 26 */	1,	/* # emit2\n */
/* 27 */	1,	/* ?\tmov\t%c,%0\n */
/* 28 */	1,	/* ?\tmov\t%c,%0\n */
/* 29 */	1,	/* ?\tmov\t%c,%0\n */
/* 30 */	1,	/* \tld\ta,(%0)\n\tst\t(%c),a\n\tld\ta,(%0+2)\n\tst\t(%c+2),a\n */
/* 31 */	1,	/* \tld\ta,(%0)\n\tst\t(%c),a\n\tld\ta,(%0+2)\n\tst\t(%c+2),a\n */
/* 32 */	1,	/* \tCOPY32(%c,%0)\n */
/* 33 */	1,	/* \tCOPY32(%c,%0)\n */
/* 34 */	0,	/* %0 */
/* 35 */	0,	/* %0 */
/* 36 */	1,	/* # emit2\n */
/* 37 */	1,	/* # emit2\n */
/* 38 */	1,	/* \tld\t%c,(%0+2)\n */
/* 39 */	1,	/* \tld\t%c,(%0+2)\n */
/* 40 */	0,	/* %a */
/* 41 */	0,	/* %a */
/* 42 */	0,	/* %a */
/* 43 */	0,	/* %a */
/* 44 */	0,	/* %a */
/* 45 */	0,	/* %a */
/* 46 */	0,	/* %a */
/* 47 */	0,	/* %a */
/* 48 */	0,	/* %a */
/* 49 */	0,	/* %a */
/* 50 */	0,	/* %a */
/* 51 */	0,	/* %a */
/* 52 */	0,	/* %a */
/* 53 */	0,	/* %a */
/* 54 */	0,	/* %a */
/* 55 */	0,	/* %a */
/* 56 */	0,	/* %a */
/* 57 */	0,	/* %a */
/* 58 */	0,	/* %a */
/* 59 */	1,	/* \tld\t%c,%0\n */
/* 60 */	1,	/* \tld\t%c,0\n */
/* 61 */	1,	/* \tld\t%c,%0\n */
/* 62 */	0,	/* dp:%a */
/* 63 */	0,	/* sp:%a+2+%F */
/* 64 */	0,	/* sp:%a+%F */
/* 65 */	0,	/* %0 */
/* 66 */	0,	/* %0:0 */
/* 67 */	0,	/* %0:%1 */
/* 68 */	0,	/* %0:-%1 */
/* 69 */	0,	/* %a */
/* 70 */	0,	/* %0 */
/* 71 */	0,	/* %0 */
/* 72 */	1,	/* \tlea\t%c,(%0)\n */
/* 73 */	1,	/* \tst\t(%0),%1\n */
/* 74 */	1,	/* \tst\t(%0),%1\n */
/* 75 */	1,	/* \tst\t(%0),%1\n */
/* 76 */	1,	/* \tst\t(%0),%1\n */
/* 77 */	1,	/* \tst\t(%0),%1\n */
/* 78 */	1,	/* # emit2\n */
/* 79 */	1,	/* \tCOPY32(%0,%1)\n */
/* 80 */	1,	/* \tCOPY32(%0,%1)\n */
/* 81 */	1,	/* \tCOPY32(%0,%1)\n */
/* 82 */	1,	/* \tCOPY32(%0,%1)\n */
/* 83 */	1,	/* \tCOPY32(%0,%1)\n */
/* 84 */	1,	/* \tCOPY32(%0,%1)\n */
/* 85 */	1,	/* \tCOPY32(%0,%1)\n */
/* 86 */	1,	/* \tCOPY32(%0,%1)\n */
/* 87 */	1,	/* \tld\t%c,(%0)\n */
/* 88 */	1,	/* \tld\t%c,(%0)\n */
/* 89 */	1,	/* \tld\t%c,(%0)\n */
/* 90 */	1,	/* \tld\t%c,(%0)\n */
/* 91 */	1,	/* \tld\t%c,(%0)\n */
/* 92 */	1,	/* \tCOPY32(%c,%0)\n */
/* 93 */	1,	/* \tld\ta,(%0)\n\tst\t(%c),a\n\tlea\ta,(%0)\n\tld\ta,(a:2)\n\tst\t(%c+2),a\n */
/* 94 */	1,	/* \tCOPY32(%c,%0)\n */
/* 95 */	1,	/* \tCOPY32(%c,%0)\n */
/* 96 */	1,	/* \tCOPY32(%c,%0)\n */
/* 97 */	1,	/* \tCOPY32(%c,%0)\n */
/* 98 */	1,	/* \tCOPY32(%c,%0)\n */
/* 99 */	1,	/* \tCOPY32(%c,%0)\n */
/* 100 */	1,	/* \tCVI32I8(%c,%0)\n */
/* 101 */	1,	/* \tCVI32U8(%c,%0)\n */
/* 102 */	1,	/* \tCVU32I8(%c,%0)\n */
/* 103 */	1,	/* \tCVU32U8(%c,%0)\n */
/* 104 */	1,	/* \tsex\t%c\n */
/* 105 */	1,	/* \tand\t%c,0x00ff\n */
/* 106 */	1,	/* \tand\t%c,0x00ff\n */
/* 107 */	1,	/* \tand\t%c,0x00ff\n */
/* 108 */	1,	/* \tCVI8I32(%c,%0)\n */
/* 109 */	1,	/* \tCVI8U32(%c,%0)\n */
/* 110 */	1,	/* \tCVU8I32(%c,%0)\n */
/* 111 */	1,	/* \tCVU8U32(%c,%0)\n */
/* 112 */	1,	/* \tCVI16I32(%c,%0)\n */
/* 113 */	1,	/* \tst\t(%c+2),%0\n\tld\ta,0\n\tst\t(%c),a\n */
/* 114 */	1,	/* \tst\t(%c+2),%0\n\tld\ta,0\n\tst\t(%c),a\n */
/* 115 */	1,	/* \tst\t(%c+2),%0\n\tld\ta,0\n\tst\t(%c),a\n */
/* 116 */	1,	/* \tCVTI8F32(%c,%0)\n */
/* 117 */	1,	/* \tCVTI16F32(%c,%0)\n */
/* 118 */	1,	/* \tCVTI32F32(%c,%0)\n */
/* 119 */	1,	/* \tCVTI8F64(%c,%0)\n */
/* 120 */	1,	/* \tCVTI16F64(%c,%0)\n */
/* 121 */	1,	/* \tCVTI32F64(%c,%0)\n */
/* 122 */	1,	/* \tCVTFI16(%c,%0)\n */
/* 123 */	1,	/* \tCVTFI32(%c,%0)\n */
/* 124 */	1,	/* \tCVTF64F32(%c,%0)\n */
/* 125 */	1,	/* \tCVTF32F64(%c,%0)\n */
/* 126 */	1,	/* \tmov\t%c,%0\n */
/* 127 */	1,	/* \tmov\t%c,%0\n */
/* 128 */	1,	/* ?\tmov\t%c,%0\n\tadd\t%c,%1\n */
/* 129 */	1,	/* ?\tmov\t%c,%0\n\tadd\t%c,(%1)\n */
/* 130 */	1,	/* ?\tmov\t%c,%0\n\tadd\t%c,%1\n */
/* 131 */	1,	/* ?\tmov\t%c,%0\n\tadd\t%c,%1\n */
/* 132 */	1,	/* ?\tmov\t%c,%0\n\tadd\t%c,(%1)\n */
/* 133 */	1,	/* ?\tmov\t%c,%0\n\tadd\t%c,%1\n */
/* 134 */	1,	/* ?\tmov\t%c,%0\n\tadd\t%c,%1\n */
/* 135 */	1,	/* ?\tmov\t%c,%0\n\tadd\t%c,%1\n */
/* 136 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 137 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 138 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 139 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 140 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 141 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 142 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 143 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 144 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 145 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 146 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 147 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 148 */	1,	/* ?\tCOPY32(%c,%0)\n\tADDI32(%c,%1)\n */
/* 149 */	1,	/* ?\tCOPY32(%c,%0)\n\tADDI32(%c,%1)\n */
/* 150 */	1,	/* ?\tld\ta,(%0)\tst\t(%c),a\tld\ta,(%0+2)\tst\t(%c+2),a\n\tld\ta,(%c+2)\n\tadd\ta,(%1+2)\n\tst\t(%c+2),a\n\tld\ta,(%c)\n\tld\ty,(%1)\n\tadc\ta,y\n\tst\t(%c),a\n */
/* 151 */	1,	/* ?\tld\ta,(%0)\tst\t(%c),a\tld\ta,(%0+2)\tst\t(%c+2),a\n\tlea\ty,(%1)\n\tld\ta,(%c+2)\n\tadd\ta,(y:2)\n\tst\t(%c+2),a\n\tld\ta,(%c)\n\tld\ty,(y:0)\n\tadc\ta,y\n\tst\t(%c),a\n */
/* 152 */	1,	/* ?\tCOPY32(%c,%0)\n\tADDF32(%c,%1)\n */
/* 153 */	1,	/* ?\tCOPY32(%c,%0)\n\tADDF32(%c,%1)\n */
/* 154 */	1,	/* ?\tCOPY32(%c,%0)\n\tADDF64(%c,%1)\n */
/* 155 */	1,	/* ?\tCOPY32(%c,%0)\n\tADDF64(%c,%1)\n */
/* 156 */	1,	/* \tCOPY32(%0,%1)\n\tADDI32(%0,%2)\n */
/* 157 */	1,	/* \tADDI32(%1,%2)\n */
/* 158 */	1,	/* \tCOPY32(%0,%1)\n\tADDU32(%0,%2)\n */
/* 159 */	1,	/* \tADDU32(%1,%2)\n */
/* 160 */	1,	/* \tCOPY32(%0,%1)\n\tADDF32(%0,%2)\n */
/* 161 */	1,	/* \tADDF32(%1,%2)\n */
/* 162 */	1,	/* \tCOPY32(%0,%1)\n\tADDF64(%0,%2)\n */
/* 163 */	1,	/* \tADDF64(%1,%2)\n */
/* 164 */	1,	/* ?\tmov\t%c,%0\n\tsub\t%c,%1\n */
/* 165 */	1,	/* ?\tmov\t%c,%0\n\tsub\t%c,(%1)\n */
/* 166 */	1,	/* ?\tmov\t%c,%0\n\tsub\t%c,%1\n */
/* 167 */	1,	/* ?\tmov\t%c,%0\n\tsub\t%c,%1\n */
/* 168 */	1,	/* ?\tmov\t%c,%0\n\tsub\t%c,(%1)\n */
/* 169 */	1,	/* ?\tmov\t%c,%0\n\tsub\t%c,%1\n */
/* 170 */	1,	/* ?\tmov\t%c,%0\n\tsub\t%c,%1\n */
/* 171 */	1,	/* ?\tmov\t%c,%0\n\tsub\t%c,%1\n */
/* 172 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 173 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 174 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 175 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 176 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 177 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 178 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 179 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 180 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 181 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 182 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 183 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 184 */	1,	/* ?\tCOPY32(%c,%0)\n\tSUBI32(%c,%1)\n */
/* 185 */	1,	/* ?\tCOPY32(%c,%0)\n\tSUBI32(%c,%1)\n */
/* 186 */	1,	/* ?\tld\ta,(%0)\tst\t(%c),a\tld\ta,(%0+2)\tst\t(%c+2),a\n\tld\ta,(%c+2)\n\tsub\ta,(%1+2)\n\tst\t(%c+2),a\n\tld\ta,(%c)\n\tld\ty,(%1)\n\tsbc\ta,y\n\tst\t(%c),a\n */
/* 187 */	1,	/* ?\tld\ta,(%0)\tst\t(%c),a\tld\ta,(%0+2)\tst\t(%c+2),a\n\tlea\ty,(%1)\n\tld\ta,(%c+2)\n\tsub\ta,(y:2)\n\tst\t(%c+2),a\n\tld\ta,(%c)\n\tld\ty,(y:0)\n\tsbc\ta,y\n\tst\t(%c),a\n */
/* 188 */	1,	/* ?\tCOPY32(%c,%0)\n\tSUBF32(%c,%1)\n */
/* 189 */	1,	/* ?\tCOPY32(%c,%0)\n\tSUBF32(%c,%1)\n */
/* 190 */	1,	/* ?\tCOPY32(%c,%0)\n\tSUBF64(%c,%1)\n */
/* 191 */	1,	/* ?\tCOPY32(%c,%0)\n\tSUBF64(%c,%1)\n */
/* 192 */	1,	/* \tCOPY32(%0,%1)\n\tSUBI32(%0,%2)\n */
/* 193 */	1,	/* \tSUBI32(%1,%2)\n */
/* 194 */	1,	/* \tCOPY32(%0,%1)\n\tSUBU32(%0,%2)\n */
/* 195 */	1,	/* \tSUBU32(%1,%2)\n */
/* 196 */	1,	/* \tCOPY32(%0,%1)\n\tSUBF32(%0,%2)\n */
/* 197 */	1,	/* \tSUBF32(%1,%2)\n */
/* 198 */	1,	/* \tCOPY32(%0,%1)\n\tSUBF64(%0,%2)\n */
/* 199 */	1,	/* \tSUBF64(%1,%2)\n */
/* 200 */	1,	/* \tld\t%c,0\n\tsub\t%c,%0\n */
/* 201 */	1,	/* \tld\t%c,0\n\tsub\t%c,(%0)\n */
/* 202 */	1,	/* \tNEGI32(%c,%0)\n */
/* 203 */	1,	/* \tNEGI32(%c,%0)\n */
/* 204 */	1,	/* \tNEGF32(%c,%0)\n */
/* 205 */	1,	/* \tNEGF32(%c,%0)\n */
/* 206 */	1,	/* \tNEGF64(%c,%0)\n */
/* 207 */	1,	/* \tNEGF64(%c,%0)\n */
/* 208 */	1,	/* ?\tmov\t%c,%0\n\tand\t%c,%1\n */
/* 209 */	1,	/* ?\tmov\t%c,%0\n\tand\t%c,(%1)\n */
/* 210 */	1,	/* ?\tmov\t%c,%0\n\tand\t%c,%1\n */
/* 211 */	1,	/* ?\tmov\t%c,%0\n\tand\t%c,%1\n */
/* 212 */	1,	/* ?\tmov\t%c,%0\n\tand\t%c,(%1)\n */
/* 213 */	1,	/* ?\tmov\t%c,%0\n\tand\t%c,%1\n */
/* 214 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 215 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 216 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 217 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 218 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 219 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 220 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 221 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 222 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 223 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 224 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 225 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 226 */	1,	/* ?\tCOPY32(%c,%0)\n\tBANDI32(%c,%1)\n */
/* 227 */	1,	/* ?\tCOPY32(%c,%0)\n\tBANDI32(%c,%1)\n */
/* 228 */	1,	/* ?\tCOPY32(%c,%0)\n\tBANDI32(%c,%1)\n */
/* 229 */	1,	/* ?\tCOPY32(%c,%0)\n\tBANDI32(%c,%1)\n */
/* 230 */	1,	/* \tmov\t%c,-1\n\txor\t%c,%0\n */
/* 231 */	1,	/* \tmov\t%c,-1\n\txor\t%c,%0\n */
/* 232 */	1,	/* \tBCOMI32(%c,%0)\n */
/* 233 */	1,	/* \tBCOMI32(%c,%0)\n */
/* 234 */	1,	/* ?\tmov\t%c,%0\n\tor\t%c,%1\n */
/* 235 */	1,	/* ?\tmov\t%c,%0\n\tor\t%c,(%1)\n */
/* 236 */	1,	/* ?\tmov\t%c,%0\n\tor\t%c,%1\n */
/* 237 */	1,	/* ?\tmov\t%c,%0\n\tor\t%c,%1\n */
/* 238 */	1,	/* ?\tmov\t%c,%0\n\tor\t%c,(%1)\n */
/* 239 */	1,	/* ?\tmov\t%c,%0\n\tor\t%c,%1\n */
/* 240 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 241 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 242 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 243 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 244 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 245 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 246 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 247 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 248 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 249 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 250 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 251 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 252 */	1,	/* ?\tCOPY32(%c,%0)\n\tBORI32(%c,%1)\n */
/* 253 */	1,	/* ?\tCOPY32(%c,%0)\n\tBORI32(%c,%1)\n */
/* 254 */	1,	/* ?\tCOPY32(%c,%0)\n\tBORI32(%c,%1)\n */
/* 255 */	1,	/* ?\tCOPY32(%c,%0)\n\tBORI32(%c,%1)\n */
/* 256 */	1,	/* ?\tmov\t%c,%0\n\txor\t%c,%1\n */
/* 257 */	1,	/* ?\tmov\t%c,%0\n\txor\t%c,(%1)\n */
/* 258 */	1,	/* ?\tmov\t%c,%0\n\txor\t%c,%1\n */
/* 259 */	1,	/* ?\tmov\t%c,%0\n\txor\t%c,%1\n */
/* 260 */	1,	/* ?\tmov\t%c,%0\n\txor\t%c,(%1)\n */
/* 261 */	1,	/* ?\tmov\t%c,%0\n\txor\t%c,%1\n */
/* 262 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 263 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 264 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 265 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 266 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 267 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 268 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 269 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 270 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 271 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 272 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 273 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 274 */	1,	/* ?\tCOPY32(%c,%0)\n\tBXORI32(%c,%1)\n */
/* 275 */	1,	/* ?\tCOPY32(%c,%0)\n\tBXORI32(%c,%1)\n */
/* 276 */	1,	/* ?\tCOPY32(%c,%0)\n\tBXORI32(%c,%1)\n */
/* 277 */	1,	/* ?\tCOPY32(%c,%0)\n\tBXORI32(%c,%1)\n */
/* 278 */	1,	/* ?\tmov\t%c,%0\n\tcall\t__muli16\n */
/* 279 */	1,	/* ?\tmov\t%c,%0\n\tcall\t__mulu16\n */
/* 280 */	1,	/* ?\tmov\t%c,%0\n\tcall\t__divi16\n */
/* 281 */	1,	/* ?\tmov\t%c,%0\n\tcall\t__divu16\n */
/* 282 */	1,	/* ?\tmov\t%c,%0\n\tcall\t__modi16\n */
/* 283 */	1,	/* ?\tmov\t%c,%0\n\tcall\t__modu16\n */
/* 284 */	1,	/* ?\tCOPY32(%c,%0)\n\tMULI32(%c,%1)\n */
/* 285 */	1,	/* ?\tCOPY32(%c,%0)\n\tMULI32(%c,%1)\n */
/* 286 */	1,	/* ?\tCOPY32(%c,%0)\n\tMULU32(%c,%1)\n */
/* 287 */	1,	/* ?\tCOPY32(%c,%0)\n\tMULU32(%c,%1)\n */
/* 288 */	1,	/* ?\tCOPY32(%c,%0)\n\tDIVI32(%c,%1)\n */
/* 289 */	1,	/* ?\tCOPY32(%c,%0)\n\tDIVI32(%c,%1)\n */
/* 290 */	1,	/* ?\tCOPY32(%c,%0)\n\tDIVU32(%c,%1)\n */
/* 291 */	1,	/* ?\tCOPY32(%c,%0)\n\tDIVU32(%c,%1)\n */
/* 292 */	1,	/* ?\tCOPY32(%c,%0)\n\tMODI32(%c,%1)\n */
/* 293 */	1,	/* ?\tCOPY32(%c,%0)\n\tMODI32(%c,%1)\n */
/* 294 */	1,	/* ?\tCOPY32(%c,%0)\n\tMODU32(%c,%1)\n */
/* 295 */	1,	/* ?\tCOPY32(%c,%0)\n\tMODU32(%c,%1)\n */
/* 296 */	1,	/* ?\tCOPY32(%c,%0)\n\tMULF32(%c,%1)\n */
/* 297 */	1,	/* ?\tCOPY32(%c,%0)\n\tMULF32(%c,%1)\n */
/* 298 */	1,	/* ?\tCOPY32(%c,%0)\n\tMULF64(%c,%1)\n */
/* 299 */	1,	/* ?\tCOPY32(%c,%0)\n\tMULF64(%c,%1)\n */
/* 300 */	1,	/* ?\tCOPY32(%c,%0)\n\tDIVF32(%c,%1)\n */
/* 301 */	1,	/* ?\tCOPY32(%c,%0)\n\tDIVF32(%c,%1)\n */
/* 302 */	1,	/* ?\tCOPY32(%c,%0)\n\tDIVF64(%c,%1)\n */
/* 303 */	1,	/* ?\tCOPY32(%c,%0)\n\tDIVF64(%c,%1)\n */
/* 304 */	1,	/* ?\tmov\t%c,%0\n\tshl\t%c\n */
/* 305 */	1,	/* ?\tmov\t%c,%0\n\tshl\t%c\n */
/* 306 */	1,	/* ?\tmov\t%c,%0\n\tshr\t%c\n */
/* 307 */	1,	/* ?\tmov\t%c,%0\n\tshr\t%c\n */
/* 308 */	1,	/* ?\tmov\t%c,%0\n\tshl\t%c\n\tshl\t%c\n */
/* 309 */	1,	/* ?\tmov\t%c,%0\n\tshl\t%c\n\tshl\t%c\n */
/* 310 */	1,	/* ?\tmov\t%c,%0\n\tshr\t%c\n\tshr\t%c\n */
/* 311 */	1,	/* ?\tmov\t%c,%0\n\tshr\t%c\n\tshr\t%c\n */
/* 312 */	1,	/* # emit2 (loop)\n */
/* 313 */	1,	/* # emit2 (loop)\n */
/* 314 */	1,	/* # emit2 (loop)\n */
/* 315 */	1,	/* # emit2 (loop)\n */
/* 316 */	1,	/* ?\tCOPY32(%c,%0)\n\tLSHI32(%0)\n */
/* 317 */	1,	/* ?\tld\ta,(%0)\tst\t(%c),a\tld\ta,(%0+2)\tst\t(%c+2),a\n\tld\ta,(%c)\n\tshl\ta\nst\t(%c),a\n\tld\ta,(%c+2)\n\tshl\ta\nst\t(%c+2),a\n\tld\ta,(%c)\n\tld\ty,0\n\tadc\ta,y\n\tst\t(%c),a\n */
/* 318 */	1,	/* ?\tCOPY32(%c,%0)\n\tRSHI32(%0)\n */
/* 319 */	1,	/* ?\tCOPY32(%c,%0)\n\tRSHU32(%0)\n */
/* 320 */	1,	/* \tcmp\t%0,%1\n\tje\t%a\n */
/* 321 */	1,	/* \tcmp\t%0,(%1)\n\tje\t%a\n */
/* 322 */	1,	/* \tcmp\t%0,%1\n\tje\t%a\n */
/* 323 */	1,	/* \tcmp\t%0,(%1)\n\tje\t%a\n */
/* 324 */	1,	/* \tcmp\t%0,(%1)\n\tje\t%a\n */
/* 325 */	1,	/* \tcmp\t%0,%1\n\tje\t%a\n */
/* 326 */	1,	/* \tcmp\t%0,%1\n\tje\t%a\n */
/* 327 */	1,	/* \tcmp\t%0,%1\n\tje\t%a\n */
/* 328 */	1,	/* \tcmp\t%0,(%1)\n\tje\t%a\n */
/* 329 */	1,	/* \tcmp\t%0,%1\n\tje\t%a\n */
/* 330 */	1,	/* \tcmp\t%0,(%1)\n\tje\t%a\n */
/* 331 */	1,	/* \tcmp\t%0,(%1)\n\tje\t%a\n */
/* 332 */	1,	/* \tcmp\t%0,%1\n\tje\t%a\n */
/* 333 */	1,	/* \tcmp\t%0,%1\n\tje\t%a\n */
/* 334 */	1,	/* \tCMP32(%0,%1)\n\tje\t%a\n */
/* 335 */	1,	/* \tCMP32(%0,%1)\n\tje\t%a\n */
/* 336 */	1,	/* \tCMP32(%0,%1)\n\tje\t%a\n */
/* 337 */	1,	/* \tCMP32(%0,%1)\n\tje\t%a\n */
/* 338 */	1,	/* \tCMP32(%0,%1)\n\tje\t%a\n */
/* 339 */	1,	/* \tCMP32(%0,%1)\n\tje\t%a\n */
/* 340 */	1,	/* \tCMP64(%0,%1)\n\tje\t%a\n */
/* 341 */	1,	/* \tCMP64(%0,%1)\n\tje\t%a\n */
/* 342 */	1,	/* \tcmp\t%0,%1\n\tjne\t%a\n */
/* 343 */	1,	/* \tcmp\t%0,(%1)\n\tjne\t%a\n */
/* 344 */	1,	/* \tcmp\t%0,%1\n\tjne\t%a\n */
/* 345 */	1,	/* \tcmp\t%0,(%1)\n\tjne\t%a\n */
/* 346 */	1,	/* \tcmp\t%0,(%1)\n\tjne\t%a\n */
/* 347 */	1,	/* \tcmp\t%0,%1\n\tjne\t%a\n */
/* 348 */	1,	/* \tcmp\t%0,%1\n\tjne\t%a\n */
/* 349 */	1,	/* \tcmp\t%0,%1\n\tjne\t%a\n */
/* 350 */	1,	/* \tcmp\t%0,(%1)\n\tjne\t%a\n */
/* 351 */	1,	/* \tcmp\t%0,%1\n\tjne\t%a\n */
/* 352 */	1,	/* \tcmp\t%0,(%1)\n\tjne\t%a\n */
/* 353 */	1,	/* \tcmp\t%0,(%1)\n\tjne\t%a\n */
/* 354 */	1,	/* \tcmp\t%0,%1\n\tjne\t%a\n */
/* 355 */	1,	/* \tcmp\t%0,%1\n\tjne\t%a\n */
/* 356 */	1,	/* \tCMP32(%0,%1)\n\tjne\t%a\n */
/* 357 */	1,	/* \tCMP32(%0,%1)\n\tjne\t%a\n */
/* 358 */	1,	/* \tCMP32(%0,%1)\n\tjne\t%a\n */
/* 359 */	1,	/* \tCMP32(%0,%1)\n\tjne\t%a\n */
/* 360 */	1,	/* \tCMP32(%0,%1)\n\tjne\t%a\n */
/* 361 */	1,	/* \tCMP32(%0,%1)\n\tjne\t%a\n */
/* 362 */	1,	/* \tCMP64(%0,%1)\n\tjne\t%a\n */
/* 363 */	1,	/* \tCMP64(%0,%1)\n\tjne\t%a\n */
/* 364 */	1,	/* \tcmp\t%0,%1\n\tjle\t%a\n */
/* 365 */	1,	/* \tcmp\t%0,(%1)\n\tjle\t%a\n */
/* 366 */	1,	/* \tcmp\t%0,%1\n\tjle\t%a\n */
/* 367 */	1,	/* \tcmp\t%0,(%1)\n\tjle\t%a\n */
/* 368 */	1,	/* \tcmp\t%0,(%1)\n\tjle\t%a\n */
/* 369 */	1,	/* \tcmp\t%0,%1\n\tjle\t%a\n */
/* 370 */	1,	/* \tcmp\t%0,%1\n\tjle\t%a\n */
/* 371 */	1,	/* \tcmp\t%0,%1\n\tjleu\t%a\n */
/* 372 */	1,	/* \tcmp\t%0,(%1)\n\tjleu\t%a\n */
/* 373 */	1,	/* \tcmp\t%0,%1\n\tjleu\t%a\n */
/* 374 */	1,	/* \tcmp\t%0,(%1)\n\tjleu\t%a\n */
/* 375 */	1,	/* \tcmp\t%0,(%1)\n\tjleu\t%a\n */
/* 376 */	1,	/* \tcmp\t%0,%1\n\tjleu\t%a\n */
/* 377 */	1,	/* \tcmp\t%0,%1\n\tjleu\t%a\n */
/* 378 */	1,	/* \tCMP32(%0,%1)\n\tjle\t%a\n */
/* 379 */	1,	/* \tCMP32(%0,%1)\n\tjle\t%a\n */
/* 380 */	1,	/* \tCMP32(%0,%1)\n\tjleu\t%a\n */
/* 381 */	1,	/* \tCMP32(%0,%1)\n\tjleu\t%a\n */
/* 382 */	1,	/* \tCMP32(%0,%1)\n\tjle\t%a\n */
/* 383 */	1,	/* \tCMP32(%0,%1)\n\tjle\t%a\n */
/* 384 */	1,	/* \tCMP64(%0,%1)\n\tjle\t%a\n */
/* 385 */	1,	/* \tCMP64(%0,%1)\n\tjle\t%a\n */
/* 386 */	1,	/* \tcmp\t%0,%1\n\tjl\t%a\n */
/* 387 */	1,	/* \tcmp\t%0,(%1)\n\tjl\t%a\n */
/* 388 */	1,	/* \tcmp\t%0,%1\n\tjl\t%a\n */
/* 389 */	1,	/* \tcmp\t%0,(%1)\n\tjl\t%a\n */
/* 390 */	1,	/* \tcmp\t%0,(%1)\n\tjl\t%a\n */
/* 391 */	1,	/* \tcmp\t%0,%1\n\tjl\t%a\n */
/* 392 */	1,	/* \tcmp\t%0,%1\n\tjl\t%a\n */
/* 393 */	1,	/* \tcmp\t%0,%1\n\tjlu\t%a\n */
/* 394 */	1,	/* \tcmp\t%0,(%1)\n\tjlu\t%a\n */
/* 395 */	1,	/* \tcmp\t%0,%1\n\tjlu\t%a\n */
/* 396 */	1,	/* \tcmp\t%0,(%1)\n\tjlu\t%a\n */
/* 397 */	1,	/* \tcmp\t%0,(%1)\n\tjlu\t%a\n */
/* 398 */	1,	/* \tcmp\t%0,%1\n\tjlu\t%a\n */
/* 399 */	1,	/* \tcmp\t%0,%1\n\tjlu\t%a\n */
/* 400 */	1,	/* \tCMP32(%0,%1)\n\tjl\t%a\n */
/* 401 */	1,	/* \tCMP32(%0,%1)\n\tjl\t%a\n */
/* 402 */	1,	/* \tCMP32(%0,%1)\n\tjlu\t%a\n */
/* 403 */	1,	/* \tCMP32(%0,%1)\n\tjlu\t%a\n */
/* 404 */	1,	/* \tCMP32(%0,%1)\n\tjl\t%a\n */
/* 405 */	1,	/* \tCMP32(%0,%1)\n\tjl\t%a\n */
/* 406 */	1,	/* \tCMP64(%0,%1)\n\tjl\t%a\n */
/* 407 */	1,	/* \tCMP64(%0,%1)\n\tjl\t%a\n */
/* 408 */	1,	/* \tcmp\t%0,%1\n\tjge\t%a\n */
/* 409 */	1,	/* \tcmp\t%0,(%1)\n\tjge\t%a\n */
/* 410 */	1,	/* \tcmp\t%0,%1\n\tjge\t%a\n */
/* 411 */	1,	/* \tcmp\t%0,(%1)\n\tjge\t%a\n */
/* 412 */	1,	/* \tcmp\t%0,(%1)\n\tjge\t%a\n */
/* 413 */	1,	/* \tcmp\t%0,%1\n\tjge\t%a\n */
/* 414 */	1,	/* \tcmp\t%0,%1\n\tjge\t%a\n */
/* 415 */	1,	/* \tcmp\t%0,%1\n\tjgeu\t%a\n */
/* 416 */	1,	/* \tcmp\t%0,(%1)\n\tjgeu\t%a\n */
/* 417 */	1,	/* \tcmp\t%0,%1\n\tjgeu\t%a\n */
/* 418 */	1,	/* \tcmp\t%0,(%1)\n\tjgeu\t%a\n */
/* 419 */	1,	/* \tcmp\t%0,(%1)\n\tjgeu\t%a\n */
/* 420 */	1,	/* \tcmp\t%0,%1\n\tjgeu\t%a\n */
/* 421 */	1,	/* \tcmp\t%0,%1\n\tjgeu\t%a\n */
/* 422 */	1,	/* \tCMP32(%0,%1)\n\tjge\t%a\n */
/* 423 */	1,	/* \tCMP32(%0,%1)\n\tjge\t%a\n */
/* 424 */	1,	/* \tCMP32(%0,%1)\n\tjgeu\t%a\n */
/* 425 */	1,	/* \tCMP32(%0,%1)\n\tjgeu\t%a\n */
/* 426 */	1,	/* \tCMP32(%0,%1)\n\tjge\t%a\n */
/* 427 */	1,	/* \tCMP32(%0,%1)\n\tjge\t%a\n */
/* 428 */	1,	/* \tCMP64(%0,%1)\n\tjge\t%a\n */
/* 429 */	1,	/* \tCMP64(%0,%1)\n\tjge\t%a\n */
/* 430 */	1,	/* \tcmp\t%0,%1\n\tjg\t%a\n */
/* 431 */	1,	/* \tcmp\t%0,(%1)\n\tjg\t%a\n */
/* 432 */	1,	/* \tcmp\t%0,%1\n\tjg\t%a\n */
/* 433 */	1,	/* \tcmp\t%0,(%1)\n\tjg\t%a\n */
/* 434 */	1,	/* \tcmp\t%0,(%1)\n\tjg\t%a\n */
/* 435 */	1,	/* \tcmp\t%0,%1\n\tjg\t%a\n */
/* 436 */	1,	/* \tcmp\t%0,%1\n\tjg\t%a\n */
/* 437 */	1,	/* \tcmp\t%0,%1\n\tjgu\t%a\n */
/* 438 */	1,	/* \tcmp\t%0,(%1)\n\tjgu\t%a\n */
/* 439 */	1,	/* \tcmp\t%0,%1\n\tjgu\t%a\n */
/* 440 */	1,	/* \tcmp\t%0,(%1)\n\tjgu\t%a\n */
/* 441 */	1,	/* \tcmp\t%0,(%1)\n\tjgu\t%a\n */
/* 442 */	1,	/* \tcmp\t%0,%1\n\tjgu\t%a\n */
/* 443 */	1,	/* \tcmp\t%0,%1\n\tjgu\t%a\n */
/* 444 */	1,	/* \tCMP32(%0,%1)\n\tjg\t%a\n */
/* 445 */	1,	/* \tCMP32(%0,%1)\n\tjg\t%a\n */
/* 446 */	1,	/* \tCMP32(%0,%1)\n\tjgu\t%a\n */
/* 447 */	1,	/* \tCMP32(%0,%1)\n\tjgu\t%a\n */
/* 448 */	1,	/* \tCMP32(%0,%1)\n\tjg\t%a\n */
/* 449 */	1,	/* \tCMP32(%0,%1)\n\tjg\t%a\n */
/* 450 */	1,	/* \tCMP64(%0,%1)\n\tjg\t%a\n */
/* 451 */	1,	/* \tCMP64(%0,%1)\n\tjg\t%a\n */
/* 452 */	1,	/* # emit2\n */
/* 453 */	1,	/* # emit2\n */
/* 454 */	1,	/* # emit2\n */
/* 455 */	1,	/* # emit2\n */
/* 456 */	1,	/* # emit2\n */
/* 457 */	1,	/* # emit2\n */
/* 458 */	1,	/* # emit2\n */
/* 459 */	1,	/* \tcall\t%0\n */
/* 460 */	1,	/* \tcall\t%0\n */
/* 461 */	1,	/* \tcall\t%0\n */
/* 462 */	1,	/* \tcall\t%0\n */
/* 463 */	1,	/* # emit2\n */
/* 464 */	1,	/* # emit2\n */
/* 465 */	1,	/* # emit2\n */
/* 466 */	1,	/* \tlea\tx,%c\n\tcall\t%0\n */
/* 467 */	1,	/* # return\n */
/* 468 */	1,	/* # return\n */
/* 469 */	1,	/* # return\n */
/* 470 */	1,	/* # return\n */
/* 471 */	1,	/* # return\n */
/* 472 */	1,	/* # return\n */
/* 473 */	1,	/* # return\n */
/* 474 */	1,	/* # return\n */
/* 475 */	1,	/* \tjmp\t%0\n */
/* 476 */	1,	/* \tjmp\t%0\n */
/* 477 */	1,	/* %a:\n */
};

static char *_string[] = {
/* 0 */	0,
/* 1 */	"reg8: INDIRI1(VREGP)",
/* 2 */	"reg8: INDIRU1(VREGP)",
/* 3 */	"reg: INDIRI2(VREGP)",
/* 4 */	"reg: INDIRU2(VREGP)",
/* 5 */	"reg32: INDIRI4(VREGP)",
/* 6 */	"reg32: INDIRU4(VREGP)",
/* 7 */	"reg: INDIRP2(VREGP)",
/* 8 */	"regf: INDIRF4(VREGP)",
/* 9 */	"regf: INDIRF8(VREGP)",
/* 10 */	"stmt: ASGNI1(VREGP,reg8)",
/* 11 */	"stmt: ASGNU1(VREGP,reg8)",
/* 12 */	"stmt: ASGNI2(VREGP,reg)",
/* 13 */	"stmt: ASGNU2(VREGP,reg)",
/* 14 */	"stmt: ASGNI4(VREGP,reg32)",
/* 15 */	"stmt: ASGNU4(VREGP,reg32)",
/* 16 */	"stmt: ASGNP2(VREGP,reg)",
/* 17 */	"stmt: ASGNF4(VREGP,regf)",
/* 18 */	"stmt: ASGNF8(VREGP,regf)",
/* 19 */	"stmt: reg8",
/* 20 */	"stmt: reg",
/* 21 */	"stmt: reg32",
/* 22 */	"stmt: regf",
/* 23 */	"reg8: LOADI1(reg8)",
/* 24 */	"reg8: LOADU1(reg8)",
/* 25 */	"reg8: LOADI1(reg)",
/* 26 */	"reg8: LOADU1(reg)",
/* 27 */	"reg: LOADI2(reg)",
/* 28 */	"reg: LOADU2(reg)",
/* 29 */	"reg: LOADP2(reg)",
/* 30 */	"reg32: LOADI4(reg32)",
/* 31 */	"reg32: LOADU4(reg32)",
/* 32 */	"regf: LOADF4(regf)",
/* 33 */	"regf: LOADF8(regf)",
/* 34 */	"reg8: LOADU1(LOADU2(CVII2(reg8)))",
/* 35 */	"reg8: LOADI1(LOADI2(CVUU2(reg8)))",
/* 36 */	"reg8: LOADI1(reg32)",
/* 37 */	"reg8: LOADU1(reg32)",
/* 38 */	"reg: LOADI2(reg32)",
/* 39 */	"reg: LOADU2(reg32)",
/* 40 */	"con8: CNSTI1",
/* 41 */	"con8: CNSTU1",
/* 42 */	"con16: CNSTI2",
/* 43 */	"con16: CNSTU2",
/* 44 */	"con16: CNSTP2",
/* 45 */	"con0: CNSTI1",
/* 46 */	"con0: CNSTU1",
/* 47 */	"con0: CNSTI2",
/* 48 */	"con0: CNSTU2",
/* 49 */	"con1: CNSTI1",
/* 50 */	"con1: CNSTU1",
/* 51 */	"con1: CNSTI2",
/* 52 */	"con1: CNSTU2",
/* 53 */	"con2: CNSTI1",
/* 54 */	"con2: CNSTU1",
/* 55 */	"con2: CNSTI2",
/* 56 */	"con2: CNSTU2",
/* 57 */	"con: con8",
/* 58 */	"con: con16",
/* 59 */	"reg: con",
/* 60 */	"reg: con0",
/* 61 */	"reg8: con8",
/* 62 */	"lgaddr: ADDRGP2",
/* 63 */	"lgaddr: ADDRFP2",
/* 64 */	"lgaddr: ADDRLP2",
/* 65 */	"addr: lgaddr",
/* 66 */	"addr: reg",
/* 67 */	"addr: ADDP2(reg,con)",
/* 68 */	"addr: SUBP2(reg,con)",
/* 69 */	"albl: ADDRGP2",
/* 70 */	"ar: reg",
/* 71 */	"ar: albl",
/* 72 */	"reg: lgaddr",
/* 73 */	"stmt: ASGNI1(addr,reg8)",
/* 74 */	"stmt: ASGNU1(addr,reg8)",
/* 75 */	"stmt: ASGNI2(addr,reg)",
/* 76 */	"stmt: ASGNU2(addr,reg)",
/* 77 */	"stmt: ASGNP2(addr,reg)",
/* 78 */	"stmt: ASGNB(reg,INDIRB(reg))",
/* 79 */	"stmt: ASGNI4(lgaddr,reg32)",
/* 80 */	"stmt: ASGNI4(lgaddr,INDIRI4(lgaddr))",
/* 81 */	"stmt: ASGNU4(lgaddr,reg32)",
/* 82 */	"stmt: ASGNU4(lgaddr,INDIRU4(lgaddr))",
/* 83 */	"stmt: ASGNF4(lgaddr,regf)",
/* 84 */	"stmt: ASGNF4(lgaddr,INDIRF4(lgaddr))",
/* 85 */	"stmt: ASGNF8(lgaddr,regf)",
/* 86 */	"stmt: ASGNF8(lgaddr,INDIRF8(lgaddr))",
/* 87 */	"reg8: INDIRI1(addr)",
/* 88 */	"reg8: INDIRU1(addr)",
/* 89 */	"reg: INDIRI2(addr)",
/* 90 */	"reg: INDIRU2(addr)",
/* 91 */	"reg: INDIRP2(addr)",
/* 92 */	"reg32: INDIRI4(lgaddr)",
/* 93 */	"reg32: INDIRU4(lgaddr)",
/* 94 */	"regf: INDIRF4(lgaddr)",
/* 95 */	"regf: INDIRF8(lgaddr)",
/* 96 */	"reg32: INDIRI4(reg)",
/* 97 */	"reg32: INDIRU4(reg)",
/* 98 */	"regf: INDIRF4(reg)",
/* 99 */	"regf: INDIRF8(reg)",
/* 100 */	"reg8: CVII1(reg32)",
/* 101 */	"reg8: CVIU1(reg32)",
/* 102 */	"reg8: CVUI1(reg32)",
/* 103 */	"reg8: CVUU1(reg32)",
/* 104 */	"reg: CVII2(reg8)",
/* 105 */	"reg: CVIU2(reg8)",
/* 106 */	"reg: CVUI2(reg8)",
/* 107 */	"reg: CVUU2(reg8)",
/* 108 */	"reg32: CVII4(reg8)",
/* 109 */	"reg32: CVIU4(reg8)",
/* 110 */	"reg32: CVUI4(reg8)",
/* 111 */	"reg32: CVUU4(reg8)",
/* 112 */	"reg32: CVII4(reg)",
/* 113 */	"reg32: CVIU4(reg)",
/* 114 */	"reg32: CVUI4(reg)",
/* 115 */	"reg32: CVUU4(reg)",
/* 116 */	"regf: CVIF4(reg8)",
/* 117 */	"regf: CVIF4(reg)",
/* 118 */	"regf: CVIF4(reg32)",
/* 119 */	"regf: CVIF8(reg8)",
/* 120 */	"regf: CVIF8(reg)",
/* 121 */	"regf: CVIF8(reg32)",
/* 122 */	"reg: CVFI2(regf)",
/* 123 */	"reg: CVFI4(regf)",
/* 124 */	"regf: CVFF4(regf)",
/* 125 */	"regf: CVFF8(regf)",
/* 126 */	"reg: CVPU2(reg)",
/* 127 */	"reg: CVUP2(reg)",
/* 128 */	"reg: ADDI2(reg,reg)",
/* 129 */	"reg: ADDI2(reg,INDIRI2(addr))",
/* 130 */	"reg: ADDI2(reg,con)",
/* 131 */	"reg: ADDU2(reg,reg)",
/* 132 */	"reg: ADDU2(reg,INDIRU2(addr))",
/* 133 */	"reg: ADDU2(reg,con)",
/* 134 */	"reg: ADDP2(reg,reg)",
/* 135 */	"reg: ADDP2(reg,con)",
/* 136 */	"reg8: ADDI2(reg8,CVII2(INDIRI1(addr)))",
/* 137 */	"reg8: ADDI2(CVII2(reg8),CVII2(INDIRI1(addr)))",
/* 138 */	"reg8: ADDI2(CVUI2(reg8),CVII2(INDIRI1(addr)))",
/* 139 */	"reg8: ADDI2(reg8,con)",
/* 140 */	"reg8: ADDI2(CVII2(reg8),con)",
/* 141 */	"reg8: ADDI2(CVUI2(reg8),con)",
/* 142 */	"reg8: ADDU2(reg8,CVUU2(INDIRU1(addr)))",
/* 143 */	"reg8: ADDU2(CVUU2(reg8),CVUU2(INDIRU1(addr)))",
/* 144 */	"reg8: ADDU2(CVIU2(reg8),CVUU2(INDIRU1(addr)))",
/* 145 */	"reg8: ADDU2(reg8,con)",
/* 146 */	"reg8: ADDU2(CVUU2(reg8),con)",
/* 147 */	"reg8: ADDU2(CVIU2(reg8),con)",
/* 148 */	"reg32: ADDI4(reg32,reg32)",
/* 149 */	"reg32: ADDI4(reg32,INDIRI4(lgaddr))",
/* 150 */	"reg32: ADDU4(reg32,reg32)",
/* 151 */	"reg32: ADDU4(reg32,INDIRU4(lgaddr))",
/* 152 */	"regf: ADDF4(regf,regf)",
/* 153 */	"regf: ADDF4(regf,INDIRF4(lgaddr))",
/* 154 */	"regf: ADDF8(regf,regf)",
/* 155 */	"regf: ADDF8(regf,INDIRF8(lgaddr))",
/* 156 */	"stmt: ASGNI4(lgaddr,ADDI4(INDIRI4(lgaddr),INDIRI4(lgaddr)))",
/* 157 */	"stmt: ASGNI4(lgaddr,ADDI4(INDIRI4(lgaddr),INDIRI4(lgaddr)))",
/* 158 */	"stmt: ASGNU4(lgaddr,ADDU4(INDIRU4(lgaddr),INDIRU4(lgaddr)))",
/* 159 */	"stmt: ASGNU4(lgaddr,ADDU4(INDIRU4(lgaddr),INDIRU4(lgaddr)))",
/* 160 */	"stmt: ASGNF4(lgaddr,ADDF4(INDIRF4(lgaddr),INDIRF4(lgaddr)))",
/* 161 */	"stmt: ASGNF4(lgaddr,ADDF4(INDIRF4(lgaddr),INDIRF4(lgaddr)))",
/* 162 */	"stmt: ASGNF8(lgaddr,ADDF8(INDIRF8(lgaddr),INDIRF8(lgaddr)))",
/* 163 */	"stmt: ASGNF8(lgaddr,ADDF8(INDIRF8(lgaddr),INDIRF8(lgaddr)))",
/* 164 */	"reg: SUBI2(reg,reg)",
/* 165 */	"reg: SUBI2(reg,INDIRI2(addr))",
/* 166 */	"reg: SUBI2(reg,con)",
/* 167 */	"reg: SUBU2(reg,reg)",
/* 168 */	"reg: SUBU2(reg,INDIRU2(addr))",
/* 169 */	"reg: SUBU2(reg,con)",
/* 170 */	"reg: SUBP2(reg,reg)",
/* 171 */	"reg: SUBP2(reg,con)",
/* 172 */	"reg8: SUBI2(reg8,CVII2(INDIRI1(addr)))",
/* 173 */	"reg8: SUBI2(CVII2(reg8),CVII2(INDIRI1(addr)))",
/* 174 */	"reg8: SUBI2(CVUI2(reg8),CVII2(INDIRI1(addr)))",
/* 175 */	"reg8: SUBI2(reg8,con)",
/* 176 */	"reg8: SUBI2(CVII2(reg8),con)",
/* 177 */	"reg8: SUBI2(CVUI2(reg8),con)",
/* 178 */	"reg8: SUBU2(reg8,CVUU2(INDIRU1(addr)))",
/* 179 */	"reg8: SUBU2(CVUU2(reg8),CVUU2(INDIRU1(addr)))",
/* 180 */	"reg8: SUBU2(CVIU2(reg8),CVUU2(INDIRU1(addr)))",
/* 181 */	"reg8: SUBU2(reg8,con)",
/* 182 */	"reg8: SUBU2(CVUU2(reg8),con)",
/* 183 */	"reg8: SUBU2(CVIU2(reg8),con)",
/* 184 */	"reg32: SUBI4(reg32,reg32)",
/* 185 */	"reg32: SUBI4(reg32,INDIRI4(lgaddr))",
/* 186 */	"reg32: SUBU4(reg32,reg32)",
/* 187 */	"reg32: SUBU4(reg32,INDIRU4(lgaddr))",
/* 188 */	"regf: SUBF4(regf,regf)",
/* 189 */	"regf: SUBF4(regf,INDIRF4(lgaddr))",
/* 190 */	"regf: SUBF8(regf,regf)",
/* 191 */	"regf: SUBF8(regf,INDIRF8(lgaddr))",
/* 192 */	"stmt: ASGNI4(lgaddr,SUBI4(INDIRI4(lgaddr),INDIRI4(lgaddr)))",
/* 193 */	"stmt: ASGNI4(lgaddr,SUBI4(INDIRI4(lgaddr),INDIRI4(lgaddr)))",
/* 194 */	"stmt: ASGNU4(lgaddr,SUBU4(INDIRU4(lgaddr),INDIRU4(lgaddr)))",
/* 195 */	"stmt: ASGNU4(lgaddr,SUBU4(INDIRU4(lgaddr),INDIRU4(lgaddr)))",
/* 196 */	"stmt: ASGNF4(lgaddr,SUBF4(INDIRF4(lgaddr),INDIRF4(lgaddr)))",
/* 197 */	"stmt: ASGNF4(lgaddr,SUBF4(INDIRF4(lgaddr),INDIRF4(lgaddr)))",
/* 198 */	"stmt: ASGNF8(lgaddr,SUBF8(INDIRF8(lgaddr),INDIRF8(lgaddr)))",
/* 199 */	"stmt: ASGNF8(lgaddr,SUBF8(INDIRF8(lgaddr),INDIRF8(lgaddr)))",
/* 200 */	"reg: NEGI2(reg)",
/* 201 */	"reg: NEGI2(INDIRI2(lgaddr))",
/* 202 */	"reg32: NEGI4(reg32)",
/* 203 */	"reg32: NEGI4(INDIRI4(lgaddr))",
/* 204 */	"regf: NEGF4(regf)",
/* 205 */	"regf: NEGF4(INDIRF4(lgaddr))",
/* 206 */	"regf: NEGF8(regf)",
/* 207 */	"regf: NEGF8(INDIRF8(lgaddr))",
/* 208 */	"reg: BANDI2(reg,reg)",
/* 209 */	"reg: BANDI2(reg,INDIRI2(lgaddr))",
/* 210 */	"reg: BANDI2(reg,con)",
/* 211 */	"reg: BANDU2(reg,reg)",
/* 212 */	"reg: BANDU2(reg,INDIRU2(lgaddr))",
/* 213 */	"reg: BANDU2(reg,con)",
/* 214 */	"reg8: BANDI2(reg8,CVII2(INDIRI1(lgaddr)))",
/* 215 */	"reg8: BANDI2(CVII2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 216 */	"reg8: BANDI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 217 */	"reg8: BANDI2(reg8,con)",
/* 218 */	"reg8: BANDI2(CVII2(reg8),con)",
/* 219 */	"reg8: BANDI2(CVUI2(reg8),con)",
/* 220 */	"reg8: BANDU2(reg8,CVUU2(INDIRU1(lgaddr)))",
/* 221 */	"reg8: BANDU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 222 */	"reg8: BANDU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 223 */	"reg8: BANDU2(reg8,con)",
/* 224 */	"reg8: BANDU2(CVUU2(reg8),con)",
/* 225 */	"reg8: BANDU2(CVIU2(reg8),con)",
/* 226 */	"reg32: BANDI4(reg32,reg32)",
/* 227 */	"reg32: BANDI4(reg32,INDIRI4(lgaddr))",
/* 228 */	"reg32: BANDU4(reg32,reg32)",
/* 229 */	"reg32: BANDU4(reg32,INDIRU4(lgaddr))",
/* 230 */	"reg: BCOMI2(reg)",
/* 231 */	"reg: BCOMU2(reg)",
/* 232 */	"reg32: BCOMI4(reg32)",
/* 233 */	"reg32: BCOMU4(reg32)",
/* 234 */	"reg: BORI2(reg,reg)",
/* 235 */	"reg: BORI2(reg,INDIRI2(lgaddr))",
/* 236 */	"reg: BORI2(reg,con)",
/* 237 */	"reg: BORU2(reg,reg)",
/* 238 */	"reg: BORU2(reg,INDIRU2(lgaddr))",
/* 239 */	"reg: BORU2(reg,con)",
/* 240 */	"reg8: BORI2(reg8,CVII2(INDIRI1(lgaddr)))",
/* 241 */	"reg8: BORI2(CVII2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 242 */	"reg8: BORI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 243 */	"reg8: BORI2(reg8,con)",
/* 244 */	"reg8: BORI2(CVII2(reg8),con)",
/* 245 */	"reg8: BORI2(CVUI2(reg8),con)",
/* 246 */	"reg8: BORU2(reg8,CVUU2(INDIRU1(lgaddr)))",
/* 247 */	"reg8: BORU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 248 */	"reg8: BORU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 249 */	"reg8: BORU2(reg8,con)",
/* 250 */	"reg8: BORU2(CVUU2(reg8),con)",
/* 251 */	"reg8: BORU2(CVIU2(reg8),con)",
/* 252 */	"reg32: BORI4(reg32,reg32)",
/* 253 */	"reg32: BORI4(reg32,INDIRI4(lgaddr))",
/* 254 */	"reg32: BORU4(reg32,reg32)",
/* 255 */	"reg32: BORU4(reg32,INDIRU4(lgaddr))",
/* 256 */	"reg: BXORI2(reg,reg)",
/* 257 */	"reg: BXORI2(reg,INDIRI2(lgaddr))",
/* 258 */	"reg: BXORI2(reg,con)",
/* 259 */	"reg: BXORU2(reg,reg)",
/* 260 */	"reg: BXORU2(reg,INDIRU2(lgaddr))",
/* 261 */	"reg: BXORU2(reg,con)",
/* 262 */	"reg8: BXORI2(reg8,CVII2(INDIRI1(lgaddr)))",
/* 263 */	"reg8: BXORI2(CVII2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 264 */	"reg8: BXORI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 265 */	"reg8: BXORI2(reg8,con)",
/* 266 */	"reg8: BXORI2(CVII2(reg8),con)",
/* 267 */	"reg8: BXORI2(CVUI2(reg8),con)",
/* 268 */	"reg8: BXORU2(reg8,CVUU2(INDIRU1(lgaddr)))",
/* 269 */	"reg8: BXORU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 270 */	"reg8: BXORU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 271 */	"reg8: BXORU2(reg8,con)",
/* 272 */	"reg8: BXORU2(CVUU2(reg8),con)",
/* 273 */	"reg8: BXORU2(CVIU2(reg8),con)",
/* 274 */	"reg32: BXORI4(reg32,reg32)",
/* 275 */	"reg32: BXORI4(reg32,INDIRI4(lgaddr))",
/* 276 */	"reg32: BXORU4(reg32,reg32)",
/* 277 */	"reg32: BXORU4(reg32,INDIRU4(lgaddr))",
/* 278 */	"reg: MULI2(reg,reg)",
/* 279 */	"reg: MULU2(reg,reg)",
/* 280 */	"reg: DIVI2(reg,reg)",
/* 281 */	"reg: DIVU2(reg,reg)",
/* 282 */	"reg: MODI2(reg,reg)",
/* 283 */	"reg: MODU2(reg,reg)",
/* 284 */	"reg32: MULI4(reg32,reg32)",
/* 285 */	"reg32: MULI4(reg32,INDIRI4(lgaddr))",
/* 286 */	"reg32: MULU4(reg32,reg32)",
/* 287 */	"reg32: MULU4(reg32,INDIRU4(lgaddr))",
/* 288 */	"reg32: DIVI4(reg32,reg32)",
/* 289 */	"reg32: DIVI4(reg32,INDIRI4(lgaddr))",
/* 290 */	"reg32: DIVU4(reg32,reg32)",
/* 291 */	"reg32: DIVU4(reg32,INDIRU4(lgaddr))",
/* 292 */	"reg32: MODI4(reg32,reg32)",
/* 293 */	"reg32: MODI4(reg32,INDIRI4(lgaddr))",
/* 294 */	"reg32: MODU4(reg32,reg32)",
/* 295 */	"reg32: MODU4(reg32,INDIRU4(lgaddr))",
/* 296 */	"regf: MULF4(regf,regf)",
/* 297 */	"regf: MULF4(regf,INDIRF4(lgaddr))",
/* 298 */	"regf: MULF8(regf,regf)",
/* 299 */	"regf: MULF8(regf,INDIRF8(lgaddr))",
/* 300 */	"regf: DIVF4(regf,regf)",
/* 301 */	"regf: DIVF4(regf,INDIRF4(lgaddr))",
/* 302 */	"regf: DIVF8(regf,regf)",
/* 303 */	"regf: DIVF8(regf,INDIRF8(lgaddr))",
/* 304 */	"reg: LSHI2(reg,con1)",
/* 305 */	"reg: LSHU2(reg,con1)",
/* 306 */	"reg: RSHI2(reg,con1)",
/* 307 */	"reg: RSHU2(reg,con1)",
/* 308 */	"reg: LSHI2(reg,con2)",
/* 309 */	"reg: LSHU2(reg,con2)",
/* 310 */	"reg: RSHI2(reg,con2)",
/* 311 */	"reg: RSHU2(reg,con2)",
/* 312 */	"reg: LSHI2(reg,reg)",
/* 313 */	"reg: LSHU2(reg,reg)",
/* 314 */	"reg: RSHI2(reg,reg)",
/* 315 */	"reg: RSHU2(reg,reg)",
/* 316 */	"reg32: LSHI4(reg32,con1)",
/* 317 */	"reg32: LSHU4(reg32,con1)",
/* 318 */	"reg32: RSHI4(reg32,con1)",
/* 319 */	"reg32: RSHU4(reg32,con1)",
/* 320 */	"stmt: EQI2(reg,reg)",
/* 321 */	"stmt: EQI2(reg,INDIRI2(lgaddr))",
/* 322 */	"stmt: EQI2(reg,con)",
/* 323 */	"stmt: EQI2(CVII2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 324 */	"stmt: EQI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 325 */	"stmt: EQI2(CVII2(reg8),con)",
/* 326 */	"stmt: EQI2(CVUI2(reg8),con)",
/* 327 */	"stmt: EQU2(reg,reg)",
/* 328 */	"stmt: EQU2(reg,INDIRU2(lgaddr))",
/* 329 */	"stmt: EQU2(reg,con)",
/* 330 */	"stmt: EQU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 331 */	"stmt: EQU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 332 */	"stmt: EQU2(CVUU2(reg8),con)",
/* 333 */	"stmt: EQU2(CVIU2(reg8),con)",
/* 334 */	"stmt: EQI4(reg32,reg32)",
/* 335 */	"stmt: EQI4(reg32,INDIRI4(lgaddr))",
/* 336 */	"stmt: EQU4(reg32,reg32)",
/* 337 */	"stmt: EQU4(reg32,INDIRU4(lgaddr))",
/* 338 */	"stmt: EQF4(regf,regf)",
/* 339 */	"stmt: EQF4(regf,INDIRF4(lgaddr))",
/* 340 */	"stmt: EQF8(regf,regf)",
/* 341 */	"stmt: EQF8(regf,INDIRF8(lgaddr))",
/* 342 */	"stmt: NEI2(reg,reg)",
/* 343 */	"stmt: NEI2(reg,INDIRI2(lgaddr))",
/* 344 */	"stmt: NEI2(reg,con)",
/* 345 */	"stmt: NEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 346 */	"stmt: NEI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 347 */	"stmt: NEI2(CVII2(reg8),con)",
/* 348 */	"stmt: NEI2(CVUI2(reg8),con)",
/* 349 */	"stmt: NEU2(reg,reg)",
/* 350 */	"stmt: NEU2(reg,INDIRU2(lgaddr))",
/* 351 */	"stmt: NEU2(reg,con)",
/* 352 */	"stmt: NEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 353 */	"stmt: NEU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 354 */	"stmt: NEU2(CVUU2(reg8),con)",
/* 355 */	"stmt: NEU2(CVIU2(reg8),con)",
/* 356 */	"stmt: NEI4(reg32,reg32)",
/* 357 */	"stmt: NEI4(reg32,INDIRI4(lgaddr))",
/* 358 */	"stmt: NEU4(reg32,reg32)",
/* 359 */	"stmt: NEU4(reg32,INDIRU4(lgaddr))",
/* 360 */	"stmt: NEF4(regf,regf)",
/* 361 */	"stmt: NEF4(regf,INDIRF4(lgaddr))",
/* 362 */	"stmt: NEF8(regf,regf)",
/* 363 */	"stmt: NEF8(regf,INDIRF8(lgaddr))",
/* 364 */	"stmt: LEI2(reg,reg)",
/* 365 */	"stmt: LEI2(reg,INDIRI2(lgaddr))",
/* 366 */	"stmt: LEI2(reg,con)",
/* 367 */	"stmt: LEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 368 */	"stmt: LEI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 369 */	"stmt: LEI2(CVII2(reg8),con)",
/* 370 */	"stmt: LEI2(CVUI2(reg8),con)",
/* 371 */	"stmt: LEU2(reg,reg)",
/* 372 */	"stmt: LEU2(reg,INDIRU2(lgaddr))",
/* 373 */	"stmt: LEU2(reg,con)",
/* 374 */	"stmt: LEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 375 */	"stmt: LEU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 376 */	"stmt: LEU2(CVUU2(reg8),con)",
/* 377 */	"stmt: LEU2(CVIU2(reg8),con)",
/* 378 */	"stmt: LEI4(reg32,reg32)",
/* 379 */	"stmt: LEI4(reg32,INDIRI4(lgaddr))",
/* 380 */	"stmt: LEU4(reg32,reg32)",
/* 381 */	"stmt: LEU4(reg32,INDIRU4(lgaddr))",
/* 382 */	"stmt: LEF4(regf,regf)",
/* 383 */	"stmt: LEF4(regf,INDIRF4(lgaddr))",
/* 384 */	"stmt: LEF8(regf,regf)",
/* 385 */	"stmt: LEF8(regf,INDIRF8(lgaddr))",
/* 386 */	"stmt: LTI2(reg,reg)",
/* 387 */	"stmt: LTI2(reg,INDIRI2(lgaddr))",
/* 388 */	"stmt: LTI2(reg,con)",
/* 389 */	"stmt: LTI2(CVII2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 390 */	"stmt: LTI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 391 */	"stmt: LTI2(CVII2(reg8),con)",
/* 392 */	"stmt: LTI2(CVUI2(reg8),con)",
/* 393 */	"stmt: LTU2(reg,reg)",
/* 394 */	"stmt: LTU2(reg,INDIRU2(lgaddr))",
/* 395 */	"stmt: LTU2(reg,con)",
/* 396 */	"stmt: LTU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 397 */	"stmt: LTU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 398 */	"stmt: LTU2(CVUU2(reg8),con)",
/* 399 */	"stmt: LTU2(CVIU2(reg8),con)",
/* 400 */	"stmt: LTI4(reg32,reg32)",
/* 401 */	"stmt: LTI4(reg32,INDIRI4(lgaddr))",
/* 402 */	"stmt: LTU4(reg32,reg32)",
/* 403 */	"stmt: LTU4(reg32,INDIRU4(lgaddr))",
/* 404 */	"stmt: LTF4(regf,regf)",
/* 405 */	"stmt: LTF4(regf,INDIRF4(lgaddr))",
/* 406 */	"stmt: LTF8(regf,regf)",
/* 407 */	"stmt: LTF8(regf,INDIRF8(lgaddr))",
/* 408 */	"stmt: GEI2(reg,reg)",
/* 409 */	"stmt: GEI2(reg,INDIRI2(lgaddr))",
/* 410 */	"stmt: GEI2(reg,con)",
/* 411 */	"stmt: GEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 412 */	"stmt: GEI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 413 */	"stmt: GEI2(CVII2(reg8),con)",
/* 414 */	"stmt: GEI2(CVUI2(reg8),con)",
/* 415 */	"stmt: GEU2(reg,reg)",
/* 416 */	"stmt: GEU2(reg,INDIRU2(lgaddr))",
/* 417 */	"stmt: GEU2(reg,con)",
/* 418 */	"stmt: GEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 419 */	"stmt: GEU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 420 */	"stmt: GEU2(CVUU2(reg8),con)",
/* 421 */	"stmt: GEU2(CVIU2(reg8),con)",
/* 422 */	"stmt: GEI4(reg32,reg32)",
/* 423 */	"stmt: GEI4(reg32,INDIRI4(lgaddr))",
/* 424 */	"stmt: GEU4(reg32,reg32)",
/* 425 */	"stmt: GEU4(reg32,INDIRU4(lgaddr))",
/* 426 */	"stmt: GEF4(regf,regf)",
/* 427 */	"stmt: GEF4(regf,INDIRF4(lgaddr))",
/* 428 */	"stmt: GEF8(regf,regf)",
/* 429 */	"stmt: GEF8(regf,INDIRF8(lgaddr))",
/* 430 */	"stmt: GTI2(reg,reg)",
/* 431 */	"stmt: GTI2(reg,INDIRI2(lgaddr))",
/* 432 */	"stmt: GTI2(reg,con)",
/* 433 */	"stmt: GTI2(CVII2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 434 */	"stmt: GTI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 435 */	"stmt: GTI2(CVII2(reg8),con)",
/* 436 */	"stmt: GTI2(CVUI2(reg8),con)",
/* 437 */	"stmt: GTU2(reg,reg)",
/* 438 */	"stmt: GTU2(reg,INDIRU2(lgaddr))",
/* 439 */	"stmt: GTU2(reg,con)",
/* 440 */	"stmt: GTU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 441 */	"stmt: GTU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 442 */	"stmt: GTU2(CVUU2(reg8),con)",
/* 443 */	"stmt: GTU2(CVIU2(reg8),con)",
/* 444 */	"stmt: GTI4(reg32,reg32)",
/* 445 */	"stmt: GTI4(reg32,INDIRI4(lgaddr))",
/* 446 */	"stmt: GTU4(reg32,reg32)",
/* 447 */	"stmt: GTU4(reg32,INDIRU4(lgaddr))",
/* 448 */	"stmt: GTF4(regf,regf)",
/* 449 */	"stmt: GTF4(regf,INDIRF4(lgaddr))",
/* 450 */	"stmt: GTF8(regf,regf)",
/* 451 */	"stmt: GTF8(regf,INDIRF8(lgaddr))",
/* 452 */	"stmt: ARGI2(reg)",
/* 453 */	"stmt: ARGU2(reg)",
/* 454 */	"stmt: ARGP2(reg)",
/* 455 */	"stmt: ARGI4(reg32)",
/* 456 */	"stmt: ARGU4(reg32)",
/* 457 */	"stmt: ARGF4(regf)",
/* 458 */	"stmt: ARGF8(regf)",
/* 459 */	"reg: CALLI2(ar)",
/* 460 */	"reg: CALLU2(ar)",
/* 461 */	"reg: CALLP2(ar)",
/* 462 */	"stmt: CALLV(ar)",
/* 463 */	"reg32: CALLI4(ar)",
/* 464 */	"reg32: CALLU4(ar)",
/* 465 */	"regf: CALLF4(ar)",
/* 466 */	"regf: CALLF8(ar)",
/* 467 */	"stmt: RETI2(reg)",
/* 468 */	"stmt: RETU2(reg)",
/* 469 */	"stmt: RETP2(reg)",
/* 470 */	"stmt: RETV",
/* 471 */	"stmt: RETI4(reg32)",
/* 472 */	"stmt: RETU4(reg32)",
/* 473 */	"stmt: RETF4(regf)",
/* 474 */	"stmt: RETF8(regf)",
/* 475 */	"stmt: JUMPV(albl)",
/* 476 */	"stmt: JUMPV(reg)",
/* 477 */	"stmt: LABELV",
};

static short _decode_stmt[] = {
	0,
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	21,
	22,
	73,
	74,
	75,
	76,
	77,
	78,
	79,
	80,
	81,
	82,
	83,
	84,
	85,
	86,
	156,
	157,
	158,
	159,
	160,
	161,
	162,
	163,
	192,
	193,
	194,
	195,
	196,
	197,
	198,
	199,
	320,
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
	333,
	334,
	335,
	336,
	337,
	338,
	339,
	340,
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
	381,
	382,
	383,
	384,
	385,
	386,
	387,
	388,
	389,
	390,
	391,
	392,
	393,
	394,
	395,
	396,
	397,
	398,
	399,
	400,
	401,
	402,
	403,
	404,
	405,
	406,
	407,
	408,
	409,
	410,
	411,
	412,
	413,
	414,
	415,
	416,
	417,
	418,
	419,
	420,
	421,
	422,
	423,
	424,
	425,
	426,
	427,
	428,
	429,
	430,
	431,
	432,
	433,
	434,
	435,
	436,
	437,
	438,
	439,
	440,
	441,
	442,
	443,
	444,
	445,
	446,
	447,
	448,
	449,
	450,
	451,
	452,
	453,
	454,
	455,
	456,
	457,
	458,
	462,
	467,
	468,
	469,
	470,
	471,
	472,
	473,
	474,
	475,
	476,
	477,
};

static short _decode_reg8[] = {
	0,
	1,
	2,
	23,
	24,
	25,
	26,
	34,
	35,
	36,
	37,
	61,
	87,
	88,
	100,
	101,
	102,
	103,
	136,
	137,
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
};

static short _decode_reg[] = {
	0,
	3,
	4,
	7,
	27,
	28,
	29,
	38,
	39,
	59,
	60,
	72,
	89,
	90,
	91,
	104,
	105,
	106,
	107,
	122,
	123,
	126,
	127,
	128,
	129,
	130,
	131,
	132,
	133,
	134,
	135,
	164,
	165,
	166,
	167,
	168,
	169,
	170,
	171,
	200,
	201,
	208,
	209,
	210,
	211,
	212,
	213,
	230,
	231,
	234,
	235,
	236,
	237,
	238,
	239,
	256,
	257,
	258,
	259,
	260,
	261,
	278,
	279,
	280,
	281,
	282,
	283,
	304,
	305,
	306,
	307,
	308,
	309,
	310,
	311,
	312,
	313,
	314,
	315,
	459,
	460,
	461,
};

static short _decode_reg32[] = {
	0,
	5,
	6,
	30,
	31,
	92,
	93,
	96,
	97,
	108,
	109,
	110,
	111,
	112,
	113,
	114,
	115,
	148,
	149,
	150,
	151,
	184,
	185,
	186,
	187,
	202,
	203,
	226,
	227,
	228,
	229,
	232,
	233,
	252,
	253,
	254,
	255,
	274,
	275,
	276,
	277,
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
	316,
	317,
	318,
	319,
	463,
	464,
};

static short _decode_regf[] = {
	0,
	8,
	9,
	32,
	33,
	94,
	95,
	98,
	99,
	116,
	117,
	118,
	119,
	120,
	121,
	124,
	125,
	152,
	153,
	154,
	155,
	188,
	189,
	190,
	191,
	204,
	205,
	206,
	207,
	296,
	297,
	298,
	299,
	300,
	301,
	302,
	303,
	465,
	466,
};

static short _decode_con8[] = {
	0,
	40,
	41,
};

static short _decode_con16[] = {
	0,
	42,
	43,
	44,
};

static short _decode_con0[] = {
	0,
	45,
	46,
	47,
	48,
};

static short _decode_con1[] = {
	0,
	49,
	50,
	51,
	52,
};

static short _decode_con2[] = {
	0,
	53,
	54,
	55,
	56,
};

static short _decode_con[] = {
	0,
	57,
	58,
};

static short _decode_lgaddr[] = {
	0,
	62,
	63,
	64,
};

static short _decode_addr[] = {
	0,
	65,
	66,
	67,
	68,
};

static short _decode_albl[] = {
	0,
	69,
};

static short _decode_ar[] = {
	0,
	70,
	71,
};

static int _rule(void *state, int goalnt) {
	if (goalnt < 1 || goalnt > 15)
		fatal("_rule", "Bad goal nonterminal %d\n", goalnt);
	if (!state)
		return 0;
	switch (goalnt) {
	case _stmt_NT:	return _decode_stmt[((struct _state *)state)->rule._stmt];
	case _reg8_NT:	return _decode_reg8[((struct _state *)state)->rule._reg8];
	case _reg_NT:	return _decode_reg[((struct _state *)state)->rule._reg];
	case _reg32_NT:	return _decode_reg32[((struct _state *)state)->rule._reg32];
	case _regf_NT:	return _decode_regf[((struct _state *)state)->rule._regf];
	case _con8_NT:	return _decode_con8[((struct _state *)state)->rule._con8];
	case _con16_NT:	return _decode_con16[((struct _state *)state)->rule._con16];
	case _con0_NT:	return _decode_con0[((struct _state *)state)->rule._con0];
	case _con1_NT:	return _decode_con1[((struct _state *)state)->rule._con1];
	case _con2_NT:	return _decode_con2[((struct _state *)state)->rule._con2];
	case _con_NT:	return _decode_con[((struct _state *)state)->rule._con];
	case _lgaddr_NT:	return _decode_lgaddr[((struct _state *)state)->rule._lgaddr];
	case _addr_NT:	return _decode_addr[((struct _state *)state)->rule._addr];
	case _albl_NT:	return _decode_albl[((struct _state *)state)->rule._albl];
	case _ar_NT:	return _decode_ar[((struct _state *)state)->rule._ar];
	default:
		fatal("_rule", "Bad goal nonterminal %d\n", goalnt);
		return 0;
	}
}

static void _closure_reg8(NODEPTR_TYPE, int);
static void _closure_reg(NODEPTR_TYPE, int);
static void _closure_reg32(NODEPTR_TYPE, int);
static void _closure_regf(NODEPTR_TYPE, int);
static void _closure_con8(NODEPTR_TYPE, int);
static void _closure_con16(NODEPTR_TYPE, int);
static void _closure_con0(NODEPTR_TYPE, int);
static void _closure_con(NODEPTR_TYPE, int);
static void _closure_lgaddr(NODEPTR_TYPE, int);
static void _closure_albl(NODEPTR_TYPE, int);

static void _closure_reg8(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 0 < p->cost[_stmt_NT]) {
		p->cost[_stmt_NT] = c + 0;
		p->rule._stmt = 10;
	}
}

static void _closure_reg(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 0 < p->cost[_ar_NT]) {
		p->cost[_ar_NT] = c + 0;
		p->rule._ar = 1;
	}
	if (c + 0 < p->cost[_addr_NT]) {
		p->cost[_addr_NT] = c + 0;
		p->rule._addr = 2;
	}
	if (c + 0 < p->cost[_stmt_NT]) {
		p->cost[_stmt_NT] = c + 0;
		p->rule._stmt = 11;
	}
}

static void _closure_reg32(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 0 < p->cost[_stmt_NT]) {
		p->cost[_stmt_NT] = c + 0;
		p->rule._stmt = 12;
	}
}

static void _closure_regf(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 0 < p->cost[_stmt_NT]) {
		p->cost[_stmt_NT] = c + 0;
		p->rule._stmt = 13;
	}
}

static void _closure_con8(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 1 < p->cost[_reg8_NT]) {
		p->cost[_reg8_NT] = c + 1;
		p->rule._reg8 = 11;
		_closure_reg8(a, c + 1);
	}
	if (c + 0 < p->cost[_con_NT]) {
		p->cost[_con_NT] = c + 0;
		p->rule._con = 1;
		_closure_con(a, c + 0);
	}
}

static void _closure_con16(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 0 < p->cost[_con_NT]) {
		p->cost[_con_NT] = c + 0;
		p->rule._con = 2;
		_closure_con(a, c + 0);
	}
}

static void _closure_con0(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 1 < p->cost[_reg_NT]) {
		p->cost[_reg_NT] = c + 1;
		p->rule._reg = 10;
		_closure_reg(a, c + 1);
	}
}

static void _closure_con(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 2 < p->cost[_reg_NT]) {
		p->cost[_reg_NT] = c + 2;
		p->rule._reg = 9;
		_closure_reg(a, c + 2);
	}
}

static void _closure_lgaddr(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 2 < p->cost[_reg_NT]) {
		p->cost[_reg_NT] = c + 2;
		p->rule._reg = 11;
		_closure_reg(a, c + 2);
	}
	if (c + 0 < p->cost[_addr_NT]) {
		p->cost[_addr_NT] = c + 0;
		p->rule._addr = 1;
	}
}

static void _closure_albl(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 0 < p->cost[_ar_NT]) {
		p->cost[_ar_NT] = c + 0;
		p->rule._ar = 2;
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
	p->cost[13] =
	p->cost[14] =
	p->cost[15] =
		0x7fff;
	switch (OP_LABEL(a)) {
	case 41: /* ARGB */
		break;
	case 57: /* ASGNB */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNB(reg,INDIRB(reg)) */
			RIGHT_CHILD(a)->op == 73 /* INDIRB */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_reg_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 19;
			}
		}
		break;
	case 73: /* INDIRB */
		_label(LEFT_CHILD(a));
		break;
	case 216: /* CALLV */
		_label(LEFT_CHILD(a));
		/* stmt: CALLV(ar) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_ar_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 183;
		}
		break;
	case 217: /* CALLB */
		break;
	case 233: /* LOADB */
		break;
	case 248: /* RETV */
		/* stmt: RETV */
		if (1 + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = 1 + 0;
			p->rule._stmt = 187;
		}
		break;
	case 584: /* JUMPV */
		_label(LEFT_CHILD(a));
		/* stmt: JUMPV(albl) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_albl_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 192;
		}
		/* stmt: JUMPV(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 193;
		}
		break;
	case 600: /* LABELV */
		/* stmt: LABELV */
		if (0 + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = 0 + 0;
			p->rule._stmt = 194;
		}
		break;
	case 711: /* VREGP */
		break;
	case 1045: /* CNSTI1 */
		/* con8: CNSTI1 */
		if (0 + 0 < p->cost[_con8_NT]) {
			p->cost[_con8_NT] = 0 + 0;
			p->rule._con8 = 1;
			_closure_con8(a, 0 + 0);
		}
		/* con0: CNSTI1 */
		c = (range(a,0,0));
		if (c + 0 < p->cost[_con0_NT]) {
			p->cost[_con0_NT] = c + 0;
			p->rule._con0 = 1;
			_closure_con0(a, c + 0);
		}
		/* con1: CNSTI1 */
		c = (range(a,1,1));
		if (c + 0 < p->cost[_con1_NT]) {
			p->cost[_con1_NT] = c + 0;
			p->rule._con1 = 1;
		}
		/* con2: CNSTI1 */
		c = (range(a,2,2));
		if (c + 0 < p->cost[_con2_NT]) {
			p->cost[_con2_NT] = c + 0;
			p->rule._con2 = 1;
		}
		break;
	case 1046: /* CNSTU1 */
		/* con8: CNSTU1 */
		if (0 + 0 < p->cost[_con8_NT]) {
			p->cost[_con8_NT] = 0 + 0;
			p->rule._con8 = 2;
			_closure_con8(a, 0 + 0);
		}
		/* con0: CNSTU1 */
		c = (range(a,0,0));
		if (c + 0 < p->cost[_con0_NT]) {
			p->cost[_con0_NT] = c + 0;
			p->rule._con0 = 2;
			_closure_con0(a, c + 0);
		}
		/* con1: CNSTU1 */
		c = (range(a,1,1));
		if (c + 0 < p->cost[_con1_NT]) {
			p->cost[_con1_NT] = c + 0;
			p->rule._con1 = 2;
		}
		/* con2: CNSTU1 */
		c = (range(a,2,2));
		if (c + 0 < p->cost[_con2_NT]) {
			p->cost[_con2_NT] = c + 0;
			p->rule._con2 = 2;
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
		/* stmt: ASGNI1(addr,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 14;
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
		/* stmt: ASGNU1(addr,reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg8_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 15;
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
				if (q->cost[_reg32_NT] == 0) {
					p->cost[_reg32_NT] = 0;
					p->rule._reg32 = q->rule._reg32;
				}
				if (q->cost[_regf_NT] == 0) {
					p->cost[_regf_NT] = 0;
					p->rule._regf = q->rule._regf;
				}
				if (q->cost[_con8_NT] == 0) {
					p->cost[_con8_NT] = 0;
					p->rule._con8 = q->rule._con8;
				}
				if (q->cost[_con16_NT] == 0) {
					p->cost[_con16_NT] = 0;
					p->rule._con16 = q->rule._con16;
				}
				if (q->cost[_con0_NT] == 0) {
					p->cost[_con0_NT] = 0;
					p->rule._con0 = q->rule._con0;
				}
				if (q->cost[_con1_NT] == 0) {
					p->cost[_con1_NT] = 0;
					p->rule._con1 = q->rule._con1;
				}
				if (q->cost[_con2_NT] == 0) {
					p->cost[_con2_NT] = 0;
					p->rule._con2 = q->rule._con2;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_lgaddr_NT] == 0) {
					p->cost[_lgaddr_NT] = 0;
					p->rule._lgaddr = q->rule._lgaddr;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_albl_NT] == 0) {
					p->cost[_albl_NT] = 0;
					p->rule._albl = q->rule._albl;
				}
				if (q->cost[_ar_NT] == 0) {
					p->cost[_ar_NT] = 0;
					p->rule._ar = q->rule._ar;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 1;
				_closure_reg8(a, c + 0);
			}
		}
		/* reg8: INDIRI1(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 12;
			_closure_reg8(a, c + 0);
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
				if (q->cost[_reg32_NT] == 0) {
					p->cost[_reg32_NT] = 0;
					p->rule._reg32 = q->rule._reg32;
				}
				if (q->cost[_regf_NT] == 0) {
					p->cost[_regf_NT] = 0;
					p->rule._regf = q->rule._regf;
				}
				if (q->cost[_con8_NT] == 0) {
					p->cost[_con8_NT] = 0;
					p->rule._con8 = q->rule._con8;
				}
				if (q->cost[_con16_NT] == 0) {
					p->cost[_con16_NT] = 0;
					p->rule._con16 = q->rule._con16;
				}
				if (q->cost[_con0_NT] == 0) {
					p->cost[_con0_NT] = 0;
					p->rule._con0 = q->rule._con0;
				}
				if (q->cost[_con1_NT] == 0) {
					p->cost[_con1_NT] = 0;
					p->rule._con1 = q->rule._con1;
				}
				if (q->cost[_con2_NT] == 0) {
					p->cost[_con2_NT] = 0;
					p->rule._con2 = q->rule._con2;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_lgaddr_NT] == 0) {
					p->cost[_lgaddr_NT] = 0;
					p->rule._lgaddr = q->rule._lgaddr;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_albl_NT] == 0) {
					p->cost[_albl_NT] = 0;
					p->rule._albl = q->rule._albl;
				}
				if (q->cost[_ar_NT] == 0) {
					p->cost[_ar_NT] = 0;
					p->rule._ar = q->rule._ar;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 2;
				_closure_reg8(a, c + 0);
			}
		}
		/* reg8: INDIRU1(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 13;
			_closure_reg8(a, c + 0);
		}
		break;
	case 1157: /* CVII1 */
		_label(LEFT_CHILD(a));
		/* reg8: CVII1(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 14;
			_closure_reg8(a, c + 0);
		}
		break;
	case 1158: /* CVIU1 */
		_label(LEFT_CHILD(a));
		/* reg8: CVIU1(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 15;
			_closure_reg8(a, c + 0);
		}
		break;
	case 1205: /* CVUI1 */
		_label(LEFT_CHILD(a));
		/* reg8: CVUI1(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 16;
			_closure_reg8(a, c + 0);
		}
		break;
	case 1206: /* CVUU1 */
		_label(LEFT_CHILD(a));
		/* reg8: CVUU1(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 17;
			_closure_reg8(a, c + 0);
		}
		break;
	case 1253: /* LOADI1 */
		_label(LEFT_CHILD(a));
		/* reg8: LOADI1(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + (move(a));
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 3;
			_closure_reg8(a, c + 0);
		}
		/* reg8: LOADI1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 5;
			_closure_reg8(a, c + 0);
		}
		if (	/* reg8: LOADI1(LOADI2(CVUU2(reg8))) */
			LEFT_CHILD(a)->op == 2277 && /* LOADI2 */
			LEFT_CHILD(LEFT_CHILD(a))->op == 2230 /* CVUU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(LEFT_CHILD(a)))->x.state))->cost[_reg8_NT] + 0;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 8;
				_closure_reg8(a, c + 0);
			}
		}
		/* reg8: LOADI1(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 9;
			_closure_reg8(a, c + 0);
		}
		break;
	case 1254: /* LOADU1 */
		_label(LEFT_CHILD(a));
		/* reg8: LOADU1(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + (move(a));
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 4;
			_closure_reg8(a, c + 0);
		}
		/* reg8: LOADU1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 6;
			_closure_reg8(a, c + 0);
		}
		if (	/* reg8: LOADU1(LOADU2(CVII2(reg8))) */
			LEFT_CHILD(a)->op == 2278 && /* LOADU2 */
			LEFT_CHILD(LEFT_CHILD(a))->op == 2181 /* CVII2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(LEFT_CHILD(a)))->x.state))->cost[_reg8_NT] + 0;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 7;
				_closure_reg8(a, c + 0);
			}
		}
		/* reg8: LOADU1(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 10;
			_closure_reg8(a, c + 0);
		}
		break;
	case 2069: /* CNSTI2 */
		/* con16: CNSTI2 */
		if (0 + 0 < p->cost[_con16_NT]) {
			p->cost[_con16_NT] = 0 + 0;
			p->rule._con16 = 1;
			_closure_con16(a, 0 + 0);
		}
		/* con0: CNSTI2 */
		c = (range(a,0,0));
		if (c + 0 < p->cost[_con0_NT]) {
			p->cost[_con0_NT] = c + 0;
			p->rule._con0 = 3;
			_closure_con0(a, c + 0);
		}
		/* con1: CNSTI2 */
		c = (range(a,1,1));
		if (c + 0 < p->cost[_con1_NT]) {
			p->cost[_con1_NT] = c + 0;
			p->rule._con1 = 3;
		}
		/* con2: CNSTI2 */
		c = (range(a,2,2));
		if (c + 0 < p->cost[_con2_NT]) {
			p->cost[_con2_NT] = c + 0;
			p->rule._con2 = 3;
		}
		break;
	case 2070: /* CNSTU2 */
		/* con16: CNSTU2 */
		if (0 + 0 < p->cost[_con16_NT]) {
			p->cost[_con16_NT] = 0 + 0;
			p->rule._con16 = 2;
			_closure_con16(a, 0 + 0);
		}
		/* con0: CNSTU2 */
		c = (range(a,0,0));
		if (c + 0 < p->cost[_con0_NT]) {
			p->cost[_con0_NT] = c + 0;
			p->rule._con0 = 4;
			_closure_con0(a, c + 0);
		}
		/* con1: CNSTU2 */
		c = (range(a,1,1));
		if (c + 0 < p->cost[_con1_NT]) {
			p->cost[_con1_NT] = c + 0;
			p->rule._con1 = 4;
		}
		/* con2: CNSTU2 */
		c = (range(a,2,2));
		if (c + 0 < p->cost[_con2_NT]) {
			p->cost[_con2_NT] = c + 0;
			p->rule._con2 = 4;
		}
		break;
	case 2071: /* CNSTP2 */
		/* con16: CNSTP2 */
		if (0 + 0 < p->cost[_con16_NT]) {
			p->cost[_con16_NT] = 0 + 0;
			p->rule._con16 = 3;
			_closure_con16(a, 0 + 0);
		}
		break;
	case 2085: /* ARGI2 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 176;
		}
		break;
	case 2086: /* ARGU2 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 177;
		}
		break;
	case 2087: /* ARGP2 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGP2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 178;
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
		/* stmt: ASGNI2(addr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 16;
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
		/* stmt: ASGNU2(addr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 17;
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
		/* stmt: ASGNP2(addr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 18;
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
				if (q->cost[_reg32_NT] == 0) {
					p->cost[_reg32_NT] = 0;
					p->rule._reg32 = q->rule._reg32;
				}
				if (q->cost[_regf_NT] == 0) {
					p->cost[_regf_NT] = 0;
					p->rule._regf = q->rule._regf;
				}
				if (q->cost[_con8_NT] == 0) {
					p->cost[_con8_NT] = 0;
					p->rule._con8 = q->rule._con8;
				}
				if (q->cost[_con16_NT] == 0) {
					p->cost[_con16_NT] = 0;
					p->rule._con16 = q->rule._con16;
				}
				if (q->cost[_con0_NT] == 0) {
					p->cost[_con0_NT] = 0;
					p->rule._con0 = q->rule._con0;
				}
				if (q->cost[_con1_NT] == 0) {
					p->cost[_con1_NT] = 0;
					p->rule._con1 = q->rule._con1;
				}
				if (q->cost[_con2_NT] == 0) {
					p->cost[_con2_NT] = 0;
					p->rule._con2 = q->rule._con2;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_lgaddr_NT] == 0) {
					p->cost[_lgaddr_NT] = 0;
					p->rule._lgaddr = q->rule._lgaddr;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_albl_NT] == 0) {
					p->cost[_albl_NT] = 0;
					p->rule._albl = q->rule._albl;
				}
				if (q->cost[_ar_NT] == 0) {
					p->cost[_ar_NT] = 0;
					p->rule._ar = q->rule._ar;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 1;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: INDIRI2(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 12;
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
				if (q->cost[_reg32_NT] == 0) {
					p->cost[_reg32_NT] = 0;
					p->rule._reg32 = q->rule._reg32;
				}
				if (q->cost[_regf_NT] == 0) {
					p->cost[_regf_NT] = 0;
					p->rule._regf = q->rule._regf;
				}
				if (q->cost[_con8_NT] == 0) {
					p->cost[_con8_NT] = 0;
					p->rule._con8 = q->rule._con8;
				}
				if (q->cost[_con16_NT] == 0) {
					p->cost[_con16_NT] = 0;
					p->rule._con16 = q->rule._con16;
				}
				if (q->cost[_con0_NT] == 0) {
					p->cost[_con0_NT] = 0;
					p->rule._con0 = q->rule._con0;
				}
				if (q->cost[_con1_NT] == 0) {
					p->cost[_con1_NT] = 0;
					p->rule._con1 = q->rule._con1;
				}
				if (q->cost[_con2_NT] == 0) {
					p->cost[_con2_NT] = 0;
					p->rule._con2 = q->rule._con2;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_lgaddr_NT] == 0) {
					p->cost[_lgaddr_NT] = 0;
					p->rule._lgaddr = q->rule._lgaddr;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_albl_NT] == 0) {
					p->cost[_albl_NT] = 0;
					p->rule._albl = q->rule._albl;
				}
				if (q->cost[_ar_NT] == 0) {
					p->cost[_ar_NT] = 0;
					p->rule._ar = q->rule._ar;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 2;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: INDIRU2(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 13;
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
				if (q->cost[_reg32_NT] == 0) {
					p->cost[_reg32_NT] = 0;
					p->rule._reg32 = q->rule._reg32;
				}
				if (q->cost[_regf_NT] == 0) {
					p->cost[_regf_NT] = 0;
					p->rule._regf = q->rule._regf;
				}
				if (q->cost[_con8_NT] == 0) {
					p->cost[_con8_NT] = 0;
					p->rule._con8 = q->rule._con8;
				}
				if (q->cost[_con16_NT] == 0) {
					p->cost[_con16_NT] = 0;
					p->rule._con16 = q->rule._con16;
				}
				if (q->cost[_con0_NT] == 0) {
					p->cost[_con0_NT] = 0;
					p->rule._con0 = q->rule._con0;
				}
				if (q->cost[_con1_NT] == 0) {
					p->cost[_con1_NT] = 0;
					p->rule._con1 = q->rule._con1;
				}
				if (q->cost[_con2_NT] == 0) {
					p->cost[_con2_NT] = 0;
					p->rule._con2 = q->rule._con2;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_lgaddr_NT] == 0) {
					p->cost[_lgaddr_NT] = 0;
					p->rule._lgaddr = q->rule._lgaddr;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_albl_NT] == 0) {
					p->cost[_albl_NT] = 0;
					p->rule._albl = q->rule._albl;
				}
				if (q->cost[_ar_NT] == 0) {
					p->cost[_ar_NT] = 0;
					p->rule._ar = q->rule._ar;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 3;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: INDIRP2(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 14;
			_closure_reg(a, c + 0);
		}
		break;
	case 2165: /* CVFI2 */
		_label(LEFT_CHILD(a));
		/* reg: CVFI2(regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 19;
			_closure_reg(a, c + 0);
		}
		break;
	case 2181: /* CVII2 */
		_label(LEFT_CHILD(a));
		/* reg: CVII2(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 15;
			_closure_reg(a, c + 0);
		}
		break;
	case 2182: /* CVIU2 */
		_label(LEFT_CHILD(a));
		/* reg: CVIU2(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 16;
			_closure_reg(a, c + 0);
		}
		break;
	case 2198: /* CVPU2 */
		_label(LEFT_CHILD(a));
		/* reg: CVPU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 21;
			_closure_reg(a, c + 0);
		}
		break;
	case 2229: /* CVUI2 */
		_label(LEFT_CHILD(a));
		/* reg: CVUI2(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 17;
			_closure_reg(a, c + 0);
		}
		break;
	case 2230: /* CVUU2 */
		_label(LEFT_CHILD(a));
		/* reg: CVUU2(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 18;
			_closure_reg(a, c + 0);
		}
		break;
	case 2231: /* CVUP2 */
		_label(LEFT_CHILD(a));
		/* reg: CVUP2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 22;
			_closure_reg(a, c + 0);
		}
		break;
	case 2245: /* NEGI2 */
		_label(LEFT_CHILD(a));
		/* reg: NEGI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 39;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: NEGI2(INDIRI2(lgaddr)) */
			LEFT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 40;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 2261: /* CALLI2 */
		_label(LEFT_CHILD(a));
		/* reg: CALLI2(ar) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_ar_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 79;
			_closure_reg(a, c + 0);
		}
		break;
	case 2262: /* CALLU2 */
		_label(LEFT_CHILD(a));
		/* reg: CALLU2(ar) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_ar_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 80;
			_closure_reg(a, c + 0);
		}
		break;
	case 2263: /* CALLP2 */
		_label(LEFT_CHILD(a));
		/* reg: CALLP2(ar) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_ar_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 81;
			_closure_reg(a, c + 0);
		}
		break;
	case 2277: /* LOADI2 */
		_label(LEFT_CHILD(a));
		/* reg: LOADI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 4;
			_closure_reg(a, c + 0);
		}
		/* reg: LOADI2(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 7;
			_closure_reg(a, c + 0);
		}
		break;
	case 2278: /* LOADU2 */
		_label(LEFT_CHILD(a));
		/* reg: LOADU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 5;
			_closure_reg(a, c + 0);
		}
		/* reg: LOADU2(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 8;
			_closure_reg(a, c + 0);
		}
		break;
	case 2279: /* LOADP2 */
		_label(LEFT_CHILD(a));
		/* reg: LOADP2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 6;
			_closure_reg(a, c + 0);
		}
		break;
	case 2293: /* RETI2 */
		_label(LEFT_CHILD(a));
		/* stmt: RETI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 184;
		}
		break;
	case 2294: /* RETU2 */
		_label(LEFT_CHILD(a));
		/* stmt: RETU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 185;
		}
		break;
	case 2295: /* RETP2 */
		_label(LEFT_CHILD(a));
		/* stmt: RETP2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 186;
		}
		break;
	case 2311: /* ADDRGP2 */
		/* lgaddr: ADDRGP2 */
		if (0 + 0 < p->cost[_lgaddr_NT]) {
			p->cost[_lgaddr_NT] = 0 + 0;
			p->rule._lgaddr = 1;
			_closure_lgaddr(a, 0 + 0);
		}
		/* albl: ADDRGP2 */
		if (0 + 0 < p->cost[_albl_NT]) {
			p->cost[_albl_NT] = 0 + 0;
			p->rule._albl = 1;
			_closure_albl(a, 0 + 0);
		}
		break;
	case 2327: /* ADDRFP2 */
		/* lgaddr: ADDRFP2 */
		if (0 + 0 < p->cost[_lgaddr_NT]) {
			p->cost[_lgaddr_NT] = 0 + 0;
			p->rule._lgaddr = 2;
			_closure_lgaddr(a, 0 + 0);
		}
		break;
	case 2343: /* ADDRLP2 */
		/* lgaddr: ADDRLP2 */
		if (0 + 0 < p->cost[_lgaddr_NT]) {
			p->cost[_lgaddr_NT] = 0 + 0;
			p->rule._lgaddr = 3;
			_closure_lgaddr(a, 0 + 0);
		}
		break;
	case 2357: /* ADDI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: ADDI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 23;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: ADDI2(reg,INDIRI2(addr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 24;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: ADDI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 25;
			_closure_reg(a, c + 0);
		}
		if (	/* reg8: ADDI2(reg8,CVII2(INDIRI1(addr))) */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 18;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: ADDI2(CVII2(reg8),CVII2(INDIRI1(addr))) */
			LEFT_CHILD(a)->op == 2181 && /* CVII2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 19;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: ADDI2(CVUI2(reg8),CVII2(INDIRI1(addr))) */
			LEFT_CHILD(a)->op == 2229 && /* CVUI2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 20;
				_closure_reg8(a, c + 0);
			}
		}
		/* reg8: ADDI2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 21;
			_closure_reg8(a, c + 0);
		}
		if (	/* reg8: ADDI2(CVII2(reg8),con) */
			LEFT_CHILD(a)->op == 2181 /* CVII2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 22;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: ADDI2(CVUI2(reg8),con) */
			LEFT_CHILD(a)->op == 2229 /* CVUI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 23;
				_closure_reg8(a, c + 0);
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
			p->rule._reg = 26;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: ADDU2(reg,INDIRU2(addr)) */
			RIGHT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 27;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: ADDU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 28;
			_closure_reg(a, c + 0);
		}
		if (	/* reg8: ADDU2(reg8,CVUU2(INDIRU1(addr))) */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 24;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: ADDU2(CVUU2(reg8),CVUU2(INDIRU1(addr))) */
			LEFT_CHILD(a)->op == 2230 && /* CVUU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 25;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: ADDU2(CVIU2(reg8),CVUU2(INDIRU1(addr))) */
			LEFT_CHILD(a)->op == 2182 && /* CVIU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 26;
				_closure_reg8(a, c + 0);
			}
		}
		/* reg8: ADDU2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 27;
			_closure_reg8(a, c + 0);
		}
		if (	/* reg8: ADDU2(CVUU2(reg8),con) */
			LEFT_CHILD(a)->op == 2230 /* CVUU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 28;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: ADDU2(CVIU2(reg8),con) */
			LEFT_CHILD(a)->op == 2182 /* CVIU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 29;
				_closure_reg8(a, c + 0);
			}
		}
		break;
	case 2359: /* ADDP2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* addr: ADDP2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 0;
		if (c + 0 < p->cost[_addr_NT]) {
			p->cost[_addr_NT] = c + 0;
			p->rule._addr = 3;
		}
		/* reg: ADDP2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 29;
			_closure_reg(a, c + 0);
		}
		/* reg: ADDP2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 30;
			_closure_reg(a, c + 0);
		}
		break;
	case 2373: /* SUBI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: SUBI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 31;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: SUBI2(reg,INDIRI2(addr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 32;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: SUBI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 33;
			_closure_reg(a, c + 0);
		}
		if (	/* reg8: SUBI2(reg8,CVII2(INDIRI1(addr))) */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 30;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: SUBI2(CVII2(reg8),CVII2(INDIRI1(addr))) */
			LEFT_CHILD(a)->op == 2181 && /* CVII2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 31;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: SUBI2(CVUI2(reg8),CVII2(INDIRI1(addr))) */
			LEFT_CHILD(a)->op == 2229 && /* CVUI2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 32;
				_closure_reg8(a, c + 0);
			}
		}
		/* reg8: SUBI2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 33;
			_closure_reg8(a, c + 0);
		}
		if (	/* reg8: SUBI2(CVII2(reg8),con) */
			LEFT_CHILD(a)->op == 2181 /* CVII2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 34;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: SUBI2(CVUI2(reg8),con) */
			LEFT_CHILD(a)->op == 2229 /* CVUI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 35;
				_closure_reg8(a, c + 0);
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
			p->rule._reg = 34;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: SUBU2(reg,INDIRU2(addr)) */
			RIGHT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 35;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: SUBU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 36;
			_closure_reg(a, c + 0);
		}
		if (	/* reg8: SUBU2(reg8,CVUU2(INDIRU1(addr))) */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 36;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: SUBU2(CVUU2(reg8),CVUU2(INDIRU1(addr))) */
			LEFT_CHILD(a)->op == 2230 && /* CVUU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 37;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: SUBU2(CVIU2(reg8),CVUU2(INDIRU1(addr))) */
			LEFT_CHILD(a)->op == 2182 && /* CVIU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 38;
				_closure_reg8(a, c + 0);
			}
		}
		/* reg8: SUBU2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 39;
			_closure_reg8(a, c + 0);
		}
		if (	/* reg8: SUBU2(CVUU2(reg8),con) */
			LEFT_CHILD(a)->op == 2230 /* CVUU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 40;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: SUBU2(CVIU2(reg8),con) */
			LEFT_CHILD(a)->op == 2182 /* CVIU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 41;
				_closure_reg8(a, c + 0);
			}
		}
		break;
	case 2375: /* SUBP2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* addr: SUBP2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 0;
		if (c + 0 < p->cost[_addr_NT]) {
			p->cost[_addr_NT] = c + 0;
			p->rule._addr = 4;
		}
		/* reg: SUBP2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 37;
			_closure_reg(a, c + 0);
		}
		/* reg: SUBP2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 38;
			_closure_reg(a, c + 0);
		}
		break;
	case 2389: /* LSHI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: LSHI2(reg,con1) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con1_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 67;
			_closure_reg(a, c + 0);
		}
		/* reg: LSHI2(reg,con2) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con2_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 71;
			_closure_reg(a, c + 0);
		}
		/* reg: LSHI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 75;
			_closure_reg(a, c + 0);
		}
		break;
	case 2390: /* LSHU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: LSHU2(reg,con1) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con1_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 68;
			_closure_reg(a, c + 0);
		}
		/* reg: LSHU2(reg,con2) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con2_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 72;
			_closure_reg(a, c + 0);
		}
		/* reg: LSHU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 76;
			_closure_reg(a, c + 0);
		}
		break;
	case 2405: /* MODI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MODI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 65;
			_closure_reg(a, c + 0);
		}
		break;
	case 2406: /* MODU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MODU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 66;
			_closure_reg(a, c + 0);
		}
		break;
	case 2421: /* RSHI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: RSHI2(reg,con1) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con1_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 69;
			_closure_reg(a, c + 0);
		}
		/* reg: RSHI2(reg,con2) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con2_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 73;
			_closure_reg(a, c + 0);
		}
		/* reg: RSHI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 77;
			_closure_reg(a, c + 0);
		}
		break;
	case 2422: /* RSHU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: RSHU2(reg,con1) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con1_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 70;
			_closure_reg(a, c + 0);
		}
		/* reg: RSHU2(reg,con2) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con2_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 74;
			_closure_reg(a, c + 0);
		}
		/* reg: RSHU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 78;
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
			p->rule._reg = 41;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: BANDI2(reg,INDIRI2(lgaddr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 42;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: BANDI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 43;
			_closure_reg(a, c + 0);
		}
		if (	/* reg8: BANDI2(reg8,CVII2(INDIRI1(lgaddr))) */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 42;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: BANDI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
			LEFT_CHILD(a)->op == 2181 && /* CVII2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 43;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: BANDI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
			LEFT_CHILD(a)->op == 2229 && /* CVUI2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 44;
				_closure_reg8(a, c + 0);
			}
		}
		/* reg8: BANDI2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 45;
			_closure_reg8(a, c + 0);
		}
		if (	/* reg8: BANDI2(CVII2(reg8),con) */
			LEFT_CHILD(a)->op == 2181 /* CVII2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 46;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: BANDI2(CVUI2(reg8),con) */
			LEFT_CHILD(a)->op == 2229 /* CVUI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 47;
				_closure_reg8(a, c + 0);
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
			p->rule._reg = 44;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: BANDU2(reg,INDIRU2(lgaddr)) */
			RIGHT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 45;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: BANDU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 46;
			_closure_reg(a, c + 0);
		}
		if (	/* reg8: BANDU2(reg8,CVUU2(INDIRU1(lgaddr))) */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 48;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: BANDU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
			LEFT_CHILD(a)->op == 2230 && /* CVUU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 49;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: BANDU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
			LEFT_CHILD(a)->op == 2182 && /* CVIU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 50;
				_closure_reg8(a, c + 0);
			}
		}
		/* reg8: BANDU2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 51;
			_closure_reg8(a, c + 0);
		}
		if (	/* reg8: BANDU2(CVUU2(reg8),con) */
			LEFT_CHILD(a)->op == 2230 /* CVUU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 52;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: BANDU2(CVIU2(reg8),con) */
			LEFT_CHILD(a)->op == 2182 /* CVIU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 53;
				_closure_reg8(a, c + 0);
			}
		}
		break;
	case 2453: /* BCOMI2 */
		_label(LEFT_CHILD(a));
		/* reg: BCOMI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 47;
			_closure_reg(a, c + 0);
		}
		break;
	case 2454: /* BCOMU2 */
		_label(LEFT_CHILD(a));
		/* reg: BCOMU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 48;
			_closure_reg(a, c + 0);
		}
		break;
	case 2469: /* BORI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BORI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 49;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: BORI2(reg,INDIRI2(lgaddr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 50;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: BORI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 51;
			_closure_reg(a, c + 0);
		}
		if (	/* reg8: BORI2(reg8,CVII2(INDIRI1(lgaddr))) */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 54;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: BORI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
			LEFT_CHILD(a)->op == 2181 && /* CVII2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 55;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: BORI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
			LEFT_CHILD(a)->op == 2229 && /* CVUI2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 56;
				_closure_reg8(a, c + 0);
			}
		}
		/* reg8: BORI2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 57;
			_closure_reg8(a, c + 0);
		}
		if (	/* reg8: BORI2(CVII2(reg8),con) */
			LEFT_CHILD(a)->op == 2181 /* CVII2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 58;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: BORI2(CVUI2(reg8),con) */
			LEFT_CHILD(a)->op == 2229 /* CVUI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 59;
				_closure_reg8(a, c + 0);
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
			p->rule._reg = 52;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: BORU2(reg,INDIRU2(lgaddr)) */
			RIGHT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 53;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: BORU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 54;
			_closure_reg(a, c + 0);
		}
		if (	/* reg8: BORU2(reg8,CVUU2(INDIRU1(lgaddr))) */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 60;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: BORU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
			LEFT_CHILD(a)->op == 2230 && /* CVUU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 61;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: BORU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
			LEFT_CHILD(a)->op == 2182 && /* CVIU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 62;
				_closure_reg8(a, c + 0);
			}
		}
		/* reg8: BORU2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 63;
			_closure_reg8(a, c + 0);
		}
		if (	/* reg8: BORU2(CVUU2(reg8),con) */
			LEFT_CHILD(a)->op == 2230 /* CVUU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 64;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: BORU2(CVIU2(reg8),con) */
			LEFT_CHILD(a)->op == 2182 /* CVIU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 65;
				_closure_reg8(a, c + 0);
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
			p->rule._reg = 55;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: BXORI2(reg,INDIRI2(lgaddr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 56;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: BXORI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 57;
			_closure_reg(a, c + 0);
		}
		if (	/* reg8: BXORI2(reg8,CVII2(INDIRI1(lgaddr))) */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 66;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: BXORI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
			LEFT_CHILD(a)->op == 2181 && /* CVII2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 67;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: BXORI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
			LEFT_CHILD(a)->op == 2229 && /* CVUI2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 68;
				_closure_reg8(a, c + 0);
			}
		}
		/* reg8: BXORI2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 69;
			_closure_reg8(a, c + 0);
		}
		if (	/* reg8: BXORI2(CVII2(reg8),con) */
			LEFT_CHILD(a)->op == 2181 /* CVII2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 70;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: BXORI2(CVUI2(reg8),con) */
			LEFT_CHILD(a)->op == 2229 /* CVUI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 71;
				_closure_reg8(a, c + 0);
			}
		}
		break;
	case 2486: /* BXORU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BXORU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 58;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: BXORU2(reg,INDIRU2(lgaddr)) */
			RIGHT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 59;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: BXORU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 60;
			_closure_reg(a, c + 0);
		}
		if (	/* reg8: BXORU2(reg8,CVUU2(INDIRU1(lgaddr))) */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 72;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: BXORU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
			LEFT_CHILD(a)->op == 2230 && /* CVUU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 73;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: BXORU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
			LEFT_CHILD(a)->op == 2182 && /* CVIU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 74;
				_closure_reg8(a, c + 0);
			}
		}
		/* reg8: BXORU2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 75;
			_closure_reg8(a, c + 0);
		}
		if (	/* reg8: BXORU2(CVUU2(reg8),con) */
			LEFT_CHILD(a)->op == 2230 /* CVUU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 76;
				_closure_reg8(a, c + 0);
			}
		}
		if (	/* reg8: BXORU2(CVIU2(reg8),con) */
			LEFT_CHILD(a)->op == 2182 /* CVIU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 77;
				_closure_reg8(a, c + 0);
			}
		}
		break;
	case 2501: /* DIVI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: DIVI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 63;
			_closure_reg(a, c + 0);
		}
		break;
	case 2502: /* DIVU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: DIVU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 64;
			_closure_reg(a, c + 0);
		}
		break;
	case 2517: /* MULI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MULI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 61;
			_closure_reg(a, c + 0);
		}
		break;
	case 2518: /* MULU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MULU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 62;
			_closure_reg(a, c + 0);
		}
		break;
	case 2533: /* EQI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: EQI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 44;
		}
		if (	/* stmt: EQI2(reg,INDIRI2(lgaddr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 45;
			}
		}
		/* stmt: EQI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 46;
		}
		if (	/* stmt: EQI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
			LEFT_CHILD(a)->op == 2181 && /* CVII2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 47;
			}
		}
		if (	/* stmt: EQI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
			LEFT_CHILD(a)->op == 2229 && /* CVUI2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 48;
			}
		}
		if (	/* stmt: EQI2(CVII2(reg8),con) */
			LEFT_CHILD(a)->op == 2181 /* CVII2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 49;
			}
		}
		if (	/* stmt: EQI2(CVUI2(reg8),con) */
			LEFT_CHILD(a)->op == 2229 /* CVUI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 50;
			}
		}
		break;
	case 2534: /* EQU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: EQU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 51;
		}
		if (	/* stmt: EQU2(reg,INDIRU2(lgaddr)) */
			RIGHT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 52;
			}
		}
		/* stmt: EQU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 53;
		}
		if (	/* stmt: EQU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
			LEFT_CHILD(a)->op == 2230 && /* CVUU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 54;
			}
		}
		if (	/* stmt: EQU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
			LEFT_CHILD(a)->op == 2182 && /* CVIU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 55;
			}
		}
		if (	/* stmt: EQU2(CVUU2(reg8),con) */
			LEFT_CHILD(a)->op == 2230 /* CVUU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 56;
			}
		}
		if (	/* stmt: EQU2(CVIU2(reg8),con) */
			LEFT_CHILD(a)->op == 2182 /* CVIU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 57;
			}
		}
		break;
	case 2549: /* GEI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GEI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 132;
		}
		if (	/* stmt: GEI2(reg,INDIRI2(lgaddr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 133;
			}
		}
		/* stmt: GEI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 134;
		}
		if (	/* stmt: GEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
			LEFT_CHILD(a)->op == 2181 && /* CVII2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 135;
			}
		}
		if (	/* stmt: GEI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
			LEFT_CHILD(a)->op == 2229 && /* CVUI2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 136;
			}
		}
		if (	/* stmt: GEI2(CVII2(reg8),con) */
			LEFT_CHILD(a)->op == 2181 /* CVII2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 137;
			}
		}
		if (	/* stmt: GEI2(CVUI2(reg8),con) */
			LEFT_CHILD(a)->op == 2229 /* CVUI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 138;
			}
		}
		break;
	case 2550: /* GEU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GEU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 139;
		}
		if (	/* stmt: GEU2(reg,INDIRU2(lgaddr)) */
			RIGHT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 140;
			}
		}
		/* stmt: GEU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 141;
		}
		if (	/* stmt: GEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
			LEFT_CHILD(a)->op == 2230 && /* CVUU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 142;
			}
		}
		if (	/* stmt: GEU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
			LEFT_CHILD(a)->op == 2182 && /* CVIU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 143;
			}
		}
		if (	/* stmt: GEU2(CVUU2(reg8),con) */
			LEFT_CHILD(a)->op == 2230 /* CVUU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 144;
			}
		}
		if (	/* stmt: GEU2(CVIU2(reg8),con) */
			LEFT_CHILD(a)->op == 2182 /* CVIU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 145;
			}
		}
		break;
	case 2565: /* GTI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GTI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 154;
		}
		if (	/* stmt: GTI2(reg,INDIRI2(lgaddr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 155;
			}
		}
		/* stmt: GTI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 156;
		}
		if (	/* stmt: GTI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
			LEFT_CHILD(a)->op == 2181 && /* CVII2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 157;
			}
		}
		if (	/* stmt: GTI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
			LEFT_CHILD(a)->op == 2229 && /* CVUI2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 158;
			}
		}
		if (	/* stmt: GTI2(CVII2(reg8),con) */
			LEFT_CHILD(a)->op == 2181 /* CVII2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 159;
			}
		}
		if (	/* stmt: GTI2(CVUI2(reg8),con) */
			LEFT_CHILD(a)->op == 2229 /* CVUI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 160;
			}
		}
		break;
	case 2566: /* GTU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GTU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 161;
		}
		if (	/* stmt: GTU2(reg,INDIRU2(lgaddr)) */
			RIGHT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 162;
			}
		}
		/* stmt: GTU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 163;
		}
		if (	/* stmt: GTU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
			LEFT_CHILD(a)->op == 2230 && /* CVUU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 164;
			}
		}
		if (	/* stmt: GTU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
			LEFT_CHILD(a)->op == 2182 && /* CVIU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 165;
			}
		}
		if (	/* stmt: GTU2(CVUU2(reg8),con) */
			LEFT_CHILD(a)->op == 2230 /* CVUU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 166;
			}
		}
		if (	/* stmt: GTU2(CVIU2(reg8),con) */
			LEFT_CHILD(a)->op == 2182 /* CVIU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 167;
			}
		}
		break;
	case 2581: /* LEI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LEI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 88;
		}
		if (	/* stmt: LEI2(reg,INDIRI2(lgaddr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 89;
			}
		}
		/* stmt: LEI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 90;
		}
		if (	/* stmt: LEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
			LEFT_CHILD(a)->op == 2181 && /* CVII2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 91;
			}
		}
		if (	/* stmt: LEI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
			LEFT_CHILD(a)->op == 2229 && /* CVUI2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 92;
			}
		}
		if (	/* stmt: LEI2(CVII2(reg8),con) */
			LEFT_CHILD(a)->op == 2181 /* CVII2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 93;
			}
		}
		if (	/* stmt: LEI2(CVUI2(reg8),con) */
			LEFT_CHILD(a)->op == 2229 /* CVUI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 94;
			}
		}
		break;
	case 2582: /* LEU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LEU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 95;
		}
		if (	/* stmt: LEU2(reg,INDIRU2(lgaddr)) */
			RIGHT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 96;
			}
		}
		/* stmt: LEU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 97;
		}
		if (	/* stmt: LEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
			LEFT_CHILD(a)->op == 2230 && /* CVUU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 98;
			}
		}
		if (	/* stmt: LEU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
			LEFT_CHILD(a)->op == 2182 && /* CVIU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 99;
			}
		}
		if (	/* stmt: LEU2(CVUU2(reg8),con) */
			LEFT_CHILD(a)->op == 2230 /* CVUU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 100;
			}
		}
		if (	/* stmt: LEU2(CVIU2(reg8),con) */
			LEFT_CHILD(a)->op == 2182 /* CVIU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 101;
			}
		}
		break;
	case 2597: /* LTI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LTI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 110;
		}
		if (	/* stmt: LTI2(reg,INDIRI2(lgaddr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 111;
			}
		}
		/* stmt: LTI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 112;
		}
		if (	/* stmt: LTI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
			LEFT_CHILD(a)->op == 2181 && /* CVII2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 113;
			}
		}
		if (	/* stmt: LTI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
			LEFT_CHILD(a)->op == 2229 && /* CVUI2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 114;
			}
		}
		if (	/* stmt: LTI2(CVII2(reg8),con) */
			LEFT_CHILD(a)->op == 2181 /* CVII2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 115;
			}
		}
		if (	/* stmt: LTI2(CVUI2(reg8),con) */
			LEFT_CHILD(a)->op == 2229 /* CVUI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 116;
			}
		}
		break;
	case 2598: /* LTU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LTU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 117;
		}
		if (	/* stmt: LTU2(reg,INDIRU2(lgaddr)) */
			RIGHT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 118;
			}
		}
		/* stmt: LTU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 119;
		}
		if (	/* stmt: LTU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
			LEFT_CHILD(a)->op == 2230 && /* CVUU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 120;
			}
		}
		if (	/* stmt: LTU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
			LEFT_CHILD(a)->op == 2182 && /* CVIU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 121;
			}
		}
		if (	/* stmt: LTU2(CVUU2(reg8),con) */
			LEFT_CHILD(a)->op == 2230 /* CVUU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 122;
			}
		}
		if (	/* stmt: LTU2(CVIU2(reg8),con) */
			LEFT_CHILD(a)->op == 2182 /* CVIU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 123;
			}
		}
		break;
	case 2613: /* NEI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: NEI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 66;
		}
		if (	/* stmt: NEI2(reg,INDIRI2(lgaddr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 67;
			}
		}
		/* stmt: NEI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 68;
		}
		if (	/* stmt: NEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
			LEFT_CHILD(a)->op == 2181 && /* CVII2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 69;
			}
		}
		if (	/* stmt: NEI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
			LEFT_CHILD(a)->op == 2229 && /* CVUI2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 70;
			}
		}
		if (	/* stmt: NEI2(CVII2(reg8),con) */
			LEFT_CHILD(a)->op == 2181 /* CVII2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 71;
			}
		}
		if (	/* stmt: NEI2(CVUI2(reg8),con) */
			LEFT_CHILD(a)->op == 2229 /* CVUI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 72;
			}
		}
		break;
	case 2614: /* NEU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: NEU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 73;
		}
		if (	/* stmt: NEU2(reg,INDIRU2(lgaddr)) */
			RIGHT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 74;
			}
		}
		/* stmt: NEU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 75;
		}
		if (	/* stmt: NEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
			LEFT_CHILD(a)->op == 2230 && /* CVUU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 76;
			}
		}
		if (	/* stmt: NEU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
			LEFT_CHILD(a)->op == 2182 && /* CVIU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 77;
			}
		}
		if (	/* stmt: NEU2(CVUU2(reg8),con) */
			LEFT_CHILD(a)->op == 2230 /* CVUU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 78;
			}
		}
		if (	/* stmt: NEU2(CVIU2(reg8),con) */
			LEFT_CHILD(a)->op == 2182 /* CVIU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 79;
			}
		}
		break;
	case 4113: /* CNSTF4 */
		break;
	case 4117: /* CNSTI4 */
		break;
	case 4118: /* CNSTU4 */
		break;
	case 4129: /* ARGF4 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGF4(regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 181;
		}
		break;
	case 4133: /* ARGI4 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGI4(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 179;
		}
		break;
	case 4134: /* ARGU4 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGU4(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 180;
		}
		break;
	case 4145: /* ASGNF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNF4(VREGP,regf) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 8;
			}
		}
		/* stmt: ASGNF4(lgaddr,regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 24;
		}
		if (	/* stmt: ASGNF4(lgaddr,INDIRF4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 25;
			}
		}
		if (	/* stmt: ASGNF4(lgaddr,ADDF4(INDIRF4(lgaddr),INDIRF4(lgaddr))) */
			RIGHT_CHILD(a)->op == 4401 && /* ADDF4 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 4161 && /* INDIRF4 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 32;
			}
		}
		if (	/* stmt: ASGNF4(lgaddr,ADDF4(INDIRF4(lgaddr),INDIRF4(lgaddr))) */
			RIGHT_CHILD(a)->op == 4401 && /* ADDF4 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 4161 && /* INDIRF4 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + (memop(a));
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 33;
			}
		}
		if (	/* stmt: ASGNF4(lgaddr,SUBF4(INDIRF4(lgaddr),INDIRF4(lgaddr))) */
			RIGHT_CHILD(a)->op == 4417 && /* SUBF4 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 4161 && /* INDIRF4 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 40;
			}
		}
		if (	/* stmt: ASGNF4(lgaddr,SUBF4(INDIRF4(lgaddr),INDIRF4(lgaddr))) */
			RIGHT_CHILD(a)->op == 4417 && /* SUBF4 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 4161 && /* INDIRF4 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + (memop(a));
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 41;
			}
		}
		break;
	case 4149: /* ASGNI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNI4(VREGP,reg32) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 5;
			}
		}
		/* stmt: ASGNI4(lgaddr,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 20;
		}
		if (	/* stmt: ASGNI4(lgaddr,INDIRI4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 21;
			}
		}
		if (	/* stmt: ASGNI4(lgaddr,ADDI4(INDIRI4(lgaddr),INDIRI4(lgaddr))) */
			RIGHT_CHILD(a)->op == 4405 && /* ADDI4 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 4165 && /* INDIRI4 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 28;
			}
		}
		if (	/* stmt: ASGNI4(lgaddr,ADDI4(INDIRI4(lgaddr),INDIRI4(lgaddr))) */
			RIGHT_CHILD(a)->op == 4405 && /* ADDI4 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 4165 && /* INDIRI4 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + (memop(a));
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 29;
			}
		}
		if (	/* stmt: ASGNI4(lgaddr,SUBI4(INDIRI4(lgaddr),INDIRI4(lgaddr))) */
			RIGHT_CHILD(a)->op == 4421 && /* SUBI4 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 4165 && /* INDIRI4 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 36;
			}
		}
		if (	/* stmt: ASGNI4(lgaddr,SUBI4(INDIRI4(lgaddr),INDIRI4(lgaddr))) */
			RIGHT_CHILD(a)->op == 4421 && /* SUBI4 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 4165 && /* INDIRI4 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + (memop(a));
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 37;
			}
		}
		break;
	case 4150: /* ASGNU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNU4(VREGP,reg32) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 6;
			}
		}
		/* stmt: ASGNU4(lgaddr,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 22;
		}
		if (	/* stmt: ASGNU4(lgaddr,INDIRU4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 23;
			}
		}
		if (	/* stmt: ASGNU4(lgaddr,ADDU4(INDIRU4(lgaddr),INDIRU4(lgaddr))) */
			RIGHT_CHILD(a)->op == 4406 && /* ADDU4 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 4166 && /* INDIRU4 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 30;
			}
		}
		if (	/* stmt: ASGNU4(lgaddr,ADDU4(INDIRU4(lgaddr),INDIRU4(lgaddr))) */
			RIGHT_CHILD(a)->op == 4406 && /* ADDU4 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 4166 && /* INDIRU4 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + (memop(a));
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 31;
			}
		}
		if (	/* stmt: ASGNU4(lgaddr,SUBU4(INDIRU4(lgaddr),INDIRU4(lgaddr))) */
			RIGHT_CHILD(a)->op == 4422 && /* SUBU4 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 4166 && /* INDIRU4 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 38;
			}
		}
		if (	/* stmt: ASGNU4(lgaddr,SUBU4(INDIRU4(lgaddr),INDIRU4(lgaddr))) */
			RIGHT_CHILD(a)->op == 4422 && /* SUBU4 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 4166 && /* INDIRU4 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + (memop(a));
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 39;
			}
		}
		break;
	case 4161: /* INDIRF4 */
		_label(LEFT_CHILD(a));
		if (	/* regf: INDIRF4(VREGP) */
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
				if (q->cost[_reg32_NT] == 0) {
					p->cost[_reg32_NT] = 0;
					p->rule._reg32 = q->rule._reg32;
				}
				if (q->cost[_regf_NT] == 0) {
					p->cost[_regf_NT] = 0;
					p->rule._regf = q->rule._regf;
				}
				if (q->cost[_con8_NT] == 0) {
					p->cost[_con8_NT] = 0;
					p->rule._con8 = q->rule._con8;
				}
				if (q->cost[_con16_NT] == 0) {
					p->cost[_con16_NT] = 0;
					p->rule._con16 = q->rule._con16;
				}
				if (q->cost[_con0_NT] == 0) {
					p->cost[_con0_NT] = 0;
					p->rule._con0 = q->rule._con0;
				}
				if (q->cost[_con1_NT] == 0) {
					p->cost[_con1_NT] = 0;
					p->rule._con1 = q->rule._con1;
				}
				if (q->cost[_con2_NT] == 0) {
					p->cost[_con2_NT] = 0;
					p->rule._con2 = q->rule._con2;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_lgaddr_NT] == 0) {
					p->cost[_lgaddr_NT] = 0;
					p->rule._lgaddr = q->rule._lgaddr;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_albl_NT] == 0) {
					p->cost[_albl_NT] = 0;
					p->rule._albl = q->rule._albl;
				}
				if (q->cost[_ar_NT] == 0) {
					p->cost[_ar_NT] = 0;
					p->rule._ar = q->rule._ar;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_regf_NT]) {
				p->cost[_regf_NT] = c + 0;
				p->rule._regf = 1;
				_closure_regf(a, c + 0);
			}
		}
		/* regf: INDIRF4(lgaddr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 5;
			_closure_regf(a, c + 0);
		}
		/* regf: INDIRF4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 7;
			_closure_regf(a, c + 0);
		}
		break;
	case 4165: /* INDIRI4 */
		_label(LEFT_CHILD(a));
		if (	/* reg32: INDIRI4(VREGP) */
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
				if (q->cost[_reg32_NT] == 0) {
					p->cost[_reg32_NT] = 0;
					p->rule._reg32 = q->rule._reg32;
				}
				if (q->cost[_regf_NT] == 0) {
					p->cost[_regf_NT] = 0;
					p->rule._regf = q->rule._regf;
				}
				if (q->cost[_con8_NT] == 0) {
					p->cost[_con8_NT] = 0;
					p->rule._con8 = q->rule._con8;
				}
				if (q->cost[_con16_NT] == 0) {
					p->cost[_con16_NT] = 0;
					p->rule._con16 = q->rule._con16;
				}
				if (q->cost[_con0_NT] == 0) {
					p->cost[_con0_NT] = 0;
					p->rule._con0 = q->rule._con0;
				}
				if (q->cost[_con1_NT] == 0) {
					p->cost[_con1_NT] = 0;
					p->rule._con1 = q->rule._con1;
				}
				if (q->cost[_con2_NT] == 0) {
					p->cost[_con2_NT] = 0;
					p->rule._con2 = q->rule._con2;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_lgaddr_NT] == 0) {
					p->cost[_lgaddr_NT] = 0;
					p->rule._lgaddr = q->rule._lgaddr;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_albl_NT] == 0) {
					p->cost[_albl_NT] = 0;
					p->rule._albl = q->rule._albl;
				}
				if (q->cost[_ar_NT] == 0) {
					p->cost[_ar_NT] = 0;
					p->rule._ar = q->rule._ar;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 1;
				_closure_reg32(a, c + 0);
			}
		}
		/* reg32: INDIRI4(lgaddr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 5;
			_closure_reg32(a, c + 0);
		}
		/* reg32: INDIRI4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 7;
			_closure_reg32(a, c + 0);
		}
		break;
	case 4166: /* INDIRU4 */
		_label(LEFT_CHILD(a));
		if (	/* reg32: INDIRU4(VREGP) */
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
				if (q->cost[_reg32_NT] == 0) {
					p->cost[_reg32_NT] = 0;
					p->rule._reg32 = q->rule._reg32;
				}
				if (q->cost[_regf_NT] == 0) {
					p->cost[_regf_NT] = 0;
					p->rule._regf = q->rule._regf;
				}
				if (q->cost[_con8_NT] == 0) {
					p->cost[_con8_NT] = 0;
					p->rule._con8 = q->rule._con8;
				}
				if (q->cost[_con16_NT] == 0) {
					p->cost[_con16_NT] = 0;
					p->rule._con16 = q->rule._con16;
				}
				if (q->cost[_con0_NT] == 0) {
					p->cost[_con0_NT] = 0;
					p->rule._con0 = q->rule._con0;
				}
				if (q->cost[_con1_NT] == 0) {
					p->cost[_con1_NT] = 0;
					p->rule._con1 = q->rule._con1;
				}
				if (q->cost[_con2_NT] == 0) {
					p->cost[_con2_NT] = 0;
					p->rule._con2 = q->rule._con2;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_lgaddr_NT] == 0) {
					p->cost[_lgaddr_NT] = 0;
					p->rule._lgaddr = q->rule._lgaddr;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_albl_NT] == 0) {
					p->cost[_albl_NT] = 0;
					p->rule._albl = q->rule._albl;
				}
				if (q->cost[_ar_NT] == 0) {
					p->cost[_ar_NT] = 0;
					p->rule._ar = q->rule._ar;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 2;
				_closure_reg32(a, c + 0);
			}
		}
		/* reg32: INDIRU4(lgaddr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 6;
			_closure_reg32(a, c + 0);
		}
		/* reg32: INDIRU4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 8;
			_closure_reg32(a, c + 0);
		}
		break;
	case 4209: /* CVFF4 */
		_label(LEFT_CHILD(a));
		/* regf: CVFF4(regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 15;
			_closure_regf(a, c + 0);
		}
		break;
	case 4213: /* CVFI4 */
		_label(LEFT_CHILD(a));
		/* reg: CVFI4(regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 20;
			_closure_reg(a, c + 0);
		}
		break;
	case 4225: /* CVIF4 */
		_label(LEFT_CHILD(a));
		/* regf: CVIF4(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 9;
			_closure_regf(a, c + 0);
		}
		/* regf: CVIF4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 10;
			_closure_regf(a, c + 0);
		}
		/* regf: CVIF4(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 11;
			_closure_regf(a, c + 0);
		}
		break;
	case 4229: /* CVII4 */
		_label(LEFT_CHILD(a));
		/* reg32: CVII4(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 9;
			_closure_reg32(a, c + 0);
		}
		/* reg32: CVII4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 13;
			_closure_reg32(a, c + 0);
		}
		break;
	case 4230: /* CVIU4 */
		_label(LEFT_CHILD(a));
		/* reg32: CVIU4(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 10;
			_closure_reg32(a, c + 0);
		}
		/* reg32: CVIU4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 14;
			_closure_reg32(a, c + 0);
		}
		break;
	case 4277: /* CVUI4 */
		_label(LEFT_CHILD(a));
		/* reg32: CVUI4(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 11;
			_closure_reg32(a, c + 0);
		}
		/* reg32: CVUI4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 15;
			_closure_reg32(a, c + 0);
		}
		break;
	case 4278: /* CVUU4 */
		_label(LEFT_CHILD(a));
		/* reg32: CVUU4(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 12;
			_closure_reg32(a, c + 0);
		}
		/* reg32: CVUU4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 16;
			_closure_reg32(a, c + 0);
		}
		break;
	case 4289: /* NEGF4 */
		_label(LEFT_CHILD(a));
		/* regf: NEGF4(regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 25;
			_closure_regf(a, c + 0);
		}
		if (	/* regf: NEGF4(INDIRF4(lgaddr)) */
			LEFT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_regf_NT]) {
				p->cost[_regf_NT] = c + 0;
				p->rule._regf = 26;
				_closure_regf(a, c + 0);
			}
		}
		break;
	case 4293: /* NEGI4 */
		_label(LEFT_CHILD(a));
		/* reg32: NEGI4(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 25;
			_closure_reg32(a, c + 0);
		}
		if (	/* reg32: NEGI4(INDIRI4(lgaddr)) */
			LEFT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 26;
				_closure_reg32(a, c + 0);
			}
		}
		break;
	case 4305: /* CALLF4 */
		_label(LEFT_CHILD(a));
		/* regf: CALLF4(ar) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_ar_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 37;
			_closure_regf(a, c + 0);
		}
		break;
	case 4309: /* CALLI4 */
		_label(LEFT_CHILD(a));
		/* reg32: CALLI4(ar) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_ar_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 57;
			_closure_reg32(a, c + 0);
		}
		break;
	case 4310: /* CALLU4 */
		_label(LEFT_CHILD(a));
		/* reg32: CALLU4(ar) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_ar_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 58;
			_closure_reg32(a, c + 0);
		}
		break;
	case 4321: /* LOADF4 */
		_label(LEFT_CHILD(a));
		/* regf: LOADF4(regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + (move(a));
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 3;
			_closure_regf(a, c + 0);
		}
		break;
	case 4325: /* LOADI4 */
		_label(LEFT_CHILD(a));
		/* reg32: LOADI4(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + (move(a));
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 3;
			_closure_reg32(a, c + 0);
		}
		break;
	case 4326: /* LOADU4 */
		_label(LEFT_CHILD(a));
		/* reg32: LOADU4(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + (move(a));
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 4;
			_closure_reg32(a, c + 0);
		}
		break;
	case 4337: /* RETF4 */
		_label(LEFT_CHILD(a));
		/* stmt: RETF4(regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 190;
		}
		break;
	case 4341: /* RETI4 */
		_label(LEFT_CHILD(a));
		/* stmt: RETI4(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 188;
		}
		break;
	case 4342: /* RETU4 */
		_label(LEFT_CHILD(a));
		/* stmt: RETU4(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 189;
		}
		break;
	case 4401: /* ADDF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* regf: ADDF4(regf,regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 17;
			_closure_regf(a, c + 0);
		}
		if (	/* regf: ADDF4(regf,INDIRF4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_regf_NT]) {
				p->cost[_regf_NT] = c + 0;
				p->rule._regf = 18;
				_closure_regf(a, c + 0);
			}
		}
		break;
	case 4405: /* ADDI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg32: ADDI4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 17;
			_closure_reg32(a, c + 0);
		}
		if (	/* reg32: ADDI4(reg32,INDIRI4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 18;
				_closure_reg32(a, c + 0);
			}
		}
		break;
	case 4406: /* ADDU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg32: ADDU4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 19;
			_closure_reg32(a, c + 0);
		}
		if (	/* reg32: ADDU4(reg32,INDIRU4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 20;
				_closure_reg32(a, c + 0);
			}
		}
		break;
	case 4417: /* SUBF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* regf: SUBF4(regf,regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 21;
			_closure_regf(a, c + 0);
		}
		if (	/* regf: SUBF4(regf,INDIRF4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_regf_NT]) {
				p->cost[_regf_NT] = c + 0;
				p->rule._regf = 22;
				_closure_regf(a, c + 0);
			}
		}
		break;
	case 4421: /* SUBI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg32: SUBI4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 21;
			_closure_reg32(a, c + 0);
		}
		if (	/* reg32: SUBI4(reg32,INDIRI4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 22;
				_closure_reg32(a, c + 0);
			}
		}
		break;
	case 4422: /* SUBU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg32: SUBU4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 23;
			_closure_reg32(a, c + 0);
		}
		if (	/* reg32: SUBU4(reg32,INDIRU4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 24;
				_closure_reg32(a, c + 0);
			}
		}
		break;
	case 4437: /* LSHI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg32: LSHI4(reg32,con1) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con1_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 53;
			_closure_reg32(a, c + 0);
		}
		break;
	case 4438: /* LSHU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg32: LSHU4(reg32,con1) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con1_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 54;
			_closure_reg32(a, c + 0);
		}
		break;
	case 4453: /* MODI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg32: MODI4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 49;
			_closure_reg32(a, c + 0);
		}
		if (	/* reg32: MODI4(reg32,INDIRI4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 50;
				_closure_reg32(a, c + 0);
			}
		}
		break;
	case 4454: /* MODU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg32: MODU4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 51;
			_closure_reg32(a, c + 0);
		}
		if (	/* reg32: MODU4(reg32,INDIRU4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 52;
				_closure_reg32(a, c + 0);
			}
		}
		break;
	case 4469: /* RSHI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg32: RSHI4(reg32,con1) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con1_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 55;
			_closure_reg32(a, c + 0);
		}
		break;
	case 4470: /* RSHU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg32: RSHU4(reg32,con1) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con1_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 56;
			_closure_reg32(a, c + 0);
		}
		break;
	case 4485: /* BANDI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg32: BANDI4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 27;
			_closure_reg32(a, c + 0);
		}
		if (	/* reg32: BANDI4(reg32,INDIRI4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 28;
				_closure_reg32(a, c + 0);
			}
		}
		break;
	case 4486: /* BANDU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg32: BANDU4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 29;
			_closure_reg32(a, c + 0);
		}
		if (	/* reg32: BANDU4(reg32,INDIRU4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 30;
				_closure_reg32(a, c + 0);
			}
		}
		break;
	case 4501: /* BCOMI4 */
		_label(LEFT_CHILD(a));
		/* reg32: BCOMI4(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 31;
			_closure_reg32(a, c + 0);
		}
		break;
	case 4502: /* BCOMU4 */
		_label(LEFT_CHILD(a));
		/* reg32: BCOMU4(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 32;
			_closure_reg32(a, c + 0);
		}
		break;
	case 4517: /* BORI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg32: BORI4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 33;
			_closure_reg32(a, c + 0);
		}
		if (	/* reg32: BORI4(reg32,INDIRI4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 34;
				_closure_reg32(a, c + 0);
			}
		}
		break;
	case 4518: /* BORU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg32: BORU4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 35;
			_closure_reg32(a, c + 0);
		}
		if (	/* reg32: BORU4(reg32,INDIRU4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 36;
				_closure_reg32(a, c + 0);
			}
		}
		break;
	case 4533: /* BXORI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg32: BXORI4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 37;
			_closure_reg32(a, c + 0);
		}
		if (	/* reg32: BXORI4(reg32,INDIRI4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 38;
				_closure_reg32(a, c + 0);
			}
		}
		break;
	case 4534: /* BXORU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg32: BXORU4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 39;
			_closure_reg32(a, c + 0);
		}
		if (	/* reg32: BXORU4(reg32,INDIRU4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 40;
				_closure_reg32(a, c + 0);
			}
		}
		break;
	case 4545: /* DIVF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* regf: DIVF4(regf,regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 33;
			_closure_regf(a, c + 0);
		}
		if (	/* regf: DIVF4(regf,INDIRF4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_regf_NT]) {
				p->cost[_regf_NT] = c + 0;
				p->rule._regf = 34;
				_closure_regf(a, c + 0);
			}
		}
		break;
	case 4549: /* DIVI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg32: DIVI4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 45;
			_closure_reg32(a, c + 0);
		}
		if (	/* reg32: DIVI4(reg32,INDIRI4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 46;
				_closure_reg32(a, c + 0);
			}
		}
		break;
	case 4550: /* DIVU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg32: DIVU4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 47;
			_closure_reg32(a, c + 0);
		}
		if (	/* reg32: DIVU4(reg32,INDIRU4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 48;
				_closure_reg32(a, c + 0);
			}
		}
		break;
	case 4561: /* MULF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* regf: MULF4(regf,regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 29;
			_closure_regf(a, c + 0);
		}
		if (	/* regf: MULF4(regf,INDIRF4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_regf_NT]) {
				p->cost[_regf_NT] = c + 0;
				p->rule._regf = 30;
				_closure_regf(a, c + 0);
			}
		}
		break;
	case 4565: /* MULI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg32: MULI4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 41;
			_closure_reg32(a, c + 0);
		}
		if (	/* reg32: MULI4(reg32,INDIRI4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 42;
				_closure_reg32(a, c + 0);
			}
		}
		break;
	case 4566: /* MULU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg32: MULU4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 43;
			_closure_reg32(a, c + 0);
		}
		if (	/* reg32: MULU4(reg32,INDIRU4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 44;
				_closure_reg32(a, c + 0);
			}
		}
		break;
	case 4577: /* EQF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: EQF4(regf,regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 62;
		}
		if (	/* stmt: EQF4(regf,INDIRF4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 63;
			}
		}
		break;
	case 4581: /* EQI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: EQI4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 58;
		}
		if (	/* stmt: EQI4(reg32,INDIRI4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 59;
			}
		}
		break;
	case 4582: /* EQU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: EQU4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 60;
		}
		if (	/* stmt: EQU4(reg32,INDIRU4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 61;
			}
		}
		break;
	case 4593: /* GEF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GEF4(regf,regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 150;
		}
		if (	/* stmt: GEF4(regf,INDIRF4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 151;
			}
		}
		break;
	case 4597: /* GEI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GEI4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 146;
		}
		if (	/* stmt: GEI4(reg32,INDIRI4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 147;
			}
		}
		break;
	case 4598: /* GEU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GEU4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 148;
		}
		if (	/* stmt: GEU4(reg32,INDIRU4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 149;
			}
		}
		break;
	case 4609: /* GTF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GTF4(regf,regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 172;
		}
		if (	/* stmt: GTF4(regf,INDIRF4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 173;
			}
		}
		break;
	case 4613: /* GTI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GTI4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 168;
		}
		if (	/* stmt: GTI4(reg32,INDIRI4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 169;
			}
		}
		break;
	case 4614: /* GTU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GTU4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 170;
		}
		if (	/* stmt: GTU4(reg32,INDIRU4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 171;
			}
		}
		break;
	case 4625: /* LEF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LEF4(regf,regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 106;
		}
		if (	/* stmt: LEF4(regf,INDIRF4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 107;
			}
		}
		break;
	case 4629: /* LEI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LEI4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 102;
		}
		if (	/* stmt: LEI4(reg32,INDIRI4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 103;
			}
		}
		break;
	case 4630: /* LEU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LEU4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 104;
		}
		if (	/* stmt: LEU4(reg32,INDIRU4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 105;
			}
		}
		break;
	case 4641: /* LTF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LTF4(regf,regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 128;
		}
		if (	/* stmt: LTF4(regf,INDIRF4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 129;
			}
		}
		break;
	case 4645: /* LTI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LTI4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 124;
		}
		if (	/* stmt: LTI4(reg32,INDIRI4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 125;
			}
		}
		break;
	case 4646: /* LTU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LTU4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 126;
		}
		if (	/* stmt: LTU4(reg32,INDIRU4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 127;
			}
		}
		break;
	case 4657: /* NEF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: NEF4(regf,regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 84;
		}
		if (	/* stmt: NEF4(regf,INDIRF4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 85;
			}
		}
		break;
	case 4661: /* NEI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: NEI4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 80;
		}
		if (	/* stmt: NEI4(reg32,INDIRI4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 81;
			}
		}
		break;
	case 4662: /* NEU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: NEU4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 82;
		}
		if (	/* stmt: NEU4(reg32,INDIRU4(lgaddr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 83;
			}
		}
		break;
	case 8209: /* CNSTF8 */
		break;
	case 8225: /* ARGF8 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGF8(regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + 8;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 182;
		}
		break;
	case 8241: /* ASGNF8 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNF8(VREGP,regf) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 9;
			}
		}
		/* stmt: ASGNF8(lgaddr,regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 26;
		}
		if (	/* stmt: ASGNF8(lgaddr,INDIRF8(lgaddr)) */
			RIGHT_CHILD(a)->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 27;
			}
		}
		if (	/* stmt: ASGNF8(lgaddr,ADDF8(INDIRF8(lgaddr),INDIRF8(lgaddr))) */
			RIGHT_CHILD(a)->op == 8497 && /* ADDF8 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 8257 && /* INDIRF8 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 8;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 34;
			}
		}
		if (	/* stmt: ASGNF8(lgaddr,ADDF8(INDIRF8(lgaddr),INDIRF8(lgaddr))) */
			RIGHT_CHILD(a)->op == 8497 && /* ADDF8 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 8257 && /* INDIRF8 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + (memop(a));
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 35;
			}
		}
		if (	/* stmt: ASGNF8(lgaddr,SUBF8(INDIRF8(lgaddr),INDIRF8(lgaddr))) */
			RIGHT_CHILD(a)->op == 8513 && /* SUBF8 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 8257 && /* INDIRF8 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 8;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 42;
			}
		}
		if (	/* stmt: ASGNF8(lgaddr,SUBF8(INDIRF8(lgaddr),INDIRF8(lgaddr))) */
			RIGHT_CHILD(a)->op == 8513 && /* SUBF8 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 8257 && /* INDIRF8 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + (memop(a));
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 43;
			}
		}
		break;
	case 8257: /* INDIRF8 */
		_label(LEFT_CHILD(a));
		if (	/* regf: INDIRF8(VREGP) */
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
				if (q->cost[_reg32_NT] == 0) {
					p->cost[_reg32_NT] = 0;
					p->rule._reg32 = q->rule._reg32;
				}
				if (q->cost[_regf_NT] == 0) {
					p->cost[_regf_NT] = 0;
					p->rule._regf = q->rule._regf;
				}
				if (q->cost[_con8_NT] == 0) {
					p->cost[_con8_NT] = 0;
					p->rule._con8 = q->rule._con8;
				}
				if (q->cost[_con16_NT] == 0) {
					p->cost[_con16_NT] = 0;
					p->rule._con16 = q->rule._con16;
				}
				if (q->cost[_con0_NT] == 0) {
					p->cost[_con0_NT] = 0;
					p->rule._con0 = q->rule._con0;
				}
				if (q->cost[_con1_NT] == 0) {
					p->cost[_con1_NT] = 0;
					p->rule._con1 = q->rule._con1;
				}
				if (q->cost[_con2_NT] == 0) {
					p->cost[_con2_NT] = 0;
					p->rule._con2 = q->rule._con2;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_lgaddr_NT] == 0) {
					p->cost[_lgaddr_NT] = 0;
					p->rule._lgaddr = q->rule._lgaddr;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_albl_NT] == 0) {
					p->cost[_albl_NT] = 0;
					p->rule._albl = q->rule._albl;
				}
				if (q->cost[_ar_NT] == 0) {
					p->cost[_ar_NT] = 0;
					p->rule._ar = q->rule._ar;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_regf_NT]) {
				p->cost[_regf_NT] = c + 0;
				p->rule._regf = 2;
				_closure_regf(a, c + 0);
			}
		}
		/* regf: INDIRF8(lgaddr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_lgaddr_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 6;
			_closure_regf(a, c + 0);
		}
		/* regf: INDIRF8(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 8;
			_closure_regf(a, c + 0);
		}
		break;
	case 8305: /* CVFF8 */
		_label(LEFT_CHILD(a));
		/* regf: CVFF8(regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 16;
			_closure_regf(a, c + 0);
		}
		break;
	case 8321: /* CVIF8 */
		_label(LEFT_CHILD(a));
		/* regf: CVIF8(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + 8;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 12;
			_closure_regf(a, c + 0);
		}
		/* regf: CVIF8(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 8;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 13;
			_closure_regf(a, c + 0);
		}
		/* regf: CVIF8(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 8;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 14;
			_closure_regf(a, c + 0);
		}
		break;
	case 8385: /* NEGF8 */
		_label(LEFT_CHILD(a));
		/* regf: NEGF8(regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + 8;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 27;
			_closure_regf(a, c + 0);
		}
		if (	/* regf: NEGF8(INDIRF8(lgaddr)) */
			LEFT_CHILD(a)->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 8;
			if (c + 0 < p->cost[_regf_NT]) {
				p->cost[_regf_NT] = c + 0;
				p->rule._regf = 28;
				_closure_regf(a, c + 0);
			}
		}
		break;
	case 8401: /* CALLF8 */
		_label(LEFT_CHILD(a));
		/* regf: CALLF8(ar) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_ar_NT] + 8;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 38;
			_closure_regf(a, c + 0);
		}
		break;
	case 8417: /* LOADF8 */
		_label(LEFT_CHILD(a));
		/* regf: LOADF8(regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + (move(a));
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 4;
			_closure_regf(a, c + 0);
		}
		break;
	case 8433: /* RETF8 */
		_label(LEFT_CHILD(a));
		/* stmt: RETF8(regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 191;
		}
		break;
	case 8497: /* ADDF8 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* regf: ADDF8(regf,regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 8;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 19;
			_closure_regf(a, c + 0);
		}
		if (	/* regf: ADDF8(regf,INDIRF8(lgaddr)) */
			RIGHT_CHILD(a)->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 8;
			if (c + 0 < p->cost[_regf_NT]) {
				p->cost[_regf_NT] = c + 0;
				p->rule._regf = 20;
				_closure_regf(a, c + 0);
			}
		}
		break;
	case 8513: /* SUBF8 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* regf: SUBF8(regf,regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 8;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 23;
			_closure_regf(a, c + 0);
		}
		if (	/* regf: SUBF8(regf,INDIRF8(lgaddr)) */
			RIGHT_CHILD(a)->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 8;
			if (c + 0 < p->cost[_regf_NT]) {
				p->cost[_regf_NT] = c + 0;
				p->rule._regf = 24;
				_closure_regf(a, c + 0);
			}
		}
		break;
	case 8641: /* DIVF8 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* regf: DIVF8(regf,regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 35;
			_closure_regf(a, c + 0);
		}
		if (	/* regf: DIVF8(regf,INDIRF8(lgaddr)) */
			RIGHT_CHILD(a)->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_regf_NT]) {
				p->cost[_regf_NT] = c + 0;
				p->rule._regf = 36;
				_closure_regf(a, c + 0);
			}
		}
		break;
	case 8657: /* MULF8 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* regf: MULF8(regf,regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 31;
			_closure_regf(a, c + 0);
		}
		if (	/* regf: MULF8(regf,INDIRF8(lgaddr)) */
			RIGHT_CHILD(a)->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 4;
			if (c + 0 < p->cost[_regf_NT]) {
				p->cost[_regf_NT] = c + 0;
				p->rule._regf = 32;
				_closure_regf(a, c + 0);
			}
		}
		break;
	case 8673: /* EQF8 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: EQF8(regf,regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 8;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 64;
		}
		if (	/* stmt: EQF8(regf,INDIRF8(lgaddr)) */
			RIGHT_CHILD(a)->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 8;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 65;
			}
		}
		break;
	case 8689: /* GEF8 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GEF8(regf,regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 8;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 152;
		}
		if (	/* stmt: GEF8(regf,INDIRF8(lgaddr)) */
			RIGHT_CHILD(a)->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 8;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 153;
			}
		}
		break;
	case 8705: /* GTF8 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GTF8(regf,regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 8;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 174;
		}
		if (	/* stmt: GTF8(regf,INDIRF8(lgaddr)) */
			RIGHT_CHILD(a)->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 8;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 175;
			}
		}
		break;
	case 8721: /* LEF8 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LEF8(regf,regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 8;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 108;
		}
		if (	/* stmt: LEF8(regf,INDIRF8(lgaddr)) */
			RIGHT_CHILD(a)->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 8;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 109;
			}
		}
		break;
	case 8737: /* LTF8 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LTF8(regf,regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 8;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 130;
		}
		if (	/* stmt: LTF8(regf,INDIRF8(lgaddr)) */
			RIGHT_CHILD(a)->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 8;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 131;
			}
		}
		break;
	case 8753: /* NEF8 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: NEF8(regf,regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 8;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 86;
		}
		if (	/* stmt: NEF8(regf,INDIRF8(lgaddr)) */
			RIGHT_CHILD(a)->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 8;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 87;
			}
		}
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
	case 477: /* stmt: LABELV */
	case 470: /* stmt: RETV */
	case 69: /* albl: ADDRGP2 */
	case 64: /* lgaddr: ADDRLP2 */
	case 63: /* lgaddr: ADDRFP2 */
	case 62: /* lgaddr: ADDRGP2 */
	case 56: /* con2: CNSTU2 */
	case 55: /* con2: CNSTI2 */
	case 54: /* con2: CNSTU1 */
	case 53: /* con2: CNSTI1 */
	case 52: /* con1: CNSTU2 */
	case 51: /* con1: CNSTI2 */
	case 50: /* con1: CNSTU1 */
	case 49: /* con1: CNSTI1 */
	case 48: /* con0: CNSTU2 */
	case 47: /* con0: CNSTI2 */
	case 46: /* con0: CNSTU1 */
	case 45: /* con0: CNSTI1 */
	case 44: /* con16: CNSTP2 */
	case 43: /* con16: CNSTU2 */
	case 42: /* con16: CNSTI2 */
	case 41: /* con8: CNSTU1 */
	case 40: /* con8: CNSTI1 */
	case 9: /* regf: INDIRF8(VREGP) */
	case 8: /* regf: INDIRF4(VREGP) */
	case 7: /* reg: INDIRP2(VREGP) */
	case 6: /* reg32: INDIRU4(VREGP) */
	case 5: /* reg32: INDIRI4(VREGP) */
	case 4: /* reg: INDIRU2(VREGP) */
	case 3: /* reg: INDIRI2(VREGP) */
	case 2: /* reg8: INDIRU1(VREGP) */
	case 1: /* reg8: INDIRI1(VREGP) */
		break;
	case 18: /* stmt: ASGNF8(VREGP,regf) */
	case 17: /* stmt: ASGNF4(VREGP,regf) */
	case 16: /* stmt: ASGNP2(VREGP,reg) */
	case 15: /* stmt: ASGNU4(VREGP,reg32) */
	case 14: /* stmt: ASGNI4(VREGP,reg32) */
	case 13: /* stmt: ASGNU2(VREGP,reg) */
	case 12: /* stmt: ASGNI2(VREGP,reg) */
	case 11: /* stmt: ASGNU1(VREGP,reg8) */
	case 10: /* stmt: ASGNI1(VREGP,reg8) */
		kids[0] = RIGHT_CHILD(p);
		break;
	case 72: /* reg: lgaddr */
	case 71: /* ar: albl */
	case 70: /* ar: reg */
	case 66: /* addr: reg */
	case 65: /* addr: lgaddr */
	case 61: /* reg8: con8 */
	case 60: /* reg: con0 */
	case 59: /* reg: con */
	case 58: /* con: con16 */
	case 57: /* con: con8 */
	case 22: /* stmt: regf */
	case 21: /* stmt: reg32 */
	case 20: /* stmt: reg */
	case 19: /* stmt: reg8 */
		kids[0] = p;
		break;
	case 476: /* stmt: JUMPV(reg) */
	case 475: /* stmt: JUMPV(albl) */
	case 474: /* stmt: RETF8(regf) */
	case 473: /* stmt: RETF4(regf) */
	case 472: /* stmt: RETU4(reg32) */
	case 471: /* stmt: RETI4(reg32) */
	case 469: /* stmt: RETP2(reg) */
	case 468: /* stmt: RETU2(reg) */
	case 467: /* stmt: RETI2(reg) */
	case 466: /* regf: CALLF8(ar) */
	case 465: /* regf: CALLF4(ar) */
	case 464: /* reg32: CALLU4(ar) */
	case 463: /* reg32: CALLI4(ar) */
	case 462: /* stmt: CALLV(ar) */
	case 461: /* reg: CALLP2(ar) */
	case 460: /* reg: CALLU2(ar) */
	case 459: /* reg: CALLI2(ar) */
	case 458: /* stmt: ARGF8(regf) */
	case 457: /* stmt: ARGF4(regf) */
	case 456: /* stmt: ARGU4(reg32) */
	case 455: /* stmt: ARGI4(reg32) */
	case 454: /* stmt: ARGP2(reg) */
	case 453: /* stmt: ARGU2(reg) */
	case 452: /* stmt: ARGI2(reg) */
	case 233: /* reg32: BCOMU4(reg32) */
	case 232: /* reg32: BCOMI4(reg32) */
	case 231: /* reg: BCOMU2(reg) */
	case 230: /* reg: BCOMI2(reg) */
	case 206: /* regf: NEGF8(regf) */
	case 204: /* regf: NEGF4(regf) */
	case 202: /* reg32: NEGI4(reg32) */
	case 200: /* reg: NEGI2(reg) */
	case 127: /* reg: CVUP2(reg) */
	case 126: /* reg: CVPU2(reg) */
	case 125: /* regf: CVFF8(regf) */
	case 124: /* regf: CVFF4(regf) */
	case 123: /* reg: CVFI4(regf) */
	case 122: /* reg: CVFI2(regf) */
	case 121: /* regf: CVIF8(reg32) */
	case 120: /* regf: CVIF8(reg) */
	case 119: /* regf: CVIF8(reg8) */
	case 118: /* regf: CVIF4(reg32) */
	case 117: /* regf: CVIF4(reg) */
	case 116: /* regf: CVIF4(reg8) */
	case 115: /* reg32: CVUU4(reg) */
	case 114: /* reg32: CVUI4(reg) */
	case 113: /* reg32: CVIU4(reg) */
	case 112: /* reg32: CVII4(reg) */
	case 111: /* reg32: CVUU4(reg8) */
	case 110: /* reg32: CVUI4(reg8) */
	case 109: /* reg32: CVIU4(reg8) */
	case 108: /* reg32: CVII4(reg8) */
	case 107: /* reg: CVUU2(reg8) */
	case 106: /* reg: CVUI2(reg8) */
	case 105: /* reg: CVIU2(reg8) */
	case 104: /* reg: CVII2(reg8) */
	case 103: /* reg8: CVUU1(reg32) */
	case 102: /* reg8: CVUI1(reg32) */
	case 101: /* reg8: CVIU1(reg32) */
	case 100: /* reg8: CVII1(reg32) */
	case 99: /* regf: INDIRF8(reg) */
	case 98: /* regf: INDIRF4(reg) */
	case 97: /* reg32: INDIRU4(reg) */
	case 96: /* reg32: INDIRI4(reg) */
	case 95: /* regf: INDIRF8(lgaddr) */
	case 94: /* regf: INDIRF4(lgaddr) */
	case 93: /* reg32: INDIRU4(lgaddr) */
	case 92: /* reg32: INDIRI4(lgaddr) */
	case 91: /* reg: INDIRP2(addr) */
	case 90: /* reg: INDIRU2(addr) */
	case 89: /* reg: INDIRI2(addr) */
	case 88: /* reg8: INDIRU1(addr) */
	case 87: /* reg8: INDIRI1(addr) */
	case 39: /* reg: LOADU2(reg32) */
	case 38: /* reg: LOADI2(reg32) */
	case 37: /* reg8: LOADU1(reg32) */
	case 36: /* reg8: LOADI1(reg32) */
	case 33: /* regf: LOADF8(regf) */
	case 32: /* regf: LOADF4(regf) */
	case 31: /* reg32: LOADU4(reg32) */
	case 30: /* reg32: LOADI4(reg32) */
	case 29: /* reg: LOADP2(reg) */
	case 28: /* reg: LOADU2(reg) */
	case 27: /* reg: LOADI2(reg) */
	case 26: /* reg8: LOADU1(reg) */
	case 25: /* reg8: LOADI1(reg) */
	case 24: /* reg8: LOADU1(reg8) */
	case 23: /* reg8: LOADI1(reg8) */
		kids[0] = LEFT_CHILD(p);
		break;
	case 35: /* reg8: LOADI1(LOADI2(CVUU2(reg8))) */
	case 34: /* reg8: LOADU1(LOADU2(CVII2(reg8))) */
		kids[0] = LEFT_CHILD(LEFT_CHILD(LEFT_CHILD(p)));
		break;
	case 450: /* stmt: GTF8(regf,regf) */
	case 448: /* stmt: GTF4(regf,regf) */
	case 446: /* stmt: GTU4(reg32,reg32) */
	case 444: /* stmt: GTI4(reg32,reg32) */
	case 439: /* stmt: GTU2(reg,con) */
	case 437: /* stmt: GTU2(reg,reg) */
	case 432: /* stmt: GTI2(reg,con) */
	case 430: /* stmt: GTI2(reg,reg) */
	case 428: /* stmt: GEF8(regf,regf) */
	case 426: /* stmt: GEF4(regf,regf) */
	case 424: /* stmt: GEU4(reg32,reg32) */
	case 422: /* stmt: GEI4(reg32,reg32) */
	case 417: /* stmt: GEU2(reg,con) */
	case 415: /* stmt: GEU2(reg,reg) */
	case 410: /* stmt: GEI2(reg,con) */
	case 408: /* stmt: GEI2(reg,reg) */
	case 406: /* stmt: LTF8(regf,regf) */
	case 404: /* stmt: LTF4(regf,regf) */
	case 402: /* stmt: LTU4(reg32,reg32) */
	case 400: /* stmt: LTI4(reg32,reg32) */
	case 395: /* stmt: LTU2(reg,con) */
	case 393: /* stmt: LTU2(reg,reg) */
	case 388: /* stmt: LTI2(reg,con) */
	case 386: /* stmt: LTI2(reg,reg) */
	case 384: /* stmt: LEF8(regf,regf) */
	case 382: /* stmt: LEF4(regf,regf) */
	case 380: /* stmt: LEU4(reg32,reg32) */
	case 378: /* stmt: LEI4(reg32,reg32) */
	case 373: /* stmt: LEU2(reg,con) */
	case 371: /* stmt: LEU2(reg,reg) */
	case 366: /* stmt: LEI2(reg,con) */
	case 364: /* stmt: LEI2(reg,reg) */
	case 362: /* stmt: NEF8(regf,regf) */
	case 360: /* stmt: NEF4(regf,regf) */
	case 358: /* stmt: NEU4(reg32,reg32) */
	case 356: /* stmt: NEI4(reg32,reg32) */
	case 351: /* stmt: NEU2(reg,con) */
	case 349: /* stmt: NEU2(reg,reg) */
	case 344: /* stmt: NEI2(reg,con) */
	case 342: /* stmt: NEI2(reg,reg) */
	case 340: /* stmt: EQF8(regf,regf) */
	case 338: /* stmt: EQF4(regf,regf) */
	case 336: /* stmt: EQU4(reg32,reg32) */
	case 334: /* stmt: EQI4(reg32,reg32) */
	case 329: /* stmt: EQU2(reg,con) */
	case 327: /* stmt: EQU2(reg,reg) */
	case 322: /* stmt: EQI2(reg,con) */
	case 320: /* stmt: EQI2(reg,reg) */
	case 319: /* reg32: RSHU4(reg32,con1) */
	case 318: /* reg32: RSHI4(reg32,con1) */
	case 317: /* reg32: LSHU4(reg32,con1) */
	case 316: /* reg32: LSHI4(reg32,con1) */
	case 315: /* reg: RSHU2(reg,reg) */
	case 314: /* reg: RSHI2(reg,reg) */
	case 313: /* reg: LSHU2(reg,reg) */
	case 312: /* reg: LSHI2(reg,reg) */
	case 311: /* reg: RSHU2(reg,con2) */
	case 310: /* reg: RSHI2(reg,con2) */
	case 309: /* reg: LSHU2(reg,con2) */
	case 308: /* reg: LSHI2(reg,con2) */
	case 307: /* reg: RSHU2(reg,con1) */
	case 306: /* reg: RSHI2(reg,con1) */
	case 305: /* reg: LSHU2(reg,con1) */
	case 304: /* reg: LSHI2(reg,con1) */
	case 302: /* regf: DIVF8(regf,regf) */
	case 300: /* regf: DIVF4(regf,regf) */
	case 298: /* regf: MULF8(regf,regf) */
	case 296: /* regf: MULF4(regf,regf) */
	case 294: /* reg32: MODU4(reg32,reg32) */
	case 292: /* reg32: MODI4(reg32,reg32) */
	case 290: /* reg32: DIVU4(reg32,reg32) */
	case 288: /* reg32: DIVI4(reg32,reg32) */
	case 286: /* reg32: MULU4(reg32,reg32) */
	case 284: /* reg32: MULI4(reg32,reg32) */
	case 283: /* reg: MODU2(reg,reg) */
	case 282: /* reg: MODI2(reg,reg) */
	case 281: /* reg: DIVU2(reg,reg) */
	case 280: /* reg: DIVI2(reg,reg) */
	case 279: /* reg: MULU2(reg,reg) */
	case 278: /* reg: MULI2(reg,reg) */
	case 276: /* reg32: BXORU4(reg32,reg32) */
	case 274: /* reg32: BXORI4(reg32,reg32) */
	case 271: /* reg8: BXORU2(reg8,con) */
	case 265: /* reg8: BXORI2(reg8,con) */
	case 261: /* reg: BXORU2(reg,con) */
	case 259: /* reg: BXORU2(reg,reg) */
	case 258: /* reg: BXORI2(reg,con) */
	case 256: /* reg: BXORI2(reg,reg) */
	case 254: /* reg32: BORU4(reg32,reg32) */
	case 252: /* reg32: BORI4(reg32,reg32) */
	case 249: /* reg8: BORU2(reg8,con) */
	case 243: /* reg8: BORI2(reg8,con) */
	case 239: /* reg: BORU2(reg,con) */
	case 237: /* reg: BORU2(reg,reg) */
	case 236: /* reg: BORI2(reg,con) */
	case 234: /* reg: BORI2(reg,reg) */
	case 228: /* reg32: BANDU4(reg32,reg32) */
	case 226: /* reg32: BANDI4(reg32,reg32) */
	case 223: /* reg8: BANDU2(reg8,con) */
	case 217: /* reg8: BANDI2(reg8,con) */
	case 213: /* reg: BANDU2(reg,con) */
	case 211: /* reg: BANDU2(reg,reg) */
	case 210: /* reg: BANDI2(reg,con) */
	case 208: /* reg: BANDI2(reg,reg) */
	case 190: /* regf: SUBF8(regf,regf) */
	case 188: /* regf: SUBF4(regf,regf) */
	case 186: /* reg32: SUBU4(reg32,reg32) */
	case 184: /* reg32: SUBI4(reg32,reg32) */
	case 181: /* reg8: SUBU2(reg8,con) */
	case 175: /* reg8: SUBI2(reg8,con) */
	case 171: /* reg: SUBP2(reg,con) */
	case 170: /* reg: SUBP2(reg,reg) */
	case 169: /* reg: SUBU2(reg,con) */
	case 167: /* reg: SUBU2(reg,reg) */
	case 166: /* reg: SUBI2(reg,con) */
	case 164: /* reg: SUBI2(reg,reg) */
	case 154: /* regf: ADDF8(regf,regf) */
	case 152: /* regf: ADDF4(regf,regf) */
	case 150: /* reg32: ADDU4(reg32,reg32) */
	case 148: /* reg32: ADDI4(reg32,reg32) */
	case 145: /* reg8: ADDU2(reg8,con) */
	case 139: /* reg8: ADDI2(reg8,con) */
	case 135: /* reg: ADDP2(reg,con) */
	case 134: /* reg: ADDP2(reg,reg) */
	case 133: /* reg: ADDU2(reg,con) */
	case 131: /* reg: ADDU2(reg,reg) */
	case 130: /* reg: ADDI2(reg,con) */
	case 128: /* reg: ADDI2(reg,reg) */
	case 85: /* stmt: ASGNF8(lgaddr,regf) */
	case 83: /* stmt: ASGNF4(lgaddr,regf) */
	case 81: /* stmt: ASGNU4(lgaddr,reg32) */
	case 79: /* stmt: ASGNI4(lgaddr,reg32) */
	case 77: /* stmt: ASGNP2(addr,reg) */
	case 76: /* stmt: ASGNU2(addr,reg) */
	case 75: /* stmt: ASGNI2(addr,reg) */
	case 74: /* stmt: ASGNU1(addr,reg8) */
	case 73: /* stmt: ASGNI1(addr,reg8) */
	case 68: /* addr: SUBP2(reg,con) */
	case 67: /* addr: ADDP2(reg,con) */
		kids[0] = LEFT_CHILD(p);
		kids[1] = RIGHT_CHILD(p);
		break;
	case 451: /* stmt: GTF8(regf,INDIRF8(lgaddr)) */
	case 449: /* stmt: GTF4(regf,INDIRF4(lgaddr)) */
	case 447: /* stmt: GTU4(reg32,INDIRU4(lgaddr)) */
	case 445: /* stmt: GTI4(reg32,INDIRI4(lgaddr)) */
	case 438: /* stmt: GTU2(reg,INDIRU2(lgaddr)) */
	case 431: /* stmt: GTI2(reg,INDIRI2(lgaddr)) */
	case 429: /* stmt: GEF8(regf,INDIRF8(lgaddr)) */
	case 427: /* stmt: GEF4(regf,INDIRF4(lgaddr)) */
	case 425: /* stmt: GEU4(reg32,INDIRU4(lgaddr)) */
	case 423: /* stmt: GEI4(reg32,INDIRI4(lgaddr)) */
	case 416: /* stmt: GEU2(reg,INDIRU2(lgaddr)) */
	case 409: /* stmt: GEI2(reg,INDIRI2(lgaddr)) */
	case 407: /* stmt: LTF8(regf,INDIRF8(lgaddr)) */
	case 405: /* stmt: LTF4(regf,INDIRF4(lgaddr)) */
	case 403: /* stmt: LTU4(reg32,INDIRU4(lgaddr)) */
	case 401: /* stmt: LTI4(reg32,INDIRI4(lgaddr)) */
	case 394: /* stmt: LTU2(reg,INDIRU2(lgaddr)) */
	case 387: /* stmt: LTI2(reg,INDIRI2(lgaddr)) */
	case 385: /* stmt: LEF8(regf,INDIRF8(lgaddr)) */
	case 383: /* stmt: LEF4(regf,INDIRF4(lgaddr)) */
	case 381: /* stmt: LEU4(reg32,INDIRU4(lgaddr)) */
	case 379: /* stmt: LEI4(reg32,INDIRI4(lgaddr)) */
	case 372: /* stmt: LEU2(reg,INDIRU2(lgaddr)) */
	case 365: /* stmt: LEI2(reg,INDIRI2(lgaddr)) */
	case 363: /* stmt: NEF8(regf,INDIRF8(lgaddr)) */
	case 361: /* stmt: NEF4(regf,INDIRF4(lgaddr)) */
	case 359: /* stmt: NEU4(reg32,INDIRU4(lgaddr)) */
	case 357: /* stmt: NEI4(reg32,INDIRI4(lgaddr)) */
	case 350: /* stmt: NEU2(reg,INDIRU2(lgaddr)) */
	case 343: /* stmt: NEI2(reg,INDIRI2(lgaddr)) */
	case 341: /* stmt: EQF8(regf,INDIRF8(lgaddr)) */
	case 339: /* stmt: EQF4(regf,INDIRF4(lgaddr)) */
	case 337: /* stmt: EQU4(reg32,INDIRU4(lgaddr)) */
	case 335: /* stmt: EQI4(reg32,INDIRI4(lgaddr)) */
	case 328: /* stmt: EQU2(reg,INDIRU2(lgaddr)) */
	case 321: /* stmt: EQI2(reg,INDIRI2(lgaddr)) */
	case 303: /* regf: DIVF8(regf,INDIRF8(lgaddr)) */
	case 301: /* regf: DIVF4(regf,INDIRF4(lgaddr)) */
	case 299: /* regf: MULF8(regf,INDIRF8(lgaddr)) */
	case 297: /* regf: MULF4(regf,INDIRF4(lgaddr)) */
	case 295: /* reg32: MODU4(reg32,INDIRU4(lgaddr)) */
	case 293: /* reg32: MODI4(reg32,INDIRI4(lgaddr)) */
	case 291: /* reg32: DIVU4(reg32,INDIRU4(lgaddr)) */
	case 289: /* reg32: DIVI4(reg32,INDIRI4(lgaddr)) */
	case 287: /* reg32: MULU4(reg32,INDIRU4(lgaddr)) */
	case 285: /* reg32: MULI4(reg32,INDIRI4(lgaddr)) */
	case 277: /* reg32: BXORU4(reg32,INDIRU4(lgaddr)) */
	case 275: /* reg32: BXORI4(reg32,INDIRI4(lgaddr)) */
	case 260: /* reg: BXORU2(reg,INDIRU2(lgaddr)) */
	case 257: /* reg: BXORI2(reg,INDIRI2(lgaddr)) */
	case 255: /* reg32: BORU4(reg32,INDIRU4(lgaddr)) */
	case 253: /* reg32: BORI4(reg32,INDIRI4(lgaddr)) */
	case 238: /* reg: BORU2(reg,INDIRU2(lgaddr)) */
	case 235: /* reg: BORI2(reg,INDIRI2(lgaddr)) */
	case 229: /* reg32: BANDU4(reg32,INDIRU4(lgaddr)) */
	case 227: /* reg32: BANDI4(reg32,INDIRI4(lgaddr)) */
	case 212: /* reg: BANDU2(reg,INDIRU2(lgaddr)) */
	case 209: /* reg: BANDI2(reg,INDIRI2(lgaddr)) */
	case 191: /* regf: SUBF8(regf,INDIRF8(lgaddr)) */
	case 189: /* regf: SUBF4(regf,INDIRF4(lgaddr)) */
	case 187: /* reg32: SUBU4(reg32,INDIRU4(lgaddr)) */
	case 185: /* reg32: SUBI4(reg32,INDIRI4(lgaddr)) */
	case 168: /* reg: SUBU2(reg,INDIRU2(addr)) */
	case 165: /* reg: SUBI2(reg,INDIRI2(addr)) */
	case 155: /* regf: ADDF8(regf,INDIRF8(lgaddr)) */
	case 153: /* regf: ADDF4(regf,INDIRF4(lgaddr)) */
	case 151: /* reg32: ADDU4(reg32,INDIRU4(lgaddr)) */
	case 149: /* reg32: ADDI4(reg32,INDIRI4(lgaddr)) */
	case 132: /* reg: ADDU2(reg,INDIRU2(addr)) */
	case 129: /* reg: ADDI2(reg,INDIRI2(addr)) */
	case 86: /* stmt: ASGNF8(lgaddr,INDIRF8(lgaddr)) */
	case 84: /* stmt: ASGNF4(lgaddr,INDIRF4(lgaddr)) */
	case 82: /* stmt: ASGNU4(lgaddr,INDIRU4(lgaddr)) */
	case 80: /* stmt: ASGNI4(lgaddr,INDIRI4(lgaddr)) */
	case 78: /* stmt: ASGNB(reg,INDIRB(reg)) */
		kids[0] = LEFT_CHILD(p);
		kids[1] = LEFT_CHILD(RIGHT_CHILD(p));
		break;
	case 268: /* reg8: BXORU2(reg8,CVUU2(INDIRU1(lgaddr))) */
	case 262: /* reg8: BXORI2(reg8,CVII2(INDIRI1(lgaddr))) */
	case 246: /* reg8: BORU2(reg8,CVUU2(INDIRU1(lgaddr))) */
	case 240: /* reg8: BORI2(reg8,CVII2(INDIRI1(lgaddr))) */
	case 220: /* reg8: BANDU2(reg8,CVUU2(INDIRU1(lgaddr))) */
	case 214: /* reg8: BANDI2(reg8,CVII2(INDIRI1(lgaddr))) */
	case 178: /* reg8: SUBU2(reg8,CVUU2(INDIRU1(addr))) */
	case 172: /* reg8: SUBI2(reg8,CVII2(INDIRI1(addr))) */
	case 142: /* reg8: ADDU2(reg8,CVUU2(INDIRU1(addr))) */
	case 136: /* reg8: ADDI2(reg8,CVII2(INDIRI1(addr))) */
		kids[0] = LEFT_CHILD(p);
		kids[1] = LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(p)));
		break;
	case 441: /* stmt: GTU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 440: /* stmt: GTU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 434: /* stmt: GTI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 433: /* stmt: GTI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 419: /* stmt: GEU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 418: /* stmt: GEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 412: /* stmt: GEI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 411: /* stmt: GEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 397: /* stmt: LTU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 396: /* stmt: LTU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 390: /* stmt: LTI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 389: /* stmt: LTI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 375: /* stmt: LEU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 374: /* stmt: LEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 368: /* stmt: LEI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 367: /* stmt: LEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 353: /* stmt: NEU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 352: /* stmt: NEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 346: /* stmt: NEI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 345: /* stmt: NEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 331: /* stmt: EQU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 330: /* stmt: EQU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 324: /* stmt: EQI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 323: /* stmt: EQI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 270: /* reg8: BXORU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 269: /* reg8: BXORU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 264: /* reg8: BXORI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 263: /* reg8: BXORI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 248: /* reg8: BORU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 247: /* reg8: BORU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 242: /* reg8: BORI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 241: /* reg8: BORI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 222: /* reg8: BANDU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 221: /* reg8: BANDU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 216: /* reg8: BANDI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 215: /* reg8: BANDI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 180: /* reg8: SUBU2(CVIU2(reg8),CVUU2(INDIRU1(addr))) */
	case 179: /* reg8: SUBU2(CVUU2(reg8),CVUU2(INDIRU1(addr))) */
	case 174: /* reg8: SUBI2(CVUI2(reg8),CVII2(INDIRI1(addr))) */
	case 173: /* reg8: SUBI2(CVII2(reg8),CVII2(INDIRI1(addr))) */
	case 144: /* reg8: ADDU2(CVIU2(reg8),CVUU2(INDIRU1(addr))) */
	case 143: /* reg8: ADDU2(CVUU2(reg8),CVUU2(INDIRU1(addr))) */
	case 138: /* reg8: ADDI2(CVUI2(reg8),CVII2(INDIRI1(addr))) */
	case 137: /* reg8: ADDI2(CVII2(reg8),CVII2(INDIRI1(addr))) */
		kids[0] = LEFT_CHILD(LEFT_CHILD(p));
		kids[1] = LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(p)));
		break;
	case 443: /* stmt: GTU2(CVIU2(reg8),con) */
	case 442: /* stmt: GTU2(CVUU2(reg8),con) */
	case 436: /* stmt: GTI2(CVUI2(reg8),con) */
	case 435: /* stmt: GTI2(CVII2(reg8),con) */
	case 421: /* stmt: GEU2(CVIU2(reg8),con) */
	case 420: /* stmt: GEU2(CVUU2(reg8),con) */
	case 414: /* stmt: GEI2(CVUI2(reg8),con) */
	case 413: /* stmt: GEI2(CVII2(reg8),con) */
	case 399: /* stmt: LTU2(CVIU2(reg8),con) */
	case 398: /* stmt: LTU2(CVUU2(reg8),con) */
	case 392: /* stmt: LTI2(CVUI2(reg8),con) */
	case 391: /* stmt: LTI2(CVII2(reg8),con) */
	case 377: /* stmt: LEU2(CVIU2(reg8),con) */
	case 376: /* stmt: LEU2(CVUU2(reg8),con) */
	case 370: /* stmt: LEI2(CVUI2(reg8),con) */
	case 369: /* stmt: LEI2(CVII2(reg8),con) */
	case 355: /* stmt: NEU2(CVIU2(reg8),con) */
	case 354: /* stmt: NEU2(CVUU2(reg8),con) */
	case 348: /* stmt: NEI2(CVUI2(reg8),con) */
	case 347: /* stmt: NEI2(CVII2(reg8),con) */
	case 333: /* stmt: EQU2(CVIU2(reg8),con) */
	case 332: /* stmt: EQU2(CVUU2(reg8),con) */
	case 326: /* stmt: EQI2(CVUI2(reg8),con) */
	case 325: /* stmt: EQI2(CVII2(reg8),con) */
	case 273: /* reg8: BXORU2(CVIU2(reg8),con) */
	case 272: /* reg8: BXORU2(CVUU2(reg8),con) */
	case 267: /* reg8: BXORI2(CVUI2(reg8),con) */
	case 266: /* reg8: BXORI2(CVII2(reg8),con) */
	case 251: /* reg8: BORU2(CVIU2(reg8),con) */
	case 250: /* reg8: BORU2(CVUU2(reg8),con) */
	case 245: /* reg8: BORI2(CVUI2(reg8),con) */
	case 244: /* reg8: BORI2(CVII2(reg8),con) */
	case 225: /* reg8: BANDU2(CVIU2(reg8),con) */
	case 224: /* reg8: BANDU2(CVUU2(reg8),con) */
	case 219: /* reg8: BANDI2(CVUI2(reg8),con) */
	case 218: /* reg8: BANDI2(CVII2(reg8),con) */
	case 183: /* reg8: SUBU2(CVIU2(reg8),con) */
	case 182: /* reg8: SUBU2(CVUU2(reg8),con) */
	case 177: /* reg8: SUBI2(CVUI2(reg8),con) */
	case 176: /* reg8: SUBI2(CVII2(reg8),con) */
	case 147: /* reg8: ADDU2(CVIU2(reg8),con) */
	case 146: /* reg8: ADDU2(CVUU2(reg8),con) */
	case 141: /* reg8: ADDI2(CVUI2(reg8),con) */
	case 140: /* reg8: ADDI2(CVII2(reg8),con) */
		kids[0] = LEFT_CHILD(LEFT_CHILD(p));
		kids[1] = RIGHT_CHILD(p);
		break;
	case 199: /* stmt: ASGNF8(lgaddr,SUBF8(INDIRF8(lgaddr),INDIRF8(lgaddr))) */
	case 198: /* stmt: ASGNF8(lgaddr,SUBF8(INDIRF8(lgaddr),INDIRF8(lgaddr))) */
	case 197: /* stmt: ASGNF4(lgaddr,SUBF4(INDIRF4(lgaddr),INDIRF4(lgaddr))) */
	case 196: /* stmt: ASGNF4(lgaddr,SUBF4(INDIRF4(lgaddr),INDIRF4(lgaddr))) */
	case 195: /* stmt: ASGNU4(lgaddr,SUBU4(INDIRU4(lgaddr),INDIRU4(lgaddr))) */
	case 194: /* stmt: ASGNU4(lgaddr,SUBU4(INDIRU4(lgaddr),INDIRU4(lgaddr))) */
	case 193: /* stmt: ASGNI4(lgaddr,SUBI4(INDIRI4(lgaddr),INDIRI4(lgaddr))) */
	case 192: /* stmt: ASGNI4(lgaddr,SUBI4(INDIRI4(lgaddr),INDIRI4(lgaddr))) */
	case 163: /* stmt: ASGNF8(lgaddr,ADDF8(INDIRF8(lgaddr),INDIRF8(lgaddr))) */
	case 162: /* stmt: ASGNF8(lgaddr,ADDF8(INDIRF8(lgaddr),INDIRF8(lgaddr))) */
	case 161: /* stmt: ASGNF4(lgaddr,ADDF4(INDIRF4(lgaddr),INDIRF4(lgaddr))) */
	case 160: /* stmt: ASGNF4(lgaddr,ADDF4(INDIRF4(lgaddr),INDIRF4(lgaddr))) */
	case 159: /* stmt: ASGNU4(lgaddr,ADDU4(INDIRU4(lgaddr),INDIRU4(lgaddr))) */
	case 158: /* stmt: ASGNU4(lgaddr,ADDU4(INDIRU4(lgaddr),INDIRU4(lgaddr))) */
	case 157: /* stmt: ASGNI4(lgaddr,ADDI4(INDIRI4(lgaddr),INDIRI4(lgaddr))) */
	case 156: /* stmt: ASGNI4(lgaddr,ADDI4(INDIRI4(lgaddr),INDIRI4(lgaddr))) */
		kids[0] = LEFT_CHILD(p);
		kids[1] = LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(p)));
		kids[2] = LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(p)));
		break;
	case 207: /* regf: NEGF8(INDIRF8(lgaddr)) */
	case 205: /* regf: NEGF4(INDIRF4(lgaddr)) */
	case 203: /* reg32: NEGI4(INDIRI4(lgaddr)) */
	case 201: /* reg: NEGI2(INDIRI2(lgaddr)) */
		kids[0] = LEFT_CHILD(LEFT_CHILD(p));
		break;
	default:
		fatal("_kids", "Bad rule number %d\n", eruleno);
	}
}


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

    charreg[R_AH]->x.regnode->mask |= 1<<R_A;
    charreg[R_AL]->x.regnode->mask |= 1<<R_A;      
	
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
    tmask[IREG] = 1<<R_A | 1<<R_X | 1<<R_Y | 1<<R_L0 | 1<<R_L1 | 1<<R_L2 | 1<<R_L3 | 1<<R_AL | 1<<R_AH;
    // Set up registers for variables
    vmask[IREG] = 0;

    tmask[FREG] = ~(unsigned)0; // this is OK as we use all 32 slots
    vmask[FREG] = 0;
    
    print(";    BYTEC/16 assembly, generated by lcc 4.2\n\n");

    cseg = 0;

    ever_used_muldiv16 = 0;

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
    if (ever_used_muldiv16) {
        print("\t.extern\t__mulu16\n");
        print("\t.extern\t__divu16\n");
        print("\t.extern\t__modu16\n");
        print("\t.extern\t__muli16\n");
        print("\t.extern\t__divi16\n");
        print("\t.extern\t__modi16\n");
    }
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
        case BCOM+I:
        case BCOM+U:
			if (opsize(p->op)==2) {
				rtarget(p,0,intreg[R_A]);
				setreg(p,intreg[R_A]);
			}
            break;      

        case MUL+I:
        case MUL+U:
        case DIV+I:
        case DIV+U:
        case MOD+I:
        case MOD+U:        
            if (opsize(p->op)==2) {
				rtarget(p,0,intreg[R_A]);
				rtarget(p,1,intreg[R_X]);
				setreg(p,intreg[R_A]);
                ever_used_muldiv16 = 1;
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
			if (opsize(p->op)==2) {
				rtarget(p,0,intreg[R_A]);
			}
        break;

		case ASGN+B:
			// ASGNB(addr,INDIRB(addr))
			rtarget(p,0,intreg[R_X]);
			rtarget(p->kids[1],0,intreg[R_Y]);
		break;

        case LOAD+I:
        case LOAD+U:
            if (opsize(p->op)==1 && opsize(p->kids[0]->op)==2) {
                setreg(p,charreg[R_AL]);
            }
        break;

		case ASGN+I:
		case ASGN+U:	
		case INDIR+I:
		case INDIR+U:
			if (opsize(p->op)==1) {
		        // prevent A and AL/AH conflict when address in A
                rtarget(p,0,intreg[R_X]);
                switch (specific(p->kids[0]->op)) {
                    case ADD+P:
                    case SUB+P:
    			        rtarget(p->kids[0],0,intreg[R_X]);
                    break;
                } 
			}
			else 
                if (opsize(p->op)>2) {
				// this is to target INDIRx4(reg) to A
				rtarget(p,0,intreg[R_A]);
			}
		break;
		
        case JUMP+V:
			rtarget(p,0,intreg[R_A]);
        break;

		case CALL+I:
		case CALL+U:
		case CALL+P:
		case CALL+V:
		case CALL+F:		
			setreg(p,intreg[R_A]);		
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
        case DIV+I:
        case MOD+I:
        case MUL+U:
        case DIV+U:
        case MOD+U:
            if (opsize(p->op)==2) {
		        spill(1<<R_X|1<<R_Y,IREG,p);
            }
        break;

        case SUB+U:
        case ADD+U:
        case SUB+I:
        case ADD+I:
            if (opsize(p->op)==4) {
                spill(1<<R_A|1<<R_Y,IREG,p);
            }
        break;
        
        case LSH+U:
        case RSH+U:
        case LSH+I:
        case RSH+I:
            if (opsize(p->op)==4) {
                spill(1<<R_A|1<<R_Y,IREG,p);
            }
        break;

		case CALL+I:
		case CALL+U:
		case CALL+P:
		case CALL+V:				
		case CALL+F:
			if (opsize(p->op)==8) {
				// spill A and Y (will be destroyed in 64-bit routine), spill X (holds pointer to 64-bit temp for return value)
				spill(1<<R_X|1<<R_Y|1<<R_A,IREG,p);
			}
			else if (opsize(p->op)==4) {
				// spill X and Y (will hold 32-bit return value), spill A (will be destroyed in 32-bit routine)
				spill(1<<R_X|1<<R_Y|1<<R_A,IREG,p);
			}
			else if (opsize(p->op)<=2) {
				// spill X and Y (will be destroyed in a called routine) (A is targeted for RET so no need to spill)
				spill(1<<R_X|1<<R_Y,IREG,p);
			}					
		break;

        case LOAD+I:
        case LOAD+U:
            if (opsize(p->op)==4) {
                spill(1<<R_A,IREG,p);
            }
        break;

        case INDIR+I:
        case INDIR+U:
            if (opsize(p->op)==4) {
                spill(1<<R_A,IREG,p);
            }
        break;

        case ARG+I:
        case ARG+U:
            if (opsize(p->op)==4) {
                spill(1<<R_A,IREG,p);
            }
        break;

        case CVU+I:
        case CVU+U:
        case CVI+I:
        case CVI+U:
            if (opsize(p->op)==4) {
                spill(1<<R_A,IREG,p);
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
    int lbl1, lbl2;
    
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

        case LSH+I:
        case LSH+U:
        case RSH+I:
        case RSH+U:
            lbl1 = genlabel(1);
            lbl2 = genlabel(2);
            drnum = getregnum(p->kids[0]);
            srnum = getregnum(p->kids[1]);
            print("\tpush\t%s\n", intreg[srnum]->x.name);
            print("L%d:\n", lbl1);
            print("\tsub\t%s,1\n", intreg[srnum]->x.name);
            print("\tjn\tL%d\n", lbl2);
            if (generic(p->op)==LSH) {
                print("\tshl\t");
            }
            else {
                print("\tshr\t");
            }
            print("%s\n", intreg[drnum]->x.name);
            print("\tjmp\tL%d\n", lbl1);
            print("L%d:\n", lbl2);
            print("\tpop\t%s\n", intreg[srnum]->x.name);
        break;

		case LOAD+I:
		case LOAD+U:
			if (opsize(p->op)==1) {
				if (opsize(p->kids[0]->op)==2) {
					drnum = getregnum(p->kids[0]);
					// prune movl al,a
					if (drnum!=R_A) {
						// safe to assume target is in al beacause we target so
						print("\tmovl\tal,%s\t;emit2\n",intreg[drnum]->x.name);
					}
				}
				else if (opsize(p->kids[0]->op)==4) {
					drnum = getregnum(p);
					char *s = p->kids[0]->syms[2]->x.name;
					print("\tld\t%s,%s+3)\t;emit2\n",charreg[drnum]->x.name, stringn(s,strlen(s)-1));					
                }
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
				print("\tld\ta,(%s)\n\tst\t(sp:%d),a\n\tld\ta,(%s+2)\n\tst\t(sp:%d+2),a\n", p->kids[0]->syms[2]->x.name, p->syms[2]->u.c.v.i, p->kids[0]->syms[2]->x.name, p->syms[2]->u.c.v.i); 
			}
			else if (opsize(p->op)==8) {
				print("\tCOPY32(sp:%d,%s)\n",p->syms[2]->u.c.v.i,p->kids[0]->syms[2]->x.name); 
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
				print("\tld\tx,(sp:%d+%d)\n",ptr64,framesize);
				print("\tCOPY64((x:0),%s)\n",floatreg[0]->x.name);
			}
		break;

		case ASGN+B: {
			// ASGNB(addr,INDIRB(addr))
			static int tmpregs[] = {R_A};
			dalign = salign = p->syms[1]->u.c.v.i;
            blkcopy(getregnum(p->kids[0]), 0,
                    getregnum(p->kids[1]->kids[0]), 0,
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
	        longreg[i]->x.name = stringf("sp:%d",longreg[i]->x.offset+framesize);
			printf("; L%d -> sp:%d\n",i,longreg[i]->x.offset+framesize);
	    }
        }
    }
    if (used_floats) {
        for (i=0;i<32;i++) {
	    if (usedmask[1] & (1<<i)) {
	        floatreg[i]->x.name = stringf("sp:%d",floatreg[i]->x.offset+framesize);
			printf("; F%d -> sp:%d\n",i,floatreg[i]->x.offset+framesize);
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

/* address function currently not used, see interface record */
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
                print("\t.db\t0x%x\n", v.i&0xff);
        else if (suffix == I && size == 2) {
                sprintf(s0,"%04x",v.i&0xffff);
                print("\t.dw\t0x%s\n", s0);
        }
        else if (suffix == I && size == 4) {
                sprintf(s0,"%04x",(v.i>>16)&0xffff);
                sprintf(s1,"%04x",v.i&0xffff);          
                print("\t.dw\t0x%s,0x%s\n", s0, s1);
        }
        else if (suffix == U && size == 1)
                print("\t.db\t0x%x\n", v.u&0xff);
        else if (suffix == U && size == 2) {
				sprintf(s0,"%04x",v.u&0xffff);  
                print("\t.dw\t0x%s\n", s0);
        }
        else if (suffix == U && size == 4) {
                sprintf(s0,"%04x",(v.u>>16)&0xffff);
                sprintf(s1,"%04x",v.u&0xffff);          
                print("\t.dw\t0x%s,0x%s\n", s0, s1);
        }
        else if (suffix == P && size == 2) {
                sprintf(s0,"%04x",(v.u)&0xffff);
                print("\t.dw\t0x%s\n", s0);
        }
        else if (suffix == F && size == 4) {
				float d = (float)v.d;
                unsigned short *f = (unsigned short *)&d;
                sprintf(s0,"%04x",f[0]);
                sprintf(s1,"%04x",f[1]);                
                print("\t.dw\t0x%s,0x%s\n", s1, s0);
        }
        else if (suffix == F && size == 8) {
                unsigned long *f = (unsigned long *)&v.d;
                sprintf(s0,"%04x",f[0]);
                sprintf(s1,"%04x",f[1]);
                sprintf(s2,"%04x",f[2]);
                sprintf(s3,"%04x",f[3]);
                print("\t.dw\t0x%s,0x%s,0x%s,0x%s\n", s3, s2, s1, s0);
        }
        else assert(0);
}

static void defaddress(Symbol p) {
	print("\t.dw\t%s\n", p->x.name);
}

static void defstring(int n, char *str) {
	char *s;
	char s0[3];
	for (s = str; s < str + n; s++) {
        sprintf(s0,"%02x",((*s)&0377) & 0xff);
		print("\t.db\t0x%s\n", s0);
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
	print("\t.db\t0x00:%d\n", n);
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
        NULL,
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
