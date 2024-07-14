#ifndef arvore_h
#define arvore_h

#include <stdio.h>
#include "tabela.h"

typedef struct arvore Arvore;

Arvore* criaArvoreVazia();

Arvore* criaArvore(int freq, char c, Arvore* esq, Arvore* dir);

Arvore* liberaArvore(Arvore* a);

int arvoreVazia(Arvore* a);

int ehFolha(Arvore* a);

int retornaFrequencia(Arvore* a);

char retornaCaracter(Arvore* a);

unsigned int alturaArvore(Arvore* a);

/*Cria uma lista de tabelas de conversão
Para cada caractere registrado na arvore, insere uma nova tabela à lista de tabelas
Para cada tabela, o tamanho limite de bits no bitmap corresponde a altura da arvore
*/
Tabela* criaTabelas(Arvore* a, Tabela* tab, unsigned int altura);

#endif