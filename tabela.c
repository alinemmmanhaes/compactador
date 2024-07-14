#include "tabela.h"

struct tabela{
    char c;
    bitmap* bitmap;
    Tabela* prox;
};

Tabela* criaTabela(char c, unsigned int tam_limite){
    Tabela* tab = malloc(sizeof(Tabela));
    tab->c = c;
    tab->bitmap = bitmapInit(tam_limite);
    tab->prox = NULL;

    return tab;
}

Tabela* insereTabela(Tabela* t, char c, unsigned int tam){
    if(t == NULL){
        t = criaTabela(c, tam);
        return t;
    }else{
        Tabela* novaTab = criaTabela(c, tam);
        novaTab->prox = t;
        return novaTab;
    }
}

void insereBit(Tabela* t, char c, unsigned char bit){
    while(t != NULL){
        if(t->c == c){
            bitmapAppendLeastSignificantBit(t->bitmap, bit);
            break;
        }
        t = t->prox;
    }
}