#include "huffman.h"

struct cel {
    Arvore *arv;
    Cel *prox;
};

Lista *criaListaDeArvores(int *caracteres, int tam){
    Lista *lista = NULL;
    for(int i=0; i<tam; i++){
        //Se o caractere tiver frequência maior que 0, cria uma árvore para ele, e a insere na lista
        if(caracteres[i] > 0){
            unsigned char c = (unsigned char)i;
            Arvore *arv = criaArvore(caracteres[i], c, NULL, NULL);
            lista = insereNaLista(lista, arv);
        }
    }
    return lista;
}

Lista *insereNaLista(Lista *l, Arvore *arv){
    //Se a lista for nula, cria sua primeira célula com a árvore passada e a retorna
    if(l == NULL){
        Lista *aux = malloc(sizeof(Lista));
        aux->arv = arv;
        aux->prox = NULL;
        return aux;
    }
    //Compara a frequência da árvore da célula da lista com a árvore passada por parâmetro
    else if(retornaFrequencia(arv) > retornaFrequencia(l->arv)){
        //Insere recursivamente na posição correta de acordo com a frequência
        l->prox = insereNaLista(l->prox, arv);
    }
    //Cria e insere uma nova célula como início da lista
    else {
        Lista *aux = malloc(sizeof(Lista));
        aux->arv = arv;
        aux->prox = l;
        return aux;
    }
    //Retorna a lista atualizada
    return l;
}

Lista *retiraInicioLista(Lista *l){
    Lista *aux = l;
    l = l->prox;
    free(aux);
    return l;
}

Lista *criaArvoreUnica(Lista *l){
    //Enquanto houve mais de uma célula na lista, o loop continua
    while(l->prox != NULL){
        //Copia a árvore da atual primeira célula da lista e depois a retira da lista
        Arvore *node1 = l->arv;
        l = retiraInicioLista(l);
    
        //Novamente copia a árvore da atual primeira célula da lista e depois a retira da lista
        Arvore *node2 = l->arv;
        l = retiraInicioLista(l);

        //Soma as frequências dos dois nós
        int somaFreq = retornaFrequencia(node1) + retornaFrequencia(node2);
        //Cria uma nova árvore com os dois nós como filhos 
        Arvore *raiz = criaArvore(somaFreq, '\0', node1, node2);
        //Insere a nova árvore na lista
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