OBJS = Microcode.o Parser.o Lexer.o main.o
CC = g++
DEBUG =
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

ucasm : $(OBJS)
		$(CC) $(LFLAGS) $(OBJS) -o ucasm

Microcode.o : Microcode.cpp Microcode.h tokens.h
		$(CC) $(CFLAGS) Microcode.cpp

Parser.o : Parser.cpp Parser.h tokens.h
		$(CC) $(CFLAGS) Parser.cpp

Lexer.o : Lexer.cpp Lexer.h tokens.h
		$(CC) $(CFLAGS) Lexer.cpp

main.o : main.cpp tokens.h
		$(CC) $(CFLAGS) main.cpp

clean:
		rm *.o ucasm



