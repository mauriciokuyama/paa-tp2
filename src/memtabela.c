#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memtabela.h"

// função pra inicializar matriz terreno com 0
void inicializaMemtabelaVazia(memtabela *tabela, int x, int y)
{
    int i;
    tabela->tamanhox = x;
    tabela->tamanhoy = y;
    tabela->mat = calloc(x, sizeof(item *));
    for (i = 0; i < x; i++)
    {
        tabela->mat[i] = calloc(y, sizeof(item));
    }
}

// função pra imprimir resultado de acordo com a posição atual do heroi
void imprimeResultado(memtabela tabela, int tempolimite)
{
    int i, j, menorpeso, menorpesoj;
    i = tabela.tamanhox - 1;
    j = 0;
    menorpesoj = 0;
    menorpeso = tabela.mat[i][j].peso;
    for (j = 1; j < tabela.tamanhoy; j++)
    {
        if (menorpeso > tabela.mat[i][j].peso)
        {
            menorpeso = tabela.mat[i][j].peso;
            menorpesoj = j;
        }
    }
    if (menorpeso <= tempolimite)
    {
        j = 0;
        while (j < tabela.tamanhox)
        {
            printf("%d %d\n", i, menorpesoj);
            if (i % 2 == 0)
            {
                if (tabela.mat[i][menorpesoj].direcao == esquerda)
                {
                    menorpesoj--;
                }
            }
            else
            {
                if (tabela.mat[i][menorpesoj].direcao == direita)
                {
                    menorpesoj++;
                }
            }
            i--;
            j++;
        }
    }
    else printf("Samus falhou na missao\n");
}

// função para desalocar
void desalocaMemtabela(memtabela tabela)
{
    for (int i = 0; i < tabela.tamanhox; i++)
    {
        free(tabela.mat[i]);
    }
    free(tabela.mat);
}
