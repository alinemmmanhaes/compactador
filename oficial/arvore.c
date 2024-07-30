#include <stdlib.h>
#include "arvore.h"

struct arvore{
    int freq;
    unsigned char c;
    bitmap* bm;
    Arvore* esq;
    Arvore* dir;
};

Arvore* criaArvoreVazia(){
    Arvore* arv = malloc(sizeof(Arvore));
    arv->freq = 0;
    arv->c = '\0';
    arv->bm = NULL;
    arv->esq = NULL;
    arv->dir = NULL;
    return arv;
}

Arvore* criaArvore(int freq, unsigned char c, Arvore* esq, Arvore* dir){
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
        if(a->bm){
            bitmapLibera(a->bm);
        }
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

unsigned char retornaCaracter(Arvore* a){
    return a->c;
}

/*Arvore* retornaArvoreEsq(Arvore* a){
    return a->esq;
}

Arvore* retornaArvoreDir(Arvore* a){
    return a->dir;
}*/

unsigned int alturaArvore(Arvore* a){
    unsigned int n1 = 0, n2 = 0;
    if(arvoreVazia(a)) return 0;

    if(arvoreVazia(a->esq) && arvoreVazia(a->dir)) return 0;

    n1 = 1 + alturaArvore(a->esq);
    n2 = 1 + alturaArvore(a->dir);

    return (n1>n2)?n1:n2;
}

/*void imprime(Arvore *a){
    if(a){
        printf("%c: ", a->c);
        if(a->bm){
            for(int i=0; i<bitmapGetLength(a->bm); i++){
                unsigned char bit = bitmapGetBit(a->bm, i);
                printf("%0x", bit);
            }
            printf("\n");
        }
        imprime(a->esq);
        imprime(a->dir);
    }
}*/

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

    bitmapLibera(bm_novo);
    return a;
}

bitmap* retornaBMChar(Arvore* a, unsigned char c){
    if(a == NULL){
        return NULL;
    }
    if(c == a->c && ehFolha(a)){
        return a->bm;
    }
    if(retornaBMChar(a->esq, c)){
        return retornaBMChar(a->esq, c);
    }
    return retornaBMChar(a->dir, c);
}

void decodifica(Arvore* a, FILE* pTexto, bitmap** bm, int* totalLength, int* index, int* i){
    if(a == NULL){
        return;
    }
    if(ehFolha(a)){
        fwrite(&(a->c), sizeof(unsigned char), 1, pTexto);
        return;
    }
    if(*i == bitmapGetLength(bm[*index])){
        (*index)++;
        *i = 0;
    }
    if(bitmapGetBit(bm[*index], *i) == 0){
        (*i)++;
        (*totalLength)++;
        decodifica(a->esq, pTexto, bm, totalLength, index, i);
    }
    else if(bitmapGetBit(bm[*index], *i) == 1){
        (*i)++;
        (*totalLength)++;
        decodifica(a->dir, pTexto, bm, totalLength, index, i);
    }
}



void converteCharBinario(bitmap* bm, unsigned char c){
    int num = (int) c, div = 128;
    while(div >= 1){
        if(num/div){
            bitmapAppendLeastSignificantBit(bm, 1);
            num = num - div;
        }else{
            bitmapAppendLeastSignificantBit(bm, 0);
        }
        div = div/2;
    }
}

void escreveArvoreBM(Arvore* a, bitmap* bm){
    if(!a){
        bitmapAppendLeastSignificantBit(bm, 1);
        converteCharBinario(bm, '\0');
    }
    else if(!ehFolha(a)){
        bitmapAppendLeastSignificantBit(bm, 0);
        escreveArvoreBM(a->esq, bm);
        escreveArvoreBM(a->dir, bm);
    }
    else{
        bitmapAppendLeastSignificantBit(bm, 1);
        converteCharBinario(bm, a->c);
    }
}

unsigned char converteBinInt(bitmap* bm, int* index){
    int num = 0, mult = 128;
    for(int i=0; i<8; i++){
        unsigned char c = bitmapGetBit(bm, (unsigned int)*index);
        if(c == 1){
            num += mult;
        }
        mult = mult/2;
        (*index)++;
    }
    (*index)--;
    return (unsigned char)num;
}

void montaArvore(Arvore* a, bitmap* bm, int* i){
    unsigned char c = bitmapGetBit(bm, (unsigned int)*i);
    if(c == 0){
        a->esq = criaArvoreVazia();
        a->dir = criaArvoreVazia();
        (*i)++;
        montaArvore(a->esq, bm, i);
        (*i)++;
        montaArvore(a->dir, bm, i);
    }
    else if(c == 1){
        (*i)++;
        a->c = converteBinInt(bm, i);
    }
}
