/* 
 * 
 *    Devices.cpp - this file is part of CPU Simulator
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

using namespace simulation;
using namespace std;

// Power Source
//
//////////////////////////////////////////////////////////////////////

PowerSource::PowerSource(std::string label, Wire& gnd, Wire& vcc) : Device(label)
{
    pd=0;
    Output("gnd", gnd);
    Output("vcc", vcc);
}

void PowerSource::go(long t)
{
    begin(t);
    cout<<"Power On"<<endl<<endl;
    assert_signal("gnd", Logic(LO));
    assert_signal("vcc", Logic(HI));
    end();
}

// Oscillator
//
//////////////////////////////////////////////////////////////////////

Oscillator::Oscillator(std::string label, float mhz, Wire& out) : Device(label)
{
    pd = 0;
    freq_mhz = mhz;
    t_osc = 0;
    l = Logic(LO);

    Output("out", out);
}

void Oscillator::go(long t)
{
    begin(t);
    t_osc = t_osc + long((1 / freq_mhz) * 1000 / 2);
    l = !l;
    assert_signal("out", l);
    end();
}

// IRQ generator
//
//////////////////////////////////////////////////////////////////////

IRQ::IRQ(std::string label, Wire& irq0, Wire& irq1, Wire& irq2, Wire& irq3, Wire& irq4, Wire& irq5, Wire& irq6, Wire& irq7) : Device(label)
{
    pd = 0;
    Output("irq0", irq0); Output("irq1", irq1); Output("irq2", irq2); Output("irq3", irq3);
    Output("irq4", irq4); Output("irq5", irq5); Output("irq6", irq6); Output("irq7", irq7);
};

void IRQ::go(int irq, long time, int s_len)
{
    std::stringstream s;
    s << irq;

    begin(time);
    assert_signal("irq"+s.str(), Logic(LO));
    end();

    begin(time + s_len);
    assert_signal("irq"+s.str(), Logic(HI));
    end();
}

// Reset
//
//////////////////////////////////////////////////////////////////////

Reset::Reset(std::string label, long len, Wire& rst_bar) : Device(label)
{
    pd = 0;
    t_rst = len;
    Output("rst_bar", rst_bar);
}

void Reset::go(long t)
{
    begin(t);
    assert_signal("rst_bar", Logic(LO));
    end();

    begin(t+t_rst);
    assert_signal("rst_bar", Logic(HI));
    end();
}

// 74LS74 Dual Positive Edge Triggered D Flip-Flop with Preset and Clear
//
//////////////////////////////////////////////////////////////////////

LS74::LS74(std::string label, Wire& clk1, Wire& clk2, Wire& pr1_bar, Wire& pr2_bar, Wire& clr1_bar, Wire& clr2_bar,
           Wire& d1, Wire& d2, Wire& q1, Wire& q2, Wire& q1_bar, Wire& q2_bar) : SynchronousDevice(label)
{
    // worst case propagation delay for 74LS74
    pd = 35;
    lq1 = Logic(LO);
    lq2 = Logic(LO);
    // inputs
    HotInput("clk1", clk1);
    HotInput("clk2", clk2);
    HotInput("pr1_bar", pr1_bar);
    HotInput("pr2_bar", pr2_bar);
    HotInput("clr1_bar", clr1_bar);
    HotInput("clr2_bar", clr2_bar);
    Input("d1", d1);
    Input("d2", d2);
    // outputs
    Output("q1", q1);
    Output("q2", q2);
    Output("q1_bar", q1_bar);
    Output("q2_bar", q2_bar);
};

void LS74::go(long t)
{
    begin(t);

    if (!input("pr1_bar") & input("clr1_bar"))
    {
        lq1 = Logic(HI);
        lq1_bar = Logic(LO);
    }
    else if (input("pr1_bar") & !input("clr1_bar"))
    {
        lq1 = Logic(LO);
        lq1_bar = Logic(HI);
    }
    else if (!input("clr1_bar") & !input("pr1_bar"))
    {
        lq1 = Logic(HI);
        lq1_bar = Logic(HI);
    }
    else
    {
        if (inputRisingEdge("clk1"))
        {
            lq1 = input("d1");
            lq1_bar = !input("d1");
        }
        else
        {
            lq1_bar = !lq1;
        }
    }


    if (!input("pr2_bar") & input("clr2_bar"))
    {
        lq2 = Logic(HI);
        lq2_bar = Logic(LO);
    }
    else if (input("pr2_bar") & !input("clr2_bar"))
    {
        lq2 = Logic(LO);
        lq2_bar = Logic(HI);
    }
    else if (!input("clr2_bar") & !input("pr2_bar"))
    {
        lq2 = Logic(HI);
        lq2_bar = Logic(HI);
    }
    else
    {
        if (inputRisingEdge("clk2"))
        {
            lq2 = input("d2");
            lq2_bar = !input("d2");
        }
        else
        {
            lq2_bar = !lq2;
        }
    }

    assert_signal("q1", lq1);
    assert_signal("q2", lq2);
    assert_signal("q1_bar", lq1_bar);
    assert_signal("q2_bar", lq2_bar);

    end();
}

// 74LS163A Synchronous 4-bit Binary Counter with Synchronous Clear
//
//////////////////////////////////////////////////////////////////////


LS163A::LS163A(std::string label, Wire& clk, Wire& clr_bar, Wire& load_bar, Wire& p, Wire& t,
               Wire& a0, Wire& a1, Wire& a2, Wire& a3, Wire& q0, Wire& q1, Wire& q2, Wire& q3, Wire& rco) : SynchronousDevice(label)
{
    pd = 45; // worst case
    reg = reg & 0x0f;
    HotInput("clk", clk);
    Input("clr_bar", clr_bar);
    Input("load_bar", load_bar);
    Input("p", p);
    HotInput("t", t);
    Input("a0", a0); Input("a1", a1); Input("a2", a2); Input("a3", a3);
    Output("q0", q0); Output("q1", q1); Output("q2", q2); Output("q3", q3);
    Output("rco", rco);
}

void LS163A::go(long t)
{
    begin(t);

    if (inputRisingEdge("clk"))
    {
        if (!input("clr_bar"))
        {
            reg = 0;
        }
        else if (!input("load_bar"))
        {
            reg = ((char)input("a3") << 3) + ((char)input("a2") << 2) + ((char)input("a1") << 1) + (char)input("a0");
        }
        else if (input("p") & input("t"))
        {
            if (reg == 15)
            {
                reg = 0;
            }
            else
            {
                reg = reg + 1;
            }
        }

        assert_signal("q3", reg & 0x08);
        assert_signal("q2", reg & 0x04);
        assert_signal("q1", reg & 0x02);
        assert_signal("q0", reg & 0x01);
    }

    if ((bool)input("t") && reg == 15)
    {
        assert_signal("rco", Logic(HI));
    }
    else
    {
        assert_signal("rco", Logic(LO));
    }

    end();
}

// 74LS169A Synchronous 4-Bit Up/Down Binary Counter
//
//////////////////////////////////////////////////////////////////////


LS169A::LS169A(std::string label, Wire& clk, Wire& load_bar, Wire& ud, Wire& p_bar, Wire& t_bar,
               Wire& a0, Wire& a1, Wire& a2, Wire& a3, Wire& q0, Wire& q1, Wire& q2, Wire& q3, Wire& rco_bar) : SynchronousDevice(label)
{
    pd = 44;
    reg = reg & 0x0f;
    HotInput("clk", clk);
    Input("load_bar", load_bar);
    HotInput("ud", ud);
    Input("p_bar", p_bar);
    HotInput("t_bar", t_bar);
    Input("a0", a0); Input("a1", a1); Input("a2", a2); Input("a3", a3);
    Output("q0", q0); Output("q1", q1); Output("q2", q2); Output("q3", q3);
    Output("rco_bar", rco_bar);
}


void LS169A::go(long t)
{
    begin(t);

    if (inputRisingEdge("clk"))
    {
        if (!input("load_bar"))
        {
            reg = ((char)input("a3") << 3) + ((char)input("a2") << 2) + ((char)input("a1") << 1) + (char)input("a0");
        }
        else if (!input("p_bar") & !input("t_bar") & input("ud"))
        {
            if (reg == 15)
            {
                reg = 0;
            }
            else
            {
                reg = reg + 1;
            }
        }
        else if (!input("p_bar") & !input("t_bar") & !input("ud"))
        {
            if (reg == 0)
            {
                reg = 15;
            }
            else
            {
                reg = reg - 1;
            }
        }
        assert_signal("q3", reg & 0x08);
        assert_signal("q2", reg & 0x04);
        assert_signal("q1", reg & 0x02);
        assert_signal("q0", reg & 0x01);
    }

    if (!(bool)input("t_bar") && (((bool)input("ud") && reg == 15) || (!(bool)input("ud") && reg == 0)))
    {
        assert_signal("rco_bar", Logic(LO));
    }
    else
    {
        assert_signal("rco_bar", Logic(HI));
    }

    end();
}


// 74LS181 4-bit ALU
//
// Based on VERILOG BEHAVIORAL DESCRIPTION OF THE TI 74181 CIRCUIT
// by Mark C. Hansen
//
//////////////////////////////////////////////////////////////////////

LS181::LS181(std::string label,
        Wire& s0, Wire& s1, Wire& s2, Wire& s3,
        Wire& a0, Wire& a1, Wire& a2, Wire& a3,
        Wire& b0, Wire& b1, Wire& b2, Wire& b3,
        Wire& cn_bar, Wire& m,
        Wire& f0, Wire& f1, Wire& f2, Wire& f3,
        Wire& p, Wire& g, Wire& cn4_bar, Wire& aeqb) : AsynchronousDevice(label)
{
    Emodule = new LS181_emodule("emodule", a0, a1, a2, a3, b0, b1, b2, b3, s0, s1, s2, s3, e0, e1, e2, e3);
    Dmodule = new LS181_dmodule("dmodule", a0, a1, a2, a3, b0, b1, b2, b3, s0, s1, s2, s3, d0, d1, d2, d3);
    CLAmodule = new LS181_clamodule("clamodule", e0, e1, e2, e3, d0, d1, d2, d3, cn_bar, c0, c1, c2, c3, p, g, cn4_bar);
    SUMmodule = new LS181_summodule("summodule", e0, e1, e2, e3, d0, d1, d2, d3, c0, c1, c2, c3, m, f0, f1, f2, f3, aeqb);
}

LS181::~LS181()
{
    delete Emodule;
    delete Dmodule;
    delete CLAmodule;
    delete SUMmodule;
}

void LS181::go(long t)
{
    begin(t);
    end();
}

LS181_emodule::LS181_emodule(std::string label,
        Wire& a0, Wire& a1, Wire& a2, Wire& a3,
        Wire& b0, Wire& b1, Wire& b2, Wire& b3,
        Wire& s0, Wire& s1, Wire& s2, Wire& s3,
        Wire& e0, Wire& e1, Wire& e2, Wire& e3) : AsynchronousDevice(label)
{
    Input("s0", s0); Input("s1", s1); Input("s2", s2); Input("s3", s3);
    Input("a0", a0); Input("a1", a1); Input("a2", a2); Input("a3", a3);
    Input("b0", b0); Input("b1", b1); Input("b2", b2); Input("b3", b3);
    Output("e0", e0); Output("e1", e1); Output("e2", e2); Output("e3", e3);
}

void LS181_emodule::go(long t)
{
    begin(t);

 // input [3:0] A, B, S;
 // output [3:0] E;
 // wire [3:0]  ABS3, ABbS2;

 // assign ABS3 = A&B&{4{S[3]}};
 // assign ABbS2 = A&~B&{4{S[2]}};
 // assign E = ~(ABS3|ABbS2);

    Logic abs3_0, abs3_1, abs3_2, abs3_3;
    Logic ab_bars2_0, ab_bars2_1, ab_bars2_2, ab_bars2_3;

    abs3_0 = input("a0") & input("b0") & input("s3");
    abs3_1 = input("a1") & input("b1") & input("s3");
    abs3_2 = input("a2") & input("b2") & input("s3");
    abs3_3 = input("a3") & input("b3") & input("s3");

    ab_bars2_0 = input("a0") & !input("b0") & input("s2");
    ab_bars2_1 = input("a1") & !input("b1") & input("s2");
    ab_bars2_2 = input("a2") & !input("b2") & input("s2");
    ab_bars2_3 = input("a3") & !input("b3") & input("s2");

    assert_signal("e0", !(abs3_0 | ab_bars2_0));
    assert_signal("e1", !(abs3_1 | ab_bars2_1));
    assert_signal("e2", !(abs3_2 | ab_bars2_2));
    assert_signal("e3", !(abs3_3 | ab_bars2_3));

    end();
}


LS181_dmodule::LS181_dmodule(std::string label,
        Wire& a0, Wire& a1, Wire& a2, Wire& a3,
        Wire& b0, Wire& b1, Wire& b2, Wire& b3,
        Wire& s0, Wire& s1, Wire& s2, Wire& s3,
        Wire& d0, Wire& d1, Wire& d2, Wire& d3) : AsynchronousDevice(label)
{
    Input("s0", s0); Input("s1", s1); Input("s2", s2); Input("s3", s3);
    Input("a0", a0); Input("a1", a1); Input("a2", a2); Input("a3", a3);
    Input("b0", b0); Input("b1", b1); Input("b2", b2); Input("b3", b3);
    Output("d0", d0); Output("d1", d1); Output("d2", d2); Output("d3", d3);
}

void LS181_dmodule::go(long t)
{
    begin(t);

 // input [3:0] A, B, S;
 // output [3:0] D;
 // wire [3:0]  BbS1, BS0;

 // assign BbS1 = ~B&{4{S[1]}};
 // assign BS0 = B&{4{S[0]}};
 // assign D = ~(BbS1|BS0|A);

    Logic b_bars1_0, b_bars1_1, b_bars1_2, b_bars1_3;
    Logic bs0_0, bs0_1, bs0_2, bs0_3;

    b_bars1_0 = !input("b0") & input("s1");
    b_bars1_1 = !input("b1") & input("s1");
    b_bars1_2 = !input("b2") & input("s1");
    b_bars1_3 = !input("b3") & input("s1");

    bs0_0 = input("b0") & input("s0");
    bs0_1 = input("b1") & input("s0");
    bs0_2 = input("b2") & input("s0");
    bs0_3 = input("b3") & input("s0");

    assert_signal("d0", !(b_bars1_0 | bs0_0 | input("a0")));
    assert_signal("d1", !(b_bars1_1 | bs0_1 | input("a1")));
    assert_signal("d2", !(b_bars1_2 | bs0_2 | input("a2")));
    assert_signal("d3", !(b_bars1_3 | bs0_3 | input("a3")));

    end();
}

LS181_clamodule::LS181_clamodule(std::string label,
        Wire& g0_bar, Wire& g1_bar, Wire& g2_bar, Wire& g3_bar,
        Wire& p0_bar, Wire& p1_bar, Wire& p2_bar, Wire& p3_bar,
        Wire& cn_bar,
        Wire& c0, Wire& c1, Wire& c2, Wire& c3,
        Wire& p, Wire& g, Wire& cn4_bar) : AsynchronousDevice(label)
{
    Input("g0_bar", g0_bar); Input("g1_bar", g1_bar); Input("g2_bar", g2_bar); Input("g3_bar", g3_bar);
    Input("p0_bar", p0_bar); Input("p1_bar", p1_bar); Input("p2_bar", p2_bar); Input("p3_bar", p3_bar);
    Input("cn_bar", cn_bar);

    Output("c0", c0); Output("c1", c1); Output("c2", c2); Output("c3", c3);
    Output("p", p); Output("g", g); Output("cn4_bar", cn4_bar);
}

void LS181_clamodule::go(long t)
{
    begin(t);

 // input [3:0] Gb, Pb;
 // input CNb;
 // output [3:0] C;
 // output X, Y, CN4b;

 // assign C[0] = ~CNb;
 // assign C[1] = ~(Pb[0]|(CNb&Gb[0]));
 // assign C[2] = ~(Pb[1]|(Pb[0]&Gb[1])|(CNb&Gb[0]&Gb[1]));
 // assign C[3] = ~(Pb[2]|(Pb[1]&Gb[2])|(Pb[0]&Gb[1]&Gb[2])|(CNb&Gb[0]&Gb[1]&Gb[2]));
 // assign X = ~&Gb;
 // assign Y = ~(Pb[3]|(Pb[2]&Gb[3])|(Pb[1]&Gb[2]&Gb[3])|(Pb[0]&Gb[1]&Gb[2]&Gb[3]));
 // assign CN4b = ~(Y&~(&Gb&CNb));

    assert_signal("c0", !input("cn_bar"));
    assert_signal("c1", !( input("p0_bar") | ( input("cn_bar") & input("g0_bar") ) ) );
    assert_signal("c2", !( input("p1_bar") | ( input("p0_bar") & input("g1_bar") ) | (input("cn_bar") & input("g0_bar") & input("g1_bar")) ) );
    assert_signal("c3", !( input("p2_bar") | ( input("p1_bar") & input("g2_bar") ) | (input("p0_bar") & input("g1_bar") & input("g2_bar")) | ( input("cn_bar") & input("g0_bar") & input("g1_bar") & input("g2_bar") ) ) );

    assert_signal("p", !(input("g0_bar")&input("g1_bar")&input("g2_bar")&input("g3_bar")));
    Logic g = !(input("p3_bar")|(input("p2_bar")&input("g3_bar"))|(input("p1_bar")&input("g2_bar")&input("g3_bar"))|(input("p0_bar") & input("g1_bar") & input("g2_bar") & input("g3_bar")));
    assert_signal("g", g);
    assert_signal("cn4_bar", !(g&!(input("g0_bar")&input("g1_bar")&input("g2_bar")&input("g3_bar")&input("cn_bar"))));

    end();
}

LS181_summodule::LS181_summodule(std::string label,
        Wire& e0, Wire& e1, Wire& e2, Wire& e3,
        Wire& d0, Wire& d1, Wire& d2, Wire& d3,
        Wire& c0, Wire& c1, Wire& c2, Wire& c3,
        Wire& m,
        Wire& f0, Wire& f1, Wire& f2, Wire& f3,
        Wire& aeqb) : AsynchronousDevice(label)
{

    pd = 62; // 74LS181 (worst case)

    Input("e0", e0); Input("e1", e1); Input("e2", e2); Input("e3", e3);
    Input("d0", d0); Input("d1", d1); Input("d2", d2); Input("d3", d3);
    Input("c0", c0); Input("c1", c1); Input("c2", c2); Input("c3", c3);
    Input("m", m);
    Output("f0", f0); Output("f1", f1); Output("f2", f2); Output("f3", f3);
    Output("aeqb", aeqb);
}

void LS181_summodule::go(long t)
{
    begin(t);

 // input [3:0] E, D, C;
 // input M;
 // output [3:0] F;
 // output AEB;

 // assign F = (E ^ D) ^ (C|{4{M}});
 // assign AEB = &F;

    Logic f0, f1, f2, f3;

    f0 = ( (input("e0") ^ input("d0")) ^ (input("c0") | input("m")));
    f1 = ( (input("e1") ^ input("d1")) ^ (input("c1") | input("m")));
    f2 = ( (input("e2") ^ input("d2")) ^ (input("c2") | input("m")));
    f3 = ( (input("e3") ^ input("d3")) ^ (input("c3") | input("m")));

    assert_signal("f0", f0);
    assert_signal("f1", f1);
    assert_signal("f2", f2);
    assert_signal("f3", f3);
    assert_signal("aeqb", f0 & f1 & f2 & f3);

    end();
}

// 74LS182 Carry Lookahead Generator
//
//////////////////////////////////////////////////////////////////////

LS182::LS182(std::string label, Wire& cn, Wire& p0_bar, Wire& g0_bar, Wire& p1_bar, Wire& g1_bar, Wire& p2_bar, Wire& g2_bar, Wire& p3_bar, Wire& g3_bar,
             Wire& cnx, Wire& cny, Wire& cnz, Wire& p_bar, Wire& g_bar) : AsynchronousDevice(label)
{
    pd = 30;
    Input("cn", cn);
    Input("p0_bar", p0_bar);
    Input("g0_bar", g0_bar);
    Input("p1_bar", p1_bar);
    Input("g1_bar", g1_bar);
    Input("p2_bar", p2_bar);
    Input("g2_bar", g2_bar);
    Input("p3_bar", p3_bar);
    Input("g3_bar", g3_bar);
    Output("cnx", cnx);
    Output("cny", cny);
    Output("cnz", cnz);
    Output("p_bar", p_bar);
    Output("g_bar", g_bar);
}

void LS182::go(long t)
{
    begin(t);
    assert_signal("cnx", !input("g0_bar") | (!input("p0_bar") & input("cn")));
    assert_signal("cny", !input("g1_bar") | (!input("p1_bar") & !input("g0_bar")) | (!input("p1_bar") & !input("p0_bar") & input("cn")));
    assert_signal("cnz", !input("g2_bar") | (!input("p2_bar") & !input("g1_bar")) | (!input("p2_bar") & !input("p1_bar") & !input("g0_bar")) | (!input("p2_bar") & !input("p1_bar") & !input("p0_bar") & input("cn")));
    assert_signal("p_bar", input("p3_bar") & input("p2_bar") & input("p1_bar") & input("p0_bar"));
    assert_signal("g_bar", input("g3_bar") | (input("p3_bar") & input("g2_bar")) | (input("p3_bar") & input("p2_bar") & input("g1_bar")) | (input("p3_bar") & input("p2_bar") & input("p1_bar") & input("g0_bar")));
    end();
}

// 74LS173 Quad D Flip-Flop with Three-state Outputs
//
//////////////////////////////////////////////////////////////////////

LS173::LS173(std::string label, Wire& clk, Wire& clr, Wire& g1_bar, Wire& g2_bar, Wire& m_bar, Wire& n_bar,
             Wire& d1, Wire& d2, Wire& d3, Wire& d4, Wire& q1, Wire& q2, Wire& q3, Wire& q4) : SynchronousDevice(label)
{
    pd = 35; // worst case for LS173A
    HotInput("clk", clk);
    Input("clr", clr);
    Input("g1_bar", g1_bar);
    Input("g2_bar", g2_bar);
    HotInput("m_bar", m_bar);
    HotInput("n_bar", n_bar);
    Input("d1", d1); Input("d2", d2); Input("d3", d3); Input("d4", d4);
    Output("q1", q1); Output("q2", q2); Output("q3", q3); Output("q4", q4);
}


void LS173::go(long t)
{
    begin(t);

    if (inputRisingEdge("clk"))
    {
        if (!input("g1_bar") & !input("g2_bar"))
        {
            l1 = input("d1");
            l2 = input("d2");
            l3 = input("d3");
            l4 = input("d4");
            //cout<<devLabel<<" latched "<<(int)(char)l4*8+(int)(char)l3*4+(int)(char)l2*2+(int)(char)l1<<" @ "<<t<<endl;
        }
    }

    if (input("m_bar") | input("n_bar"))
    {
        assert_signal("q1", Logic(Z));
        assert_signal("q2", Logic(Z));
        assert_signal("q3", Logic(Z));
        assert_signal("q4", Logic(Z));
    }
    else
    {
        assert_signal("q1", l1);
        assert_signal("q2", l2);
        assert_signal("q3", l3);
        assert_signal("q4", l4);
    }

    if (input("clr"))
    {
        l1 = Logic(LO);
        l2 = Logic(LO);
        l3 = Logic(LO);
        l4 = Logic(LO);
        //cout<<devLabel<<" reset @ "<<t<<endl;
    }

    end();
}

// 74LS175 Quad D Edge-Triggered Flip-Flop with Complementary Outputs and Asynchronous Clear
//
//////////////////////////////////////////////////////////////////////

LS175::LS175(std::string label, Wire& clk, Wire& mr_bar, Wire& d1, Wire& d2, Wire& d3, Wire& d4,
             Wire& q1, Wire& q2, Wire& q3, Wire& q4, Wire& q1_bar, Wire& q2_bar, Wire& q3_bar, Wire& q4_bar) : SynchronousDevice(label)
{
    pd = 30;
    HotInput("clk", clk);
    HotInput("mr_bar", mr_bar);
    Input("d1", d1); Input("d2", d2); Input("d3", d3); Input("d4", d4);
    Output("q1", q1); Output("q2", q2); Output("q3", q3); Output("q4", q4);
    Output("q1_bar", q1_bar); Output("q2_bar", q2_bar); Output("q3_bar", q3_bar); Output("q4_bar", q4_bar);
}

void LS175::go(long t)
{
    begin(t);

    if (inputRisingEdge("clk"))
    {
        l1 = input("d1");
        l2 = input("d2");
        l3 = input("d3");
        l4 = input("d4");
    }

    if (!input("mr_bar"))
    {
        l1 = Logic(LO);
        l2 = Logic(LO);
        l3 = Logic(LO);
        l4 = Logic(LO);
    }

    assert_signal("q1", l1); assert_signal("q1_bar", !l1);
    assert_signal("q2", l2); assert_signal("q2_bar", !l2);
    assert_signal("q3", l3); assert_signal("q3_bar", !l3);
    assert_signal("q4", l4); assert_signal("q4_bar", !l4);

    end();
}

// 74LS273 8-bit Register with Reset
//
//////////////////////////////////////////////////////////////////////

LS273::LS273(std::string label, Wire& clk, Wire& clr_bar,
        Wire& d1, Wire& d2, Wire& d3, Wire& d4, Wire& d5, Wire& d6, Wire& d7, Wire& d8,
        Wire& q1, Wire& q2, Wire& q3, Wire& q4, Wire& q5, Wire& q6, Wire& q7, Wire& q8) : SynchronousDevice(label)
{
    pd = 27;
    HotInput("clk", clk);
    HotInput("clr_bar", clr_bar);
    Input("d1", d1); Input("d2", d2); Input("d3", d3); Input("d4", d4); Input("d5", d5); Input("d6", d6); Input("d7", d7); Input("d8", d8);
    Output("q1", q1); Output("q2", q2); Output("q3", q3); Output("q4", q4); Output("q5", q5); Output("q6", q6); Output("q7", q7); Output("q8", q8);
}

void LS273::go(long t)
{
    begin(t);

    if (inputRisingEdge("clk"))
    {
        l1 = input("d1");
        l2 = input("d2");
        l3 = input("d3");
        l4 = input("d4");
        l5 = input("d5");
        l6 = input("d6");
        l7 = input("d7");
        l8 = input("d8");
        //cout<<devLabel<<" latched "<<(int)(char)l8*128+(int)(char)l7*64+(int)(char)l6*32+(int)(char)l5*16+(int)(char)l4*8+(int)(char)l3*4+(int)(char)l2*2+(int)(char)l1<<" @ "<<t<<endl;
    }

    if (!input("clr_bar"))
    {
        l1 = Logic(LO);
        l2 = Logic(LO);
        l3 = Logic(LO);
        l4 = Logic(LO);
        l5 = Logic(LO);
        l6 = Logic(LO);
        l7 = Logic(LO);
        l8 = Logic(LO);
    }

    assert_signal("q1", l1);
    assert_signal("q2", l2);
    assert_signal("q3", l3);
    assert_signal("q4", l4);
    assert_signal("q5", l5);
    assert_signal("q6", l6);
    assert_signal("q7", l7);
    assert_signal("q8", l8);

    end();
}

// 74LS348 8-to-3 line Priority Encoder with three-state outputs
//
//////////////////////////////////////////////////////////////////////

LS348::LS348(std::string label, Wire& ei_bar,
        Wire& i0_bar, Wire& i1_bar, Wire& i2_bar, Wire& i3_bar, Wire& i4_bar, Wire& i5_bar, Wire& i6_bar, Wire& i7_bar,
        Wire& a0_bar, Wire& a1_bar, Wire& a2_bar, Wire& eo_bar, Wire& gs_bar) : AsynchronousDevice(label)
{
    pd = 55;
    Input("ei_bar", ei_bar);
    Input("i0_bar", i0_bar);
    Input("i1_bar", i1_bar);
    Input("i2_bar", i2_bar);
    Input("i3_bar", i3_bar);
    Input("i4_bar", i4_bar);
    Input("i5_bar", i5_bar);
    Input("i6_bar", i6_bar);
    Input("i7_bar", i7_bar);
    Output("a0_bar", a0_bar);
    Output("a1_bar", a1_bar);
    Output("a2_bar", a2_bar);
    Output("eo_bar", eo_bar);
    Output("gs_bar", gs_bar);
}

void LS348::go(long t)
{
    begin(t);

    char sel = 0;

    if (input("ei_bar"))
    {
        assert_signal("a0_bar", Logic(Z));
        assert_signal("a1_bar", Logic(Z));
        assert_signal("a2_bar", Logic(Z));
        assert_signal("gs_bar", Logic(HI));
        assert_signal("eo_bar", Logic(HI));
    }
    else if (input("i0_bar") & input("i1_bar") & input("i2_bar") & input("i3_bar") & input("i4_bar") & input("i5_bar") & input("i6_bar") & input("i7_bar"))
    {
        assert_signal("a0_bar", Logic(Z));
        assert_signal("a1_bar", Logic(Z));
        assert_signal("a2_bar", Logic(Z));
        assert_signal("gs_bar", Logic(HI));
        assert_signal("eo_bar", Logic(LO));
    }
    else {
        if (!input("i7_bar"))
        {
            sel = 0;
        }
        else if (!input("i6_bar"))
        {
            sel = 1;
        }
        else if (!input("i5_bar"))
        {
            sel = 2;
        }
        else if (!input("i4_bar"))
        {
            sel = 3;
        }
        else if (!input("i3_bar"))
        {
            sel = 4;
        }
        else if (!input("i2_bar"))
        {
            sel = 5;
        }
        else if (!input("i1_bar"))
        {
            sel = 6;
        }
        else if (!input("i0_bar"))
        {
            sel = 7;
        }
        assert_signal("a0_bar", sel & 0x01);
        assert_signal("a1_bar", sel & 0x02);
        assert_signal("a2_bar", sel & 0x04);
        assert_signal("gs_bar", Logic(LO));
        assert_signal("eo_bar", Logic(HI));
    }

    end();
}

// 74LS374 Octal Register with three-state outputs
//
//////////////////////////////////////////////////////////////////////

LS374::LS374(std::string label, Wire& clk, Wire& oe_bar,
        Wire& d1, Wire& d2, Wire& d3, Wire& d4, Wire& d5, Wire& d6, Wire& d7, Wire& d8,
        Wire& q1, Wire& q2, Wire& q3, Wire& q4, Wire& q5, Wire& q6, Wire& q7, Wire& q8) : SynchronousDevice (label)
{
    pd = 44;
    l1 = Logic(LO); l2 = Logic(LO); l3 = Logic(LO); l4 = Logic(LO);
    l5 = Logic(LO); l6 = Logic(LO); l7 = Logic(LO); l8 = Logic(LO);
    HotInput("clk", clk);
    Input("d1", d1); Input("d2", d2); Input("d3", d3); Input("d4", d4); Input("d5", d5); Input("d6", d6); Input("d7", d7); Input("d8", d8);
    HotInput("oe_bar", oe_bar);
    Output("q1", q1); Output("q2", q2); Output("q3", q3); Output("q4", q4); Output("q5", q5); Output("q6", q6); Output("q7", q7); Output("q8", q8);
}

void LS374::go(long t)
{
    begin(t);

    if (inputRisingEdge("clk"))
    {
        l1 = input("d1");
        l2 = input("d2");
        l3 = input("d3");
        l4 = input("d4");
        l5 = input("d5");
        l6 = input("d6");
        l7 = input("d7");
        l8 = input("d8");
        // cout<<devLabel<<" stored "<<(int)(char)l8*128+(int)(char)l7*64+(int)(char)l6*32+(int)(char)l5*16+(int)(char)l4*8+(int)(char)l3*4+(int)(char)l2*2+(int)(char)l1<<" @ "<<t<<endl;
    }

    if (!input("oe_bar"))
    {
        assert_signal("q1", l1);
        assert_signal("q2", l2);
        assert_signal("q3", l3);
        assert_signal("q4", l4);
        assert_signal("q5", l5);
        assert_signal("q6", l6);
        assert_signal("q7", l7);
        assert_signal("q8", l8);
        // cout<<devLabel<<" output "<<(int)(char)l8*128+(int)(char)l7*64+(int)(char)l6*32+(int)(char)l5*16+(int)(char)l4*8+(int)(char)l3*4+(int)(char)l2*2+(int)(char)l1<<" @ "<<t<<endl;
    }
    else if (input("oe_bar"))
    {
        assert_signal("q1", Logic(Z));
        assert_signal("q2", Logic(Z));
        assert_signal("q3", Logic(Z));
        assert_signal("q4", Logic(Z));
        assert_signal("q5", Logic(Z));
        assert_signal("q6", Logic(Z));
        assert_signal("q7", Logic(Z));
        assert_signal("q8", Logic(Z));
    }

    end();
}

// 74LS569 Binary Up/Down Counter with three-state outputs
//
//////////////////////////////////////////////////////////////////////

LS569::LS569(std::string label, Wire& clk, Wire& load_bar, Wire& aclr_bar, Wire& sclr_bar,
        Wire& oe_bar, Wire& cep_bar, Wire& cet_bar, Wire& ud,
        Wire& a, Wire& b, Wire& c, Wire& d,
        Wire& ya, Wire& yb, Wire& yc, Wire& yd,
        Wire& rco_bar, Wire& cco) : SynchronousDevice(label)
{
    pd = 32;
    reg = reg & 0x0f;
    HotInput("clk", clk);
    Input("load_bar", load_bar);
    HotInput("aclr_bar", aclr_bar);
    Input("sclr_bar", sclr_bar);
    HotInput("oe_bar", oe_bar);
    HotInput("cep_bar", cep_bar);
    HotInput("cet_bar", cet_bar);
    Input("ud", ud);
    Input("a", a); Input("b", b); Input("c", c); Input("d", d);
    Output("ya", ya); Output("yb", yb); Output("yc", yc); Output("yd", yd);
    Output("rco_bar", rco_bar);
    Output("cco", cco);
}

void LS569::go(long t)
{
    begin(t);

    if (!input("aclr_bar"))
    {
        reg = 0;
    }

    else if (inputRisingEdge("clk"))
    {
        if (!input("sclr_bar"))
        {
            reg = 0;
        }
        else if (!input("load_bar"))
        {
            reg = ((char)input("d") << 3) + ((char)input("c") << 2) + ((char)input("b") << 1) + (char)input("a");
        }
        else if (!input("cep_bar") & !input("cet_bar") & input("ud"))
        {
            if (reg == 15)
            {
                reg = 0;
            }
            else
            {
                reg = reg + 1;
            }
        }
        else if (!input("cep_bar") & !input("cet_bar") & !input("ud"))
        {
            if (reg == 0)
            {
                reg = 15;
            }
            else
            {
                reg = reg - 1;
            }
        }
    }

    if (!input("oe_bar"))
    {
        assert_signal("yd", reg & 0x08);
        assert_signal("yc", reg & 0x04);
        assert_signal("yb", reg & 0x02);
        assert_signal("ya", reg & 0x01);
    }
    else
    {
        assert_signal("yd", Logic(Z));
        assert_signal("yc", Logic(Z));
        assert_signal("yb", Logic(Z));
        assert_signal("ya", Logic(Z));
    }

    Logic rco_bar = !input("cet_bar") & ( (input("ud") & Logic(reg == 15)) | (!input("ud") & Logic(reg == 0)));
    assert_signal("rco_bar", !rco_bar);
    assert_signal("cco", (rco_bar & !input("clk") & !input("cet_bar") & !input("cep_bar")));

    end();
}


// 74LS04 Hex Inverting Gates
//
//////////////////////////////////////////////////////////////////////

LS04::LS04(std::string label,
        Wire& a1, Wire& y1,
        Wire& a2, Wire& y2,
        Wire& a3, Wire& y3,
        Wire& a4, Wire& y4,
        Wire& a5, Wire& y5,
        Wire& a6, Wire& y6) : AsynchronousDevice(label)
{
    pd = 15;

    Input("a1", a1); Input("a2", a2); Input("a3", a3);
    Input("a4", a4); Input("a5", a5); Input("a6", a6);
    Output("y1", y1); Output("y2", y2); Output("y3", y3);
    Output("y4", y4); Output("y5", y5); Output("y6", y6);
}

void LS04::go(long t)
{
    begin(t);
    assert_signal("y1", !input("a1"));
    assert_signal("y2", !input("a2"));
    assert_signal("y3", !input("a3"));
    assert_signal("y4", !input("a4"));
    assert_signal("y5", !input("a5"));
    assert_signal("y6", !input("a6"));
    end();
}

// 29F020 70ns 256k ROM
//
//////////////////////////////////////////////////////////////////////

EEPROM_29F020::EEPROM_29F020(std::string label, std::string rom_name,
        Wire& ce_bar, Wire& oe_bar, Wire& we_bar,
        Wire& a0, Wire& a1, Wire& a2, Wire& a3,
        Wire& a4, Wire& a5, Wire& a6, Wire& a7,
        Wire& a8, Wire& a9, Wire& a10, Wire& a11,
        Wire& a12, Wire& a13, Wire& a14, Wire& a15,
        Wire& a16, Wire& a17,
        Wire& dq0, Wire& dq1, Wire& dq2, Wire& dq3, Wire& dq4, Wire& dq5, Wire& dq6, Wire& dq7) : AsynchronousDevice(label)
{
    pd = 70; // 70 ns for AMIC 29F002

    Input("ce_bar", ce_bar); Input("oe_bar", oe_bar); Input("we_bar", we_bar);
    Input("a0", a0); Input("a1", a1); Input("a2", a2); Input("a3", a3);
    Input("a4", a4); Input("a5", a5); Input("a6", a6); Input("a7", a7);
    Input("a8", a8); Input("a9", a9); Input("a10", a10); Input("a11", a11);
    Input("a12", a12); Input("a13", a13); Input("a14", a14); Input("a15", a15);
    Input("a16", a16); Input("a17", a17);
    Output("dq0", dq0); Output("dq1", dq1); Output("dq2", dq2); Output("dq3", dq3);
    Output("dq4", dq4); Output("dq5", dq5); Output("dq6", dq6); Output("dq7", dq7);

    // read ROM contents from file
    char c;
    int i = 0;
    mem.resize((int)pow((float)2, (int)18));
    ifstream f(rom_name.c_str(), ios::in | ios::binary);
    cout << "Reading ROM " << rom_name << " ";
    if (f.good()) {
        while (!f.eof())
        {
            f.read(&c, 1);
            mem[i++] = c;
        }
        cout<<"["<<i-1<<" bytes]"<<endl;
        f.close();
    }
    else
    {
        cout<<"ERROR: unable to open "<<rom_name<<endl;
    }
    f.close();
}

void EEPROM_29F020::go(long t)
{
    begin(t);

    addr = (int)((char)input("a17")) * 0x20000 + (int)((char)input("a16")) * 0x10000 + (int)((char)input("a15")) * 0x08000 +
            (int)((char)input("a14")) * 0x04000 + (int)((char)input("a13")) * 0x02000 + (int)((char)input("a12")) * 0x01000 +
            (int)((char)input("a11")) * 0x00800 + (int)((char)input("a10")) * 0x00400 + (int)((char)input("a9")) * 0x00200 +
            (int)((char)input("a8")) * 0x00100 + (int)((char)input("a7")) * 0x00080 + (int)((char)input("a6")) * 0x00040 +
            (int)((char)input("a5")) * 0x00020 + (int)((char)input("a4")) * 0x00010 + (int)((char)input("a3")) * 0x00008 +
            (int)((char)input("a2")) * 0x00004 + (int)((char)input("a1")) * 0x00002 + (int)((char)input("a0")) * 0x00001;

    if (!input("ce_bar") & !input("oe_bar"))
    {
        c = mem[addr];
        // cout<<t<<": Reading ROM from "<<hex<<addr<<": "<<int(c)<<dec<<endl;
        assert_signal("dq7", c & 0x80); assert_signal("dq6", c & 0x40); assert_signal("dq5", c & 0x20); assert_signal("dq4", c & 0x10);
        assert_signal("dq3", c & 0x08); assert_signal("dq2", c & 0x04); assert_signal("dq1", c & 0x02); assert_signal("dq0", c & 0x01);
    }
    else
    {
        assert_signal("dq0", Logic(Z)); assert_signal("dq1", Logic(Z)); assert_signal("dq2", Logic(Z)); assert_signal("dq3", Logic(Z));
        assert_signal("dq4", Logic(Z)); assert_signal("dq5", Logic(Z)); assert_signal("dq6", Logic(Z)); assert_signal("dq7", Logic(Z));
    }

    end();
}

// 628512 DIP-32 S-RAM 70ns 8x512k
//
//////////////////////////////////////////////////////////////////////

SRAM_628512::SRAM_628512(std::string label, Wire& cs_bar, Wire& oe_bar, Wire& we_bar,
        Wire& a0, Wire& a1, Wire& a2, Wire& a3,
        Wire& a4, Wire& a5, Wire& a6, Wire& a7,
        Wire& a8, Wire& a9, Wire& a10, Wire& a11,
        Wire& a12, Wire& a13, Wire& a14, Wire& a15,
        Wire& a16, Wire& a17, Wire& a18,
        Wire& io0, Wire& io1, Wire& io2, Wire& io3, Wire& io4, Wire& io5, Wire& io6, Wire& io7) : AsynchronousDevice(label)
{
    pd = 70;
    do_not_notify_self = true;
    mem.resize(524288);
    cout<<"Initializing "<<524288/1024<<"k memory ["<<label<<"]"<<endl;

    Input("cs_bar", cs_bar); Input("oe_bar", oe_bar); Input("we_bar", we_bar);
    Input("a0", a0); Input("a1", a1); Input("a2", a2); Input("a3", a3);
    Input("a4", a4); Input("a5", a5); Input("a6", a6); Input("a7", a7);
    Input("a8", a8); Input("a9", a9); Input("a10", a10); Input("a11", a11);
    Input("a12", a12); Input("a13", a13); Input("a14", a14); Input("a15", a15);
    Input("a16", a16); Input("a17", a17); Input("a18", a18);
    Input("io0", io0); Input("io1", io1); Input("io2", io2); Input("io3", io3);
    Input("io4", io4); Input("io5", io5); Input("io6", io6); Input("io7", io7);
    Output("io0", io0); Output("io1", io1); Output("io2", io2); Output("io3", io3);
    Output("io4", io4); Output("io5", io5); Output("io6", io6); Output("io7", io7);
}

void SRAM_628512::go(long t)
{
    begin(t);

    int addr;
    unsigned char c;
    addr = (int)((char)input("a18")) * 0x40000 + (int)((char)input("a17")) * 0x20000 + (int)((char)input("a16")) * 0x10000 + (int)((char)input("a15")) * 0x08000 +
            (int)((char)input("a14")) * 0x04000 + (int)((char)input("a13")) * 0x02000 + (int)((char)input("a12")) * 0x01000 +
            (int)((char)input("a11")) * 0x00800 + (int)((char)input("a10")) * 0x00400 + (int)((char)input("a9")) * 0x00200 +
            (int)((char)input("a8")) * 0x00100 + (int)((char)input("a7")) * 0x00080 + (int)((char)input("a6")) * 0x00040 +
            (int)((char)input("a5")) * 0x00020 + (int)((char)input("a4")) * 0x00010 + (int)((char)input("a3")) * 0x00008 +
            (int)((char)input("a2")) * 0x00004 + (int)((char)input("a1")) * 0x00002 + (int)((char)input("a0")) * 0x00001;

    if (input("cs_bar") | (!input("cs_bar") & input("oe_bar") & input("we_bar")))
    {
        assert_signal("io0", Logic(Z)); assert_signal("io1", Logic(Z)); assert_signal("io2", Logic(Z)); assert_signal("io3", Logic(Z));
        assert_signal("io4", Logic(Z)); assert_signal("io5", Logic(Z)); assert_signal("io6", Logic(Z)); assert_signal("io7", Logic(Z));
    }
    else if ((Logic)inputFallingEdge("we_bar") & !input("cs_bar"))
        // this entry condition is cheat, the device is actually not edge sensitive
        // but due to signal propagation algorithm in the simulator we need to supress spurious
        // memory writes when /WE is not yet deasserted, but other signals (address, data) are
    {
        // first, disable driving the bus
        assert_signal("io0", Logic(Z)); assert_signal("io1", Logic(Z)); assert_signal("io2", Logic(Z)); assert_signal("io3", Logic(Z));
        assert_signal("io4", Logic(Z)); assert_signal("io5", Logic(Z)); assert_signal("io6", Logic(Z)); assert_signal("io7", Logic(Z));
        // then, write
        c = ((char)input("io7") << 7) + ((char)input("io6") << 6) + ((char)input("io5") << 5) + ((char)input("io4") << 4) +
            ((char)input("io3") << 3) + ((char)input("io2") << 2) + ((char)input("io1") << 1) + ((char)input("io0") << 0);
        //cout<<"Writing to 0x"<<setw(4)<<setfill('0')<<hex<<addr<<" : "<<int(c)<<dec<<" @ " << t << "ns" << endl;
        mem[addr] = c;
    }
    else
    {
        c = mem[addr];
        //cout<<"Reading from "<<hex<<addr<<": "<<int(c)<<dec<<endl;
        assert_signal("io7", c & 0x80); assert_signal("io6", c & 0x40); assert_signal("io5", c & 0x20); assert_signal("io4", c & 0x10);
        assert_signal("io3", c & 0x08); assert_signal("io2", c & 0x04); assert_signal("io1", c & 0x02); assert_signal("io0", c & 0x01);
    }

    end();
}

SRAM_628512::~SRAM_628512()
{
    cout<<"Dumping memory '"<<devLabel<<"'"<<endl;
    ofstream f(devLabel.c_str(), ios::out);
    int i;
    if (f.good()) {
        for (i=0; i<524288; i++) {
            if (i % 16 == 0)
            {
                if (i!=0) f<<endl;
                f<<hex<<setw(8)<<setfill('0')<<i<<": ";
            }
            f<<hex<<setw(2)<<((int)(mem[i]) & 0x000000ff)<<" ";
        }
    }
    else
    {
        cout<<"ERROR: unable to write to "<<devLabel<<endl;
    }
    f.close();
}

// 74LS148 8-Line to 3-Line Priority Encoder
//
//////////////////////////////////////////////////////////////////////

LS148::LS148(std::string label, Wire& ei_bar,
        Wire& i0_bar, Wire& i1_bar, Wire& i2_bar, Wire& i3_bar, Wire& i4_bar, Wire& i5_bar, Wire& i6_bar, Wire& i7_bar,
        Wire& a0_bar, Wire& a1_bar, Wire& a2_bar, Wire& eo_bar, Wire& gs_bar) : AsynchronousDevice(label)
{
    pd = 55;
    Input("ei_bar", ei_bar);
    Input("i0_bar", i0_bar);
    Input("i1_bar", i1_bar);
    Input("i2_bar", i2_bar);
    Input("i3_bar", i3_bar);
    Input("i4_bar", i4_bar);
    Input("i5_bar", i5_bar);
    Input("i6_bar", i6_bar);
    Input("i7_bar", i7_bar);
    Output("a0_bar", a0_bar);
    Output("a1_bar", a1_bar);
    Output("a2_bar", a2_bar);
    Output("eo_bar", eo_bar);
    Output("gs_bar", gs_bar);
}

void LS148::go(long t)
{
    begin(t);

    char sel = 0;

    if (input("ei_bar"))
    {
        assert_signal("a0_bar", Logic(HI));
        assert_signal("a1_bar", Logic(HI));
        assert_signal("a2_bar", Logic(HI));
        assert_signal("gs_bar", Logic(HI));
        assert_signal("eo_bar", Logic(HI));
    }
    else if (input("i0_bar") & input("i1_bar") & input("i2_bar") & input("i3_bar") & input("i4_bar") & input("i5_bar") & input("i6_bar") & input("i7_bar"))
    {
        assert_signal("a0_bar", Logic(HI));
        assert_signal("a1_bar", Logic(HI));
        assert_signal("a2_bar", Logic(HI));
        assert_signal("gs_bar", Logic(HI));
        assert_signal("eo_bar", Logic(LO));
    }
    else {

        if (!input("i7_bar"))
        {
            sel = 0;
        }
        else if (!input("i6_bar"))
        {
            sel = 1;
        }
        else if (!input("i5_bar"))
        {
            sel = 2;
        }
        else if (!input("i4_bar"))
        {
            sel = 3;
        }
        else if (!input("i3_bar"))
        {
            sel = 4;
        }
        else if (!input("i2_bar"))
        {
            sel = 5;
        }
        else if (!input("i1_bar"))
        {
            sel = 6;
        }
        else if (!input("i0_bar"))
        {
            sel = 7;
        }
        //cout<<t<<" "<<devLabel<<" pe selected: "<<(int)sel<<endl;
        assert_signal("a0_bar", sel & 0x01);
        assert_signal("a1_bar", sel & 0x02);
        assert_signal("a2_bar", sel & 0x04);
        assert_signal("gs_bar", Logic(LO));
        assert_signal("eo_bar", Logic(HI));
    }

    end();
}

// 3 to 8-line Decoder/Demultiplexer
//
//////////////////////////////////////////////////////////////////////

LS138::LS138(std::string label, Wire& g1, Wire& g2a_bar, Wire& g2b_bar, Wire& a, Wire& b, Wire &c,
        Wire& y0_bar, Wire& y1_bar, Wire& y2_bar, Wire& y3_bar, Wire& y4_bar, Wire& y5_bar, Wire& y6_bar, Wire& y7_bar) : AsynchronousDevice(label)
{
    pd = 40;
    Input("g1", g1); Input("g2a_bar", g2a_bar); Input("g2b_bar", g2b_bar);
    Input("a", a); Input("b", b); Input("c", c);
    Output("y0_bar", y0_bar); Output("y1_bar", y1_bar); Output("y2_bar", y2_bar); Output("y3_bar", y3_bar);
    Output("y4_bar", y4_bar); Output("y5_bar", y5_bar); Output("y6_bar", y6_bar); Output("y7_bar", y7_bar);
};

void LS138::go(long t)
{
    begin(t);

    assert_signal("y0_bar", !( input("g1") & !(input("g2a_bar") | input("g2b_bar")) & !input("c") & !input("b") & !input("a") ));
    assert_signal("y1_bar", !( input("g1") & !(input("g2a_bar") | input("g2b_bar")) & !input("c") & !input("b") &  input("a") ));
    assert_signal("y2_bar", !( input("g1") & !(input("g2a_bar") | input("g2b_bar")) & !input("c") &  input("b") & !input("a") ));
    assert_signal("y3_bar", !( input("g1") & !(input("g2a_bar") | input("g2b_bar")) & !input("c") &  input("b") &  input("a") ));
    assert_signal("y4_bar", !( input("g1") & !(input("g2a_bar") | input("g2b_bar")) &  input("c") & !input("b") & !input("a") ));
    assert_signal("y5_bar", !( input("g1") & !(input("g2a_bar") | input("g2b_bar")) &  input("c") & !input("b") &  input("a") ));
    assert_signal("y6_bar", !( input("g1") & !(input("g2a_bar") | input("g2b_bar")) &  input("c") &  input("b") & !input("a") ));
    assert_signal("y7_bar", !( input("g1") & !(input("g2a_bar") | input("g2b_bar")) &  input("c") &  input("b") &  input("a") ));

    end();
}

// 74LS139 Dual 1-of-4 Decoder/Demultiplexer
//
//////////////////////////////////////////////////////////////////////

LS139::LS139(std::string label, Wire& ea_bar, Wire& eb_bar,
        Wire& a0a, Wire& a1a, Wire& o0a_bar, Wire& o1a_bar, Wire& o2a_bar, Wire& o3a_bar,
        Wire& a0b, Wire& a1b, Wire& o0b_bar, Wire& o1b_bar, Wire& o2b_bar, Wire& o3b_bar) : AsynchronousDevice(label)
{
    pd=38;
    Input("ea_bar", ea_bar);
    Input("eb_bar", eb_bar);
    Input("a0a", a0a); Input("a1a", a1a);
    Input("a0b", a0b); Input("a1b", a1b);
    Output("o0a_bar", o0a_bar); Output("o1a_bar", o1a_bar); Output("o2a_bar", o2a_bar); Output("o3a_bar", o3a_bar);
    Output("o0b_bar", o0b_bar); Output("o1b_bar", o1b_bar); Output("o2b_bar", o2b_bar); Output("o3b_bar", o3b_bar);
}

void LS139::go(long t)
{
    begin(t);

    assert_signal("o0a_bar", !(!input("ea_bar") & (!input("a0a") & !input("a1a"))));
    assert_signal("o1a_bar", !(!input("ea_bar") & (!input("a0a") &  input("a1a"))));
    assert_signal("o2a_bar", !(!input("ea_bar") & ( input("a0a") & !input("a1a"))));
    assert_signal("o3a_bar", !(!input("ea_bar") & ( input("a0a") &  input("a1a"))));

    assert_signal("o0b_bar", !(!input("eb_bar") & (!input("a0b") & !input("a1b"))));
    assert_signal("o1b_bar", !(!input("eb_bar") & (!input("a0b") &  input("a1b"))));
    assert_signal("o2b_bar", !(!input("eb_bar") & ( input("a0b") & !input("a1b"))));
    assert_signal("o3b_bar", !(!input("eb_bar") & ( input("a0b") &  input("a1b"))));

    end();
}

// 74LS154 1-of-16 Decoder/Demultiplexer
//
//////////////////////////////////////////////////////////////////////

LS154::LS154(std::string label, Wire& g1_bar, Wire& g2_bar,
        Wire& a, Wire& b, Wire& c, Wire& d,
        Wire& y0_bar, Wire& y1_bar, Wire& y2_bar, Wire& y3_bar, Wire& y4_bar, Wire& y5_bar, Wire& y6_bar, Wire& y7_bar,
        Wire& y8_bar, Wire& y9_bar, Wire& y10_bar, Wire& y11_bar, Wire& y12_bar, Wire& y13_bar, Wire& y14_bar, Wire& y15_bar) : AsynchronousDevice(label)
{
    pd = 35;
    Input("g1_bar", g1_bar); Input("g2_bar", g2_bar);
    Input("a", a); Input("b", b); Input("c", c); Input("d", d);
    Output("y0_bar", y0_bar);
    Output("y1_bar", y1_bar);
    Output("y2_bar", y2_bar);
    Output("y3_bar", y3_bar);
    Output("y4_bar", y4_bar);
    Output("y5_bar", y5_bar);
    Output("y6_bar", y6_bar);
    Output("y7_bar", y7_bar);
    Output("y8_bar", y8_bar);
    Output("y9_bar", y9_bar);
    Output("y10_bar", y10_bar);
    Output("y11_bar", y11_bar);
    Output("y12_bar", y12_bar);
    Output("y13_bar", y13_bar);
    Output("y14_bar", y14_bar);
    Output("y15_bar", y15_bar);
}

void LS154::go(long t)
{
    begin(t);

    assert_signal("y0_bar", !( !input("g1_bar") & !input("g2_bar") & (!input("d") & !input("c") & !input("b") & !input("a") )));
    assert_signal("y1_bar", !( !input("g1_bar") & !input("g2_bar") & (!input("d") & !input("c") & !input("b") &  input("a") )));
    assert_signal("y2_bar", !( !input("g1_bar") & !input("g2_bar") & (!input("d") & !input("c") &  input("b") & !input("a") )));
    assert_signal("y3_bar", !( !input("g1_bar") & !input("g2_bar") & (!input("d") & !input("c") &  input("b") &  input("a") )));
    assert_signal("y4_bar", !( !input("g1_bar") & !input("g2_bar") & (!input("d") &  input("c") & !input("b") & !input("a") )));
    assert_signal("y5_bar", !( !input("g1_bar") & !input("g2_bar") & (!input("d") &  input("c") & !input("b") &  input("a") )));
    assert_signal("y6_bar", !( !input("g1_bar") & !input("g2_bar") & (!input("d") &  input("c") &  input("b") & !input("a") )));
    assert_signal("y7_bar", !( !input("g1_bar") & !input("g2_bar") & (!input("d") &  input("c") &  input("b") &  input("a") )));
    assert_signal("y8_bar", !( !input("g1_bar") & !input("g2_bar") & ( input("d") & !input("c") & !input("b") & !input("a") )));
    assert_signal("y9_bar", !( !input("g1_bar") & !input("g2_bar") & ( input("d") & !input("c") & !input("b") &  input("a") )));
    assert_signal("y10_bar", !( !input("g1_bar") & !input("g2_bar") & ( input("d") & !input("c") &  input("b") & !input("a") )));
    assert_signal("y11_bar", !( !input("g1_bar") & !input("g2_bar") & ( input("d") & !input("c") &  input("b") &  input("a") )));
    assert_signal("y12_bar", !( !input("g1_bar") & !input("g2_bar") & ( input("d") &  input("c") & !input("b") & !input("a") )));
    assert_signal("y13_bar", !( !input("g1_bar") & !input("g2_bar") & ( input("d") &  input("c") & !input("b") &  input("a") )));
    assert_signal("y14_bar", !( !input("g1_bar") & !input("g2_bar") & ( input("d") &  input("c") &  input("b") & !input("a") )));
    assert_signal("y15_bar", !( !input("g1_bar") & !input("g2_bar") & ( input("d") &  input("c") &  input("b") &  input("a") )));

    end();
}

// 74LS157 Quad 2-line to 1-line Data Selector/Multiplexer
//
//////////////////////////////////////////////////////////////////////

LS157::LS157(std::string label, Wire& g_bar, Wire& a_bar_b,
        Wire& a1, Wire& a2, Wire& a3, Wire& a4, Wire& b1, Wire& b2, Wire& b3, Wire& b4,
        Wire& y1, Wire& y2, Wire& y3, Wire& y4) : AsynchronousDevice(label)
{
    pd = 27;
    Input("g_bar", g_bar);
    Input("a_bar_b", a_bar_b);
    Input("a1", a1); Input("b1", b1);
    Input("a2", a2); Input("b2", b2);
    Input("a3", a3); Input("b3", b3);
    Input("a4", a4); Input("b4", b4);
    Output("y1", y1);
    Output("y2", y2);
    Output("y3", y3);
    Output("y4", y4);
}

void LS157::go(long t)
{
    begin(t);
    assert_signal("y1", !input("g_bar") & ( (input("a1") & !input("a_bar_b")) | (input("b1") & input("a_bar_b")) ));
    assert_signal("y2", !input("g_bar") & ( (input("a2") & !input("a_bar_b")) | (input("b2") & input("a_bar_b")) ));
    assert_signal("y3", !input("g_bar") & ( (input("a3") & !input("a_bar_b")) | (input("b3") & input("a_bar_b")) ));
    assert_signal("y4", !input("g_bar") & ( (input("a4") & !input("a_bar_b")) | (input("b4") & input("a_bar_b")) ));
    end();
}


// 74LS00 Quad 2-input NAND Gate
//
//////////////////////////////////////////////////////////////////////

LS00::LS00(std::string label,
        Wire& a1, Wire& b1, Wire& y1_bar, Wire& a2, Wire& b2, Wire& y2_bar,
        Wire& a3, Wire& b3, Wire& y3_bar, Wire& a4, Wire& b4, Wire& y4_bar) : AsynchronousDevice(label)
{
    pd = 15;
    Input("a1", a1); Input("b1", b1);
    Input("a2", a2); Input("b2", b2);
    Input("a3", a3); Input("b3", b3);
    Input("a4", a4); Input("b4", b4);
    Output("y1_bar", y1_bar);
    Output("y2_bar", y2_bar);
    Output("y3_bar", y3_bar);
    Output("y4_bar", y4_bar);
}

void LS00::go(long t)
{
    begin(t);
    assert_signal("y1_bar", !(input("a1") & input("b1")));
    assert_signal("y2_bar", !(input("a2") & input("b2")));
    assert_signal("y3_bar", !(input("a3") & input("b3")));
    assert_signal("y4_bar", !(input("a4") & input("b4")));
    end();
}

// 74LS02 Quad 2-input NOR Gate
//
//////////////////////////////////////////////////////////////////////

LS02::LS02(std::string label,
        Wire& a1, Wire& b1, Wire& y1_bar, Wire& a2, Wire& b2, Wire& y2_bar,
        Wire& a3, Wire& b3, Wire& y3_bar, Wire& a4, Wire& b4, Wire& y4_bar) : AsynchronousDevice(label)
{
    pd = 18;
    Input("a1", a1); Input("b1", b1);
    Input("a2", a2); Input("b2", b2);
    Input("a3", a3); Input("b3", b3);
    Input("a4", a4); Input("b4", b4);
    Output("y1_bar", y1_bar);
    Output("y2_bar", y2_bar);
    Output("y3_bar", y3_bar);
    Output("y4_bar", y4_bar);
}

void LS02::go(long t)
{
    begin(t);
    assert_signal("y1_bar", !(input("a1") | input("b1")));
    assert_signal("y2_bar", !(input("a2") | input("b2")));
    assert_signal("y3_bar", !(input("a3") | input("b3")));
    assert_signal("y4_bar", !(input("a4") | input("b4")));
    end();
}

// 74LS08 Quad 2-input AND Gate
//
//////////////////////////////////////////////////////////////////////

LS08::LS08(std::string label,
        Wire& a1, Wire& b1, Wire& y1, Wire& a2, Wire& b2, Wire& y2,
        Wire& a3, Wire& b3, Wire& y3, Wire& a4, Wire& b4, Wire& y4) : AsynchronousDevice(label)
{
    pd = 18;
    Input("a1", a1); Input("b1", b1);
    Input("a2", a2); Input("b2", b2);
    Input("a3", a3); Input("b3", b3);
    Input("a4", a4); Input("b4", b4);
    Output("y1", y1);
    Output("y2", y2);
    Output("y3", y3);
    Output("y4", y4);
}

void LS08::go(long t)
{
    begin(t);
    assert_signal("y1", input("a1") & input("b1"));
    assert_signal("y2", input("a2") & input("b2"));
    assert_signal("y3", input("a3") & input("b3"));
    assert_signal("y4", input("a4") & input("b4"));
    end();
}

// 74LS20 Dual 4-Input NAND Gate
//
//////////////////////////////////////////////////////////////////////

LS20::LS20(std::string label,
           Wire& a1, Wire& b1, Wire& c1, Wire& d1, Wire& y1, Wire& a2, Wire& b2, Wire& c2, Wire& d2, Wire& y2) : AsynchronousDevice(label)
{
    pd = 15;
    Input("a1", a1);
    Input("b1", b1);
    Input("c1", c1);
    Input("d1", d1);
    Input("a2", a2);
    Input("b2", b2);
    Input("c2", c2);
    Input("d2", d2);
    Output("y1", y1);
    Output("y2", y2);
}

void LS20::go(long t)
{
    begin(t);
    assert_signal("y1", !(input("a1") & input("b1") & input("c1") & input("d1")));
    assert_signal("y2", !(input("a2") & input("b2") & input("c2") & input("d2")));
    end();
}

// 74LS21 Dual 4-Input NAND Gate
//
//////////////////////////////////////////////////////////////////////

LS21::LS21(std::string label,
           Wire& a1, Wire& b1, Wire& c1, Wire& d1, Wire& y1, Wire& a2, Wire& b2, Wire& c2, Wire& d2, Wire& y2) : AsynchronousDevice(label)
{
    pd = 15;
    Input("a1", a1);
    Input("b1", b1);
    Input("c1", c1);
    Input("d1", d1);
    Input("a2", a2);
    Input("b2", b2);
    Input("c2", c2);
    Input("d2", d2);
    Output("y1", y1);
    Output("y2", y2);
}

void LS21::go(long t)
{
    begin(t);
    assert_signal("y1", (input("a1") & input("b1") & input("c1") & input("d1")));
    assert_signal("y2", (input("a2") & input("b2") & input("c2") & input("d2")));
    end();
}

// 74LS30 8-Input NAND Gate
//
//////////////////////////////////////////////////////////////////////

LS30::LS30(std::string label,
           Wire& a, Wire& b, Wire& c, Wire& d, Wire& e, Wire& f, Wire& g, Wire& h, Wire& y) : AsynchronousDevice(label)
{
    pd = 20;
    Input("a", a);
    Input("b", b);
    Input("c", c);
    Input("d", d);
    Input("e", e);
    Input("f", f);
    Input("g", g);
    Input("h", h);
    Output("y", y);
}

void LS30::go(long t)
{
    begin(t);
    assert_signal("y", !(input("a") & input("b") & input("c") & input("d") & input("e") & input("f") & input("g") & input("h")));
    end();
}

// 74LS32 Quad 2-input OR Gate
//
//////////////////////////////////////////////////////////////////////

LS32::LS32(std::string label,
        Wire& a1, Wire& b1, Wire& y1, Wire& a2, Wire& b2, Wire& y2,
        Wire& a3, Wire& b3, Wire& y3, Wire& a4, Wire& b4, Wire& y4) : AsynchronousDevice(label)
{
    pd = 15;
    Input("a1", a1); Input("b1", b1);
    Input("a2", a2); Input("b2", b2);
    Input("a3", a3); Input("b3", b3);
    Input("a4", a4); Input("b4", b4);
    Output("y1", y1);
    Output("y2", y2);
    Output("y3", y3);
    Output("y4", y4);
}

void LS32::go(long t)
{
    begin(t);
    assert_signal("y1", input("a1") | input("b1"));
    assert_signal("y2", input("a2") | input("b2"));
    assert_signal("y3", input("a3") | input("b3"));
    assert_signal("y4", input("a4") | input("b4"));
    end();
}

// 74LS244 Octal Buffer/Driver with 3-State Outputs
//
//////////////////////////////////////////////////////////////////////

LS244::LS244(std::string label, Wire& g1_bar, Wire& g2_bar,
        Wire& a1, Wire& a2, Wire& a3, Wire& a4, Wire& a5, Wire& a6, Wire& a7, Wire& a8,
        Wire& y1, Wire& y2, Wire& y3, Wire& y4, Wire& y5, Wire& y6, Wire& y7, Wire& y8) : AsynchronousDevice(label)
{
    pd = 30;
    Input("g1_bar", g1_bar); Input("g2_bar", g2_bar);
    Input("a1", a1); Input("a2", a2); Input("a3", a3); Input("a4", a4);
    Input("a5", a5); Input("a6", a6); Input("a7", a7); Input("a8", a8);
    Output("y1", y1); Output("y2", y2); Output("y3", y3); Output("y4", y4);
    Output("y5", y5); Output("y6", y6); Output("y7", y7); Output("y8", y8);
}

void LS244::go(long t)
{
    begin(t);

    if (!input("g1_bar"))
    {
        assert_signal("y1", input("a1"));
        assert_signal("y2", input("a2"));
        assert_signal("y3", input("a3"));
        assert_signal("y4", input("a4"));
    }
    else
    {
        assert_signal("y1", Logic(Z));
        assert_signal("y2", Logic(Z));
        assert_signal("y3", Logic(Z));
        assert_signal("y4", Logic(Z));
    }

    if (!input("g2_bar"))
    {     
        assert_signal("y5", input("a5"));
        assert_signal("y6", input("a6"));
        assert_signal("y7", input("a7"));
        assert_signal("y8", input("a8"));
        //if (devLabel=="mem2alulo_ext") cout<<t<<": mem2alulo_ext enabled and asserting"<<endl;
    }
    else
    {
        assert_signal("y5", Logic(Z));
        assert_signal("y6", Logic(Z));
        assert_signal("y7", Logic(Z));
        assert_signal("y8", Logic(Z));
        //if (devLabel=="mem2alulo_ext") cout<<t<<": mem2alulo_ext disabled and asserting ZZZ"<<endl;
    }

    end();
}

// 74LS245 Octal Bus Transciever with 3-State Outputs
//
//////////////////////////////////////////////////////////////////////

LS245::LS245(std::string label, Wire& g_bar, Wire& dir,
        Wire& a1, Wire& a2, Wire& a3, Wire& a4, Wire& a5, Wire& a6, Wire& a7, Wire& a8,
        Wire& b1, Wire& b2, Wire& b3, Wire& b4, Wire& b5, Wire& b6, Wire& b7, Wire& b8) : AsynchronousDevice(label)
{
    pd = 45;
    do_not_notify_self = true;
    Input("g_bar", g_bar); Input("dir", dir);

    Input("a1", a1); Input("a2", a2); Input("a3", a3); Input("a4", a4);
    Input("a5", a5); Input("a6", a6); Input("a7", a7); Input("a8", a8);

    Input("b1", b1); Input("b2", b2); Input("b3", b3); Input("b4", b4);
    Input("b5", b5); Input("b6", b6); Input("b7", b7); Input("b8", b8);

    Output("a1", a1); Output("a2", a2); Output("a3", a3); Output("a4", a4);
    Output("a5", a5); Output("a6", a6); Output("a7", a7); Output("a8", a8);

    Output("b1", b1); Output("b2", b2); Output("b3", b3); Output("b4", b4);
    Output("b5", b5); Output("b6", b6); Output("b7", b7); Output("b8", b8);
}

void LS245::go(long t)
{
    begin(t);

    if (!input("dir")) // b->a
    { 
        if (!input("g_bar")) 
        {            
            assert_signal("a1", input("b1"));
            assert_signal("a2", input("b2"));
            assert_signal("a3", input("b3"));
            assert_signal("a4", input("b4"));
            assert_signal("a5", input("b5"));
            assert_signal("a6", input("b6"));
            assert_signal("a7", input("b7"));
            assert_signal("a8", input("b8"));
            
            assert_signal("b1", Logic(Z));
            assert_signal("b2", Logic(Z));
            assert_signal("b3", Logic(Z));
            assert_signal("b4", Logic(Z));
            assert_signal("b5", Logic(Z));
            assert_signal("b6", Logic(Z));
            assert_signal("b7", Logic(Z));
            assert_signal("b8", Logic(Z));              
        }
        else
        {
            assert_signal("b1", Logic(Z));
            assert_signal("b2", Logic(Z));
            assert_signal("b3", Logic(Z));
            assert_signal("b4", Logic(Z));
            assert_signal("b5", Logic(Z));
            assert_signal("b6", Logic(Z));
            assert_signal("b7", Logic(Z));
            assert_signal("b8", Logic(Z));              
            
            assert_signal("a1", Logic(Z));
            assert_signal("a2", Logic(Z));
            assert_signal("a3", Logic(Z));
            assert_signal("a4", Logic(Z));
            assert_signal("a5", Logic(Z));
            assert_signal("a6", Logic(Z));
            assert_signal("a7", Logic(Z));
            assert_signal("a8", Logic(Z));            
        }
    }
    else // a->b
    {        
        if (!input("g_bar")) 
        { 
            assert_signal("b1", input("a1"));
            assert_signal("b2", input("a2"));
            assert_signal("b3", input("a3"));
            assert_signal("b4", input("a4"));
            assert_signal("b5", input("a5"));
            assert_signal("b6", input("a6"));
            assert_signal("b7", input("a7"));
            assert_signal("b8", input("a8"));
            
            assert_signal("a1", Logic(Z));
            assert_signal("a2", Logic(Z));
            assert_signal("a3", Logic(Z));
            assert_signal("a4", Logic(Z));
            assert_signal("a5", Logic(Z));
            assert_signal("a6", Logic(Z));
            assert_signal("a7", Logic(Z));
            assert_signal("a8", Logic(Z));             
        }
        else
        {
            assert_signal("a1", Logic(Z));
            assert_signal("a2", Logic(Z));
            assert_signal("a3", Logic(Z));
            assert_signal("a4", Logic(Z));
            assert_signal("a5", Logic(Z));
            assert_signal("a6", Logic(Z));
            assert_signal("a7", Logic(Z));
            assert_signal("a8", Logic(Z));  
                        
            assert_signal("b1", Logic(Z));
            assert_signal("b2", Logic(Z));
            assert_signal("b3", Logic(Z));
            assert_signal("b4", Logic(Z));
            assert_signal("b5", Logic(Z));
            assert_signal("b6", Logic(Z));
            assert_signal("b7", Logic(Z));
            assert_signal("b8", Logic(Z));          
        }              
    }

/*  if (!input("g_bar"))
    {
        if (!input("dir")) // b->a
        {
            assert_signal("b1", Logic(Z));
            assert_signal("b2", Logic(Z));
            assert_signal("b3", Logic(Z));
            assert_signal("b4", Logic(Z));
            assert_signal("b5", Logic(Z));
            assert_signal("b6", Logic(Z));
            assert_signal("b7", Logic(Z));
            assert_signal("b8", Logic(Z));

            assert_signal("a1", input("b1"));
            assert_signal("a2", input("b2"));
            assert_signal("a3", input("b3"));
            assert_signal("a4", input("b4"));
            assert_signal("a5", input("b5"));
            assert_signal("a6", input("b6"));
            assert_signal("a7", input("b7"));
            assert_signal("a8", input("b8"));
        }
        else // a->b
        {
            
            assert_signal("a1", Logic(Z));
            assert_signal("a2", Logic(Z));
            assert_signal("a3", Logic(Z));
            assert_signal("a4", Logic(Z));
            assert_signal("a5", Logic(Z));
            assert_signal("a6", Logic(Z));
            assert_signal("a7", Logic(Z));
            assert_signal("a8", Logic(Z));

            assert_signal("b1", input("a1"));
            assert_signal("b2", input("a2"));
            assert_signal("b3", input("a3"));
            assert_signal("b4", input("a4"));
            assert_signal("b5", input("a5"));
            assert_signal("b6", input("a6"));
            assert_signal("b7", input("a7"));
            assert_signal("b8", input("a8"));
        }
    }
    else
    {
        if (!input("dir")) // b->a
        {
            assert_signal("a1", Logic(Z));
            assert_signal("a2", Logic(Z));
            assert_signal("a3", Logic(Z));
            assert_signal("a4", Logic(Z));
            assert_signal("a5", Logic(Z));
            assert_signal("a6", Logic(Z));
            assert_signal("a7", Logic(Z));
            assert_signal("a8", Logic(Z));
        }
        else // a->b
        {
            assert_signal("b1", Logic(Z));
            assert_signal("b2", Logic(Z));
            assert_signal("b3", Logic(Z));
            assert_signal("b4", Logic(Z));
            assert_signal("b5", Logic(Z));
            assert_signal("b6", Logic(Z));
            assert_signal("b7", Logic(Z));
            assert_signal("b8", Logic(Z));
        }
    }
*/

    end();
}

// 74LS151 8-Line to 1-Line Data Selector/Multiplexer
//
//////////////////////////////////////////////////////////////////////

LS151::LS151(std::string label, Wire& e_bar, Wire& s0, Wire& s1, Wire& s2,
        Wire& i1, Wire& i2, Wire& i3, Wire& i4, Wire& i5, Wire& i6, Wire& i7, Wire& i8,
        Wire& z, Wire& z_bar) : AsynchronousDevice(label)
{
    pd = 43;
    Input("e_bar", e_bar);
    Input("s0", s0);
    Input("s1", s1);
    Input("s2", s2);
    Input("i1", i1);
    Input("i2", i2);
    Input("i3", i3);
    Input("i4", i4);
    Input("i5", i5);
    Input("i6", i6);
    Input("i7", i7);
    Input("i8", i8);
    Output("z", z);
    Output("z_bar", z_bar);
}

void LS151::go(long t)
{
    begin(t);
    Logic z_tmp;
    z_tmp = !input("e_bar") & ((!input("s2") & !input("s1") & !input("s0") & input("i1")) |
                               (!input("s2") & !input("s1") &  input("s0") & input("i2")) |
                               (!input("s2") &  input("s1") & !input("s0") & input("i3")) |
                               (!input("s2") &  input("s1") &  input("s0") & input("i4")) |
                               ( input("s2") & !input("s1") & !input("s0") & input("i5")) |
                               ( input("s2") & !input("s1") &  input("s0") & input("i6")) |
                               ( input("s2") &  input("s1") & !input("s0") & input("i7")) |
                               ( input("s2") &  input("s1") &  input("s0") & input("i8")));
    assert_signal("z", z_tmp);
    assert_signal("z_bar", !z_tmp);
    end();
}

// 74LS153 Dual 4-Line to 1-Line Data Selector/Multiplexer
//
//////////////////////////////////////////////////////////////////////

LS153::LS153(std::string label, Wire& e_bar, Wire& s0, Wire& s1,
        Wire& i1a, Wire& i2a, Wire& i3a, Wire& i4a, Wire& i1b, Wire& i2b, Wire& i3b, Wire& i4b,
        Wire& za, Wire& zb) : AsynchronousDevice(label)
{
    pd = 38;
    Input("e_bar", e_bar);
    Input("s0", s0);
    Input("s1", s1);
    Input("i1a", i1a);
    Input("i2a", i2a);
    Input("i3a", i3a);
    Input("i4a", i4a);
    Input("i1b", i1b);
    Input("i2b", i2b);
    Input("i3b", i3b);
    Input("i4b", i4b);
    Output("za", za);
    Output("zb", zb);
}

void LS153::go(long t)
{
    begin(t);
    assert_signal("za", !input("e_bar") & ( (input("i1a") & !input("s1") & !input("s0")) |
                                            (input("i2a") & !input("s1") &  input("s0")) |
                                            (input("i3a") &  input("s1") & !input("s0")) |
                                            (input("i4a") &  input("s1") &  input("s0")) ));
    assert_signal("zb", !input("e_bar") & ( (input("i1b") & !input("s1") & !input("s0")) |
                                            (input("i2b") & !input("s1") &  input("s0")) |
                                            (input("i3b") &  input("s1") & !input("s0")) |
                                            (input("i4b") &  input("s1") &  input("s0")) ));
    end();
}
