CC = g++ -g -Ofast -std=gnu++11

OBJS = PrintBuf.o \
	   PrintStream.o \
	   Interface.o \
	   HtmlToPlain.o

HEADERS = PrintBuf.h \
		  PrintStream.h \
		  Interface.h \
		  HtmlToPlain.h

%.o: %.cpp
	$(CC) -c $< -o ../build/$@

default: UI
.PHONY: UI

UI: $(OBJS)
