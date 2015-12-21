/* 
 * 
 *    Memory.cpp - this file is part of CPU Simulator
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
#include "Memory.h"

using namespace simulation;
using namespace std;

Memory::Memory(std::string label, Wire& gnd, Wire& vcc, Wire& clk0, Wire& clk1,
        Wire& dbus0, Wire& dbus1, Wire& dbus2, Wire& dbus3, Wire& dbus4, Wire& dbus5, Wire& dbus6, Wire& dbus7,
        Wire& abus0, Wire& abus1, Wire& abus2, Wire& abus3, Wire& abus4, Wire& abus5, Wire& abus6, Wire& abus7, Wire& abus8, Wire& abus9, Wire& abus10, Wire& abus11, Wire& abus12, Wire& abus13, Wire& abus14, Wire& abus15, Wire& abus16_segsel,
        Wire& ldmem_bar, Wire& enmem_bar, Wire& supermode_bar) : Device(label)
{
    nc.NC();

    // glue logic
    nand0 = new LS00("nand0", bank0rom_bar, vcc, bank0rom, supermode_bar, vcc, supermode, nc, nc, nc, nc, nc, nc);
    or0 = new LS32("or0", bank0rom, bank0sel_bar, bank0ram_bar, cp0_bar, supermode, cp0s_bar, dp0_bar, supermode, dp0s_bar, p0_bar, supermode_bar, p0s_bar);    
    and0 = new LS08("and0", cp0_bar, dp0_bar, p0_bar, io_bar, regs_bar, nophysmem_bar, nc, nc, nc, nc, nc, nc);
        
    // logical address bus decode (page select)
    ldecode0 = new LS139("ldecode0", gnd, gnd, abus15, abus16_segsel, cp0_bar, dp0_bar, cp1_bar, dp1_bar, nc, nc, nc, nc, nc, nc);

    // logical address bus decode (system area: I/O, special registers select)
    ldecode1 = new LS138("ldecode1", abus16_segsel, supermode_bar, abus15, abus12, abus13, abus14, nc, io_bar, regs_bar, nc, nc, nc, nc, nc);
    ldecode2 = new LS138("ldecode2", vcc, ldmem_bar, regs_bar, abus9, abus10, abus11, we_cp0, we_cp1, we_dp0, we_dp1, nc, nc, nc, nc);
    
    // page registers
    cpage0 = new LS374("cpage0", we_cp0, cp0s_bar, dbus0, dbus1, dbus2, dbus3, dbus4, dbus5, dbus6, dbus7, pbus15, pbus16, pbus17, pbus18, pbus19, pbus20, pbus21, nc);
    cpage1 = new LS374("cpage1", we_cp1, cp1_bar , dbus0, dbus1, dbus2, dbus3, dbus4, dbus5, dbus6, dbus7, pbus15, pbus16, pbus17, pbus18, pbus19, pbus20, pbus21, nc);
    dpage0 = new LS374("dpage0", we_dp0, dp0s_bar, dbus0, dbus1, dbus2, dbus3, dbus4, dbus5, dbus6, dbus7, pbus15, pbus16, pbus17, pbus18, pbus19, pbus20, pbus21, nc);
    dpage1 = new LS374("dpage1", we_dp1, dp1_bar , dbus0, dbus1, dbus2, dbus3, dbus4, dbus5, dbus6, dbus7, pbus15, pbus16, pbus17, pbus18, pbus19, pbus20, pbus21, nc);
    cdpage0s = new LS244("cdpage0s", p0s_bar, p0s_bar, gnd, gnd, abus16_segsel, gnd, gnd, gnd, gnd, gnd, pbus15, pbus16, pbus17, pbus18, pbus19, pbus20, pbus21, nc);
    
    // physical address decoding (memory chip select)
    pdecode0 = new LS138("pdecode0", nophysmem_bar, gnd, gnd, pbus19, pbus20, pbus21, bank0sel_bar, bank1sel_bar, bank2sel_bar, bank3sel_bar, bank4sel_bar, bank5sel_bar, bank6sel_bar, bank7sel_bar);
    pdecode1 = new LS139("pdecode1", bank0sel_bar, vcc, pbus18, pbus17, bank0rom_bar, nc, nc, nc, nc, nc, nc, nc, nc, nc);

    // ROM (128k)
    rom = new EEPROM_29F020("rom", "osrom.bin", bank0rom_bar, enmem_bar, vcc,
        abus0, abus1, abus2, abus3, abus4, abus5, abus6, abus7, abus8, abus9, abus10, abus11, abus12, abus13, abus14, pbus15, pbus16, gnd, 
        dbus0, dbus1, dbus2, dbus3, dbus4, dbus5, dbus6, dbus7);

    // RAM banks (4 x 512k)
    bank0 = new SRAM_628512("membank0", bank0ram_bar /*cs*/, enmem_bar /*oe*/, ldmem_bar, 
        abus0, abus1, abus2, abus3, abus4, abus5, abus6, abus7, abus8, abus9, abus10, abus11, abus12, abus13, abus14, pbus15, pbus16, pbus17, pbus18, 
        dbus0, dbus1, dbus2, dbus3, dbus4, dbus5, dbus6, dbus7);

    bank1 = new SRAM_628512("membank1", bank1sel_bar, enmem_bar, ldmem_bar, 
        abus0, abus1, abus2, abus3, abus4, abus5, abus6, abus7, abus8, abus9, abus10, abus11, abus12, abus13, abus14, pbus15, pbus16, pbus17, pbus18, 
        dbus0, dbus1, dbus2, dbus3, dbus4, dbus5, dbus6, dbus7);
    
    bank2 = new SRAM_628512("membank2", bank2sel_bar, enmem_bar, ldmem_bar, 
        abus0, abus1, abus2, abus3, abus4, abus5, abus6, abus7, abus8, abus9, abus10, abus11, abus12, abus13, abus14, pbus15, pbus16, pbus17, pbus18, 
        dbus0, dbus1, dbus2, dbus3, dbus4, dbus5, dbus6, dbus7);
    
    bank3 = new SRAM_628512("membank3", bank3sel_bar, enmem_bar, ldmem_bar, 
        abus0, abus1, abus2, abus3, abus4, abus5, abus6, abus7, abus8, abus9, abus10, abus11, abus12, abus13, abus14, pbus15, pbus16, pbus17, pbus18, 
        dbus0, dbus1, dbus2, dbus3, dbus4, dbus5, dbus6, dbus7);

    // probes
    
    /*
    p1 = new Probe("bank0sel_", bank0sel_bar);
    p2 = new Probe("bank1sel_", bank1sel_bar);
    p3 = new Probe("bank2sel_", bank2sel_bar);
    p4 = new Probe("bank3sel_", bank3sel_bar);
    p5 = new Probe("bank0rom_", bank0rom_bar);
    p6 = new Probe("bank0ram_", bank0ram_bar);
    
    p1a = new Probe("cp0s_", cp0s_bar);
    p2a = new Probe("cp1_", cp1_bar);
    p3a = new Probe("dp0s_", dp0s_bar);
    p4a = new Probe("dp1_", dp1_bar);
    
    p1a = new Probe("we_cp0_", we_cp0);
    p2a = new Probe("we_cp1_", we_cp1);
    p3a = new Probe("we_dp0_", we_dp0);
    p4a = new Probe("we_dp1_", we_dp1); 
    
    p5a = new Probe("p0s_", p0s_bar);
    p6a = new Probe("mempage", gnd, pbus21, pbus20, pbus19, pbus18, pbus17, pbus16, pbus15);
    
    p7 = new Probe("we_", we_bar);
    p8 = new Probe("enmem_", enmem_bar);
    */
    p9 = new Probe("pbus", gnd, gnd, gnd, gnd, gnd, gnd, gnd, gnd, gnd, gnd, pbus21, pbus20, pbus19, pbus18, pbus17, pbus16, pbus15, 
                            abus14, abus13, abus12, abus11, abus10, abus9, abus8, abus7, abus6, abus5, abus4, abus3, abus2, abus1, abus0);
    
}

Memory::~Memory()
{
    delete nand0; delete or0; delete and0;
    delete ldecode0; delete ldecode1; delete ldecode2;
    delete cpage0; delete cpage1;
    delete dpage0; delete dpage1;
    delete cdpage0s;
    delete pdecode0; delete pdecode1;
    delete rom;
    delete bank0; delete bank1; delete bank2; delete bank3;

    /*
    delete p1;
    delete p2;
    delete p3;
    delete p4; 
    delete p1a;
    delete p2a;
    delete p3a;
    delete p4a;     
    delete p5a;     
    delete p6a;
    delete p5; 
    delete p6; 
    delete p7; 
    delete p8;
    */
    delete p9;
}

void Memory::go(long t)
{
    begin(t);
    end();
}

void Memory::debugInfo(long t)
{
    /*
    p1->debugInfo(t);
    p2->debugInfo(t);
    p3->debugInfo(t);
    p4->debugInfo(t);
    p1a->debugInfo(t);
    p2a->debugInfo(t);
    p3a->debugInfo(t);
    p4a->debugInfo(t);  
    p5a->debugInfo(t);      
    p6a->debugInfo(t);          
    p5->debugInfo(t);
    p6->debugInfo(t);
    p7->debugInfo(t);
    p8->debugInfo(t);
    */
    p9->debugInfo(t);
    
}
