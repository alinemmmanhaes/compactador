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
    //imprime(arvoreHuffman);

    //abre arquivo binario que conterá o codigo de conversão e texto compactado
    sprintf(nomeArquivoBin, "%s.comp", nomeArquivoTxt);
    FILE* pBinario = fopen(nomeArquivoBin, "wb");

    fwrite(caracteres, sizeof(short int), tam, pBinario);

    /*
    AQUI FALTA
    1- VETOR DE BITMAPS > 1MEGA
    2- GUARDAR A ARVORE
    */
    
    //relê o arquivo de texto colocando as codificações de cada char no arquivo binario
    pTexto = fopen(nomeArquivoTxt, "rb");
    bitmap* fraseFinal = bitmapInit(limiteBM);
    escreveBinario(arvoreHuffman, pTexto, pBinario, fraseFinal);
    fclose(pTexto);
    fclose(pBinario);

    liberaLista(listaHuffman);
    liberaArvore(arvoreHuffman);
    bitmapLibera(fraseFinal);

    return 0;
}