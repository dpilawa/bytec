/* 
 * 
 *    Parser.cpp - this file is part of Microcode Assembler
 *   
 *    Copyright 2009, 2010, 2011, 2016 Dawid Pilawa
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
#include <vector>
#include <set>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include "Microcode.h"
#include "Lexer.h"
#include "Parser.h"

using namespace ucasm;
using namespace std;

/**************************************************************
 *
 * Parser constructor
 *
 **************************************************************/
Parser::Parser(Lexer* l, Microcode* m) {
	lexer = l;
	ucode = m;
}

/**************************************************************
 *
 * Accept token given in parameter and read next token
 *
 **************************************************************/
int Parser::accept(ifstream& s, token t) {
	if (currentToken==t) {
		currentToken = lexer->getToken(s);
		return 1;
	} else {
		return 0;
	}
}

/**************************************************************
 *
 * Return next visible token
 *
 **************************************************************/
int Parser::see(ifstream& s, token t) {
	if (currentToken==t) {
		return 1;
	} else {
		return 0;
	}
}

/**************************************************************
 *
 * Return 1 if current token as expected (provided), 0 otherwise
 *
 **************************************************************/
int Parser::expect(ifstream& s, token t) {
	if (accept(s, t)) {
		return 1;
	}
	else {
		return 0;
	}
}

/**************************************************************
 *
 * Top level parsing routine. Parse opcodes until EOF:
 *   opcode
 *   opcode
 *   ...
 *   opcode
 *   END
 *
 **************************************************************/
void Parser::Parse(ifstream& s) {
	currentToken = lexer->getToken(s);
	while (!accept(s, END)) {
		parseOpcode(s);
	}
}

/**************************************************************
 *
 * Parse opcode:
 *   opcode(OPCODE#)
 *		line
 *		line
 *		...
 *		line
 *   endop
 *
 **************************************************************/
void Parser::parseOpcode(ifstream& s) {

	if (!expect(s, OP))
	{
		err("Expected opcode definition");
	}

	if (!expect(s, LBR))
	{
		err("Expected (");
	}

	if (!expect(s, HEXVAL))
	{
		err("Expected 8-bit hexadecimal value");
	}
	else
	{
		// check if opcode# in range 00h-FFh or 100h-10Fh
		currentOpcode = lexer->getVal();
		if ((currentOpcode < 0) or (currentOpcode > 255 + 16))
		{
			err("Opcode out of range");
		}
		else
		{
			// check for opcode redefinition
			if (usedTokens.find(currentOpcode) != usedTokens.end())
			{
				err("Redefinition of opcode");
			}
			else
			{
				usedTokens.insert(currentOpcode);
			}
		}
	}

	if (!expect(s, RBR))
	{
		err("Expected )");
	}

	// parse lines
	usedSteps.clear();
	while (!accept(s, ENDOP))
	{
		parseLine(s);
	}

	// verify if steps are continuous in range 0..n
	for (unsigned int i=0; i < usedSteps.size(); i++)
	{
		if (usedSteps.find(i) == usedSteps.end())
		{
			stringstream s;
			s << "Non continuous instruction steps for opcode " << hex << setw(3) << setfill('0') << currentOpcode << endl;
			err(s.str().c_str());
		}
	}

}

/**************************************************************
 *
 * Parse line:
 *   STEP, FLAGS, microinstructions
 *
 **************************************************************/
void Parser::parseLine(ifstream& s)
{

	addressBus = ANY;
	busIfcFieldInUse = 0;
	currentLine = lexer->getVal();

	// step
	if (!expect(s, DECVAL))
	{
		err("Expected microcode step number or ENDOP");
	}
	else
	{
		// check if step in range [0, 31)
		if (currentLine<0 || currentLine>31)
		{
			err("Microcode step number out of bounds");
		}
	}

	if (!expect(s, COMMA))
	{
		err("Expected comma");
	}

	// flags
	parseFlags(s);

	if (!expect(s, COMMA))
	{
		err("Expected comma");
	}

	// parse microinstructions for current step
	MicrocodeWord ucword = MicrocodeWord();
	parseMicroinstructions(s, ucword);

	// store microcode word at addresses for selected flags
	int c, z, n, v;
	int address_base;

	address_base = (currentOpcode << 9) | (currentLine << 4);

	for (c=0; c<=1; c++)
		for (z=0; z<=1; z++)
			for (n=0; n<=1; n++)
				for (v=0; v<=1; v++)
				{
					if ((flagC == c || flagC == -1) && (flagZ == z || flagZ == -1) &&
					    (flagN == n || flagN == -1) && (flagV == v || flagV == -1))
					{

						// check for microcode step redefinition
						set<int>::iterator si;
						si = usedSteps.find((currentLine << 4) + c*8 + z*4 + n*2 + v);
						if (si != usedSteps.end())
						{
							err("Redefinition of microcode step");
						}
						else
						{
							usedSteps.insert((currentLine << 4) + c*8 + z*4 + n*2 + v);
						}

						// store microcode word
						ucode->storeWord(address_base + c*8 + z*4 + n*2 + v, ucword);
					}
				}
}

/**************************************************************
 *
 * Parse flags:
 *	 F -> *, f0, end
 *	 f0 -> !f1, f1, end
 *	 f1 -> C, Z, N, V
 *
 **************************************************************/
void Parser::parseFlags(ifstream& s)
{

	flagC = -1;
	flagZ = -1;
	flagN = -1;
	flagV = -1;

	if (accept(s, ANY))
	{
		// leave defaults
	}
	else {
		while(see(s, C) || see(s, Z) || see(s, N) || see(s, V) || see(s, NOT))
		{
			if (accept(s, NOT))
			{
				if (accept(s, C))
				{
					flagC = 0;
				}
				else if (accept(s, Z))
				{
					flagZ = 0;
				}
				else if (accept(s, N))
				{
					flagN = 0;
				}
				else if (accept(s, V))
				{
					flagV = 0;
				}
				else
				{
					err("Expected any of C, Z, N, V");
				}
			}
			else if (accept(s, C))
			{
					flagC = 1;
			}
			else if (accept(s, Z))
			{
					flagZ = 1;
			}
			else if (accept(s, N))
			{
					flagN = 1;
			}
			else if (accept(s, V))
			{
					flagV = 1;
			}
		}
	}
}

/**************************************************************
 *
 * Parse microinstructions:
 *   FETCH | SETFLAGS | SHR | CODE | DATA | SUPERVISOR | transfer
 *
 **************************************************************/
void Parser::parseMicroinstructions(ifstream& s, MicrocodeWord& ucword)
{

	while (!see(s, DECVAL) && !see(s, ENDOP))
	{

		// fetch
		if (accept(s, FETCH))
		{
			if (addressBus != ANY && (addressBus != PC))
			{
				err("Address bus conflict. FETCH is illegal in this step.");
			}
			else
			{
				ucword.setBits(ucMemSeg, ucMemSeg_Code);
				ucword.setBits(ucADRBus, ucADRBus_PC);
				ucword.setBits(ucLoadIR, ucLoadIR_En);
				ucword.setBits(ucIncPC, ucIncPC_En);
				ucword.setBits(ucMemOp, ucMemOp_En);
				addressBus = PC;
			}
		}

		// IRET
		else if (accept(s, IRET))
		{
			ucword.setBits(ucIRET, ucIRET_En);
		}
		
		// misc latch
		else if (accept(s, LATCH_I))
		{
			if (busIfcFieldInUse == 0)
			{
				ucword.setBits(ucMiscLatch, ucMiscLatch_I);
				busIfcFieldInUse = 1;
			}
			else
			{
				err("Data-memory bus interface use and misc signal latching (I, S) must be exclusive and it was already used.");
			}
		}

		else if (accept(s, LATCH_S))
		{
			if (busIfcFieldInUse == 0)
			{
				ucword.setBits(ucMiscLatch, ucMiscLatch_S);
				busIfcFieldInUse = 1;
			}
			else
			{
				err("Data-memory bus interface use and misc signal latching (I, S) must be exclusive and it was already used.");
			}
		}

		// setflags
		else if (accept(s, SETFLAGS_WORD))
		{
			ucword.setBits(ucLoadFlags, ucLoadFlags_Word);
		}
		else if (accept(s, SETFLAGS_HIBYTE))
		{
			ucword.setBits(ucLoadFlags, ucLoadFlags_HiByte);
		}
		else if (accept(s, SETFLAGS_LOBYTE))
		{
			ucword.setBits(ucLoadFlags, ucLoadFlags_LoByte);
		}

		// shifter
		else if (accept(s, SHR))
		{
			ucword.setBits(ucALUShiftR, ucALUShiftR_En);
		}

		// code
		else if (accept(s, CODE))
		{
			ucword.setBits(ucMemSeg, ucMemSeg_Code);
		}

		// data
		else if (accept(s, DATA))
		{
			ucword.setBits(ucMemSeg, ucMemSeg_Data);
		}

		// protected
		else if (accept(s, SUPERVISOR))
		{
			ucword.setBits(ucSupervisor, ucSupervisor_En);
		}

		// transfer operation: ? <- ?, or reg++/reg--
		else
		{
			parseTransfer(s, ucword);
		}

		accept(s, SEMICOLON);

	}

}

/**************************************************************
 *
 * Parse transfer operation:
 *	 ? <- ?, reg++, reg--
 *
 **************************************************************/
void Parser::parseTransfer(ifstream& s, MicrocodeWord& ucword)
{
	token destToken = currentToken;
	token destByte;
	token unaryOperand, firstOperand, secondOperand;
	token currentAdrBus;
	token op1;
	bool unary = false;
	bool unary_minus_1 = false;

	// simple register destinations
	// REG <- ?;
	if (accept(s, MDR))
	{
		ucword.setBits(ucLoad, ucLoad_MDR);
	}
	else if (accept(s, A))
	{
		ucword.setBits(ucLoad, ucLoad_A);
	}
	else if (accept(s, X))
	{
		ucword.setBits(ucLoad, ucLoad_X);
	}
	else if (accept(s, Y))
	{
		ucword.setBits(ucLoad, ucLoad_Y);
	}
	else if (accept(s, MAR))
	{
		// MAR++;
		if (accept(s, INC))
		{
			ucword.setBits(ucIncMAR, ucIncMAR_En);
			return;
		}
		// MAR < ?;
		else
		{
			ucword.setBits(ucLoad, ucLoad_MAR);
		}
	}
	else if (accept(s, SP))
	{
		// SP++;
		if (accept(s, INC))
		{
			ucword.setBits(ucCntSP, ucCntSP_En);
			ucword.setBits(ucCntSPDir, ucCntSPDir_Up);
			return;
		}
		// SP --;
		else if (accept(s, DEC))
		{
			ucword.setBits(ucCntSP, ucCntSP_En);
			ucword.setBits(ucCntSPDir, ucCntSPDir_Dn);
			return;
		}
		// SP <- ?;
		else
		{
			ucword.setBits(ucLoad, ucLoad_SP);
		}
	}
	else if (accept(s, DP))
	{
		ucword.setBits(ucLoad, ucLoad_DP);
	}
	else if (accept(s, PC))
	{
		// PC++;
		if (accept(s, INC))
		{
			ucword.setBits(ucIncPC, ucIncPC_En);
			return;
		}
		// PC <- ?;
		else
		{
			ucword.setBits(ucLoad, ucLoad_PC);
		}
	}
	else if (accept(s, MSW))
	{
		ucword.setBits(ucLoad, ucLoad_MSW);
	}
	else if (accept(s, IR))
	{
		ucword.setBits(ucLoadIR, ucLoadIR_En);
	}
	// HI or LO register destination (possible for MDR, MAR and A)
	// HI(?) <- ?;
	// LO(?) <- ?;
	else if (see(s, HI) || see(s, LO))
	{

		destByte = currentToken;

		if (!accept(s, HI))
		{
			accept(s, LO);
		}

		if (!expect(s, LBR))
		{
			err("Expected (");
		}

		// HI/LO(A) <- ?
		if (accept(s, A))
		{
			if (destByte == HI)
			{
				ucword.setBits(ucLoad, ucLoad_AHI);
			}
			else
			{
				ucword.setBits(ucLoad, ucLoad_ALO);
			}
		}
		// HI/LO(MDR) <- ?
		else if (accept(s, MDR))
		{
			if (destByte == HI)
			{
				ucword.setBits(ucLoad, ucLoad_MDRHI);
			}
			else
			{
				ucword.setBits(ucLoad, ucLoad_MDRLO);
			}
		}
		// HI/LO(MAR) <- ?
		else if (accept(s, MAR))
		{
			if (destByte == HI)
			{
				ucword.setBits(ucLoad, ucLoad_MARHI);
			}
			else
			{
				ucword.setBits(ucLoad, ucLoad_MARLO);
			}
		}
		else
		{
			err("HI/LO qualifier allowed only for destinations MDR, MAR and A.");
		}

		if (!expect(s, RBR))
		{
			err("Expected )");
		}

	}

	// MEM() destination
	// MEM(?) <- ?;
	else if (accept(s, MEM))
	{

		ucword.setBits(ucLoad, ucLoad_MEM);
		ucword.setBits(ucMemOp, ucMemOp_En);
		
		if (!expect(s, LBR))
		{
			err("Expected (");
		}

		// read address bus source
		currentAdrBus = currentToken;
		if (addressBus != ANY && (addressBus != currentAdrBus)) {
			err("Address bus conflict");
		}
		else
		{
			if (accept(s, MAR))
			{
				ucword.setBits(ucADRBus, ucADRBus_MAR);
				addressBus = MAR;
			}
			else if (accept(s, SP))
			{
				ucword.setBits(ucADRBus, ucADRBus_SP);
				addressBus = SP;
			}
			else if (accept(s, DP))
			{
				ucword.setBits(ucADRBus, ucADRBus_DP);
				addressBus = DP;
			}
			else if (accept(s, PC))
			{
				ucword.setBits(ucADRBus, ucADRBus_PC);
				addressBus = PC;
			}
			else
			{
				err("Expected address register MAR, SP, DP or PC after MEM(");
			}
		}

		if (!expect(s, RBR))
		{
			err("Expected )");
		}
	}
	// invalid token
	else
	{
		err("Unexpected token");
	}

	// eat <-
	if (!expect(s, TRANSFER))
	{
		err("Expected <-");
	}

	// parse source

	// MEM() source
	// ? <- MEM(?);
	if (accept(s, MEM))
	{
		
		ucword.setBits(ucMemOp, ucMemOp_En);
		
		// check if left-hand-side was not mem
		if (destToken != MEM)
		{
			// enable bus interface
			if (busIfcFieldInUse == 0)
			{
				ucword.setBits(ucBusIfcEn, ucBusIfcEn_En);
				busIfcFieldInUse = 1;
			}
			else
			{
				err("Data-memory bus interface use and misc signal latching (I, S) must be exclusive and it was already used.");
			}
		}
		else
		{
			// MEM(?) <- MEM(?) is illegal
			err("MEM(...) <- MEM(...) is invalid. Address bus conflict");
		}

		// set bus interface direction and mode
		if (destByte == HI)
		{
			ucword.setBits(ucBusIfcMode, ucBusIfcMode_MEM2ALUHI);
		}
		else
		{
			ucword.setBits(ucBusIfcMode, ucBusIfcMode_MEM2ALULO);
		}

		// eat "("
		if (!expect(s, LBR))
		{
			err("Expected ( after MEM on right-hand-side of transfer instruction");
		}

		// set address bus source
		currentAdrBus = currentToken;
		if (addressBus != ANY && (addressBus != currentAdrBus)) {
			err("Address bus conflict");
		}
		else
		{
			if (accept(s, MAR))
			{
				ucword.setBits(ucADRBus, ucADRBus_MAR);
				addressBus = MAR;
			}
			else if (accept(s, SP))
			{
				ucword.setBits(ucADRBus, ucADRBus_SP);
				addressBus = SP;
			}
			else if (accept(s, DP))
			{
				ucword.setBits(ucADRBus, ucADRBus_DP);
				addressBus = DP;
			}
			else if (accept(s, PC))
			{
				ucword.setBits(ucADRBus, ucADRBus_PC);
				addressBus = PC;
			}
			else
			{
				err("Invalid address source -- expected MAR, SP, DP or PC");
			}
		}

		// eat ")"
		if (!expect(s, RBR))
		{
			err("Expected ) after address source in right-hand-side transfer instruction");
		}

	}
	else
	{

		// if destination is MEM(), parse qualifier HI/LO for source
		// MEM(?) <- HI(?);
		// MEM(?) <- LO(?);
		if (destToken == MEM)
		{

			// enable bus interface
			if (busIfcFieldInUse == 0)
			{
				ucword.setBits(ucBusIfcEn, ucBusIfcEn_En);
				busIfcFieldInUse = 1;
			}
			else
			{
				err("Data-memory bus interface use and misc signal latching (I, S) must be exclusive and it was already used.");
			}

			// read HI/LO qualifier and set bus interface direction and mode
			if (accept(s, LO))
			{
				ucword.setBits(ucBusIfcMode, ucBusIfcMode_ALULO2MEM);
			}
			else if (accept(s, HI))
			{
				ucword.setBits(ucBusIfcMode, ucBusIfcMode_ALUHI2MEM);
			}
			else
			{
				err("Memory qualifier HI/LO expected");
			}

			if (!expect(s, LBR))
			{
				err("Expected ( after memory qualifier");
			}

		}

		// parse left operand or unary operand

		// register tied to left bus
		// ? <- MDR
		if (accept(s, MDR))
		{
			firstOperand = MDR;
			ucword.setBits(ucLBus, ucLBus_MDR);
		}
		// ? <- A
		else if (accept(s, A))
		{
			firstOperand = A;
			ucword.setBits(ucLBus, ucLBus_A);
		}
		// ? <- X
		else if (accept(s, X))
		{
			firstOperand = X;
			ucword.setBits(ucLBus, ucLBus_X);
		}
		// ? <- Y
		else if (accept(s, Y))
		{
			firstOperand = Y;
			ucword.setBits(ucLBus, ucLBus_Y);
		}

		// register tied to right bus
		// ? <- MAR
		else if (accept(s, MAR))
		{
			if (addressBus != ANY && (addressBus != MAR)) {
				err("Address bus conflict");
			}
			firstOperand = MAR;
			ucword.setBits(ucADRBus, ucADRBus_MAR);
			ucword.setBits(ucRBus, ucRBus_ABUS);
			addressBus = MAR;
		}
		// ? <- SP
		else if (accept(s, SP))
		{
			if (addressBus != ANY && (addressBus != SP)) {
				err("Address bus conflict");
			}
			firstOperand = SP;
			ucword.setBits(ucADRBus, ucADRBus_SP);
			ucword.setBits(ucRBus, ucRBus_ABUS);
			addressBus = SP;
		}
		// ? <- DP
		else if (accept(s, DP))
		{
			if (addressBus != ANY && (addressBus != DP)) {
				err("Address bus conflict");
			}
			firstOperand = DP;
			ucword.setBits(ucADRBus, ucADRBus_DP);
			ucword.setBits(ucRBus, ucRBus_ABUS);
			addressBus = DP;
		}
		// ? <- PC
		else if (accept(s, PC))
		{
			if (addressBus != ANY && (addressBus != PC)) {
				err("Address bus conflict");
			}
			firstOperand = PC;
			ucword.setBits(ucADRBus, ucADRBus_PC);
			ucword.setBits(ucRBus, ucRBus_ABUS);
			addressBus = PC;
		}
		// ? <- MSW
		else if (accept(s, MSW))
		{
			firstOperand = MSW;
			ucword.setBits(ucRBus, ucRBus_MSW);
		}
		// ? <- IPTR
		else if (accept(s, IPTR))
		{
			firstOperand = IPTR;
			ucword.setBits(ucRBus, ucRBus_IPTR);
		}
		// 74181's constant (-1)
		// ? <- -1
		else if (accept(s, MINUS))
		{
			int c = lexer->getVal();
			if (accept(s, DECVAL))
			{
				if (c==1)
				{
					firstOperand = MINUSONE;
				}
				else
				{
					err("Expected 1");
				}
			}
			else
			{
				err("Expected decimal");
			}
		}
		else
		{
			err("Invalid register in left operand or unary operand of transfer's right-hand-side");
		}


		// operator
		op1 = currentToken;
		// ? <- ? + ?;
		if (accept(s, PLUS))
		{
			ucword.setBits(ucALUMode, ucALUMode_ARITHM);
			ucword.setBits(ucALUOp, ucALUOpA_AplusB);

			// if next token is 1 -> process carry for unary operation
			int c = lexer->getVal();
			if (accept(s, DECVAL))
			{
				if (c == 1)
				{
					ucword.setBits(ucALUCarry, ucALUCarry_C);
					unary = true;
					unaryOperand = firstOperand;
				}
				else
				{
					err("Only '1' can be a carry value");
				}
			}
		}
		// ? <- ? - ?;
		else if (accept(s, MINUS))
		{
			ucword.setBits(ucALUMode, ucALUMode_ARITHM);
			ucword.setBits(ucALUOp, ucALUOpA_AminusBminus1);
			ucword.setBits(ucALUCarry, ucALUCarry_C); // ALU's a-b-1 is used here, so carry must be set

			// check if it is not the case ? <- ? - 1 (special ALU code should be used)
			int c = lexer->getVal();
			if (accept(s, DECVAL))
			{
				if (c == 1)
				{
					unary = true;
					unary_minus_1 = true;
					unaryOperand = firstOperand;
				}
				else
				{
					err("Only '1' can be a right immediate operand of subtraction");
				}
			}

		}
		// ? <- ? | ?;
		else if (accept(s, OR))
		{
			ucword.setBits(ucALUMode, ucALUMode_LOGIC);
			ucword.setBits(ucALUOp, ucALUOpL_AorB);
		}
		// ? <- ? & ?;
		else if (accept(s, AND))
		{
			ucword.setBits(ucALUMode, ucALUMode_LOGIC);
			ucword.setBits(ucALUOp, ucALUOpL_AandB);
		}
		// ? <- ? ^ ?;
		else if (accept(s, XOR))
		{
			ucword.setBits(ucALUMode, ucALUMode_LOGIC);
			ucword.setBits(ucALUOp, ucALUOpL_AxorB);
		}
		// no operator found - assuming unary
		else
		{
			unary = true;
			unaryOperand = firstOperand;
		}

		// check feasibility of unary ops
		// ? <- ?;
		if (unary)
		{
			// encode unary RHS
			if (unaryOperand == MDR || unaryOperand == A || unaryOperand == X || unaryOperand == Y)
			{
				if (!unary_minus_1)
				{
					ucword.setBits(ucALUOp, ucALUOpA_A);
					ucword.setBits(ucALUMode, ucALUMode_ARITHM);
				}
				else
				{
					ucword.setBits(ucALUMode, ucALUMode_ARITHM);
					ucword.setBits(ucALUOp, ucALUOpA_Aminus1);
					ucword.setBits(ucALUCarry, ucALUCarry_NC);
				}
			}
			else if (unaryOperand == MAR || unaryOperand == SP || unaryOperand == DP || unaryOperand == PC || unaryOperand == MSW || unaryOperand == IPTR)
			{
				if (!unary_minus_1)
				{
					ucword.setBits(ucALUOp, ucALUOpL_B);
					ucword.setBits(ucALUMode, ucALUMode_LOGIC);
				}
				else
				{
					err("n - 1 only possible for registers on left ALU bus - MDR, A, X and Y");
				}
			}
			else if (unaryOperand == MINUSONE)
			{
				ucword.setBits(ucALUOp, ucALUOpA_minus1);
				ucword.setBits(ucALUMode, ucALUMode_ARITHM);
			}
			else
			{
				err("Invalid unary right-hand-side. Should be one of MDR, A, X, Y, MAR, SP, DP, PC, MSW, IPTR.");
			}

		}
		// not unary
		else
		{
			// check for left operands that cannot be left operands
			if (firstOperand==MAR || firstOperand==SP || firstOperand==DP || firstOperand==PC || firstOperand==MSW || firstOperand==IPTR)
			{
				err("MAR, SP, DP, PC, MSW, IPTR cannot be left operands");
			}

			// parse right operand (process only if not unary)

			// right operands tied to right bus
			secondOperand = currentToken;

			// ? <- [HI(|LO(] ? op MDR [)]
			if (accept(s, MDR))
			{
				ucword.setBits(ucRBus, ucRBus_MDR);
			}
			// ? <- [HI(|LO(] ? op MAR [)]
			else if (accept(s, MAR))
			{
				if (addressBus != ANY && (addressBus != MAR))
				{
					err("Address bus conflict");
				}
				ucword.setBits(ucADRBus, ucADRBus_MAR);
				ucword.setBits(ucRBus, ucRBus_ABUS);
				addressBus = MAR;
			}
			// ? <- [HI(|LO(] ? op SP [)]
			else if (accept(s, SP))
			{
				if (addressBus != ANY && (addressBus != SP))
				{
					err("Address bus conflict");
				}
				ucword.setBits(ucADRBus, ucADRBus_SP);
				ucword.setBits(ucRBus, ucRBus_ABUS);
				addressBus = SP;
			}
			// ? <- [HI(|LO(] ? op DP [)]
			else if (accept(s, DP))
			{
				if (addressBus != ANY && (addressBus != DP))
				{
					err("Address bus conflict");
				}
				ucword.setBits(ucADRBus, ucADRBus_DP);
				ucword.setBits(ucRBus, ucRBus_ABUS);
				addressBus = DP;
			}
			// ? <- [HI(|LO(] ? op PC [)]
			else if (accept(s, PC))
			{
				if (addressBus != ANY && (addressBus != PC))
				{
					err("Address bus conflict");
				}
				ucword.setBits(ucADRBus, ucADRBus_PC);
				ucword.setBits(ucRBus, ucRBus_ABUS);
				addressBus = PC;
			}
			// ? <- [HI(|LO(] ? op MSW [)]
			else if (accept(s, MSW))
			{
				ucword.setBits(ucRBus, ucRBus_MSW);
			}
			// ? <- [HI(|LO(] ? op IPTR [)]
			else if (accept(s, IPTR))
			{
				ucword.setBits(ucRBus, ucRBus_IPTR);
			}
			else // A or X or Y (special case - they are not tied to the right bus but there is a special ALU code to help)
			{
				// A + A, X + X, Y + Y
				if (secondOperand == firstOperand)
				{
					accept(s, secondOperand);
					ucword.setBits(ucALUMode, ucALUMode_ARITHM);
					ucword.setBits(ucALUOp, ucALUOpA_AplusA);
				}
				else
				{
					err("Invalid register in right operand of transfer's right-hand-side");
				}
			}

			// parse third auxiliary argument (including carry/no_carry)
			// ? <- [HI(|LO(] ? op ? + ? [)]
			if (accept(s, PLUS))
			{
				if (op1 != MINUS)
				{
					int c = lexer->getVal();
					if (accept(s, DECVAL))
					{
						// ? <- [HI(|LO(] ? op ? + 1 [)]
						if (c == 1)
						{
							ucword.setBits(ucALUCarry, ucALUCarry_C);
						}
						else
						{
							err("Invalid number. Expected 1 as carry value");
						}
					}
					else
					{
						err("Expected decimal");
					}
				}
				// ? <- [HI(|LO(] ? - ? + 1 [)] is illegal
				else
				{
					err("Carry not allowed after MINUS operation, as MINUS in fact uses ALU's A-B-1 op.");
				}
			}
			// ? <- [HI(|LO(] ? op ? - ? [)]
			else if (accept(s, MINUS))
			{
				// ? <- [HI(|LO(] ? - ? - 1 [)]
				if (op1 == MINUS)
				{
					int c = lexer->getVal();
					if (accept(s, DECVAL))
					{
						if (c == 1)
						{
							ucword.setBits(ucALUCarry, ucALUCarry_NC);
						}
						else
						{
							err("Invalid number. Expected 1");
						}
					}
					else
					{
						err("Expected decimal");
					}
				}
				// ? <- [HI(|LO(] ? op ? - 1 [)]
				// is illegal when op is not MINUS
				else
				{
					err("Invalid operation. Only a - b - 1 is allowed");
				}
			}
		}

		// if right-hand-side is MEM(), parse closing bracket of qualfier for RHS
		if (destToken == MEM)
		{
			if (!expect(s, RBR))
			{
				err("Expected )");
			}
		}

	}
}


/***********************************************
 *
 * Print error message
 *
 ***********************************************/
void Parser::err(const char* msg) {
	cout << "PARSE(line " << lexer->getLine() << ", column "<<lexer->getPosInLine()<<"): " << msg << endl;
	exit(-1);
}
