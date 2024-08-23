/*Arquivo criado por: Aline Mendonça Mayerhofer Manhães e Marcela Carpenter da Paixão*/

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
    //Inicializa a árvore
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
    //Libera toda memória alocada para a árvore        
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

unsigned int alturaArvore(Arvore* a){
    unsigned int n1 = 0, n2 = 0;
    //Se árore for vazia, retorna 0
    if(arvoreVazia(a)) return 0;

    //Se ambas subárvores forem vazias, retorna 0
    if(arvoreVazia(a->esq) && arvoreVazia(a->dir)) return 0;

    //Calcula a altura das subárvores
    n1 = 1 + alturaArvore(a->esq);
    n2 = 1 + alturaArvore(a->dir);

    return (n1>n2) ? n1:n2;
}

Arvore* percorreArvoreBM(Arvore* a, bitmap* bm, unsigned int tam, int bit){
    //Se a árvore for nula, retorna NULL
    if(a == NULL){
        return a;
    }

    //Inicializa um novo bitmap
    bitmap* bm_novo = bitmapInit(tam);
    
    //Copia bits do bitmap atual para o novo bitmap
    if(bm){
        for(int i=0; i<bitmapGetLength(bm); i++){
            bitmapAppendLeastSignificantBit(bm_novo, bitmapGetBit(bm, i));
        }
        bitmapAppendLeastSignificantBit(bm_novo, bit);
    }

    //Associa o bitmap à arvore caso ela seja folha e retorna
    if(ehFolha(a)){
        a->bm = bm_novo;
        return a;
    }

    //Recursão para entrar nas subárores da esquerda e da direita, caso árore não seja folha
    a->esq = percorreArvoreBM(a->esq, bm_novo, tam, ESQ);
    a->dir = percorreArvoreBM(a->dir, bm_novo, tam, DIR);

    bitmapLibera(bm_novo);
    return a;
}

bitmap* retornaBMChar(Arvore* a, unsigned char c){
    //Se a árvore for nula, retorna NULL
    if(a == NULL){
        return NULL;
    }
    //Se a árvore for folha e seu unsigned char for igual ao procurado, retorna seu bitmap
    if(c == a->c && ehFolha(a)){
        return a->bm;
    }
    //Entra em recursão na subárvore da esquerda
    if(retornaBMChar(a->esq, c)){
        return retornaBMChar(a->esq, c);
    }
    //Entra em recursão na subárvore da direita
    return retornaBMChar(a->dir, c);
}

void decodifica(Arvore* a, FILE* pTexto, bitmap** bm, int* totalLength, int* index, int* i){
    //Se a árvore for nula, retorna
    if(a == NULL){
        return;
    }
    //Se a árore for folha, escreve seu unsigned char no arquivo de texto
    if(ehFolha(a)){
        fwrite(&(a->c), sizeof(unsigned char), 1, pTexto);
        return;
    }
    //Atualiza o índice passado e reinicia a posição i
    if(*i == bitmapGetLength(bm[*index])){
        (*index)++;
        *i = 0; 
    }
    //Se o bit na posição for 0, atualiza os ponteiros e entra em recursão na subárvore da esquerda
    if(bitmapGetBit(bm[*index], *i) == 0){
        (*i)++;
        (*totalLength)++;
        decodifica(a->esq, pTexto, bm, totalLength, index, i);
    }
    //Se o bit na posição for 1, atualiza os ponteiros e entra em recursão na subárvore da direita
    else if(bitmapGetBit(bm[*index], *i) == 1){
        (*i)++;
        (*totalLength)++;
        decodifica(a->dir, pTexto, bm, totalLength, index, i);
    }
}

/*Converte um caractere para sua representação binária e adiciona ao bitmap*/
void converteCharBinario(bitmap* bm, unsigned char c){
    int num = (int) c, div = 128;
    
    while(div >= 1){
        //Se o número for divisível por div, insere 1 no bitmap e atualiza a variável num
        if(num/div){
            bitmapAppendLeastSignificantBit(bm, 1);
            num = num - div;
        
        //Caso contrário insere 0 no bitmap
        }else{
            bitmapAppendLeastSignificantBit(bm, 0);
        }
        //O divisor é atualizado
        div = div/2;
    }
}

void escreveArvoreBM(Arvore* a, bitmap* bm){
    //Se árvore for nula, insere 1 no bitmap seguido de '\0' convertido para binário
    if(!a){
        bitmapAppendLeastSignificantBit(bm, 1);
        converteCharBinario(bm, '\0');
    }
    //Se a árvore não for folha, insere 0 no bitmap e entra em recursão nas suas subárvores
    else if(!ehFolha(a)){
        bitmapAppendLeastSignificantBit(bm, 0);
        escreveArvoreBM(a->esq, bm);
        escreveArvoreBM(a->dir, bm);
    }
    //Se for folha, insere 1 no bitmap seguido do unsigned char da árvore convertido para binário
    else{
        bitmapAppendLeastSignificantBit(bm, 1);
        converteCharBinario(bm, a->c);
    }
}

/*Converte 8 bits para caracter*/
unsigned char converteBinInt(bitmap* bm, int* index){
    int num = 0, mult = 128;

    //Converte os 8 bits recuperados do bitmap no índice passado para decimal
    for(int i=0; i<8; i++){
        unsigned char c = bitmapGetBit(bm, (unsigned int)*index);
        //Se bit for 1, atualiza o valor de num
        if(c == 1){
            num += mult;
        }
        //Atualiza a váriável mult e o índice
        mult = mult/2;
        (*index)++;
    }
    (*index)--;
    //Retorna o unsigned char correspondente ao número encontrado acima
    return (unsigned char)num;
}

void montaArvore(Arvore* a, bitmap* bm, int* i){
    //Recupera um bit do bitmap na posição passada
    unsigned char c = bitmapGetBit(bm, (unsigned int)*i);
    //Se o bit for 0, significa que se trata de árvore raiz, então cria e monta para ela subárvores da esquera e direita 
    if(c == 0){
        a->esq = criaArvoreVazia();
        a->dir = criaArvoreVazia();
        (*i)++;
        montaArvore(a->esq, bm, i);
        (*i)++;
        montaArvore(a->dir, bm, i);
    }
    //Se for 1, se trata de árvore folha, então associa à árvore o caracter lido e convertido
    //a partir dos próximos bits do bitmap em relação ao índice
    else if(c == 1){
        (*i)++;
        a->c = converteBinInt(bm, i);
    }
}
