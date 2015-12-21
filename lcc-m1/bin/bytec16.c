
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

/*
generated at Sun Jan 27 12:22:53 2013
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
#define _con_NT 10
#define _lgaddr_NT 11
#define _addr_NT 12
#define _albl_NT 13

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
	"con",
	"lgaddr",
	"addr",
	"albl",
	0
};

struct _state {
	short cost[14];
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
		unsigned int _con:2;
		unsigned int _lgaddr:2;
		unsigned int _addr:3;
		unsigned int _albl:1;
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
static short _nts_11[] = { _addr_NT, _reg8_NT, 0 };
static short _nts_12[] = { _addr_NT, _reg_NT, 0 };
static short _nts_13[] = { _reg_NT, _reg_NT, 0 };
static short _nts_14[] = { _addr_NT, _reg32_NT, 0 };
static short _nts_15[] = { _addr_NT, _addr_NT, 0 };
static short _nts_16[] = { _addr_NT, _regf_NT, 0 };
static short _nts_17[] = { _addr_NT, 0 };
static short _nts_18[] = { _reg_NT, _addr_NT, 0 };
static short _nts_19[] = { _reg_NT, _con1_NT, 0 };
static short _nts_20[] = { _reg8_NT, _addr_NT, 0 };
static short _nts_21[] = { _reg8_NT, _con_NT, 0 };
static short _nts_22[] = { _reg32_NT, _reg32_NT, 0 };
static short _nts_23[] = { _reg32_NT, _addr_NT, 0 };
static short _nts_24[] = { _regf_NT, _regf_NT, 0 };
static short _nts_25[] = { _regf_NT, _addr_NT, 0 };
static short _nts_26[] = { _addr_NT, _addr_NT, _addr_NT, 0 };
static short _nts_27[] = { _reg_NT, _lgaddr_NT, 0 };
static short _nts_28[] = { _reg8_NT, _lgaddr_NT, 0 };
static short _nts_29[] = { _reg32_NT, _con1_NT, 0 };
static short _nts_30[] = { _albl_NT, 0 };

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
	_nts_2,	/* 19 */
	_nts_1,	/* 20 */
	_nts_2,	/* 21 */
	_nts_1,	/* 22 */
	_nts_2,	/* 23 */
	_nts_2,	/* 24 */
	_nts_2,	/* 25 */
	_nts_3,	/* 26 */
	_nts_3,	/* 27 */
	_nts_2,	/* 28 */
	_nts_4,	/* 29 */
	_nts_4,	/* 30 */
	_nts_1,	/* 31 */
	_nts_1,	/* 32 */
	_nts_0,	/* 33 */
	_nts_0,	/* 34 */
	_nts_0,	/* 35 */
	_nts_0,	/* 36 */
	_nts_0,	/* 37 */
	_nts_0,	/* 38 */
	_nts_0,	/* 39 */
	_nts_0,	/* 40 */
	_nts_0,	/* 41 */
	_nts_0,	/* 42 */
	_nts_0,	/* 43 */
	_nts_0,	/* 44 */
	_nts_0,	/* 45 */
	_nts_5,	/* 46 */
	_nts_6,	/* 47 */
	_nts_7,	/* 48 */
	_nts_8,	/* 49 */
	_nts_5,	/* 50 */
	_nts_0,	/* 51 */
	_nts_0,	/* 52 */
	_nts_0,	/* 53 */
	_nts_9,	/* 54 */
	_nts_0,	/* 55 */
	_nts_2,	/* 56 */
	_nts_10,	/* 57 */
	_nts_10,	/* 58 */
	_nts_10,	/* 59 */
	_nts_10,	/* 60 */
	_nts_9,	/* 61 */
	_nts_11,	/* 62 */
	_nts_11,	/* 63 */
	_nts_12,	/* 64 */
	_nts_12,	/* 65 */
	_nts_12,	/* 66 */
	_nts_13,	/* 67 */
	_nts_14,	/* 68 */
	_nts_15,	/* 69 */
	_nts_14,	/* 70 */
	_nts_15,	/* 71 */
	_nts_16,	/* 72 */
	_nts_15,	/* 73 */
	_nts_16,	/* 74 */
	_nts_15,	/* 75 */
	_nts_17,	/* 76 */
	_nts_17,	/* 77 */
	_nts_17,	/* 78 */
	_nts_17,	/* 79 */
	_nts_17,	/* 80 */
	_nts_17,	/* 81 */
	_nts_17,	/* 82 */
	_nts_17,	/* 83 */
	_nts_17,	/* 84 */
	_nts_2,	/* 85 */
	_nts_2,	/* 86 */
	_nts_2,	/* 87 */
	_nts_2,	/* 88 */
	_nts_3,	/* 89 */
	_nts_3,	/* 90 */
	_nts_3,	/* 91 */
	_nts_3,	/* 92 */
	_nts_1,	/* 93 */
	_nts_1,	/* 94 */
	_nts_1,	/* 95 */
	_nts_1,	/* 96 */
	_nts_3,	/* 97 */
	_nts_3,	/* 98 */
	_nts_3,	/* 99 */
	_nts_3,	/* 100 */
	_nts_1,	/* 101 */
	_nts_1,	/* 102 */
	_nts_1,	/* 103 */
	_nts_1,	/* 104 */
	_nts_2,	/* 105 */
	_nts_2,	/* 106 */
	_nts_2,	/* 107 */
	_nts_2,	/* 108 */
	_nts_1,	/* 109 */
	_nts_2,	/* 110 */
	_nts_3,	/* 111 */
	_nts_1,	/* 112 */
	_nts_2,	/* 113 */
	_nts_3,	/* 114 */
	_nts_4,	/* 115 */
	_nts_4,	/* 116 */
	_nts_4,	/* 117 */
	_nts_4,	/* 118 */
	_nts_2,	/* 119 */
	_nts_2,	/* 120 */
	_nts_13,	/* 121 */
	_nts_18,	/* 122 */
	_nts_10,	/* 123 */
	_nts_19,	/* 124 */
	_nts_13,	/* 125 */
	_nts_18,	/* 126 */
	_nts_10,	/* 127 */
	_nts_19,	/* 128 */
	_nts_13,	/* 129 */
	_nts_10,	/* 130 */
	_nts_20,	/* 131 */
	_nts_20,	/* 132 */
	_nts_20,	/* 133 */
	_nts_21,	/* 134 */
	_nts_21,	/* 135 */
	_nts_21,	/* 136 */
	_nts_20,	/* 137 */
	_nts_20,	/* 138 */
	_nts_20,	/* 139 */
	_nts_21,	/* 140 */
	_nts_21,	/* 141 */
	_nts_21,	/* 142 */
	_nts_22,	/* 143 */
	_nts_23,	/* 144 */
	_nts_22,	/* 145 */
	_nts_23,	/* 146 */
	_nts_24,	/* 147 */
	_nts_25,	/* 148 */
	_nts_24,	/* 149 */
	_nts_25,	/* 150 */
	_nts_26,	/* 151 */
	_nts_26,	/* 152 */
	_nts_26,	/* 153 */
	_nts_26,	/* 154 */
	_nts_26,	/* 155 */
	_nts_26,	/* 156 */
	_nts_13,	/* 157 */
	_nts_18,	/* 158 */
	_nts_10,	/* 159 */
	_nts_19,	/* 160 */
	_nts_13,	/* 161 */
	_nts_18,	/* 162 */
	_nts_10,	/* 163 */
	_nts_19,	/* 164 */
	_nts_13,	/* 165 */
	_nts_10,	/* 166 */
	_nts_20,	/* 167 */
	_nts_20,	/* 168 */
	_nts_20,	/* 169 */
	_nts_21,	/* 170 */
	_nts_21,	/* 171 */
	_nts_21,	/* 172 */
	_nts_20,	/* 173 */
	_nts_20,	/* 174 */
	_nts_20,	/* 175 */
	_nts_21,	/* 176 */
	_nts_21,	/* 177 */
	_nts_21,	/* 178 */
	_nts_22,	/* 179 */
	_nts_23,	/* 180 */
	_nts_22,	/* 181 */
	_nts_23,	/* 182 */
	_nts_24,	/* 183 */
	_nts_25,	/* 184 */
	_nts_24,	/* 185 */
	_nts_25,	/* 186 */
	_nts_26,	/* 187 */
	_nts_26,	/* 188 */
	_nts_26,	/* 189 */
	_nts_26,	/* 190 */
	_nts_26,	/* 191 */
	_nts_26,	/* 192 */
	_nts_2,	/* 193 */
	_nts_17,	/* 194 */
	_nts_3,	/* 195 */
	_nts_17,	/* 196 */
	_nts_4,	/* 197 */
	_nts_17,	/* 198 */
	_nts_4,	/* 199 */
	_nts_17,	/* 200 */
	_nts_13,	/* 201 */
	_nts_27,	/* 202 */
	_nts_10,	/* 203 */
	_nts_13,	/* 204 */
	_nts_27,	/* 205 */
	_nts_10,	/* 206 */
	_nts_28,	/* 207 */
	_nts_28,	/* 208 */
	_nts_28,	/* 209 */
	_nts_21,	/* 210 */
	_nts_21,	/* 211 */
	_nts_21,	/* 212 */
	_nts_28,	/* 213 */
	_nts_28,	/* 214 */
	_nts_28,	/* 215 */
	_nts_21,	/* 216 */
	_nts_21,	/* 217 */
	_nts_21,	/* 218 */
	_nts_22,	/* 219 */
	_nts_23,	/* 220 */
	_nts_22,	/* 221 */
	_nts_23,	/* 222 */
	_nts_2,	/* 223 */
	_nts_2,	/* 224 */
	_nts_3,	/* 225 */
	_nts_3,	/* 226 */
	_nts_13,	/* 227 */
	_nts_27,	/* 228 */
	_nts_10,	/* 229 */
	_nts_13,	/* 230 */
	_nts_27,	/* 231 */
	_nts_10,	/* 232 */
	_nts_28,	/* 233 */
	_nts_28,	/* 234 */
	_nts_28,	/* 235 */
	_nts_21,	/* 236 */
	_nts_21,	/* 237 */
	_nts_21,	/* 238 */
	_nts_28,	/* 239 */
	_nts_28,	/* 240 */
	_nts_28,	/* 241 */
	_nts_21,	/* 242 */
	_nts_21,	/* 243 */
	_nts_21,	/* 244 */
	_nts_22,	/* 245 */
	_nts_23,	/* 246 */
	_nts_22,	/* 247 */
	_nts_23,	/* 248 */
	_nts_13,	/* 249 */
	_nts_27,	/* 250 */
	_nts_10,	/* 251 */
	_nts_13,	/* 252 */
	_nts_27,	/* 253 */
	_nts_10,	/* 254 */
	_nts_28,	/* 255 */
	_nts_28,	/* 256 */
	_nts_28,	/* 257 */
	_nts_21,	/* 258 */
	_nts_21,	/* 259 */
	_nts_21,	/* 260 */
	_nts_28,	/* 261 */
	_nts_28,	/* 262 */
	_nts_28,	/* 263 */
	_nts_21,	/* 264 */
	_nts_21,	/* 265 */
	_nts_21,	/* 266 */
	_nts_22,	/* 267 */
	_nts_23,	/* 268 */
	_nts_22,	/* 269 */
	_nts_23,	/* 270 */
	_nts_13,	/* 271 */
	_nts_13,	/* 272 */
	_nts_13,	/* 273 */
	_nts_13,	/* 274 */
	_nts_13,	/* 275 */
	_nts_13,	/* 276 */
	_nts_22,	/* 277 */
	_nts_23,	/* 278 */
	_nts_22,	/* 279 */
	_nts_23,	/* 280 */
	_nts_22,	/* 281 */
	_nts_23,	/* 282 */
	_nts_22,	/* 283 */
	_nts_23,	/* 284 */
	_nts_22,	/* 285 */
	_nts_23,	/* 286 */
	_nts_22,	/* 287 */
	_nts_23,	/* 288 */
	_nts_24,	/* 289 */
	_nts_25,	/* 290 */
	_nts_24,	/* 291 */
	_nts_25,	/* 292 */
	_nts_24,	/* 293 */
	_nts_25,	/* 294 */
	_nts_24,	/* 295 */
	_nts_25,	/* 296 */
	_nts_19,	/* 297 */
	_nts_19,	/* 298 */
	_nts_19,	/* 299 */
	_nts_19,	/* 300 */
	_nts_21,	/* 301 */
	_nts_21,	/* 302 */
	_nts_21,	/* 303 */
	_nts_21,	/* 304 */
	_nts_21,	/* 305 */
	_nts_21,	/* 306 */
	_nts_21,	/* 307 */
	_nts_21,	/* 308 */
	_nts_21,	/* 309 */
	_nts_21,	/* 310 */
	_nts_21,	/* 311 */
	_nts_21,	/* 312 */
	_nts_29,	/* 313 */
	_nts_29,	/* 314 */
	_nts_13,	/* 315 */
	_nts_27,	/* 316 */
	_nts_10,	/* 317 */
	_nts_28,	/* 318 */
	_nts_28,	/* 319 */
	_nts_21,	/* 320 */
	_nts_21,	/* 321 */
	_nts_13,	/* 322 */
	_nts_27,	/* 323 */
	_nts_10,	/* 324 */
	_nts_28,	/* 325 */
	_nts_28,	/* 326 */
	_nts_21,	/* 327 */
	_nts_21,	/* 328 */
	_nts_22,	/* 329 */
	_nts_23,	/* 330 */
	_nts_22,	/* 331 */
	_nts_23,	/* 332 */
	_nts_24,	/* 333 */
	_nts_25,	/* 334 */
	_nts_24,	/* 335 */
	_nts_25,	/* 336 */
	_nts_13,	/* 337 */
	_nts_13,	/* 338 */
	_nts_10,	/* 339 */
	_nts_28,	/* 340 */
	_nts_28,	/* 341 */
	_nts_21,	/* 342 */
	_nts_21,	/* 343 */
	_nts_13,	/* 344 */
	_nts_13,	/* 345 */
	_nts_10,	/* 346 */
	_nts_28,	/* 347 */
	_nts_28,	/* 348 */
	_nts_21,	/* 349 */
	_nts_21,	/* 350 */
	_nts_22,	/* 351 */
	_nts_23,	/* 352 */
	_nts_22,	/* 353 */
	_nts_23,	/* 354 */
	_nts_24,	/* 355 */
	_nts_25,	/* 356 */
	_nts_24,	/* 357 */
	_nts_25,	/* 358 */
	_nts_13,	/* 359 */
	_nts_13,	/* 360 */
	_nts_10,	/* 361 */
	_nts_28,	/* 362 */
	_nts_28,	/* 363 */
	_nts_21,	/* 364 */
	_nts_21,	/* 365 */
	_nts_13,	/* 366 */
	_nts_13,	/* 367 */
	_nts_10,	/* 368 */
	_nts_28,	/* 369 */
	_nts_28,	/* 370 */
	_nts_21,	/* 371 */
	_nts_21,	/* 372 */
	_nts_22,	/* 373 */
	_nts_23,	/* 374 */
	_nts_22,	/* 375 */
	_nts_23,	/* 376 */
	_nts_24,	/* 377 */
	_nts_25,	/* 378 */
	_nts_24,	/* 379 */
	_nts_25,	/* 380 */
	_nts_13,	/* 381 */
	_nts_13,	/* 382 */
	_nts_10,	/* 383 */
	_nts_28,	/* 384 */
	_nts_28,	/* 385 */
	_nts_21,	/* 386 */
	_nts_21,	/* 387 */
	_nts_13,	/* 388 */
	_nts_13,	/* 389 */
	_nts_10,	/* 390 */
	_nts_28,	/* 391 */
	_nts_28,	/* 392 */
	_nts_21,	/* 393 */
	_nts_21,	/* 394 */
	_nts_22,	/* 395 */
	_nts_23,	/* 396 */
	_nts_22,	/* 397 */
	_nts_23,	/* 398 */
	_nts_24,	/* 399 */
	_nts_25,	/* 400 */
	_nts_24,	/* 401 */
	_nts_25,	/* 402 */
	_nts_13,	/* 403 */
	_nts_13,	/* 404 */
	_nts_10,	/* 405 */
	_nts_28,	/* 406 */
	_nts_28,	/* 407 */
	_nts_21,	/* 408 */
	_nts_21,	/* 409 */
	_nts_13,	/* 410 */
	_nts_13,	/* 411 */
	_nts_10,	/* 412 */
	_nts_28,	/* 413 */
	_nts_28,	/* 414 */
	_nts_21,	/* 415 */
	_nts_21,	/* 416 */
	_nts_22,	/* 417 */
	_nts_23,	/* 418 */
	_nts_22,	/* 419 */
	_nts_23,	/* 420 */
	_nts_24,	/* 421 */
	_nts_25,	/* 422 */
	_nts_24,	/* 423 */
	_nts_25,	/* 424 */
	_nts_13,	/* 425 */
	_nts_13,	/* 426 */
	_nts_10,	/* 427 */
	_nts_28,	/* 428 */
	_nts_28,	/* 429 */
	_nts_21,	/* 430 */
	_nts_21,	/* 431 */
	_nts_13,	/* 432 */
	_nts_13,	/* 433 */
	_nts_10,	/* 434 */
	_nts_28,	/* 435 */
	_nts_28,	/* 436 */
	_nts_21,	/* 437 */
	_nts_21,	/* 438 */
	_nts_22,	/* 439 */
	_nts_23,	/* 440 */
	_nts_22,	/* 441 */
	_nts_23,	/* 442 */
	_nts_24,	/* 443 */
	_nts_25,	/* 444 */
	_nts_24,	/* 445 */
	_nts_25,	/* 446 */
	_nts_2,	/* 447 */
	_nts_2,	/* 448 */
	_nts_2,	/* 449 */
	_nts_3,	/* 450 */
	_nts_3,	/* 451 */
	_nts_4,	/* 452 */
	_nts_4,	/* 453 */
	_nts_30,	/* 454 */
	_nts_30,	/* 455 */
	_nts_30,	/* 456 */
	_nts_30,	/* 457 */
	_nts_30,	/* 458 */
	_nts_30,	/* 459 */
	_nts_30,	/* 460 */
	_nts_30,	/* 461 */
	_nts_2,	/* 462 */
	_nts_2,	/* 463 */
	_nts_2,	/* 464 */
	_nts_0,	/* 465 */
	_nts_3,	/* 466 */
	_nts_3,	/* 467 */
	_nts_4,	/* 468 */
	_nts_4,	/* 469 */
	_nts_30,	/* 470 */
	_nts_0,	/* 471 */
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
/* 19 */	"",	/* stmt: reg */
/* 20 */	"\tpush\t%0\n\tpop\t%c\n",	/* reg8: LOADI1(reg8) */
/* 21 */	"# emit2\n",	/* reg8: LOADI1(reg) */
/* 22 */	"\tpush\t%0\n\tpop\t%c\n",	/* reg8: LOADU1(reg8) */
/* 23 */	"# emit2\n",	/* reg8: LOADU1(reg) */
/* 24 */	"\tmov\t%c,%0\n",	/* reg: LOADI2(reg) */
/* 25 */	"\tmov\t%c,%0\n",	/* reg: LOADU2(reg) */
/* 26 */	"\tCOPY32\t(%c,%0)\n",	/* reg32: LOADI4(reg32) */
/* 27 */	"\tCOPY32\t(%c,%0)\n",	/* reg32: LOADU4(reg32) */
/* 28 */	"\tmov\t%c,%0\n",	/* reg: LOADP2(reg) */
/* 29 */	"\tCOPY32\t(%c,%0)\n",	/* regf: LOADF4(regf) */
/* 30 */	"\tCOPY64\t(%c,%0)\n",	/* regf: LOADF8(regf) */
/* 31 */	"%0",	/* reg8: LOADU1(LOADU2(CVII2(reg8))) */
/* 32 */	"%0",	/* reg8: LOADI1(LOADI2(CVUU2(reg8))) */
/* 33 */	"%a",	/* con8: CNSTI1 */
/* 34 */	"%a",	/* con8: CNSTU1 */
/* 35 */	"%a",	/* con16: CNSTI2 */
/* 36 */	"%a",	/* con16: CNSTU2 */
/* 37 */	"%a",	/* con16: CNSTP2 */
/* 38 */	"%a",	/* con0: CNSTI1 */
/* 39 */	"%a",	/* con0: CNSTU1 */
/* 40 */	"%a",	/* con0: CNSTI2 */
/* 41 */	"%a",	/* con0: CNSTU2 */
/* 42 */	"%a",	/* con1: CNSTI1 */
/* 43 */	"%a",	/* con1: CNSTU1 */
/* 44 */	"%a",	/* con1: CNSTI2 */
/* 45 */	"%a",	/* con1: CNSTU2 */
/* 46 */	"%a",	/* con: con8 */
/* 47 */	"%a",	/* con: con16 */
/* 48 */	"\tld\t%c,%0\n",	/* reg: con */
/* 49 */	"\txor\t%c,%c\n",	/* reg: con0 */
/* 50 */	"\tld\t%c,%0\n",	/* reg8: con8 */
/* 51 */	"(dp:%a)",	/* lgaddr: ADDRGP2 */
/* 52 */	"(sp:%a+2+%F)",	/* lgaddr: ADDRFP2 */
/* 53 */	"(sp:%a+%F)",	/* lgaddr: ADDRLP2 */
/* 54 */	"%0",	/* addr: lgaddr */
/* 55 */	"%a",	/* albl: ADDRGP2 */
/* 56 */	"(%0:0)",	/* addr: reg */
/* 57 */	"(%0:%1)",	/* addr: ADDP2(reg,con) */
/* 58 */	"(%0:-%1)",	/* addr: SUBP2(reg,con) */
/* 59 */	"?\tmov\t%c,%0\n\tadd\t%c,%1\n",	/* reg: ADDP2(reg,con) */
/* 60 */	"?\tmov\t%c,%0\n\tsub\t%c,%1\n",	/* reg: SUBP2(reg,con) */
/* 61 */	"\tlea\t%c,%0\n",	/* reg: lgaddr */
/* 62 */	"\tst\t%0,%1\n",	/* stmt: ASGNI1(addr,reg8) */
/* 63 */	"\tst\t%0,%1\n",	/* stmt: ASGNU1(addr,reg8) */
/* 64 */	"\tst\t%0,%1\n",	/* stmt: ASGNI2(addr,reg) */
/* 65 */	"\tst\t%0,%1\n",	/* stmt: ASGNU2(addr,reg) */
/* 66 */	"\tst\t%0,%1\n",	/* stmt: ASGNP2(addr,reg) */
/* 67 */	"# emit2\n",	/* stmt: ASGNB(reg,INDIRB(reg)) */
/* 68 */	"\tCOPY32\t(%0,%1)\n",	/* stmt: ASGNI4(addr,reg32) */
/* 69 */	"\tCOPY32\t(%0,%1)\n",	/* stmt: ASGNI4(addr,INDIRI4(addr)) */
/* 70 */	"\tCOPY32\t(%0,%1)\n",	/* stmt: ASGNU4(addr,reg32) */
/* 71 */	"\tCOPY32\t(%0,%1)\n",	/* stmt: ASGNU4(addr,INDIRU4(addr)) */
/* 72 */	"\tCOPY32\t(%0,%1)\n",	/* stmt: ASGNF4(addr,regf) */
/* 73 */	"\tCOPY32\t(%0,%1)\n",	/* stmt: ASGNF4(addr,INDIRF4(addr)) */
/* 74 */	"\tCOPY64\t(%0,%1)\n",	/* stmt: ASGNF8(addr,regf) */
/* 75 */	"\tCOPY64\t(%0,%1)\n",	/* stmt: ASGNF8(addr,INDIRF8(addr)) */
/* 76 */	"\tld\t%c,%0\n",	/* reg8: INDIRI1(addr) */
/* 77 */	"\tld\t%c,%0\n",	/* reg8: INDIRU1(addr) */
/* 78 */	"\tld\t%c,%0\n",	/* reg: INDIRI2(addr) */
/* 79 */	"\tld\t%c,%0\n",	/* reg: INDIRU2(addr) */
/* 80 */	"\tld\t%c,%0\n",	/* reg: INDIRP2(addr) */
/* 81 */	"\tCOPY32\t(%c,%0)\n",	/* reg32: INDIRI4(addr) */
/* 82 */	"\tCOPY32\t(%c,%0)\n",	/* reg32: INDIRU4(addr) */
/* 83 */	"\tCOPY32\t(%c,%0)\n",	/* regf: INDIRF4(addr) */
/* 84 */	"\tCOPY64\t(%c,%0)\n",	/* regf: INDIRF8(addr) */
/* 85 */	"\tmovb\t%c,%0\n",	/* reg8: CVII1(reg) */
/* 86 */	"\tmovb\t%c,%0\n",	/* reg8: CVIU1(reg) */
/* 87 */	"\tmovb\t%c,%0\n",	/* reg8: CVUI1(reg) */
/* 88 */	"\tmovb\t%c,%0\n",	/* reg8: CVUU1(reg) */
/* 89 */	"\tCVI4I1\t(%c,%0)\n",	/* reg8: CVII1(reg32) */
/* 90 */	"\tCVI4U1\t(%c,%0)\n",	/* reg8: CVIU1(reg32) */
/* 91 */	"\tCVU4I1\t(%c,%0)\n",	/* reg8: CVUI1(reg32) */
/* 92 */	"\tCVU4U1\t(%c,%0)\n",	/* reg8: CVUU1(reg32) */
/* 93 */	"\tsex\t%c\n",	/* reg: CVII2(reg8) */
/* 94 */	"\tsex\t%c\n",	/* reg: CVIU2(reg8) */
/* 95 */	"\tand\t%c,0x00ff\n",	/* reg: CVUI2(reg8) */
/* 96 */	"\tand\t%c,0x00ff\n",	/* reg: CVUU2(reg8) */
/* 97 */	"\tCVI4I2\t(%c,%0)\n",	/* reg: CVII2(reg32) */
/* 98 */	"\tCVI4U2\t(%c,%0)\n",	/* reg: CVIU2(reg32) */
/* 99 */	"\tCVU4I2\t(%c,%0)\n",	/* reg: CVUI2(reg32) */
/* 100 */	"\tCVU4U2\t(%c,%0)\n",	/* reg: CVUU2(reg32) */
/* 101 */	"\tCVI1I4\t(%c,%0)\n",	/* reg32: CVII4(reg8) */
/* 102 */	"\tCVI1U4\t(%c,%0)\n",	/* reg32: CVIU4(reg8) */
/* 103 */	"\tCVU1I4\t(%c,%0)\n",	/* reg32: CVUI4(reg8) */
/* 104 */	"\tCVU1U4\t(%c,%0)\n",	/* reg32: CVUU4(reg8) */
/* 105 */	"\tCVI2I4\t(%c,%0)\n",	/* reg32: CVII4(reg) */
/* 106 */	"\tCVI2U4\t(%c,%0)\n",	/* reg32: CVIU4(reg) */
/* 107 */	"\tCVU2I4\t(%c,%0)\n",	/* reg32: CVUI4(reg) */
/* 108 */	"\tCVI2U4\t(%c,%0)\n",	/* reg32: CVUU4(reg) */
/* 109 */	"\tCVTI1F4\t(%c,%0)\n",	/* regf: CVIF4(reg8) */
/* 110 */	"\tCVTI2F4\t(%c,%0)\n",	/* regf: CVIF4(reg) */
/* 111 */	"\tCVTI4F4\t(%c,%0)\n",	/* regf: CVIF4(reg32) */
/* 112 */	"\tCVTI1F8\t(%c,%0)\n",	/* regf: CVIF8(reg8) */
/* 113 */	"\tCVTI2F8\t(%c,%0)\n",	/* regf: CVIF8(reg) */
/* 114 */	"\tCVTI4F8\t(%c,%0)\n",	/* regf: CVIF8(reg32) */
/* 115 */	"\tCVTFI2\t(%c,%0)\n",	/* reg: CVFI2(regf) */
/* 116 */	"\tCVTFI4\t(%c,%0)\n",	/* reg: CVFI4(regf) */
/* 117 */	"\tCVTF8F4\t(%c,%0)\n",	/* regf: CVFF4(regf) */
/* 118 */	"\tCVTF4F8\t(%c,%0)\n",	/* regf: CVFF8(regf) */
/* 119 */	"\tmov\t%c,%0\n",	/* reg: CVPU2(reg) */
/* 120 */	"\tmov\t%c,%0\n",	/* reg: CVUP2(reg) */
/* 121 */	"?\tmov\t%c,%0\n\tadd\t%c,%1\n",	/* reg: ADDI2(reg,reg) */
/* 122 */	"?\tmov\t%c,%0\n\tadd\t%c,%1\n",	/* reg: ADDI2(reg,INDIRI2(addr)) */
/* 123 */	"?\tmov\t%c,%0\n\tadd\t%c,%1\n",	/* reg: ADDI2(reg,con) */
/* 124 */	"?\tmov\t%c,%0\n\tinc\t%c\n",	/* reg: ADDI2(reg,con1) */
/* 125 */	"?\tmov\t%c,%0\n\tadd\t%c,%1\n",	/* reg: ADDU2(reg,reg) */
/* 126 */	"?\tmov\t%c,%0\n\tadd\t%c,%1\n",	/* reg: ADDU2(reg,INDIRU2(addr)) */
/* 127 */	"?\tmov\t%c,%0\n\tadd\t%c,%1\n",	/* reg: ADDU2(reg,con) */
/* 128 */	"?\tmov\t%c,%0\n\tinc\t%c\n",	/* reg: ADDU2(reg,con1) */
/* 129 */	"?\tmov\t%c,%0\n\tadd\t%c,%1\n",	/* reg: ADDP2(reg,reg) */
/* 130 */	"\tlea\t%c,(%0:%1)\n",	/* reg: ADDP2(reg,con) */
/* 131 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: ADDI2(reg8,CVII2(INDIRI1(addr))) */
/* 132 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: ADDI2(CVII2(reg8),CVII2(INDIRI1(addr))) */
/* 133 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: ADDI2(CVUI2(reg8),CVII2(INDIRI1(addr))) */
/* 134 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: ADDI2(reg8,con) */
/* 135 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: ADDI2(CVII2(reg8),con) */
/* 136 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: ADDI2(CVUI2(reg8),con) */
/* 137 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: ADDU2(reg8,CVUU2(INDIRU1(addr))) */
/* 138 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: ADDU2(CVUU2(reg8),CVUU2(INDIRU1(addr))) */
/* 139 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: ADDU2(CVIU2(reg8),CVUU2(INDIRU1(addr))) */
/* 140 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: ADDU2(reg8,con) */
/* 141 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: ADDU2(CVUU2(reg8),con) */
/* 142 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: ADDU2(CVIU2(reg8),con) */
/* 143 */	"?\tCOPY32\t(%c,%0)\n\tADDI32\t(%c,%1)\n",	/* reg32: ADDI4(reg32,reg32) */
/* 144 */	"?\tCOPY32\t(%c,%0)\n\tADDI32\t(%c,%1)\n",	/* reg32: ADDI4(reg32,INDIRI4(addr)) */
/* 145 */	"?\tCOPY32\t(%c,%0)\n\tADDU32\t(%c,%1)\n",	/* reg32: ADDU4(reg32,reg32) */
/* 146 */	"?\tCOPY32\t(%c,%0)\n\tADDU32\t(%c,%1)\n",	/* reg32: ADDU4(reg32,INDIRU4(addr)) */
/* 147 */	"?\tCOPY32\t(%c,%0)\n\tADDF32\t(%c,%1)\n",	/* regf: ADDF4(regf,regf) */
/* 148 */	"?\tCOPY32\t(%c,%0)\n\tADDF32\t(%c,%1)\n",	/* regf: ADDF4(regf,INDIRF4(addr)) */
/* 149 */	"?\tCOPY64\t(%c,%0)\n\tADDF64\t(%c,%1)\n",	/* regf: ADDF8(regf,regf) */
/* 150 */	"?\tCOPY64\t(%c,%0)\n\tADDF64\t(%c,%1)\n",	/* regf: ADDF8(regf,INDIRF8(addr)) */
/* 151 */	"\tCOPY32\t(%0,%1)\n\tADDI32(%0,%2)\n",	/* stmt: ASGNI4(addr,ADDI4(INDIRI4(addr),INDIRI4(addr))) */
/* 152 */	"\tADDI32\t(%1,%2)\n",	/* stmt: ASGNI4(addr,ADDI4(INDIRI4(addr),INDIRI4(addr))) */
/* 153 */	"\tCOPY32\t(%0,%1)\n\tADDF32(%0,%2)\n",	/* stmt: ASGNF4(addr,ADDF4(INDIRF4(addr),INDIRF4(addr))) */
/* 154 */	"\tADDF32\t(%1,%2)\n",	/* stmt: ASGNF4(addr,ADDF4(INDIRF4(addr),INDIRF4(addr))) */
/* 155 */	"\tCOPY64\t(%0,%1)\n\tADDF64(%0,%2)\n",	/* stmt: ASGNF8(addr,ADDF8(INDIRF8(addr),INDIRF8(addr))) */
/* 156 */	"\tADDF64\t(%1,%2)\n",	/* stmt: ASGNF8(addr,ADDF8(INDIRF8(addr),INDIRF8(addr))) */
/* 157 */	"?\tmov\t%c,%0\n\tsub\t%c,%1\n",	/* reg: SUBI2(reg,reg) */
/* 158 */	"?\tmov\t%c,%0\n\tsub\t%c,%1\n",	/* reg: SUBI2(reg,INDIRI2(addr)) */
/* 159 */	"?\tmov\t%c,%0\n\tsub\t%c,%1\n",	/* reg: SUBI2(reg,con) */
/* 160 */	"?\tmov\t%c,%0\n\tdec\t%c\n",	/* reg: SUBI2(reg,con1) */
/* 161 */	"?\tmov\t%c,%0\n\tsub\t%c,%1\n",	/* reg: SUBU2(reg,reg) */
/* 162 */	"?\tmov\t%c,%0\n\tsub\t%c,%1\n",	/* reg: SUBU2(reg,INDIRU2(addr)) */
/* 163 */	"?\tmov\t%c,%0\n\tsub\t%c,%1\n",	/* reg: SUBU2(reg,con) */
/* 164 */	"?\tmov\t%c,%0\n\tdec\t%c\n",	/* reg: SUBU2(reg,con1) */
/* 165 */	"?\tmov\t%c,%0\n\tsub\t%c,%1\n",	/* reg: SUBP2(reg,reg) */
/* 166 */	"\tlea\t%c,(%0:-%1)\n",	/* reg: ADDP2(reg,con) */
/* 167 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: SUBI2(reg8,CVII2(INDIRI1(addr))) */
/* 168 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: SUBI2(CVII2(reg8),CVII2(INDIRI1(addr))) */
/* 169 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: SUBI2(CVUI2(reg8),CVII2(INDIRI1(addr))) */
/* 170 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: SUBI2(reg8,con) */
/* 171 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: SUBI2(CVII2(reg8),con) */
/* 172 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: SUBI2(CVUI2(reg8),con) */
/* 173 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: SUBU2(reg8,CVUU2(INDIRU1(addr))) */
/* 174 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: SUBU2(CVUU2(reg8),CVUU2(INDIRU1(addr))) */
/* 175 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: SUBU2(CVIU2(reg8),CVUU2(INDIRU1(addr))) */
/* 176 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: SUBU2(reg8,con) */
/* 177 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: SUBU2(CVUU2(reg8),con) */
/* 178 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: SUBU2(CVIU2(reg8),con) */
/* 179 */	"?\tCOPY32\t(%c,%0)\n\tSUBI32\t(%c,%1)\n",	/* reg32: SUBI4(reg32,reg32) */
/* 180 */	"?\tCOPY32\t(%c,%0)\n\tSUBI32\t(%c,%1)\n",	/* reg32: SUBI4(reg32,INDIRI4(addr)) */
/* 181 */	"?\tCOPY32\t(%c,%0)\n\tSUBU32\t(%c,%1)\n",	/* reg32: SUBU4(reg32,reg32) */
/* 182 */	"?\tCOPY32\t(%c,%0)\n\tSUBU32\t(%c,%1)\n",	/* reg32: SUBU4(reg32,INDIRU4(addr)) */
/* 183 */	"?\tCOPY32\t(%c,%0)\n\tSUBF32\t(%c,%1)\n",	/* regf: SUBF4(regf,regf) */
/* 184 */	"?\tCOPY32\t(%c,%0)\n\tSUBF32\t(%c,%1)\n",	/* regf: SUBF4(regf,INDIRF4(addr)) */
/* 185 */	"?\tCOPY64\t(%c,%0)\n\tSUBF64\t(%c,%1)\n",	/* regf: SUBF8(regf,regf) */
/* 186 */	"?\tCOPY64\t(%c,%0)\n\tSUBF64\t(%c,%1)\n",	/* regf: SUBF8(regf,INDIRF8(addr)) */
/* 187 */	"\tCOPY32\t(%0,%1)\n\tSUBI32(%0,%2)\n",	/* stmt: ASGNI4(addr,SUBI4(INDIRI4(addr),INDIRI4(addr))) */
/* 188 */	"\tSUBI32\t(%1,%2)\n",	/* stmt: ASGNI4(addr,SUBI4(INDIRI4(addr),INDIRI4(addr))) */
/* 189 */	"\tCOPY32\t(%0,%1)\n\tSUBF32(%0,%2)\n",	/* stmt: ASGNF4(addr,SUBF4(INDIRF4(addr),INDIRF4(addr))) */
/* 190 */	"\tSUBF32\t(%1,%2)\n",	/* stmt: ASGNF4(addr,SUBF4(INDIRF4(addr),INDIRF4(addr))) */
/* 191 */	"\tCOPY64\t(%0,%1)\n\tSUBF64(%0,%2)\n",	/* stmt: ASGNF8(addr,SUBF8(INDIRF8(addr),INDIRF8(addr))) */
/* 192 */	"\tSUBF64\t(%1,%2)\n",	/* stmt: ASGNF8(addr,SUBF8(INDIRF8(addr),INDIRF8(addr))) */
/* 193 */	"\txor\t%c,%c\n\tsub\t%c,%0\n",	/* reg: NEGI2(reg) */
/* 194 */	"\txor\t%c,%c\n\tsub\t%c,%0\n",	/* reg: NEGI2(INDIRI2(addr)) */
/* 195 */	"\tNEGI32\t(%c,%0)\n",	/* reg32: NEGI4(reg32) */
/* 196 */	"\tNEGI32\t(%c,%0)\n",	/* reg32: NEGI4(INDIRI4(addr)) */
/* 197 */	"\tNEGF32\t(%c,%0)\n",	/* regf: NEGF4(regf) */
/* 198 */	"\tNEGF32\t(%c,%0)\n",	/* regf: NEGF4(INDIRF4(addr)) */
/* 199 */	"\tNEGF64\t(%c,%0)\n",	/* regf: NEGF8(regf) */
/* 200 */	"\tNEGF64\t(%c,%0)\n",	/* regf: NEGF8(INDIRF8(addr)) */
/* 201 */	"?\tmov\t%c,%0\n\tand\t%c,%1\n",	/* reg: BANDI2(reg,reg) */
/* 202 */	"?\tmov\t%c,%0\n\tand\t%c,%1\n",	/* reg: BANDI2(reg,INDIRI2(lgaddr)) */
/* 203 */	"?\tmov\t%c,%0\n\tand\t%c,%1\n",	/* reg: BANDI2(reg,con) */
/* 204 */	"?\tmov\t%c,%0\n\tand\t%c,%1\n",	/* reg: BANDU2(reg,reg) */
/* 205 */	"?\tmov\t%c,%0\n\tand\t%c,%1\n",	/* reg: BANDU2(reg,INDIRU2(lgaddr)) */
/* 206 */	"?\tmov\t%c,%0\n\tand\t%c,%1\n",	/* reg: BANDU2(reg,con) */
/* 207 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BANDI2(reg8,CVII2(INDIRI1(lgaddr))) */
/* 208 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BANDI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 209 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BANDI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 210 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BANDI2(reg8,con) */
/* 211 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BANDI2(CVII2(reg8),con) */
/* 212 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BANDI2(CVUI2(reg8),con) */
/* 213 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BANDU2(reg8,CVUU2(INDIRU1(lgaddr))) */
/* 214 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BANDU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 215 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BANDU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 216 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BANDU2(reg8,con) */
/* 217 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BANDU2(CVUU2(reg8),con) */
/* 218 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BANDU2(CVIU2(reg8),con) */
/* 219 */	"?\tCOPY32\t%(c,%0)\n\tBANDI32\t(%c,%1)\n",	/* reg32: BANDI4(reg32,reg32) */
/* 220 */	"?\tCOPY32\t%(c,%0)\n\tBANDI32\t(%c,%1)\n",	/* reg32: BANDI4(reg32,INDIRI4(addr)) */
/* 221 */	"?\tCOPY32\t%(c,%0)\n\tBANDI32\t(%c,%1)\n",	/* reg32: BANDU4(reg32,reg32) */
/* 222 */	"?\tCOPY32\t%(c,%0)\n\tBANDI32\t(%c,%1)\n",	/* reg32: BANDU4(reg32,INDIRU4(addr)) */
/* 223 */	"\tmov\t%c,-1\n\txor\t%c,%0\n",	/* reg: BCOMI2(reg) */
/* 224 */	"\tmov\t%c,-1\n\txor\t%c,%0\n",	/* reg: BCOMU2(reg) */
/* 225 */	"\tBCOMI4\t(%c,%0)\n",	/* reg32: BCOMI4(reg32) */
/* 226 */	"\tBCOMI4\t(%c,%0)\n",	/* reg32: BCOMU4(reg32) */
/* 227 */	"?\tmov\t%c,%0\n\tor\t%c,%1\n",	/* reg: BORI2(reg,reg) */
/* 228 */	"?\tmov\t%c,%0\n\tor\t%c,%1\n",	/* reg: BORI2(reg,INDIRI2(lgaddr)) */
/* 229 */	"?\tmov\t%c,%0\n\tor\t%c,%1\n",	/* reg: BORI2(reg,con) */
/* 230 */	"?\tmov\t%c,%0\n\tor\t%c,%1\n",	/* reg: BORU2(reg,reg) */
/* 231 */	"?\tmov\t%c,%0\n\tor\t%c,%1\n",	/* reg: BORU2(reg,INDIRU2(lgaddr)) */
/* 232 */	"?\tmov\t%c,%0\n\tor\t%c,%1\n",	/* reg: BORU2(reg,con) */
/* 233 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BORI2(reg8,CVII2(INDIRI1(lgaddr))) */
/* 234 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BORI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 235 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BORI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 236 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BORI2(reg8,con) */
/* 237 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BORI2(CVII2(reg8),con) */
/* 238 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BORI2(CVUI2(reg8),con) */
/* 239 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BORU2(reg8,CVUU2(INDIRU1(lgaddr))) */
/* 240 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BORU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 241 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BORU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 242 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BORU2(reg8,con) */
/* 243 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BORU2(CVUU2(reg8),con) */
/* 244 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BORU2(CVIU2(reg8),con) */
/* 245 */	"?\tCOPY32\t%(c,%0)\n\tBORI32\t(%c,%1)\n",	/* reg32: BORI4(reg32,reg32) */
/* 246 */	"?\tCOPY32\t%(c,%0)\n\tBORI32\t(%c,%1)\n",	/* reg32: BORI4(reg32,INDIRI4(addr)) */
/* 247 */	"?\tCOPY32\t%(c,%0)\n\tBORI32\t(%c,%1)\n",	/* reg32: BORU4(reg32,reg32) */
/* 248 */	"?\tCOPY32\t%(c,%0)\n\tBORI32\t(%c,%1)\n",	/* reg32: BORU4(reg32,INDIRU4(addr)) */
/* 249 */	"?\tmov\t%c,%0\n\txor\t%c,%1\n",	/* reg: BXORI2(reg,reg) */
/* 250 */	"?\tmov\t%c,%0\n\txor\t%c,%1\n",	/* reg: BXORI2(reg,INDIRI2(lgaddr)) */
/* 251 */	"?\tmov\t%c,%0\n\txor\t%c,%1\n",	/* reg: BXORI2(reg,con) */
/* 252 */	"?\tmov\t%c,%0\n\txor\t%c,%1\n",	/* reg: BXORU2(reg,reg) */
/* 253 */	"?\tmov\t%c,%0\n\txor\t%c,%1\n",	/* reg: BXORU2(reg,INDIRU2(lgaddr)) */
/* 254 */	"?\tmov\t%c,%0\n\txor\t%c,%1\n",	/* reg: BXORU2(reg,con) */
/* 255 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BXORI2(reg8,CVII2(INDIRI1(lgaddr))) */
/* 256 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BXORI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 257 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BXORI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 258 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BXORI2(reg8,con) */
/* 259 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BXORI2(CVII2(reg8),con) */
/* 260 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BXORI2(CVUI2(reg8),con) */
/* 261 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BXORU2(reg8,CVUU2(INDIRU1(lgaddr))) */
/* 262 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BXORU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 263 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BXORU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 264 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BXORU2(reg8,con) */
/* 265 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BXORU2(CVUU2(reg8),con) */
/* 266 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: BXORU2(CVIU2(reg8),con) */
/* 267 */	"?\tCOPY32\t%(c,%0)\n\tBXORI32\t(%c,%1)\n",	/* reg32: BXORI4(reg32,reg32) */
/* 268 */	"?\tCOPY32\t%(c,%0)\n\tBXORI32\t(%c,%1)\n",	/* reg32: BXORI4(reg32,INDIRI4(addr)) */
/* 269 */	"?\tCOPY32\t%(c,%0)\n\tBXORI32\t(%c,%1)\n",	/* reg32: BXORU4(reg32,reg32) */
/* 270 */	"?\tCOPY32\t%(c,%0)\n\tBXORI32\t(%c,%1)\n",	/* reg32: BXORU4(reg32,INDIRU4(addr)) */
/* 271 */	"?\tmov\t%c,%0\n\tcall\t__muli2\n",	/* reg: MULI2(reg,reg) */
/* 272 */	"?\tmov\t%c,%0\n\tcall\t__mulu2\n",	/* reg: MULU2(reg,reg) */
/* 273 */	"?\tmov\t%c,%0\n\tcall\t__divi2\n",	/* reg: DIVI2(reg,reg) */
/* 274 */	"?\tmov\t%c,%0\n\tcall\t__divu2\n",	/* reg: DIVU2(reg,reg) */
/* 275 */	"?\tmov\t%c,%0\n\tcall\t__modi2\n",	/* reg: MODI2(reg,reg) */
/* 276 */	"?\tmov\t%c,%0\n\tcall\t__modu2\n",	/* reg: MODU2(reg,reg) */
/* 277 */	"?\tCOPY32\t%(c,%0)\n\tMULI32\t(%c,%1)\n",	/* reg32: MULI4(reg32,reg32) */
/* 278 */	"?\tCOPY32\t%(c,%0)\n\tMULI32\t(%c,%1)\n",	/* reg32: MULI4(reg32,INDIRI4(addr)) */
/* 279 */	"?\tCOPY32\t%(c,%0)\n\tMULU32\t(%c,%1)\n",	/* reg32: MULU4(reg32,reg32) */
/* 280 */	"?\tCOPY32\t%(c,%0)\n\tMULU32\t(%c,%1)\n",	/* reg32: MULU4(reg32,INDIRU4(addr)) */
/* 281 */	"?\tCOPY32\t%(c,%0)\n\tDIVI32\t(%c,%1)\n",	/* reg32: DIVI4(reg32,reg32) */
/* 282 */	"?\tCOPY32\t%(c,%0)\n\tDIVI32\t(%c,%1)\n",	/* reg32: DIVI4(reg32,INDIRI4(addr)) */
/* 283 */	"?\tCOPY32\t%(c,%0)\n\tDIVU32\t(%c,%1)\n",	/* reg32: DIVU4(reg32,reg32) */
/* 284 */	"?\tCOPY32\t%(c,%0)\n\tDIVU32\t(%c,%1)\n",	/* reg32: DIVU4(reg32,INDIRU4(addr)) */
/* 285 */	"?\tCOPY32\t%(c,%0)\n\tMODI32\t(%c,%1)\n",	/* reg32: MODI4(reg32,reg32) */
/* 286 */	"?\tCOPY32\t%(c,%0)\n\tMODI32\t(%c,%1)\n",	/* reg32: MODI4(reg32,INDIRI4(addr)) */
/* 287 */	"?\tCOPY32\t%(c,%0)\n\tMODU32\t(%c,%1)\n",	/* reg32: MODU4(reg32,reg32) */
/* 288 */	"?\tCOPY32\t%(c,%0)\n\tMODU32\t(%c,%1)\n",	/* reg32: MODU4(reg32,INDIRU4(addr)) */
/* 289 */	"?\tCOPY32\t%(c,%0)\n\tMULF32\t(%c,%1)\n",	/* regf: MULF4(regf,regf) */
/* 290 */	"?\tCOPY32\t%(c,%0)\n\tMULF32\t(%c,%1)\n",	/* regf: MULF4(regf,INDIRF4(addr)) */
/* 291 */	"?\tCOPY64\t%(c,%0)\n\tMULF64\t(%c,%1)\n",	/* regf: MULF8(regf,regf) */
/* 292 */	"?\tCOPY64\t%(c,%0)\n\tMULF64\t(%c,%1)\n",	/* regf: MULF8(regf,INDIRF8(addr)) */
/* 293 */	"?\tCOPY32\t%(c,%0)\n\tDIVF32\t(%c,%1)\n",	/* regf: DIVF4(regf,regf) */
/* 294 */	"?\tCOPY32\t%(c,%0)\n\tDIVF32\t(%c,%1)\n",	/* regf: DIVF4(regf,INDIRF4(addr)) */
/* 295 */	"?\tCOPY64\t%(c,%0)\n\tDIVF64\t(%c,%1)\n",	/* regf: DIVF8(regf,regf) */
/* 296 */	"?\tCOPY64\t%(c,%0)\n\tDIVF64\t(%c,%1)\n",	/* regf: DIVF8(regf,INDIRF8(addr)) */
/* 297 */	"?\tmov\t%c,%0\n\tshl\t%0\n",	/* reg: LSHI2(reg,con1) */
/* 298 */	"?\tmov\t%c,%0\n\tshl\t%0\n",	/* reg: LSHU2(reg,con1) */
/* 299 */	"?\tmov\t%c,%0\n\tshr\t%0\n",	/* reg: RSHI2(reg,con1) */
/* 300 */	"?\tmov\t%c,%0\n\tshr\t%0\n",	/* reg: RSHU2(reg,con1) */
/* 301 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: LSHI2(reg8,con) */
/* 302 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: LSHI2(CVII2(reg8),con) */
/* 303 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: LSHI2(CVUI2(reg8),con) */
/* 304 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: LSHU2(reg8,con) */
/* 305 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: LSHU2(CVUU2(reg8),con) */
/* 306 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: LSHU2(CVIU2(reg8),con) */
/* 307 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: RSHI2(reg8,con) */
/* 308 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: RSHI2(CVII2(reg8),con) */
/* 309 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: RSHI2(CVUI2(reg8),con) */
/* 310 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: RSHU2(reg8,con) */
/* 311 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: RSHU2(CVUU2(reg8),con) */
/* 312 */	"# emit2 (use AH/AL instead of A)\n",	/* reg8: RSHU2(CVIU2(reg8),con) */
/* 313 */	"?\tCOPY32\t(%c,%0)\n\tRSHI32\t(%0)\n",	/* reg32: RSHI4(reg32,con1) */
/* 314 */	"?\tCOPY32\t(%c,%0)\n\tRSHU32\t(%0)\n",	/* reg32: RSHU4(reg32,con1) */
/* 315 */	"\tcmp\t%0,%1\n\tje\t%a\n",	/* stmt: EQI2(reg,reg) */
/* 316 */	"\tcmp\t%0,%1\n\tje\t%a\n",	/* stmt: EQI2(reg,INDIRI2(lgaddr)) */
/* 317 */	"\tcmp\t%0,%1\n\tje\t%a\n",	/* stmt: EQI2(reg,con) */
/* 318 */	"\tcmp\t%0,%1\n\tje\t%a\n",	/* stmt: EQI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 319 */	"\tcmp\t%0,%1\n\tje\t%a\n",	/* stmt: EQI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 320 */	"\tcmp\t%0,%1\n\tje\t%a\n",	/* stmt: EQI2(CVII2(reg8),con) */
/* 321 */	"\tcmp\t%0,%1\n\tje\t%a\n",	/* stmt: EQI2(CVUI2(reg8),con) */
/* 322 */	"\tcmp\t%0,%1\n\tje\t%a\n",	/* stmt: EQU2(reg,reg) */
/* 323 */	"\tcmp\t%0,%1\n\tje\t%a\n",	/* stmt: EQU2(reg,INDIRU2(lgaddr)) */
/* 324 */	"\tcmp\t%0,%1\n\tje\t%a\n",	/* stmt: EQU2(reg,con) */
/* 325 */	"\tcmp\t%0,%1\n\tje\t%a\n",	/* stmt: EQU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 326 */	"\tcmp\t%0,%1\n\tje\t%a\n",	/* stmt: EQU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 327 */	"\tcmp\t%0,%1\n\tje\t%a\n",	/* stmt: EQU2(CVUU2(reg8),con) */
/* 328 */	"\tcmp\t%0,%1\n\tje\t%a\n",	/* stmt: EQU2(CVIU2(reg8),con) */
/* 329 */	"\tCMP32\t(%0,%1)\n\tje\t%a\n",	/* stmt: EQI4(reg32,reg32) */
/* 330 */	"\tCMP32\t(%0,%1)\n\tje\t%a\n",	/* stmt: EQI4(reg32,INDIRI4(addr)) */
/* 331 */	"\tCMP32\t(%0,%1)\n\tje\t%a\n",	/* stmt: EQU4(reg32,reg32) */
/* 332 */	"\tCMP32\t(%0,%1)\n\tje\t%a\n",	/* stmt: EQU4(reg32,INDIRU4(addr)) */
/* 333 */	"\tCMP32\t(%0,%1)\n\tje\t%a\n",	/* stmt: EQF4(regf,regf) */
/* 334 */	"\tCMP32\t(%0,%1)\n\tje\t%a\n",	/* stmt: EQF4(regf,INDIRF4(addr)) */
/* 335 */	"\tCMP64\t(%0,%1)\n\tje\t%a\n",	/* stmt: EQF8(regf,regf) */
/* 336 */	"\tCMP64\t(%0,%1)\n\tje\t%a\n",	/* stmt: EQF8(regf,INDIRF8(addr)) */
/* 337 */	"\tcmp\t%0,%1\n\tjne\t%a\n",	/* stmt: NEI2(reg,reg) */
/* 338 */	"\tcmp\t%0,%1\n\tjne\t%a\n",	/* stmt: NEI2(reg,INDIRI2(reg)) */
/* 339 */	"\tcmp\t%0,%1\n\tjne\t%a\n",	/* stmt: NEI2(reg,con) */
/* 340 */	"\tcmp\t%0,%1\n\tjne\t%a\n",	/* stmt: NEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 341 */	"\tcmp\t%0,%1\n\tjne\t%a\n",	/* stmt: NEI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 342 */	"\tcmp\t%0,%1\n\tjne\t%a\n",	/* stmt: NEI2(CVII2(reg8),con) */
/* 343 */	"\tcmp\t%0,%1\n\tjne\t%a\n",	/* stmt: NEI2(CVUI2(reg8),con) */
/* 344 */	"\tcmp\t%0,%1\n\tjne\t%a\n",	/* stmt: NEU2(reg,reg) */
/* 345 */	"\tcmp\t%0,%1\n\tjne\t%a\n",	/* stmt: NEU2(reg,INDIRU2(reg)) */
/* 346 */	"\tcmp\t%0,%1\n\tjne\t%a\n",	/* stmt: NEU2(reg,con) */
/* 347 */	"\tcmp\t%0,%1\n\tjne\t%a\n",	/* stmt: NEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 348 */	"\tcmp\t%0,%1\n\tjne\t%a\n",	/* stmt: NEU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 349 */	"\tcmp\t%0,%1\n\tjne\t%a\n",	/* stmt: NEU2(CVUU2(reg8),con) */
/* 350 */	"\tcmp\t%0,%1\n\tjne\t%a\n",	/* stmt: NEU2(CVIU2(reg8),con) */
/* 351 */	"\tCMP32\t(%0,%1)\n\tjne\t%a\n",	/* stmt: NEI4(reg32,reg32) */
/* 352 */	"\tCMP32\t(%0,%1)\n\tjne\t%a\n",	/* stmt: NEI4(reg32,INDIRI4(addr)) */
/* 353 */	"\tCMP32\t(%0,%1)\n\tjne\t%a\n",	/* stmt: NEU4(reg32,reg32) */
/* 354 */	"\tCMP32\t(%0,%1)\n\tjne\t%a\n",	/* stmt: NEU4(reg32,INDIRU4(addr)) */
/* 355 */	"\tCMP32\t(%0,%1)\n\tjne\t%a\n",	/* stmt: NEF4(regf,regf) */
/* 356 */	"\tCMP32\t(%0,%1)\n\tjne\t%a\n",	/* stmt: NEF4(regf,INDIRF4(addr)) */
/* 357 */	"\tCMP64\t(%0,%1)\n\tjne\t%a\n",	/* stmt: NEF8(regf,regf) */
/* 358 */	"\tCMP64\t(%0,%1)\n\tjne\t%a\n",	/* stmt: NEF8(regf,INDIRF8(addr)) */
/* 359 */	"\tcmp\t%0,%1\n\tjle\t%a\n",	/* stmt: LEI2(reg,reg) */
/* 360 */	"\tcmp\t%0,%1\n\tjle\t%a\n",	/* stmt: LEI2(reg,INDIRI2(reg)) */
/* 361 */	"\tcmp\t%0,%1\n\tjle\t%a\n",	/* stmt: LEI2(reg,con) */
/* 362 */	"\tcmp\t%0,%1\n\tjle\t%a\n",	/* stmt: LEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 363 */	"\tcmp\t%0,%1\n\tjle\t%a\n",	/* stmt: LEI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 364 */	"\tcmp\t%0,%1\n\tjle\t%a\n",	/* stmt: LEI2(CVII2(reg8),con) */
/* 365 */	"\tcmp\t%0,%1\n\tjle\t%a\n",	/* stmt: LEI2(CVUI2(reg8),con) */
/* 366 */	"\tcmp\t%0,%1\n\tjleu\t%a\n",	/* stmt: LEU2(reg,reg) */
/* 367 */	"\tcmp\t%0,%1\n\tjleu\t%a\n",	/* stmt: LEU2(reg,INDIRU2(reg)) */
/* 368 */	"\tcmp\t%0,%1\n\tjleu\t%a\n",	/* stmt: LEU2(reg,con) */
/* 369 */	"\tcmp\t%0,%1\n\tjleu\t%a\n",	/* stmt: LEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 370 */	"\tcmp\t%0,%1\n\tjleu\t%a\n",	/* stmt: LEU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 371 */	"\tcmp\t%0,%1\n\tjleu\t%a\n",	/* stmt: LEU2(CVUU2(reg8),con) */
/* 372 */	"\tcmp\t%0,%1\n\tjleu\t%a\n",	/* stmt: LEU2(CVIU2(reg8),con) */
/* 373 */	"\tCMP32\t(%0,%1)\n\tjle\t%a\n",	/* stmt: LEI4(reg32,reg32) */
/* 374 */	"\tCMP32\t(%0,%1)\n\tjle\t%a\n",	/* stmt: LEI4(reg32,INDIRI4(addr)) */
/* 375 */	"\tCMP32\t(%0,%1)\n\tjleu\t%a\n",	/* stmt: LEU4(reg32,reg32) */
/* 376 */	"\tCMP32\t(%0,%1)\n\tjleu\t%a\n",	/* stmt: LEU4(reg32,INDIRU4(addr)) */
/* 377 */	"\tCMP32\t(%0,%1)\n\tjle\t%a\n",	/* stmt: LEF4(regf,regf) */
/* 378 */	"\tCMP32\t(%0,%1)\n\tjle\t%a\n",	/* stmt: LEF4(regf,INDIRF4(addr)) */
/* 379 */	"\tCMP64\t(%0,%1)\n\tjle\t%a\n",	/* stmt: LEF8(regf,regf) */
/* 380 */	"\tCMP64\t(%0,%1)\n\tjle\t%a\n",	/* stmt: LEF8(regf,INDIRF8(addr)) */
/* 381 */	"\tcmp\t%0,%1\n\tjl\t%a\n",	/* stmt: LTI2(reg,reg) */
/* 382 */	"\tcmp\t%0,%1\n\tjl\t%a\n",	/* stmt: LTI2(reg,INDIRI2(reg)) */
/* 383 */	"\tcmp\t%0,%1\n\tjl\t%a\n",	/* stmt: LTI2(reg,con) */
/* 384 */	"\tcmp\t%0,%1\n\tjl\t%a\n",	/* stmt: LTI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 385 */	"\tcmp\t%0,%1\n\tjl\t%a\n",	/* stmt: LTI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 386 */	"\tcmp\t%0,%1\n\tjl\t%a\n",	/* stmt: LTI2(CVII2(reg8),con) */
/* 387 */	"\tcmp\t%0,%1\n\tjl\t%a\n",	/* stmt: LTI2(CVUI2(reg8),con) */
/* 388 */	"\tcmp\t%0,%1\n\tjlu\t%a\n",	/* stmt: LTU2(reg,reg) */
/* 389 */	"\tcmp\t%0,%1\n\tjlu\t%a\n",	/* stmt: LTU2(reg,INDIRU2(reg)) */
/* 390 */	"\tcmp\t%0,%1\n\tjlu\t%a\n",	/* stmt: LTU2(reg,con) */
/* 391 */	"\tcmp\t%0,%1\n\tjlu\t%a\n",	/* stmt: LTU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 392 */	"\tcmp\t%0,%1\n\tjlu\t%a\n",	/* stmt: LTU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 393 */	"\tcmp\t%0,%1\n\tjlu\t%a\n",	/* stmt: LTU2(CVUU2(reg8),con) */
/* 394 */	"\tcmp\t%0,%1\n\tjlu\t%a\n",	/* stmt: LTU2(CVIU2(reg8),con) */
/* 395 */	"\tCMP32\t(%0,%1)\n\tjlt\t%a\n",	/* stmt: LTI4(reg32,reg32) */
/* 396 */	"\tCMP32\t(%0,%1)\n\tjlt\t%a\n",	/* stmt: LTI4(reg32,INDIRI4(addr)) */
/* 397 */	"\tCMP32\t(%0,%1)\n\tjltu\t%a\n",	/* stmt: LTU4(reg32,reg32) */
/* 398 */	"\tCMP32\t(%0,%1)\n\tjltu\t%a\n",	/* stmt: LTU4(reg32,INDIRU4(addr)) */
/* 399 */	"\tCMP32\t(%0,%1)\n\tjlt\t%a\n",	/* stmt: LTF4(regf,regf) */
/* 400 */	"\tCMP32\t(%0,%1)\n\tjlt\t%a\n",	/* stmt: LTF4(regf,INDIRF4(addr)) */
/* 401 */	"\tCMP64\t(%0,%1)\n\tjlt\t%a\n",	/* stmt: LTF8(regf,regf) */
/* 402 */	"\tCMP64\t(%0,%1)\n\tjlt\t%a\n",	/* stmt: LTF8(regf,INDIRF8(addr)) */
/* 403 */	"\tcmp\t%0,%1\n\tjge\t%a\n",	/* stmt: GEI2(reg,reg) */
/* 404 */	"\tcmp\t%0,%1\n\tjge\t%a\n",	/* stmt: GEI2(reg,INDIRI2(reg)) */
/* 405 */	"\tcmp\t%0,%1\n\tjge\t%a\n",	/* stmt: GEI2(reg,con) */
/* 406 */	"\tcmp\t%0,%1\n\tjge\t%a\n",	/* stmt: GEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 407 */	"\tcmp\t%0,%1\n\tjge\t%a\n",	/* stmt: GEI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 408 */	"\tcmp\t%0,%1\n\tjge\t%a\n",	/* stmt: GEI2(CVII2(reg8),con) */
/* 409 */	"\tcmp\t%0,%1\n\tjge\t%a\n",	/* stmt: GEI2(CVUI2(reg8),con) */
/* 410 */	"\tcmp\t%0,%1\n\tjgeu\t%a\n",	/* stmt: GEU2(reg,reg) */
/* 411 */	"\tcmp\t%0,%1\n\tjgeu\t%a\n",	/* stmt: GEU2(reg,INDIRU2(reg)) */
/* 412 */	"\tcmp\t%0,%1\n\tjgeu\t%a\n",	/* stmt: GEU2(reg,con) */
/* 413 */	"\tcmp\t%0,%1\n\tjgeu\t%a\n",	/* stmt: GEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 414 */	"\tcmp\t%0,%1\n\tjgeu\t%a\n",	/* stmt: GEU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 415 */	"\tcmp\t%0,%1\n\tjgeu\t%a\n",	/* stmt: GEU2(CVUU2(reg8),con) */
/* 416 */	"\tcmp\t%0,%1\n\tjgeu\t%a\n",	/* stmt: GEU2(CVIU2(reg8),con) */
/* 417 */	"\tCMP32\t(%0,%1)\n\tjge\t%a\n",	/* stmt: GEI4(reg32,reg32) */
/* 418 */	"\tCMP32\t(%0,%1)\n\tjge\t%a\n",	/* stmt: GEI4(reg32,INDIRI4(addr)) */
/* 419 */	"\tCMP32\t(%0,%1)\n\tjgeu\t%a\n",	/* stmt: GEU4(reg32,reg32) */
/* 420 */	"\tCMP32\t(%0,%1)\n\tjgeu\t%a\n",	/* stmt: GEU4(reg32,INDIRU4(addr)) */
/* 421 */	"\tCMP32\t(%0,%1)\n\tjge\t%a\n",	/* stmt: GEF4(regf,regf) */
/* 422 */	"\tCMP32\t(%0,%1)\n\tjge\t%a\n",	/* stmt: GEF4(regf,INDIRF4(addr)) */
/* 423 */	"\tCMP64\t(%0,%1)\n\tjge\t%a\n",	/* stmt: GEF8(regf,regf) */
/* 424 */	"\tCMP64\t(%0,%1)\n\tjge\t%a\n",	/* stmt: GEF8(regf,INDIRF8(addr)) */
/* 425 */	"\tcmp\t%0,%1\n\tjg\t%a\n",	/* stmt: GTI2(reg,reg) */
/* 426 */	"\tcmp\t%0,%1\n\tjg\t%a\n",	/* stmt: GTI2(reg,INDIRI2(reg)) */
/* 427 */	"\tcmp\t%0,%1\n\tjg\t%a\n",	/* stmt: GTI2(reg,con) */
/* 428 */	"\tcmp\t%0,%1\n\tjg\t%a\n",	/* stmt: GTI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 429 */	"\tcmp\t%0,%1\n\tjg\t%a\n",	/* stmt: GTI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
/* 430 */	"\tcmp\t%0,%1\n\tjg\t%a\n",	/* stmt: GTI2(CVII2(reg8),con) */
/* 431 */	"\tcmp\t%0,%1\n\tjg\t%a\n",	/* stmt: GTI2(CVUI2(reg8),con) */
/* 432 */	"\tcmp\t%0,%1\n\tjgu\t%a\n",	/* stmt: GTU2(reg,reg) */
/* 433 */	"\tcmp\t%0,%1\n\tjgu\t%a\n",	/* stmt: GTU2(reg,INDIRU2(reg)) */
/* 434 */	"\tcmp\t%0,%1\n\tjgu\t%a\n",	/* stmt: GTU2(reg,con) */
/* 435 */	"\tcmp\t%0,%1\n\tjgu\t%a\n",	/* stmt: GTU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 436 */	"\tcmp\t%0,%1\n\tjgu\t%a\n",	/* stmt: GTU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
/* 437 */	"\tcmp\t%0,%1\n\tjgu\t%a\n",	/* stmt: GTU2(CVUU2(reg8),con) */
/* 438 */	"\tcmp\t%0,%1\n\tjgu\t%a\n",	/* stmt: GTU2(CVIU2(reg8),con) */
/* 439 */	"\tCMP32\t(%0,%1)\n\tjg\t%a\n",	/* stmt: GTI4(reg32,reg32) */
/* 440 */	"\tCMP32\t(%0,%1)\n\tjg\t%a\n",	/* stmt: GTI4(reg32,INDIRI4(addr)) */
/* 441 */	"\tCMP32\t(%0,%1)\n\tjgu\t%a\n",	/* stmt: GTU4(reg32,reg32) */
/* 442 */	"\tCMP32\t(%0,%1)\n\tjgu\t%a\n",	/* stmt: GTU4(reg32,INDIRU4(addr)) */
/* 443 */	"\tCMP32\t(%0,%1)\n\tjg\t%a\n",	/* stmt: GTF4(regf,regf) */
/* 444 */	"\tCMP32\t(%0,%1)\n\tjg\t%a\n",	/* stmt: GTF4(regf,INDIRF4(addr)) */
/* 445 */	"\tCMP64\t(%0,%1)\n\tjg\t%a\n",	/* stmt: GTF8(regf,regf) */
/* 446 */	"\tCMP64\t(%0,%1)\n\tjg\t%a\n",	/* stmt: GTF8(regf,INDIRF8(addr)) */
/* 447 */	"# emit2\n",	/* stmt: ARGI2(reg) */
/* 448 */	"# emit2\n",	/* stmt: ARGU2(reg) */
/* 449 */	"# emit2\n",	/* stmt: ARGP2(reg) */
/* 450 */	"# emit2\n",	/* stmt: ARGI4(reg32) */
/* 451 */	"# emit2\n",	/* stmt: ARGU4(reg32) */
/* 452 */	"# emit2\n",	/* stmt: ARGF4(regf) */
/* 453 */	"# emit2\n",	/* stmt: ARGF8(regf) */
/* 454 */	"\tcall\t%0\n",	/* reg: CALLI2(albl) */
/* 455 */	"\tcall\t%0\n",	/* reg: CALLU2(albl) */
/* 456 */	"\tcall\t%0\n",	/* reg: CALLP2(albl) */
/* 457 */	"\tcall\t%0\n",	/* stmt: CALLV(albl) */
/* 458 */	"# emit2\n",	/* reg32: CALLI4(albl) */
/* 459 */	"# emit2\n",	/* reg32: CALLU4(albl) */
/* 460 */	"# emit2\n",	/* regf: CALLF4(albl) */
/* 461 */	"\tlea\ta,%c\n\tcall\t%0\n",	/* regf: CALLF8(albl) */
/* 462 */	"# return\n",	/* stmt: RETI2(reg) */
/* 463 */	"# return\n",	/* stmt: RETU2(reg) */
/* 464 */	"# return\n",	/* stmt: RETP2(reg) */
/* 465 */	"# return\n",	/* stmt: RETV */
/* 466 */	"# return\n",	/* stmt: RETI4(reg32) */
/* 467 */	"# return\n",	/* stmt: RETU4(reg32) */
/* 468 */	"# return\n",	/* stmt: RETF4(regf) */
/* 469 */	"# return\n",	/* stmt: RETF8(regf) */
/* 470 */	"\tjmp\t%0\n",	/* stmt: JUMPV(albl) */
/* 471 */	"%a:\n",	/* stmt: LABELV */
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
/* 20 */	1,	/* \tpush\t%0\n\tpop\t%c\n */
/* 21 */	1,	/* # emit2\n */
/* 22 */	1,	/* \tpush\t%0\n\tpop\t%c\n */
/* 23 */	1,	/* # emit2\n */
/* 24 */	1,	/* \tmov\t%c,%0\n */
/* 25 */	1,	/* \tmov\t%c,%0\n */
/* 26 */	1,	/* \tCOPY32\t(%c,%0)\n */
/* 27 */	1,	/* \tCOPY32\t(%c,%0)\n */
/* 28 */	1,	/* \tmov\t%c,%0\n */
/* 29 */	1,	/* \tCOPY32\t(%c,%0)\n */
/* 30 */	1,	/* \tCOPY64\t(%c,%0)\n */
/* 31 */	0,	/* %0 */
/* 32 */	0,	/* %0 */
/* 33 */	0,	/* %a */
/* 34 */	0,	/* %a */
/* 35 */	0,	/* %a */
/* 36 */	0,	/* %a */
/* 37 */	0,	/* %a */
/* 38 */	0,	/* %a */
/* 39 */	0,	/* %a */
/* 40 */	0,	/* %a */
/* 41 */	0,	/* %a */
/* 42 */	0,	/* %a */
/* 43 */	0,	/* %a */
/* 44 */	0,	/* %a */
/* 45 */	0,	/* %a */
/* 46 */	0,	/* %a */
/* 47 */	0,	/* %a */
/* 48 */	1,	/* \tld\t%c,%0\n */
/* 49 */	1,	/* \txor\t%c,%c\n */
/* 50 */	1,	/* \tld\t%c,%0\n */
/* 51 */	0,	/* (dp:%a) */
/* 52 */	0,	/* (sp:%a+2+%F) */
/* 53 */	0,	/* (sp:%a+%F) */
/* 54 */	0,	/* %0 */
/* 55 */	0,	/* %a */
/* 56 */	0,	/* (%0:0) */
/* 57 */	0,	/* (%0:%1) */
/* 58 */	0,	/* (%0:-%1) */
/* 59 */	1,	/* ?\tmov\t%c,%0\n\tadd\t%c,%1\n */
/* 60 */	1,	/* ?\tmov\t%c,%0\n\tsub\t%c,%1\n */
/* 61 */	1,	/* \tlea\t%c,%0\n */
/* 62 */	1,	/* \tst\t%0,%1\n */
/* 63 */	1,	/* \tst\t%0,%1\n */
/* 64 */	1,	/* \tst\t%0,%1\n */
/* 65 */	1,	/* \tst\t%0,%1\n */
/* 66 */	1,	/* \tst\t%0,%1\n */
/* 67 */	1,	/* # emit2\n */
/* 68 */	1,	/* \tCOPY32\t(%0,%1)\n */
/* 69 */	1,	/* \tCOPY32\t(%0,%1)\n */
/* 70 */	1,	/* \tCOPY32\t(%0,%1)\n */
/* 71 */	1,	/* \tCOPY32\t(%0,%1)\n */
/* 72 */	1,	/* \tCOPY32\t(%0,%1)\n */
/* 73 */	1,	/* \tCOPY32\t(%0,%1)\n */
/* 74 */	1,	/* \tCOPY64\t(%0,%1)\n */
/* 75 */	1,	/* \tCOPY64\t(%0,%1)\n */
/* 76 */	1,	/* \tld\t%c,%0\n */
/* 77 */	1,	/* \tld\t%c,%0\n */
/* 78 */	1,	/* \tld\t%c,%0\n */
/* 79 */	1,	/* \tld\t%c,%0\n */
/* 80 */	1,	/* \tld\t%c,%0\n */
/* 81 */	1,	/* \tCOPY32\t(%c,%0)\n */
/* 82 */	1,	/* \tCOPY32\t(%c,%0)\n */
/* 83 */	1,	/* \tCOPY32\t(%c,%0)\n */
/* 84 */	1,	/* \tCOPY64\t(%c,%0)\n */
/* 85 */	1,	/* \tmovb\t%c,%0\n */
/* 86 */	1,	/* \tmovb\t%c,%0\n */
/* 87 */	1,	/* \tmovb\t%c,%0\n */
/* 88 */	1,	/* \tmovb\t%c,%0\n */
/* 89 */	1,	/* \tCVI4I1\t(%c,%0)\n */
/* 90 */	1,	/* \tCVI4U1\t(%c,%0)\n */
/* 91 */	1,	/* \tCVU4I1\t(%c,%0)\n */
/* 92 */	1,	/* \tCVU4U1\t(%c,%0)\n */
/* 93 */	1,	/* \tsex\t%c\n */
/* 94 */	1,	/* \tsex\t%c\n */
/* 95 */	1,	/* \tand\t%c,0x00ff\n */
/* 96 */	1,	/* \tand\t%c,0x00ff\n */
/* 97 */	1,	/* \tCVI4I2\t(%c,%0)\n */
/* 98 */	1,	/* \tCVI4U2\t(%c,%0)\n */
/* 99 */	1,	/* \tCVU4I2\t(%c,%0)\n */
/* 100 */	1,	/* \tCVU4U2\t(%c,%0)\n */
/* 101 */	1,	/* \tCVI1I4\t(%c,%0)\n */
/* 102 */	1,	/* \tCVI1U4\t(%c,%0)\n */
/* 103 */	1,	/* \tCVU1I4\t(%c,%0)\n */
/* 104 */	1,	/* \tCVU1U4\t(%c,%0)\n */
/* 105 */	1,	/* \tCVI2I4\t(%c,%0)\n */
/* 106 */	1,	/* \tCVI2U4\t(%c,%0)\n */
/* 107 */	1,	/* \tCVU2I4\t(%c,%0)\n */
/* 108 */	1,	/* \tCVI2U4\t(%c,%0)\n */
/* 109 */	1,	/* \tCVTI1F4\t(%c,%0)\n */
/* 110 */	1,	/* \tCVTI2F4\t(%c,%0)\n */
/* 111 */	1,	/* \tCVTI4F4\t(%c,%0)\n */
/* 112 */	1,	/* \tCVTI1F8\t(%c,%0)\n */
/* 113 */	1,	/* \tCVTI2F8\t(%c,%0)\n */
/* 114 */	1,	/* \tCVTI4F8\t(%c,%0)\n */
/* 115 */	1,	/* \tCVTFI2\t(%c,%0)\n */
/* 116 */	1,	/* \tCVTFI4\t(%c,%0)\n */
/* 117 */	1,	/* \tCVTF8F4\t(%c,%0)\n */
/* 118 */	1,	/* \tCVTF4F8\t(%c,%0)\n */
/* 119 */	1,	/* \tmov\t%c,%0\n */
/* 120 */	1,	/* \tmov\t%c,%0\n */
/* 121 */	1,	/* ?\tmov\t%c,%0\n\tadd\t%c,%1\n */
/* 122 */	1,	/* ?\tmov\t%c,%0\n\tadd\t%c,%1\n */
/* 123 */	1,	/* ?\tmov\t%c,%0\n\tadd\t%c,%1\n */
/* 124 */	1,	/* ?\tmov\t%c,%0\n\tinc\t%c\n */
/* 125 */	1,	/* ?\tmov\t%c,%0\n\tadd\t%c,%1\n */
/* 126 */	1,	/* ?\tmov\t%c,%0\n\tadd\t%c,%1\n */
/* 127 */	1,	/* ?\tmov\t%c,%0\n\tadd\t%c,%1\n */
/* 128 */	1,	/* ?\tmov\t%c,%0\n\tinc\t%c\n */
/* 129 */	1,	/* ?\tmov\t%c,%0\n\tadd\t%c,%1\n */
/* 130 */	1,	/* \tlea\t%c,(%0:%1)\n */
/* 131 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 132 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 133 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 134 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 135 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 136 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 137 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 138 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 139 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 140 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 141 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 142 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 143 */	1,	/* ?\tCOPY32\t(%c,%0)\n\tADDI32\t(%c,%1)\n */
/* 144 */	1,	/* ?\tCOPY32\t(%c,%0)\n\tADDI32\t(%c,%1)\n */
/* 145 */	1,	/* ?\tCOPY32\t(%c,%0)\n\tADDU32\t(%c,%1)\n */
/* 146 */	1,	/* ?\tCOPY32\t(%c,%0)\n\tADDU32\t(%c,%1)\n */
/* 147 */	1,	/* ?\tCOPY32\t(%c,%0)\n\tADDF32\t(%c,%1)\n */
/* 148 */	1,	/* ?\tCOPY32\t(%c,%0)\n\tADDF32\t(%c,%1)\n */
/* 149 */	1,	/* ?\tCOPY64\t(%c,%0)\n\tADDF64\t(%c,%1)\n */
/* 150 */	1,	/* ?\tCOPY64\t(%c,%0)\n\tADDF64\t(%c,%1)\n */
/* 151 */	1,	/* \tCOPY32\t(%0,%1)\n\tADDI32(%0,%2)\n */
/* 152 */	1,	/* \tADDI32\t(%1,%2)\n */
/* 153 */	1,	/* \tCOPY32\t(%0,%1)\n\tADDF32(%0,%2)\n */
/* 154 */	1,	/* \tADDF32\t(%1,%2)\n */
/* 155 */	1,	/* \tCOPY64\t(%0,%1)\n\tADDF64(%0,%2)\n */
/* 156 */	1,	/* \tADDF64\t(%1,%2)\n */
/* 157 */	1,	/* ?\tmov\t%c,%0\n\tsub\t%c,%1\n */
/* 158 */	1,	/* ?\tmov\t%c,%0\n\tsub\t%c,%1\n */
/* 159 */	1,	/* ?\tmov\t%c,%0\n\tsub\t%c,%1\n */
/* 160 */	1,	/* ?\tmov\t%c,%0\n\tdec\t%c\n */
/* 161 */	1,	/* ?\tmov\t%c,%0\n\tsub\t%c,%1\n */
/* 162 */	1,	/* ?\tmov\t%c,%0\n\tsub\t%c,%1\n */
/* 163 */	1,	/* ?\tmov\t%c,%0\n\tsub\t%c,%1\n */
/* 164 */	1,	/* ?\tmov\t%c,%0\n\tdec\t%c\n */
/* 165 */	1,	/* ?\tmov\t%c,%0\n\tsub\t%c,%1\n */
/* 166 */	1,	/* \tlea\t%c,(%0:-%1)\n */
/* 167 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 168 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 169 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 170 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 171 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 172 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 173 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 174 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 175 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 176 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 177 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 178 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 179 */	1,	/* ?\tCOPY32\t(%c,%0)\n\tSUBI32\t(%c,%1)\n */
/* 180 */	1,	/* ?\tCOPY32\t(%c,%0)\n\tSUBI32\t(%c,%1)\n */
/* 181 */	1,	/* ?\tCOPY32\t(%c,%0)\n\tSUBU32\t(%c,%1)\n */
/* 182 */	1,	/* ?\tCOPY32\t(%c,%0)\n\tSUBU32\t(%c,%1)\n */
/* 183 */	1,	/* ?\tCOPY32\t(%c,%0)\n\tSUBF32\t(%c,%1)\n */
/* 184 */	1,	/* ?\tCOPY32\t(%c,%0)\n\tSUBF32\t(%c,%1)\n */
/* 185 */	1,	/* ?\tCOPY64\t(%c,%0)\n\tSUBF64\t(%c,%1)\n */
/* 186 */	1,	/* ?\tCOPY64\t(%c,%0)\n\tSUBF64\t(%c,%1)\n */
/* 187 */	1,	/* \tCOPY32\t(%0,%1)\n\tSUBI32(%0,%2)\n */
/* 188 */	1,	/* \tSUBI32\t(%1,%2)\n */
/* 189 */	1,	/* \tCOPY32\t(%0,%1)\n\tSUBF32(%0,%2)\n */
/* 190 */	1,	/* \tSUBF32\t(%1,%2)\n */
/* 191 */	1,	/* \tCOPY64\t(%0,%1)\n\tSUBF64(%0,%2)\n */
/* 192 */	1,	/* \tSUBF64\t(%1,%2)\n */
/* 193 */	1,	/* \txor\t%c,%c\n\tsub\t%c,%0\n */
/* 194 */	1,	/* \txor\t%c,%c\n\tsub\t%c,%0\n */
/* 195 */	1,	/* \tNEGI32\t(%c,%0)\n */
/* 196 */	1,	/* \tNEGI32\t(%c,%0)\n */
/* 197 */	1,	/* \tNEGF32\t(%c,%0)\n */
/* 198 */	1,	/* \tNEGF32\t(%c,%0)\n */
/* 199 */	1,	/* \tNEGF64\t(%c,%0)\n */
/* 200 */	1,	/* \tNEGF64\t(%c,%0)\n */
/* 201 */	1,	/* ?\tmov\t%c,%0\n\tand\t%c,%1\n */
/* 202 */	1,	/* ?\tmov\t%c,%0\n\tand\t%c,%1\n */
/* 203 */	1,	/* ?\tmov\t%c,%0\n\tand\t%c,%1\n */
/* 204 */	1,	/* ?\tmov\t%c,%0\n\tand\t%c,%1\n */
/* 205 */	1,	/* ?\tmov\t%c,%0\n\tand\t%c,%1\n */
/* 206 */	1,	/* ?\tmov\t%c,%0\n\tand\t%c,%1\n */
/* 207 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 208 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 209 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 210 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 211 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 212 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 213 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 214 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 215 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 216 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 217 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 218 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 219 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tBANDI32\t(%c,%1)\n */
/* 220 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tBANDI32\t(%c,%1)\n */
/* 221 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tBANDI32\t(%c,%1)\n */
/* 222 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tBANDI32\t(%c,%1)\n */
/* 223 */	1,	/* \tmov\t%c,-1\n\txor\t%c,%0\n */
/* 224 */	1,	/* \tmov\t%c,-1\n\txor\t%c,%0\n */
/* 225 */	1,	/* \tBCOMI4\t(%c,%0)\n */
/* 226 */	1,	/* \tBCOMI4\t(%c,%0)\n */
/* 227 */	1,	/* ?\tmov\t%c,%0\n\tor\t%c,%1\n */
/* 228 */	1,	/* ?\tmov\t%c,%0\n\tor\t%c,%1\n */
/* 229 */	1,	/* ?\tmov\t%c,%0\n\tor\t%c,%1\n */
/* 230 */	1,	/* ?\tmov\t%c,%0\n\tor\t%c,%1\n */
/* 231 */	1,	/* ?\tmov\t%c,%0\n\tor\t%c,%1\n */
/* 232 */	1,	/* ?\tmov\t%c,%0\n\tor\t%c,%1\n */
/* 233 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 234 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 235 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 236 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 237 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 238 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 239 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 240 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 241 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 242 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 243 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 244 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 245 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tBORI32\t(%c,%1)\n */
/* 246 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tBORI32\t(%c,%1)\n */
/* 247 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tBORI32\t(%c,%1)\n */
/* 248 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tBORI32\t(%c,%1)\n */
/* 249 */	1,	/* ?\tmov\t%c,%0\n\txor\t%c,%1\n */
/* 250 */	1,	/* ?\tmov\t%c,%0\n\txor\t%c,%1\n */
/* 251 */	1,	/* ?\tmov\t%c,%0\n\txor\t%c,%1\n */
/* 252 */	1,	/* ?\tmov\t%c,%0\n\txor\t%c,%1\n */
/* 253 */	1,	/* ?\tmov\t%c,%0\n\txor\t%c,%1\n */
/* 254 */	1,	/* ?\tmov\t%c,%0\n\txor\t%c,%1\n */
/* 255 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 256 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 257 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 258 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 259 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 260 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 261 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 262 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 263 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 264 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 265 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 266 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 267 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tBXORI32\t(%c,%1)\n */
/* 268 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tBXORI32\t(%c,%1)\n */
/* 269 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tBXORI32\t(%c,%1)\n */
/* 270 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tBXORI32\t(%c,%1)\n */
/* 271 */	1,	/* ?\tmov\t%c,%0\n\tcall\t__muli2\n */
/* 272 */	1,	/* ?\tmov\t%c,%0\n\tcall\t__mulu2\n */
/* 273 */	1,	/* ?\tmov\t%c,%0\n\tcall\t__divi2\n */
/* 274 */	1,	/* ?\tmov\t%c,%0\n\tcall\t__divu2\n */
/* 275 */	1,	/* ?\tmov\t%c,%0\n\tcall\t__modi2\n */
/* 276 */	1,	/* ?\tmov\t%c,%0\n\tcall\t__modu2\n */
/* 277 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tMULI32\t(%c,%1)\n */
/* 278 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tMULI32\t(%c,%1)\n */
/* 279 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tMULU32\t(%c,%1)\n */
/* 280 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tMULU32\t(%c,%1)\n */
/* 281 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tDIVI32\t(%c,%1)\n */
/* 282 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tDIVI32\t(%c,%1)\n */
/* 283 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tDIVU32\t(%c,%1)\n */
/* 284 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tDIVU32\t(%c,%1)\n */
/* 285 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tMODI32\t(%c,%1)\n */
/* 286 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tMODI32\t(%c,%1)\n */
/* 287 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tMODU32\t(%c,%1)\n */
/* 288 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tMODU32\t(%c,%1)\n */
/* 289 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tMULF32\t(%c,%1)\n */
/* 290 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tMULF32\t(%c,%1)\n */
/* 291 */	1,	/* ?\tCOPY64\t%(c,%0)\n\tMULF64\t(%c,%1)\n */
/* 292 */	1,	/* ?\tCOPY64\t%(c,%0)\n\tMULF64\t(%c,%1)\n */
/* 293 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tDIVF32\t(%c,%1)\n */
/* 294 */	1,	/* ?\tCOPY32\t%(c,%0)\n\tDIVF32\t(%c,%1)\n */
/* 295 */	1,	/* ?\tCOPY64\t%(c,%0)\n\tDIVF64\t(%c,%1)\n */
/* 296 */	1,	/* ?\tCOPY64\t%(c,%0)\n\tDIVF64\t(%c,%1)\n */
/* 297 */	1,	/* ?\tmov\t%c,%0\n\tshl\t%0\n */
/* 298 */	1,	/* ?\tmov\t%c,%0\n\tshl\t%0\n */
/* 299 */	1,	/* ?\tmov\t%c,%0\n\tshr\t%0\n */
/* 300 */	1,	/* ?\tmov\t%c,%0\n\tshr\t%0\n */
/* 301 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 302 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 303 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 304 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 305 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 306 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 307 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 308 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 309 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 310 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 311 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 312 */	1,	/* # emit2 (use AH/AL instead of A)\n */
/* 313 */	1,	/* ?\tCOPY32\t(%c,%0)\n\tRSHI32\t(%0)\n */
/* 314 */	1,	/* ?\tCOPY32\t(%c,%0)\n\tRSHU32\t(%0)\n */
/* 315 */	1,	/* \tcmp\t%0,%1\n\tje\t%a\n */
/* 316 */	1,	/* \tcmp\t%0,%1\n\tje\t%a\n */
/* 317 */	1,	/* \tcmp\t%0,%1\n\tje\t%a\n */
/* 318 */	1,	/* \tcmp\t%0,%1\n\tje\t%a\n */
/* 319 */	1,	/* \tcmp\t%0,%1\n\tje\t%a\n */
/* 320 */	1,	/* \tcmp\t%0,%1\n\tje\t%a\n */
/* 321 */	1,	/* \tcmp\t%0,%1\n\tje\t%a\n */
/* 322 */	1,	/* \tcmp\t%0,%1\n\tje\t%a\n */
/* 323 */	1,	/* \tcmp\t%0,%1\n\tje\t%a\n */
/* 324 */	1,	/* \tcmp\t%0,%1\n\tje\t%a\n */
/* 325 */	1,	/* \tcmp\t%0,%1\n\tje\t%a\n */
/* 326 */	1,	/* \tcmp\t%0,%1\n\tje\t%a\n */
/* 327 */	1,	/* \tcmp\t%0,%1\n\tje\t%a\n */
/* 328 */	1,	/* \tcmp\t%0,%1\n\tje\t%a\n */
/* 329 */	1,	/* \tCMP32\t(%0,%1)\n\tje\t%a\n */
/* 330 */	1,	/* \tCMP32\t(%0,%1)\n\tje\t%a\n */
/* 331 */	1,	/* \tCMP32\t(%0,%1)\n\tje\t%a\n */
/* 332 */	1,	/* \tCMP32\t(%0,%1)\n\tje\t%a\n */
/* 333 */	1,	/* \tCMP32\t(%0,%1)\n\tje\t%a\n */
/* 334 */	1,	/* \tCMP32\t(%0,%1)\n\tje\t%a\n */
/* 335 */	1,	/* \tCMP64\t(%0,%1)\n\tje\t%a\n */
/* 336 */	1,	/* \tCMP64\t(%0,%1)\n\tje\t%a\n */
/* 337 */	1,	/* \tcmp\t%0,%1\n\tjne\t%a\n */
/* 338 */	1,	/* \tcmp\t%0,%1\n\tjne\t%a\n */
/* 339 */	1,	/* \tcmp\t%0,%1\n\tjne\t%a\n */
/* 340 */	1,	/* \tcmp\t%0,%1\n\tjne\t%a\n */
/* 341 */	1,	/* \tcmp\t%0,%1\n\tjne\t%a\n */
/* 342 */	1,	/* \tcmp\t%0,%1\n\tjne\t%a\n */
/* 343 */	1,	/* \tcmp\t%0,%1\n\tjne\t%a\n */
/* 344 */	1,	/* \tcmp\t%0,%1\n\tjne\t%a\n */
/* 345 */	1,	/* \tcmp\t%0,%1\n\tjne\t%a\n */
/* 346 */	1,	/* \tcmp\t%0,%1\n\tjne\t%a\n */
/* 347 */	1,	/* \tcmp\t%0,%1\n\tjne\t%a\n */
/* 348 */	1,	/* \tcmp\t%0,%1\n\tjne\t%a\n */
/* 349 */	1,	/* \tcmp\t%0,%1\n\tjne\t%a\n */
/* 350 */	1,	/* \tcmp\t%0,%1\n\tjne\t%a\n */
/* 351 */	1,	/* \tCMP32\t(%0,%1)\n\tjne\t%a\n */
/* 352 */	1,	/* \tCMP32\t(%0,%1)\n\tjne\t%a\n */
/* 353 */	1,	/* \tCMP32\t(%0,%1)\n\tjne\t%a\n */
/* 354 */	1,	/* \tCMP32\t(%0,%1)\n\tjne\t%a\n */
/* 355 */	1,	/* \tCMP32\t(%0,%1)\n\tjne\t%a\n */
/* 356 */	1,	/* \tCMP32\t(%0,%1)\n\tjne\t%a\n */
/* 357 */	1,	/* \tCMP64\t(%0,%1)\n\tjne\t%a\n */
/* 358 */	1,	/* \tCMP64\t(%0,%1)\n\tjne\t%a\n */
/* 359 */	1,	/* \tcmp\t%0,%1\n\tjle\t%a\n */
/* 360 */	1,	/* \tcmp\t%0,%1\n\tjle\t%a\n */
/* 361 */	1,	/* \tcmp\t%0,%1\n\tjle\t%a\n */
/* 362 */	1,	/* \tcmp\t%0,%1\n\tjle\t%a\n */
/* 363 */	1,	/* \tcmp\t%0,%1\n\tjle\t%a\n */
/* 364 */	1,	/* \tcmp\t%0,%1\n\tjle\t%a\n */
/* 365 */	1,	/* \tcmp\t%0,%1\n\tjle\t%a\n */
/* 366 */	1,	/* \tcmp\t%0,%1\n\tjleu\t%a\n */
/* 367 */	1,	/* \tcmp\t%0,%1\n\tjleu\t%a\n */
/* 368 */	1,	/* \tcmp\t%0,%1\n\tjleu\t%a\n */
/* 369 */	1,	/* \tcmp\t%0,%1\n\tjleu\t%a\n */
/* 370 */	1,	/* \tcmp\t%0,%1\n\tjleu\t%a\n */
/* 371 */	1,	/* \tcmp\t%0,%1\n\tjleu\t%a\n */
/* 372 */	1,	/* \tcmp\t%0,%1\n\tjleu\t%a\n */
/* 373 */	1,	/* \tCMP32\t(%0,%1)\n\tjle\t%a\n */
/* 374 */	1,	/* \tCMP32\t(%0,%1)\n\tjle\t%a\n */
/* 375 */	1,	/* \tCMP32\t(%0,%1)\n\tjleu\t%a\n */
/* 376 */	1,	/* \tCMP32\t(%0,%1)\n\tjleu\t%a\n */
/* 377 */	1,	/* \tCMP32\t(%0,%1)\n\tjle\t%a\n */
/* 378 */	1,	/* \tCMP32\t(%0,%1)\n\tjle\t%a\n */
/* 379 */	1,	/* \tCMP64\t(%0,%1)\n\tjle\t%a\n */
/* 380 */	1,	/* \tCMP64\t(%0,%1)\n\tjle\t%a\n */
/* 381 */	1,	/* \tcmp\t%0,%1\n\tjl\t%a\n */
/* 382 */	1,	/* \tcmp\t%0,%1\n\tjl\t%a\n */
/* 383 */	1,	/* \tcmp\t%0,%1\n\tjl\t%a\n */
/* 384 */	1,	/* \tcmp\t%0,%1\n\tjl\t%a\n */
/* 385 */	1,	/* \tcmp\t%0,%1\n\tjl\t%a\n */
/* 386 */	1,	/* \tcmp\t%0,%1\n\tjl\t%a\n */
/* 387 */	1,	/* \tcmp\t%0,%1\n\tjl\t%a\n */
/* 388 */	1,	/* \tcmp\t%0,%1\n\tjlu\t%a\n */
/* 389 */	1,	/* \tcmp\t%0,%1\n\tjlu\t%a\n */
/* 390 */	1,	/* \tcmp\t%0,%1\n\tjlu\t%a\n */
/* 391 */	1,	/* \tcmp\t%0,%1\n\tjlu\t%a\n */
/* 392 */	1,	/* \tcmp\t%0,%1\n\tjlu\t%a\n */
/* 393 */	1,	/* \tcmp\t%0,%1\n\tjlu\t%a\n */
/* 394 */	1,	/* \tcmp\t%0,%1\n\tjlu\t%a\n */
/* 395 */	1,	/* \tCMP32\t(%0,%1)\n\tjlt\t%a\n */
/* 396 */	1,	/* \tCMP32\t(%0,%1)\n\tjlt\t%a\n */
/* 397 */	1,	/* \tCMP32\t(%0,%1)\n\tjltu\t%a\n */
/* 398 */	1,	/* \tCMP32\t(%0,%1)\n\tjltu\t%a\n */
/* 399 */	1,	/* \tCMP32\t(%0,%1)\n\tjlt\t%a\n */
/* 400 */	1,	/* \tCMP32\t(%0,%1)\n\tjlt\t%a\n */
/* 401 */	1,	/* \tCMP64\t(%0,%1)\n\tjlt\t%a\n */
/* 402 */	1,	/* \tCMP64\t(%0,%1)\n\tjlt\t%a\n */
/* 403 */	1,	/* \tcmp\t%0,%1\n\tjge\t%a\n */
/* 404 */	1,	/* \tcmp\t%0,%1\n\tjge\t%a\n */
/* 405 */	1,	/* \tcmp\t%0,%1\n\tjge\t%a\n */
/* 406 */	1,	/* \tcmp\t%0,%1\n\tjge\t%a\n */
/* 407 */	1,	/* \tcmp\t%0,%1\n\tjge\t%a\n */
/* 408 */	1,	/* \tcmp\t%0,%1\n\tjge\t%a\n */
/* 409 */	1,	/* \tcmp\t%0,%1\n\tjge\t%a\n */
/* 410 */	1,	/* \tcmp\t%0,%1\n\tjgeu\t%a\n */
/* 411 */	1,	/* \tcmp\t%0,%1\n\tjgeu\t%a\n */
/* 412 */	1,	/* \tcmp\t%0,%1\n\tjgeu\t%a\n */
/* 413 */	1,	/* \tcmp\t%0,%1\n\tjgeu\t%a\n */
/* 414 */	1,	/* \tcmp\t%0,%1\n\tjgeu\t%a\n */
/* 415 */	1,	/* \tcmp\t%0,%1\n\tjgeu\t%a\n */
/* 416 */	1,	/* \tcmp\t%0,%1\n\tjgeu\t%a\n */
/* 417 */	1,	/* \tCMP32\t(%0,%1)\n\tjge\t%a\n */
/* 418 */	1,	/* \tCMP32\t(%0,%1)\n\tjge\t%a\n */
/* 419 */	1,	/* \tCMP32\t(%0,%1)\n\tjgeu\t%a\n */
/* 420 */	1,	/* \tCMP32\t(%0,%1)\n\tjgeu\t%a\n */
/* 421 */	1,	/* \tCMP32\t(%0,%1)\n\tjge\t%a\n */
/* 422 */	1,	/* \tCMP32\t(%0,%1)\n\tjge\t%a\n */
/* 423 */	1,	/* \tCMP64\t(%0,%1)\n\tjge\t%a\n */
/* 424 */	1,	/* \tCMP64\t(%0,%1)\n\tjge\t%a\n */
/* 425 */	1,	/* \tcmp\t%0,%1\n\tjg\t%a\n */
/* 426 */	1,	/* \tcmp\t%0,%1\n\tjg\t%a\n */
/* 427 */	1,	/* \tcmp\t%0,%1\n\tjg\t%a\n */
/* 428 */	1,	/* \tcmp\t%0,%1\n\tjg\t%a\n */
/* 429 */	1,	/* \tcmp\t%0,%1\n\tjg\t%a\n */
/* 430 */	1,	/* \tcmp\t%0,%1\n\tjg\t%a\n */
/* 431 */	1,	/* \tcmp\t%0,%1\n\tjg\t%a\n */
/* 432 */	1,	/* \tcmp\t%0,%1\n\tjgu\t%a\n */
/* 433 */	1,	/* \tcmp\t%0,%1\n\tjgu\t%a\n */
/* 434 */	1,	/* \tcmp\t%0,%1\n\tjgu\t%a\n */
/* 435 */	1,	/* \tcmp\t%0,%1\n\tjgu\t%a\n */
/* 436 */	1,	/* \tcmp\t%0,%1\n\tjgu\t%a\n */
/* 437 */	1,	/* \tcmp\t%0,%1\n\tjgu\t%a\n */
/* 438 */	1,	/* \tcmp\t%0,%1\n\tjgu\t%a\n */
/* 439 */	1,	/* \tCMP32\t(%0,%1)\n\tjg\t%a\n */
/* 440 */	1,	/* \tCMP32\t(%0,%1)\n\tjg\t%a\n */
/* 441 */	1,	/* \tCMP32\t(%0,%1)\n\tjgu\t%a\n */
/* 442 */	1,	/* \tCMP32\t(%0,%1)\n\tjgu\t%a\n */
/* 443 */	1,	/* \tCMP32\t(%0,%1)\n\tjg\t%a\n */
/* 444 */	1,	/* \tCMP32\t(%0,%1)\n\tjg\t%a\n */
/* 445 */	1,	/* \tCMP64\t(%0,%1)\n\tjg\t%a\n */
/* 446 */	1,	/* \tCMP64\t(%0,%1)\n\tjg\t%a\n */
/* 447 */	1,	/* # emit2\n */
/* 448 */	1,	/* # emit2\n */
/* 449 */	1,	/* # emit2\n */
/* 450 */	1,	/* # emit2\n */
/* 451 */	1,	/* # emit2\n */
/* 452 */	1,	/* # emit2\n */
/* 453 */	1,	/* # emit2\n */
/* 454 */	1,	/* \tcall\t%0\n */
/* 455 */	1,	/* \tcall\t%0\n */
/* 456 */	1,	/* \tcall\t%0\n */
/* 457 */	1,	/* \tcall\t%0\n */
/* 458 */	1,	/* # emit2\n */
/* 459 */	1,	/* # emit2\n */
/* 460 */	1,	/* # emit2\n */
/* 461 */	1,	/* \tlea\ta,%c\n\tcall\t%0\n */
/* 462 */	1,	/* # return\n */
/* 463 */	1,	/* # return\n */
/* 464 */	1,	/* # return\n */
/* 465 */	1,	/* # return\n */
/* 466 */	1,	/* # return\n */
/* 467 */	1,	/* # return\n */
/* 468 */	1,	/* # return\n */
/* 469 */	1,	/* # return\n */
/* 470 */	1,	/* \tjmp\t%0\n */
/* 471 */	1,	/* %a:\n */
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
/* 19 */	"stmt: reg",
/* 20 */	"reg8: LOADI1(reg8)",
/* 21 */	"reg8: LOADI1(reg)",
/* 22 */	"reg8: LOADU1(reg8)",
/* 23 */	"reg8: LOADU1(reg)",
/* 24 */	"reg: LOADI2(reg)",
/* 25 */	"reg: LOADU2(reg)",
/* 26 */	"reg32: LOADI4(reg32)",
/* 27 */	"reg32: LOADU4(reg32)",
/* 28 */	"reg: LOADP2(reg)",
/* 29 */	"regf: LOADF4(regf)",
/* 30 */	"regf: LOADF8(regf)",
/* 31 */	"reg8: LOADU1(LOADU2(CVII2(reg8)))",
/* 32 */	"reg8: LOADI1(LOADI2(CVUU2(reg8)))",
/* 33 */	"con8: CNSTI1",
/* 34 */	"con8: CNSTU1",
/* 35 */	"con16: CNSTI2",
/* 36 */	"con16: CNSTU2",
/* 37 */	"con16: CNSTP2",
/* 38 */	"con0: CNSTI1",
/* 39 */	"con0: CNSTU1",
/* 40 */	"con0: CNSTI2",
/* 41 */	"con0: CNSTU2",
/* 42 */	"con1: CNSTI1",
/* 43 */	"con1: CNSTU1",
/* 44 */	"con1: CNSTI2",
/* 45 */	"con1: CNSTU2",
/* 46 */	"con: con8",
/* 47 */	"con: con16",
/* 48 */	"reg: con",
/* 49 */	"reg: con0",
/* 50 */	"reg8: con8",
/* 51 */	"lgaddr: ADDRGP2",
/* 52 */	"lgaddr: ADDRFP2",
/* 53 */	"lgaddr: ADDRLP2",
/* 54 */	"addr: lgaddr",
/* 55 */	"albl: ADDRGP2",
/* 56 */	"addr: reg",
/* 57 */	"addr: ADDP2(reg,con)",
/* 58 */	"addr: SUBP2(reg,con)",
/* 59 */	"reg: ADDP2(reg,con)",
/* 60 */	"reg: SUBP2(reg,con)",
/* 61 */	"reg: lgaddr",
/* 62 */	"stmt: ASGNI1(addr,reg8)",
/* 63 */	"stmt: ASGNU1(addr,reg8)",
/* 64 */	"stmt: ASGNI2(addr,reg)",
/* 65 */	"stmt: ASGNU2(addr,reg)",
/* 66 */	"stmt: ASGNP2(addr,reg)",
/* 67 */	"stmt: ASGNB(reg,INDIRB(reg))",
/* 68 */	"stmt: ASGNI4(addr,reg32)",
/* 69 */	"stmt: ASGNI4(addr,INDIRI4(addr))",
/* 70 */	"stmt: ASGNU4(addr,reg32)",
/* 71 */	"stmt: ASGNU4(addr,INDIRU4(addr))",
/* 72 */	"stmt: ASGNF4(addr,regf)",
/* 73 */	"stmt: ASGNF4(addr,INDIRF4(addr))",
/* 74 */	"stmt: ASGNF8(addr,regf)",
/* 75 */	"stmt: ASGNF8(addr,INDIRF8(addr))",
/* 76 */	"reg8: INDIRI1(addr)",
/* 77 */	"reg8: INDIRU1(addr)",
/* 78 */	"reg: INDIRI2(addr)",
/* 79 */	"reg: INDIRU2(addr)",
/* 80 */	"reg: INDIRP2(addr)",
/* 81 */	"reg32: INDIRI4(addr)",
/* 82 */	"reg32: INDIRU4(addr)",
/* 83 */	"regf: INDIRF4(addr)",
/* 84 */	"regf: INDIRF8(addr)",
/* 85 */	"reg8: CVII1(reg)",
/* 86 */	"reg8: CVIU1(reg)",
/* 87 */	"reg8: CVUI1(reg)",
/* 88 */	"reg8: CVUU1(reg)",
/* 89 */	"reg8: CVII1(reg32)",
/* 90 */	"reg8: CVIU1(reg32)",
/* 91 */	"reg8: CVUI1(reg32)",
/* 92 */	"reg8: CVUU1(reg32)",
/* 93 */	"reg: CVII2(reg8)",
/* 94 */	"reg: CVIU2(reg8)",
/* 95 */	"reg: CVUI2(reg8)",
/* 96 */	"reg: CVUU2(reg8)",
/* 97 */	"reg: CVII2(reg32)",
/* 98 */	"reg: CVIU2(reg32)",
/* 99 */	"reg: CVUI2(reg32)",
/* 100 */	"reg: CVUU2(reg32)",
/* 101 */	"reg32: CVII4(reg8)",
/* 102 */	"reg32: CVIU4(reg8)",
/* 103 */	"reg32: CVUI4(reg8)",
/* 104 */	"reg32: CVUU4(reg8)",
/* 105 */	"reg32: CVII4(reg)",
/* 106 */	"reg32: CVIU4(reg)",
/* 107 */	"reg32: CVUI4(reg)",
/* 108 */	"reg32: CVUU4(reg)",
/* 109 */	"regf: CVIF4(reg8)",
/* 110 */	"regf: CVIF4(reg)",
/* 111 */	"regf: CVIF4(reg32)",
/* 112 */	"regf: CVIF8(reg8)",
/* 113 */	"regf: CVIF8(reg)",
/* 114 */	"regf: CVIF8(reg32)",
/* 115 */	"reg: CVFI2(regf)",
/* 116 */	"reg: CVFI4(regf)",
/* 117 */	"regf: CVFF4(regf)",
/* 118 */	"regf: CVFF8(regf)",
/* 119 */	"reg: CVPU2(reg)",
/* 120 */	"reg: CVUP2(reg)",
/* 121 */	"reg: ADDI2(reg,reg)",
/* 122 */	"reg: ADDI2(reg,INDIRI2(addr))",
/* 123 */	"reg: ADDI2(reg,con)",
/* 124 */	"reg: ADDI2(reg,con1)",
/* 125 */	"reg: ADDU2(reg,reg)",
/* 126 */	"reg: ADDU2(reg,INDIRU2(addr))",
/* 127 */	"reg: ADDU2(reg,con)",
/* 128 */	"reg: ADDU2(reg,con1)",
/* 129 */	"reg: ADDP2(reg,reg)",
/* 130 */	"reg: ADDP2(reg,con)",
/* 131 */	"reg8: ADDI2(reg8,CVII2(INDIRI1(addr)))",
/* 132 */	"reg8: ADDI2(CVII2(reg8),CVII2(INDIRI1(addr)))",
/* 133 */	"reg8: ADDI2(CVUI2(reg8),CVII2(INDIRI1(addr)))",
/* 134 */	"reg8: ADDI2(reg8,con)",
/* 135 */	"reg8: ADDI2(CVII2(reg8),con)",
/* 136 */	"reg8: ADDI2(CVUI2(reg8),con)",
/* 137 */	"reg8: ADDU2(reg8,CVUU2(INDIRU1(addr)))",
/* 138 */	"reg8: ADDU2(CVUU2(reg8),CVUU2(INDIRU1(addr)))",
/* 139 */	"reg8: ADDU2(CVIU2(reg8),CVUU2(INDIRU1(addr)))",
/* 140 */	"reg8: ADDU2(reg8,con)",
/* 141 */	"reg8: ADDU2(CVUU2(reg8),con)",
/* 142 */	"reg8: ADDU2(CVIU2(reg8),con)",
/* 143 */	"reg32: ADDI4(reg32,reg32)",
/* 144 */	"reg32: ADDI4(reg32,INDIRI4(addr))",
/* 145 */	"reg32: ADDU4(reg32,reg32)",
/* 146 */	"reg32: ADDU4(reg32,INDIRU4(addr))",
/* 147 */	"regf: ADDF4(regf,regf)",
/* 148 */	"regf: ADDF4(regf,INDIRF4(addr))",
/* 149 */	"regf: ADDF8(regf,regf)",
/* 150 */	"regf: ADDF8(regf,INDIRF8(addr))",
/* 151 */	"stmt: ASGNI4(addr,ADDI4(INDIRI4(addr),INDIRI4(addr)))",
/* 152 */	"stmt: ASGNI4(addr,ADDI4(INDIRI4(addr),INDIRI4(addr)))",
/* 153 */	"stmt: ASGNF4(addr,ADDF4(INDIRF4(addr),INDIRF4(addr)))",
/* 154 */	"stmt: ASGNF4(addr,ADDF4(INDIRF4(addr),INDIRF4(addr)))",
/* 155 */	"stmt: ASGNF8(addr,ADDF8(INDIRF8(addr),INDIRF8(addr)))",
/* 156 */	"stmt: ASGNF8(addr,ADDF8(INDIRF8(addr),INDIRF8(addr)))",
/* 157 */	"reg: SUBI2(reg,reg)",
/* 158 */	"reg: SUBI2(reg,INDIRI2(addr))",
/* 159 */	"reg: SUBI2(reg,con)",
/* 160 */	"reg: SUBI2(reg,con1)",
/* 161 */	"reg: SUBU2(reg,reg)",
/* 162 */	"reg: SUBU2(reg,INDIRU2(addr))",
/* 163 */	"reg: SUBU2(reg,con)",
/* 164 */	"reg: SUBU2(reg,con1)",
/* 165 */	"reg: SUBP2(reg,reg)",
/* 166 */	"reg: ADDP2(reg,con)",
/* 167 */	"reg8: SUBI2(reg8,CVII2(INDIRI1(addr)))",
/* 168 */	"reg8: SUBI2(CVII2(reg8),CVII2(INDIRI1(addr)))",
/* 169 */	"reg8: SUBI2(CVUI2(reg8),CVII2(INDIRI1(addr)))",
/* 170 */	"reg8: SUBI2(reg8,con)",
/* 171 */	"reg8: SUBI2(CVII2(reg8),con)",
/* 172 */	"reg8: SUBI2(CVUI2(reg8),con)",
/* 173 */	"reg8: SUBU2(reg8,CVUU2(INDIRU1(addr)))",
/* 174 */	"reg8: SUBU2(CVUU2(reg8),CVUU2(INDIRU1(addr)))",
/* 175 */	"reg8: SUBU2(CVIU2(reg8),CVUU2(INDIRU1(addr)))",
/* 176 */	"reg8: SUBU2(reg8,con)",
/* 177 */	"reg8: SUBU2(CVUU2(reg8),con)",
/* 178 */	"reg8: SUBU2(CVIU2(reg8),con)",
/* 179 */	"reg32: SUBI4(reg32,reg32)",
/* 180 */	"reg32: SUBI4(reg32,INDIRI4(addr))",
/* 181 */	"reg32: SUBU4(reg32,reg32)",
/* 182 */	"reg32: SUBU4(reg32,INDIRU4(addr))",
/* 183 */	"regf: SUBF4(regf,regf)",
/* 184 */	"regf: SUBF4(regf,INDIRF4(addr))",
/* 185 */	"regf: SUBF8(regf,regf)",
/* 186 */	"regf: SUBF8(regf,INDIRF8(addr))",
/* 187 */	"stmt: ASGNI4(addr,SUBI4(INDIRI4(addr),INDIRI4(addr)))",
/* 188 */	"stmt: ASGNI4(addr,SUBI4(INDIRI4(addr),INDIRI4(addr)))",
/* 189 */	"stmt: ASGNF4(addr,SUBF4(INDIRF4(addr),INDIRF4(addr)))",
/* 190 */	"stmt: ASGNF4(addr,SUBF4(INDIRF4(addr),INDIRF4(addr)))",
/* 191 */	"stmt: ASGNF8(addr,SUBF8(INDIRF8(addr),INDIRF8(addr)))",
/* 192 */	"stmt: ASGNF8(addr,SUBF8(INDIRF8(addr),INDIRF8(addr)))",
/* 193 */	"reg: NEGI2(reg)",
/* 194 */	"reg: NEGI2(INDIRI2(addr))",
/* 195 */	"reg32: NEGI4(reg32)",
/* 196 */	"reg32: NEGI4(INDIRI4(addr))",
/* 197 */	"regf: NEGF4(regf)",
/* 198 */	"regf: NEGF4(INDIRF4(addr))",
/* 199 */	"regf: NEGF8(regf)",
/* 200 */	"regf: NEGF8(INDIRF8(addr))",
/* 201 */	"reg: BANDI2(reg,reg)",
/* 202 */	"reg: BANDI2(reg,INDIRI2(lgaddr))",
/* 203 */	"reg: BANDI2(reg,con)",
/* 204 */	"reg: BANDU2(reg,reg)",
/* 205 */	"reg: BANDU2(reg,INDIRU2(lgaddr))",
/* 206 */	"reg: BANDU2(reg,con)",
/* 207 */	"reg8: BANDI2(reg8,CVII2(INDIRI1(lgaddr)))",
/* 208 */	"reg8: BANDI2(CVII2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 209 */	"reg8: BANDI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 210 */	"reg8: BANDI2(reg8,con)",
/* 211 */	"reg8: BANDI2(CVII2(reg8),con)",
/* 212 */	"reg8: BANDI2(CVUI2(reg8),con)",
/* 213 */	"reg8: BANDU2(reg8,CVUU2(INDIRU1(lgaddr)))",
/* 214 */	"reg8: BANDU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 215 */	"reg8: BANDU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 216 */	"reg8: BANDU2(reg8,con)",
/* 217 */	"reg8: BANDU2(CVUU2(reg8),con)",
/* 218 */	"reg8: BANDU2(CVIU2(reg8),con)",
/* 219 */	"reg32: BANDI4(reg32,reg32)",
/* 220 */	"reg32: BANDI4(reg32,INDIRI4(addr))",
/* 221 */	"reg32: BANDU4(reg32,reg32)",
/* 222 */	"reg32: BANDU4(reg32,INDIRU4(addr))",
/* 223 */	"reg: BCOMI2(reg)",
/* 224 */	"reg: BCOMU2(reg)",
/* 225 */	"reg32: BCOMI4(reg32)",
/* 226 */	"reg32: BCOMU4(reg32)",
/* 227 */	"reg: BORI2(reg,reg)",
/* 228 */	"reg: BORI2(reg,INDIRI2(lgaddr))",
/* 229 */	"reg: BORI2(reg,con)",
/* 230 */	"reg: BORU2(reg,reg)",
/* 231 */	"reg: BORU2(reg,INDIRU2(lgaddr))",
/* 232 */	"reg: BORU2(reg,con)",
/* 233 */	"reg8: BORI2(reg8,CVII2(INDIRI1(lgaddr)))",
/* 234 */	"reg8: BORI2(CVII2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 235 */	"reg8: BORI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 236 */	"reg8: BORI2(reg8,con)",
/* 237 */	"reg8: BORI2(CVII2(reg8),con)",
/* 238 */	"reg8: BORI2(CVUI2(reg8),con)",
/* 239 */	"reg8: BORU2(reg8,CVUU2(INDIRU1(lgaddr)))",
/* 240 */	"reg8: BORU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 241 */	"reg8: BORU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 242 */	"reg8: BORU2(reg8,con)",
/* 243 */	"reg8: BORU2(CVUU2(reg8),con)",
/* 244 */	"reg8: BORU2(CVIU2(reg8),con)",
/* 245 */	"reg32: BORI4(reg32,reg32)",
/* 246 */	"reg32: BORI4(reg32,INDIRI4(addr))",
/* 247 */	"reg32: BORU4(reg32,reg32)",
/* 248 */	"reg32: BORU4(reg32,INDIRU4(addr))",
/* 249 */	"reg: BXORI2(reg,reg)",
/* 250 */	"reg: BXORI2(reg,INDIRI2(lgaddr))",
/* 251 */	"reg: BXORI2(reg,con)",
/* 252 */	"reg: BXORU2(reg,reg)",
/* 253 */	"reg: BXORU2(reg,INDIRU2(lgaddr))",
/* 254 */	"reg: BXORU2(reg,con)",
/* 255 */	"reg8: BXORI2(reg8,CVII2(INDIRI1(lgaddr)))",
/* 256 */	"reg8: BXORI2(CVII2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 257 */	"reg8: BXORI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 258 */	"reg8: BXORI2(reg8,con)",
/* 259 */	"reg8: BXORI2(CVII2(reg8),con)",
/* 260 */	"reg8: BXORI2(CVUI2(reg8),con)",
/* 261 */	"reg8: BXORU2(reg8,CVUU2(INDIRU1(lgaddr)))",
/* 262 */	"reg8: BXORU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 263 */	"reg8: BXORU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 264 */	"reg8: BXORU2(reg8,con)",
/* 265 */	"reg8: BXORU2(CVUU2(reg8),con)",
/* 266 */	"reg8: BXORU2(CVIU2(reg8),con)",
/* 267 */	"reg32: BXORI4(reg32,reg32)",
/* 268 */	"reg32: BXORI4(reg32,INDIRI4(addr))",
/* 269 */	"reg32: BXORU4(reg32,reg32)",
/* 270 */	"reg32: BXORU4(reg32,INDIRU4(addr))",
/* 271 */	"reg: MULI2(reg,reg)",
/* 272 */	"reg: MULU2(reg,reg)",
/* 273 */	"reg: DIVI2(reg,reg)",
/* 274 */	"reg: DIVU2(reg,reg)",
/* 275 */	"reg: MODI2(reg,reg)",
/* 276 */	"reg: MODU2(reg,reg)",
/* 277 */	"reg32: MULI4(reg32,reg32)",
/* 278 */	"reg32: MULI4(reg32,INDIRI4(addr))",
/* 279 */	"reg32: MULU4(reg32,reg32)",
/* 280 */	"reg32: MULU4(reg32,INDIRU4(addr))",
/* 281 */	"reg32: DIVI4(reg32,reg32)",
/* 282 */	"reg32: DIVI4(reg32,INDIRI4(addr))",
/* 283 */	"reg32: DIVU4(reg32,reg32)",
/* 284 */	"reg32: DIVU4(reg32,INDIRU4(addr))",
/* 285 */	"reg32: MODI4(reg32,reg32)",
/* 286 */	"reg32: MODI4(reg32,INDIRI4(addr))",
/* 287 */	"reg32: MODU4(reg32,reg32)",
/* 288 */	"reg32: MODU4(reg32,INDIRU4(addr))",
/* 289 */	"regf: MULF4(regf,regf)",
/* 290 */	"regf: MULF4(regf,INDIRF4(addr))",
/* 291 */	"regf: MULF8(regf,regf)",
/* 292 */	"regf: MULF8(regf,INDIRF8(addr))",
/* 293 */	"regf: DIVF4(regf,regf)",
/* 294 */	"regf: DIVF4(regf,INDIRF4(addr))",
/* 295 */	"regf: DIVF8(regf,regf)",
/* 296 */	"regf: DIVF8(regf,INDIRF8(addr))",
/* 297 */	"reg: LSHI2(reg,con1)",
/* 298 */	"reg: LSHU2(reg,con1)",
/* 299 */	"reg: RSHI2(reg,con1)",
/* 300 */	"reg: RSHU2(reg,con1)",
/* 301 */	"reg8: LSHI2(reg8,con)",
/* 302 */	"reg8: LSHI2(CVII2(reg8),con)",
/* 303 */	"reg8: LSHI2(CVUI2(reg8),con)",
/* 304 */	"reg8: LSHU2(reg8,con)",
/* 305 */	"reg8: LSHU2(CVUU2(reg8),con)",
/* 306 */	"reg8: LSHU2(CVIU2(reg8),con)",
/* 307 */	"reg8: RSHI2(reg8,con)",
/* 308 */	"reg8: RSHI2(CVII2(reg8),con)",
/* 309 */	"reg8: RSHI2(CVUI2(reg8),con)",
/* 310 */	"reg8: RSHU2(reg8,con)",
/* 311 */	"reg8: RSHU2(CVUU2(reg8),con)",
/* 312 */	"reg8: RSHU2(CVIU2(reg8),con)",
/* 313 */	"reg32: RSHI4(reg32,con1)",
/* 314 */	"reg32: RSHU4(reg32,con1)",
/* 315 */	"stmt: EQI2(reg,reg)",
/* 316 */	"stmt: EQI2(reg,INDIRI2(lgaddr))",
/* 317 */	"stmt: EQI2(reg,con)",
/* 318 */	"stmt: EQI2(CVII2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 319 */	"stmt: EQI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 320 */	"stmt: EQI2(CVII2(reg8),con)",
/* 321 */	"stmt: EQI2(CVUI2(reg8),con)",
/* 322 */	"stmt: EQU2(reg,reg)",
/* 323 */	"stmt: EQU2(reg,INDIRU2(lgaddr))",
/* 324 */	"stmt: EQU2(reg,con)",
/* 325 */	"stmt: EQU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 326 */	"stmt: EQU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 327 */	"stmt: EQU2(CVUU2(reg8),con)",
/* 328 */	"stmt: EQU2(CVIU2(reg8),con)",
/* 329 */	"stmt: EQI4(reg32,reg32)",
/* 330 */	"stmt: EQI4(reg32,INDIRI4(addr))",
/* 331 */	"stmt: EQU4(reg32,reg32)",
/* 332 */	"stmt: EQU4(reg32,INDIRU4(addr))",
/* 333 */	"stmt: EQF4(regf,regf)",
/* 334 */	"stmt: EQF4(regf,INDIRF4(addr))",
/* 335 */	"stmt: EQF8(regf,regf)",
/* 336 */	"stmt: EQF8(regf,INDIRF8(addr))",
/* 337 */	"stmt: NEI2(reg,reg)",
/* 338 */	"stmt: NEI2(reg,INDIRI2(reg))",
/* 339 */	"stmt: NEI2(reg,con)",
/* 340 */	"stmt: NEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 341 */	"stmt: NEI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 342 */	"stmt: NEI2(CVII2(reg8),con)",
/* 343 */	"stmt: NEI2(CVUI2(reg8),con)",
/* 344 */	"stmt: NEU2(reg,reg)",
/* 345 */	"stmt: NEU2(reg,INDIRU2(reg))",
/* 346 */	"stmt: NEU2(reg,con)",
/* 347 */	"stmt: NEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 348 */	"stmt: NEU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 349 */	"stmt: NEU2(CVUU2(reg8),con)",
/* 350 */	"stmt: NEU2(CVIU2(reg8),con)",
/* 351 */	"stmt: NEI4(reg32,reg32)",
/* 352 */	"stmt: NEI4(reg32,INDIRI4(addr))",
/* 353 */	"stmt: NEU4(reg32,reg32)",
/* 354 */	"stmt: NEU4(reg32,INDIRU4(addr))",
/* 355 */	"stmt: NEF4(regf,regf)",
/* 356 */	"stmt: NEF4(regf,INDIRF4(addr))",
/* 357 */	"stmt: NEF8(regf,regf)",
/* 358 */	"stmt: NEF8(regf,INDIRF8(addr))",
/* 359 */	"stmt: LEI2(reg,reg)",
/* 360 */	"stmt: LEI2(reg,INDIRI2(reg))",
/* 361 */	"stmt: LEI2(reg,con)",
/* 362 */	"stmt: LEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 363 */	"stmt: LEI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 364 */	"stmt: LEI2(CVII2(reg8),con)",
/* 365 */	"stmt: LEI2(CVUI2(reg8),con)",
/* 366 */	"stmt: LEU2(reg,reg)",
/* 367 */	"stmt: LEU2(reg,INDIRU2(reg))",
/* 368 */	"stmt: LEU2(reg,con)",
/* 369 */	"stmt: LEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 370 */	"stmt: LEU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 371 */	"stmt: LEU2(CVUU2(reg8),con)",
/* 372 */	"stmt: LEU2(CVIU2(reg8),con)",
/* 373 */	"stmt: LEI4(reg32,reg32)",
/* 374 */	"stmt: LEI4(reg32,INDIRI4(addr))",
/* 375 */	"stmt: LEU4(reg32,reg32)",
/* 376 */	"stmt: LEU4(reg32,INDIRU4(addr))",
/* 377 */	"stmt: LEF4(regf,regf)",
/* 378 */	"stmt: LEF4(regf,INDIRF4(addr))",
/* 379 */	"stmt: LEF8(regf,regf)",
/* 380 */	"stmt: LEF8(regf,INDIRF8(addr))",
/* 381 */	"stmt: LTI2(reg,reg)",
/* 382 */	"stmt: LTI2(reg,INDIRI2(reg))",
/* 383 */	"stmt: LTI2(reg,con)",
/* 384 */	"stmt: LTI2(CVII2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 385 */	"stmt: LTI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 386 */	"stmt: LTI2(CVII2(reg8),con)",
/* 387 */	"stmt: LTI2(CVUI2(reg8),con)",
/* 388 */	"stmt: LTU2(reg,reg)",
/* 389 */	"stmt: LTU2(reg,INDIRU2(reg))",
/* 390 */	"stmt: LTU2(reg,con)",
/* 391 */	"stmt: LTU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 392 */	"stmt: LTU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 393 */	"stmt: LTU2(CVUU2(reg8),con)",
/* 394 */	"stmt: LTU2(CVIU2(reg8),con)",
/* 395 */	"stmt: LTI4(reg32,reg32)",
/* 396 */	"stmt: LTI4(reg32,INDIRI4(addr))",
/* 397 */	"stmt: LTU4(reg32,reg32)",
/* 398 */	"stmt: LTU4(reg32,INDIRU4(addr))",
/* 399 */	"stmt: LTF4(regf,regf)",
/* 400 */	"stmt: LTF4(regf,INDIRF4(addr))",
/* 401 */	"stmt: LTF8(regf,regf)",
/* 402 */	"stmt: LTF8(regf,INDIRF8(addr))",
/* 403 */	"stmt: GEI2(reg,reg)",
/* 404 */	"stmt: GEI2(reg,INDIRI2(reg))",
/* 405 */	"stmt: GEI2(reg,con)",
/* 406 */	"stmt: GEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 407 */	"stmt: GEI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 408 */	"stmt: GEI2(CVII2(reg8),con)",
/* 409 */	"stmt: GEI2(CVUI2(reg8),con)",
/* 410 */	"stmt: GEU2(reg,reg)",
/* 411 */	"stmt: GEU2(reg,INDIRU2(reg))",
/* 412 */	"stmt: GEU2(reg,con)",
/* 413 */	"stmt: GEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 414 */	"stmt: GEU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 415 */	"stmt: GEU2(CVUU2(reg8),con)",
/* 416 */	"stmt: GEU2(CVIU2(reg8),con)",
/* 417 */	"stmt: GEI4(reg32,reg32)",
/* 418 */	"stmt: GEI4(reg32,INDIRI4(addr))",
/* 419 */	"stmt: GEU4(reg32,reg32)",
/* 420 */	"stmt: GEU4(reg32,INDIRU4(addr))",
/* 421 */	"stmt: GEF4(regf,regf)",
/* 422 */	"stmt: GEF4(regf,INDIRF4(addr))",
/* 423 */	"stmt: GEF8(regf,regf)",
/* 424 */	"stmt: GEF8(regf,INDIRF8(addr))",
/* 425 */	"stmt: GTI2(reg,reg)",
/* 426 */	"stmt: GTI2(reg,INDIRI2(reg))",
/* 427 */	"stmt: GTI2(reg,con)",
/* 428 */	"stmt: GTI2(CVII2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 429 */	"stmt: GTI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr)))",
/* 430 */	"stmt: GTI2(CVII2(reg8),con)",
/* 431 */	"stmt: GTI2(CVUI2(reg8),con)",
/* 432 */	"stmt: GTU2(reg,reg)",
/* 433 */	"stmt: GTU2(reg,INDIRU2(reg))",
/* 434 */	"stmt: GTU2(reg,con)",
/* 435 */	"stmt: GTU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 436 */	"stmt: GTU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr)))",
/* 437 */	"stmt: GTU2(CVUU2(reg8),con)",
/* 438 */	"stmt: GTU2(CVIU2(reg8),con)",
/* 439 */	"stmt: GTI4(reg32,reg32)",
/* 440 */	"stmt: GTI4(reg32,INDIRI4(addr))",
/* 441 */	"stmt: GTU4(reg32,reg32)",
/* 442 */	"stmt: GTU4(reg32,INDIRU4(addr))",
/* 443 */	"stmt: GTF4(regf,regf)",
/* 444 */	"stmt: GTF4(regf,INDIRF4(addr))",
/* 445 */	"stmt: GTF8(regf,regf)",
/* 446 */	"stmt: GTF8(regf,INDIRF8(addr))",
/* 447 */	"stmt: ARGI2(reg)",
/* 448 */	"stmt: ARGU2(reg)",
/* 449 */	"stmt: ARGP2(reg)",
/* 450 */	"stmt: ARGI4(reg32)",
/* 451 */	"stmt: ARGU4(reg32)",
/* 452 */	"stmt: ARGF4(regf)",
/* 453 */	"stmt: ARGF8(regf)",
/* 454 */	"reg: CALLI2(albl)",
/* 455 */	"reg: CALLU2(albl)",
/* 456 */	"reg: CALLP2(albl)",
/* 457 */	"stmt: CALLV(albl)",
/* 458 */	"reg32: CALLI4(albl)",
/* 459 */	"reg32: CALLU4(albl)",
/* 460 */	"regf: CALLF4(albl)",
/* 461 */	"regf: CALLF8(albl)",
/* 462 */	"stmt: RETI2(reg)",
/* 463 */	"stmt: RETU2(reg)",
/* 464 */	"stmt: RETP2(reg)",
/* 465 */	"stmt: RETV",
/* 466 */	"stmt: RETI4(reg32)",
/* 467 */	"stmt: RETU4(reg32)",
/* 468 */	"stmt: RETF4(regf)",
/* 469 */	"stmt: RETF8(regf)",
/* 470 */	"stmt: JUMPV(albl)",
/* 471 */	"stmt: LABELV",
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
	62,
	63,
	64,
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
	151,
	152,
	153,
	154,
	155,
	156,
	187,
	188,
	189,
	190,
	191,
	192,
	315,
	316,
	317,
	318,
	319,
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
	457,
	462,
	463,
	464,
	465,
	466,
	467,
	468,
	469,
	470,
	471,
};

static short _decode_reg8[] = {
	0,
	1,
	2,
	20,
	21,
	22,
	23,
	31,
	32,
	50,
	76,
	77,
	85,
	86,
	87,
	88,
	89,
	90,
	91,
	92,
	131,
	132,
	133,
	134,
	135,
	136,
	137,
	138,
	139,
	140,
	141,
	142,
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
	301,
	302,
	303,
	304,
	305,
	306,
	307,
	308,
	309,
	310,
	311,
	312,
};

static short _decode_reg[] = {
	0,
	3,
	4,
	7,
	24,
	25,
	28,
	48,
	49,
	59,
	60,
	61,
	78,
	79,
	80,
	93,
	94,
	95,
	96,
	97,
	98,
	99,
	100,
	115,
	116,
	119,
	120,
	121,
	122,
	123,
	124,
	125,
	126,
	127,
	128,
	129,
	130,
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
	193,
	194,
	201,
	202,
	203,
	204,
	205,
	206,
	223,
	224,
	227,
	228,
	229,
	230,
	231,
	232,
	249,
	250,
	251,
	252,
	253,
	254,
	271,
	272,
	273,
	274,
	275,
	276,
	297,
	298,
	299,
	300,
	454,
	455,
	456,
};

static short _decode_reg32[] = {
	0,
	5,
	6,
	26,
	27,
	81,
	82,
	101,
	102,
	103,
	104,
	105,
	106,
	107,
	108,
	143,
	144,
	145,
	146,
	179,
	180,
	181,
	182,
	195,
	196,
	219,
	220,
	221,
	222,
	225,
	226,
	245,
	246,
	247,
	248,
	267,
	268,
	269,
	270,
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
	313,
	314,
	458,
	459,
};

static short _decode_regf[] = {
	0,
	8,
	9,
	29,
	30,
	83,
	84,
	109,
	110,
	111,
	112,
	113,
	114,
	117,
	118,
	147,
	148,
	149,
	150,
	183,
	184,
	185,
	186,
	197,
	198,
	199,
	200,
	289,
	290,
	291,
	292,
	293,
	294,
	295,
	296,
	460,
	461,
};

static short _decode_con8[] = {
	0,
	33,
	34,
};

static short _decode_con16[] = {
	0,
	35,
	36,
	37,
};

static short _decode_con0[] = {
	0,
	38,
	39,
	40,
	41,
};

static short _decode_con1[] = {
	0,
	42,
	43,
	44,
	45,
};

static short _decode_con[] = {
	0,
	46,
	47,
};

static short _decode_lgaddr[] = {
	0,
	51,
	52,
	53,
};

static short _decode_addr[] = {
	0,
	54,
	56,
	57,
	58,
};

static short _decode_albl[] = {
	0,
	55,
};

static int _rule(void *state, int goalnt) {
	if (goalnt < 1 || goalnt > 13)
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
	case _con_NT:	return _decode_con[((struct _state *)state)->rule._con];
	case _lgaddr_NT:	return _decode_lgaddr[((struct _state *)state)->rule._lgaddr];
	case _addr_NT:	return _decode_addr[((struct _state *)state)->rule._addr];
	case _albl_NT:	return _decode_albl[((struct _state *)state)->rule._albl];
	default:
		fatal("_rule", "Bad goal nonterminal %d\n", goalnt);
		return 0;
	}
}

static void _closure_reg(NODEPTR_TYPE, int);
static void _closure_con8(NODEPTR_TYPE, int);
static void _closure_con16(NODEPTR_TYPE, int);
static void _closure_con0(NODEPTR_TYPE, int);
static void _closure_con(NODEPTR_TYPE, int);
static void _closure_lgaddr(NODEPTR_TYPE, int);

static void _closure_reg(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 0 < p->cost[_addr_NT]) {
		p->cost[_addr_NT] = c + 0;
		p->rule._addr = 2;
	}
	if (c + 0 < p->cost[_stmt_NT]) {
		p->cost[_stmt_NT] = c + 0;
		p->rule._stmt = 10;
	}
}

static void _closure_con8(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 1 < p->cost[_reg8_NT]) {
		p->cost[_reg8_NT] = c + 1;
		p->rule._reg8 = 9;
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
		p->rule._reg = 8;
		_closure_reg(a, c + 1);
	}
}

static void _closure_con(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 2 < p->cost[_reg_NT]) {
		p->cost[_reg_NT] = c + 2;
		p->rule._reg = 7;
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
				p->rule._stmt = 16;
			}
		}
		break;
	case 73: /* INDIRB */
		_label(LEFT_CHILD(a));
		break;
	case 216: /* CALLV */
		_label(LEFT_CHILD(a));
		/* stmt: CALLV(albl) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_albl_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 176;
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
			p->rule._stmt = 180;
		}
		break;
	case 584: /* JUMPV */
		_label(LEFT_CHILD(a));
		/* stmt: JUMPV(albl) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_albl_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 185;
		}
		break;
	case 600: /* LABELV */
		/* stmt: LABELV */
		if (0 + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = 0 + 0;
			p->rule._stmt = 186;
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
			p->rule._stmt = 11;
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
			p->rule._stmt = 12;
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
			}
			c = 0;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 1;
			}
		}
		/* reg8: INDIRI1(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 10;
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
			}
			c = 0;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 2;
			}
		}
		/* reg8: INDIRU1(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 11;
		}
		break;
	case 1157: /* CVII1 */
		_label(LEFT_CHILD(a));
		/* reg8: CVII1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 12;
		}
		/* reg8: CVII1(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 16;
		}
		break;
	case 1158: /* CVIU1 */
		_label(LEFT_CHILD(a));
		/* reg8: CVIU1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 13;
		}
		/* reg8: CVIU1(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 17;
		}
		break;
	case 1205: /* CVUI1 */
		_label(LEFT_CHILD(a));
		/* reg8: CVUI1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 14;
		}
		/* reg8: CVUI1(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 18;
		}
		break;
	case 1206: /* CVUU1 */
		_label(LEFT_CHILD(a));
		/* reg8: CVUU1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 15;
		}
		/* reg8: CVUU1(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 19;
		}
		break;
	case 1253: /* LOADI1 */
		_label(LEFT_CHILD(a));
		/* reg8: LOADI1(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + (move(a));
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 3;
		}
		/* reg8: LOADI1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 4;
		}
		if (	/* reg8: LOADI1(LOADI2(CVUU2(reg8))) */
			LEFT_CHILD(a)->op == 2277 && /* LOADI2 */
			LEFT_CHILD(LEFT_CHILD(a))->op == 2230 /* CVUU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(LEFT_CHILD(a)))->x.state))->cost[_reg8_NT] + 0;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 8;
			}
		}
		break;
	case 1254: /* LOADU1 */
		_label(LEFT_CHILD(a));
		/* reg8: LOADU1(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + (move(a));
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 5;
		}
		/* reg8: LOADU1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 6;
		}
		if (	/* reg8: LOADU1(LOADU2(CVII2(reg8))) */
			LEFT_CHILD(a)->op == 2278 && /* LOADU2 */
			LEFT_CHILD(LEFT_CHILD(a))->op == 2181 /* CVII2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(LEFT_CHILD(a)))->x.state))->cost[_reg8_NT] + 0;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 7;
			}
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
			p->rule._stmt = 169;
		}
		break;
	case 2086: /* ARGU2 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 170;
		}
		break;
	case 2087: /* ARGP2 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGP2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 171;
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
			p->rule._stmt = 13;
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
			p->rule._stmt = 14;
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
			p->rule._stmt = 15;
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
			p->rule._reg = 23;
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
		/* reg: CVII2(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 19;
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
		/* reg: CVIU2(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
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
			p->rule._reg = 25;
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
		/* reg: CVUI2(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 21;
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
		/* reg: CVUU2(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 22;
			_closure_reg(a, c + 0);
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
			p->rule._reg = 47;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: NEGI2(INDIRI2(addr)) */
			LEFT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 48;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 2261: /* CALLI2 */
		_label(LEFT_CHILD(a));
		/* reg: CALLI2(albl) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_albl_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 79;
			_closure_reg(a, c + 0);
		}
		break;
	case 2262: /* CALLU2 */
		_label(LEFT_CHILD(a));
		/* reg: CALLU2(albl) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_albl_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 80;
			_closure_reg(a, c + 0);
		}
		break;
	case 2263: /* CALLP2 */
		_label(LEFT_CHILD(a));
		/* reg: CALLP2(albl) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_albl_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 81;
			_closure_reg(a, c + 0);
		}
		break;
	case 2277: /* LOADI2 */
		_label(LEFT_CHILD(a));
		/* reg: LOADI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 4;
			_closure_reg(a, c + 0);
		}
		break;
	case 2278: /* LOADU2 */
		_label(LEFT_CHILD(a));
		/* reg: LOADU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 5;
			_closure_reg(a, c + 0);
		}
		break;
	case 2279: /* LOADP2 */
		_label(LEFT_CHILD(a));
		/* reg: LOADP2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
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
			p->rule._stmt = 177;
		}
		break;
	case 2294: /* RETU2 */
		_label(LEFT_CHILD(a));
		/* stmt: RETU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 178;
		}
		break;
	case 2295: /* RETP2 */
		_label(LEFT_CHILD(a));
		/* stmt: RETP2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 179;
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
			p->rule._reg = 27;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: ADDI2(reg,INDIRI2(addr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 28;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: ADDI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 29;
			_closure_reg(a, c + 0);
		}
		/* reg: ADDI2(reg,con1) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con1_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 30;
			_closure_reg(a, c + 0);
		}
		if (	/* reg8: ADDI2(reg8,CVII2(INDIRI1(addr))) */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 20;
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
				p->rule._reg8 = 21;
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
				p->rule._reg8 = 22;
			}
		}
		/* reg8: ADDI2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 23;
		}
		if (	/* reg8: ADDI2(CVII2(reg8),con) */
			LEFT_CHILD(a)->op == 2181 /* CVII2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 24;
			}
		}
		if (	/* reg8: ADDI2(CVUI2(reg8),con) */
			LEFT_CHILD(a)->op == 2229 /* CVUI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 25;
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
			p->rule._reg = 31;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: ADDU2(reg,INDIRU2(addr)) */
			RIGHT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 32;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: ADDU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 33;
			_closure_reg(a, c + 0);
		}
		/* reg: ADDU2(reg,con1) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con1_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 34;
			_closure_reg(a, c + 0);
		}
		if (	/* reg8: ADDU2(reg8,CVUU2(INDIRU1(addr))) */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 26;
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
				p->rule._reg8 = 27;
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
				p->rule._reg8 = 28;
			}
		}
		/* reg8: ADDU2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 29;
		}
		if (	/* reg8: ADDU2(CVUU2(reg8),con) */
			LEFT_CHILD(a)->op == 2230 /* CVUU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 30;
			}
		}
		if (	/* reg8: ADDU2(CVIU2(reg8),con) */
			LEFT_CHILD(a)->op == 2182 /* CVIU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 31;
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
		/* reg: ADDP2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 9;
			_closure_reg(a, c + 0);
		}
		/* reg: ADDP2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 35;
			_closure_reg(a, c + 0);
		}
		/* reg: ADDP2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 36;
			_closure_reg(a, c + 0);
		}
		/* reg: ADDP2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 46;
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
			p->rule._reg = 37;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: SUBI2(reg,INDIRI2(addr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 38;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: SUBI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 39;
			_closure_reg(a, c + 0);
		}
		/* reg: SUBI2(reg,con1) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con1_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 40;
			_closure_reg(a, c + 0);
		}
		if (	/* reg8: SUBI2(reg8,CVII2(INDIRI1(addr))) */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 32;
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
				p->rule._reg8 = 33;
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
				p->rule._reg8 = 34;
			}
		}
		/* reg8: SUBI2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 35;
		}
		if (	/* reg8: SUBI2(CVII2(reg8),con) */
			LEFT_CHILD(a)->op == 2181 /* CVII2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 36;
			}
		}
		if (	/* reg8: SUBI2(CVUI2(reg8),con) */
			LEFT_CHILD(a)->op == 2229 /* CVUI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 37;
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
			p->rule._reg = 41;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: SUBU2(reg,INDIRU2(addr)) */
			RIGHT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 42;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: SUBU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 43;
			_closure_reg(a, c + 0);
		}
		/* reg: SUBU2(reg,con1) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con1_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 44;
			_closure_reg(a, c + 0);
		}
		if (	/* reg8: SUBU2(reg8,CVUU2(INDIRU1(addr))) */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 38;
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
				p->rule._reg8 = 39;
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
				p->rule._reg8 = 40;
			}
		}
		/* reg8: SUBU2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 41;
		}
		if (	/* reg8: SUBU2(CVUU2(reg8),con) */
			LEFT_CHILD(a)->op == 2230 /* CVUU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 42;
			}
		}
		if (	/* reg8: SUBU2(CVIU2(reg8),con) */
			LEFT_CHILD(a)->op == 2182 /* CVIU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 43;
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
		/* reg: SUBP2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 10;
			_closure_reg(a, c + 0);
		}
		/* reg: SUBP2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 45;
			_closure_reg(a, c + 0);
		}
		break;
	case 2389: /* LSHI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: LSHI2(reg,con1) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con1_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 75;
			_closure_reg(a, c + 0);
		}
		/* reg8: LSHI2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 80;
		}
		if (	/* reg8: LSHI2(CVII2(reg8),con) */
			LEFT_CHILD(a)->op == 2181 /* CVII2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 81;
			}
		}
		if (	/* reg8: LSHI2(CVUI2(reg8),con) */
			LEFT_CHILD(a)->op == 2229 /* CVUI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 82;
			}
		}
		break;
	case 2390: /* LSHU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: LSHU2(reg,con1) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con1_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 76;
			_closure_reg(a, c + 0);
		}
		/* reg8: LSHU2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 83;
		}
		if (	/* reg8: LSHU2(CVUU2(reg8),con) */
			LEFT_CHILD(a)->op == 2230 /* CVUU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 84;
			}
		}
		if (	/* reg8: LSHU2(CVIU2(reg8),con) */
			LEFT_CHILD(a)->op == 2182 /* CVIU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 85;
			}
		}
		break;
	case 2405: /* MODI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MODI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 73;
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
			p->rule._reg = 74;
			_closure_reg(a, c + 0);
		}
		break;
	case 2421: /* RSHI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: RSHI2(reg,con1) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con1_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 77;
			_closure_reg(a, c + 0);
		}
		/* reg8: RSHI2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 86;
		}
		if (	/* reg8: RSHI2(CVII2(reg8),con) */
			LEFT_CHILD(a)->op == 2181 /* CVII2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 87;
			}
		}
		if (	/* reg8: RSHI2(CVUI2(reg8),con) */
			LEFT_CHILD(a)->op == 2229 /* CVUI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 88;
			}
		}
		break;
	case 2422: /* RSHU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: RSHU2(reg,con1) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con1_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 78;
			_closure_reg(a, c + 0);
		}
		/* reg8: RSHU2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 89;
		}
		if (	/* reg8: RSHU2(CVUU2(reg8),con) */
			LEFT_CHILD(a)->op == 2230 /* CVUU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 90;
			}
		}
		if (	/* reg8: RSHU2(CVIU2(reg8),con) */
			LEFT_CHILD(a)->op == 2182 /* CVIU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 91;
			}
		}
		break;
	case 2437: /* BANDI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BANDI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 49;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: BANDI2(reg,INDIRI2(lgaddr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 50;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: BANDI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 51;
			_closure_reg(a, c + 0);
		}
		if (	/* reg8: BANDI2(reg8,CVII2(INDIRI1(lgaddr))) */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 44;
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
				p->rule._reg8 = 45;
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
				p->rule._reg8 = 46;
			}
		}
		/* reg8: BANDI2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 47;
		}
		if (	/* reg8: BANDI2(CVII2(reg8),con) */
			LEFT_CHILD(a)->op == 2181 /* CVII2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 48;
			}
		}
		if (	/* reg8: BANDI2(CVUI2(reg8),con) */
			LEFT_CHILD(a)->op == 2229 /* CVUI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 49;
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
			p->rule._reg = 52;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: BANDU2(reg,INDIRU2(lgaddr)) */
			RIGHT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 53;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: BANDU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 54;
			_closure_reg(a, c + 0);
		}
		if (	/* reg8: BANDU2(reg8,CVUU2(INDIRU1(lgaddr))) */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 50;
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
				p->rule._reg8 = 51;
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
				p->rule._reg8 = 52;
			}
		}
		/* reg8: BANDU2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 53;
		}
		if (	/* reg8: BANDU2(CVUU2(reg8),con) */
			LEFT_CHILD(a)->op == 2230 /* CVUU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 54;
			}
		}
		if (	/* reg8: BANDU2(CVIU2(reg8),con) */
			LEFT_CHILD(a)->op == 2182 /* CVIU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 55;
			}
		}
		break;
	case 2453: /* BCOMI2 */
		_label(LEFT_CHILD(a));
		/* reg: BCOMI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 55;
			_closure_reg(a, c + 0);
		}
		break;
	case 2454: /* BCOMU2 */
		_label(LEFT_CHILD(a));
		/* reg: BCOMU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 56;
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
			p->rule._reg = 57;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: BORI2(reg,INDIRI2(lgaddr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 58;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: BORI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 59;
			_closure_reg(a, c + 0);
		}
		if (	/* reg8: BORI2(reg8,CVII2(INDIRI1(lgaddr))) */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 56;
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
				p->rule._reg8 = 57;
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
				p->rule._reg8 = 58;
			}
		}
		/* reg8: BORI2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 59;
		}
		if (	/* reg8: BORI2(CVII2(reg8),con) */
			LEFT_CHILD(a)->op == 2181 /* CVII2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 60;
			}
		}
		if (	/* reg8: BORI2(CVUI2(reg8),con) */
			LEFT_CHILD(a)->op == 2229 /* CVUI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 61;
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
			p->rule._reg = 60;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: BORU2(reg,INDIRU2(lgaddr)) */
			RIGHT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 61;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: BORU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 62;
			_closure_reg(a, c + 0);
		}
		if (	/* reg8: BORU2(reg8,CVUU2(INDIRU1(lgaddr))) */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 62;
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
				p->rule._reg8 = 63;
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
				p->rule._reg8 = 64;
			}
		}
		/* reg8: BORU2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 65;
		}
		if (	/* reg8: BORU2(CVUU2(reg8),con) */
			LEFT_CHILD(a)->op == 2230 /* CVUU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 66;
			}
		}
		if (	/* reg8: BORU2(CVIU2(reg8),con) */
			LEFT_CHILD(a)->op == 2182 /* CVIU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 67;
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
			p->rule._reg = 63;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: BXORI2(reg,INDIRI2(lgaddr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 64;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: BXORI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 65;
			_closure_reg(a, c + 0);
		}
		if (	/* reg8: BXORI2(reg8,CVII2(INDIRI1(lgaddr))) */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 68;
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
				p->rule._reg8 = 69;
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
				p->rule._reg8 = 70;
			}
		}
		/* reg8: BXORI2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 71;
		}
		if (	/* reg8: BXORI2(CVII2(reg8),con) */
			LEFT_CHILD(a)->op == 2181 /* CVII2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 72;
			}
		}
		if (	/* reg8: BXORI2(CVUI2(reg8),con) */
			LEFT_CHILD(a)->op == 2229 /* CVUI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 73;
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
			p->rule._reg = 66;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: BXORU2(reg,INDIRU2(lgaddr)) */
			RIGHT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 67;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: BXORU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 68;
			_closure_reg(a, c + 0);
		}
		if (	/* reg8: BXORU2(reg8,CVUU2(INDIRU1(lgaddr))) */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 74;
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
				p->rule._reg8 = 75;
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
				p->rule._reg8 = 76;
			}
		}
		/* reg8: BXORU2(reg8,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg8_NT]) {
			p->cost[_reg8_NT] = c + 0;
			p->rule._reg8 = 77;
		}
		if (	/* reg8: BXORU2(CVUU2(reg8),con) */
			LEFT_CHILD(a)->op == 2230 /* CVUU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 78;
			}
		}
		if (	/* reg8: BXORU2(CVIU2(reg8),con) */
			LEFT_CHILD(a)->op == 2182 /* CVIU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_reg8_NT]) {
				p->cost[_reg8_NT] = c + 0;
				p->rule._reg8 = 79;
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
			p->rule._reg = 71;
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
			p->rule._reg = 72;
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
			p->rule._reg = 69;
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
			p->rule._reg = 70;
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
			p->rule._stmt = 37;
		}
		if (	/* stmt: EQI2(reg,INDIRI2(lgaddr)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 38;
			}
		}
		/* stmt: EQI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 39;
		}
		if (	/* stmt: EQI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
			LEFT_CHILD(a)->op == 2181 && /* CVII2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 40;
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
				p->rule._stmt = 41;
			}
		}
		if (	/* stmt: EQI2(CVII2(reg8),con) */
			LEFT_CHILD(a)->op == 2181 /* CVII2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 42;
			}
		}
		if (	/* stmt: EQI2(CVUI2(reg8),con) */
			LEFT_CHILD(a)->op == 2229 /* CVUI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 43;
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
			p->rule._stmt = 44;
		}
		if (	/* stmt: EQU2(reg,INDIRU2(lgaddr)) */
			RIGHT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_lgaddr_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 45;
			}
		}
		/* stmt: EQU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 46;
		}
		if (	/* stmt: EQU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
			LEFT_CHILD(a)->op == 2230 && /* CVUU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 47;
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
				p->rule._stmt = 48;
			}
		}
		if (	/* stmt: EQU2(CVUU2(reg8),con) */
			LEFT_CHILD(a)->op == 2230 /* CVUU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 49;
			}
		}
		if (	/* stmt: EQU2(CVIU2(reg8),con) */
			LEFT_CHILD(a)->op == 2182 /* CVIU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 50;
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
			p->rule._stmt = 125;
		}
		if (	/* stmt: GEI2(reg,INDIRI2(reg)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_reg_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 126;
			}
		}
		/* stmt: GEI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 127;
		}
		if (	/* stmt: GEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
			LEFT_CHILD(a)->op == 2181 && /* CVII2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 128;
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
				p->rule._stmt = 129;
			}
		}
		if (	/* stmt: GEI2(CVII2(reg8),con) */
			LEFT_CHILD(a)->op == 2181 /* CVII2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 130;
			}
		}
		if (	/* stmt: GEI2(CVUI2(reg8),con) */
			LEFT_CHILD(a)->op == 2229 /* CVUI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 131;
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
			p->rule._stmt = 132;
		}
		if (	/* stmt: GEU2(reg,INDIRU2(reg)) */
			RIGHT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_reg_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 133;
			}
		}
		/* stmt: GEU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 134;
		}
		if (	/* stmt: GEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
			LEFT_CHILD(a)->op == 2230 && /* CVUU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 135;
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
				p->rule._stmt = 136;
			}
		}
		if (	/* stmt: GEU2(CVUU2(reg8),con) */
			LEFT_CHILD(a)->op == 2230 /* CVUU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 137;
			}
		}
		if (	/* stmt: GEU2(CVIU2(reg8),con) */
			LEFT_CHILD(a)->op == 2182 /* CVIU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 138;
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
			p->rule._stmt = 147;
		}
		if (	/* stmt: GTI2(reg,INDIRI2(reg)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_reg_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 148;
			}
		}
		/* stmt: GTI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 149;
		}
		if (	/* stmt: GTI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
			LEFT_CHILD(a)->op == 2181 && /* CVII2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 150;
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
				p->rule._stmt = 151;
			}
		}
		if (	/* stmt: GTI2(CVII2(reg8),con) */
			LEFT_CHILD(a)->op == 2181 /* CVII2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 152;
			}
		}
		if (	/* stmt: GTI2(CVUI2(reg8),con) */
			LEFT_CHILD(a)->op == 2229 /* CVUI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 153;
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
			p->rule._stmt = 154;
		}
		if (	/* stmt: GTU2(reg,INDIRU2(reg)) */
			RIGHT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_reg_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 155;
			}
		}
		/* stmt: GTU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 156;
		}
		if (	/* stmt: GTU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
			LEFT_CHILD(a)->op == 2230 && /* CVUU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 157;
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
				p->rule._stmt = 158;
			}
		}
		if (	/* stmt: GTU2(CVUU2(reg8),con) */
			LEFT_CHILD(a)->op == 2230 /* CVUU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 159;
			}
		}
		if (	/* stmt: GTU2(CVIU2(reg8),con) */
			LEFT_CHILD(a)->op == 2182 /* CVIU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 160;
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
			p->rule._stmt = 81;
		}
		if (	/* stmt: LEI2(reg,INDIRI2(reg)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_reg_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 82;
			}
		}
		/* stmt: LEI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 83;
		}
		if (	/* stmt: LEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
			LEFT_CHILD(a)->op == 2181 && /* CVII2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 84;
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
				p->rule._stmt = 85;
			}
		}
		if (	/* stmt: LEI2(CVII2(reg8),con) */
			LEFT_CHILD(a)->op == 2181 /* CVII2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 86;
			}
		}
		if (	/* stmt: LEI2(CVUI2(reg8),con) */
			LEFT_CHILD(a)->op == 2229 /* CVUI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 87;
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
			p->rule._stmt = 88;
		}
		if (	/* stmt: LEU2(reg,INDIRU2(reg)) */
			RIGHT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_reg_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 89;
			}
		}
		/* stmt: LEU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 90;
		}
		if (	/* stmt: LEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
			LEFT_CHILD(a)->op == 2230 && /* CVUU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 91;
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
				p->rule._stmt = 92;
			}
		}
		if (	/* stmt: LEU2(CVUU2(reg8),con) */
			LEFT_CHILD(a)->op == 2230 /* CVUU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 93;
			}
		}
		if (	/* stmt: LEU2(CVIU2(reg8),con) */
			LEFT_CHILD(a)->op == 2182 /* CVIU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 94;
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
			p->rule._stmt = 103;
		}
		if (	/* stmt: LTI2(reg,INDIRI2(reg)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_reg_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 104;
			}
		}
		/* stmt: LTI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 105;
		}
		if (	/* stmt: LTI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
			LEFT_CHILD(a)->op == 2181 && /* CVII2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 106;
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
				p->rule._stmt = 107;
			}
		}
		if (	/* stmt: LTI2(CVII2(reg8),con) */
			LEFT_CHILD(a)->op == 2181 /* CVII2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 108;
			}
		}
		if (	/* stmt: LTI2(CVUI2(reg8),con) */
			LEFT_CHILD(a)->op == 2229 /* CVUI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 109;
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
			p->rule._stmt = 110;
		}
		if (	/* stmt: LTU2(reg,INDIRU2(reg)) */
			RIGHT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_reg_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 111;
			}
		}
		/* stmt: LTU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 112;
		}
		if (	/* stmt: LTU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
			LEFT_CHILD(a)->op == 2230 && /* CVUU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 113;
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
				p->rule._stmt = 114;
			}
		}
		if (	/* stmt: LTU2(CVUU2(reg8),con) */
			LEFT_CHILD(a)->op == 2230 /* CVUU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 115;
			}
		}
		if (	/* stmt: LTU2(CVIU2(reg8),con) */
			LEFT_CHILD(a)->op == 2182 /* CVIU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 116;
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
			p->rule._stmt = 59;
		}
		if (	/* stmt: NEI2(reg,INDIRI2(reg)) */
			RIGHT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_reg_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 60;
			}
		}
		/* stmt: NEI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 61;
		}
		if (	/* stmt: NEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
			LEFT_CHILD(a)->op == 2181 && /* CVII2 */
			RIGHT_CHILD(a)->op == 2181 && /* CVII2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 62;
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
				p->rule._stmt = 63;
			}
		}
		if (	/* stmt: NEI2(CVII2(reg8),con) */
			LEFT_CHILD(a)->op == 2181 /* CVII2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 64;
			}
		}
		if (	/* stmt: NEI2(CVUI2(reg8),con) */
			LEFT_CHILD(a)->op == 2229 /* CVUI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 65;
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
			p->rule._stmt = 66;
		}
		if (	/* stmt: NEU2(reg,INDIRU2(reg)) */
			RIGHT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_reg_NT] + 2;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 67;
			}
		}
		/* stmt: NEU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 68;
		}
		if (	/* stmt: NEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
			LEFT_CHILD(a)->op == 2230 && /* CVUU2 */
			RIGHT_CHILD(a)->op == 2230 && /* CVUU2 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_lgaddr_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 69;
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
				p->rule._stmt = 70;
			}
		}
		if (	/* stmt: NEU2(CVUU2(reg8),con) */
			LEFT_CHILD(a)->op == 2230 /* CVUU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 71;
			}
		}
		if (	/* stmt: NEU2(CVIU2(reg8),con) */
			LEFT_CHILD(a)->op == 2182 /* CVIU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 72;
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
			p->rule._stmt = 174;
		}
		break;
	case 4133: /* ARGI4 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGI4(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 172;
		}
		break;
	case 4134: /* ARGU4 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGU4(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 173;
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
		/* stmt: ASGNF4(addr,regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 21;
		}
		if (	/* stmt: ASGNF4(addr,INDIRF4(addr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 22;
			}
		}
		if (	/* stmt: ASGNF4(addr,ADDF4(INDIRF4(addr),INDIRF4(addr))) */
			RIGHT_CHILD(a)->op == 4401 && /* ADDF4 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 4161 && /* INDIRF4 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 27;
			}
		}
		if (	/* stmt: ASGNF4(addr,ADDF4(INDIRF4(addr),INDIRF4(addr))) */
			RIGHT_CHILD(a)->op == 4401 && /* ADDF4 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 4161 && /* INDIRF4 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + (memop(a));
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 28;
			}
		}
		if (	/* stmt: ASGNF4(addr,SUBF4(INDIRF4(addr),INDIRF4(addr))) */
			RIGHT_CHILD(a)->op == 4417 && /* SUBF4 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 4161 && /* INDIRF4 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 33;
			}
		}
		if (	/* stmt: ASGNF4(addr,SUBF4(INDIRF4(addr),INDIRF4(addr))) */
			RIGHT_CHILD(a)->op == 4417 && /* SUBF4 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 4161 && /* INDIRF4 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + (memop(a));
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 34;
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
		/* stmt: ASGNI4(addr,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 17;
		}
		if (	/* stmt: ASGNI4(addr,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 18;
			}
		}
		if (	/* stmt: ASGNI4(addr,ADDI4(INDIRI4(addr),INDIRI4(addr))) */
			RIGHT_CHILD(a)->op == 4405 && /* ADDI4 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 4165 && /* INDIRI4 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 25;
			}
		}
		if (	/* stmt: ASGNI4(addr,ADDI4(INDIRI4(addr),INDIRI4(addr))) */
			RIGHT_CHILD(a)->op == 4405 && /* ADDI4 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 4165 && /* INDIRI4 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + (memop(a));
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 26;
			}
		}
		if (	/* stmt: ASGNI4(addr,SUBI4(INDIRI4(addr),INDIRI4(addr))) */
			RIGHT_CHILD(a)->op == 4421 && /* SUBI4 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 4165 && /* INDIRI4 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 31;
			}
		}
		if (	/* stmt: ASGNI4(addr,SUBI4(INDIRI4(addr),INDIRI4(addr))) */
			RIGHT_CHILD(a)->op == 4421 && /* SUBI4 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 4165 && /* INDIRI4 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + (memop(a));
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 32;
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
		/* stmt: ASGNU4(addr,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 19;
		}
		if (	/* stmt: ASGNU4(addr,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 20;
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
			}
			c = 0;
			if (c + 0 < p->cost[_regf_NT]) {
				p->cost[_regf_NT] = c + 0;
				p->rule._regf = 1;
			}
		}
		/* regf: INDIRF4(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 5;
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
			}
			c = 0;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 1;
			}
		}
		/* reg32: INDIRI4(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 5;
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
			}
			c = 0;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 2;
			}
		}
		/* reg32: INDIRU4(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 6;
		}
		break;
	case 4209: /* CVFF4 */
		_label(LEFT_CHILD(a));
		/* regf: CVFF4(regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 13;
		}
		break;
	case 4213: /* CVFI4 */
		_label(LEFT_CHILD(a));
		/* reg: CVFI4(regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 24;
			_closure_reg(a, c + 0);
		}
		break;
	case 4225: /* CVIF4 */
		_label(LEFT_CHILD(a));
		/* regf: CVIF4(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 7;
		}
		/* regf: CVIF4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 8;
		}
		/* regf: CVIF4(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 9;
		}
		break;
	case 4229: /* CVII4 */
		_label(LEFT_CHILD(a));
		/* reg32: CVII4(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 7;
		}
		/* reg32: CVII4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 11;
		}
		break;
	case 4230: /* CVIU4 */
		_label(LEFT_CHILD(a));
		/* reg32: CVIU4(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 8;
		}
		/* reg32: CVIU4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 12;
		}
		break;
	case 4277: /* CVUI4 */
		_label(LEFT_CHILD(a));
		/* reg32: CVUI4(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 9;
		}
		/* reg32: CVUI4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 13;
		}
		break;
	case 4278: /* CVUU4 */
		_label(LEFT_CHILD(a));
		/* reg32: CVUU4(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 10;
		}
		/* reg32: CVUU4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 14;
		}
		break;
	case 4289: /* NEGF4 */
		_label(LEFT_CHILD(a));
		/* regf: NEGF4(regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 23;
		}
		if (	/* regf: NEGF4(INDIRF4(addr)) */
			LEFT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_regf_NT]) {
				p->cost[_regf_NT] = c + 0;
				p->rule._regf = 24;
			}
		}
		break;
	case 4293: /* NEGI4 */
		_label(LEFT_CHILD(a));
		/* reg32: NEGI4(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 23;
		}
		if (	/* reg32: NEGI4(INDIRI4(addr)) */
			LEFT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 24;
			}
		}
		break;
	case 4305: /* CALLF4 */
		_label(LEFT_CHILD(a));
		/* regf: CALLF4(albl) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_albl_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 35;
		}
		break;
	case 4309: /* CALLI4 */
		_label(LEFT_CHILD(a));
		/* reg32: CALLI4(albl) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_albl_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 53;
		}
		break;
	case 4310: /* CALLU4 */
		_label(LEFT_CHILD(a));
		/* reg32: CALLU4(albl) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_albl_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 54;
		}
		break;
	case 4321: /* LOADF4 */
		_label(LEFT_CHILD(a));
		/* regf: LOADF4(regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + (move(a));
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 3;
		}
		break;
	case 4325: /* LOADI4 */
		_label(LEFT_CHILD(a));
		/* reg32: LOADI4(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + (move(a));
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 3;
		}
		break;
	case 4326: /* LOADU4 */
		_label(LEFT_CHILD(a));
		/* reg32: LOADU4(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + (move(a));
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 4;
		}
		break;
	case 4337: /* RETF4 */
		_label(LEFT_CHILD(a));
		/* stmt: RETF4(regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 183;
		}
		break;
	case 4341: /* RETI4 */
		_label(LEFT_CHILD(a));
		/* stmt: RETI4(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 181;
		}
		break;
	case 4342: /* RETU4 */
		_label(LEFT_CHILD(a));
		/* stmt: RETU4(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 182;
		}
		break;
	case 4401: /* ADDF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* regf: ADDF4(regf,regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 15;
		}
		if (	/* regf: ADDF4(regf,INDIRF4(addr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_regf_NT]) {
				p->cost[_regf_NT] = c + 0;
				p->rule._regf = 16;
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
			p->rule._reg32 = 15;
		}
		if (	/* reg32: ADDI4(reg32,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 16;
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
			p->rule._reg32 = 17;
		}
		if (	/* reg32: ADDU4(reg32,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 18;
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
			p->rule._regf = 19;
		}
		if (	/* regf: SUBF4(regf,INDIRF4(addr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_regf_NT]) {
				p->cost[_regf_NT] = c + 0;
				p->rule._regf = 20;
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
			p->rule._reg32 = 19;
		}
		if (	/* reg32: SUBI4(reg32,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 20;
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
			p->rule._reg32 = 21;
		}
		if (	/* reg32: SUBU4(reg32,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 22;
			}
		}
		break;
	case 4437: /* LSHI4 */
		break;
	case 4438: /* LSHU4 */
		break;
	case 4453: /* MODI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg32: MODI4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 47;
		}
		if (	/* reg32: MODI4(reg32,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 48;
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
			p->rule._reg32 = 49;
		}
		if (	/* reg32: MODU4(reg32,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 50;
			}
		}
		break;
	case 4469: /* RSHI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg32: RSHI4(reg32,con1) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con1_NT] + 2;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 51;
		}
		break;
	case 4470: /* RSHU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg32: RSHU4(reg32,con1) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con1_NT] + 2;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 52;
		}
		break;
	case 4485: /* BANDI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg32: BANDI4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 25;
		}
		if (	/* reg32: BANDI4(reg32,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 26;
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
			p->rule._reg32 = 27;
		}
		if (	/* reg32: BANDU4(reg32,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 28;
			}
		}
		break;
	case 4501: /* BCOMI4 */
		_label(LEFT_CHILD(a));
		/* reg32: BCOMI4(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 29;
		}
		break;
	case 4502: /* BCOMU4 */
		_label(LEFT_CHILD(a));
		/* reg32: BCOMU4(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 30;
		}
		break;
	case 4517: /* BORI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg32: BORI4(reg32,reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg32_NT] + 4;
		if (c + 0 < p->cost[_reg32_NT]) {
			p->cost[_reg32_NT] = c + 0;
			p->rule._reg32 = 31;
		}
		if (	/* reg32: BORI4(reg32,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 32;
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
			p->rule._reg32 = 33;
		}
		if (	/* reg32: BORU4(reg32,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 34;
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
			p->rule._reg32 = 35;
		}
		if (	/* reg32: BXORI4(reg32,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 36;
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
			p->rule._reg32 = 37;
		}
		if (	/* reg32: BXORU4(reg32,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 38;
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
			p->rule._regf = 31;
		}
		if (	/* regf: DIVF4(regf,INDIRF4(addr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_regf_NT]) {
				p->cost[_regf_NT] = c + 0;
				p->rule._regf = 32;
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
			p->rule._reg32 = 43;
		}
		if (	/* reg32: DIVI4(reg32,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 44;
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
			p->rule._reg32 = 45;
		}
		if (	/* reg32: DIVU4(reg32,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 46;
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
			p->rule._regf = 27;
		}
		if (	/* regf: MULF4(regf,INDIRF4(addr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_regf_NT]) {
				p->cost[_regf_NT] = c + 0;
				p->rule._regf = 28;
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
			p->rule._reg32 = 39;
		}
		if (	/* reg32: MULI4(reg32,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 40;
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
			p->rule._reg32 = 41;
		}
		if (	/* reg32: MULU4(reg32,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_reg32_NT]) {
				p->cost[_reg32_NT] = c + 0;
				p->rule._reg32 = 42;
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
			p->rule._stmt = 55;
		}
		if (	/* stmt: EQF4(regf,INDIRF4(addr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 56;
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
			p->rule._stmt = 51;
		}
		if (	/* stmt: EQI4(reg32,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 52;
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
			p->rule._stmt = 53;
		}
		if (	/* stmt: EQU4(reg32,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 54;
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
			p->rule._stmt = 143;
		}
		if (	/* stmt: GEF4(regf,INDIRF4(addr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 144;
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
			p->rule._stmt = 139;
		}
		if (	/* stmt: GEI4(reg32,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 140;
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
			p->rule._stmt = 141;
		}
		if (	/* stmt: GEU4(reg32,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 142;
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
			p->rule._stmt = 165;
		}
		if (	/* stmt: GTF4(regf,INDIRF4(addr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 166;
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
			p->rule._stmt = 161;
		}
		if (	/* stmt: GTI4(reg32,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 162;
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
			p->rule._stmt = 163;
		}
		if (	/* stmt: GTU4(reg32,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 164;
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
			p->rule._stmt = 99;
		}
		if (	/* stmt: LEF4(regf,INDIRF4(addr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 100;
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
			p->rule._stmt = 95;
		}
		if (	/* stmt: LEI4(reg32,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 96;
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
			p->rule._stmt = 97;
		}
		if (	/* stmt: LEU4(reg32,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 98;
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
			p->rule._stmt = 121;
		}
		if (	/* stmt: LTF4(regf,INDIRF4(addr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 122;
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
			p->rule._stmt = 117;
		}
		if (	/* stmt: LTI4(reg32,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 118;
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
			p->rule._stmt = 119;
		}
		if (	/* stmt: LTU4(reg32,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 120;
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
			p->rule._stmt = 77;
		}
		if (	/* stmt: NEF4(regf,INDIRF4(addr)) */
			RIGHT_CHILD(a)->op == 4161 /* INDIRF4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 78;
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
			p->rule._stmt = 73;
		}
		if (	/* stmt: NEI4(reg32,INDIRI4(addr)) */
			RIGHT_CHILD(a)->op == 4165 /* INDIRI4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 74;
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
			p->rule._stmt = 75;
		}
		if (	/* stmt: NEU4(reg32,INDIRU4(addr)) */
			RIGHT_CHILD(a)->op == 4166 /* INDIRU4 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 76;
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
			p->rule._stmt = 175;
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
		/* stmt: ASGNF8(addr,regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 23;
		}
		if (	/* stmt: ASGNF8(addr,INDIRF8(addr)) */
			RIGHT_CHILD(a)->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 24;
			}
		}
		if (	/* stmt: ASGNF8(addr,ADDF8(INDIRF8(addr),INDIRF8(addr))) */
			RIGHT_CHILD(a)->op == 8497 && /* ADDF8 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 8257 && /* INDIRF8 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 8;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 29;
			}
		}
		if (	/* stmt: ASGNF8(addr,ADDF8(INDIRF8(addr),INDIRF8(addr))) */
			RIGHT_CHILD(a)->op == 8497 && /* ADDF8 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 8257 && /* INDIRF8 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + (memop(a));
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 30;
			}
		}
		if (	/* stmt: ASGNF8(addr,SUBF8(INDIRF8(addr),INDIRF8(addr))) */
			RIGHT_CHILD(a)->op == 8513 && /* SUBF8 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 8257 && /* INDIRF8 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + 8;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 35;
			}
		}
		if (	/* stmt: ASGNF8(addr,SUBF8(INDIRF8(addr),INDIRF8(addr))) */
			RIGHT_CHILD(a)->op == 8513 && /* SUBF8 */
			LEFT_CHILD(RIGHT_CHILD(a))->op == 8257 && /* INDIRF8 */
			RIGHT_CHILD(RIGHT_CHILD(a))->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))->x.state))->cost[_addr_NT] + (memop(a));
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 36;
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
			}
			c = 0;
			if (c + 0 < p->cost[_regf_NT]) {
				p->cost[_regf_NT] = c + 0;
				p->rule._regf = 2;
			}
		}
		/* regf: INDIRF8(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 6;
		}
		break;
	case 8305: /* CVFF8 */
		_label(LEFT_CHILD(a));
		/* regf: CVFF8(regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + 4;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 14;
		}
		break;
	case 8321: /* CVIF8 */
		_label(LEFT_CHILD(a));
		/* regf: CVIF8(reg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg8_NT] + 8;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 10;
		}
		/* regf: CVIF8(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 8;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 11;
		}
		/* regf: CVIF8(reg32) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg32_NT] + 8;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 12;
		}
		break;
	case 8385: /* NEGF8 */
		_label(LEFT_CHILD(a));
		/* regf: NEGF8(regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + 8;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 25;
		}
		if (	/* regf: NEGF8(INDIRF8(addr)) */
			LEFT_CHILD(a)->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_addr_NT] + 8;
			if (c + 0 < p->cost[_regf_NT]) {
				p->cost[_regf_NT] = c + 0;
				p->rule._regf = 26;
			}
		}
		break;
	case 8401: /* CALLF8 */
		_label(LEFT_CHILD(a));
		/* regf: CALLF8(albl) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_albl_NT] + 8;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 36;
		}
		break;
	case 8417: /* LOADF8 */
		_label(LEFT_CHILD(a));
		/* regf: LOADF8(regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + (move(a));
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 4;
		}
		break;
	case 8433: /* RETF8 */
		_label(LEFT_CHILD(a));
		/* stmt: RETF8(regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 184;
		}
		break;
	case 8497: /* ADDF8 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* regf: ADDF8(regf,regf) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_regf_NT] + 8;
		if (c + 0 < p->cost[_regf_NT]) {
			p->cost[_regf_NT] = c + 0;
			p->rule._regf = 17;
		}
		if (	/* regf: ADDF8(regf,INDIRF8(addr)) */
			RIGHT_CHILD(a)->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 8;
			if (c + 0 < p->cost[_regf_NT]) {
				p->cost[_regf_NT] = c + 0;
				p->rule._regf = 18;
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
			p->rule._regf = 21;
		}
		if (	/* regf: SUBF8(regf,INDIRF8(addr)) */
			RIGHT_CHILD(a)->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 8;
			if (c + 0 < p->cost[_regf_NT]) {
				p->cost[_regf_NT] = c + 0;
				p->rule._regf = 22;
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
			p->rule._regf = 33;
		}
		if (	/* regf: DIVF8(regf,INDIRF8(addr)) */
			RIGHT_CHILD(a)->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_regf_NT]) {
				p->cost[_regf_NT] = c + 0;
				p->rule._regf = 34;
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
			p->rule._regf = 29;
		}
		if (	/* regf: MULF8(regf,INDIRF8(addr)) */
			RIGHT_CHILD(a)->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 4;
			if (c + 0 < p->cost[_regf_NT]) {
				p->cost[_regf_NT] = c + 0;
				p->rule._regf = 30;
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
			p->rule._stmt = 57;
		}
		if (	/* stmt: EQF8(regf,INDIRF8(addr)) */
			RIGHT_CHILD(a)->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 8;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 58;
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
			p->rule._stmt = 145;
		}
		if (	/* stmt: GEF8(regf,INDIRF8(addr)) */
			RIGHT_CHILD(a)->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 8;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 146;
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
			p->rule._stmt = 167;
		}
		if (	/* stmt: GTF8(regf,INDIRF8(addr)) */
			RIGHT_CHILD(a)->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 8;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 168;
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
			p->rule._stmt = 101;
		}
		if (	/* stmt: LEF8(regf,INDIRF8(addr)) */
			RIGHT_CHILD(a)->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 8;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 102;
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
			p->rule._stmt = 123;
		}
		if (	/* stmt: LTF8(regf,INDIRF8(addr)) */
			RIGHT_CHILD(a)->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 8;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 124;
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
			p->rule._stmt = 79;
		}
		if (	/* stmt: NEF8(regf,INDIRF8(addr)) */
			RIGHT_CHILD(a)->op == 8257 /* INDIRF8 */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_regf_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_addr_NT] + 8;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 80;
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
	case 471: /* stmt: LABELV */
	case 465: /* stmt: RETV */
	case 55: /* albl: ADDRGP2 */
	case 53: /* lgaddr: ADDRLP2 */
	case 52: /* lgaddr: ADDRFP2 */
	case 51: /* lgaddr: ADDRGP2 */
	case 45: /* con1: CNSTU2 */
	case 44: /* con1: CNSTI2 */
	case 43: /* con1: CNSTU1 */
	case 42: /* con1: CNSTI1 */
	case 41: /* con0: CNSTU2 */
	case 40: /* con0: CNSTI2 */
	case 39: /* con0: CNSTU1 */
	case 38: /* con0: CNSTI1 */
	case 37: /* con16: CNSTP2 */
	case 36: /* con16: CNSTU2 */
	case 35: /* con16: CNSTI2 */
	case 34: /* con8: CNSTU1 */
	case 33: /* con8: CNSTI1 */
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
	case 61: /* reg: lgaddr */
	case 56: /* addr: reg */
	case 54: /* addr: lgaddr */
	case 50: /* reg8: con8 */
	case 49: /* reg: con0 */
	case 48: /* reg: con */
	case 47: /* con: con16 */
	case 46: /* con: con8 */
	case 19: /* stmt: reg */
		kids[0] = p;
		break;
	case 470: /* stmt: JUMPV(albl) */
	case 469: /* stmt: RETF8(regf) */
	case 468: /* stmt: RETF4(regf) */
	case 467: /* stmt: RETU4(reg32) */
	case 466: /* stmt: RETI4(reg32) */
	case 464: /* stmt: RETP2(reg) */
	case 463: /* stmt: RETU2(reg) */
	case 462: /* stmt: RETI2(reg) */
	case 461: /* regf: CALLF8(albl) */
	case 460: /* regf: CALLF4(albl) */
	case 459: /* reg32: CALLU4(albl) */
	case 458: /* reg32: CALLI4(albl) */
	case 457: /* stmt: CALLV(albl) */
	case 456: /* reg: CALLP2(albl) */
	case 455: /* reg: CALLU2(albl) */
	case 454: /* reg: CALLI2(albl) */
	case 453: /* stmt: ARGF8(regf) */
	case 452: /* stmt: ARGF4(regf) */
	case 451: /* stmt: ARGU4(reg32) */
	case 450: /* stmt: ARGI4(reg32) */
	case 449: /* stmt: ARGP2(reg) */
	case 448: /* stmt: ARGU2(reg) */
	case 447: /* stmt: ARGI2(reg) */
	case 226: /* reg32: BCOMU4(reg32) */
	case 225: /* reg32: BCOMI4(reg32) */
	case 224: /* reg: BCOMU2(reg) */
	case 223: /* reg: BCOMI2(reg) */
	case 199: /* regf: NEGF8(regf) */
	case 197: /* regf: NEGF4(regf) */
	case 195: /* reg32: NEGI4(reg32) */
	case 193: /* reg: NEGI2(reg) */
	case 120: /* reg: CVUP2(reg) */
	case 119: /* reg: CVPU2(reg) */
	case 118: /* regf: CVFF8(regf) */
	case 117: /* regf: CVFF4(regf) */
	case 116: /* reg: CVFI4(regf) */
	case 115: /* reg: CVFI2(regf) */
	case 114: /* regf: CVIF8(reg32) */
	case 113: /* regf: CVIF8(reg) */
	case 112: /* regf: CVIF8(reg8) */
	case 111: /* regf: CVIF4(reg32) */
	case 110: /* regf: CVIF4(reg) */
	case 109: /* regf: CVIF4(reg8) */
	case 108: /* reg32: CVUU4(reg) */
	case 107: /* reg32: CVUI4(reg) */
	case 106: /* reg32: CVIU4(reg) */
	case 105: /* reg32: CVII4(reg) */
	case 104: /* reg32: CVUU4(reg8) */
	case 103: /* reg32: CVUI4(reg8) */
	case 102: /* reg32: CVIU4(reg8) */
	case 101: /* reg32: CVII4(reg8) */
	case 100: /* reg: CVUU2(reg32) */
	case 99: /* reg: CVUI2(reg32) */
	case 98: /* reg: CVIU2(reg32) */
	case 97: /* reg: CVII2(reg32) */
	case 96: /* reg: CVUU2(reg8) */
	case 95: /* reg: CVUI2(reg8) */
	case 94: /* reg: CVIU2(reg8) */
	case 93: /* reg: CVII2(reg8) */
	case 92: /* reg8: CVUU1(reg32) */
	case 91: /* reg8: CVUI1(reg32) */
	case 90: /* reg8: CVIU1(reg32) */
	case 89: /* reg8: CVII1(reg32) */
	case 88: /* reg8: CVUU1(reg) */
	case 87: /* reg8: CVUI1(reg) */
	case 86: /* reg8: CVIU1(reg) */
	case 85: /* reg8: CVII1(reg) */
	case 84: /* regf: INDIRF8(addr) */
	case 83: /* regf: INDIRF4(addr) */
	case 82: /* reg32: INDIRU4(addr) */
	case 81: /* reg32: INDIRI4(addr) */
	case 80: /* reg: INDIRP2(addr) */
	case 79: /* reg: INDIRU2(addr) */
	case 78: /* reg: INDIRI2(addr) */
	case 77: /* reg8: INDIRU1(addr) */
	case 76: /* reg8: INDIRI1(addr) */
	case 30: /* regf: LOADF8(regf) */
	case 29: /* regf: LOADF4(regf) */
	case 28: /* reg: LOADP2(reg) */
	case 27: /* reg32: LOADU4(reg32) */
	case 26: /* reg32: LOADI4(reg32) */
	case 25: /* reg: LOADU2(reg) */
	case 24: /* reg: LOADI2(reg) */
	case 23: /* reg8: LOADU1(reg) */
	case 22: /* reg8: LOADU1(reg8) */
	case 21: /* reg8: LOADI1(reg) */
	case 20: /* reg8: LOADI1(reg8) */
		kids[0] = LEFT_CHILD(p);
		break;
	case 32: /* reg8: LOADI1(LOADI2(CVUU2(reg8))) */
	case 31: /* reg8: LOADU1(LOADU2(CVII2(reg8))) */
		kids[0] = LEFT_CHILD(LEFT_CHILD(LEFT_CHILD(p)));
		break;
	case 445: /* stmt: GTF8(regf,regf) */
	case 443: /* stmt: GTF4(regf,regf) */
	case 441: /* stmt: GTU4(reg32,reg32) */
	case 439: /* stmt: GTI4(reg32,reg32) */
	case 434: /* stmt: GTU2(reg,con) */
	case 432: /* stmt: GTU2(reg,reg) */
	case 427: /* stmt: GTI2(reg,con) */
	case 425: /* stmt: GTI2(reg,reg) */
	case 423: /* stmt: GEF8(regf,regf) */
	case 421: /* stmt: GEF4(regf,regf) */
	case 419: /* stmt: GEU4(reg32,reg32) */
	case 417: /* stmt: GEI4(reg32,reg32) */
	case 412: /* stmt: GEU2(reg,con) */
	case 410: /* stmt: GEU2(reg,reg) */
	case 405: /* stmt: GEI2(reg,con) */
	case 403: /* stmt: GEI2(reg,reg) */
	case 401: /* stmt: LTF8(regf,regf) */
	case 399: /* stmt: LTF4(regf,regf) */
	case 397: /* stmt: LTU4(reg32,reg32) */
	case 395: /* stmt: LTI4(reg32,reg32) */
	case 390: /* stmt: LTU2(reg,con) */
	case 388: /* stmt: LTU2(reg,reg) */
	case 383: /* stmt: LTI2(reg,con) */
	case 381: /* stmt: LTI2(reg,reg) */
	case 379: /* stmt: LEF8(regf,regf) */
	case 377: /* stmt: LEF4(regf,regf) */
	case 375: /* stmt: LEU4(reg32,reg32) */
	case 373: /* stmt: LEI4(reg32,reg32) */
	case 368: /* stmt: LEU2(reg,con) */
	case 366: /* stmt: LEU2(reg,reg) */
	case 361: /* stmt: LEI2(reg,con) */
	case 359: /* stmt: LEI2(reg,reg) */
	case 357: /* stmt: NEF8(regf,regf) */
	case 355: /* stmt: NEF4(regf,regf) */
	case 353: /* stmt: NEU4(reg32,reg32) */
	case 351: /* stmt: NEI4(reg32,reg32) */
	case 346: /* stmt: NEU2(reg,con) */
	case 344: /* stmt: NEU2(reg,reg) */
	case 339: /* stmt: NEI2(reg,con) */
	case 337: /* stmt: NEI2(reg,reg) */
	case 335: /* stmt: EQF8(regf,regf) */
	case 333: /* stmt: EQF4(regf,regf) */
	case 331: /* stmt: EQU4(reg32,reg32) */
	case 329: /* stmt: EQI4(reg32,reg32) */
	case 324: /* stmt: EQU2(reg,con) */
	case 322: /* stmt: EQU2(reg,reg) */
	case 317: /* stmt: EQI2(reg,con) */
	case 315: /* stmt: EQI2(reg,reg) */
	case 314: /* reg32: RSHU4(reg32,con1) */
	case 313: /* reg32: RSHI4(reg32,con1) */
	case 310: /* reg8: RSHU2(reg8,con) */
	case 307: /* reg8: RSHI2(reg8,con) */
	case 304: /* reg8: LSHU2(reg8,con) */
	case 301: /* reg8: LSHI2(reg8,con) */
	case 300: /* reg: RSHU2(reg,con1) */
	case 299: /* reg: RSHI2(reg,con1) */
	case 298: /* reg: LSHU2(reg,con1) */
	case 297: /* reg: LSHI2(reg,con1) */
	case 295: /* regf: DIVF8(regf,regf) */
	case 293: /* regf: DIVF4(regf,regf) */
	case 291: /* regf: MULF8(regf,regf) */
	case 289: /* regf: MULF4(regf,regf) */
	case 287: /* reg32: MODU4(reg32,reg32) */
	case 285: /* reg32: MODI4(reg32,reg32) */
	case 283: /* reg32: DIVU4(reg32,reg32) */
	case 281: /* reg32: DIVI4(reg32,reg32) */
	case 279: /* reg32: MULU4(reg32,reg32) */
	case 277: /* reg32: MULI4(reg32,reg32) */
	case 276: /* reg: MODU2(reg,reg) */
	case 275: /* reg: MODI2(reg,reg) */
	case 274: /* reg: DIVU2(reg,reg) */
	case 273: /* reg: DIVI2(reg,reg) */
	case 272: /* reg: MULU2(reg,reg) */
	case 271: /* reg: MULI2(reg,reg) */
	case 269: /* reg32: BXORU4(reg32,reg32) */
	case 267: /* reg32: BXORI4(reg32,reg32) */
	case 264: /* reg8: BXORU2(reg8,con) */
	case 258: /* reg8: BXORI2(reg8,con) */
	case 254: /* reg: BXORU2(reg,con) */
	case 252: /* reg: BXORU2(reg,reg) */
	case 251: /* reg: BXORI2(reg,con) */
	case 249: /* reg: BXORI2(reg,reg) */
	case 247: /* reg32: BORU4(reg32,reg32) */
	case 245: /* reg32: BORI4(reg32,reg32) */
	case 242: /* reg8: BORU2(reg8,con) */
	case 236: /* reg8: BORI2(reg8,con) */
	case 232: /* reg: BORU2(reg,con) */
	case 230: /* reg: BORU2(reg,reg) */
	case 229: /* reg: BORI2(reg,con) */
	case 227: /* reg: BORI2(reg,reg) */
	case 221: /* reg32: BANDU4(reg32,reg32) */
	case 219: /* reg32: BANDI4(reg32,reg32) */
	case 216: /* reg8: BANDU2(reg8,con) */
	case 210: /* reg8: BANDI2(reg8,con) */
	case 206: /* reg: BANDU2(reg,con) */
	case 204: /* reg: BANDU2(reg,reg) */
	case 203: /* reg: BANDI2(reg,con) */
	case 201: /* reg: BANDI2(reg,reg) */
	case 185: /* regf: SUBF8(regf,regf) */
	case 183: /* regf: SUBF4(regf,regf) */
	case 181: /* reg32: SUBU4(reg32,reg32) */
	case 179: /* reg32: SUBI4(reg32,reg32) */
	case 176: /* reg8: SUBU2(reg8,con) */
	case 170: /* reg8: SUBI2(reg8,con) */
	case 166: /* reg: ADDP2(reg,con) */
	case 165: /* reg: SUBP2(reg,reg) */
	case 164: /* reg: SUBU2(reg,con1) */
	case 163: /* reg: SUBU2(reg,con) */
	case 161: /* reg: SUBU2(reg,reg) */
	case 160: /* reg: SUBI2(reg,con1) */
	case 159: /* reg: SUBI2(reg,con) */
	case 157: /* reg: SUBI2(reg,reg) */
	case 149: /* regf: ADDF8(regf,regf) */
	case 147: /* regf: ADDF4(regf,regf) */
	case 145: /* reg32: ADDU4(reg32,reg32) */
	case 143: /* reg32: ADDI4(reg32,reg32) */
	case 140: /* reg8: ADDU2(reg8,con) */
	case 134: /* reg8: ADDI2(reg8,con) */
	case 130: /* reg: ADDP2(reg,con) */
	case 129: /* reg: ADDP2(reg,reg) */
	case 128: /* reg: ADDU2(reg,con1) */
	case 127: /* reg: ADDU2(reg,con) */
	case 125: /* reg: ADDU2(reg,reg) */
	case 124: /* reg: ADDI2(reg,con1) */
	case 123: /* reg: ADDI2(reg,con) */
	case 121: /* reg: ADDI2(reg,reg) */
	case 74: /* stmt: ASGNF8(addr,regf) */
	case 72: /* stmt: ASGNF4(addr,regf) */
	case 70: /* stmt: ASGNU4(addr,reg32) */
	case 68: /* stmt: ASGNI4(addr,reg32) */
	case 66: /* stmt: ASGNP2(addr,reg) */
	case 65: /* stmt: ASGNU2(addr,reg) */
	case 64: /* stmt: ASGNI2(addr,reg) */
	case 63: /* stmt: ASGNU1(addr,reg8) */
	case 62: /* stmt: ASGNI1(addr,reg8) */
	case 60: /* reg: SUBP2(reg,con) */
	case 59: /* reg: ADDP2(reg,con) */
	case 58: /* addr: SUBP2(reg,con) */
	case 57: /* addr: ADDP2(reg,con) */
		kids[0] = LEFT_CHILD(p);
		kids[1] = RIGHT_CHILD(p);
		break;
	case 446: /* stmt: GTF8(regf,INDIRF8(addr)) */
	case 444: /* stmt: GTF4(regf,INDIRF4(addr)) */
	case 442: /* stmt: GTU4(reg32,INDIRU4(addr)) */
	case 440: /* stmt: GTI4(reg32,INDIRI4(addr)) */
	case 433: /* stmt: GTU2(reg,INDIRU2(reg)) */
	case 426: /* stmt: GTI2(reg,INDIRI2(reg)) */
	case 424: /* stmt: GEF8(regf,INDIRF8(addr)) */
	case 422: /* stmt: GEF4(regf,INDIRF4(addr)) */
	case 420: /* stmt: GEU4(reg32,INDIRU4(addr)) */
	case 418: /* stmt: GEI4(reg32,INDIRI4(addr)) */
	case 411: /* stmt: GEU2(reg,INDIRU2(reg)) */
	case 404: /* stmt: GEI2(reg,INDIRI2(reg)) */
	case 402: /* stmt: LTF8(regf,INDIRF8(addr)) */
	case 400: /* stmt: LTF4(regf,INDIRF4(addr)) */
	case 398: /* stmt: LTU4(reg32,INDIRU4(addr)) */
	case 396: /* stmt: LTI4(reg32,INDIRI4(addr)) */
	case 389: /* stmt: LTU2(reg,INDIRU2(reg)) */
	case 382: /* stmt: LTI2(reg,INDIRI2(reg)) */
	case 380: /* stmt: LEF8(regf,INDIRF8(addr)) */
	case 378: /* stmt: LEF4(regf,INDIRF4(addr)) */
	case 376: /* stmt: LEU4(reg32,INDIRU4(addr)) */
	case 374: /* stmt: LEI4(reg32,INDIRI4(addr)) */
	case 367: /* stmt: LEU2(reg,INDIRU2(reg)) */
	case 360: /* stmt: LEI2(reg,INDIRI2(reg)) */
	case 358: /* stmt: NEF8(regf,INDIRF8(addr)) */
	case 356: /* stmt: NEF4(regf,INDIRF4(addr)) */
	case 354: /* stmt: NEU4(reg32,INDIRU4(addr)) */
	case 352: /* stmt: NEI4(reg32,INDIRI4(addr)) */
	case 345: /* stmt: NEU2(reg,INDIRU2(reg)) */
	case 338: /* stmt: NEI2(reg,INDIRI2(reg)) */
	case 336: /* stmt: EQF8(regf,INDIRF8(addr)) */
	case 334: /* stmt: EQF4(regf,INDIRF4(addr)) */
	case 332: /* stmt: EQU4(reg32,INDIRU4(addr)) */
	case 330: /* stmt: EQI4(reg32,INDIRI4(addr)) */
	case 323: /* stmt: EQU2(reg,INDIRU2(lgaddr)) */
	case 316: /* stmt: EQI2(reg,INDIRI2(lgaddr)) */
	case 296: /* regf: DIVF8(regf,INDIRF8(addr)) */
	case 294: /* regf: DIVF4(regf,INDIRF4(addr)) */
	case 292: /* regf: MULF8(regf,INDIRF8(addr)) */
	case 290: /* regf: MULF4(regf,INDIRF4(addr)) */
	case 288: /* reg32: MODU4(reg32,INDIRU4(addr)) */
	case 286: /* reg32: MODI4(reg32,INDIRI4(addr)) */
	case 284: /* reg32: DIVU4(reg32,INDIRU4(addr)) */
	case 282: /* reg32: DIVI4(reg32,INDIRI4(addr)) */
	case 280: /* reg32: MULU4(reg32,INDIRU4(addr)) */
	case 278: /* reg32: MULI4(reg32,INDIRI4(addr)) */
	case 270: /* reg32: BXORU4(reg32,INDIRU4(addr)) */
	case 268: /* reg32: BXORI4(reg32,INDIRI4(addr)) */
	case 253: /* reg: BXORU2(reg,INDIRU2(lgaddr)) */
	case 250: /* reg: BXORI2(reg,INDIRI2(lgaddr)) */
	case 248: /* reg32: BORU4(reg32,INDIRU4(addr)) */
	case 246: /* reg32: BORI4(reg32,INDIRI4(addr)) */
	case 231: /* reg: BORU2(reg,INDIRU2(lgaddr)) */
	case 228: /* reg: BORI2(reg,INDIRI2(lgaddr)) */
	case 222: /* reg32: BANDU4(reg32,INDIRU4(addr)) */
	case 220: /* reg32: BANDI4(reg32,INDIRI4(addr)) */
	case 205: /* reg: BANDU2(reg,INDIRU2(lgaddr)) */
	case 202: /* reg: BANDI2(reg,INDIRI2(lgaddr)) */
	case 186: /* regf: SUBF8(regf,INDIRF8(addr)) */
	case 184: /* regf: SUBF4(regf,INDIRF4(addr)) */
	case 182: /* reg32: SUBU4(reg32,INDIRU4(addr)) */
	case 180: /* reg32: SUBI4(reg32,INDIRI4(addr)) */
	case 162: /* reg: SUBU2(reg,INDIRU2(addr)) */
	case 158: /* reg: SUBI2(reg,INDIRI2(addr)) */
	case 150: /* regf: ADDF8(regf,INDIRF8(addr)) */
	case 148: /* regf: ADDF4(regf,INDIRF4(addr)) */
	case 146: /* reg32: ADDU4(reg32,INDIRU4(addr)) */
	case 144: /* reg32: ADDI4(reg32,INDIRI4(addr)) */
	case 126: /* reg: ADDU2(reg,INDIRU2(addr)) */
	case 122: /* reg: ADDI2(reg,INDIRI2(addr)) */
	case 75: /* stmt: ASGNF8(addr,INDIRF8(addr)) */
	case 73: /* stmt: ASGNF4(addr,INDIRF4(addr)) */
	case 71: /* stmt: ASGNU4(addr,INDIRU4(addr)) */
	case 69: /* stmt: ASGNI4(addr,INDIRI4(addr)) */
	case 67: /* stmt: ASGNB(reg,INDIRB(reg)) */
		kids[0] = LEFT_CHILD(p);
		kids[1] = LEFT_CHILD(RIGHT_CHILD(p));
		break;
	case 261: /* reg8: BXORU2(reg8,CVUU2(INDIRU1(lgaddr))) */
	case 255: /* reg8: BXORI2(reg8,CVII2(INDIRI1(lgaddr))) */
	case 239: /* reg8: BORU2(reg8,CVUU2(INDIRU1(lgaddr))) */
	case 233: /* reg8: BORI2(reg8,CVII2(INDIRI1(lgaddr))) */
	case 213: /* reg8: BANDU2(reg8,CVUU2(INDIRU1(lgaddr))) */
	case 207: /* reg8: BANDI2(reg8,CVII2(INDIRI1(lgaddr))) */
	case 173: /* reg8: SUBU2(reg8,CVUU2(INDIRU1(addr))) */
	case 167: /* reg8: SUBI2(reg8,CVII2(INDIRI1(addr))) */
	case 137: /* reg8: ADDU2(reg8,CVUU2(INDIRU1(addr))) */
	case 131: /* reg8: ADDI2(reg8,CVII2(INDIRI1(addr))) */
		kids[0] = LEFT_CHILD(p);
		kids[1] = LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(p)));
		break;
	case 436: /* stmt: GTU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 435: /* stmt: GTU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 429: /* stmt: GTI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 428: /* stmt: GTI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 414: /* stmt: GEU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 413: /* stmt: GEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 407: /* stmt: GEI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 406: /* stmt: GEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 392: /* stmt: LTU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 391: /* stmt: LTU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 385: /* stmt: LTI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 384: /* stmt: LTI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 370: /* stmt: LEU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 369: /* stmt: LEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 363: /* stmt: LEI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 362: /* stmt: LEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 348: /* stmt: NEU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 347: /* stmt: NEU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 341: /* stmt: NEI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 340: /* stmt: NEI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 326: /* stmt: EQU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 325: /* stmt: EQU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 319: /* stmt: EQI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 318: /* stmt: EQI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 263: /* reg8: BXORU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 262: /* reg8: BXORU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 257: /* reg8: BXORI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 256: /* reg8: BXORI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 241: /* reg8: BORU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 240: /* reg8: BORU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 235: /* reg8: BORI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 234: /* reg8: BORI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 215: /* reg8: BANDU2(CVIU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 214: /* reg8: BANDU2(CVUU2(reg8),CVUU2(INDIRU1(lgaddr))) */
	case 209: /* reg8: BANDI2(CVUI2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 208: /* reg8: BANDI2(CVII2(reg8),CVII2(INDIRI1(lgaddr))) */
	case 175: /* reg8: SUBU2(CVIU2(reg8),CVUU2(INDIRU1(addr))) */
	case 174: /* reg8: SUBU2(CVUU2(reg8),CVUU2(INDIRU1(addr))) */
	case 169: /* reg8: SUBI2(CVUI2(reg8),CVII2(INDIRI1(addr))) */
	case 168: /* reg8: SUBI2(CVII2(reg8),CVII2(INDIRI1(addr))) */
	case 139: /* reg8: ADDU2(CVIU2(reg8),CVUU2(INDIRU1(addr))) */
	case 138: /* reg8: ADDU2(CVUU2(reg8),CVUU2(INDIRU1(addr))) */
	case 133: /* reg8: ADDI2(CVUI2(reg8),CVII2(INDIRI1(addr))) */
	case 132: /* reg8: ADDI2(CVII2(reg8),CVII2(INDIRI1(addr))) */
		kids[0] = LEFT_CHILD(LEFT_CHILD(p));
		kids[1] = LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(p)));
		break;
	case 438: /* stmt: GTU2(CVIU2(reg8),con) */
	case 437: /* stmt: GTU2(CVUU2(reg8),con) */
	case 431: /* stmt: GTI2(CVUI2(reg8),con) */
	case 430: /* stmt: GTI2(CVII2(reg8),con) */
	case 416: /* stmt: GEU2(CVIU2(reg8),con) */
	case 415: /* stmt: GEU2(CVUU2(reg8),con) */
	case 409: /* stmt: GEI2(CVUI2(reg8),con) */
	case 408: /* stmt: GEI2(CVII2(reg8),con) */
	case 394: /* stmt: LTU2(CVIU2(reg8),con) */
	case 393: /* stmt: LTU2(CVUU2(reg8),con) */
	case 387: /* stmt: LTI2(CVUI2(reg8),con) */
	case 386: /* stmt: LTI2(CVII2(reg8),con) */
	case 372: /* stmt: LEU2(CVIU2(reg8),con) */
	case 371: /* stmt: LEU2(CVUU2(reg8),con) */
	case 365: /* stmt: LEI2(CVUI2(reg8),con) */
	case 364: /* stmt: LEI2(CVII2(reg8),con) */
	case 350: /* stmt: NEU2(CVIU2(reg8),con) */
	case 349: /* stmt: NEU2(CVUU2(reg8),con) */
	case 343: /* stmt: NEI2(CVUI2(reg8),con) */
	case 342: /* stmt: NEI2(CVII2(reg8),con) */
	case 328: /* stmt: EQU2(CVIU2(reg8),con) */
	case 327: /* stmt: EQU2(CVUU2(reg8),con) */
	case 321: /* stmt: EQI2(CVUI2(reg8),con) */
	case 320: /* stmt: EQI2(CVII2(reg8),con) */
	case 312: /* reg8: RSHU2(CVIU2(reg8),con) */
	case 311: /* reg8: RSHU2(CVUU2(reg8),con) */
	case 309: /* reg8: RSHI2(CVUI2(reg8),con) */
	case 308: /* reg8: RSHI2(CVII2(reg8),con) */
	case 306: /* reg8: LSHU2(CVIU2(reg8),con) */
	case 305: /* reg8: LSHU2(CVUU2(reg8),con) */
	case 303: /* reg8: LSHI2(CVUI2(reg8),con) */
	case 302: /* reg8: LSHI2(CVII2(reg8),con) */
	case 266: /* reg8: BXORU2(CVIU2(reg8),con) */
	case 265: /* reg8: BXORU2(CVUU2(reg8),con) */
	case 260: /* reg8: BXORI2(CVUI2(reg8),con) */
	case 259: /* reg8: BXORI2(CVII2(reg8),con) */
	case 244: /* reg8: BORU2(CVIU2(reg8),con) */
	case 243: /* reg8: BORU2(CVUU2(reg8),con) */
	case 238: /* reg8: BORI2(CVUI2(reg8),con) */
	case 237: /* reg8: BORI2(CVII2(reg8),con) */
	case 218: /* reg8: BANDU2(CVIU2(reg8),con) */
	case 217: /* reg8: BANDU2(CVUU2(reg8),con) */
	case 212: /* reg8: BANDI2(CVUI2(reg8),con) */
	case 211: /* reg8: BANDI2(CVII2(reg8),con) */
	case 178: /* reg8: SUBU2(CVIU2(reg8),con) */
	case 177: /* reg8: SUBU2(CVUU2(reg8),con) */
	case 172: /* reg8: SUBI2(CVUI2(reg8),con) */
	case 171: /* reg8: SUBI2(CVII2(reg8),con) */
	case 142: /* reg8: ADDU2(CVIU2(reg8),con) */
	case 141: /* reg8: ADDU2(CVUU2(reg8),con) */
	case 136: /* reg8: ADDI2(CVUI2(reg8),con) */
	case 135: /* reg8: ADDI2(CVII2(reg8),con) */
		kids[0] = LEFT_CHILD(LEFT_CHILD(p));
		kids[1] = RIGHT_CHILD(p);
		break;
	case 192: /* stmt: ASGNF8(addr,SUBF8(INDIRF8(addr),INDIRF8(addr))) */
	case 191: /* stmt: ASGNF8(addr,SUBF8(INDIRF8(addr),INDIRF8(addr))) */
	case 190: /* stmt: ASGNF4(addr,SUBF4(INDIRF4(addr),INDIRF4(addr))) */
	case 189: /* stmt: ASGNF4(addr,SUBF4(INDIRF4(addr),INDIRF4(addr))) */
	case 188: /* stmt: ASGNI4(addr,SUBI4(INDIRI4(addr),INDIRI4(addr))) */
	case 187: /* stmt: ASGNI4(addr,SUBI4(INDIRI4(addr),INDIRI4(addr))) */
	case 156: /* stmt: ASGNF8(addr,ADDF8(INDIRF8(addr),INDIRF8(addr))) */
	case 155: /* stmt: ASGNF8(addr,ADDF8(INDIRF8(addr),INDIRF8(addr))) */
	case 154: /* stmt: ASGNF4(addr,ADDF4(INDIRF4(addr),INDIRF4(addr))) */
	case 153: /* stmt: ASGNF4(addr,ADDF4(INDIRF4(addr),INDIRF4(addr))) */
	case 152: /* stmt: ASGNI4(addr,ADDI4(INDIRI4(addr),INDIRI4(addr))) */
	case 151: /* stmt: ASGNI4(addr,ADDI4(INDIRI4(addr),INDIRI4(addr))) */
		kids[0] = LEFT_CHILD(p);
		kids[1] = LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(p)));
		kids[2] = LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(p)));
		break;
	case 200: /* regf: NEGF8(INDIRF8(addr)) */
	case 198: /* regf: NEGF4(INDIRF4(addr)) */
	case 196: /* reg32: NEGI4(INDIRI4(addr)) */
	case 194: /* reg: NEGI2(INDIRI2(addr)) */
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
