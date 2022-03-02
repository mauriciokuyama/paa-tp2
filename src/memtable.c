#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memtable.h"


// função pra inicializar matriz terreno com 0
void inicializaMemtableVazia(memtable *table, int x, int y)
{
    int i;
    table->tamanhox = x;
    table->tamanhoy = y;
    table->mat = calloc(x, sizeof(item *));
    for (i = 0; i < x; i++)
    {
        table->mat[i] = calloc(y, sizeof(item));
    }
}

void imprimeMemtable(memtable table)
{
    int i, j;
    for (i = 0; i < table.tamanhox; i++)
    {
        for (j = 0; j < table.tamanhoy; j++)
        {
            if(i%2){
                printf("      ");
            }
            printf("peso: %d direcao: %d ", table.mat[i][j].peso,table.mat[i][j].direct);
        }
        printf("\n");
    }
}

// função para desalocar
void desalocaMemtable(memtable table)
{
    for (int i = 0; i < table.tamanhox; i++)
    {
        free(table.mat[i]);
    }
    free(table.mat);
}