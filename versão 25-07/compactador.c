#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "huffman.h"
#include "bitmap.h"

#define tam 256
#define limiteBM 1000000

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
    short int caracteres[tam];
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
    1- VETOR DE BITMAPS > 1MEGA
    2- IMAGEM
    3- TIRAR O 2 DO ARQUIVO FINAL
    */
    
    bitmap* arvoreBM = bitmapInit(limiteBM);
    escreveArvoreBinario(arvoreHuffman, arvoreBM, pBinario);

    //relê o arquivo de texto colocando as codificações de cada char no arquivo binario
    pTexto = fopen(nomeArquivoTxt, "rb");
    bitmap* fraseFinal = bitmapInit(limiteBM);
    escreveBinario(arvoreHuffman, pTexto, pBinario, fraseFinal);
    fclose(pTexto);
    fclose(pBinario);

    liberaLista(listaHuffman);
    arvoreHuffman = liberaArvore(arvoreHuffman);
    bitmapLibera(fraseFinal);
    bitmapLibera(arvoreBM);

    return 0;
}