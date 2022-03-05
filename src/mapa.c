#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <time.h>
#include "mapa.h"

#define inf INT_MAX
#define MAX_LINHA 1000

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

// função responsável por ler o arquivo de entrada e transformar em uma matriz reponsável por armazenar o mapa
void leArqv(char *path)
{
    FILE *arq,*arqcsv;
    char Linha[MAX_LINHA];
    mapa terreno;
    memtable table;
    int mapax, mapay, tempoheroi, tempolava, i, j,resultado,qtrecursao;
    clock_t t;
    qtrecursao = 0;
    arq = fopen(path, "rt");
    if (!arq)
    {
        printf("Problemas na abertura do arquivo\n");
        return;
    }
    if (!feof(arq))
    {

        fscanf(arq, "%d %d %d %d", &mapax, &mapay, &tempoheroi, &tempolava);
        fgets(Linha, MAX_LINHA, arq);
        inicializaMapaVazio(&terreno, mapax, mapay,tempolava);
        for (i = 0; i < mapax; i++)
        {
            fgets(Linha, MAX_LINHA, arq);
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
    arqcsv = fopen("./data/desempenho.csv","a");
    t = clock();
    for(i=terreno.tamanhoy-1; i>=0; i--){
        qtrecursao++;
        resultado = calcDp(&table,terreno,mapax-1,i,tempoheroi,&qtrecursao);
    }
    t = clock() - t;
    fprintf(arqcsv,"%d;%d;%d;%.2lf\n",terreno.tamanhox,terreno.tamanhoy,qtrecursao,((double)t)/((CLOCKS_PER_SEC/1000)));
    fclose(arqcsv);
    imprimeResultado(table,(terreno.tempolava*terreno.tamanhox));
    desalocaMemtable(table);
    desalocaMapa(terreno);
}

// função responsável por calcular a direção da movimentação do heroi de acordo com sua posição atual
int calcDp(memtable *table, mapa terreno, int i, int j, int tempoheroi, int *qtrecursao){
    int esq, dir, menortempo;
    (*qtrecursao)++;
    if (i == -1) return 0;
    if (j < 0 || j == terreno.tamanhoy) return inf;
    if (table->mat[i][j].peso == inf || terreno.mat[i][j] > terreno.tempolava * (terreno.tamanhox-i)) return table->mat[i][j].peso = inf;
    if (table->mat[i][j].foiCalculado) return table->mat[i][j].peso;
    table->mat[i][j].foiCalculado = true;
    if(i % 2 == 0){
        esq = calcDp(table,terreno,i-1,j-1,tempoheroi,qtrecursao);
        dir = calcDp(table,terreno,i-1,j,tempoheroi,qtrecursao);
    }
    else{
        esq = calcDp(table,terreno,i-1,j,tempoheroi,qtrecursao);
        dir = calcDp(table,terreno,i-1,j+1,tempoheroi,qtrecursao);
    }
    table->mat[i][j].direcao = esq < dir ? esquerda : direita;
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
