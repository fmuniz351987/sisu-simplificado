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

Estudante* novo_estudante(char* nome, float nota, Estudante* proximo, Estudante *anterior) {
    Estudante *estudante;

    estudante = (Estudante*) malloc(sizeof(Estudante));
    estudante->nome = nome;
    estudante->nota = nota;
    estudante->proximo = proximo;
    estudante->anterior = anterior;
    return estudante;
}

ListaEstudantes* nova_lista() {
    Estudante *head;
    ListaEstudantes *lista;

    lista = (ListaEstudantes*) malloc(sizeof(ListaEstudantes));
    head = novo_estudante(NULL, 0, NULL, NULL);
    lista->head = head;
    lista->last = head;
    lista->length = 0;
    return lista;
}

void inserir_estudante(ListaEstudantes *lista, char *nome, float nota) {
    Estudante *estudante;

    estudante = novo_estudante(nome, nota);
    estudante->anterior = lista->last;
    lista->last->proximo = estudante;
    lista->length ++;
}

void imprimir_lista_de_nomes(ListaEstudantes *lista) {
    Estudante* proximo = lista->head;

    for(int i = 0; proximo->proximo != NULL; i++) {
        
    }
}

void deletar_estudante(Estudante *estudante) {
    free(estudante);
}

int main() {
    ListaEstudantes *lista;
    Estudante *estudante;

    lista = nova_lista();
    estudante = novo_estudante("Felipe", 4.2, NULL, NULL);
    deletar_estudante(estudante);
    return 0;
}
