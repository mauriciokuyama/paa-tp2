#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mapa.h"
#define inf 1000000000

// função pra inicializar matriz terreno com 0
void inicializaMapaVazio(mapa *terreno, int x, int y)
{
    int i;
    terreno->tamanhox = x;
    terreno->tamanhoy = y;
    terreno->mat = calloc(x, sizeof(int *));
    for (i = 0; i < x; i++)
    {
        terreno->mat[i] = calloc(y, sizeof(int));
    }
}

void leArqv(char *path)
{
    FILE *arq;
    char Linha[100];
    mapa terreno;
    memtable table;
    int mapax, mapay, tempoh, tempol, i, j,resultado;
    arq = fopen(path, "rt");
    if (!arq)
    {
        printf("Problemas na abertura do arquivo\n");
        return;
    }
    if (!feof(arq))
    {

        fscanf(arq, "%d %d %d %d", &mapax, &mapay, &tempoh, &tempol);
        fgets(Linha, 100, arq);
        inicializaMapaVazio(&terreno, mapax, mapay);
        for (i = 0; i < mapax; i++)
        {
            fgets(Linha, 100, arq);
            int k;
            if (i % 2 == 0)
            {
                k = 0;
            }
            else
            {
                k = 2;
            }
            char buffer[4];
            buffer[3] = '\0';
            for (j = 0; j < mapay; j++)
            {
                buffer[0] = Linha[k];
                buffer[1] = Linha[k + 1];
                buffer[2] = Linha[k + 2];
                k += 4;
                if (strcmp(buffer, "###") == 0)
                {
                    terreno.mat[i][j] = inf;
                }
                else
                {
                    terreno.mat[i][j] = atoi(buffer);
                }
            }
        }
    }
    inicializaMemtableVazia(&table,mapax,mapay);
    for(i=terreno.tamanhoy-1; i>=0; i--){
        resultado = calcDp(&table,terreno,mapax-1,i,tempoh);
    }
    imprimeMemtable(table);
    desalocaMemtable(table);
    desalocaMapa(terreno);
}

int calcDp(memtable *table, mapa terreno, int i, int j, int movecost){
    int esq, dir;
    if (i == -1) return 0;
    if (j < 0 || j == terreno.tamanhoy) return inf;
    if (table->mat[i][j].iscalc) return table->mat[i][j].peso;
    if (terreno.mat[i][j] >= inf) return inf;
    table->mat[i][j].iscalc = true;
    if(i % 2 == 0){
        esq = calcDp(table,terreno,i-1,j-1,movecost);
        dir = calcDp(table,terreno,i-1,j,movecost);
        table->mat[i][j].direct = esq < dir ? false : true;      
        return table->mat[i][j].peso = movecost + terreno.mat[i][j] + (esq < dir ? esq : dir);
    }
    esq = calcDp(table,terreno,i-1,j,movecost);
    dir = calcDp(table,terreno,i-1,j+1,movecost);
    table->mat[i][j].direct = esq < dir ? false : true; 
    return table->mat[i][j].peso = movecost + terreno.mat[i][j] + (esq < dir ? esq : dir);
}


void imprimeMapa(mapa terreno)
{
    int i, j;
    for (i = 0; i < terreno.tamanhox; i++)
    {
        for (j = 0; j < terreno.tamanhoy; j++)
        {
            printf("%d ", terreno.mat[i][j]);
        }
        printf("\n");
    }
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