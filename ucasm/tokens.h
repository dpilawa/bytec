/* 
 * 
 *    tokens.h - this file is part of Microcode Assembler
 *   
 *    Copyright 2009, 2010, 2011 Dawid Pilawa
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

/*******************************************************
 *
 * Tokens returned by microcode lexical analyzer
 *
 *******************************************************/
enum token {
    
    // OP, ENDOP
    OP,
    ENDOP,
    
    // literals
    DECVAL,
    HEXVAL,
    
    // register identifiers
    A,
    X,
    Y,
    MDR,
    PC,
    PPC,    
    DP,
    SP,
    USP,
    MAR,
    IR,
    MSW,
    IPTR,
    MEM,
    
    // byte qualifiers
    HI,
    LO,
    
    // register transfer
    TRANSFER,
    
    // delimiters
    COMMA,
    SEMICOLON,
    LBR,
    RBR,
    
    // arithmetic
    PLUS,
    MINUS,
    INC,
    DEC,
    
    // logic
    AND,
    OR,
    XOR,
    
    // shifter
    SHR,
    
    // flags logic
    ANY,
    NOT,
    C,
    Z,
    N,
    V,
    SETFLAGS_WORD,
    SETFLAGS_HIBYTE,
    SETFLAGS_LOBYTE,
    
    // misc
    FETCH,
    CODE,
    DATA,
    SUPERVISOR,
    ERROR,
    END,
    LATCH_I,
    LATCH_S,
    
    // special
    MINUSONE
};
