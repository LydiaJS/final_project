CC = g++ -g -Ofast -std=gnu++11

OBJS = Post.o \
	   OriginalPost.o \
	   Reply.o \
	   Catalog.o \
	   Thread.o

HEADERS = Post.h \
		  OriginalPost.h \
		  Reply.h \
		  Catalog.h \
		  Thread.h

%.o: %.cpp $(HEADERS)
	$(CC) -c $< -o ../build/$@

default: $(OBJS)
