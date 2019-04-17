#include <stdlib.h>
#include <stdio.h>


typedef struct Estudante {
    char *nome;
    float nota;
    struct Estudante *proximo, *anterior;
} Estudante;

typedef struct ListaEstudantes {
    Estudante *head;
    Estudante *last;
    int length;
} ListaEstudantes;

ListaEstudantes* nova_lista() {
    ListaEstudantes *lista;

    lista = (ListaEstudantes*) malloc(sizeof(ListaEstudantes));
    lista->head = NULL;
    lista->last = NULL;
    lista->length = 0;
    return lista;
}

Estudante* novo_estudante(char* nome, float nota) {
    Estudante *estudante;

    estudante = (Estudante*) malloc(sizeof(Estudante));
    estudante->nome = nome;
    estudante->nota = nota;
    return estudante;
}

void deletar_estudante(Estudante *estudante) {
    free(estudante);
}

int main() {
    ListaEstudantes *lista;
    Estudante *estudante;

    lista = nova_lista();
    printf("%p %p %i \n", lista->head, lista->last, lista->length);
    estudante = novo_estudante("Felipe", 4.2);
    printf("%s %.2f\n", estudante->nome, estudante->nota);
    deletar_estudante(estudante);
    return 0;
}
