CC = g++
CFLAGS = -Wall -pedantic -std=c++11 -g3

biblioteca: main.o aluno.o curso.o
	$(CC) $(CFLAGS) -o biblioteca main.o aluno.o curso.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

aluno.o: aluno.cpp aluno.hpp
	$(CC) $(CFLAGS) -c aluno.cpp

curso.o: lista.tpp lista.hpp aluno.cpp aluno.hpp curso.cpp curso.hpp
	$(CC) $(CFLAGS) -c curso.cpp

clean:
	rm biblioteca main.o aluno.o curso.o