#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int my_strlen(char *string){
    int len = 0;
    char c = string[len++];
    while(c != '\0')
        c = string[len++];
    return len-1;
}

int main(int argc, char **argv){ 

    char *entrada;

    scanf("%20ms",&entrada);

    printf("%d\n", my_strlen(entrada));

    return 0;
}
