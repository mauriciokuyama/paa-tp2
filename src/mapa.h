#ifndef MAPA_H
#define MAPA_H

#include <stdio.h>
#include <stdlib.h>
#include "memtabela.h"

typedef struct Mapa {
    int **mat;
    int tamanhox;
    int tamanhoy;
    int tempolava;
} mapa;

void inicializaMapaVazio(mapa *terreno, int x, int y, int tempolava);
void leArqv(char *path);
int calcDp(memtabela *table, mapa terreno, int i, int j, int tempoh, int *qtrecursao);
void desalocaMapa(mapa terreno);

#endif
