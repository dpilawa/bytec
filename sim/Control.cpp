/* 
 * 
 *    Control.cpp - this file is part of CPU Simulator
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

using namespace simulation;
using namespace std;

Control::Control(std::string label,
                 Wire& gnd, Wire& vcc,
                 Wire& master_clk, Wire& clk0, Wire& clk1,
                 Wire& rst_bar_nonsync, Wire& rst_bar, Wire& rst,
                 Wire& dbus0, Wire& dbus1, Wire& dbus2, Wire& dbus3, Wire& dbus4, Wire& dbus5, Wire& dbus6, Wire& dbus7,
                 Wire& alubus0, Wire& alubus1, Wire& alubus2, Wire& alubus3, Wire& alubus4, Wire& alubus5, Wire& alubus6, Wire& alubus7, Wire& alubus8, Wire& alubus9, Wire& alubus10, Wire& alubus11, Wire& alubus12, Wire& alubus13, Wire& alubus14, Wire& alubus15,
                 Wire& rbus0, Wire& rbus1, Wire& rbus2, Wire& rbus3, Wire& rbus4, Wire& rbus5, Wire& rbus6, Wire& rbus7, Wire& rbus8, Wire& rbus9, Wire& rbus10, Wire& rbus11, Wire& rbus12, Wire& rbus13, Wire& rbus14, Wire& rbus15,
                 Wire& enmdrl_bar, Wire& ena_bar, Wire& enx_bar, Wire& eny_bar,
                 Wire& enmdrr_bar, Wire& enmsw_bar, Wire& enabus_bar, Wire& enppc_bar,
                 Wire& enmar_bar, Wire& ensp_bar, Wire& endp_bar, Wire& enpc_bar,
                 Wire& mdr_load_inhibit,
                 Wire& ldmdrlo_bar, Wire& ldmdrhi_bar, Wire& ldmdr_bar, Wire& ldalo_bar, Wire& ldahi_bar, Wire& lda_bar, Wire& ldx_bar, Wire& ldy_bar,
                 Wire& ldmem_bar, Wire& ldmarlo_bar, Wire& ldmarhi_bar, Wire& ldmar_bar, Wire& ldsp_bar, Wire& lddp_bar, Wire& ldpc_bar, Wire& ldmsw_bar,
                 Wire& loadirclk,
                 Wire& aluop0, Wire& aluop1, Wire& aluop2, Wire& aluop3,
                 Wire& alumode, Wire& alucarryin_bar, Wire& alushr_bar,
                 Wire& enalu_bar, Wire& enmem_bar,
                 Wire& mem2alulo_bar, Wire& mem2aluhi_bar, Wire& alulo2mem_bar, Wire& aluhi2mem_bar,
                 Wire& abus16_segsel,
                 Wire& incpc_bar, Wire& incmar_bar, Wire& cntsp_bar, Wire& cntspdir,
                 Wire& loadaluflags0, Wire& loadaluflags1,
                 Wire& aluc, Wire& aluz, Wire& alun, Wire& aluv,
                 Wire& irq0, Wire& irq1, Wire& irq2, Wire& irq3, Wire& irq4, Wire& irq5, Wire& irq6, Wire& irq7,
                 Wire& flag_supervisor
                 )
                 : Device(label)
{

    nc.NC();

    // devices - multiphase clocks generation
    clk_gen = new LS74("clk_gen", master_clk, master_clk, vcc, vcc, vcc, vcc, clkgenloop, clk0, clk0, clk1, nc, clkgenloop);
    clk_or = new LS32("clk_or", clk0, clk1, busclk, nc, nc, nc, nc, nc, nc, nc, nc, nc);
    clk_rst_sync = new LS74("clk_rst_sync", clk1, vcc, vcc, vcc, vcc, vcc, rst_bar_nonsync, vcc, rst_bar, nc, rst, nc);

    // glue logic
    and_0 = new LS08("and0", loadir_bar, rst_bar, rstcnt_bar, uc11, latch_none_bar, mdr_load_inhibit, nc, nc, nc, nc, nc, nc);
    nand_0 = new LS00("nand0", mem2alulo_bar, mem2aluhi_bar, enalu_bar, alulo2mem_bar, aluhi2mem_bar, enmem_bar, flag_supervisor, uc35, fault_protectionfault, uc11, fault_bar, uc11_fault_bar);

    // devices - priority encoder
    irqsync = new LS273("irqsync", clk0, vcc, irq7, irq6, irq5, irq4, irq3, irq2, irq1, irq0, sirq7, sirq6, sirq5, sirq4, sirq3, sirq2, sirq1, sirq0);
    pe_0 = new LS148("pe0", gnd, vcc, vcc, vcc, vcc, vcc, vcc, vcc, fault_protectionfault, pe00, pe01, pe02, oe_bar, fault_bar);
    pe_1 = new LS148("pe1", ei_bar, sirq7, sirq6, sirq5, sirq4, sirq3, sirq2, sirq1, sirq0, pe10, pe11, pe12, nc, int_bar);
    and_pe = new LS08("andpe", pe00, pe10, pe0_out, pe01, pe11, pe1_out, pe02, pe12, pe2_out, fault_bar, int_bar, faultint);
    pe_latch = new LS173("pe_latch", clk0, rst, rstcnt_bar, rstcnt_bar, gnd, gnd, pe0_out, pe1_out, pe2_out, int_bar, pe0, pe1, pe2, pe3);

    // devices - step counter
    step_0 = new LS163A("step0", clk0, rstcnt_bar, vcc, vcc, vcc, gnd, gnd, gnd, gnd, cnt0, cnt1, cnt2, cnt3, rco);
    step_1 = new LS163A("step1", clk0, rstcnt_bar, vcc, rco, rco, gnd, gnd, gnd, gnd, cnt4, nc, nc, nc, nc);

    // devices - IR
    or_0 = new LS32("or0", rstcnt_bar, busclk, loadirclk, oe_bar, flag_interrupt, ei_bar, nc, nc, nc, nc, nc, nc);
    ir_0 = new LS273("ir0", loadirclk, rst_bar, dbus0, dbus1, dbus2, dbus3, dbus4, dbus5, dbus6, dbus7, ir0, ir1, ir2, ir3, ir4, ir5, ir6, ir7);

    // devices - mux
    ff_0 = new LS74("ff", nc, loadirclk, nc, rst_bar, nc, vcc, nc, faultint, nc, op_page, nc, op_page_bar);
    mux_0 = new LS157("mux0", gnd, op_page, pe0, pe1, pe2, pe3, ir0, ir1, ir2, ir3, op0, op1, op2, op3);
    mux_1 = new LS157("mux1", gnd, op_page, gnd, gnd, gnd, gnd, ir4, ir5, ir6, ir7, op4, op5, op6, op7);

    // devices - IPTR pseudoregister
    iptrbuf0 = new LS244("iptrbuf0", eniptr_bar, eniptr_bar, gnd, op0, op1, op2, op3, gnd, gnd, gnd, rbus0, rbus1, rbus2, rbus3, rbus4, rbus5, rbus6, rbus7);
    iptrbuf1 = new LS244("iptrbuf1", eniptr_bar, eniptr_bar, gnd, gnd, gnd, gnd, gnd, gnd, gnd, gnd, rbus8, rbus9, rbus10, rbus11, rbus12, rbus13, rbus14, rbus15);

    // devices - MSW
    and_msw = new LS08("andmsw", loadaluflags0, loadaluflags1, loadaluflags_bar,
                                 loadaluflags_bar, ldmsw_bar, ldf_bar,
                                 latch_i_bar, ldmsw_bar, ld_i_bar,
                                 latch_s_bar, ldmsw_bar, ld_s_bar);

    mux_msw = new LS157("mux_msw", gnd, ldmsw_bar,
        alubus0, alubus1, alubus2, alubus3, aluc, aluz, alun, aluv, mswmux0, mswmux1, mswmux2, mswmux3);

    or_msw = new LS32("ormsw", ld_i_bar, busclk, ld_i_clk, ld_s_bar, busclk, ld_s_clk, nc, nc, nc, nc, nc, nc);

    msw_0 = new LS173("msw_0", clk0, rst, ldf_bar, ldf_bar, gnd, gnd, mswmux0, mswmux1, mswmux2, mswmux3, flag_carry, flag_zero, flag_negative, flag_overflow);
    msw_1 = new LS74("msw_1", ld_i_clk, ld_s_clk, rst_bar, vcc, vcc, rst_bar, alubus4, alubus5, flag_interrupt, flag_supervisor, nc, nc);
    msw_2 = new LS74("msw_2", ldmsw_bar, ldmsw_bar, vcc, vcc, vcc, vcc, alubus6, alubus7, flag_f6, flag_f7, nc, nc);

    flagbuf = new LS244("flagbuf", enmsw_bar, enmsw_bar, flag_carry, flag_zero, flag_negative, flag_overflow, flag_interrupt, flag_supervisor, flag_f6, flag_f7, rbus0, rbus1, rbus2, rbus3, rbus4, rbus5, rbus6, rbus7);

    // devices - field decoders

    dec_0 = new LS139("adrbus_sel&busmode", gnd, uc11 /*busifcen*/,
                        uc05, uc06, enmar_bar, ensp_bar, endp_bar, enpc_bar,
                        uc07, uc10, mem2alulo_bar, mem2aluhi_bar, alulo2mem_bar, aluhi2mem_bar);

    dec_1 = new LS139("misc_latch&alul_sel", uc11_fault_bar /*not busifcen and not fault*/, gnd,
                        uc07, uc10, latch_i_bar, latch_s_bar, nc, latch_none_bar,
                        uc00, uc01, enmdrl_bar, ena_bar, enx_bar, eny_bar);

    dec_2 = new LS154("load_sel", busclk, oe_bar /* inhibit load on fault */, uc15, uc14, uc13, uc12,
        ldmdrlo_bar, ldmdrhi_bar, ldmdr_bar, ldalo_bar, ldahi_bar, lda_bar, ldx_bar, ldy_bar,
        ldmem_bar, ldmarlo_bar, ldmarhi_bar, ldmar_bar, ldsp_bar, lddp_bar, ldpc_bar, ldmsw_bar);

    dec_3 = new LS138("alur_sel", vcc, gnd, gnd, uc04, uc03, uc02,
                        enmdrr_bar, enmsw_bar, enabus_bar, eniptr_bar, enppc_bar, nc, nc, nc);

    finhbt_0 = new LS32("finhbt_0", cntsp_uc_bar, oe_bar, cntsp_bar, incpc_uc_bar, oe_bar, incpc_bar, nc, nc, nc, nc, nc, nc);

    // microcode EEPROMS
    uc_0 = new EEPROM_29F020("microcode0", "microcode000.bin", gnd, gnd, vcc,
                            flag_overflow, flag_negative, flag_zero, flag_carry,
                            cnt0, cnt1, cnt2, cnt3, cnt4,
                            op0, op1, op2, op3, op4, op5, op6, op7, op_page_bar,
                            uc07, uc06, uc05, uc04, uc03, uc02, uc01, uc00);

    uc_1 = new EEPROM_29F020("microcode1", "microcode001.bin", gnd, gnd, vcc,
                            flag_overflow, flag_negative, flag_zero, flag_carry,
                            cnt0, cnt1, cnt2, cnt3, cnt4,
                            op0, op1, op2, op3, op4, op5, op6, op7, op_page_bar,
                            aluop3, loadir_bar, uc15, uc14, uc13, uc12, uc11, uc10);

    uc_2 = new EEPROM_29F020("microcode2", "microcode002.bin", gnd, gnd, vcc,
                            flag_overflow, flag_negative, flag_zero, flag_carry,
                            cnt0, cnt1, cnt2, cnt3, cnt4,
                            op0, op1, op2, op3, op4, op5, op6, op7, op_page_bar,
                            loadaluflags0, loadaluflags1, alushr_bar, alucarryin_bar, alumode, aluop0, aluop1, aluop2);

    uc_3 = new EEPROM_29F020("microcode3", "microcode003.bin", gnd, gnd, vcc,
                            flag_overflow, flag_negative, flag_zero, flag_carry,
                            cnt0, cnt1, cnt2, cnt3, cnt4,
                            op0, op1, op2, op3, op4, op5, op6, op7, op_page_bar,
                            uc37, uc36, uc35 /*supervisor*/, abus16_segsel, cntspdir, cntsp_uc_bar, incmar_bar, incpc_uc_bar);


    // probes
    p_0 = new Probe("rst_", rst_bar);
    p_1 = new Probe("stepcnt", cnt4, cnt3, cnt2, cnt1, cnt0);
    p_2 = new Probe("opcode", op_page_bar, op7, op6, op5, op4, op3, op2, op1, op0);
    p_3 = new Probe("fault_", fault_bar);
    p_4 = new Probe("interrupt_", int_bar);
    p_5 = new Probe("pe_latch", gnd, pe3, pe2, pe1, pe0);
    p_6 = new Probe("IR", ir7, ir6, ir5, ir4, ir3, ir2, ir1, ir0);
    //p_7 = new Probe("fault_", fault_bar);
    //p_8 = new Probe("int_", int_bar);
    // p_9 = new Probe("mdr_load_inhibit", mdr_load_inhibit);
    p_microcode = new Probe("microcode", uc00, uc01, uc02, uc03, uc04, uc05, uc06, uc07,
                                         uc10, uc11, uc12, uc13, uc14, uc15, loadir_bar, aluop3,
                                         aluop2, aluop1, aluop0, alumode, alucarryin_bar, alushr_bar, loadaluflags1, loadaluflags0,
                                         incpc_bar, incmar_bar, cntsp_bar, cntspdir, abus16_segsel, uc35, uc36, uc37);

    pf7 = new Probe("pf7", flag_f7);
    pf6 = new Probe("pf6", flag_f6);
    pf5 = new Probe("pf5", flag_supervisor);
    pf4 = new Probe("pf4", flag_interrupt);
    pf3 = new Probe("pf3", flag_overflow);
    pf2 = new Probe("pf2", flag_negative);
    pf1 = new Probe("pf1", flag_zero);
    pf0 = new Probe("pf0", flag_carry);

    irqline0 = new Probe("irq0", irq0);
    irqline1 = new Probe("irq1", irq1);
    irqline2 = new Probe("irq2", irq2);
    irqline3 = new Probe("irq3", irq3);
    irqline4 = new Probe("irq4", irq4);
    irqline5 = new Probe("irq5", irq5);
    irqline6 = new Probe("irq6", irq6);
    irqline7 = new Probe("irq7", irq7);
}

Control::~Control()
{
    delete clk_gen;
    delete clk_or;
    delete clk_rst_sync;

    delete and_0;
    delete nand_0;

    delete irqsync;
    delete pe_0; delete pe_1;
    delete and_pe;
    delete pe_latch;

    delete step_0;
    delete step_1;
    delete or_0;
    delete ir_0;

    delete ff_0;
    delete mux_0;
    delete mux_1;

    delete mux_msw;
    delete and_msw;
    delete or_msw;
    delete msw_0; delete msw_1; delete msw_2;
    delete flagbuf;

    delete iptrbuf0; delete iptrbuf1;

    delete dec_0; delete dec_1; delete dec_2; delete dec_3;
    delete finhbt_0;

    delete uc_0; delete uc_1; delete uc_2; delete uc_3;

    delete p_0; delete p_1; delete p_2; delete p_3; delete p_4; delete p_5; delete p_6; // delete p_7; delete p_8; delete p_9;
    delete pf0; delete pf1; delete pf2; delete pf3; delete pf4; delete pf5; delete pf6; delete pf7;
    delete irqline0; delete irqline1; delete irqline2; delete irqline3; delete irqline4; delete irqline5; delete irqline6; delete irqline7;
    delete p_microcode;
}

void Control::go(long t)
{
    begin(t);
    end();
}

bool Control::isHalted(long t)
{
    if (p_2->getValue(t) == 1)
    {
        return true;
    }
    return false;
}

void Control::debugInfo(long t)
{
    // flags
    cout<<endl;
    cout<<"            --SIVNZC"<<endl;
    cout<<"     FLAGS: ";
    pf7->debugInfoBit(t);
    pf6->debugInfoBit(t);
    pf5->debugInfoBit(t);
    pf4->debugInfoBit(t);
    pf3->debugInfoBit(t);
    pf2->debugInfoBit(t);
    pf1->debugInfoBit(t);
    pf0->debugInfoBit(t);
    cout<<endl<<endl;;

    // IRQ
    cout<<"            01234567"<<endl;
    cout<<"       IRQ: ";
    irqline0->debugInfoBit(t);
    irqline1->debugInfoBit(t);
    irqline2->debugInfoBit(t);
    irqline3->debugInfoBit(t);
    irqline4->debugInfoBit(t);
    irqline5->debugInfoBit(t);
    irqline6->debugInfoBit(t);
    irqline7->debugInfoBit(t);
    cout<<endl<<endl;;

    p_0->debugInfo(t);
    p_1->debugInfo(t);
    p_2->debugInfo(t);
    p_3->debugInfo(t);
    p_4->debugInfo(t);
    p_5->debugInfo(t);
    p_6->debugInfo(t);
    //p_7->debugInfo(t);
    //p_8->debugInfo(t);
    //p_9->debugInfo(t);
    p_microcode->debugInfo(t);
}
