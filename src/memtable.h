#ifndef MEMTABLE_H
#define MEMTABLE_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//iscalc = false, nao calculado, iscalc = true, ja calculado
typedef enum {direita, esquerda} Direct;
typedef struct Item{
    int peso;
    Direct direct,iscalc;
}item;

typedef struct Memtable
{
    item **mat;
    int tamanhox, tamanhoy;
} memtable;

void inicializaMemtableVazia(memtable *table, int x, int y);
void imprimeResultado(memtable table);
void desalocaMemtable(memtable table);


#endif
