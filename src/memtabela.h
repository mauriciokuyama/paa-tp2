#ifndef Memtabela_H
#define Memtabela_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//foiCalculado = false, nao calculado, foiCalculado = true, ja calculado
typedef enum {direita, esquerda} Direcao;
typedef struct Item {
    int peso;
    Direcao direcao;
    bool foiCalculado;
} item;

typedef struct Memtabela {
    item **mat;
    int tamanhox, tamanhoy;
} memtabela;

void inicializaMemtabelaVazia(memtabela *tabela, int x, int y);
void imprimeResultado(memtabela tabela,int tempolimite);
void desalocaMemtabela(memtabela tabela);


#endif
