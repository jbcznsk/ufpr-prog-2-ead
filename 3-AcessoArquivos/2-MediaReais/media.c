#include <stdio.h>
#include <stdlib.h>
#include <strings.h>


int main(int argc, char **argv)
{

    FILE *arq;
    char line[101];
    int n = 0;
    float mean = 0;

    arq = fopen("arquivo", "r");
    if (!arq)
    {
        perror("Erro ao abrir arquivo");
        exit(1);
    }


    fgets(line, 101, arq);
    while(!feof(arq))
    {
        n++;
        mean += atof(line);
        fgets(line, 101, arq);

    }

    printf("Mean: %.2f\n", mean/n);
    return 0;
}