// GRR20190372 Jorge Lucas Vicilli Jabczenski

#include "dicionario.h"

// Carrega o dicionario em RAM
String *carregaDicionario(FILE *dic, unsigned long int *contador){

	String *ptr;
	int iteracao = 1;

	*contador = 0;

	ptr = (String *) malloc (sizeof(String)*MAX_PALAVRAS); // Aloca dinamicamente o local das palavras
	if (!ptr)
	{													 // Confere se a alocação ocorreu com sucesso
		perror("MALLOC FAILED");
		exit(1);
	}

	fscanf(dic, "%ms", &ptr[*contador]); // Lê a primeira palavra
	while(ptr[*contador] != NULL)
	{
		(*contador)++;
		if ((*contador) >= iteracao*MAX_PALAVRAS) // Caso o número de palavras ultrapasse o número de alocações
		{
			iteracao++;
			ptr = realloc (ptr, iteracao*MAX_PALAVRAS*sizeof(String)); // Realoca mais MAX_PALAVRAS lugares de palavras
		}
		fscanf(dic, "%ms", &ptr[(*contador)]);
	}

	return ptr;
}

// Funcao utilizada no qsort e bsearch
int funcaoComparacao(const void *p1,const void *p2) {
	return strcasecmp(*(char **) p1, *(char **) p2);
}

// Acha as palavras erradas no texto e bota elas entre []
void processaTexto(String *dicionario, unsigned long int tamanho_dicionario){

	int contador;
	String palavra;
	char c;

	palavra = (String) malloc (TAM_PALAVRA*sizeof(char)); // Aloca a palavra que será usada como comparação
	if (!palavra) // Verifica se foi alocada corretamente
	{
		perror("MALLOC FAILED");

		// Desaloca todo o espaço usado
		desalocaDicionario(dicionario, tamanho_dicionario);
		exit(1);
	}

	contador = 0;
	c = getchar();
	while(c != EOF){
		while(!isalpha(c) && c != EOF){
			printf("%c", c);
			c = getchar();
		}
		while(isalpha(c) && c != EOF){
			palavra[contador++] = c;
			c = getchar();
		}
		palavra[contador] = '\0';
		if (strcmp(palavra, "")){
			if (bsearch(&palavra,dicionario,tamanho_dicionario,sizeof(String),funcaoComparacao))
				printf("%s", palavra);
			else
				printf("[%s]", palavra);
		contador = 0;
		}
	}
	free(palavra);
}

// Libera o espaco alocado pelo dicionario
void desalocaDicionario(String *dicionario, unsigned long int tamanho_dicionario){

	for (unsigned long int i = 0; i < tamanho_dicionario; i++)
		free(dicionario[i]);
	free(dicionario);

}
