#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>

int main(){

	srand(time(NULL));
	
	FILE *arq;
	
	int16_t vetor[20], leitura[20];

	for (int i = 0; i < 20; i++)
		vetor[i] = (rand() % 10) - 5;

	arq = fopen("arquivo", "w+");

	fwrite(vetor, sizeof(int16_t), 20, arq);
	fread(leitura, sizeof(int16_t),20, arq);

	for (int i = 0; i < 20; i++)
		printf("%d ", vetor[i]);
	putchar('\n');

	return 0;
}
