#include <stdio.h>
#include <strings.h>
#include <string.h>

int main(){

    char *endereco,**nomes;

    FILE *arq;

    arq = fopen("nomes","r");
    
    endereco = "rua dos bobos,0";
    
    for (int i = 0; i < strlen(endereco); i++)
        putchar(endereco[i]);
    putchar('\n');

    puts(endereco);


    return 0;
}
