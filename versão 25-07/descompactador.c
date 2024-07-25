#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "huffman.h"
#include "bitmap.h"

#define tam 256
#define limiteBM 1000000

int main(int argc, char * argv[]){
    char nomeArquivoTxt[101], nomeArquivoBin[200], nomeArquivo[90], extensao[10];
    sprintf(nomeArquivoBin, "%s", argv[1]);

    FILE* pBinario = fopen(nomeArquivoBin, "rb");
    if(!pBinario){
        printf("O arquivo de entrada nao pode ser aberto\n");
        exit(1);
    }

    bitmap* arvoreBM = bitmapInit(limiteBM);
    Arvore* arvoreHuffman = criaArvoreVazia();
    leArvoreB(arvoreHuffman, arvoreBM, pBinario);

    arvoreHuffman = percorreArvoreBM(arvoreHuffman, NULL, alturaArvore(arvoreHuffman), 0);

    sscanf(nomeArquivoBin, "%[^.].%[^.].comp", nomeArquivo, extensao);
    sprintf(nomeArquivoTxt, "%s2.%s", nomeArquivo, extensao);
    FILE* pTexto = fopen(nomeArquivoTxt, "wb");

    bitmap* fraseFinal = bitmapInit(limiteBM);

    leBinario(arvoreHuffman, pTexto, pBinario, fraseFinal);

    fclose(pTexto);
    fclose(pBinario);

    liberaArvore(arvoreHuffman);
    bitmapLibera(fraseFinal);
    bitmapLibera(arvoreBM);

    return 0;
}