/* 
 * 
 *    Parser.h - this file is part of Microcode Assembler
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


namespace ucasm {

class Parser {

	Lexer* lexer;
	Microcode* ucode;

	token currentToken;
	int currentOpcode;
	int currentLine;
	int currentFlags;
	int flagC, flagZ, flagN, flagV;
	token addressBus;
	int busIfcFieldInUse;

	set<int> usedTokens;
	set<int> usedSteps;

	void err(const char* msg);
	void parseOpcode(ifstream& s);
	void parseLine(ifstream& s);
	void parseFlags(ifstream& s);
	void parseMicroinstructions(ifstream& s, MicrocodeWord& ucword);
	void parseTransfer(ifstream& s, MicrocodeWord& ucword);

	int accept(ifstream& s, token t);
	int expect(ifstream& s, token t);
	int see(ifstream& s, token t);

public:

	Parser(Lexer* l, Microcode* m);
	void Parse(ifstream& s);

};

};
