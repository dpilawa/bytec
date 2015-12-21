/* 
 * 
 *    Memory.h - this file is part of CPU Simulator
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

class Memory : public Device
{
    SRAM_628512 *bank0, *bank1, *bank2, *bank3;
    Device *rom;
    Device *nand0; Device *or0; Device *and0;
    Device *ldecode0, *ldecode1, *ldecode2;
    Device *cpage0; Device *cpage1;
    Device *dpage0; Device *dpage1;
    Device *cdpage0s;
    Device *pdecode0; Device *pdecode1;

    Wire nc;

    Wire bank0sel_bar, bank1sel_bar, bank2sel_bar, bank3sel_bar, bank4sel_bar, bank5sel_bar, bank6sel_bar, bank7sel_bar;
    Wire bank0rom_bar, bank0ram_bar, bank0rom;
    Wire supermode;
    Wire we_bar, we2_bar;
    Wire cp0_bar, dp0_bar, cp1_bar, dp1_bar, cp0s_bar, dp0s_bar, p0s_bar, p0_bar;
    Wire io_bar, regs_bar, nophysmem_bar;
    Wire we_cp0, we_cp1, we_dp0, we_dp1;
    
    // physical bus
    Wire pbus15, pbus16, pbus17;
    Wire pbus18, pbus19, pbus20, pbus21;

    Probe *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8, *p9;
    Probe *p1a, *p2a, *p3a, *p4a, *p5a, *p6a;

    
public:
    Memory(std::string label, Wire& gnd, Wire& vcc, Wire& clk0, Wire& clk1,
        Wire& dbus0, Wire& dbus1, Wire& dbus2, Wire& dbus3, Wire& dbus4, Wire& dbus5, Wire& dbus6, Wire& dbus7,
        Wire& abus0, Wire& abus1, Wire& abus2, Wire& abus3, Wire& abus4, Wire& abus5, Wire& abus6, Wire& abus7, Wire& abus8, Wire& abus9, Wire& abus10, Wire& abus11, Wire& abus12, Wire& abus13, Wire& abus14, Wire& abus15, Wire& abus16_segsel,
        Wire& ldmem_bar, Wire& enmem_bar, Wire& supermode);
    ~Memory();
    void go(long t);
    void debugInfo(long t);
};

}
