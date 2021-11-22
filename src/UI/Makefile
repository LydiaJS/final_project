CC = g++ -g -std=gnu++11

OBJS = Console.o \
	   PrintBuf.o \
	   PrintStream.o

HEADERS = Console.h \
		  PrintBuf.h \
		  PrintStream.h

%.o: %.cpp
	$(CC) -c $< -o ../build/$@

default: UI
.PHONY: UI

UI: $(OBJS)
