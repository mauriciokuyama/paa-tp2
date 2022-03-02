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

void imprimeResultado(memtable table, int tempolimite)
{
    int i, j, menorpeso, menorpesoj;
    i = table.tamanhox - 1;
    j = 0;
    menorpeso = table.mat[i][j].peso;
    for (j = 1; j < table.tamanhoy; j++)
    {
        if (menorpeso > table.mat[i][j].peso)
        {
            menorpeso = table.mat[i][j].peso;
            menorpesoj = j;
        }
    }
    if (menorpeso <= tempolimite)
    {
        j = 0;
        while (j < table.tamanhox)
        {
            printf("%d %d\n", i, menorpesoj);
            if (i % 2 == 0)
            {
                if (table.mat[i][menorpesoj].direct == esquerda)
                {
                    menorpesoj--;
                }
            }
            else
            {
                if (table.mat[i][menorpesoj].direct == direita)
                {
                    menorpesoj++;
                }
            }
            i--;
            j++;
        }
    }
    else printf("Samus falhou na missao");
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