# TP 1 de Estruturas de Dados (SISU Simplificado)
Aluno: Felipe Ribas Muniz

## Introdução
O algoritmo tem como objetivo receber uma lista de cursos com vagas limitadas e uma lista de candidatos, e retornar os candidatos aprovados e candidatos em espera ao final do processo. A implementação se deu através do tipo abstrato de dados de lista encadeada, tanto lista de candidatos quanto lista de cursos. Cada curso possui sua própria lista de alunos que foram aprovados ou não. Por simplicidade, os cursos inserem alunos já ordenados por quesito nota, opção e ordem de chegada, tornando desnecessário ordenar essas listas posteriormente.

## Implementação
O programa possui 4 classes essenciais: Node, List, Aluno e Curso. Node é uma classe simples que é usada para encadear as listas, e por isso não foi separada em seu próprio arquivo. Ela possui dois atributos: key e next, onde key aponta para uma instância de classe qualquer (template) e next aponta para o próximo node. A lista automatiza os processos de criar, deletar, obter e inserir nódulos, dado um objeto fornecido. A classe Aluno possui métodos para ler as entradas de alunos e comparar sua posição no ranking do curso, e a classe Curso herda diretamente de `Lista<Aluno>`, com algumas alterações: o comando `append()`, ao invés de inserir no último elemento da lista, insere os alunos na ordem apropriada, de acordo com suas notas e opções de curso.

Cada curso fornecido como input gerará uma lista de alunos; além disso, há uma lista central de alunos que não é ordenada por nota, mas apenas por ordem de inscrição. Por fim, há uma lista de cursos (lista de listas) usada para manter o controle de todos os cursos que foram fornecidos como input.

O programa começa lendo as informações de número de cursos e de alunos, e então lê os nomes e o número de vagas de cada curso; em seguida, lê os nomes e notas de todos os alunos; por fim, faz duas chamadas para remover quem passou direto e na primeira chamada, das listas de espera de seus cursos de segunda opção. Como os cursos já têm seus alunos inseridos na ordem, o método `print()` de cada curso já imprime as listas de classificados e de candidatos em espera. Cada nódulo da lista de cursos tem seu método `print()` invocado.

Alguns métodos foram implementados apenas como auxílio na depuração, como o método `print` usado na lista genérica List<T> quando T é do tipo Aluno. Esses métodos foram mantidos para reaproveitar o código Lista em projetos futuros.

Grande parte das escolhas de implementação se devem ao fato de eu ter um background maior em python; por conta disso, trabalhei com listas de forma a implementá-las o mais semelhantes possível com a forma como elas são implementadas em python. Além disso, como a passagem de argumentos em python é feita sempre por referência, busquei usar esse tipo de passagem na maior parte do tempo, salvo raras excessões, para evitar confusão. Busquei ao máximo tornar o código de lista reaproveitável, o que me levou a pesquisar sobre templates de classe, mas também me tornou incapacitado de separar o arquivo `lista.h` em dois (um header e um código-fonte). Preferi essa implementação um pouco mais confusa para que eu não tivesse que depurar duas listas idênticas (uma de Alunos e outra de Cursos) sempre que cometesse um erro na implementação delas, e por preferir uma orientação a objetos mais robustas. O uso de templates talvez não tenha sido a melhor solução, mas foi a mais simples que encontrei dado que estou mais acostumado a trabalhar com linguagens de tipagem fraca.

## Análise de complexidade
```c++
ler_primeira_linha(&n_cursos, &n_alunos);
ler_cursos_e_vagas(n_cursos, &lista_cursos);
ler_lista_alunos(n_alunos, &lista_alunos);
adicionar_alunos_aos_cursos(&lista_cursos, &lista_alunos);
remover_alunos_classificados_da_segunda_opcao(&lista_cursos, &lista_alunos);
remover_alunos_classificados_da_segunda_opcao(&lista_cursos, &lista_alunos);
lista_cursos.print();
```
Analisando a complexidade do código em relação a N (número de cursos) e M (número de alunos), temos as seguintes funções:
- `ler_primeira_linha` possui complexidade O(1), pois apenas lê uma linha e independe de M e N;
- `ler_cursos_e_vagas` itera sobre os N cursos e chama a função `append` (de complexidade O(1)) N vezes. Portanto, tem complexidade O(N).
- `ler_lista_alunos` itera sobre M alunos e chama a função `append` M vezes, portanto tem complexidade O(M).
- `adicionar_alunos_aos_cursos` passa por todos os M alunos e adiciona cada um à sua lista de classificados/espera duas vezes, uma para a primeira opção e outra para a segunda opção. Cada chamada buscando cada curso usa a função `get` na lista de cursos, que tem complexidade O(N). Cada inserção na lista de alunos do curso passa por um processo de busca do aluno que o antecede, de complexidade O(M). Tem, portanto, complexidade linear O(M²N).
- `remover_alunos_classificados_da_segunda_opcao` é chamada duas vezes e também tem a complexidade mais alta. Ela itera sobre a lista central de alunos, chamando a função `get()` M vezes, o que nos dá M² de complexidade. Além disso, ela chama a função `get()` da lista de cursos duas vezes por cada aluno (no pior dos casos), portanto `f(n) = 2NM²` e tem complexidade O(NM²).

A complexidade total do algoritmo é da ordem de O(NM²).

## Conclusão
É provável que exista uma solução mais eficiente do que a fornecida nesse trabalho, de complexidade menor do que a encontrada; no entanto, por falta de experiência com C++ e de tempo, busquei implementar a solução que fosse mais simples de ler e de escrever código, muitas vezes repetindo a função `get()` em um laço `for` sem necessidade, sendo que eu poderia iterar manualmente sobre os elementos da lista sem precisar dela. A função `get()` tem complexidade O(n), portanto, um laço `for` que passe pela lista usando `get` tem a desnecessária complexidade O(n²), sendo que podia simplesmente ser O(n). No entanto, em termos de legibilidade e de manutenção, é mais interessante e legível usar a função `get()` de uma lista sem iterar manualmente através de seus elementos, pois as funções implementadas na lista já foram testadas mais exaustivamente, são mais resilientes e evitam repetição de código (ctrl+c e ctrl+v), evitando a necessidade de depurar em dois lugares simultâneos. Dado um prazo maior, certamente seria melhor, em termos de eficiência, reduzir essa complexidade desnecessária.


## Bibliografia
https://www.tutorialspoint.com/cplusplus/cpp_templates.htm

https://www.tutorialspoint.com/cplusplus/cpp_inheritance.htm

https://www.tutorialspoint.com/cplusplus/cpp_polymorphism.htm

https://stackoverflow.com/questions/44774036/why-use-a-tpp-file-when-implementing-templated-functions-and-classes-defined-i

https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file

OBS.: Apesar de ter encontrado soluções para separar o header do código-fonte em classes que usam templates de classes, não consegui implementá-las localmente.
