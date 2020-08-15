#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define MAX 100

int main(int argc, char **argv){ 

    int i,j;
    char palavra[MAX],c,a;

    scanf("%90[^\n]",palavra);

    i = 0;
    c = palavra[i]; 

    while(c != '\0'){
        if (!isalnum(c) && c != 32){
            int tam = strlen(palavra);
            for (int j = tam; j >= i; j--)
                palavra[j+1] = palavra[j];
            palavra[i] = '[';
            i = i+2;
            tam = strlen(palavra);
            for (int j = tam; j >= i; j--){
                palavra[j+1] = palavra[j];
            }
            palavra[i] = ']';
            i = i+1;
        } else {
            i++;
        }
        c = palavra[i]; 
    }

    puts(palavra);
    return 0;
}
