#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define MAX 100

int busca(char *agulha, char *palheiro){

    if ((agulha[0] == '\0') || (palheiro[0] == '\0'))
        return -2;

    int tam_agulha   = strlen(agulha);
    int tam_palheiro = strlen(palheiro);
    int achou = 1;

    printf("Tamanho agulha: %d\nTamanho palheiro: %d\n", tam_agulha, tam_palheiro);

    if (tam_agulha > tam_palheiro)
        return -3;

    for (int i = 0; i <= (tam_palheiro-tam_agulha); i++){
        int achou = 1;
        for (int j = 0; j < tam_agulha; j++){
            printf("comparando %c com %c\n",agulha[j],palheiro[j+i]);
            if (agulha[j] != palheiro[i+j]){
                achou = 0;
                break;
            }
        }
        if (achou)
            return i;
    }    
    return -1;
}

int main(int argc, char **argv){ 

    char palheiro[MAX], agulha[MAX];

    printf("Entre com sua string principal: ");
    fgets(palheiro, MAX, stdin);
    palheiro[strlen(palheiro)-1] = '\0';

    printf("Entre com a busca: ");
    fgets(agulha, MAX, stdin);
    agulha[strlen(agulha)-1] = '\0';

    int resultado = busca(agulha, palheiro);


    switch(resultado){
        case -3:
            puts("Agulha maior que palheiro");
        break;
        case -2:
            puts("String(s) nula(s)");
        break;
        
        case -1:
            puts("Agulha nao encontrada");
        break;

        default:
            printf("A agulha foi encontrada na posição %d do palheiro\n", resultado);
    }
    
    return 0;
}
