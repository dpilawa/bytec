/* 
 * 
 *    Computer.cpp - this file is part of CPU Simulator
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
#include "Control.h"
#include "Registers.h"
#include "Memory.h"
#include "ALU.h"
#include "Computer.h"

using namespace simulation;
using namespace std;


Computer::Computer(std::string label, float freq, long reset_len) : Device(label)
{
    cout<<"Initializing machine at "<<(freq / 4.0)<<"Mhz with "<<(float)reset_len/1000.0<<"us startup reset"<<endl;

    pd = 0;
    power = new PowerSource("pwr", gnd, vcc);
    osc = new Oscillator("osc", freq, clk);
    reset = new Reset("rst", reset_len, rst_bar_nonsync);
    nc.NC();

    // cpu modules

    irq = new IRQ("irq", irq0, irq1, irq2, irq3, irq4, irq5, irq6, irq7);

    alu = new ALU("alu", gnd, vcc,
            alubus0, alubus1, alubus2, alubus3, alubus4, alubus5, alubus6, alubus7, alubus8, alubus9, alubus10, alubus11, alubus12, alubus13, alubus14, alubus15,
            lbus0, lbus1, lbus2, lbus3, lbus4, lbus5, lbus6, lbus7, lbus8, lbus9, lbus10, lbus11, lbus12, lbus13, lbus14, lbus15,
            rbus0, rbus1, rbus2, rbus3, rbus4, rbus5, rbus6, rbus7, rbus8, rbus9, rbus10, rbus11, rbus12, rbus13, rbus14, rbus15,
            aluop0, aluop1, aluop2, aluop3,
            alumode, alucarryin_bar, alushr_bar,
            enalu_bar,
            loadaluflags0, loadaluflags1,
            c, z, n, v
            );

    control = new Control("control", gnd, vcc, clk, clk0, clk1, rst_bar_nonsync, rst_bar, rst,
            dbus0, dbus1, dbus2, dbus3, dbus4, dbus5, dbus6, dbus7,
            alubus0, alubus1, alubus2, alubus3, alubus4, alubus5, alubus6, alubus7, alubus8, alubus9, alubus10, alubus11, alubus12, alubus13, alubus14, alubus15,
            rbus0, rbus1, rbus2, rbus3, rbus4, rbus5, rbus6, rbus7, rbus8, rbus9, rbus10, rbus11, rbus12, rbus13, rbus14, rbus15,
            enmdrl_bar, ena_bar, enx_bar, eny_bar,
            enmdrr_bar, enmsw_bar, enabus_bar, enppc_bar,
            enmar_bar, ensp_bar, endp_bar, enpc_bar,
            mdr_load_inhibit,
            ldmdrlo_bar, ldmdrhi_bar, ldmdr_bar, ldalo_bar, ldahi_bar, lda_bar, ldx_bar, ldy_bar,
            ldmem_bar, ldmarlo_bar, ldmarhi_bar, ldmar_bar, ldsp_bar, lddp_bar, ldpc_bar, ldmsw_bar,
            loadirclk,
            aluop0, aluop1, aluop2, aluop3,
            alumode, alucarryin_bar, alushr_bar,
            enalu_bar, enmem_bar,
            mem2alulo_bar, mem2aluhi_bar, alulo2mem_bar, aluhi2mem_bar,
            abus16_segsel, incpc_bar, incmar_bar, cntsp_bar, cntspdir,
            loadaluflags0, loadaluflags1,
            c, z, n, v,
            irq0, irq1, irq2, irq3, irq4, irq5, irq6, irq7,
            flag_supervisor
            );

    registers = new Registers("registers", gnd, vcc, clk0, clk1, rst_bar,
            abus0, abus1, abus2, abus3, abus4, abus5, abus6, abus7, abus8, abus9, abus10, abus11, abus12, abus13, abus14, abus15,
            alubus0, alubus1, alubus2, alubus3, alubus4, alubus5, alubus6, alubus7, alubus8, alubus9, alubus10, alubus11, alubus12, alubus13, alubus14, alubus15,
            lbus0, lbus1, lbus2, lbus3, lbus4, lbus5, lbus6, lbus7, lbus8, lbus9, lbus10, lbus11, lbus12, lbus13, lbus14, lbus15,
            rbus0, rbus1, rbus2, rbus3, rbus4, rbus5, rbus6, rbus7, rbus8, rbus9, rbus10, rbus11, rbus12, rbus13, rbus14, rbus15,
            enmdrl_bar, ena_bar, enx_bar, eny_bar,
            enmdrr_bar, enmsw_bar, enabus_bar, enppc_bar,
            enmar_bar, ensp_bar, endp_bar, enpc_bar,
            mdr_load_inhibit,
            ldmdrlo_bar, ldmdrhi_bar, ldmdr_bar, ldalo_bar, ldahi_bar, lda_bar, ldx_bar, ldy_bar,
            ldmem_bar, ldmarlo_bar, ldmarhi_bar, ldmar_bar, ldsp_bar, lddp_bar, ldpc_bar, ldmsw_bar,
            loadirclk,
            incpc_bar, incmar_bar, cntsp_bar, cntspdir,
            flag_supervisor
            );

    memory = new Memory("memory", gnd, vcc, clk0, clk1,
        dbus0, dbus1, dbus2, dbus3, dbus4, dbus5, dbus6, dbus7,
        abus0, abus1, abus2, abus3, abus4, abus5, abus6, abus7, abus8, abus9, abus10, abus11, abus12, abus13, abus14, abus15, abus16_segsel,
        ldmem_bar, enmem_bar, flag_supervisor
        );

    // bus interface - ALU <> DATA

    and_01 = new LS08("and01", mem2aluhi_bar, aluhi2mem_bar, enhi_bar, mem2alulo_bar, alulo2mem_bar, enlo_bar, nc, nc, nc, nc, nc, nc);
    hitransciever = new LS245("hitrcv", enhi_bar, aluhi2mem_bar, dbus0, dbus1, dbus2, dbus3, dbus4, dbus5, dbus6, dbus7, alubus8, alubus9, alubus10, alubus11, alubus12, alubus13, alubus14, alubus15);
    lotransciever = new LS245("lotrcv", enlo_bar, alulo2mem_bar, dbus0, dbus1, dbus2, dbus3, dbus4, dbus5, dbus6, dbus7, alubus0, alubus1, alubus2, alubus3, alubus4, alubus5, alubus6, alubus7);
    mem2alulo_ext = new LS244("mem2alulo_ext", mem2alulo_bar, mem2alulo_bar, dbus7, dbus7, dbus7, dbus7, dbus7, dbus7, dbus7, dbus7, alubus8, alubus9, alubus10, alubus11, alubus12, alubus13, alubus14, alubus15);    

    /*
    dmem2alulo = new LS244("dmem2alulo", mem2alulo_bar, mem2alulo_bar, dbus0, dbus1, dbus2, dbus3, dbus4, dbus5, dbus6, dbus7, alubus0, alubus1, alubus2, alubus3, alubus4, alubus5, alubus6, alubus7);
    dalulo2mem = new LS244("dalulo2mem", alulo2mem_bar, alulo2mem_bar, alubus0, alubus1, alubus2, alubus3, alubus4, alubus5, alubus6, alubus7, dbus0, dbus1, dbus2, dbus3, dbus4, dbus5, dbus6, dbus7);

    dmem2aluhi = new LS244("dmem2aluhi", mem2aluhi_bar, mem2aluhi_bar, dbus0, dbus1, dbus2, dbus3, dbus4, dbus5, dbus6, dbus7, alubus8, alubus9, alubus10, alubus11, alubus12, alubus13, alubus14, alubus15);
    daluhi2mem = new LS244("daluhi2mem", aluhi2mem_bar, aluhi2mem_bar, alubus8, alubus9, alubus10, alubus11, alubus12, alubus13, alubus14, alubus15, dbus0, dbus1, dbus2, dbus3, dbus4, dbus5, dbus6, dbus7);
    */

    // bus interface - ADDRESS > RBUS

    abus2rbusl = new LS244("abus2rbusl", enabus_bar, enabus_bar, abus8, abus9, abus10, abus11, abus12, abus13, abus14, abus15, rbus8, rbus9, rbus10, rbus11, rbus12, rbus13, rbus14, rbus15);
    abus2rbush = new LS244("abus2rbush", enabus_bar, enabus_bar, abus0, abus1, abus2, abus3, abus4, abus5, abus6, abus7, rbus0, rbus1, rbus2, rbus3, rbus4, rbus5, rbus6, rbus7);

    // probes

    p_0 = new Probe("abus", abus16_segsel, abus15, abus14, abus13, abus12, abus11, abus10, abus9, abus8, abus7, abus6, abus5, abus4, abus3, abus2, abus1, abus0);
    p_1 = new Probe("dbus", dbus7, dbus6, dbus5, dbus4, dbus3, dbus2, dbus1, dbus0);
    //p_2 = new Probe("alulo2mem_", alulo2mem_bar);
    //p_3 = new Probe("emem2alulo_", mem2alulo_bar);
    //p_4 = new Probe("aluhi2mem_", aluhi2mem_bar);
    //p_5 = new Probe("mem2aluhi_", mem2aluhi_bar);
}

void Computer::go(long t, long cycles)
{
    power->go(0);
    reset->go(0);

    time_t rtc_start, rtc_end;
    rtc_start = std::time(NULL);

    if (cycles == -1)   // run until halted
    {
        cycle = 0;
        while (!this->isHalted(time))
        {
            // flip master clock eight times to get a full cycle of a multiphase clock
            osc->go();   // LO->HI
            osc->go();   // HI->LO
            osc->go();   // LO->HI
            osc->go();   // HI->LO
            osc->go();   // LO->HI
            osc->go();   // HI->LO
            osc->go();   // LO->HI
            time = osc->go();   // HI->LO
            debugInfo(time);
            cycle++;
        }
        cout << "Machine halted." << endl;
    }
    else
    {
        for (cycle=0; cycle <= cycles; cycle++) // run for a specific number of cycles
        {
            // assert interrupt lines
            //if (cycle == 130) irq->go(3, time+100, 70000);
            //if (cycle == 250) irq->go(2, time+200, 10000);
            //if (cycle == 250) irq->go(4, time+320, 10000);
            // flip master clock eight times to get a full cycle of a multiphase clock
            osc->go();          // LO->HI
            osc->go();          // HI->LO
            osc->go();          // LO->HI
            osc->go();          // HI->LO
            osc->go();          // LO->HI
            osc->go();          // HI->LO
            osc->go();          // LO->HI
            time = osc->go();   // HI->LO
            debugInfo(time);
        }
    }

    rtc_end = std::time(NULL);
    cout<<"Simulation time "<<(rtc_end - rtc_start)/60<<" minutes."<<endl;
    cout<<"Average cycle time "<<setprecision(2)<<fixed<<float(rtc_end - rtc_start)/float(cycle)<<" seconds ("<<setprecision(2)<<fixed<<float(float(cycle)/float(rtc_end - rtc_start))<<" cycles per second)."<<endl;
}

void Computer::debugInfo(long t)
{
    cout << "====== after cycle: " << cycle << " ==== time elapsed: " << t << " ns" << endl;
    // cout << "Max propagation time: "<<tmax<<endl;
    control->debugInfo(t);
    memory->debugInfo(t);
    p_0->debugInfo(t);
    p_1->debugInfo(t);
    //p_2->debugInfo(t);
    //p_3->debugInfo(t);
    //p_4->debugInfo(t);
    //p_5->debugInfo(t);
    alu->debugInfo(t);
    registers->debugInfo(t);
    cout << endl;
}

bool Computer::isHalted(long t)
{
    if (control->isHalted(t))
    {
        return true;
    }
    return false;
}

Computer::~Computer()
{
    delete power;
    delete osc;
    delete reset;
    delete irq;
    delete control;
    delete registers;
    delete memory;
    delete alu;

    delete and_01;
    delete hitransciever;
    delete lotransciever;
    delete mem2alulo_ext;
    //delete dmem2alulo;
    //delete dmem2aluhi;
    //delete dalulo2mem;
    //delete daluhi2mem;

    delete abus2rbush;
    delete abus2rbusl;

    delete p_0;
    delete p_1;
    //delete p_2;
    //delete p_3;
    //delete p_4;
    //delete p_5;
}


