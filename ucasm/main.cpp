/* 
 * 
 *    main.cpp - this file is part of Microcode Assembler
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
#include <vector>
#include <set>
#include "Microcode.h"
#include "Lexer.h"
#include "Parser.h"

using namespace std;
using namespace ucasm;

int main (int argc, char * const argv[]) {

	if (argc != 2) {
		std::cout << "Usage: ucasm <microcode_file>" << endl;
		return -1;
	}
	else {
		try {

			ifstream inFile(argv[1], ios::in);
			if (inFile.is_open()) {

				// parse microcode
				Microcode* m = new Microcode();
				Lexer* l = new Lexer();
				Parser* p = new Parser(l, m);

				p->Parse(inFile);

				// parsing complete
				cout << "Parsing completed." << endl;

				delete l;
				delete p;

				// everyting went well - write microcode files
				cout << "Saving microcode file 000" << endl;
				m->saveHEX(0, "microcode000.hex");
				m->saveBIN(0, "microcode000.bin");
				cout << "Saving microcode file 001" << endl;
				m->saveHEX(1, "microcode001.hex");
				m->saveBIN(1, "microcode001.bin");
				cout << "Saving microcode file 002" << endl;
				m->saveHEX(2, "microcode002.hex");
				m->saveBIN(2, "microcode002.bin");
				cout << "Saving microcode file 003" << endl;
				m->saveHEX(3, "microcode003.hex");
				m->saveBIN(3, "microcode003.bin");

				delete m;

			}
			else {
				cout << "Unable to open '" << argv[1] << "'" << endl;
			}
		}
		catch (exception e) {
			cout << "Unable to read " << argv[1] << endl;
		}

		return 0;
	}
}
