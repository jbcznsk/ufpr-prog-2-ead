#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define MAX 100

void limpa_string(char *s){
    int i = 0;
    while(s[i] != '\0'){
        if (!isalnum(s[i])){
            for (int j = i; j < strlen(s); j++){
                s[j] = s[j+1];
            }
        } else {
            if(s[i] <= 90)
                s[i] += 32;
            i++;
        }
    }
}

int palindromo(const char *s){
    for (int i = 0; i < strlen(s)/2+1; i++){
        if (s[i] != s[strlen(s)-i-1])
            return 0;
    }
    return 1;
}

int main(int argc, char **argv){ 

    char entrada[MAX];

    fgets(entrada, MAX, stdin);
    entrada[strlen(entrada)-1] = '\0';

    limpa_string(entrada);
    puts(entrada);

    if (palindromo(entrada))
        puts("Eh palindromo");
    else
        puts("Nao eh palindromo");
    
    return 0;
}
