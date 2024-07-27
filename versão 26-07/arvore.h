#ifndef arvore_h
#define arvore_h

#include <stdio.h>
#include "bitmap.h"

#define ESQ 0
#define DIR 1

typedef struct arvore Arvore;

Arvore* criaArvoreVazia();

Arvore* criaArvore(int freq, unsigned char c, Arvore* esq, Arvore* dir);

Arvore* liberaArvore(Arvore* a);

int arvoreVazia(Arvore* a);

int ehFolha(Arvore* a);

int retornaFrequencia(Arvore* a);

unsigned char retornaCaracter(Arvore* a);

Arvore* retornaArvoreEsq(Arvore* a);

Arvore* retornaArvoreDir(Arvore* a);

unsigned int alturaArvore(Arvore* a);

Arvore* percorreArvoreBM(Arvore* a, bitmap* bm, unsigned int tam, int bit);

void escreveBinario(Arvore* a, FILE* pTexto, FILE* pBin, bitmap** bm);

void leBinario(Arvore* a, FILE* pTexto, FILE* pBin, bitmap** bm);

bitmap* retornaBMChar(Arvore* a, unsigned char c);

void decodifica(Arvore* a, FILE* pTexto, bitmap** bm, int* totalLength, int* index, int* i);

void imprime(Arvore *a);

void escreveArvoreBM(Arvore* a, bitmap* bm);

void escreveArvoreBinario(Arvore* a, bitmap* bm, FILE* pBin);

void leArvoreB(Arvore* a, bitmap* bm, FILE* pBin);

#endif