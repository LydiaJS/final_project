CC = g++ -g -O3 -std=gnu++11

OBJS = PrintBuf.o \
	   PrintStream.o \
	   Interface.o

HEADERS = PrintBuf.h \
		  PrintStream.h \
		  Interface.h

%.o: %.cpp
	$(CC) -c $< -o ../build/$@

default: UI
.PHONY: UI

UI: $(OBJS)
