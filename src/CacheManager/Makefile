CC = g++ -g -Ofast -std=gnu++11

%.o: %.cpp
	$(CC) -c $< -o ../build/$@

default: CacheManager
.PHONY: CacheManager

CacheManager: CacheManager.h
	$(CC) -c CacheManager.cpp -o ../build/CacheManager.o
