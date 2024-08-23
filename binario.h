/*Arquivo criado por: Aline Mendonça Mayerhofer Manhães e Marcela Carpenter da Paixão*/

#ifndef binario_h
#define binario_h

#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"
#include "arvore.h"

/*Para cada unsigned char do texto, procuramos o byte na árvore e obtemos seu bitmap,
que é escrito no bitmap final do arquivo compactado.
Ao fim, esse bitmap final é salvo no arquivo compactado. */
bitmap** escreveBinario(Arvore* a, FILE* pTexto, FILE* pBin, bitmap** bm, int* nBitMap);

/*Lê o arquivo compactado e percorre a árvore com base nas coordenadas lidas. 
Ao achar uma folha, seu unsigned char é escrito no arquivo descompactado.*/
bitmap** leBinario(Arvore* a, FILE* pTexto, FILE* pBin, bitmap** bm, int* nBitMap);

/*Transforma a árvore em binário por meio de bitmap. Se árvore não for folha, 
insere-se 0 no bitmap. Se for folha, insere-se 1 e o binário correspondente a seu unsigned char. 
Depois, o bitmap da árvore é escrito no arquivo compactado.*/
void escreveArvoreBinario(Arvore* a, bitmap* bm, FILE* pBin);

/*Lê a árvore de Huffman de um arquivo binário*/
void leArvoreBinario(Arvore* a, bitmap* bm, FILE* pBin);

#endif