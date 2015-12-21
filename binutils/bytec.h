/* 
 * 
 *    bytec.h - this file is part of BYTEC/16 binutils
 *   
 *    Copyright 2013 Dawid Pilawa
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

#ifndef _BYTEC_H
#define _BYTEC_H

/* CPU Id of TARGET machine (byte order coded in low order two bits) */
#define A_BYTEC16 0x16	/* BYTEC/16 */

/* modified nlist struct (added union to use n_strx instead of n_name */
struct nlist2 {			/* symbol table entry */
  union {
	  char n_name[8];		/* symbol name */
	  long n_strx;			/* byte offset into the string table */
  };
  long n_value;			/* value */
  unsigned char	n_sclass;	/* storage class */
  unsigned char	n_numaux;	/* number of auxiliary entries (not used) */
  unsigned short n_type;	/* language base and derived type (not used) */
};

#endif /* _BYTEC_H */
