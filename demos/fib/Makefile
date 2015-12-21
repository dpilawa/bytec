AS=as-b16
ASFLAGS=
CC=lcc
CFLAGS=-c
LFLAGS=-Wl-f -WlIHEX -Wl-d -Wl0x3000 -Wl-e -Wl0x10000 -v

all: monitor

monitor: main.o crt0.o
	$(CC) $(LFLAGS) crt0.o main.o -o main.hex

main.o: main.c
	$(CC) $(CFLAGS) main.c

crt0.o: crt0.as
	$(AS) $(ASFLAGS) crt0.as -o crt0.o

