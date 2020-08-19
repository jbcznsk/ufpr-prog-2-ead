#include <stdio.h>
#include <stdlib.h>

#define OUT "numeros.dat"

typedef struct 
{
	int idade;
	char nome[20];
	float media;


} dados_t;

int main(int argc, char **argv)
{
	
	dados_t dado = {20, "Jorge", 9.45};
	dados_t recebido;

	FILE *saida;

	saida = fopen(OUT, "w+");
	if (!saida)
	{
		exit(1);
	}

	fwrite(&dado, sizeof(dados_t),1,saida);
	
	freopen(OUT, "r+", saida);

	fread(&recebido, sizeof(dados_t),1, saida);

	puts(recebido.nome);

	fclose(saida);




	return 0;
}
