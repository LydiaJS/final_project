CC = g++ -g -O3 -std=gnu++11

%.o: %.cpp
	$(CC) -c $< -o ../build/$@

default: CacheManager
.PHONY: CacheManager

CacheManager: CacheManager.h
	$(CC) -c CacheManager.cpp -o ../build/CacheManager.o
