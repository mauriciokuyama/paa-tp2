#ifndef MAPA_H
#define MAPA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Mapa {
    int **mat;
    int tamanhox;
    int tamanhoy;
} mapa;

void leArqv(char *path);
void inicializaMapaVazio(mapa *terreno, int x, int y);
void imprimeMapa(mapa terreno);
void desalocaMapa(mapa terreno);

#endif