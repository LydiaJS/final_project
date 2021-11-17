CC = g++ -g -std=gnu++11

OBJS = src/build/Post.o \
	   src/build/OriginalPost.o \
	   src/build/Reply.o \
	   src/build/CacheManager.o \
	   src/build/PostStream.o \
	   src/build/PostBuf.o

DEPS =  src/Posts/Post.h \
		src/Posts/OriginalPost.h \
		src/Posts/Reply.h \
		src/CacheManager/CacheManager.h

CacheManager:
	+$(MAKE) -C src/CacheManager

Posts:
	+$(MAKE) -C src/Posts

all:
	+$(MAKE) -C src/CacheManager
	+$(MAKE) -C Posts

test:
	+$(MAKE) -C src/CacheManager
	+$(MAKE) -C src/Posts
	$(CC) -o test src/test.cpp $(OBJS) $(DEPS) -lcurl -ljsoncpp

.PHONY: clean

clean:
	rm src/build/*.o test
