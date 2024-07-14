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

/*deixei o codigo aqui para sua análise
eu tinha feito essas duas funções funcoes abaixo nesse TAD, so que eu percebi que precisava que tabela.h incluisse arvore.h
fiquei com medo que arvore.h incluindo tabela.h desse problema por conta de um incluir o outro
qualquer coisa te explico melhor amanha
assim, precisei fazer essas funções no tabela.c usando funcoes de retornar as coisas
se voce tiver entendido o que eu disse, pode apagar tudo abaixo
se não, vou te explicar melhor pessoalmente. nao apaga pq estou insegura com essa parte e so quero que voce apague se souber o que ta aqui
*/
/*
Tabela* criaTabelas(Arvore* a, Tabela* tab, unsigned int altura){
    if(a == NULL) return;

    if(a->c != '\0'){
        tab = insereTabela(tab, a->c, altura);
        return;
    }

    tab = criaTabelas(a->esq, tab, altura);
    tab = criaTabelas(a->dir, tab, altura);

    return tab;
}

void criaBitsCaractere(Arvore* a, int num, int i, char c){
    if(a == NULL) return;

    if(c == a->c){
        for(int j=1; j<=i; j++){
        //faltou fazer aqui
        }
    }

    criaBitsCaractere(a->esq, num*10 + ESQ, i+1, c);
    criaBitsCaractere(a->dir, num*10 + DIR, i+1, c);
}
*/