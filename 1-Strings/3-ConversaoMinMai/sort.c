#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX    100
#define BUFFER 500

int main(int argc, char **argv){ 
   
    char hist[BUFFER][MAX];
    char *c,palavra[MAX];
    int nr_p = 0;

    strcpy(hist[0], "OLA");
    puts(hist[0]);


    c = fgets(palavra,MAX,stdin);
    while(nr_p < BUFFER && c != NULL){
        palavra[strlen(palavra)-1]='\0';
        puts(palavra);
        c = fgets(palavra,MAX,stdin);
    }
    return 0;
}
