#pragma once

class Aluno {
public:
    float nota;
    std::string nome;
    int primeira_opcao, segunda_opcao;

    Aluno();

    Aluno(std::string nome_, float nota_);

    void print();

    bool ganha(Aluno *aluno, int curso);

    void ler();
};
