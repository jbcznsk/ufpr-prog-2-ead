#include "dicionario.h"

int main ()
{
	setlocale (LC_ALL, "pt_BR.ISO-8859-1") ; // Configura o locale para ISO-8859-1

/*=====================================================================================*/

	FILE *dic;
	String *dicionario;
	unsigned long int tamanho_dicionario;

/*=====================================================================================*/
/*                                                                                     */
	dic = fopen("/usr/share/dict/brazilian", "r"); // Abre o dicionario
	if (!dic) // Teste para verificar se o dicionario foi aberto com sucesso
	{ 
		perror("Dicionário não aberto");
		exit(1);
	}

	// Dicionario carregado em RAM
	dicionario = carregaDicionario(dic, &tamanho_dicionario);
    
	// Ordena o dicionário, sem ser "case-sensitive"
	qsort(dicionario, tamanho_dicionario, sizeof(char*), funcaoComparacao); 
   
	// Acha as palavras que não existem no dicionário e bota elas entre []
	processaTexto(dicionario, tamanho_dicionario);

	// Desaloca todo o espaço usado
	for (int i = 0; i  < tamanho_dicionario; i++)
		free(dicionario[i]);
	free(dicionario);

	// Fecha o arquivo
	fclose (dic); 
	return (0);
}
