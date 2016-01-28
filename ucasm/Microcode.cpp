/* 
 * 
 *    Microcode.cpp - this file is part of Microcode Assembler
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
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "Microcode.h"

using namespace std;
using namespace ucasm;

// MicrocodeWord Class

/**************************************************************
 *
 * Set default microcode word
 *
 **************************************************************/
MicrocodeWord::MicrocodeWord()
{

	// set default microcode word
	ucWord = 0x00000000;
	setBits(ucLBus, ucLBus_MDR);
	setBits(ucRBus, ucRBus_MDR);
	setBits(ucADRBus, ucADRBus_PC);
	// setBits(ucBusIfcMode, ucBusIfcMode_ALULO2MEM);
	setBits(ucMiscLatch, ucMiscLatch_None);
	setBits(ucBusIfcEn, ucBusIfcEn_Dis);
	setBits(ucLoad, ucLoad_MDR);
	setBits(ucLoadIR, ucLoadIR_Dis);
	setBits(ucALUOp, ucALUOpA_A);
	setBits(ucALUMode, ucALUMode_ARITHM);
	setBits(ucALUCarry, ucALUCarry_NC);
	setBits(ucALUShiftR, ucALUShiftR_Dis);
	setBits(ucLoadFlags, ucLoadFlags_Dis);
	setBits(ucIncPC, ucIncPC_Dis);
	setBits(ucIncMAR, ucIncMAR_Dis);
	setBits(ucCntSP, ucCntSP_Dis);
	setBits(ucCntSPDir, ucCntSPDir_Up);
	setBits(ucMemSeg, ucMemSeg_Code);
	setBits(ucSupervisor, ucSupervisor_Dis);
	setBits(ucMemOp, ucMemOp_Dis);
	setBits(ucIRET, ucIRET_Dis);
}

/**************************************************************
 *
 * Assignment operator
 *
 **************************************************************/
MicrocodeWord& MicrocodeWord::operator=(const MicrocodeWord& w)
{
	if (&w == this)
	{
		return *this;
	}
	ucWord = w.getWord();
	return *this;
}

/*************************************************************
 *
 *  Sets microcode word field at 'pos' with value from 'val'
 *  Field definitions in Microcode.h
 *
 *************************************************************/
void MicrocodeWord::setBits(int pos, int val)
{

	int left;
	int right;
	int mask;
	int size;

	switch (pos)
	{
		case ucLBus:
			size = ucLBus_s;
			break;
		case ucRBus:
			size = ucRBus_s;
			break;
		case ucADRBus:
			size = ucADRBus_s;
			break;
		case ucBusIfcMode:				// also for ucMiscLatch
			size = ucBusIfcMode_s;
			break;
		case ucBusIfcEn:
			size = ucBusIfcEn_s;
			break;
		case ucLoad:
			size = ucLoad_s;
			break;
		case ucLoadIR:
			size = ucLoadIR_s;
			break;
		case ucALUOp:
			size = ucALUOp_s;
			break;
		case ucALUMode:
			size = ucALUMode_s;
			break;
		case ucALUCarry:
			size = ucALUCarry_s;
			break;
		case ucALUShiftR:
			size = ucALUShiftR_s;
			break;
		case ucLoadFlags:
			size = ucLoadFlags_s;
			break;
		case ucIncPC:
			size = ucIncPC_s;
			break;
		case ucIncMAR:
			size = ucIncMAR_s;
			break;
		case ucCntSP:
			size = ucCntSP_s;
			break;
		case ucCntSPDir:
			size = ucCntSPDir_s;
			break;
		case ucMemSeg:
			size = ucMemSeg_s;
			break;
		case ucSupervisor:
			size = ucSupervisor_s;
			break;
	}

	left = 0xFFFFFFFF;
	left = left << (31 - pos + 1);
	right = left >> size;
	mask = left ^ right;
	mask = mask ^ 0xFFFFFFFF;

	val = val << (31 - pos - size + 1);
	ucWord = ucWord & mask;
	ucWord = ucWord | val;
}

/**************************************************************
 *
 * Get microcode word
 *
 **************************************************************/
int MicrocodeWord::getWord() const
{
	return ucWord;
}


// Microcode Class

/**************************************************************
 *
 * Microcode constructor - set EEPROM vector size
 *
 **************************************************************/
Microcode::Microcode()
{
	ucode.resize(epromSize);
}

/*************************************************************
 *
 *  Saves microcode to Intel HEX file readable by EEPROM
 *  programmer software
 *
 *************************************************************/
void Microcode::saveHEX(int rom_number, const char* fname)
{

	ofstream f(fname);
	int bank;
	int adr;
	int cnt;
	int b;

	int crc;

	for (bank=0; bank < epromSize / 0xFFFF; bank++)
	{

		// write Extended Segment Address Record
		// RECLEN = 02; LOAD_OFFSET = 0000; RECTYP = 02;
		f << ":02000002" << hex << setfill('0') << setw(4) << uppercase << (bank<<12);
		crc = 0x02 + 0x00 + 0x00 + 0x02 + (bank<<4) + ((bank<<12) & 0x000000FF);
		crc = crc & 0x000000FF;
		crc = 0x100 - crc;
		crc = crc & 0x000000FF;
		f << hex << setfill('0') << setw(2) << uppercase << crc << endl;

		// write Data Record
		// RECLEN = 10; RECTYP = 00;
		for (adr=0; adr+15 <= 0xFFFF; adr=adr+16)
		{
			f << ":10" << hex << setfill('0') << setw(4) << uppercase << adr << "00";
			crc = 0x10 + (adr >> 8) + (adr & 0x000000FF);
			for (cnt=0; cnt <= 0x0f; cnt++)
			{
				b = ucode[(bank << 16) + adr + cnt].getWord();
				b = (b >> (3 - rom_number) * 8 ) & 0x000000FF;
				crc = crc + b;
				f << hex << setfill('0') << setw(2) << uppercase << b;
			}
			crc = crc & 0x000000FF;
			crc = 0x100 - crc;
			crc = crc & 0x000000FF;
			f << hex << setfill('0') << setw(2) << uppercase << crc << endl;
		}
	}

	// write End of File Record
	f << ":00000001FF" << endl;

	f.close();

}

/*************************************************************
 *
 *  Saves microcode to a flat binary file (for simulator)
 *
 *************************************************************/

void Microcode::saveBIN(int rom_number, const char* fname)
{
	ofstream f(fname);
	int w;
	char b;

	for (int i=0; i < epromSize; i++)
	{
		w = ucode[i].getWord();
		b = (w >> (3 - rom_number) * 8 ) & 0x000000FF;
		f.write(&b, 1);
	}

	f.close();

}

/**************************************************************
 *
 * Store microcode word at provided address
 *
 **************************************************************/
void Microcode::storeWord(int address, MicrocodeWord w)
{
	if (address >= 0 && address < epromSize)
	{
		ucode[address] = w;
	}
	else
	{
		cout << "Invalid microcode word address" << endl;
		std::exit(-1);
	}
}

