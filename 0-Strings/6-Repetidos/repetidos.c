#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define MAX 100

int main(int argc, char **argv){ 

    int i,j;
    char palavra[MAX],c,a;

    fgets(palavra, MAX, stdin);
    palavra[strlen(palavra)-1] = '\0';

    i = 1;
    a = palavra[i-1]; 
    c = palavra[i]; 

    while(c != '\0'){
        if(a == c){
            j = i;
            while(palavra[j] != '\0'){
                palavra[j] = palavra[j+1];
                j++;
            }
        } else {
            i++;
        }
        a = palavra[i-1]; 
        c = palavra[i]; 
    }
    puts(palavra);

    return 0;
}
