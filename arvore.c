#include <stdlib.h>
#include "arvore.h"

struct arvore{
    int freq;
    char c;
    bitmap* bm;
    Arvore* esq;
    Arvore* dir;
};

Arvore* criaArvoreVazia(){
    return NULL;
}

Arvore* criaArvore(int freq, char c, Arvore* esq, Arvore* dir){
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

int retornaFrequencia(Arvore* a){
    return a->freq;
}

char retornaCaracter(Arvore* a){
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

    if(a->c != '\0'){
        a->bm = bm_novo;
        return a;
    }

    a->esq = percorreArvoreBM(a->esq, bm_novo, tam, ESQ);
    a->dir = percorreArvoreBM(a->dir, bm_novo, tam, DIR);

    return a;
}

void escreveBinario(Arvore* a, FILE* pTexto, FILE* pBin, bitmap* bm){
    char c;
    bitmap* bm_aux;
    while(fscanf(pTexto, "%c", &c) == 1){
        bm_aux = retornaBMChar(a, c);
        for(int i=0; i<bitmapGetLength(bm_aux); i++){
            unsigned char bit = bitmapGetBit(bm_aux, i);
            bitmapAppendLeastSignificantBit(bm, bit);
        }
    }
    //ADICIONAR CARACTERE DE PARADA
    fwrite(bitmapGetContents(bm), sizeof(unsigned char), bitmapGetLength(bm)/8 + 1, pBin);
}

bitmap* retornaBMChar(Arvore* a, char c){
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