#include "huffman.h"

typedef struct cel Cel;

struct lista {
    Cel *prim, *ult;
};

struct cel {
    Arvore *arv;
    Cel *prox;
};

Lista *criaListaDeArvores(int *caracteres, int tam){
    Lista *l = malloc(sizeof(Lista));
    if(!l) return NULL;
    l->prim = l->ult = NULL;

    for(int i=0; i<tam; i++){
        if(caracteres[i] > 0){
            char c = (char)i;
        
            Cel *nova = malloc(sizeof(Cel));
            nova->arv = criaArvore(caracteres[i], c, NULL, NULL);
            nova->prox = NULL;
        
            if(l->prim == NULL){
                l->prim = l->ult = nova;
            }
            else {
                l->ult->prox = nova;
                l->ult = nova;
            }
        }
    }

    return l;
}

/*int comparaFrequencia(const void *cel1, const void *cel2){
    Cel *c1 = (struct cel*)cel1;
    Cel *c2 = (struct cel*)cel2;
    return(retornaFrequencia(c1->arv) - retornaFrequencia(c2->arv));
}*/

void ordenaListaDeArvores(Lista *l, int tam);

void criaArvoreUnica(Lista *l);

