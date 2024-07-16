#include "huffman.h"

struct cel {
    Arvore *arv;
    Cel *prox;
};

Lista *criaListaDeArvores(short int *caracteres, int tam){
    Lista *lista = NULL;
    for(int i=0; i<tam; i++){
        if(caracteres[i] > 0){
            unsigned char c = (unsigned char)i;
            Arvore *arv = criaArvore(caracteres[i], c, NULL, NULL);
            lista = insereNaLista(lista, arv);
        }
    }
    return lista;
}

Lista *insereNaLista(Lista *l, Arvore *arv){
    if(l == NULL){
        Lista *aux = malloc(sizeof(Lista));
        aux->arv = arv;
        aux->prox = NULL;
        return aux;
    }
    else if(retornaFrequencia(arv) > retornaFrequencia(l->arv)){
        l->prox = insereNaLista(l->prox, arv);
    }
    else {
        Lista *aux = malloc(sizeof(Lista));
        aux->arv = arv;
        aux->prox = l;
        return aux;
    }
    return l;
}

Lista *retiraInicioLista(Lista *l){
    Lista *aux = l;
    l = l->prox;
    free(aux);
    return l;
}

Lista *criaArvoreUnica(Lista *l){
    //Continuar processo até que só haja uma única célula na Lista
    while(l->prox != NULL){
        Arvore *node1 = l->arv;
        l = retiraInicioLista(l);
    
        Arvore *node2 = l->arv;
        l = retiraInicioLista(l);

        int somaFreq = retornaFrequencia(node1) + retornaFrequencia(node2);
        Arvore *raiz = criaArvore(somaFreq, '\0', node1, node2);
        l = insereNaLista(l, raiz);
    }
    return l;
}

Arvore* retornaArvoreLista(Lista* l){
    return l->arv;
}

void liberaLista(Lista* l){
    Lista* aux;
    while(l){
        aux = l;
        l = l->prox;
        free(aux);
    }
}