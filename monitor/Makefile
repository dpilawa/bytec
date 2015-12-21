AS=as-b16
ASFLAGS=
CC=lcc
CFLAGS=-c -A
HLFLAGS=-Wl-f -WlIHEX -Wl-d -Wl0x3000 -Wl-e -Wl0x10000 -Wl-v
ALFLAGS=-Wl-f -WlAOUT -Wl-d -Wl0x3000 -Wl-v
OBJS=main.o kernel.o mm.o pmem.o klibc.o shell.o util.o rtc.o rs232.o rs232i.o debug.o

all: amonitor hmonitor

amonitor: $(OBJS)
	$(CC) $(ALFLAGS) /usr/local/bin/crt1.o $(OBJS) -o monitor

hmonitor: $(OBJS)
	$(CC) $(HLFLAGS) /usr/local/bin/crt0.o /usr/local/bin/crt1.o $(OBJS) -o monitor.hex

main.o: main.c rs232.h
	$(CC) $(CFLAGS) main.c

kernel.o: kernel.c kernel.h
	$(CC) $(CFLAGS) kernel.c

mm.o: mm.c mm.h
	$(CC) $(CFLAGS) mm.c

pmem.o: pmem.c pmem.h
	$(CC) $(CFLAGS) pmem.c

klibc.o: klibc.c klibc.h
	$(CC) $(CFLAGS) klibc.c

shell.o: shell.c shell.h
	$(CC) $(CFLAGS) shell.c

util.o: util.as
	$(AS) $(ASFLAGS) util.as -o util.o    

rtc.o: rtc.c rtc.h
	$(CC) $(CFLAGS) rtc.c

rs232.o: rs232.c rs232.h
	$(CC) $(CFLAGS) rs232.c

rs232i.o: rs232i.m4
	m4 rs232i.m4 > rs232i.as    
	$(AS) $(ASFLAGS) rs232i.as -o rs232i.o
	rm rs232i.as

debug.o: debug.c
	$(CC) $(CFLAGS) debug.c

clean:
	rm *.o monitor.hex monitor


