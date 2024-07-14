#include <stdlib.h>
#include "arvore.h"

struct arvore{
    int freq;
    char c;
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
    arv->esq = esq;
    arv->dir = dir;

    return arv;
}

Arvore* liberaArvore(Arvore* a){
    if(!arvoreVazia(a)){
        liberaArvore(a->esq);
        liberaArvore(a->dir);

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

unsigned int alturaArvore(Arvore* a){
    unsigned int n1 = 0, n2 = 0;
    if(arvoreVazia(a)) return 0;

    if(arvoreVazia(a->esq) && arvoreVazia(a->dir)) return 0;

    n1 = 1 + alturaArvore(a->esq);
    n2 = 1 + alturaArvore(a->dir);

    return (n1>n2)?n1:n2;
}

Tabela* criaTabelas(Arvore* a, Tabela* tab, unsigned int altura){
    if(a == NULL) return;

    if(a->c != '\0'){
        tab = insereTabela(tab, a->c, altura);
    }

    tab = criaTabelas(a->esq, tab, altura);
    tab = criaTabelas(a->dir, tab, altura);

    return tab;
}