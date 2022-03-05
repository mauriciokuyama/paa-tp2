#include <stdio.h>
#include <string.h>
#include "mapa.h"
#include "memtable.h"

int main(void)
{
    
    char nomeArquivo[100];
    char data[100];
    char buffer[100];
    strcpy(data, "data/");
    printf("Digite o nome do arquivo desejado: Ex: entrada\n");
    fgets(buffer, 100, stdin);
    sscanf(buffer, "%s", nomeArquivo);
    strcat(nomeArquivo, ".txt");
    strcat(data, nomeArquivo);
    leArqv(data);
    return 0;
}
