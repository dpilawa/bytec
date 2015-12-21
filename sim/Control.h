/* 
 * 
 *    Control.h - this file is part of CPU Simulator
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

class Control : public Device
{
    Device *clk_gen, *clk_or, *clk_rst_sync;
    Device *step_0, *step_1;
    Device *ff_0;
    Device *ir_0;
    Device *uc_0, *uc_1, *uc_2, *uc_3;
    Device *irqsync;
    Device *pe_0, *pe_1;
    Device *pe_latch;
    Device *nand_0;
    Device *or_0;
    Device *and_pe;
    Device *and_0;
    Device *mux_0, *mux_1;
    Device *dec_0, *dec_1, *dec_2, *dec_3;
    Device *finhbt_0;

    Device *msw_0, *msw_1, *msw_2;
    Device *and_msw;
    Device *or_msw;
    Device *mux_msw;


    Device *flagbuf;
    Device *iptrbuf0, *iptrbuf1;

    Probe* p_0;
    Probe* p_1;
    Probe* p_2;
    Probe* p_3;
    Probe* p_4;
    Probe* p_5;
    Probe* p_6;
    Probe* p_7;
    Probe* p_8;
    Probe* p_9;
    Probe *p_microcode;
    Probe *pf0, *pf1, *pf2, *pf3, *pf4, *pf5, *pf6, *pf7;
    Probe *irqline0, *irqline1, *irqline2, *irqline3, *irqline4, *irqline5, *irqline6, *irqline7;

    Wire clkgenloop;
    Wire busclk, rstclk;
    Wire rco;
    Wire cnt0, cnt1, cnt2, cnt3, cnt4;
    Wire rstcnt_bar;
    Wire incpc_raw_bar;
    Wire nc;
    Wire uc00, uc01, uc02, uc03, uc04, uc05, uc06, uc07;
    Wire uc10, uc11, uc12, uc13, uc14, uc15, uc16, uc17;
    Wire uc20, uc21, uc22, uc23, uc24, uc25, uc26, uc27;
    Wire uc30, uc31, uc32, uc33, uc34, uc35, uc36, uc37;
    Wire sirq0, sirq1, sirq2, sirq3, sirq4, sirq5, sirq6, sirq7;
    Wire loadir_bar;
    Wire ir0, ir1, ir2, ir3, ir4, ir5, ir6, ir7;
    Wire op0, op1, op2, op3, op4, op5, op6, op7;
    Wire op_page, op_page_bar;
    Wire fault_bar, int_bar, fault, oe_bar, ei_bar;
    Wire faultint;
    Wire fault_protectionfault;
    Wire pe00, pe01, pe02, pe10, pe11, pe12;
    Wire pe0, pe1, pe2, pe3;
    Wire pe0_out, pe1_out, pe2_out, pe3_out;
    Wire op_page_pr_bar, op_page_cl_bar;
    Wire cntsp_uc_bar, incpc_uc_bar;
    Wire enalu_nosync_bar, enmem_nosync_bar;
    Wire loadaluflags_bar, ldf_bar, ld_i_bar, ld_s_bar;
    Wire latch_i_bar, latch_s_bar, latch_none_bar;
    Wire ld_i_clk, ld_s_clk;
    Wire uc11_fault_bar;
    Wire eniptr_bar;

    Wire mswmux0, mswmux1, mswmux2, mswmux3;
    Wire flag_carry, flag_zero, flag_negative, flag_overflow, flag_interrupt, flag_f6, flag_f7;

public:
    Control(std::string label, Wire& gnd, Wire& vcc, Wire& master_clk, Wire& clk0, Wire& clk1,
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
        Wire& abus16_segsel, Wire& incpc_bar, Wire& incmar_bar, Wire& cntsp_bar, Wire& cntspdir,
        Wire& loadaluflags0, Wire& loadaluflags1,
        Wire& aluc, Wire& aluz, Wire& alun, Wire& aluv,
        Wire& irq0, Wire& irq1, Wire& irq2, Wire& irq3, Wire& irq4, Wire& irq5, Wire& irq6, Wire& irq7,
        Wire& flag_supervisor
    );
    ~Control();
    void go(long t);
    void debugInfo(long t);
    bool isHalted(long t);
};

};
