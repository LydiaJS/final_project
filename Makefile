CC = g++ -g -std=gnu++11
OBJS = Post.o OriginalPost.o Reply.o CacheManager.o PostStream.o PostBuf.o

Test: $(OBJS) Post.h OriginalPost.h Reply.h CacheManager.h
	$(CC) -o test test.cpp $(OBJS) -lcurl -ljsoncpp

CacheManager.o:
	$(CC) -c -o CacheManager.o CacheManager.cpp

Post.o:
	$(CC) -c -o Post.o Post.cpp

OriginalPost.o:
	$(CC) -c -o OriginalPost.o OriginalPost.cpp

Reply.o:
	$(CC) -c -o Reply.o Reply.cpp

PostStream.o:
	$(CC) -c -o PostStream.o PostStream.cpp

PostBuf.o:
	$(CC) -c -o PostBuf.o PostBuf.cpp


clean:
	rm $(OBJS) test *.json
