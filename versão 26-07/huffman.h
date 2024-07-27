#ifndef huffman_h
#define huffman_h

#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

typedef struct cel Cel;

typedef Cel Lista;

Lista *criaListaDeArvores(int *caracteres, int tam);

Lista *insereNaLista(Lista *l, Arvore *arv);

Lista *retiraInicioLista(Lista *l);

Lista *criaArvoreUnica(Lista *l);

Arvore* retornaArvoreLista(Lista* l);

void liberaLista(Lista* l);

#endif