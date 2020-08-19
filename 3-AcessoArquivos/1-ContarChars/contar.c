#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    FILE *arq;
    char c;
    unsigned int contador = 0;

    arq = fopen("arquivo.txt", "r");
    if (!arq){
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    c = fgetc(arq);
    while(c != EOF)
    {
        putc(c, stdout);
        contador++;
        c = fgetc(arq);
    }

    fclose(arq);

    printf("Numero de caracters: %d\n", contador);

    return 0;
}