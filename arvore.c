#include <stdlib.h>
#include "arvore.h"

struct arvore{
    short int freq;
    unsigned char c;
    bitmap* bm;
    Arvore* esq;
    Arvore* dir;
};

Arvore* criaArvoreVazia(){
    return NULL;
}

Arvore* criaArvore(short int freq, unsigned char c, Arvore* esq, Arvore* dir){
    Arvore* arv = malloc(sizeof(Arvore));
    arv->freq = freq;
    arv->c = c;
    arv->bm = NULL;
    arv->esq = esq;
    arv->dir = dir;

    return arv;
}

Arvore* liberaArvore(Arvore* a){
    if(!arvoreVazia(a)){
        liberaArvore(a->esq);
        liberaArvore(a->dir);
        bitmapLibera(a->bm);
        free(a);
    }
    return NULL;
}

int arvoreVazia(Arvore* a){
    return a == NULL;
}

int ehFolha(Arvore* a){
    return (arvoreVazia(a->esq) && arvoreVazia(a->dir));
}

short int retornaFrequencia(Arvore* a){
    return a->freq;
}

unsigned char retornaCaracter(Arvore* a){
    return a->c;
}

Arvore* retornaArvoreEsq(Arvore* a){
    return a->esq;
}

Arvore* retornaArvoreDir(Arvore* a){
    return a->dir;
}

unsigned int alturaArvore(Arvore* a){
    unsigned int n1 = 0, n2 = 0;
    if(arvoreVazia(a)) return 0;

    if(arvoreVazia(a->esq) && arvoreVazia(a->dir)) return 0;

    n1 = 1 + alturaArvore(a->esq);
    n2 = 1 + alturaArvore(a->dir);

    return (n1>n2)?n1:n2;
}

Arvore* percorreArvoreBM(Arvore* a, bitmap* bm, unsigned int tam, int bit){
    if(a == NULL){
        return a;
    }
    bitmap* bm_novo = bitmapInit(tam);
    if(bm){
        for(int i=0; i<bitmapGetLength(bm); i++){
            bitmapAppendLeastSignificantBit(bm_novo, bitmapGetBit(bm, i));
        }
        bitmapAppendLeastSignificantBit(bm_novo, bit);
    }

    if(ehFolha(a)){
        a->bm = bm_novo;
        return a;
    }

    a->esq = percorreArvoreBM(a->esq, bm_novo, tam, ESQ);
    a->dir = percorreArvoreBM(a->dir, bm_novo, tam, DIR);

    return a;
}

void escreveBinario(Arvore* a, FILE* pTexto, FILE* pBin, bitmap* bm){
    unsigned char c;
    bitmap* bm_aux;
    while(fread(&c, sizeof(unsigned char), 1, pTexto) == 1){
        bm_aux = retornaBMChar(a, c);
        for(int i=0; i<bitmapGetLength(bm_aux); i++){
            unsigned char bit = bitmapGetBit(bm_aux, i);
            bitmapAppendLeastSignificantBit(bm, bit);
        }
    }
    unsigned int length = bitmapGetLength(bm);
    fwrite(&length, sizeof(unsigned int), 1, pBin);
    fwrite(bitmapGetContents(bm), sizeof(unsigned char), bitmapGetLength(bm)/8 + 1, pBin);
}

void leBinario(Arvore* a, FILE* pTexto, FILE* pBin, bitmap* bm){
    unsigned int length;
    fread(&length, sizeof(unsigned int), 1, pBin);
    fread(bitmapGetContents(bm), sizeof(unsigned char), length/8 + 1, pBin);

    int i;
    for(i=0; i<length; i++){
        //funcao com Arvore* a, FILE* pTexto, bitmap* bm, int* i
    }
}

bitmap* retornaBMChar(Arvore* a, unsigned char c){
    if(a == NULL){
        return NULL;
    }
    if(c == a->c){
        return a->bm;
    }
    if(retornaBMChar(a->esq, c)){
        return retornaBMChar(a->esq, c);
    }
    return retornaBMChar(a->dir, c);
}