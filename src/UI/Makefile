CC = g++ -g -std=gnu++11

OBJS = PrintBuf.o \
	   PrintStream.o

HEADERS = PrintBuf.h \
		  PrintStream.h

%.o: %.cpp
	$(CC) -c $< -o ../build/$@

default: UI
.PHONY: UI

UI: $(OBJS)
