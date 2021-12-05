CC = g++ -g -Ofast -std=gnu++11

OBJS = src/build/Post.o \
	   src/build/OriginalPost.o \
	   src/build/Reply.o \
	   src/build/Thread.o \
	   src/build/Catalog.o \
	   src/build/CacheManager.o \
	   src/build/PrintStream.o \
	   src/build/PrintBuf.o \
	   src/build/Client.o \
	   src/build/Interface.o \
	   src/build/HtmlToPlain.o

DEPS =  src/ImageBoards/Post.h \
		src/ImageBoards/OriginalPost.h \
		src/ImageBoards/Reply.h \
		src/ImageBoards/Thread.h \
		src/ImageBoards/Catalog.h \
		src/CacheManager/CacheManager.h \
		src/Client/Client.h \
		src/UI/Interface.h \
		src/Common/colors.h \
		src/Common/Target.h \
		src/UI/HtmlToPlain.h

CacheManager:
	+$(MAKE) -C src/CacheManager

ImageBoards:
	+$(MAKE) -C src/ImageBoards

UI:
	+$(MAKE) -C src/UI

Client:
	+$(MAKE) -C src/Client

tbb:
	+$(MAKE) -C src/CacheManager
	+$(MAKE) -C src/ImageBoards
	+$(MAKE) -C src/Client
	+$(MAKE) -C src/UI
	$(CC) -o tbb src/tbb.cpp $(OBJS) $(DEPS) -lcurl -ljsoncpp -lreadline

all:
	+$(MAKE) -C src/CacheManager
	+$(MAKE) -C src/ImageBoards
	+$(MAKE) -C src/Client
	+$(MAKE) -C src/UI
	$(CC) -o tbb src/tbb.cpp $(OBJS) $(DEPS) -lcurl -ljsoncpp -lreadline
	$(CC) -o test src/test.cpp $(OBJS) $(DEPS) -lcurl -ljsoncpp -lreadline

test:
	+$(MAKE) -C src/CacheManager
	+$(MAKE) -C src/ImageBoards
	+$(MAKE) -C src/Client
	+$(MAKE) -C src/UI
	$(CC) -o test src/test.cpp $(OBJS) $(DEPS) -lcurl -ljsoncpp -lreadline

default: TBB


clean:
	rm src/build/*.o test tbb
.PHONY: clean
