#ifndef binario_h
#define binario_h

#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"
#include "arvore.h"

/**/
bitmap** escreveBinario(Arvore* a, FILE* pTexto, FILE* pBin, bitmap** bm, int* nBitMap);

/**/
bitmap** leBinario(Arvore* a, FILE* pTexto, FILE* pBin, bitmap** bm, int* nBitMap);

/**/
void escreveArvoreBinario(Arvore* a, bitmap* bm, FILE* pBin);

/**/
void leArvoreBinario(Arvore* a, bitmap* bm, FILE* pBin);

#endif