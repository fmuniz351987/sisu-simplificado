#include <iostream>
#include <sstream>
#include <iomanip>


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
