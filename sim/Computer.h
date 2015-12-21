/* 
 * 
 *    Computer.h - this file is part of CPU Simulator
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

namespace simulation {

class Computer : public Device  
{
    PowerSource* power;
    Oscillator* osc;
    Reset* reset;
    IRQ* irq;
    
    Control* control;
    Registers* registers;
    Memory* memory;
    ALU* alu;

    Device *and_01, *mem2alulo_ext, *hitransciever, *lotransciever;
    Device *dmem2alulo, *dmem2aluhi, *dalulo2mem, *daluhi2mem;
    Device *abus2rbush, *abus2rbusl;

    Probe *p_0, *p_1, *p_2, *p_3, *p_4, *p_5;

    Wire gnd, vcc, nc;
    Wire clk, clk0, clk1, busclk;
    Wire rst_bar_nonsync, rst_bar, rst;
    Wire nextop;
    Wire dbus0, dbus1, dbus2, dbus3, dbus4, dbus5, dbus6, dbus7;
    Wire abus0, abus1, abus2, abus3, abus4, abus5, abus6, abus7, abus8, abus9, abus10, abus11, abus12, abus13, abus14, abus15, abus16_segsel;
    Wire alubus0, alubus1, alubus2, alubus3, alubus4, alubus5, alubus6, alubus7, alubus8, alubus9, alubus10, alubus11, alubus12, alubus13, alubus14, alubus15;
    Wire lbus0, lbus1, lbus2, lbus3, lbus4, lbus5, lbus6, lbus7, lbus8, lbus9, lbus10, lbus11, lbus12, lbus13, lbus14, lbus15;
    Wire rbus0, rbus1, rbus2, rbus3, rbus4, rbus5, rbus6, rbus7, rbus8, rbus9, rbus10, rbus11, rbus12, rbus13, rbus14, rbus15;  
    Wire enmdrl_bar, ena_bar, enx_bar, eny_bar;
    Wire enmdrr_bar, enmsw_bar, enabus_bar, enppc_bar;
    Wire enmar_bar, ensp_bar, endp_bar, enpc_bar;
    Wire mdr_load_inhibit;
    Wire ldmdrlo_bar, ldmdrhi_bar, ldmdr_bar, ldalo_bar, ldahi_bar, lda_bar, ldx_bar, ldy_bar;
    Wire ldmem_bar, ldmarlo_bar, ldmarhi_bar, ldmar_bar, ldsp_bar, lddp_bar, ldpc_bar, ldmsw_bar;
    Wire loadirclk;
    Wire incpc_bar, incmar_bar, cntsp_bar, cntspdir;
    Wire mem2alulo_bar, mem2aluhi_bar, alulo2mem_bar, aluhi2mem_bar;
    Wire enhi_bar, enlo_bar;
    Wire aluop0, aluop1, aluop2, aluop3;
    Wire alumode, alucarryin_bar, alushr_bar;
    Wire enalu_bar, enmem_bar;
    Wire loadaluflags0, loadaluflags1;
    Wire c, z, n, v;
    Wire irq0, irq1, irq2, irq3, irq4, irq5, irq6, irq7;
    Wire flag_supervisor;

    long time, cycle;
    void go(long t, long cycles);
public:
    Computer(std::string label, float freq, long reset_len);
    ~Computer();
    void go(long cycles) { go(0, cycles); };
    void debugInfo(long t);
    bool isHalted(long t);
};


}
