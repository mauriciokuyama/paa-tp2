#ifndef MAPA_H
#define MAPA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Mapa
{
    int **mat;
    int tamanhox;
} mapa;

void inicializaMapaVazio(mapa *terreno, int x, int y);
void desalocaMapa(mapa terreno);

#endif