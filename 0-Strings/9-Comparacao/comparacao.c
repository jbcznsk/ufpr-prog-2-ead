#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define MAX  10000 
#define ITER 1000000   
#define MY 1
#define TEST 3                                  

int my_strlen(const char *s){
    int i = 0;
    while(s[i++] != '\0');
    return i-1;
}

void my_strcpy(char *dest, const char *src){
    memcpy(dest,src,my_strlen(src)+1);
}

void my_strcat(char *dest, const char *src){
    my_strcpy(dest+my_strlen(dest), src);
}


int main(int argc, char **argv){ 

    char palavra1[MAX]=" O design de jogos eletrônicos é o processo onde se projeta o conteúdo e as regras de um videogame no estágio de pré-produção, [1] bem como o desenvolvimento da jogabilidade, da ambientação, do enredo e dos personagens no estágio de produção. Pode-se dizer que designer de um jogo é muito parecido com o diretor de um filme; o designer é o visionário do jogo e controla os elementos artísticos e técnicos a fim de efetuar sua visão. [2] O design de videogames requer competência artística e técnica, além de habilidades de escrita";

    char palavra2[MAX]="À medida que a indústria maturou e adotou metodologias de produção alternativas, como o Desenvolvimento ágil de software, a função do designer de jogos principal começou a se dividir - alguns estúdios passaram a enfatizar o modelo mais focado na visão do autor principal enquanto outros no modelo mais orientado para o talento da equipe como um todo. Na indústria de videogames, o design de videogames é geralmente chamado de game design (design de jogos), que é um termo mais abrangente quando usado fora dela.";

    char palavra3[MAX];
    char palavra4[MAX];

    for (unsigned long int i = 0; i < ITER; i++)
    {
        #if  MY
            #if TEST == 1
                my_strlen(palavra1);
                my_strlen(palavra2);
            #elif TEST == 2
                my_strcpy(palavra3, palavra1);
                my_strcpy(palavra4, palavra2);
            #elif TEST == 3
                my_strcat(palavra1, palavra2);
            #endif
        #else
            #if TEST == 1
                strlen(palavra1);
                strlen(palavra2);
            #elif TEST == 2
                strcpy(palavra3,palavra1);
                strcpy(palavra4, palavra2);
            #elif TEST == 3
                strcat(palavra1, palavra2);
            #endif
        #endif
    }

    return 0;
}
