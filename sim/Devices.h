/* 
 * 
 *    Devices.h - this file is part of CPU Simulator
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

// Power Source
//
//////////////////////////////////////////////////////////////////////

class PowerSource : public Device
{
public:
    PowerSource(std::string label, Wire& gnd, Wire& vcc);
    void go(long t);
};

// Oscillator
//
//////////////////////////////////////////////////////////////////////
class Oscillator : public Device
{
    float freq_mhz;
    Logic l;
    long t_osc; // time of next tick
    void go(long t);
public:
    Oscillator(std::string label, float mhz, Wire& out);
    long go() { go(t_osc); return t_osc;};
};

// IRQ generator
//
//////////////////////////////////////////////////////////////////////
class IRQ : public Device
{
    void go(long t) {} ;
public:
    IRQ(std::string label, Wire& irq0, Wire& irq1, Wire& irq2, Wire& irq3, Wire& irq4, Wire& irq5, Wire& irq6, Wire& irq7);
    void go(int irq, long time, int s_len);
};

// Reset
//
//////////////////////////////////////////////////////////////////////
class Reset : public Device
{
    long t_rst;
public:
    Reset(std::string label, long len, Wire& rst_bar);
    void go(long t);
};

// 74LS74 Dual Positive Edge Triggered D Flip-Flop with Preset and Clear
//
//////////////////////////////////////////////////////////////////////

class LS74 : public SynchronousDevice 
{
    Logic lq1, lq2, lq1_bar, lq2_bar;   
public:
    LS74(std::string label, Wire& clk1, Wire& clk2, Wire& pr1_bar, Wire& pr2_bar, Wire& clr1_bar, Wire& clr2_bar, 
        Wire& d1, Wire& d2, Wire& q1, Wire& q2, Wire& q1_bar, Wire& q2_bar);
    void go(long t);
    void debugInfo() {};
};


// 74LS163A Synchronous 4-bit Binary Counter with Synchronous Clear
//
//////////////////////////////////////////////////////////////////////

class LS163A : public SynchronousDevice
{
    char reg;
public:
    LS163A(std::string label, Wire& clk, Wire& clr_bar, Wire& load_bar, Wire& p, Wire& t,
        Wire& a0, Wire& a1, Wire& a2, Wire& a3, Wire& q0, Wire& q1, Wire& q2, Wire& q3, Wire& rco);
    void go(long t);
    void debugInfo() { std::cout<<devLabel<<": "<<(int)reg<<std::endl; }
};


// 74LS169A Synchronous 4-Bit Up/Down Binary Counter
//
//////////////////////////////////////////////////////////////////////

class LS169A : public SynchronousDevice
{
    char reg;
public:
    LS169A(std::string label, Wire& clk, Wire& load_bar, Wire& ud, Wire& p_bar, Wire& t_bar,
        Wire& a0, Wire& a1, Wire& a2, Wire& a3, Wire& q0, Wire& q1, Wire& q2, Wire& q3, Wire& rco_bar);
    void go(long t);
    void debugInfo() { std::cout<<devLabel<<": "<<(int)reg<<std::endl; }
};

// 74LS181 4-bit ALU
//
//////////////////////////////////////////////////////////////////////

class LS181_emodule : public AsynchronousDevice
{
public:
    LS181_emodule(std::string label,
        Wire& a0, Wire& a1, Wire& a2, Wire& a3,
        Wire& b0, Wire& b1, Wire& b2, Wire& b3,
        Wire& s0, Wire& s1, Wire& s2, Wire& s3,
        Wire& e0, Wire& e1, Wire& e2, Wire& e3);
    void go(long t);
    void debugInfo(long t) {};
};

class LS181_dmodule : public AsynchronousDevice
{
public:
    LS181_dmodule(std::string label,
        Wire& a0, Wire& a1, Wire& a2, Wire& a3,
        Wire& b0, Wire& b1, Wire& b2, Wire& b3,
        Wire& s0, Wire& s1, Wire& s2, Wire& s3,
        Wire& d0, Wire& d1, Wire& d2, Wire& d3);
    void go(long t);
    void debugInfo(long t) {};
};

class LS181_clamodule : public AsynchronousDevice
{
public:
    LS181_clamodule(std::string label,
        Wire& g0_bar, Wire& g1_bar, Wire& g2_bar, Wire& g3_bar,
        Wire& p0_bar, Wire& p1_bar, Wire& p2_bar, Wire& p3_bar,
        Wire& cn_bar,
        Wire& c0, Wire& c1, Wire& c2, Wire& c3,
        Wire& p, Wire& g, Wire& cn4_bar);
    void go(long t);
    void debugInfo(long t) {};
};

class LS181_summodule : public AsynchronousDevice
{
public:
    LS181_summodule(std::string label,
        Wire& e0, Wire& e1, Wire& e2, Wire& e3,
        Wire& d0, Wire& d1, Wire& d2, Wire& d3,
        Wire& c0, Wire& c1, Wire& c2, Wire& c3,
        Wire& m,
        Wire& f0, Wire& f1, Wire& f2, Wire& f3,
        Wire& aeqb);
    void go(long t);
    void debugInfo(long t) {};
};

class LS181 : public AsynchronousDevice
{
    LS181_emodule* Emodule;
    LS181_dmodule* Dmodule;
    LS181_clamodule* CLAmodule;
    LS181_summodule* SUMmodule;
    // Dmodule, CLAmodule, SUMmodule;
    Wire e0, d0, c0, b0_bar;
    Wire e1, d1, c1, b1_bar;
    Wire e2, d2, c2, b2_bar;
    Wire e3, d3, c3, b3_bar;
public:
    LS181(std::string label, 
        Wire& s0, Wire& s1, Wire& s2, Wire& s3,
        Wire& a0, Wire& a1, Wire& a2, Wire& a3,
        Wire& b0, Wire& b1, Wire& b2, Wire& b3,
        Wire& cn_bar, Wire& m,
        Wire& f0, Wire& f1, Wire& f2, Wire& f3,
        Wire& p, Wire& g, Wire& cn4_bar, Wire& aeqb);
    ~LS181();
    void go(long t);
    void debugInfo(long t) {};
};

// 74LS182 Carry Lookahead Generator
//
//////////////////////////////////////////////////////////////////////

class LS182 : public AsynchronousDevice 
{
public:
    LS182(std::string label, Wire& cn, Wire& p0_bar, Wire& g0_bar, Wire& p1_bar, Wire& g1_bar, Wire& p2_bar, Wire& g2_bar, Wire& p3_bar, Wire& g3_bar,
        Wire& cnx, Wire& cny, Wire& cnz, Wire& p_bar, Wire& g_bar);
    void go(long t);
    void debugInfo(long t) {};
};

// 74LS173 Quad D Flip-Flop with Three-state Outputs
//
//////////////////////////////////////////////////////////////////////

class LS173 : public SynchronousDevice 
{
    Logic l1, l2, l3, l4;
public:
    LS173(std::string label, Wire& clk, Wire& clr, Wire& g1_bar, Wire& g2_bar, Wire& m, Wire& n, 
        Wire& d1, Wire& d2, Wire& d3, Wire& d4, Wire& q1, Wire& q2, Wire& q3, Wire& q4);
    void go(long t);
    void debugInfo() { std::cout<<std::hex<<std::setw(1)<<(int)((char)l1 * 1 + (char)l2 * 2 + (char)l3 * 4 + (char)l4 * 8)<<std::dec; };
};

// 74LS175 Quad D Edge-Triggered Flip-Flop with Complementary Outputs and Asynchronous Clear
//
//////////////////////////////////////////////////////////////////////

class LS175 : public SynchronousDevice 
{
    Logic l1, l2, l3, l4;
public:
    LS175(std::string label, Wire& clk, Wire& mr_bar, Wire& d1, Wire& d2, Wire& d3, Wire& d4, 
        Wire& q1, Wire& q2, Wire& q3, Wire& q4, Wire& q1_bar, Wire& q2_bar, Wire& q3_bar, Wire& q4_bar);
    void go(long t);
    void debugInfo() { std::cout<<std::hex<<std::setw(1)<<(int)((char)l1 * 1 + (char)l2 * 2 + (char)l3 * 4 + (char)l4 * 8)<<std::dec; };
};

// 74LS273 8-bit Register with Reset 
//
//////////////////////////////////////////////////////////////////////

class LS273 : public SynchronousDevice 
{
    Logic l1, l2, l3, l4, l5, l6, l7, l8;
public:
    LS273(std::string label, Wire& clk, Wire& clr_bar, 
        Wire& d1, Wire& d2, Wire& d3, Wire& d4, Wire& d5, Wire& d6, Wire& d7, Wire& d8, 
        Wire& q1, Wire& q2, Wire& q3, Wire& q4, Wire& q5, Wire& q6, Wire& q7, Wire& q8);
    void go(long t);
    void debugInfo() {};
};
 
// 74LS348 8-to-3 line Priority Encoder with three-state outputs
//
//////////////////////////////////////////////////////////////////////

class LS348 : public AsynchronousDevice 
{
public:
    LS348(std::string label, Wire& ei_bar, 
        Wire& i0_bar, Wire& i1_bar, Wire& i2_bar, Wire& i3_bar, Wire& i4_bar, Wire& i5_bar, Wire& i6_bar, Wire& i7_bar,
        Wire& a0_bar, Wire& a1_bar, Wire& a2_bar, Wire& eo_bar, Wire& gs_bar);
    void go(long t);
    void debugInfo(long t) {};
};


// 74LS374 Octal Register with three-state outputs
//
//////////////////////////////////////////////////////////////////////

class LS374 : public SynchronousDevice 
{
    Logic l1, l2, l3, l4, l5, l6, l7, l8;
public:
    LS374(std::string label, Wire& clk, Wire& oe_bar,
        Wire& d1, Wire& d2, Wire& d3, Wire& d4, Wire& d5, Wire& d6, Wire& d7, Wire& d8,
        Wire& q1, Wire& q2, Wire& q3, Wire& q4, Wire& q5, Wire& q6, Wire& q7, Wire& q8);
    void go(long t);
    void debugInfo() { std::cout<<std::hex<<std::setw(2)<<std::setfill('0')<<(int)((char)l1+(char)l2*2+(char)l3*4+(char)l4*8+(char)l5*16+(char)l6*32+(char)l7*64+(char)l8*128)<<std::dec; };
};

// 74LS569 Binary Up/Down Counter with three-state outputs
//
//////////////////////////////////////////////////////////////////////

class LS569 : public SynchronousDevice 
{
    char reg;
public:
    LS569(std::string label, Wire& clk, Wire& load_bar, Wire& aclr_bar, Wire& sclr_bar,
        Wire& oe_bar, Wire& cep_bar, Wire& cet_bar, Wire& ud, 
        Wire& a, Wire& b, Wire& c, Wire& d, 
        Wire& ya, Wire& yb, Wire& yc, Wire& yd,
        Wire& rco_bar, Wire& cco);
    void go(long t);
    void debugInfo() { std::cout<<std::hex<<std::setw(1)<<(int)reg<<std::dec; };
};

// 74LS04 Hex Inverting Gates
//
//////////////////////////////////////////////////////////////////////

class LS04 : public AsynchronousDevice 
{

public:
    LS04(std::string label, 
        Wire& a1, Wire& y1,
        Wire& a2, Wire& y2,
        Wire& a3, Wire& y3,
        Wire& a4, Wire& y4,
        Wire& a5, Wire& y5,
        Wire& a6, Wire& y6);
    void go(long t);
    void debugInfo(long t) {};
};

// 29F020 70ns 256k ROM
//
//////////////////////////////////////////////////////////////////////

class EEPROM_29F020 : public AsynchronousDevice
{
    std::vector<char> mem;
    int addr;
    unsigned char c;
public:
    EEPROM_29F020(std::string label, std::string rom_name, Wire& ce_bar, Wire& oe_bar, Wire& we_bar,
        Wire& a0, Wire& a1, Wire& a2, Wire& a3, 
        Wire& a4, Wire& a5, Wire& a6, Wire& a7, 
        Wire& a8, Wire& a9, Wire& a10, Wire& a11, 
        Wire& a12, Wire& a13, Wire& a14, Wire& a15, 
        Wire& a16, Wire& a17,
        Wire& dq0, Wire& dq1, Wire& dq2, Wire& dq3, Wire& dq4, Wire& dq5, Wire& dq6, Wire& dq7);
    void go(long t);
    void debugInfo(long t) {};
};


// 628512 DIP-32 S-RAM 70ns 8x512k
//
//////////////////////////////////////////////////////////////////////

class SRAM_628512 : public AsynchronousDevice
{
    std::vector<char> mem;
public:
    SRAM_628512(std::string label, Wire& cs_bar, Wire& oe_bar, Wire& we_bar,
        Wire& a0, Wire& a1, Wire& a2, Wire& a3, 
        Wire& a4, Wire& a5, Wire& a6, Wire& a7, 
        Wire& a8, Wire& a9, Wire& a10, Wire& a11, 
        Wire& a12, Wire& a13, Wire& a14, Wire& a15, 
        Wire& a16, Wire& a17, Wire& a18,
        Wire& io0, Wire& io1, Wire& io2, Wire& io3, Wire& io4, Wire& io5, Wire& io6, Wire& io7);
    ~SRAM_628512();
    void go(long t);
    void debugInfo(long t) {};
};

// 74LS148 8-Line to 3-Line Priority Encoder
//
//////////////////////////////////////////////////////////////////////

class LS148 : public AsynchronousDevice 
{
public:
    LS148(std::string label, Wire& ei_bar, 
        Wire& i0_bar, Wire& i1_bar, Wire& i2_bar, Wire& i3_bar, Wire& i4_bar, Wire& i5_bar, Wire& i6_bar, Wire& i7_bar,
        Wire& a0_bar, Wire& a1_bar, Wire& a2_bar, Wire& eo_bar, Wire& gs_bar);
    void go(long t);
    void debugInfo(long t) {};
};

// 3 to 8-line Decoder/Demultiplexer
//
//////////////////////////////////////////////////////////////////////

class LS138 : public AsynchronousDevice 
{
public:
    LS138(std::string label, Wire& g1, Wire& g2a_bar, Wire& g2b_bar, Wire& a, Wire& b, Wire &c,
        Wire& y0_bar, Wire& y1_bar, Wire& y2_bar, Wire& y3_bar, Wire& y4_bar, Wire& y5_bar, Wire& y6_bar, Wire& y7_bar);
    void go(long t);
    void debugInfo(long t) {};
};

// 74LS139 Dual 1-of-4 Decoder/Demultiplexer
//
//////////////////////////////////////////////////////////////////////

class LS139 : public AsynchronousDevice 
{
public:
    LS139(std::string label, Wire& ea_bar, Wire& eb_bar,
        Wire& a0a, Wire& a1a, Wire& o0a_bar, Wire& o1a_bar, Wire& o2a_bar, Wire& o3a_bar,
        Wire& a0b, Wire& a1b, Wire& o0b_bar, Wire& o1b_bar, Wire& o2b_bar, Wire& o3b_bar);
    void go(long t);
    void debugInfo(long t) {};
};

// 74LS154 1-of-16 Decoder/Demultiplexer
//
//////////////////////////////////////////////////////////////////////

class LS154 : public AsynchronousDevice 
{
public:
    LS154(std::string label, Wire& g1_bar, Wire& g2_bar,
        Wire& a, Wire& b, Wire& c, Wire& d, 
        Wire& y0_bar, Wire& y1_bar, Wire& y2_bar, Wire& y3_bar, Wire& y4_bar, Wire& y5_bar, Wire& y6_bar, Wire& y7_bar, 
        Wire& y8_bar, Wire& y9_bar, Wire& y10_bar, Wire& y11_bar, Wire& y12_bar, Wire& y13_bar, Wire& y14_bar, Wire& y15_bar);
    void go(long t);
    void debugInfo(long t) {};
};

// 74LS157 Quad 2-line to 1-line Data Selector/Multiplexer
//
//////////////////////////////////////////////////////////////////////

class LS157 : public AsynchronousDevice 
{
public:
    LS157(std::string label, Wire& g_bar, Wire& a_bar_b,
        Wire& a1, Wire& a2, Wire& a3, Wire& a4, Wire& b1, Wire& b2, Wire& b3, Wire& b4,
        Wire& y1, Wire& y2, Wire& y3, Wire& y4);
    void go(long t);
    void debugInfo(long t) {};
};

// 74LS00 Quad 2-input NAND Gate
//
//////////////////////////////////////////////////////////////////////

class LS00 : public AsynchronousDevice 
{
public:
    LS00(std::string label, 
        Wire& a1, Wire& b1, Wire& y1_bar, Wire& a2, Wire& b2, Wire& y2_bar, 
        Wire& a3, Wire& b3, Wire& y3_bar, Wire& a4, Wire& b4, Wire& y4_bar);
    void go(long t);
    void debugInfo(long t) {};
};

// 74LS02 Quad 2-input NOR Gate
//
//////////////////////////////////////////////////////////////////////

class LS02 : public AsynchronousDevice 
{
public:
    LS02(std::string label, 
        Wire& a1, Wire& b1, Wire& y1_bar, Wire& a2, Wire& b2, Wire& y2_bar, 
        Wire& a3, Wire& b3, Wire& y3_bar, Wire& a4, Wire& b4, Wire& y4_bar);
    void go(long t);
    void debugInfo(long t) {};
};

// 74LS08 Quad 2-input AND Gate
//
//////////////////////////////////////////////////////////////////////

class LS08 : public AsynchronousDevice 
{
public:
    LS08(std::string label, 
        Wire& a1, Wire& b1, Wire& y1, Wire& a2, Wire& b2, Wire& y2, 
        Wire& a3, Wire& b3, Wire& y3, Wire& a4, Wire& b4, Wire& y4);
    void go(long t);
    void debugInfo(long t) {};
};

// 74LS20 Dual 4-Input NAND Gate
//
//////////////////////////////////////////////////////////////////////

class LS20 : public AsynchronousDevice 
{
public:
    LS20(std::string label, 
           Wire& a1, Wire& b1, Wire& c1, Wire& d1, Wire& y1, Wire& a2, Wire& b2, Wire& c2, Wire& d2, Wire& y2);
    void go(long t);
    void debugInfo(long t) {};         
};

// 74LS21 Dual 4-Input AND Gate
//
//////////////////////////////////////////////////////////////////////

class LS21 : public AsynchronousDevice 
{
public:
    LS21(std::string label, 
           Wire& a1, Wire& b1, Wire& c1, Wire& d1, Wire& y1, Wire& a2, Wire& b2, Wire& c2, Wire& d2, Wire& y2);
    void go(long t);
    void debugInfo(long t) {};         
};

// 74LS30 8-Input NAND Gate
//
//////////////////////////////////////////////////////////////////////

class LS30 : public AsynchronousDevice 
{
public:
    LS30(std::string label, 
        Wire& a, Wire& b, Wire& c, Wire& d, Wire& e, Wire& f, Wire& g, Wire& h, Wire& y);
    void go(long t);
    void debugInfo(long t) {};
};

// 74LS32 Quad 2-input OR Gate
//
//////////////////////////////////////////////////////////////////////

class LS32 : public AsynchronousDevice 
{
public:
    LS32(std::string label, 
        Wire& a1, Wire& b1, Wire& y1, Wire& a2, Wire& b2, Wire& y2, 
        Wire& a3, Wire& b3, Wire& y3, Wire& a4, Wire& b4, Wire& y4);
    void go(long t);
    void debugInfo(long t) {};
};

// 74LS244 Octal Buffer/Driver with 3-State Outputs
//
//////////////////////////////////////////////////////////////////////

class LS244 : public AsynchronousDevice 
{
public:
    LS244(std::string label, Wire& g1_bar, Wire& g2_bar,
        Wire& a1, Wire& a2, Wire& a3, Wire& a4, Wire& a5, Wire& a6, Wire& a7, Wire& a8, 
        Wire& y1, Wire& y2, Wire& y3, Wire& y4, Wire& y5, Wire& y6, Wire& y7, Wire& y8);
    void go(long t);
    void debugInfo(long t) {};
};

// 74LS245 Octal Bus Transciever with 3-State Outputs
//
//////////////////////////////////////////////////////////////////////
class LS245 : public AsynchronousDevice 
{
public:
    LS245(std::string label, Wire& g_bar, Wire& dir,
        Wire& a1, Wire& a2, Wire& a3, Wire& a4, Wire& a5, Wire& a6, Wire& a7, Wire& a8, 
        Wire& b1, Wire& b2, Wire& b3, Wire& b4, Wire& b5, Wire& b6, Wire& b7, Wire& b8);
    void go(long t);
    void debugInfo(long t) {};      
};

// 74LS151 8-Line to 1-Line Data Selector/Multiplexer
//
//////////////////////////////////////////////////////////////////////

class LS151 : public AsynchronousDevice 
{
public:
    LS151(std::string label, Wire& e_bar, Wire& s0, Wire& s1, Wire& s2,
        Wire& i1, Wire& i2, Wire& i3, Wire& i4, Wire& i5, Wire& i6, Wire& i7, Wire& i8, 
        Wire& z, Wire& z_bar);
    void go(long t);
    void debugInfo(long t) {};
};

// 74LS153 Dual 4-Line to 1-Line Data Selector/Multiplexer
//
//////////////////////////////////////////////////////////////////////

class LS153 : public AsynchronousDevice 
{
public:
    LS153(std::string label, Wire& e_bar, Wire& s0, Wire& s1,
        Wire& i1a, Wire& i2a, Wire& i3a, Wire& i4a, Wire& i1b, Wire& i2b, Wire& i3b, Wire& i4b, 
        Wire& za, Wire& zb);
    void go(long t);
    void debugInfo(long t) {};
};


};
