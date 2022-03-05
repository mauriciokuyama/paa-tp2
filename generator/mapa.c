#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"


// função pra inicializar matriz terreno com 0
void inicializaMapaVazio(mapa *terreno, int x, int y)
{
    int i;
    terreno->mat = calloc(x, sizeof(int *));
    for (i = 0; i < x; i++)
    {
        terreno->mat[i] = calloc(y, sizeof(int));
    }
    terreno->tamanhox = x;
}

// função para desalocar
void desalocaMapa(mapa terreno)
{
    for (int i = 0; i < terreno.tamanhox; i++)
    {
        free(terreno.mat[i]);
    }
    free(terreno.mat);
}
