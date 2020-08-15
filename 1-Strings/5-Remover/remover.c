#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define MAX 100

int main(int argc, char **argv){ 

	int i;
	char palavra[MAX],c;

	fgets(palavra, MAX, stdin);

	i = 0;
	c = palavra[i]; 

	while(c != '\0'){
		if (!isalnum(c) && c != 32){
			for (int j = i+1; j < strlen(palavra)+1; j++)
				palavra[j-1] = palavra[j];
				puts(palavra);
		} else {
			i++;
		}
		c = palavra[i]; 
	}

	puts(palavra);
	printf("A palavra tem tamanho %d\n", strlen(palavra));

	return 0;
}
