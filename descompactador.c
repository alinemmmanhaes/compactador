#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "huffman.h"
#include "bitmap.h"

#define tam 256
#define limiteBM 1000000

int main(int argc, char * argv[]){
    char nomeArquivoTxt[100], nomeArquivoBin[200], extensao[10];
    sprintf(nomeArquivoBin, "%s", argv[1]);

    FILE* pBinario = fopen(nomeArquivoBin, "rb");
    short int caracteres[tam];
    fread(caracteres, sizeof(short int), tam, pBinario);

    Lista* listaHuffman = criaListaDeArvores(caracteres, tam);
    listaHuffman = criaArvoreUnica(listaHuffman);
    Arvore* arvoreHuffman = retornaArvoreLista(listaHuffman); 

    arvoreHuffman = percorreArvoreBM(arvoreHuffman, NULL, alturaArvore(arvoreHuffman), 0);

    sscanf(nomeArquivoBin, "%[^.]%[^.].comp", nomeArquivoTxt, extensao);
    sprintf(nomeArquivoTxt, "%s%s", nomeArquivoTxt, extensao);
    FILE* pTexto = fopen(nomeArquivoTxt, "wb");

    bitmap* frasefinal = bitmapInit(limiteBM);

    return 0;
}