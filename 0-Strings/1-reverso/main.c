#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <strings.h>

int main(int argc, char **argv){ 

    int tam;
    char *entrada,c;

    // Le e aloca dinamicamente a entrada, limitada a 10 chars
    scanf("%10ms", &entrada);
    
    tam = 0;
    c = entrada[tam++];
    while(c != '\0')
        c = entrada[tam++];

    for (int i = strlen(entrada)-1; i >=0; i--)
        putchar(entrada[i]);
    putchar('\n');

    return 0;
}
