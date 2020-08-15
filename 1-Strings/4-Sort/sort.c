#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX    100
#define BUFFER 500

int funcomp(const void *a, const void *b){
        return strcmp(*(char**) a, *(char**) b);
}

int main(int argc, char **argv){

    char **hist;
    char *c,palavra[MAX];
    int nr_p = 0;

    // Aloca dinamicamente
    hist = (char**) malloc (sizeof(char*) * BUFFER);
    for (int i = 0; i < BUFFER ;i++)
        hist[i] = (char*) malloc (sizeof(char)*MAX);

    // Le palavras e salva elas até encontrar fim de entrada
    c = fgets(palavra,MAX,stdin);
    while(nr_p < BUFFER && c != NULL){
        palavra[strlen(palavra)-1]='\0';
        strcpy(hist[nr_p++], palavra);
        c = fgets(palavra,MAX,stdin);
    }

    // Ordena elas
    qsort(hist, nr_p, sizeof(char*),funcomp);
    
    

    // Imprime
    printf("----Ordenando----\n");    
    for (int i = 0; i < nr_p; i++)
        puts(hist[i]);


    // Libera o espaco alocado
    for (int i = 0; i < BUFFER; i++)
        free(hist[i]);
    free(hist);
    
    return 0;
}

