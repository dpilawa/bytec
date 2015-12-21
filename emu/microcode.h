/* 
 * 
 *    microcode.h - this file is part of Microcode Assembler
 *   
 *    Copyright 2015 Dawid Pilawa
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

#include <stdint.h>

typedef struct {
    uint32_t ucLBus : 2;
    uint32_t ucRBus : 2;
    uint32_t ucADRBus : 2;
    uint32_t ucBusIfcMode : 2;	
    uint32_t ucBusIfcEn : 1;
    uint32_t ucLoad : 4;
    uint32_t ucLoadIR : 1;


} ucword_t;

#define ucLBus_MDR			0x00;
#define ucLBus_A			0x01;
#define ucLBus_X			0x02;
#define ucLBus_Y			0x03;

#define ucRBus_MDR			0x00;
#define ucRBus_MSW			0x01;
#define ucRBus_ABUS			0x02;
#define ucRBus_IPTR			0x03;	// interrupt handler address
#define ucRBus_PPC			0x04; 	// previous program counter
#define ucRBus_nc0			0x05;
#define ucRBus_nc1			0x06;
#define ucRBus_nc2			0x07;

#define ucADRBus_MAR		0x00;
#define ucADRBus_SP			0x01;
#define ucADRBus_DP			0x02;
#define ucADRBus_PC			0x03;

#define ucBusIfcMode_MEM2ALULO	0x00;
#define ucBusIfcMode_MEM2ALUHI	0x01;
#define ucBusIfcMode_ALULO2MEM	0x02;
#define ucBusIfcMode_ALUHI2MEM	0x03;

// the following used when ucBusIfcEn_Dis (bus interface disabled)
#define ucMiscLatch         ucBusIfcMode;
#define ucMiscLatch_I		0x00;		// latch I flag (enable/disable faults and interrupts)
#define ucMiscLatch_S		0x01;		// latch S flag (supervisor/user mode)
#define ucMiscLatch_nc	    0x02;		// unused
#define ucMiscLatch_None	0x03;		// do not latch anything

#define ucBusIfcEn_En		0x00;
#define ucBusIfcEn_Dis		0x01;

#define ucLoad_MDRLO		0x00;
#define ucLoad_MDRHI		0x01;
#define ucLoad_MDR			0x02;
#define ucLoad_ALO			0x03;
#define ucLoad_AHI			0x04;
#define ucLoad_A			0x05;
#define ucLoad_X			0x06;
#define ucLoad_Y			0x07;
#define ucLoad_MEM			0x08;
#define ucLoad_MARLO		0x09;
#define ucLoad_MARHI		0x0a;
#define ucLoad_MAR			0x0b;
#define ucLoad_SP			0x0c;
#define ucLoad_DP			0x0d;
#define ucLoad_PC			0x0e;
#define ucLoad_MSW			0x0f;

#define ucLoadIR_En			0x00;
#define ucLoadIR_Dis		0x01;

#define ucALUOp				15;
#define ucALUOp_s				4;
/* ARITHMETIC	*/
#define ucALUOpA_A				0x00;	// A
#define ucALUOpA_AorB				0x01; // A + B
#define ucALUOpA_AorNotB			0x02; // A + !B
#define ucALUOpA_minus1			0x03; // minus 1
#define ucALUOpA_AplusAandNotB	0x04; // A plus A!B
#define ucALUOpA_AorBplusAandNotB 0x05; // (A + B) plus A!B
#define ucALUOpA_AminusBminus1	0x06; // A minus B minus 1
#define ucALUOpA_AandBminus1		0x07; // AB minus 1
#define ucALUOpA_AplusAandB		0x08; // A plus AB
#define ucALUOpA_AplusB			0x09; // A plus B
#define ucALUOpA_AorNotBplusAandB 0x0a; // (A + !B) plus AB
#define ucALUOpA_AandBminus1_2	0x0b; // AB minus 1
#define ucALUOpA_AplusA			0x0c; // A plus A
#define ucALUOpA_AorBplusA		0x0d; // (A + B) plus A
#define ucALUOpA_AorNotBplusA		0x0e; // (A + !B) plus A
#define ucALUOpA_Aminus1			0x0f; // A minus 1
/* LOGIC		*/
#define ucALUOpL_NotA				0x00;	// !A
#define ucALUOpL_Not_AorB			0x01; // !(A + B)
#define ucALUOpL_NotAandB			0x02; // !AB
#define ucALUOpL_zero				0x03; // zero
#define ucALUOpL_Not_AandB		0x04; // !(AB)
#define ucALUOpL_NotB				0x05; // !B
#define ucALUOpL_AxorB			0x06; // A xor B
#define ucALUOpL_AandNotB			0x07; // A!B
#define ucALUOpL_NotAorB			0x08; // !A + B
#define ucALUOpL_Not_AxorB		0x09; // !(A xor B)
#define ucALUOpL_B				0x0a; // B
#define ucALUOpL_AandB			0x0b; // AB
#define ucALUOpL_one				0x0c; // one
#define ucALUOpL_AorNotB			0x0d; // A + !B
#define ucALUOpL_AorB				0x0e; // A + B
#define ucALUOpL_A				0x0f; // A

#define ucALUMode				19;
#define ucALUMode_s			1;
#define ucALUMode_ARITHM		0x00;
#define ucALUMode_LOGIC		0x01;

#define ucALUCarry			20;
#define ucALUCarry_s			1;
#define ucALUCarry_C			0x00;
#define ucALUCarry_NC			0x01;

#define ucALUShiftR			21;
#define ucALUShiftR_s			1;
#define ucALUShiftR_En		0x00;
#define ucALUShiftR_Dis		0x01;

#define ucLoadFlags			22;
#define ucLoadFlags_s			2;
#define ucLoadFlags_Word		0x00;
#define ucLoadFlags_HiByte	0x01;
#define ucLoadFlags_LoByte	0x02;
#define ucLoadFlags_Dis		0x03;

#define ucIncPC				24;
#define ucIncPC_s				1;
#define ucIncPC_En			0x00;
#define ucIncPC_Dis			0x01;

#define ucIncMAR				25;
#define ucIncMAR_s			1;
#define ucIncMAR_En			0x00;
#define ucIncMAR_Dis			0x01;

#define ucCntSP				26;
#define ucCntSP_s				1;
#define ucCntSP_En			0x00;
#define ucCntSP_Dis			0x01;

#define ucCntSPDir			27;
#define ucCntSPDir_s			1;
#define ucCntSPDir_Dn			0x00;
#define ucCntSPDir_Up			0x01;

#define ucMemSeg				28;
#define ucMemSeg_s			1;
#define ucMemSeg_Code			0x00;
#define ucMemSeg_Data			0x01;

#define ucSupervisor			29;
#define ucSupervisor_s		1;
#define ucSupervisor_Dis		0x00;
#define ucSupervisor_En		0x01;


