OBJS_AS = as.tab.o lex.yy.o error.o verbose.o
OBJS_LD = ld.o error.o verbose.o
CC = cc
AS = as-b16
DEBUG = -O3
CFLAGS = -c $(DEBUG) -g -O0 -I.
CFLAGSDBG = -c $(DEBUG)
LFLAGS = $(DEBUG)

all: as ld crt0.o crt1.o

install: all
		ln -s -f `pwd`/as-b16 /usr/local/bin/as-b16
		ln -s -f `pwd`/ld-b16 /usr/local/bin/ld-b16
		ln -s -f `pwd`/crt0.o /usr/local/bin/crt0.o
		ln -s -f `pwd`/crt1.o /usr/local/bin/crt1.o

as.tab.c: as.y
		bison -v -d as.y
		
lex.yy.c: as.l
		flex as.l
		
as.tab.o: as.tab.c
		$(CC) $(CFLAGS) as.tab.c

lex.yy.o: lex.yy.c a.out.h
		$(CC) $(CFLAGS) lex.yy.c

error.o: error.c
		$(CC) $(CFLAGS) error.c

verbose.o: verbose.c
		$(CC) $(CFLAGS) verbose.c
		
as: $(OBJS_AS)
		$(CC) $(LFLAGS) $(OBJS_AS) -o as-b16

ld.o: ld.c
		$(CC) $(CFLAGS) ld.c

ld: $(OBJS_LD)
		$(CC) $(LFLAGS) $(OBJS_LD) -o ld-b16	

crt0.o: crt0.as as ld
		$(AS) crt0.as -o crt0.o

crt1.o: crt1.as as ld
		$(AS) crt1.as -o crt1.o

clean:
		rm *.o ld-b16 as-b16 as.output as.tab.c as.tab.h lex.yy.c
