#include <iostream>
#include <sstream>
#include <iomanip>


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


class Aluno {
public:
    float nota;
    std::string nome;
    int primeira_opcao, segunda_opcao;

    Aluno() {
        nota = 0;
        nome = *new std::string;
    }

    Aluno(std::string nome_, float nota_) {
        nota = nota_;
        nome = nome_;
    }

    void print() {
        std::cout << nome << ' ' << nota << "\n";
    }

    bool ganha(Aluno *aluno, int curso) {
        if (nota > aluno->nota) return true;
        if (nota == aluno->nota && primeira_opcao == curso && aluno->primeira_opcao != curso) return true;
        return false;
    }

    void ler() {
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
};

class Curso: public List<Aluno> {
public:
    std::string nome;
    int max_alunos;
    int curso_id;

    Curso() {
        // construtor para HEAD apenas
        nome = "";
        max_alunos = 0;
    }

    Curso(std::string nome_, int max_alunos_) {
        nome = nome_;
        max_alunos = max_alunos_;
    }

    void print() {
        //imprime o nome do curso, nota de corte e lista de classificados / em espera
        std::cout << nome << " " << nota_corte() << "\n";
        Node<Aluno> *current_node;
        current_node = head;
        int i;

        // imprimindo classificados
        std::cout << "Classificados\n";
        for (i = 0; i < max_alunos && i < len; i++) {
            current_node = current_node->next;
            current_node->key->print();
        }

        // imprimindo lista de espera
        std::cout << "Lista de espera\n";
        for (; i < len; i++) {
            current_node = current_node->next;
            current_node->key->print();
        }
        std::cout << '\n';
    }

    void ler() {
        // lê duas linhas com o nome do curso e seu número de vagas
        std::string linha;

        std::getline(std::cin, nome);
        std::getline(std::cin, linha);
        std::sscanf(linha.c_str(), "%d", &max_alunos);
    }

    float nota_corte() {
        // retorna a nota mínima para aprovação no curso
        float nota;
        Node<Aluno> *n;

        n = head;
        for (int i = 0; i < max_alunos && i < len; i++) {
            n = n->next;
        }
        if (n->key == NULL) return 0;
        nota =  n->key->nota;
        return nota;
    }

    void append(Aluno* aluno) {
        /* sobrescrevendo o método de List: 
        insere um aluno de tal forma a manter a ordem de preferência, que é 
        dada por:
        - nota;
        - primeira opção;
        - primeiro a se inscrever.*/

        Node<Aluno> *node_atual = get_node(0);
        Aluno *prox_aluno;

        while(node_atual->next != NULL) {
            prox_aluno = node_atual->next->key;
            if (aluno->ganha(prox_aluno, curso_id)) {
                insert_after_node(node_atual, aluno);
                return;
            }
            node_atual = node_atual->next;
        }
        insert_after_node(last, aluno);
    }

    bool classificado(Aluno* aluno) {
        // retorna true ou false caso o aluno tenha se classificado no curso atual
        int id_aluno;
        if(!get_id(aluno, &id_aluno)) return false;
        return (id_aluno <= max_alunos && id_aluno > 0);
    }
};


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
