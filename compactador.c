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
    FILE* pTexto = fopen(nomeArquivoTxt, "r");

    //cria vetor de frequencia de caracteres zerado
    int caracteres[tam];
    for(int i=0; i<tam; i++){
        caracteres[i] = 0;
    }

    //contabiliza a frequencia dos caracteres no texto
    char c;
    while(fscanf(pTexto, "%c", &c) == 1){
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
    1- PASSAR PARA O BINARIO A TABELA E/OU A ARVORE
    2- CARACTERE DE PARADA
    */
    
    //relê o arquivo de texto colocando as codificações de cada char no arquivo binario
    pTexto = fopen(nomeArquivoTxt, "r");
    bitmap* fraseFinal = bitmapInit(limiteBM);
    escreveBinario(arvoreHuffman, pTexto, pBinario, fraseFinal);
    fclose(pTexto);
    fclose(pBinario);

    liberaLista(listaHuffman);
    liberaArvore(arvoreHuffman);

    return 0;
}