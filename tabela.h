#ifndef tabela_h
#define tabela_h

#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"
#include "arvore.h"

#define ESQ 0
#define DIR 1

typedef struct tabela Tabela;

/*
Cria uma tabela de conversão, que possui um caractere armazenado e um bitmap
*/
Tabela* criaTabela(char c, unsigned int tam_limite);

Tabela* insereTabela(Tabela* t, char c, unsigned int tam);

void insereBit(Tabela* t, char c, unsigned char bit);

/*
Le um texto, e para cada caractere, procura sua conversao na tabela;
Com os bits que representam o caractere, os salva em um arquivo binario
*/
void escreveBinario(Tabela* t, FILE* pTexto, FILE* pBin);

/*
para cada caracterer guardado na lista de tabelas, calcula seus bits de conversão
*/
void codificaTabela(Tabela* t, Arvore* a);

/*Cria uma lista de tabelas de conversão
Para cada caractere registrado na arvore, insere uma nova tabela à lista de tabelas
Para cada tabela, o tamanho limite de bits no bitmap corresponde a altura da arvore
*/
Tabela* criaTabelas(Arvore* a, Tabela* tab, unsigned int altura);

/*
funcao para calcular e guardar no bitmap os bits que representam cada caractere;
num e i iniciam zerados;
num é a sequencia de bits, por exemplo 10100;
i é numero de algarismos que tem em num, no exemplo acima i = 5;
armazena individualmente cada bit no bitmap
*/
void criaBitsCaractere(Arvore* a, int num, int i, char c, Tabela* tab);

void liberaTabela(Tabela* t);

#endif