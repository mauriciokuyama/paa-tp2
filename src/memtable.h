#ifndef MEMTABLE_H
#define MEMTABLE_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//foiCalculado = false, nao calculado, foiCalculado = true, ja calculado
typedef enum {direita, esquerda} Direcao;
typedef struct Item
{
    int peso;
    Direcao direcao, foiCalculado;
} item;

typedef struct Memtable
{
    item **mat;
    int tamanhox, tamanhoy;
} memtable;

void inicializaMemtableVazia(memtable *table, int x, int y);
void imprimeResultado(memtable table,int tempolimite);
void desalocaMemtable(memtable table);


#endif
