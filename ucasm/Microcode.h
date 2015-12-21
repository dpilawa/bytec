/* 
 * 
 *    Microcode.h - this file is part of Microcode Assembler
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

// LBUS(2) : MDR, A, X, Y
// RBUS(3) : MDR, MSW, ABUS, IPTR, PPC, nc, nc, nc
// ADDRBUS(2) : MAR, SP, DP, PC
// BUSIFCMODE(2) / MISC_LATCH(2) : MEM2ALULO, MEM2ALUHI, ALULO2MEM, ALUHI2MEM	/	I, S, nc, NONE (the latter when bus interface disabled)
// BUSIFCEN(1): _enable/disable
// LOAD(4) : MDRLO, MDRHI, MDR, ALO, AHI, A, X, Y, MEM, MARLO, MARHI, MAR, SP, DP, PC, MSW
// LOAD_IR(1) : _enable/disable
// ALUOP(4)
// ALUMODE(1)
// ALUCARRYIN(1) : _carry/no_carry
// ALUSHR(1) : _enable/disable
// LOAD_FLAGS(2) : word, hibyte, lobyte, disable
// INC_PC(1) : _enable/disable
// INC_MAR(1) : _enable/disable
// CNT_SP(1) : SP count _enable/disable
// SP_DIR(1) : dn/up
// MEMSEG(1) : CODE/DATA
// PRIVILEGED(1) : _disable/enable
// NC(2) : not_connected


namespace ucasm {

const int ucLBus				= 0;
const int ucLBus_s				= 2;
const int ucLBus_MDR			= 0x00;
const int ucLBus_A				= 0x01;
const int ucLBus_X				= 0x02;
const int ucLBus_Y				= 0x03;

const int ucRBus				= 2;
const int ucRBus_s				= 3;
const int ucRBus_MDR			= 0x00;
const int ucRBus_MSW			= 0x01;
const int ucRBus_ABUS			= 0x02;
const int ucRBus_IPTR			= 0x03;		// interrupt handler address
const int ucRBus_PPC			= 0x04; 	// previous program counter
const int ucRBus_nc0			= 0x05; 	// usermode stack pointer
const int ucRBus_nc1			= 0x06;
const int ucRBus_nc2			= 0x07;

const int ucADRBus				= 5;
const int ucADRBus_s			= 2;
const int ucADRBus_MAR			= 0x00;
const int ucADRBus_SP			= 0x01;
const int ucADRBus_DP			= 0x02;
const int ucADRBus_PC			= 0x03;

const int ucBusIfcMode			= 7;
const int ucBusIfcMode_s		= 2;
const int ucBusIfcMode_MEM2ALULO	= 0x00;
const int ucBusIfcMode_MEM2ALUHI	= 0x01;
const int ucBusIfcMode_ALULO2MEM	= 0x02;
const int ucBusIfcMode_ALUHI2MEM	= 0x03;

// the following used when ucBusIfcEn_Dis (bus interface disabled)
const int ucMiscLatch			= 7;
const int ucMiscLatch_s			= 2;
const int ucMiscLatch_I			= 0x00;		// latch I flag (enable/disable faults and interrupts)
const int ucMiscLatch_S			= 0x01;		// latch S flag (supervisor/user mode)
const int ucMiscLatch_nc		= 0x02;		// unused
const int ucMiscLatch_None		= 0x03;		// do not latch anything

const int ucBusIfcEn			= 9;
const int ucBusIfcEn_s			= 1;
const int ucBusIfcEn_En			= 0x00;
const int ucBusIfcEn_Dis		= 0x01;

const int ucLoad				= 10;
const int ucLoad_s				= 4;
const int ucLoad_MDRLO			= 0x00;
const int ucLoad_MDRHI			= 0x01;
const int ucLoad_MDR			= 0x02;
const int ucLoad_ALO			= 0x03;
const int ucLoad_AHI			= 0x04;
const int ucLoad_A				= 0x05;
const int ucLoad_X				= 0x06;
const int ucLoad_Y				= 0x07;
const int ucLoad_MEM			= 0x08;
const int ucLoad_MARLO			= 0x09;
const int ucLoad_MARHI			= 0x0a;
const int ucLoad_MAR			= 0x0b;
const int ucLoad_SP				= 0x0c;
const int ucLoad_DP				= 0x0d;
const int ucLoad_PC				= 0x0e;
const int ucLoad_MSW			= 0x0f;

const int ucLoadIR				= 14;
const int ucLoadIR_s			= 1;
const int ucLoadIR_En			= 0x00;
const int ucLoadIR_Dis			= 0x01;

const int ucALUOp				= 15;
const int ucALUOp_s				= 4;
/* ARITHMETIC	*/
const int ucALUOpA_A				= 0x00;	// A
const int ucALUOpA_AorB				= 0x01; // A + B
const int ucALUOpA_AorNotB			= 0x02; // A + !B
const int ucALUOpA_minus1			= 0x03; // minus 1
const int ucALUOpA_AplusAandNotB	= 0x04; // A plus A!B
const int ucALUOpA_AorBplusAandNotB = 0x05; // (A + B) plus A!B
const int ucALUOpA_AminusBminus1	= 0x06; // A minus B minus 1
const int ucALUOpA_AandBminus1		= 0x07; // AB minus 1
const int ucALUOpA_AplusAandB		= 0x08; // A plus AB
const int ucALUOpA_AplusB			= 0x09; // A plus B
const int ucALUOpA_AorNotBplusAandB = 0x0a; // (A + !B) plus AB
const int ucALUOpA_AandBminus1_2	= 0x0b; // AB minus 1
const int ucALUOpA_AplusA			= 0x0c; // A plus A
const int ucALUOpA_AorBplusA		= 0x0d; // (A + B) plus A
const int ucALUOpA_AorNotBplusA		= 0x0e; // (A + !B) plus A
const int ucALUOpA_Aminus1			= 0x0f; // A minus 1
/* LOGIC		*/
const int ucALUOpL_NotA				= 0x00;	// !A
const int ucALUOpL_Not_AorB			= 0x01; // !(A + B)
const int ucALUOpL_NotAandB			= 0x02; // !AB
const int ucALUOpL_zero				= 0x03; // zero
const int ucALUOpL_Not_AandB		= 0x04; // !(AB)
const int ucALUOpL_NotB				= 0x05; // !B
const int ucALUOpL_AxorB			= 0x06; // A xor B
const int ucALUOpL_AandNotB			= 0x07; // A!B
const int ucALUOpL_NotAorB			= 0x08; // !A + B
const int ucALUOpL_Not_AxorB		= 0x09; // !(A xor B)
const int ucALUOpL_B				= 0x0a; // B
const int ucALUOpL_AandB			= 0x0b; // AB
const int ucALUOpL_one				= 0x0c; // one
const int ucALUOpL_AorNotB			= 0x0d; // A + !B
const int ucALUOpL_AorB				= 0x0e; // A + B
const int ucALUOpL_A				= 0x0f; // A

const int ucALUMode				= 19;
const int ucALUMode_s			= 1;
const int ucALUMode_ARITHM		= 0x00;
const int ucALUMode_LOGIC		= 0x01;

const int ucALUCarry			= 20;
const int ucALUCarry_s			= 1;
const int ucALUCarry_C			= 0x00;
const int ucALUCarry_NC			= 0x01;

const int ucALUShiftR			= 21;
const int ucALUShiftR_s			= 1;
const int ucALUShiftR_En		= 0x00;
const int ucALUShiftR_Dis		= 0x01;

const int ucLoadFlags			= 22;
const int ucLoadFlags_s			= 2;
const int ucLoadFlags_Word		= 0x00;
const int ucLoadFlags_HiByte	= 0x01;
const int ucLoadFlags_LoByte	= 0x02;
const int ucLoadFlags_Dis		= 0x03;

const int ucIncPC				= 24;
const int ucIncPC_s				= 1;
const int ucIncPC_En			= 0x00;
const int ucIncPC_Dis			= 0x01;

const int ucIncMAR				= 25;
const int ucIncMAR_s			= 1;
const int ucIncMAR_En			= 0x00;
const int ucIncMAR_Dis			= 0x01;

const int ucCntSP				= 26;
const int ucCntSP_s				= 1;
const int ucCntSP_En			= 0x00;
const int ucCntSP_Dis			= 0x01;

const int ucCntSPDir			= 27;
const int ucCntSPDir_s			= 1;
const int ucCntSPDir_Dn			= 0x00;
const int ucCntSPDir_Up			= 0x01;

const int ucMemSeg				= 28;
const int ucMemSeg_s			= 1;
const int ucMemSeg_Code			= 0x00;
const int ucMemSeg_Data			= 0x01;

const int ucSupervisor			= 29;
const int ucSupervisor_s		= 1;
const int ucSupervisor_Dis		= 0x00;
const int ucSupervisor_En		= 0x01;


// ROM size
const int epromSize = 262144;

// a single microcode word
class MicrocodeWord {
	unsigned int ucWord;
public:
	MicrocodeWord();
	void setBits(int pos, int val);
	int  getWord() const;
	MicrocodeWord& operator=(const MicrocodeWord& w);
};

// full microcode ROM contents
class Microcode {
	std::vector<MicrocodeWord> ucode;
public:
	Microcode();
	void saveHEX(int rom_number, const char* fname);
	void saveBIN(int rom_number, const char* fname);
	void storeWord(int address, MicrocodeWord w);
};

};
