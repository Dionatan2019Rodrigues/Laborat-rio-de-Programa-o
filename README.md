# Laboratorio-de-Programacao

## 1º Semestre (2022)
Trabalhos desenvolvidos em Linguagem C.
- `T1` A partir de 3 dados a respeito de um triângulo (ângulos e comprimentos dos lados), calcula os 3 dados restantes e imprime.
- `T2` Jogo da velha disputado entre dois jogadores, com arquivo para guardar placar e tela gráfica em allegro.
```
$ gcc -Wall -o exemplo exemplo.c tela.c -lallegro_font -lallegro_color -lallegro_ttf -lallegro_primitives -lallegro 
```
- `T3` Jogo em que o usuário deve matar as palavras que o jogo apresenta, digitando-as. Exemplos([typing attack](https://www.typinggames.zone/typingattack) ou [falling words](https://www.typingstudy.com/pt-brazilian_abnt-2/games/falling_words)).**INCOMPLETO**

## 2º Semestre (2022)
Trabalhos desenvolvidos em Linguagem C++.
- `T1` Recebe os lados de um triângulo da entrada e imprimir o tipo do triângulo(escaleno/equilatero/isosceles) ou valores inválidos.
- `T2` Recebe um campo com minas e imprime o campo com os números de minas adjacentes.
- `T3` Simula aportes e resgates em um plano de previdência simplificado.
- `T4` Implementação de uma planilha de números inteiros que suporta referências a outras células e operações aritméticas. Uma célula pode ter um valor `int` ou uma fórmula matemática iniciando com `=`.
```
$ g++ -Wall -std=c++11 -o calc calculadora.cpp 
```
- `T5` Dado um conjunto de números de uma árvore binária de busca(ABB) em percurso pré-ordem, o objetivo deste trabalho é encontrar o percurso pós-ordem da ABB.
```
$ g++ -Wall -std=c++11 arvore.cpp  
```
- `T6` Dado um conjunto de números para inserção em uma ABB AVL, complete as funções do trabalho para verificação com TDD(Test Driven Development) com o framework C++ [Catch2](https://github.com/catchorg/Catch2/tree/v2.x).
```
$ g++ -Wall -std=c++11 arvore.cpp 
```
