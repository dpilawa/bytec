/* 
 * 
 *    Registers.h - this file is part of CPU Simulator
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

class Registers : public Device
{
    Wire nc;
    Wire rcopc0_bar, rcopc1_bar, rcopc2_bar;
    Wire rcomar0_bar, rcomar1_bar, rcomar2_bar;
    Wire rcousp0_bar, rcousp1_bar, rcousp2_bar;
    Wire rcoksp0_bar, rcoksp1_bar, rcoksp2_bar;
    Wire loadmarlo_bar, loadmarhi_bar, loadmdrlo_bar, loadmdrhi_bar, loadmdrlo2_bar, loadmdrhi2_bar, loadalo_bar, loadahi_bar;
    Wire ldksp_bar, enksp_bar, cntksp_bar, cntkspdir;
    Wire ldusp_bar, enusp_bar, cntusp_bar, cntuspdir;
    
    LS569 *pc3, *pc2, *pc1, *pc0;
    LS374 *ppc0, *ppc1;
    LS569 *mar3, *mar2, *mar1, *mar0;
    LS569 *sp3, *sp2, *sp1, *sp0;
    LS569 *ksp3, *ksp2, *ksp1, *ksp0;   
    LS08 *marload, *a_mdr_load;
    LS157 *spsel0, *spsel1;
    LS32 *load_inhibit;
    LS374 *dp1, *dp0, *a1, *a0, *x1, *x0, *y1, *y0;
    LS374 *mdr_l_lo, *mdr_l_hi, *mdr_r_lo, *mdr_r_hi;

    Device *mdrbuflh, *mdrbufll, *mdrbufrh, *mdrbufrl;
    
    Probe *p1, *p2, *p3;

public:
    Registers(std::string label, Wire& gnd, Wire& vcc, Wire& clk0, Wire& clk1, Wire& rst_bar,
        Wire& abus0, Wire& abus1, Wire& abus2, Wire& abus3, Wire& abus4, Wire& abus5, Wire& abus6, Wire& abus7, Wire& abus8, Wire& abus9, Wire& abus10, Wire& abus11, Wire& abus12, Wire& abus13, Wire& abus14, Wire& abus15,
        Wire& alubus0, Wire& alubus1, Wire& alubus2, Wire& alubus3, Wire& alubus4, Wire& alubus5, Wire& alubus6, Wire& alubus7, Wire& alubus8, Wire& alubus9, Wire& alubus10, Wire& alubus11, Wire& alubus12, Wire& alubus13, Wire& alubus14, Wire& alubus15,
        Wire& lbus0, Wire& lbus1, Wire& lbus2, Wire& lbus3, Wire& lbus4, Wire& lbus5, Wire& lbus6, Wire& lbus7, Wire& lbus8, Wire& lbus9, Wire& lbus10, Wire& lbus11, Wire& lbus12, Wire& lbus13, Wire& lbus14, Wire& lbus15,
        Wire& rbus0, Wire& rbus1, Wire& rbus2, Wire& rbus3, Wire& rbus4, Wire& rbus5, Wire& rbus6, Wire& rbus7, Wire& rbus8, Wire& rbus9, Wire& rbus10, Wire& rbus11, Wire& rbus12, Wire& rbus13, Wire& rbus14, Wire& rbus15,           
        Wire& enmdrl_bar, Wire& ena_bar, Wire& enx_bar, Wire& eny_bar,
        Wire& enmdrr_bar, Wire& enmsw_bar, Wire& enabus_bar, Wire& enppc_bar,
        Wire& enmar_bar, Wire& ensp_bar, Wire& endp_bar, Wire& enpc_bar,
        Wire& mdr_load_inhibit,
        Wire& ldmdrlo_bar, Wire& ldmdrhi_bar, Wire& ldmdr_bar, Wire& ldalo_bar, Wire& ldahi_bar, Wire& lda_bar, Wire& ldx_bar, Wire& ldy_bar, 
        Wire& ldmem_bar, Wire& ldmarlo_bar, Wire& ldmarhi_bar, Wire& ldmar_bar, Wire& ldsp_bar, Wire& lddp_bar, Wire& ldpc_bar, Wire& ldmsw_bar,
        Wire& ldppc_bar,
        Wire& incpc_bar, Wire& incmar_bar, Wire& cntsp_bar, Wire& cntspdir,
        Wire& flag_supervisor
    );
    virtual ~Registers();
    void go(long t);
    void debugInfo(long t);
};

}
