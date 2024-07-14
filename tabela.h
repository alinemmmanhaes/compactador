#ifndef tabela_h
#define tabela_h

#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"

#define ESQ 0
#define DIR 1

typedef struct tabela Tabela;

/*
Cria uma tabela de conversão, que possui um caractere armazenado e um bitmap
*/
Tabela* criaTabela(char c, unsigned int tam_limite);

Tabela* insereTabela(Tabela* t, char c, unsigned int tam);

void insereBit(Tabela* t, char c, unsigned char bit);

#endif