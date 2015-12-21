OBJS = ALU.o Computer.o Control.o Devices.o Logic.o Memory.o Registers.o sim.o
CC = g++
DEBUG = -O3
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

sim : $(OBJS)
		$(CC) $(LFLAGS) $(OBJS) -o sim

ALU.o : ALU.cpp ALU.h
		$(CC) $(CFLAGS) ALU.cpp

Computer.o : Computer.cpp Computer.h Control.h Devices.h Memory.h Registers.h ALU.h
		$(CC) $(CFLAGS) Computer.cpp

Control.o : Control.cpp Control.h
		$(CC) $(CFLAGS) Control.cpp

Devices.o : Devices.cpp Devices.h
		$(CC) $(CFLAGS) Devices.cpp

Logic.o : Logic.cpp Logic.h
		$(CC) $(CFLAGS) Logic.cpp

Memory.o : Memory.cpp Memory.h
		$(CC) $(CFLAGS) Memory.cpp

Registers.o : Registers.cpp Registers.h
		$(CC) $(CFLAGS) Registers.cpp

sim.o : sim.cpp
		$(CC) $(CFLAGS) sim.cpp

clean:
		rm *.o sim



