/* 
 * 
 *    ALU.cpp - this file is part of CPU Simulator
 *   
 *    Copyright 2010, 2011 Dawid Pilawa
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

#include "stdafx.h"
#include "Logic.h"
#include "Devices.h"
#include "ALU.h"

using namespace simulation;
using namespace std;

ALU::ALU(std::string label, Wire& gnd, Wire& vcc,
    Wire& alubus0, Wire& alubus1, Wire& alubus2, Wire& alubus3, Wire& alubus4, Wire& alubus5, Wire& alubus6, Wire& alubus7, Wire& alubus8, Wire& alubus9, Wire& alubus10, Wire& alubus11, Wire& alubus12, Wire& alubus13, Wire& alubus14, Wire& alubus15,
    Wire& lbus0, Wire& lbus1, Wire& lbus2, Wire& lbus3, Wire& lbus4, Wire& lbus5, Wire& lbus6, Wire& lbus7, Wire& lbus8, Wire& lbus9, Wire& lbus10, Wire& lbus11, Wire& lbus12, Wire& lbus13, Wire& lbus14, Wire& lbus15,
    Wire& rbus0, Wire& rbus1, Wire& rbus2, Wire& rbus3, Wire& rbus4, Wire& rbus5, Wire& rbus6, Wire& rbus7, Wire& rbus8, Wire& rbus9, Wire& rbus10, Wire& rbus11, Wire& rbus12, Wire& rbus13, Wire& rbus14, Wire& rbus15,        
    Wire& aluop0, Wire& aluop1, Wire& aluop2, Wire& aluop3,
    Wire& alumode, Wire& alucarryin_bar, Wire& alushr_bar,
    Wire& enalu_bar,
    Wire& loadflags0, Wire& loadflags1,
    Wire& c, Wire& z, Wire& n, Wire& v
    ) : Device(label)
{
    nc.NC();

    // ALU + carry lookahead

    alu0 = new LS181("alu0", aluop0, aluop1, aluop2, aluop3,
                             lbus0, lbus1, lbus2, lbus3,
                             rbus0, rbus1, rbus2, rbus3,
                             alucarryin_bar, alumode,
                             alures0, alures1, alures2, alures3,
                             p0, g0, nc, nc);

    alu1 = new LS181("alu1", aluop0, aluop1, aluop2, aluop3,
                             lbus4, lbus5, lbus6, lbus7,
                             rbus4, rbus5, rbus6, rbus7,
                             cnx, alumode,
                             alures4, alures5, alures6, alures7,
                             p1, g1, alucarryout1_bar, nc);

    alu2 = new LS181("alu2", aluop0, aluop1, aluop2, aluop3,
                             lbus8, lbus9, lbus10, lbus11,
                             rbus8, rbus9, rbus10, rbus11,
                             cny, alumode,
                             alures8, alures9, alures10, alures11,
                             p2, g2, nc, nc);

    alu3 = new LS181("alu3", aluop0, aluop1, aluop2, aluop3,
                             lbus12, lbus13, lbus14, lbus15,
                             rbus12, rbus13, rbus14, rbus15,
                             cnz, alumode,
                             alures12, alures13, alures14, alures15,
                             p3, g3, alucarryout3_bar, nc);

    cl = new LS182("cl", alucarryin_bar, p0, g0, p1, g1, p2, g2, p3, g3, cnx, cny, cnz, nc, nc);
    
    // flags generation - CARRY

    flag_c = new LS151("flag_c", gnd, loadflags0, loadflags1, alushr_bar,
        alures0, alures8, alures0, gnd, alucarryout3, alucarryout3, alucarryout1, gnd,
         c, nc);

    // flags generation - NEGATIVE & ZERO

    zero_l1lo = new LS02("zero_l1lo", alubus0, alubus1, b01, alubus2, alubus3, b23, alubus4, alubus5, b45, alubus6, alubus7, b67);
    zero_l1hi = new LS02("zero_l1hi", alubus8, alubus9, b89, alubus10, alubus11, b1011, alubus12, alubus13, b1213, alubus14, alubus15, b1415);
    zero_l2 = new LS21("zero_l2", b01, b23, b45, b67, zero_lo, b89, b1011, b1213, b1415, zero_hi);
    zero_l3 = new LS08("zero_l3", zero_hi, zero_lo, zero_word, nc, nc, nc, nc, nc, nc, nc, nc, nc);

    flag_nz = new LS153("flag_n", gnd, loadflags0, loadflags1,
        alubus15, alubus15, alubus7, gnd, 
        zero_word, zero_hi, zero_lo, gnd,
        n, z);

    // flags generation - OVERFLOW
    // summation = aluop1 low; subtraction = aluop high;
    // overflow when: (positive+positive=negative); (negative+negative=positive)
    //                (positive-negative=negative); (negative-positive=positive)
    // TODO: overflow also for arithmetic left shift in case arithmetic shifts need to be implemented
    
    flag_v_hi = new LS151("flag_v_hi", gnd, alubus15, rbus15, lbus15,
        gnd, aluop1_bar, gnd, aluop1, aluop1, gnd, aluop1_bar, gnd,
        v_hi, nc);

    flag_v_lo = new LS151("flag_v_hi", gnd, alubus7, rbus7, lbus7,
        gnd, aluop1_bar, gnd, aluop1, aluop1, gnd, aluop1_bar, gnd,
        v_lo, nc);

    flag_v = new LS153("flag_v", gnd, loadflags0, loadflags1,
        v_hi, v_hi, v_lo, gnd,
        nc, nc, nc, nc,
        v, nc);

    // glue logic

    inv = new LS04("inv", alushr_bar, alushr, aluop1, aluop1_bar, nc, nc, nc, nc, alucarryout1_bar, alucarryout1, alucarryout3_bar, alucarryout3);
    or_gate = new LS32("or", alushr, enalu_bar, enalubuf_bar, alushr_bar, enalu_bar, enalushr_bar, nc, nc, nc, nc, nc, nc);

    // shifter

    alubuflo = new LS244("alubuflo", enalubuf_bar, enalubuf_bar, 
        alures0, alures1, alures2, alures3, alures4, alures5, alures6, alures7, 
        alubus0, alubus1, alubus2, alubus3, alubus4, alubus5, alubus6, alubus7);

    alubufhi = new LS244("alubufhi", enalubuf_bar, enalubuf_bar, 
        alures8, alures9, alures10, alures11, alures12, alures13, alures14, alures15, 
        alubus8, alubus9, alubus10, alubus11, alubus12, alubus13, alubus14, alubus15);

    alushrlo = new LS244("alushrlo", enalushr_bar, enalushr_bar, 
        alures1, alures2, alures3, alures4, alures5, alures6, alures7, alures8, 
        alubus0, alubus1, alubus2, alubus3, alubus4, alubus5, alubus6, alubus7);

    alushrhi = new LS244("alushrhi", enalushr_bar, enalushr_bar, 
        alures9, alures10, alures11, alures12, alures13, alures14, alures15, gnd, 
        alubus8, alubus9, alubus10, alubus11, alubus12, alubus13, alubus14, alubus15);

    // probes

    p_lbus = new Probe("lbus", lbus15, lbus14, lbus13, lbus12, lbus11, lbus10, lbus9, lbus8, lbus7, lbus6, lbus5, lbus4, lbus3, lbus2, lbus1, lbus0);
    p_rbus = new Probe("rbus", rbus15, rbus14, rbus13, rbus12, rbus11, rbus10, rbus9, rbus8, rbus7, rbus6, rbus5, rbus4, rbus3, rbus2, rbus1, rbus0);
    p_alures = new Probe("aluresult", alures15, alures14, alures13, alures12, alures11, alures10, alures9, alures8, alures7, alures6, alures5, alures4, alures3, alures2, alures1, alures0);
    p_alubus = new Probe("alubus", alubus15, alubus14, alubus13, alubus12, alubus11, alubus10, alubus9, alubus8, alubus7, alubus6, alubus5, alubus4, alubus3, alubus2, alubus1, alubus0);
    p_trackflags = new Probe("c", c);
}

ALU::~ALU()
{
    delete alu0; delete alu1; delete alu2; delete alu3;
    delete cl;
    
    delete inv;
    delete or_gate;
    
    delete alubuflo;
    delete alubufhi;
    delete alushrlo;
    delete alushrhi;

    delete flag_c; delete flag_nz; delete flag_v_hi; delete flag_v_lo; delete flag_v;

    delete zero_l1lo; delete zero_l1hi; delete zero_l2; delete zero_l3;
    
    delete p_lbus; delete p_rbus; delete p_alubus; delete p_alures;
    delete p_trackflags;
}

void ALU::go(long t)
{
    begin(t);
    end();
}

void ALU::debugInfo(long t)
{
    p_lbus->debugInfo(t);
    p_rbus->debugInfo(t);
    p_alures->debugInfo(t);
    p_alubus->debugInfo(t);
    /*p_trackflags->debugInfo(t);*/
}
