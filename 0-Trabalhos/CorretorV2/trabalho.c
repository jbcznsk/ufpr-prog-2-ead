// GRR20190372 Jorge Lucas Vicilli Jabczenski

#include "dicionario.h"

int main ()
{
    setlocale (LC_ALL, "pt_BR.ISO-8859-1") ; // Configura o locale para ISO-8859-1

/*=====================================================================================*/

    FILE *dic;
    String *dicionario;
    unsigned long int tamanho_dicionario;

/*=====================================================================================*/

    dic = fopen("brazilian", "r"); // Abre o dicionario
    if (!dic) // Teste para verificar se o dicionario foi aberto com sucesso
    { 
        perror("Dicionario nao aberto");
        exit(1);
    }

    dicionario = carregaDicionario(dic, &tamanho_dicionario); // Dicionario carregado em RAM
	qsort(dicionario, tamanho_dicionario, sizeof(char*), funcaoComparacao); // Ordena o dicionário, sem ser "case-sensitive"
   
    processaTexto(dicionario, tamanho_dicionario);

    // Desaloca todo o espaço usado
    for (int i = 0; i  < tamanho_dicionario; i++)
        free(dicionario[i]);
    free(dicionario);

    fclose (dic); // Fecha o arquivo
    return (0) ;
}