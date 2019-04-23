#include <iostream>


class Node {
public:
    int key;
    Node *next;

    Node(int x) {
        key = x;
        next = NULL;
    }

    void print() {
        std::cout << key << '\n';
    }
};


class List {
public:
    Node *head;
    Node *last;
    int len;

    List() {
        len = 0;
        head = new Node(0);
        last = head;
    }

    void append(int key) {
        Node *new_node;
        new_node = new Node(key);
        last->next = new_node;
        last = new_node;

        len++;
    }

    void print() {
        Node *current_node;
        current_node = head;
        while(current_node->next != NULL) {
            current_node = current_node->next;
            current_node->print();
        }
        std::cout << '\n';
    }

    Node* get(int id) {
        int i = 0;
        Node *current_node = head;

        if(id > len || id < 0) throw std::invalid_argument("Index is out of bounds.");
        while(i < id) {
            current_node = current_node->next;
            i++;
        }
        return current_node;
    }

    void insert(int id, int key) {
        Node *node_to_insert = new Node(key);
        Node *previous_node = get(id - 1);
        
        node_to_insert->next = previous_node->next;
        previous_node->next = node_to_insert;

        len++;
    }

    void remove(int id) {
        Node *previous_node = get(id - 1);
        Node *node_to_remove = previous_node->next;
        if (node_to_remove == NULL) throw std::invalid_argument("Trying to delete a non-existant node.");

        previous_node->next = node_to_remove->next;
        delete node_to_remove;
        len--;
    }
};


int main() {
    List l;
    l.append(1);
    l.append(5);
    l.append(2);
    l.append(1);
    l.print();

    l.insert(3, 9);
    l.print();

    l.remove(5);
    l.print();
    
    std::cout << l.len << '\n';
}
