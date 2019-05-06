#include <iostream>
#include <sstream>
#include <iomanip>

#pragma once
// nao consegui separar o header file com template do arquivo cpp

template <class T>
class Node {
public:
    T *key;
    Node *next;

    Node() {
        key = NULL;
        next = NULL;
    }
    Node(T *key_) {
        key = key_;
        next = NULL;
    }
};

template <class T> 
class List {
    /* a escolha da implementação de classe usando template se deve ao fato de
    se desejar replicar o código de lista para mais de um tipo de dados, tanto
    a classe Aluno quanto a classe Curso (deseja-se ter uma lista de alunos e 
    uma de cursos). Inclusive, por esse motivo, foi escolhido C++ ao invés de C
    para implementação do projeto - reusabilidade e mais fácil manutenção. */
protected:
    int len;
    Node<T> *head;
    Node<T> *last;

public:
    List() {
        // inicia uma lista vazia
        len = 0;
        head = new Node<T>;
        last = head;
    }

    void append(T *node) {
        // insere um item ao final da lista
        Node<T> *n = new Node<T>(node);
        last->next = n;
        last = n;

        len++;
    }

    void print() {
        // imprime a lista chamando os métodos print() de cada item da lista
        Node<T> *current_node;
        current_node = head;

        while(current_node->next != NULL) {
            current_node = current_node->next;
            current_node->key->print();
        }
        std::cout << '\n';
    }

    int get_size() {
        return len;
    }

    Node<T>* get_node(int id) {
        // para uso interno apenas
        int i = 0;
        Node<T> *current_node = head;

        if(id > len || id < 0) throw std::invalid_argument("Index is out of bounds.");
        while(i < id) {
            current_node = current_node->next;
            i++;
        }
        return current_node;
    }

    T* get(int id) {
        /* retorna o id-ésimo item da lista (começando em 1). */
        if (id == 0) throw std::invalid_argument("Index is out of bounds.");
        return get_node(id)->key;
    }

    bool get_id(T* item, int *id_aluno) {
        /* dado um ponteiro, retorna o true e o id do ponteiro na lista, caso o elemento 
        exista, e false caso contrário. */
        Node<T> *n = head;
        int current_id = 0;

        while (n->next != NULL) {
            n = n->next;
            current_id++;
            if (n->key == item) {
                *id_aluno = current_id;
                return true;
            }
        }

        *id_aluno = 0;
        return false;
    }

    void insert_after_node(Node<T> *prev, T *item) {
        Node<T> *ins = new Node<T>(item);

        ins->next = prev->next;
        prev->next = ins;
        if (head == prev) head->next = ins;
        if (last == prev) last = ins;
        len++;
    }

    void insert(int id, T *node_to_insert) {
        /* Insere um item na id-ésima posição da lista, sendo 1 a primeira posição.
        O método get() é usado para pegar o item anterior a ele.*/
        Node<T> *previous_node = get_node(id-1);

        insert_after_node(previous_node, node_to_insert);
    }

    T* remove(int id) {
        /* Remove o id-ésimo item da lista e o retorna como ponteiro. */
        Node<T> *previous_node = get_node(id - 1);
        Node<T> *node_to_remove = previous_node->next;
        T *removed_item;
        if (node_to_remove == NULL) throw std::invalid_argument("Index is out of bounds.");

        previous_node->next = node_to_remove->next;
        if(head == previous_node) head->next = node_to_remove->next;
        if(id == len) last = previous_node;
        len--;
        removed_item = node_to_remove->key;
        delete node_to_remove;

        return removed_item;
    }

    bool remove_item(T* item) {
        /* retorna true se o item está na lista e false se não está; 
        o retorno do id é feito através da variável fornecida id.*/
        Node<T> *n = head;
        int current_id = 0;
        while(n->next != NULL) {
            n = n->next;
            current_id++;
            if(n->key == item) {
                remove(current_id);
                return true;
            }
        }
        return false;
    }

};
