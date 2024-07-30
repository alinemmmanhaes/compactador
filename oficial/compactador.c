#include <stdio.h>
#include <stdlib.h>
#include "binario.h"
#include "arvore.h"
#include "huffman.h"
#include "bitmap.h"

#define tam 256

int main(int argc, char * argv[]){
    char nomeArquivoTxt[100], nomeArquivoBin[200];
    sprintf(nomeArquivoTxt, "%s", argv[1]);

    //abre arquivo de texto que será compactado
    FILE* pTexto = fopen(nomeArquivoTxt, "rb");
    if(!pTexto){
        printf("O arquivo de entrada nao pode ser aberto\n");
        exit(1);
    }

    //cria vetor de frequencia de caracteres zerado
    int caracteres[tam];
    for(int i=0; i<tam; i++){
        caracteres[i] = 0;
    }

    //contabiliza a frequencia dos caracteres no texto
    unsigned char c;
    while(fread(&c, sizeof(unsigned char), 1, pTexto) == 1){
        caracteres[(int)c]++;
    }
    fclose(pTexto);

    //utilizando o algoritmo de Huffman, cria uma arvore com os caracteres do texto e suas frequencias
    Lista* listaHuffman = criaListaDeArvores(caracteres, tam);
    listaHuffman = criaArvoreUnica(listaHuffman);
    Arvore* arvoreHuffman = retornaArvoreLista(listaHuffman); 

    arvoreHuffman = percorreArvoreBM(arvoreHuffman, NULL, alturaArvore(arvoreHuffman), 0);

    //abre arquivo binario que conterá o codigo de conversão e texto compactado
    sprintf(nomeArquivoBin, "%s.comp", nomeArquivoTxt);
    FILE* pBinario = fopen(nomeArquivoBin, "wb");
    
    /*
    AQUI FALTA
    1- COMENTAR
    2- ATUALIZAR PDF COM BINARIO.C
    */
    
    bitmap* arvoreBM = bitmapInit(limiteBM);
    escreveArvoreBinario(arvoreHuffman, arvoreBM, pBinario);

    //relê o arquivo de texto colocando as codificações de cada char no arquivo binario
    pTexto = fopen(nomeArquivoTxt, "rb");
    int nBitMap = 1;
    bitmap** fraseFinal = malloc(sizeof(bitmap*));
    fraseFinal[nBitMap - 1] = bitmapInit(limiteBM);

    fraseFinal = escreveBinario(arvoreHuffman, pTexto, pBinario, fraseFinal, &nBitMap);
    fclose(pTexto);
    fclose(pBinario);

    liberaLista(listaHuffman);
    arvoreHuffman = liberaArvore(arvoreHuffman);
    for(int i=0; i<nBitMap; i++){
        bitmapLibera(fraseFinal[i]);
    }
    free(fraseFinal);
    bitmapLibera(arvoreBM);

    return 0;
}