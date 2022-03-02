#ifndef MEMTABLE_H
#define MEMTABLE_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//direct = false, movimento à esquerda, direct = true, movimento à direita
//iscalc = false, nao calculado, iscalc = true, ja calculado
typedef struct Item{
    int peso;
    bool direct,iscalc;
}item;

typedef struct Memtable
{
    item **mat;
    int tamanhox, tamanhoy;
} memtable;

void inicializaMemtableVazia(memtable *table, int x, int y);
void imprimeMemtable(memtable table);
void desalocaMemtable(memtable table);


#endif
