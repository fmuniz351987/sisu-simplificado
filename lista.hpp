#include <iostream>
#include <sstream>
#include <iomanip>

#pragma once

template <class T>
class Node {
public:
    T *key;
    Node *next;

    Node();

    Node(T *key_);
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
    List();

    void append(T *node);

    void print();

    int get_size();

    Node<T>* get_node(int id);

    T* get(int id);

    bool get_id(T* item, int *id_aluno);

    void insert_after_node(Node<T> *prev, T *item);

    void insert(int id, T *node_to_insert);

    T* remove(int id);

    bool remove_item(T* item);
};

#include "lista.tpp"
