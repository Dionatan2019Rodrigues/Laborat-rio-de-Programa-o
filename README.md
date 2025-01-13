# Laboratorio de Programação
<p style="text-align: justify; text-indent: 20px;">Disciplina do curso de Ciência da Computação com objetivo de introduzir o aluno a linguagens de programação através da linguagem C e C++.</p> 

### 1º Semestre (2022)
Neste primeiro semestre os trabalhos foram desenvolvidos em Linguagem C.
- `T_I` A partir de 3 dados a respeito de um triângulo (ângulos e comprimentos dos lados), calcula os 3 dados restantes e imprime.
- `T_II` Jogo da velha disputado entre dois jogadores, com arquivo para guardar placar e tela gráfica em allegro.
- `T_III` Jogo em que o usuário deve matar as palavras que o jogo apresenta, digitando-as. Exemplo ([typing attack](https://www.typinggames.zone/typingattack)).

## 2º Semestre (2022)
Neste semestre os trabalhos ja foram desenvolvidos em Linguagem C++.
- `t1` Recebe os lados de um triângulo da entrada e imprimir o tipo do triângulo(escaleno/equilatero/isosceles) ou valores inválidos.
- `t2` Recebe um campo com minas e imprime o campo com os números de minas adjacentes.
- `t3` Simula aportes e resgates em um plano de previdência simplificado.
- `t4` Implementação de uma planilha de números inteiros que suporta referências a outras células e operações aritméticas. Uma célula pode ter um valor `int` ou uma fórmula matemática iniciando com `=`.
- `t5` Dado um conjunto de números de uma árvore binária de busca(ABB) em percurso pré-ordem, o objetivo deste trabalho é encontrar o percurso pós-ordem da ABB.
- `t6` Dado um conjunto de números para inserção em uma ABB AVL, foram desenvolvidas funções para verificação com TDD(Test Driven Development) com o framework C++ [Catch2](https://github.com/catchorg/Catch2/tree/v2.x).
- `t7`  Este trabalho consiste na implementação de caminhos mínimos com o algoritmo de
Dijkstra (ver [aqui](https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/dijkstra.html) e [aqui](https://www.freecodecamp.org/news/dijkstras-shortest-path-algorithm-visual-introduction/)) em um grafo não-direcionado, com pesos nas arestas e com listas de
adjacência. Foram desenvolvidas funções para verificação com TDD(Test Driven Development) com o framework C++ [Catch2](https://github.com/catchorg/Catch2/tree/v2.x).

### Executar arquivos em c++
A pedido do professor da disciplina todos arquivos deveriam ser executados com a seguinte linha de comando no terminal.
```
$ g++ -Wall -std=c++11 arquivo.cpp  
```
