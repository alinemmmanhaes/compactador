#ifndef arvore_h
#define arvore_h

#include <stdio.h>
#include "bitmap.h"

#define ESQ 0
#define DIR 1
#define limiteBM 1000000

typedef struct arvore Arvore;

/*Cria uma árvore com todos os seus parâmetros inicializados como 0 ou NULL*/
Arvore* criaArvoreVazia();

/*Cria a árvore de acordo com os valores passados como parâmetro da função */
Arvore* criaArvore(int freq, unsigned char c, Arvore* esq, Arvore* dir);

/*Libera a árvore*/
Arvore* liberaArvore(Arvore* a);

/*Verifica se a árvore está vazia*/
int arvoreVazia(Arvore* a);

/*Verifica se é arvóre folha (ou seja, se não tem filhos)*/
int ehFolha(Arvore* a);

/*Retorna frequência do caracter da árvore*/
int retornaFrequencia(Arvore* a);

/*Retorna o caracter da árvore*/
unsigned char retornaCaracter(Arvore* a);

/*Calcula a altura da árvore*/
unsigned int alturaArvore(Arvore* a);

/*Função que, por meio de recursão, gera os bitmaps dos caminhos percorridos na árvore. 
Para cada folha da árvore esse bitmap é guardado*/
Arvore* percorreArvoreBM(Arvore* a, bitmap* bm, unsigned int tam, int bit);

/*Retorna o bitmap da árvore cujo caracter é o mesmo do passado como parâmetro*/
bitmap* retornaBMChar(Arvore* a, unsigned char c);

/**/
void decodifica(Arvore* a, FILE* pTexto, bitmap** bm, int* totalLength, int* index, int* i);

/**/
void escreveArvoreBM(Arvore* a, bitmap* bm);

/**/
void montaArvore(Arvore* a, bitmap* bm, int* i);

#endif