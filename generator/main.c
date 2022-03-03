#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mapa.h"

int main()
{

    int tamanhox, tamanhoy, tempoheroi, tempolava,item;
    char nomearq[100];
    char nomearq2[100];
    FILE *arquivo;
    mapa terreno;
    time_t t;
    srand((unsigned) time(&t));
    printf("Digite os parametros (altura, largura, custo de movimentacao do heroi e tempo de movimentacao da lava) para criacao do mapa: \n");
    scanf("%d %d %d %d", &tamanhox, &tamanhoy, &tempoheroi, &tempolava);
    inicializaMapaVazio(&terreno,tamanhox,tamanhoy);
    for (int i = 0; i < tamanhox; i++){
        for (int j = 0; j < tamanhoy; j++){
            terreno.mat[i][j] = 1 + (rand() % 1999);
        }
    }
    strcpy(nomearq,"../data/");
    printf("Digite o nome do arquivo para armazenar o mapa: \n");
    scanf("%s",nomearq2);
    strcat(nomearq,nomearq2);
    strcat(nomearq,".txt");
    arquivo = fopen(nomearq, "w");
    fprintf(arquivo,"%d %d %d %d\n",tamanhox, tamanhoy, tempoheroi, tempolava);
    for (int i = 0; i < tamanhox; i++){
        for (int j = 0; j < tamanhoy; j++){
            if (terreno.mat[i][j] >= 1500) fprintf(arquivo,"### ");
            else if (terreno.mat[i][j] >= 1000) fprintf(arquivo,"000 ");
            else fprintf(arquivo,"%.3d ",terreno.mat[i][j]);
        }
        fprintf(arquivo,"\n");
    }
    fclose(arquivo);
    desalocaMapa(terreno);
    return 0;
}