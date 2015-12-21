/* 
 * 
 *    Lexer.cpp - this file is part of Microcode Assembler
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

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "Lexer.h"

using namespace ucasm;
using namespace std;

/**************************************************************
 *
 * Lexical analyzer constructor. Set defaults.
 *
 **************************************************************/
Lexer::Lexer() {
	line = 1;
	val = 0;
	endlpos = 0;
}

/**************************************************************
 *
 * Get lexical symbol to be used by parser
 * Symbols are defined in tokens.h
 *
 **************************************************************/
token Lexer::getToken(ifstream& f) {

	char c;

	// fast forward through whitespace and comments, increase line count
	c = f.get();
	while (isspace(c) || c== '\r' || c=='/') {
		if (f.eof()) return END;
		if (c == '\n')
		{
			line++;
			endlpos = f.tellg();
		}
		else if (c == '/') {
			c = f.get();
			if (c == '/') {
				while ((c = f.get()) != '\n') {
					if (f.eof()) return END;
				};
				line++;
				endlpos = f.tellg();
			}
			else {
				err("Expected / and comment");
				return ERROR;
			}
		}
		c = f.get();
	};

	// store current pos
	currentpos = f.tellg();

	// read identifier: register, OP, ENDOP, MEM
	if (isalpha(c)) {
		string s;
		s += toupper(c);
		while (isalpha(c = f.get()) || c == '_') {
			s += toupper(c);
		}
		f.unget();
		// OP, ENDOP
		if (s=="OP") return OP;
		else if (s=="ENDOP") return ENDOP;
		// registers
		else if (s=="A") return A;
		else if (s=="X") return X;
		else if (s=="Y") return Y;
		else if (s=="MDR") return MDR;
		else if (s=="PC") return PC;
		else if (s=="PPC") return PPC;
		else if (s=="DP") return DP;
		else if (s=="SP") return SP;
		else if (s=="USP") return USP;
		else if (s=="MAR") return MAR;
		else if (s=="IR") return IR;
		else if (s=="MSW") return MSW;
		else if (s=="IPTR") return IPTR;
		// shifter
		else if (s=="SHR") return SHR;
		// byte qualifier
		else if (s=="HI") return HI;
		else if (s=="LO") return LO;
		// flags
		else if (s=="C") return C;
		else if (s=="Z") return Z;
		else if (s=="N") return N;
		else if (s=="V") return V;
		else if (s=="SETFLAGS_WORD") return SETFLAGS_WORD;
		else if (s=="SETFLAGS_HIBYTE") return SETFLAGS_HIBYTE;
		else if (s=="SETFLAGS_LOBYTE") return SETFLAGS_LOBYTE;
		// memory selector
		else if (s=="MEM") return MEM;
		// special
		else if (s=="LATCH_I") return LATCH_I;
		else if (s=="LATCH_S") return LATCH_S;
		else if (s=="FETCH") return FETCH;
		else if (s=="CODE") return CODE;
		else if (s=="DATA") return DATA;
		else if (s=="SUPERVISOR") return SUPERVISOR;
		else {
			string err_s = "Invalid identifier: ";
			err_s += s;
			err(err_s.c_str());
			return ERROR;
		}
	}

	// read decimal number
	else if (isdigit(c)) {
		string s;
		s += c;
		while (isdigit(c = f.get())) {
			s += c;
		}
		f.unget();
		val = atoi(s.c_str());
		return DECVAL;
	}

	// read hexadecimal number
	else if (c=='$') {
		string s;
		while (isxdigit(c = f.get())) {
			s += c;
		}
		f.unget();
		sscanf(s.c_str(), "%x", &val);
		return HEXVAL;
	}

	// read transfer operator
	else if (c=='<') {
		c = f.get();
		if (c=='-') {
			return TRANSFER;
		}
	}

	// read arithmetic
	else if (c=='+') {
		c = f.get();
		if (c=='+') {
			return INC;
		}
		else {
			f.unget();
			return PLUS;
		}
	}
	else if (c=='-') {
		c = f.get();
		if (c=='-') {
			return DEC;
		}
		else {
			f.unget();
			return MINUS;
		}
	}

	// read logic
	else if (c=='&') return AND;
	else if (c=='|') return OR;
	else if (c=='^') return XOR;

	// read special chars
	else if (c=='(') return LBR;
	else if (c==')') return RBR;
	else if (c==';') return SEMICOLON;
	else if (c==',') return COMMA;
	else if (c=='!') return NOT;
	else if (c=='*') return ANY;

	else if (f.eof()) return END;

	string s = "Invalid character: ";
	s += c;
	err(s.c_str());
	return ERROR;

}

/**************************************************************
 *
 * Get value associated to lexical symbols
 * DECVAL and HEXVAL
 *
 **************************************************************/
int Lexer::getVal() {
	return val;
}

/**************************************************************
 *
 * Get line number
 *
 **************************************************************/
int Lexer::getLine() {
	return line;
}

/**************************************************************
 *
 * Get position in current line
 *
 **************************************************************/
int Lexer::getPosInLine() {
	return currentpos - endlpos + 1;
}

/**************************************************************
 *
 * Print error message and exit
 *
 **************************************************************/
void Lexer::err(const char* msg) {
	cout << "LEX(line " << line << "): " << msg << endl;
	exit(-1);
}

