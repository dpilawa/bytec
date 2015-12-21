/* 
 * 
 *    Registers.cpp - this file is part of CPU Simulator
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
#include "Registers.h"

using namespace simulation;
using namespace std;

Registers::Registers(std::string label, Wire& gnd, Wire& vcc, Wire& clk0, Wire& clk1, Wire& rst_bar,
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
    ) : Device(label)
{
    nc.NC();

    // PC - program counter

    pc3 = new LS569("PC3", clk0, ldpc_bar, vcc, rst_bar,
        enpc_bar, incpc_bar, rcopc2_bar, vcc,
        alubus12, alubus13, alubus14, alubus15,
        abus12, abus13, abus14, abus15,
        nc, nc);

    pc2 = new LS569("PC2", clk0, ldpc_bar, vcc, rst_bar,
        enpc_bar, incpc_bar, rcopc1_bar, vcc,
        alubus8, alubus9, alubus10, alubus11,
        abus8, abus9, abus10, abus11,
        rcopc2_bar, nc);

    pc1 = new LS569("PC1", clk0, ldpc_bar, vcc, rst_bar,
        enpc_bar, incpc_bar, rcopc0_bar, vcc,
        alubus4, alubus5, alubus6, alubus7,
        abus4, abus5, abus6, abus7,
        rcopc1_bar, nc);

    pc0 = new LS569("PC0", clk0, ldpc_bar, vcc, rst_bar,
        enpc_bar, incpc_bar, gnd, vcc,
        alubus0, alubus1, alubus2, alubus3,
        abus0, abus1, abus2, abus3,
        rcopc0_bar, nc);

    // PPC - previous program counter

    ppc0 = new LS374("PPC0", ldppc_bar, enppc_bar,
        abus0, abus1, abus2, abus3, abus4, abus5, abus6, abus7,
        rbus0, rbus1, rbus2, rbus3, rbus4, rbus5, rbus6, rbus7);

    ppc1 = new LS374("PPC1", ldppc_bar, enppc_bar,
        abus8, abus9, abus10, abus11, abus12, abus13, abus14, abus15,
        rbus8, rbus9, rbus10, rbus11, rbus12, rbus13, rbus14, rbus15);

    // MAR - memory address register

    marload = new LS08("marload", ldmar_bar, ldmarlo_bar, loadmarlo_bar, ldmar_bar, ldmarhi_bar, loadmarhi_bar, nc, nc, nc, nc, nc, nc);

    mar3 = new LS569("MAR3", clk0, loadmarhi_bar, vcc, vcc,
        enmar_bar, incmar_bar, rcomar2_bar, vcc,
        alubus12, alubus13, alubus14, alubus15,
        abus12, abus13, abus14, abus15,
        nc, nc);

    mar2 = new LS569("MAR2", clk0, loadmarhi_bar, vcc, vcc,
        enmar_bar, incmar_bar, rcomar1_bar, vcc,
        alubus8, alubus9, alubus10, alubus11,
        abus8, abus9, abus10, abus11,
        rcomar2_bar, nc);

    mar1 = new LS569("MAR1", clk0, loadmarlo_bar, vcc, vcc,
        enmar_bar, incmar_bar, rcomar0_bar, vcc,
        alubus4, alubus5, alubus6, alubus7,
        abus4, abus5, abus6, abus7,
        rcomar1_bar, nc);

    mar0 = new LS569("MAR0", clk0, loadmarlo_bar, vcc, vcc,
        enmar_bar, incmar_bar, gnd, vcc,
        alubus0, alubus1, alubus2, alubus3,
        abus0, abus1, abus2, abus3,
        rcomar0_bar, nc);

    // SP - stack pointer

    spsel0 = new LS157("spsel0", gnd, flag_supervisor,
        vcc, vcc, vcc, vcc, ldsp_bar, ensp_bar, cntsp_bar, cntspdir,
        ldusp_bar, enusp_bar, cntusp_bar, cntuspdir);

    sp3 = new LS569("SP3", clk0, ldusp_bar, vcc, vcc,
        enusp_bar, cntusp_bar, rcousp2_bar, cntuspdir,
        alubus12, alubus13, alubus14, alubus15,
        abus12, abus13, abus14, abus15,
        nc, nc);

    sp2 = new LS569("SP2", clk0, ldusp_bar, vcc, vcc,
        enusp_bar, cntusp_bar, rcousp1_bar, cntuspdir,
        alubus8, alubus9, alubus10, alubus11,
        abus8, abus9, abus10, abus11,
        rcousp2_bar, nc);

    sp1 = new LS569("SP1", clk0, ldusp_bar, vcc, vcc,
        enusp_bar, cntusp_bar, rcousp0_bar, cntuspdir,
        alubus4, alubus5, alubus6, alubus7,
        abus4, abus5, abus6, abus7,
        rcousp1_bar, nc);

    sp0 = new LS569("SP0", clk0, ldusp_bar, vcc, vcc,
        enusp_bar, cntusp_bar, gnd, cntuspdir,
        alubus0, alubus1, alubus2, alubus3,
        abus0, abus1, abus2, abus3,
        rcousp0_bar, nc);

    spsel1 = new LS157("spsel1", gnd, flag_supervisor,
        ldsp_bar, ensp_bar, cntsp_bar, cntspdir, vcc, vcc, vcc, vcc,
        ldksp_bar, enksp_bar, cntksp_bar, cntkspdir);

    ksp3 = new LS569("KSP3", clk0, ldksp_bar, vcc, vcc,
        enksp_bar, cntksp_bar, rcoksp2_bar, cntkspdir,
        alubus12, alubus13, alubus14, alubus15,
        abus12, abus13, abus14, abus15,
        nc, nc);

    ksp2 = new LS569("KSP2", clk0, ldksp_bar, vcc, vcc,
        enksp_bar, cntksp_bar, rcoksp1_bar, cntkspdir,
        alubus8, alubus9, alubus10, alubus11,
        abus8, abus9, abus10, abus11,
        rcoksp2_bar, nc);

    ksp1 = new LS569("KSP1", clk0, ldksp_bar, vcc, vcc,
        enksp_bar, cntksp_bar, rcoksp0_bar, cntkspdir,
        alubus4, alubus5, alubus6, alubus7,
        abus4, abus5, abus6, abus7,
        rcoksp1_bar, nc);

    ksp0 = new LS569("KSP0", clk0, ldksp_bar, vcc, vcc,
        enksp_bar, cntksp_bar, gnd, cntkspdir,
        alubus0, alubus1, alubus2, alubus3,
        abus0, abus1, abus2, abus3,
        rcoksp0_bar, nc);

    // DP - data pointer

    dp1 = new LS374("DP1", lddp_bar, endp_bar,
        alubus8, alubus9, alubus10, alubus11, alubus12, alubus13, alubus14, alubus15,
        abus8, abus9, abus10, abus11, abus12, abus13, abus14, abus15);
    dp0 = new LS374("DP0", lddp_bar, endp_bar,
        alubus0, alubus1, alubus2, alubus3, alubus4, alubus5, alubus6, alubus7,
        abus0, abus1, abus2, abus3, abus4, abus5, abus6, abus7);

    // MDR

    a_mdr_load = new LS08("a_mdr_load", lda_bar, ldalo_bar, loadalo_bar, lda_bar, ldahi_bar, loadahi_bar,
                                        ldmdr_bar, ldmdrlo_bar, loadmdrlo_bar, ldmdr_bar, ldmdrhi_bar, loadmdrhi_bar);

    load_inhibit = new LS32("load_inhibit", loadmdrhi_bar, mdr_load_inhibit, loadmdrhi2_bar, loadmdrlo_bar, mdr_load_inhibit, loadmdrlo2_bar,
                            nc, nc, nc, nc, nc, nc);

    mdr_l_lo = new LS374("MDRLLO", loadmdrlo2_bar, enmdrl_bar,
        alubus0, alubus1, alubus2, alubus3, alubus4, alubus5, alubus6, alubus7,
        lbus0, lbus1, lbus2, lbus3, lbus4, lbus5, lbus6, lbus7);
    mdr_r_lo = new LS374("MDRRLO", loadmdrlo2_bar, enmdrr_bar,
        alubus0, alubus1, alubus2, alubus3, alubus4, alubus5, alubus6, alubus7,
        rbus0, rbus1, rbus2, rbus3, rbus4, rbus5, rbus6, rbus7);
    mdr_l_hi = new LS374("MDRLHI", loadmdrhi2_bar, enmdrl_bar,
        alubus8, alubus9, alubus10, alubus11, alubus12, alubus13, alubus14, alubus15,
        lbus8, lbus9, lbus10, lbus11, lbus12, lbus13, lbus14, lbus15);
    mdr_r_hi = new LS374("MDRRHI", loadmdrhi2_bar, enmdrr_bar,
        alubus8, alubus9, alubus10, alubus11, alubus12, alubus13, alubus14, alubus15,
        rbus8, rbus9, rbus10, rbus11, rbus12, rbus13, rbus14, rbus15);

    // A

    a1 = new LS374("A1", loadahi_bar, ena_bar,
        alubus8, alubus9, alubus10, alubus11, alubus12, alubus13, alubus14, alubus15,
        lbus8, lbus9, lbus10, lbus11, lbus12, lbus13, lbus14, lbus15);
    a0 = new LS374("A0", loadalo_bar, ena_bar,
        alubus0, alubus1, alubus2, alubus3, alubus4, alubus5, alubus6, alubus7,
        lbus0, lbus1, lbus2, lbus3, lbus4, lbus5, lbus6, lbus7);

    // X

    x1 = new LS374("X1", ldx_bar, enx_bar,
        alubus8, alubus9, alubus10, alubus11, alubus12, alubus13, alubus14, alubus15,
        lbus8, lbus9, lbus10, lbus11, lbus12, lbus13, lbus14, lbus15);
    x0 = new LS374("X0", ldx_bar, enx_bar,
        alubus0, alubus1, alubus2, alubus3, alubus4, alubus5, alubus6, alubus7,
        lbus0, lbus1, lbus2, lbus3, lbus4, lbus5, lbus6, lbus7);

    // Y

    y1 = new LS374("Y1", ldy_bar, eny_bar,
        alubus8, alubus9, alubus10, alubus11, alubus12, alubus13, alubus14, alubus15,
        lbus8, lbus9, lbus10, lbus11, lbus12, lbus13, lbus14, lbus15);
    y0 = new LS374("Y0", ldy_bar, eny_bar,
        alubus0, alubus1, alubus2, alubus3, alubus4, alubus5, alubus6, alubus7,
        lbus0, lbus1, lbus2, lbus3, lbus4, lbus5, lbus6, lbus7);

    // probes

    //p1 = new Probe("loadmdrhi2_", loadmdrhi2_bar);
    //p2 = new Probe("loadmdrlo2_", loadmdrlo2_bar);
    //p3 = new Probe("endp_", endp_bar);

}

Registers::~Registers()
{
    delete pc3; delete pc2; delete pc1; delete pc0;
    delete ppc0; delete ppc1;

    delete mar3; delete mar2; delete mar1; delete mar0;
    delete marload;

    delete sp3; delete sp2; delete sp1; delete sp0;
    delete ksp3; delete ksp2; delete ksp1; delete ksp0;
    delete spsel0; delete spsel1;

    delete dp1; delete dp0;

    delete mdr_r_lo; delete mdr_l_lo; delete mdr_r_hi; delete mdr_l_hi;
    delete a_mdr_load;
    delete load_inhibit;

    delete a1; delete a0;
    delete x1; delete x0;
    delete y1; delete y0;

    //delete p1; delete p2; delete p3;
}

void Registers::go(long t)
{
    begin(t);
    end();
}

void Registers::debugInfo(long t)
{
    cout<<endl;

    // MAR
    cout<<"    MAR: 0x";
    mar3->debugInfo();
    mar2->debugInfo();
    mar1->debugInfo();
    mar0->debugInfo();

    // PC
    cout<<"     PC: 0x";
    pc3->debugInfo();
    pc2->debugInfo();
    pc1->debugInfo();
    pc0->debugInfo();

    // PPC
    cout<<"    PPC: 0x";
    ppc1->debugInfo();
    ppc0->debugInfo();

    // SP
    cout<<"     SP: 0x";
    sp3->debugInfo();
    sp2->debugInfo();
    sp1->debugInfo();
    sp0->debugInfo();

    // KSP
    cout<<"    KSP: 0x";
    ksp3->debugInfo();
    ksp2->debugInfo();
    ksp1->debugInfo();
    ksp0->debugInfo();

    cout<<endl;

    // DP
    cout<<"     DP: 0x";
    dp1->debugInfo();
    dp0->debugInfo();

    // MDR
    cout<<"    MDR: 0x";
    mdr_l_hi->debugInfo();
    mdr_l_lo->debugInfo();

    // A
    cout<<"      A: 0x";
    a1->debugInfo();
    a0->debugInfo();

    // X
    cout<<"      X: 0x";
    x1->debugInfo();
    x0->debugInfo();

    // Y
    cout<<"      Y: 0x";
    y1->debugInfo();
    y0->debugInfo();

    cout<<endl;

    //p1->debugInfo(t);
    //p2->debugInfo(t);
    //p3->debugInfo(t);

}
