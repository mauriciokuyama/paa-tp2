#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mapa.h"

void leArqv(char *path)
{
    FILE *arq;
    char Linha[100];
    mapa terreno;

    int mapax, mapay, tempoh, tempol, i, j;
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
                    terreno.mat[i][j] = -1;
                }
                else
                {
                    terreno.mat[i][j] = atoi(buffer);
                }
            }
        }
        imprimeMapa(terreno);
    }

    desalocaMapa(terreno);
}

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