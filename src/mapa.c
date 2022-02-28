#include <stdio.h>
#include <stdlib.h>

#include "mapa.h"

//função pra inicializar matriz terreno com 0
void inicializaMapaVazio(mapa *terreno, int x, int y) {
    int i, j;
    terreno->tamanhox = x;
    terreno->tamanhoy = y;
    terreno->mat = calloc(x, sizeof(int *));
    for (i = 0; i < x; i++) {
        terreno->mat[i] = calloc(y, sizeof(int));
    }
}

void imprimeMapa(mapa terreno) {
    int i, j;
    for (i = 0; i < terreno.tamanhox; i++) {
        for (j = 0; j < terreno.tamanhoy; j++) {
            printf("%d", terreno.mat[i][j]);
        }
        printf("\n");
    }
}

// função para desalocar
void desalocaMapa(mapa terreno) {
    for (int i = 0; i < terreno.tamanhox; i++) {
        free(terreno.mat[i]);
    }
    free(terreno.mat);
}