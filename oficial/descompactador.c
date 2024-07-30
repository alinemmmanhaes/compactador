#include <stdio.h>
#include <stdlib.h>
#include "binario.h"
#include "arvore.h"
#include "huffman.h"
#include "bitmap.h"

#define tam 256

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
    leArvoreBinario(arvoreHuffman, arvoreBM, pBinario);

    arvoreHuffman = percorreArvoreBM(arvoreHuffman, NULL, alturaArvore(arvoreHuffman), 0);

    sscanf(nomeArquivoBin, "%[^.].%[^.].comp", nomeArquivo, extensao);
    sprintf(nomeArquivoTxt, "%s.%s", nomeArquivo, extensao);
    FILE* pTexto = fopen(nomeArquivoTxt, "wb");

    int nBitMap = 1;
    bitmap** fraseFinal = leBinario(arvoreHuffman, pTexto, pBinario, fraseFinal, &nBitMap);
    
    fclose(pTexto);
    fclose(pBinario);

    liberaArvore(arvoreHuffman);
    for(int i=0; i<nBitMap; i++){
        bitmapLibera(fraseFinal[i]);
    }
    free(fraseFinal);
    bitmapLibera(arvoreBM);

    return 0;
}