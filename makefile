CC = gcc
CFLAGS = -Wall -pedantic -std=c11

include:
	$(CC) $(CFLAGS) -o lista_estudantes.out lista_estudantes.c
