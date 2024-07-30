#include "binario.h"

bitmap** escreveBinario(Arvore* a, FILE* pTexto, FILE* pBin, bitmap** bm, int* nBitMap){
    unsigned char c;
    bitmap* bm_aux;
    while(fread(&c, sizeof(unsigned char), 1, pTexto) == 1){
        bm_aux = retornaBMChar(a, c);
        for(int i=0; i<bitmapGetLength(bm_aux); i++){
            unsigned char bit = bitmapGetBit(bm_aux, i);
            if(bitmapGetMaxSize(bm[*nBitMap - 1]) == bitmapGetLength(bm[*nBitMap - 1])){
                (*nBitMap)++;
                bm = realloc(bm, (*nBitMap)*sizeof(bitmap*));
                bm[*nBitMap-1] = bitmapInit(limiteBM);
            }
            bitmapAppendLeastSignificantBit(bm[*nBitMap - 1], bit);
        }
    }
    fwrite(nBitMap, sizeof(int), 1, pBin);
    for(int i=0; i<*nBitMap; i++){
        unsigned int length = bitmapGetLength(bm[i]);
        fwrite(&length, sizeof(unsigned int), 1, pBin);
        fwrite(bitmapGetContents(bm[i]), sizeof(unsigned char), (bitmapGetLength(bm[i])+7)/8, pBin); 
    }

    return bm;
}

bitmap** leBinario(Arvore* a, FILE* pTexto, FILE* pBin, bitmap** bm, int* nBitMap){
    fread(nBitMap, sizeof(int), 1, pBin);
    bm = malloc((*nBitMap)*sizeof(bitmap*));
    for(int i=0; i<(*nBitMap); i++){
        bm[i] = bitmapInit(limiteBM);
    }
    unsigned int length[*nBitMap];
    for(int j=0; j<*nBitMap; j++){
        fread(&length[j], sizeof(unsigned int), 1, pBin);
        for(int i=0; i<(length[j]+7)/8; i++){
            unsigned char c;
            fread(&c, sizeof(unsigned char), 1, pBin);
            for(int k=0; k<8; k++){
                bitmapAppendLeastSignificantBit(bm[j], c >> (7-k) & 0x01);
            }
        }
    }
    unsigned int totalLength = 0;
    for(int j=0; j<*nBitMap; j++){
        totalLength += length[j];
    }
    int i = 0, ind = 0, bit = 0;
    for(i=0; i<totalLength; i++){
        decodifica(a, pTexto, bm, &i, &ind, &bit);
        i--;
    }
    return bm;
}

void escreveArvoreBinario(Arvore* a, bitmap* bm, FILE* pBin){
    escreveArvoreBM(a, bm);
    unsigned int length = bitmapGetLength(bm);
    fwrite(&length, sizeof(unsigned int), 1, pBin);
    fwrite(bitmapGetContents(bm), sizeof(unsigned char), (bitmapGetLength(bm)+7)/8, pBin);
}


void leArvoreBinario(Arvore* a, bitmap* bm, FILE* pBin){
    unsigned int length;
    fread(&length, sizeof(unsigned int), 1, pBin);

    for(int i=0; i<(length+7)/8; i++){
        unsigned char c;
        fread(&c, sizeof(unsigned char), 1, pBin);
        for(int j=0; j<8; j++){
            bitmapAppendLeastSignificantBit(bm, c >> (7-j) & 0x01);
        }
    }

    int i = 0;
    montaArvore(a, bm, &i);
}