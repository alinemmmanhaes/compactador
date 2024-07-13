#ifndef huffman_h
#define huffman_h

#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

typedef struct lista Lista;

Lista *criaListaDeArvores(int *caracteres, int tam);

//função de inserir de acordo com a frequencia, pra já ficar a lista ordenada, e pra poder usar na hora de implementar 
//o algoritmo de huffman(função de criar a arvore unica)

//função de retirar da lista

void ordenaListaDeArvores(Lista *l, int tam);

void criaArvoreUnica(Lista *l);

#endif