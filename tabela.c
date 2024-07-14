#include "tabela.h"
#include <math.h>

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

void escreveBinario(Tabela* t, FILE* pTexto, FILE* pBin){
    char c;
    Tabela* aux;
    while(fscanf(pTexto, "%c", &c) == 1){
        aux = t;
        while(aux != NULL){
            if(c == aux->c){
                for(int i=0; i<bitmapGetLength(aux->bitmap); i++){
                    unsigned char bit = bitmapGetBit(aux->bitmap, i);
                    fwrite(&bit, sizeof(unsigned char), 1, pBin);
                }
                break;
            }
            aux = aux->prox;
        }
    }
}

void codificaTabela(Tabela* t, Arvore* a){
    while (t != NULL){
        criaBitsCaractere(a, 0, 0, t->c, t);
        t = t->prox;
    }
}

Tabela* criaTabelas(Arvore* a, Tabela* tab, unsigned int altura){
    if(a == NULL) return;

    if(retornaCaracter(a) != '\0'){
        tab = insereTabela(tab, retornaCaracter(a), altura);
        return;
    }

    tab = criaTabelas(retornaArvoreEsq(a), tab, altura);
    tab = criaTabelas(retornaArvoreDir(a), tab, altura);

    return tab;
}

void criaBitsCaractere(Arvore* a, int num, int i, char c, Tabela* tab){
    if(a == NULL) return;

    if(c == retornaCaracter(a)){
        for(int j=i; j>0; j--){
            bitmapAppendLeastSignificantBit(tab->bitmap, num/pow(10, j-1));
            num = num - ((num/pow(10, j-1)) * pow(10, j-1));
        }
        return;
    }

    criaBitsCaractere(retornaArvoreEsq(a), num*10 + ESQ, i+1, c, tab);
    criaBitsCaractere(retornaArvoreDir(a), num*10 + DIR, i+1, c, tab);
}

void liberaTabela(Tabela* t){
    Tabela* aux;
    while(t){
        aux = t;
        t = t->prox;
        bitmapLibera(aux->bitmap);
        free(aux);
    }
}