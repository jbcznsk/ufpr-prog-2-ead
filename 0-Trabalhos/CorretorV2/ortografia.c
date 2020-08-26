// GRR20190372 Jorge Lucas Vicilli Jabczenski

#include "dicionario.h"

int main ()
{
	// Configura o locale para ISO-8859-1
	setlocale (LC_ALL, "pt_BR.ISO-8859-1") ;

/*=====================================================================================*/

	FILE *dic;
	String *dicionario;
	unsigned long int tamanho_dicionario;

/*=====================================================================================*/

	// Abre o dicionario
	dic = fopen("/usr/share/dict/brazilian", "r");
	if (!dic)
	{
		fprintf(stderr,"Dicionario nao encontrado em /usr/share/brazilian, procurando no diretorio local\n");
		dic = fopen("brazilian", "r");
		if (!dic)
		{
			fprintf(stderr,"Dicionario nao encontrado no diretorio local, encerrando o programa\n");
			exit(1);
		}
	}

	// Dicionario carregado em RAM
	dicionario = carregaDicionario(dic, &tamanho_dicionario);

	// Ordena o dicionário, sem ser "case-sensitive"
	qsort(dicionario, tamanho_dicionario, sizeof(String), funcaoComparacao);

	// Acha as palavras que não existem no dicionário e bota elas entre []
	processaTexto(dicionario, tamanho_dicionario);

	// Desaloca todo o espaço usado
	desalocaDicionario(dicionario, tamanho_dicionario);

	// Fecha o arquivo
	fclose (dic);

	return (0);
}
