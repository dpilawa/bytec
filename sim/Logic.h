/* 
 * 
 *    Logic.h - this file is part of CPU Simulator
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

enum logic_t {
    LO, // low logic state  (0)
    HI, // high logic state (1)
    Z,  // Hi-Z state       (2)
    X   // undefined state  (3)
};

// Interface for the Logic class.
//
//////////////////////////////////////////////////////////////////////

class Logic  
{
    logic_t p;
    logic_t getState() const;
public:
    Logic();
    Logic(logic_t q);
    Logic(const Logic& l);
    Logic(bool b);
    ~Logic();
    Logic& operator=(const Logic& q);
    bool   operator==(const Logic& q) const;
    bool   operator!=(const Logic& q) const;
    Logic  operator&(const Logic& q) const;
    Logic  operator|(const Logic& q) const;
    Logic  operator^(const Logic& q) const;
    Logic  operator!() const;
    operator bool() const;
    operator char() const;

    friend std::ostream& operator<<(std::ostream &stream, Logic l)
    {
        if (l.getState() == HI)
        {
            stream<<"HI";
        }
        else if (l.getState() == LO)
        {
            stream<<"LO";
        }
        else if (l.getState() == Z)
        {
            stream<<"Z";
        }
        else
        {
            stream<<"X";
        }
        return stream;
    }

};

// Interface for the Wire class.
//
//////////////////////////////////////////////////////////////////////

class Device;
class PowerSource;

class Wire
{
    std::map<Device*, std::map<long, Logic> > signal;
    std::vector<Device*> tx;
    std::vector<Device*> rx;
    bool nc;
public:
    Wire();
    ~Wire();
    void NC();
    Logic operator[](long t) const;
    Logic getRawSignal(long t, bool probing) const;
    bool assert_signal(Device* d, long t, Logic l);
    void attachTx(Device* d);
    void attachRx(Device* d);
    void detachRx(Device* d);
    bool risingEdge(long t) const;
    bool fallingEdge(long t) const;
    void getRxDevices(std::set<Device*>& devices);
};
    

// Interface for the Device class.
//
//////////////////////////////////////////////////////////////////////

class Device
{
    std::stack<std::set<Device*>*> notifyDevices;
    std::set<long> notify_times;
    std::stack<long> tpd;  // t after pd
    std::stack<long> tin;  // t before pd
protected:
    std::string devLabel;
    std::map<std::string, Wire*> inputs;
    std::map<std::string, Wire*> outputs;
    bool do_not_notify_self;    
    int pd;
    void begin(long t);
    void end();
public:
    Device(std::string label);
    virtual ~Device() = 0;
    std::string getLabel();
    void Output(std::string name, Wire& w);
    void assert_signal(std::string name, Logic l);
    void assert_signal(std::string name, char c);
    Logic input(std::string name);
    bool inputRisingEdge(std::string name);
    bool inputFallingEdge(std::string name);
    void notify(long t);
    virtual void go(long t) = 0;
};

class SynchronousDevice : public Device
{
public:
    SynchronousDevice(std::string label);
    virtual ~SynchronousDevice() = 0;
    void HotInput(std::string name, Wire& w);
    void Input(std::string name, Wire& w);
    virtual void debugInfo() = 0;
};

class AsynchronousDevice : public Device
{
public:
    AsynchronousDevice(std::string label);
    virtual ~AsynchronousDevice() = 0;
    void Input(std::string name, Wire& w);
    virtual void debugInfo(long t) = 0;
};

// Interface for the logic probe
//
//////////////////////////////////////////////////////////////////////

class Probe
{
    std::string probe_label;
    std::vector<Wire*> pins;
public:
    Probe(std::string label, Wire& w0);
    Probe(std::string label, Wire& w1, Wire& w0);
    Probe(std::string label, Wire& w4, Wire& w3, Wire& w2, Wire& w1, Wire& w0);
    Probe(std::string label, Wire& w7, Wire& w6, Wire& w5, Wire& w4, Wire& w3, Wire& w2, Wire& w1, Wire& w0);
    Probe(std::string label, Wire& w8, Wire& w7, Wire& w6, Wire& w5, Wire& w4, Wire& w3, Wire& w2, Wire& w1, Wire& w0);
    Probe(std::string label, Wire& w15, Wire& w14, Wire& w13, Wire& w12, Wire& w11, Wire& w10, Wire& w9, Wire& w8, Wire& w7, Wire& w6, Wire& w5, Wire& w4, Wire& w3, Wire& w2, Wire& w1, Wire& w0);
    Probe(std::string label, Wire& w16, Wire& w15, Wire& w14, Wire& w13, Wire& w12, Wire& w11, Wire& w10, Wire& w9, Wire& w8, Wire& w7, Wire& w6, Wire& w5, Wire& w4, Wire& w3, Wire& w2, Wire& w1, Wire& w0);
    Probe(std::string label, Wire& w31, Wire& w30, Wire& w29, Wire& w28, Wire& w27, Wire& w26, Wire& w25, Wire& w24, Wire& w23, Wire& w22, Wire& w21, Wire& w20, Wire& w19, Wire& w18, Wire& w17, Wire& w16, Wire& w15, Wire& w14, Wire& w13, Wire& w12, Wire& w11, Wire& w10, Wire& w9, Wire& w8, Wire& w7, Wire& w6, Wire& w5, Wire& w4, Wire& w3, Wire& w2, Wire& w1, Wire& w0);
    ~Probe();
    void debugInfo(long t);
    void debugInfoBit(long t);
    int getValue(long t);
};

}
