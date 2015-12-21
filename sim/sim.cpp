/* 
 * 
 *    sim.cpp - this file is part of CPU Simulator
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
#include "Registers.h"
#include "Memory.h"
#include "ALU.h"
#include "Computer.h"

using namespace std;
using namespace simulation;


int main(int argc, char* argv[])
{

    Computer *c = new Computer("cpu", 4.000, 20000);
    c->go(-1);
    delete c;

    return 0;
    
}

