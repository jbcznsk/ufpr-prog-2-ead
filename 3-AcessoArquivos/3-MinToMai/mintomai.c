#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>


int main(int argc, char **argv)
{

    FILE *arqmin, *arqmai;
    char c;


    arqmin = fopen("minusc.txt", "r");
    arqmai = fopen("maisc.txt", "w");
    if(!arqmin || !arqmai)
    {
        perror("Erro ao abrir arquivos");
        exit(1);
    }

    //fscanf(arqmin, "%s", line);
    c = fgetc(arqmin);
    while(c != EOF)
    {
        char C = toupper(c);
        fputc(C, arqmai);

        c = fgetc(arqmin);
    }

    return 0;
}