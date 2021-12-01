CC = g++ -g -std=gnu++11

OBJS = src/build/Post.o \
	   src/build/OriginalPost.o \
	   src/build/Reply.o \
	   src/build/Thread.o \
	   src/build/Catalog.o \
	   src/build/CacheManager.o \
	   src/build/PrintStream.o \
	   src/build/PrintBuf.o \
	   src/build/Client.o

DEPS =  src/ImageBoards/Post.h \
		src/ImageBoards/OriginalPost.h \
		src/ImageBoards/Reply.h \
		src/ImageBoards/Thread.h \
		src/ImageBoards/Catalog.h \
		src/CacheManager/CacheManager.h \
		src/Client/Client.h \
		src/Common/colors.h \
		src/Common/Target.h

CacheManager:
	+$(MAKE) -C src/CacheManager

ImageBoards:
	+$(MAKE) -C src/ImageBoards

UI:
	+$(MAKE) -C src/UI

Client:
	+$(MAKE) -C src/Client
all:
	+$(MAKE) -C src/CacheManager
	+$(MAKE) -C src/ImageBoards
	+$(MAKE) -C src/Client
	+$(MAKE) -C src/UI

test:
	+$(MAKE) -C src/CacheManager
	+$(MAKE) -C src/ImageBoards
	+$(MAKE) -C src/Client
	+$(MAKE) -C src/UI
	$(CC) -o test src/test.cpp $(OBJS) $(DEPS) -lcurl -ljsoncpp -lreadline

.PHONY: clean

clean:
	rm src/build/*.o test
