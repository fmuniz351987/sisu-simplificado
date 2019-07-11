#pragma once

class Curso: public List<Aluno> {
public:
    std::string nome;
    int max_alunos;
    int curso_id;

    Curso();

    Curso(std::string nome_, int max_alunos_);

    void print();

    void ler();

    float nota_corte();

    void append(Aluno* aluno);

    bool classificado(Aluno* aluno);
};
