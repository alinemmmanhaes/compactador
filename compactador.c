#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
    char nomeArquivo[100];
    sprintf(nomeArquivo, "%s", argv[1]);

    FILE* pTexto = fopen(nomeArquivo, "r");
    int caracteres[128];

    for(int i=0; i<128; i++){
        caracteres[i] = 0;
    }

    char c;
    while(fscanf(pTexto, "%c", &c) == 1){
        caracteres[(int)c]++;
    }

    fclose(pTexto);

    return 0;
}