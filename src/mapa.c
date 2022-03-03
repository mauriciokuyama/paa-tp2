#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "mapa.h"
#define inf INT_MAX

// função pra inicializar matriz terreno com 0
void inicializaMapaVazio(mapa *terreno, int x, int y, int tempolava)
{
    int i;
    terreno->tamanhox = x;
    terreno->tamanhoy = y;
    terreno->tempolava = tempolava;
    terreno->mat = calloc(x, sizeof(int *));
    for (i = 0; i < x; i++)
    {
        terreno->mat[i] = calloc(y, sizeof(int));
    }
}

void leArqv(char *path)
{
    FILE *arq;
    char Linha[1000];
    mapa terreno;
    memtable table;
    int mapax, mapay, tempoheroi, tempolava, i, j,resultado;
    arq = fopen(path, "rt");
    if (!arq)
    {
        printf("Problemas na abertura do arquivo\n");
        return;
    }
    if (!feof(arq))
    {

        fscanf(arq, "%d %d %d %d", &mapax, &mapay, &tempoheroi, &tempolava);
        fgets(Linha, 1000, arq);
        inicializaMapaVazio(&terreno, mapax, mapay,tempolava);
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
    fclose(arq);
    inicializaMemtableVazia(&table,mapax,mapay);
    for(i=terreno.tamanhoy-1; i>=0; i--){
        resultado = calcDp(&table,terreno,mapax-1,i,tempoheroi);
    }
    imprimeResultado(table,(terreno.tempolava*terreno.tamanhox));
    desalocaMemtable(table);
    desalocaMapa(terreno);
}

int calcDp(memtable *table, mapa terreno, int i, int j, int tempoheroi){
    int esq, dir, menortempo;
    if (i == -1) return 0;
    if (j < 0 || j == terreno.tamanhoy) return inf;
    if (table->mat[i][j].peso == inf || terreno.mat[i][j] > terreno.tempolava * (terreno.tamanhox-i)) return table->mat[i][j].peso = inf;
    if (table->mat[i][j].iscalc) return table->mat[i][j].peso;
    table->mat[i][j].iscalc = true;
    if(i % 2 == 0){
        esq = calcDp(table,terreno,i-1,j-1,tempoheroi);
        dir = calcDp(table,terreno,i-1,j,tempoheroi);
    }
    else{
        esq = calcDp(table,terreno,i-1,j,tempoheroi);
        dir = calcDp(table,terreno,i-1,j+1,tempoheroi);
    }
    table->mat[i][j].direct = esq < dir ? esquerda : direita;
    menortempo = (esq < dir ? esq : dir);
    if (menortempo == inf) return table->mat[i][j].peso = inf;
    return table->mat[i][j].peso = tempoheroi + terreno.mat[i][j] + menortempo;
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
