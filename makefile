CC = g++
CFLAGS = -Wall -pedantic -std=c++11 -g3

include:
	$(CC) $(CFLAGS) -o lista.out lista.cpp
