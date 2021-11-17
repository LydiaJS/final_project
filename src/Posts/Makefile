CC = g++ -g -std=gnu++11

OBJS = Post.o \
	   OriginalPost.o \
	   Reply.o \
	   PostStream.o \
	   PostBuf.o

HEADERS = Post.h \
		  OriginalPost.h \
		  Reply.h \
		  PostStream.h \
		  PostBuf.h

%.o: %.cpp $(HEADERS)
	$(CC) -c $< -o ../build/$@

default: $(OBJS)
