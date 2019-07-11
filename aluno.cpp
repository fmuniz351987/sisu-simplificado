#include <iostream>
#include <sstream>
#include <iomanip>

#include "aluno.hpp"

Aluno::Aluno() {
    nota = 0;
    nome = *new std::string;
}

Aluno::Aluno(std::string nome_, float nota_) {
    nota = nota_;
    nome = nome_;
}

void Aluno::print() {
    std::cout << nome << ' ' << nota << "\n";
}

bool Aluno::ganha(Aluno *aluno, int curso) {
    if (nota > aluno->nota) return true;
    if (nota == aluno->nota && primeira_opcao == curso && aluno->primeira_opcao != curso) return true;
    return false;
}

void Aluno::ler() {
    /* lê as duas linhas, que devem estar no formato esperado:
    Nome Do Aluno
    <nota> <primeira_opcao> <segunda_opcao> ... */

    std::string linha;
    std::istringstream iss;

    std::getline(std::cin, nome);
    std::getline(std::cin, linha);
    iss = std::istringstream(linha);

    iss >> nota;
    iss >> primeira_opcao;
    iss >> segunda_opcao;

    // corrigindo indice inicial i=1 ao inves de 0
    primeira_opcao++;
    segunda_opcao++;
}
