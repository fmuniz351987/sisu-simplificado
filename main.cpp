#include <iostream>
#include <sstream>
#include <iomanip>


void ler_primeira_linha(int* n_cursos, int* n_alunos) {
    std::string linha;

    std::getline(std::cin, linha);
    std::sscanf(linha.c_str(), "%d %d", n_cursos, n_alunos);
}

void ler_cursos_e_vagas(int n_cursos, List<Curso> *lista_cursos) {
    Curso *curso_atual;

    for (int i=1; i<=n_cursos; i++) {
        curso_atual = new Curso;
        curso_atual->ler();
        curso_atual->curso_id = i;
        lista_cursos->append(curso_atual);
    }
}

void ler_lista_alunos(int n_alunos, List<Aluno> *lista_alunos) {
    Aluno *aluno_atual;

    for (int i=0; i<n_alunos; i++) {
        aluno_atual = new Aluno;
        aluno_atual->ler();
        lista_alunos->append(aluno_atual);
    }
}

void adicionar_alunos_aos_cursos(List<Curso> *lista_cursos, List<Aluno> *lista_alunos) {
    Curso *curso;
    Aluno *aluno;

    for (int i = 1; i <= lista_alunos->get_size(); i++) {
        aluno = lista_alunos->get(i);
        curso = lista_cursos->get(aluno->primeira_opcao);
        curso->append(aluno);
        curso = lista_cursos->get(aluno->segunda_opcao);
        curso->append(aluno);
    }
}

void remover_alunos_classificados_da_segunda_opcao(List<Curso> *lista_cursos, List<Aluno> *lista_alunos) {
    Aluno *aluno;
    Curso *primeira_op, *segunda_op;

    for (int i = 1; i<= lista_alunos->get_size(); i++) {
        aluno = lista_alunos->get(i);
        primeira_op = lista_cursos->get(aluno->primeira_opcao);
        if (primeira_op->classificado(aluno)) {
            segunda_op = lista_cursos->get(aluno->segunda_opcao);
            segunda_op->remove_item(aluno);
        }
    }
}

int main() {
    int n_cursos, n_alunos;
    List<Curso> lista_cursos;
    List<Aluno> lista_alunos;
    Aluno teste;

    std::cout << std::fixed;
    std::cout << std::setprecision(2);

    ler_primeira_linha(&n_cursos, &n_alunos);
    ler_cursos_e_vagas(n_cursos, &lista_cursos);
    ler_lista_alunos(n_alunos, &lista_alunos);
    adicionar_alunos_aos_cursos(&lista_cursos, &lista_alunos);
    remover_alunos_classificados_da_segunda_opcao(&lista_cursos, &lista_alunos);
    remover_alunos_classificados_da_segunda_opcao(&lista_cursos, &lista_alunos);
    lista_cursos.print();
}
