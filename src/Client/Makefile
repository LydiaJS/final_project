CC = g++ -g -std=gnu++11

OBJS = Client.o

HEADERS = Client.h \
	      ../CacheManager/CacheManager.h \
		  ../ImageBoards/OriginalPost.h \
		  ../ImageBoards/Reply.h \
		  ../UI/PrintStream.h \
		  ../colors.h

%.o: %.cpp
	$(CC) -c $< -o ../build/$@

default: CLIENT
.PHONY: CLIENT

CLIENT: $(OBJS)
