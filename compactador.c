#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "huffman.h"
#include "tabela.h"

#define tam 128

int main(int argc, char * argv[]){
    char nomeArquivo[100];
    sprintf(nomeArquivo, "%s", argv[1]);

    FILE* pTexto = fopen(nomeArquivo, "r");
    int caracteres[tam];

    for(int i=0; i<tam; i++){
        caracteres[i] = 0;
    }

    char c;
    while(fscanf(pTexto, "%c", &c) == 1){
        caracteres[(int)c]++;
    }
    fclose(pTexto);

    Lista* listaHuffman = criaListaDeArvores(caracteres, tam);
    listaHuffman = criaArvoreUnica(listaHuffman);
    Arvore* arvoreHuffman = retornaArvoreLista(listaHuffman); 

    //lista de tabelas de conversão
    Tabela* tabela = NULL;
    tabela = criaTabelas(arvoreHuffman, tabela, alturaArvore(arvoreHuffman));

    liberaLista(listaHuffman);

    return 0;
}