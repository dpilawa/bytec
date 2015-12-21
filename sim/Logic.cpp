/* 
 * 
 *    Logic.cpp - this file is part of CPU Simulator
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

using namespace simulation;
using namespace std;
int recursion = 0;

// Implementation of the Logic class
//
//////////////////////////////////////////////////////////////////////

Logic::Logic() {
    p = X;
}

Logic::Logic(logic_t q) {
    p = q;
}

Logic::Logic(bool b) {
    if (b)
    {
        p = HI;
    }
    else
    {
        p = LO;
    }
}

Logic::Logic(const Logic& q)
{
    p = q.getState();
}

Logic::~Logic() {
}


Logic& Logic::operator=(const Logic& q) {
    if (this == &q) { // check for self assignment
        return *this;
    } else {
        p = q.getState();

        return *this;
    }
}
    

bool Logic::operator==(const Logic& q) const {
    if (p == q.getState()) {
        return true;
    } else {
        return false;
    }
}

bool Logic::operator!=(const Logic& q) const {
    if (p != q.getState()) {
        return true;
    } else {
        return false;
    }
}   

Logic Logic::operator&(const Logic& q) const {
    if (p == HI) 
    {
        if (q == Logic(HI)) return Logic(HI);
        else if (q.getState() == LO) return Logic(LO);
        else if (q.getState() == Z) return Logic(X);
        else if (q.getState() == X) return Logic(X);
    }
    else if (p == LO) 
    {
        if (q.getState() == HI) return Logic(LO);
        else if (q.getState() == LO) return Logic(LO);
        else if (q.getState() == Z) return Logic(LO);
        else if (q.getState() == X) return Logic(LO);   
    }
    else if (p == Z) 
    {
        if (q.getState() == HI) return Logic(X);
        else if (q.getState() == LO) return Logic(LO);
        else if (q.getState() == Z) return Logic(X);
        else if (q.getState() == X) return Logic(X);    
    }
    else if (p == X) 
    {
        if (q.getState() == HI) return Logic(X);
        else if (q.getState() == LO) return Logic(LO);
        else if (q.getState() == Z) return Logic(X);
        else if (q.getState() == X) return Logic(X);    
    }
    return Logic(X);
}

Logic Logic::operator|(const Logic& q) const {
    if (p == HI) 
    {
        if (q.getState() == HI) return Logic(HI);
        else if (q.getState() == LO) return Logic(HI);
        else if (q.getState() == Z) return Logic(HI);
        else if (q.getState() == X) return Logic(HI);
    }
    else if (p == LO) 
    {
        if (q.getState() == HI) return Logic(HI);
        else if (q.getState() == LO) return Logic(LO);
        else if (q.getState() == Z) return Logic(X);
        else if (q.getState() == X) return Logic(X);    
    }
    else if (p == Z) 
    {
        if (q.getState() == HI) return Logic(HI);
        else if (q.getState() == LO) return Logic(X);
        else if (q.getState() == Z) return Logic(X);
        else if (q.getState() == X) return Logic(X);    
    }
    else if (p == X) 
    {
        if (q.getState() == HI) return Logic(HI);
        else if (q.getState() == LO) return Logic(X);
        else if (q.getState() == Z) return Logic(X);
        else if (q.getState() == X) return Logic(X);    
    }
    return Logic(X);
}

Logic Logic::operator^(const Logic& q) const {
    if (p == HI) 
    {
        if (q.getState() == HI) return Logic(LO);
        else if (q.getState() == LO) return Logic(HI);
        else if (q.getState() == Z) return Logic(X);
        else if (q.getState() == X) return Logic(X);
    }
    else if (p == LO) 
    {
        if (q.getState() == HI) return Logic(HI);
        else if (q.getState() == LO) return Logic(LO);
        else if (q.getState() == Z) return Logic(X);
        else if (q.getState() == X) return Logic(X);    
    }
    else if (p == Z) 
    {
        if (q.getState() == HI) return Logic(X);
        else if (q.getState() == LO) return Logic(X);
        else if (q.getState() == Z) return Logic(X);
        else if (q.getState() == X) return Logic(X);    
    }
    else if (p == X) 
    {
        if (q.getState() == HI) return Logic(X);
        else if (q.getState() == LO) return Logic(X);
        else if (q.getState() == Z) return Logic(X);
        else if (q.getState() == X) return Logic(X);    
    }
    return Logic(X);
}

Logic Logic::operator!() const {
    if (p == HI) 
    {
        return Logic(LO);
    }
    else if (p == LO) 
    {
        return Logic(HI);
    }
    else 
    {
        return Logic(X);
    }
}

Logic::operator bool() const {
    if (p == HI)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Logic::operator char() const {
    if (p == HI)
    {
        return (char)1;
    }
    else
    {
        return (char)0;
    }
}

logic_t Logic::getState() const {
    return p;
}


// Implementation of the Wire class
//
//////////////////////////////////////////////////////////////////////

Wire::Wire()
{
    nc = false;
}

Wire::~Wire()
{
}

void Wire::NC()
{
    nc = true;
}

Logic Wire::getRawSignal(long t, bool probing) const
{

    if (nc)
    {
        return Logic(Z);
    }

    Logic lres, l;
    lres = Logic(Z);
    Device* d = NULL;
    
    std::map<Device*, map<long, Logic> >::const_iterator d_it;
    std::map<long, Logic>::const_iterator s_it;
    for (d_it = signal.begin(); d_it != signal.end(); d_it++)
    {
        s_it = (*d_it).second.upper_bound(t); // upper
        s_it--;
        //if (s_it != (*d_it).second.begin()) 
        //{
        //  s_it--;
        //}
        //else 
        //{
        //  return Logic(Z);
        //}
        l = (*s_it).second;
        if (l == Logic(HI))
        {
            if (lres == Logic(LO) || lres == Logic(HI)) 
            {
                if (probing)
                {
                    if (!nc) cout << "Error - two devices driving the same wire @" << t << ": " << d->getLabel() << ", " << (*d_it).first->getLabel() << endl;
                }
                return Logic(X);
            }
            else
            {
                d = (*d_it).first;
                lres = Logic(HI);
            }
        }
        else if (l == Logic(LO))
        {
            if (lres == Logic(LO) || lres == Logic(HI)) 
            {
                if (probing)
                {
                    if (!nc) cout << "Error - two devices driving the same wire @" << t << ": " << d->getLabel() << ", " << (*d_it).first->getLabel() << endl;
                }
                return Logic(X);
            }
            else
            {
                d = (*d_it).first;
                lres = Logic(LO);
            }
        }
        else if (l == Logic(X))
        {
            return Logic(X);
        }
        else
        {
            // Hi-Z state, do nothing
        }
    }

    return lres;

}
    
Logic Wire::operator[](long t) const
{

    Logic lres = getRawSignal(t, false);

    return lres;

}

bool Wire::assert_signal(Device* d, long t, Logic l)
{

    vector<Device*>::iterator d_it;
    for (d_it = tx.begin(); d_it!=tx.end() && (*d_it != d); d_it++);
    if (d_it == tx.end())
    {
        cout<<"Device not attached to wire cannot assert it"<<endl;
        exit(-1);
    }

    std::map<long, Logic>::const_iterator s_it;
    bool change_state_relevant = false;
    s_it = signal[d].upper_bound(t);
    s_it--;
    if ((*s_it).second != l)
    {
        change_state_relevant = true;   
        signal[d][t] = l;   
    }   
    return change_state_relevant;
}

void Wire::attachTx(Device* d)
{
    signal[d][(long)0] = Logic(Z);
    tx.push_back(d);
}

void Wire::attachRx(Device* d)
{
    if (!nc)
    {
        rx.push_back(d);
    }
}

void Wire::detachRx(Device* d)
{
    if (!nc)
    {
        for (vector<Device*>::iterator i=rx.begin(); i!=rx.end(); ++i)
        {
            if ((*i) == d)
            {
                rx.erase(i);
            }
        }
    }
}

bool Wire::risingEdge(long t) const
{
    if (t > 0)
    {
        if ( ((*this)[t] == Logic(HI)) && ((*this)[t-1] == Logic(LO)) )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool Wire::fallingEdge(long t) const
{
    if (t > 0)
    {
        if ( ((*this)[t] == Logic(LO)) && ((*this)[t-1] == Logic(HI)) )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

void Wire::getRxDevices(std::set<Device*>& devices)
{
    vector<Device*>::iterator it;
    for (it = rx.begin(); it != rx.end(); it++)
    {
        devices.insert(*it);
    }
}

// Implementation for the Device class
//
//////////////////////////////////////////////////////////////////////

Device::Device(std::string label) 
{
    devLabel = label;
    pd = 0;
    tin.push(0);
    tpd.push(0);
    do_not_notify_self = false;
};

Device::~Device() {};

std::string Device::getLabel()
{
    return devLabel;
}

void Device::Output(std::string name, Wire& w)
{
    outputs[name] = &w;
    w.attachTx(this);
}

void Device::assert_signal(std::string name, Logic l)
{
    Wire* w = NULL;
    bool found = false;
        
    map<std::string, Wire*>::const_iterator it;
    for (it = outputs.begin(); it != outputs.end() && !found; it++)
    {
        if (it->first == name) 
        {
            w = outputs[name];
            found = true;
        }
    }
    
    if (!found) 
    {
        cout << "Output " << name << " not found for device " << devLabel << endl;
        exit(-1);
    }
    else
    {
        if (w->assert_signal(this, tpd.top(), l))
        {
            // get all receiving devices to be notified
            w->getRxDevices(*notifyDevices.top());
        }
    }

}

void Device::assert_signal(std::string name, char c)
{
    if (c) 
    {
        assert_signal(name, Logic(HI));
    }
    else
    {
        assert_signal(name, Logic(LO));
    }
}

Logic Device::input(std::string name)
{
    Wire* w = NULL;
    bool found = false;

    map<std::string, Wire*>::const_iterator it;
    for (it = inputs.begin(); it != inputs.end() && !found; it++)
    {
        if ((*it).first == name) 
        {
            w = inputs[name];
            found = true;
        }
    }

    if (!found) 
    {
        cout << "Input " << name << " not found for device " << devLabel << endl;
        exit(-1);
    }
    else
    {
        Logic l = w->operator [](tin.top());
        if (l == Logic(Z))
        {
            return Logic(HI);   // unconnected inputs float to logic high
        }
        else {
            return l;
        }
    }

}

bool Device::inputRisingEdge(std::string name)
{
    bool found = false;
    Wire* w = NULL;
    
    map<std::string, Wire*>::const_iterator it;
    for (it = inputs.begin(); it != inputs.end() && !found; it++)
    {
        if (it->first == name) 
        {
            w = inputs[name];
            found = true;
        }
    }

    if (!found) 
    {
        cout << "Input " << name << " not found for device " << devLabel << endl;
        exit(-1);
    }
    else
    {
        return w->risingEdge(tin.top());
    }
}

bool Device::inputFallingEdge(std::string name)
{
    bool found = false;
    Wire* w = NULL;
    
    map<std::string, Wire*>::const_iterator it;
    for (it = inputs.begin(); it != inputs.end() && !found; it++)
    {
        if (it->first == name) 
        {
            w = inputs[name];
            found = true;
        }
    }

    if (!found) 
    {
        cout << "Input " << name << " not found for device " << devLabel << endl;
        exit(-1);
    }
    else
    {
        return w->fallingEdge(tin.top());
    }
}

void Device::begin(long t)
{
    recursion++;
    notifyDevices.push(new set<Device*>);
    tin.push(t);
    tpd.push(t+pd);
    //for (int i=0; i<=recursion; i++) cout<<" ";
    //cout<<devLabel<<" begin"<<endl;    
}

void Device::end()
{
    // notify all devices @ tpd
    set<Device*>::iterator it;

    //if (notifyDevices.top()->size()) 
    //{
    //  for (int i=0; i<=recursion; i++) cout<<" ";
    //  cout<<devLabel<<" notifying "<<notifyDevices.top()->size()<<" devices"<<endl;
    //}
        
    // notify all other devices attached to wires we have asserted, at all times >= tpd
    for (it = notifyDevices.top()->begin(); it != notifyDevices.top()->end(); it++)
    {
        
        // for (int i=0; i<=recursion; i++) cout<<" ";
        // cout<<tpd.top()<<"ns: "<<devLabel<<" notifying device "<<(*it)->devLabel<<endl;
        
        if ((devLabel=="mem2alulo_ext" && (*it)->getLabel()=="hitrcv") || (devLabel=="mem2alulo_ext" && (*it)->getLabel()=="lotrcv") || (devLabel=="hitrcv" && (*it)->getLabel()=="lotrcv") || (devLabel=="lotrcv" && (*it)->getLabel()=="hitrcv"))
        {
            // do nothing - this is just a nasty hack to avoid some MEMORY-ALU interface devices notifying each other and freezing the simulation
        }
        else if (!do_not_notify_self || (*it)!=this) 
        {
            (*it)->notify(tpd.top());
        }
    }
        
    //for (int i=0; i<=recursion; i++) cout<<" ";
    //cout<<devLabel<<" end"<<endl;   
    
    recursion--;
    delete notifyDevices.top();
    notifyDevices.pop();
    tpd.pop();
    tin.pop();
    
}

void Device::notify(long t)
{
    notify_times.insert(t);
    // recalculate device at all relevant times >= t
    std::set<long>::iterator it;
    for (it=notify_times.lower_bound(t); it!=notify_times.end(); it++)
    {
        this->go(*it);
    }
}

SynchronousDevice::SynchronousDevice(std::string label) : Device(label) {};
SynchronousDevice::~SynchronousDevice() {};

void SynchronousDevice::HotInput(std::string name, Wire& w)
{
    inputs[name] = &w;
    w.attachRx(this);
}

void SynchronousDevice::Input(std::string name, Wire& w)
{
    inputs[name] = &w;
}

AsynchronousDevice::AsynchronousDevice(std::string label) : Device(label) {};
AsynchronousDevice::~AsynchronousDevice() {};

void AsynchronousDevice::Input(std::string name, Wire& w)
{
    inputs[name] = &w;
    w.attachRx(this);
}

// Implementation for the logic probe
//
//////////////////////////////////////////////////////////////////////

Probe::Probe(std::string label, Wire& w0)
{
    probe_label = label;
    pins.push_back(&w0);
}

Probe::Probe(std::string label, Wire& w1, Wire& w0)
{
    probe_label = label;
    pins.push_back(&w0);
    pins.push_back(&w1);
}

Probe::Probe(std::string label, Wire& w4, Wire& w3, Wire& w2, Wire& w1, Wire& w0)
{
    probe_label = label;
    pins.push_back(&w0);
    pins.push_back(&w1);
    pins.push_back(&w2);
    pins.push_back(&w3);
    pins.push_back(&w4);
}

Probe::Probe(std::string label, Wire& w7, Wire& w6, Wire& w5, Wire& w4, Wire& w3, Wire& w2, Wire& w1, Wire& w0)
{
    probe_label = label;
    pins.push_back(&w0);
    pins.push_back(&w1);
    pins.push_back(&w2);
    pins.push_back(&w3);
    pins.push_back(&w4);
    pins.push_back(&w5);
    pins.push_back(&w6);
    pins.push_back(&w7);
}

Probe::Probe(std::string label, Wire& w8, Wire& w7, Wire& w6, Wire& w5, Wire& w4, Wire& w3, Wire& w2, Wire& w1, Wire& w0)
{
    probe_label = label;
    pins.push_back(&w0);
    pins.push_back(&w1);
    pins.push_back(&w2);
    pins.push_back(&w3);
    pins.push_back(&w4);
    pins.push_back(&w5);
    pins.push_back(&w6);
    pins.push_back(&w7);
    pins.push_back(&w8);
}


Probe::Probe(std::string label, Wire& w15, Wire& w14, Wire& w13, Wire& w12, Wire& w11, Wire& w10, Wire& w9, Wire& w8, Wire& w7, Wire& w6, Wire& w5, Wire& w4, Wire& w3, Wire& w2, Wire& w1, Wire& w0)
{
    probe_label = label;
    pins.push_back(&w0);
    pins.push_back(&w1);
    pins.push_back(&w2);
    pins.push_back(&w3);
    pins.push_back(&w4);
    pins.push_back(&w5);
    pins.push_back(&w6);
    pins.push_back(&w7);
    pins.push_back(&w8);
    pins.push_back(&w9);
    pins.push_back(&w10);
    pins.push_back(&w11);
    pins.push_back(&w12);
    pins.push_back(&w13);
    pins.push_back(&w14);
    pins.push_back(&w15);
}

Probe::Probe(std::string label, Wire& w16, Wire& w15, Wire& w14, Wire& w13, Wire& w12, Wire& w11, Wire& w10, Wire& w9, Wire& w8, Wire& w7, Wire& w6, Wire& w5, Wire& w4, Wire& w3, Wire& w2, Wire& w1, Wire& w0)
{
    probe_label = label;
    pins.push_back(&w0);
    pins.push_back(&w1);
    pins.push_back(&w2);
    pins.push_back(&w3);
    pins.push_back(&w4);
    pins.push_back(&w5);
    pins.push_back(&w6);
    pins.push_back(&w7);
    pins.push_back(&w8);
    pins.push_back(&w9);
    pins.push_back(&w10);
    pins.push_back(&w11);
    pins.push_back(&w12);
    pins.push_back(&w13);
    pins.push_back(&w14);
    pins.push_back(&w15);
    pins.push_back(&w16);
}
    
Probe::Probe(std::string label, Wire& w31, Wire& w30, Wire& w29, Wire& w28, Wire& w27, Wire& w26, Wire& w25, Wire& w24, Wire& w23, Wire& w22, Wire& w21, Wire& w20, Wire& w19, Wire& w18, Wire& w17, Wire& w16, Wire& w15, Wire& w14, Wire& w13, Wire& w12, Wire& w11, Wire& w10, Wire& w9, Wire& w8, Wire& w7, Wire& w6, Wire& w5, Wire& w4, Wire& w3, Wire& w2, Wire& w1, Wire& w0)
{
    probe_label = label;
    pins.push_back(&w0);
    pins.push_back(&w1);
    pins.push_back(&w2);
    pins.push_back(&w3);
    pins.push_back(&w4);
    pins.push_back(&w5);
    pins.push_back(&w6);
    pins.push_back(&w7);
    pins.push_back(&w8);
    pins.push_back(&w9);
    pins.push_back(&w10);
    pins.push_back(&w11);
    pins.push_back(&w12);
    pins.push_back(&w13);
    pins.push_back(&w14);
    pins.push_back(&w15);
    pins.push_back(&w16);
    pins.push_back(&w17);
    pins.push_back(&w18);
    pins.push_back(&w19);
    pins.push_back(&w20);
    pins.push_back(&w21);
    pins.push_back(&w22);
    pins.push_back(&w23);
    pins.push_back(&w24);
    pins.push_back(&w25);
    pins.push_back(&w26);
    pins.push_back(&w27);
    pins.push_back(&w28);
    pins.push_back(&w29);
    pins.push_back(&w30);
    pins.push_back(&w31);
}

Probe::~Probe()
{
    pins.clear();
}


void Probe::debugInfo(long t)
{
    int val = 0;
    int i = 0;
    vector<Wire*>::iterator it;

    cout << setw(12) << setfill(' ') << probe_label << ": ";

    for (it=pins.begin(); it<pins.end(); it++)
    {
        if ((*it)->getRawSignal(t, true) == Logic(Z))
        {
            cout << "Z" << endl;
            return;
        }
        if ((*it)->getRawSignal(t, true) == Logic(X))
        {
            cout << "X" << endl;
            return;
        }
        val = val + (int)((char)((*it)->getRawSignal(t, true))) * (int)pow(float(2), i++);
    }
    if (pins.size() > 1)
    {
        cout<<"0x" << hex << setfill('0') << setw( (int)ceil((float)pins.size() / 4.0) ) << val << dec;
    }
    else
    {
        cout << val;
    }
    cout<<endl;
}

int Probe::getValue(long t)
{
    int val = 0;
    int i = 0;
    vector<Wire*>::iterator it;

    for (it=pins.begin(); it<pins.end(); it++)
    {
        if ((*it)->getRawSignal(t, true) == Logic(Z))
        {
            return (int)-1;
        }
        if ((*it)->getRawSignal(t, true) == Logic(X))
        {
            return (int)-1;
        }
        val = val + (int)((char)((*it)->getRawSignal(t, true))) * (int)pow(float(2), i++);
    }

    return val;
    
}

void Probe::debugInfoBit(long t)
{
    vector<Wire*>::iterator it;

    for (it=pins.begin(); it<pins.end(); it++)
    {
        if ((*it)->getRawSignal(t, true) == Logic(Z))
        {
            cout << "Z";
        }
        else if ((*it)->getRawSignal(t, true) == Logic(X))
        {
            cout << "X";
        }
        else if ((*it)->getRawSignal(t, true) == Logic(HI))
        {
            cout << "*";
        }
        else
        {
            cout << " ";
        }
    }
}
