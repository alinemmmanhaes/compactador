#ifndef huffman_h
#define huffman_h

#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

typedef struct cel Cel;

typedef Cel Lista;

/*
Cria uma lista de árvores, com uma árvore para cada caracter do vetor passado como parâmetro.
Os nós são inseridos na lista de acordo com o número de ocorrências de seus caracteres, 
retornando a lista já ordenada;
*/
Lista *criaListaDeArvores(int *caracteres, int tam);

/*
A árvore recebida como parâmetro é inserida na lista de acordo com a frêquencia de seu caracter,
de forma que a lista sempre estará odenada começando pela árvore com caracter de menor frequência 
até a com o de maior frequência;
*/
Lista *insereNaLista(Lista *l, Arvore *arv);

/*
A lista tem sua primeira célula retirada e é retornada atualizada;
*/
Lista *retiraInicioLista(Lista *l);

/*
Função que, a partir da lista de árvores irá gerar uma arvóre única, que se tornará no final do
processo a única célula da lista. Dentro de um loop, os dois primeiros nós da lista seráo retirados e 
inseridos como nós filhos de uma nova ávrore, que será colocada de volta na lista. Esse processo irá se repetir 
até que haja apenas uma célula na lista
*/
Lista *criaArvoreUnica(Lista *l);

/*
Retorna a árvore da lista recebida como parâmetro;
*/
Arvore* retornaArvoreLista(Lista* l);

/*
Libera todas as células da lista;
*/
void liberaLista(Lista* l);

#endif