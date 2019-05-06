CC = g++
CFLAGS = -Wall -pedantic -std=c++11 -g3

include:
	$(CC) $(CFLAGS) -o main.out *.cpp
