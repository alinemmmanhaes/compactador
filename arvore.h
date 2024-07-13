#ifndef arvore_h
#define arvore_h

#include <stdio.h>

typedef struct arvore Arvore;

Arvore* criaArvoreVazia();

Arvore* criaArvore(int freq, char c, Arvore* esq, Arvore* dir);

Arvore* liberaArvore(Arvore* a);

int ArvoreVazia(Arvore* a);

int folha(Arvore* a);

#endif