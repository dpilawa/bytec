/* 
 * 
 *    ALU.h - this file is part of CPU Simulator
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

namespace simulation
{

class ALU : public Device
{
    Wire nc;

    Wire alures0, alures1, alures2, alures3, alures4, alures5, alures6, alures7, alures8, alures9, alures10, alures11, alures12, alures13, alures14, alures15;
    Wire alushr;
    Wire p0, g0, p1, g1, p2, g2, p3, g3, cnx, cny, cnz;
    Wire enalubuf_bar, enalushr_bar;
    Wire alucarryout1_bar, alucarryout1, alucarryout3_bar, alucarryout3;
    Wire b01, b23, b45, b67, b89, b1011, b1213, b1415;
    Wire zero_hi_bar, zero_lo_bar, zero_hi, zero_lo, zero_word;
    Wire aluop1_bar, v_hi, v_lo;

    Device *alu0, *alu1, *alu2, *alu3;
    Device *cl;
    Device *inv, *or_gate;
    Device  *alubuflo, *alubufhi, *alushrlo, *alushrhi;
    Device *flag_c, *flag_nz, *flag_v_hi, *flag_v_lo, *flag_v;
    Device *zero_l1lo, *zero_l1hi, *zero_l2, *zero_l3;
    
    Probe *p_lbus, *p_rbus, *p_alures, *p_alubus;
    Probe *p_trackflags;

public:
    ALU(std::string label, Wire& gnd, Wire& vcc,
        Wire& alubus0, Wire& alubus1, Wire& alubus2, Wire& alubus3, Wire& alubus4, Wire& alubus5, Wire& alubus6, Wire& alubus7, Wire& alubus8, Wire& alubus9, Wire& alubus10, Wire& alubus11, Wire& alubus12, Wire& alubus13, Wire& alubus14, Wire& alubus15,
        Wire& lbus0, Wire& lbus1, Wire& lbus2, Wire& lbus3, Wire& lbus4, Wire& lbus5, Wire& lbus6, Wire& lbus7, Wire& lbus8, Wire& lbus9, Wire& lbus10, Wire& lbus11, Wire& lbus12, Wire& lbus13, Wire& lbus14, Wire& lbus15,
        Wire& rbus0, Wire& rbus1, Wire& rbus2, Wire& rbus3, Wire& rbus4, Wire& rbus5, Wire& rbus6, Wire& rbus7, Wire& rbus8, Wire& rbus9, Wire& rbus10, Wire& rbus11, Wire& rbus12, Wire& rbus13, Wire& rbus14, Wire& rbus15,
        Wire& aluop0, Wire& aluop1, Wire& aluop2, Wire& aluop3,
        Wire& alumode, Wire& alucarryin_bar, Wire& alushr_bar,
        Wire& enalu_bar,
        Wire& loadflags0, Wire& loadflags1,
        Wire& c, Wire& z, Wire& n, Wire& v
        );
    virtual ~ALU();
    void go(long t);
    void debugInfo(long t);
};

}
