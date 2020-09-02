#include "acesso.h"
#include "tratamento.h"


int main(int argc, char **argv){

	FILE *ENTRADA = stdin, *SAIDA = stdout;
	int opt;
	Audio_t audio;

/*===================================================*/

	while((opt = getopt(argc, argv, "i:"))!= -1 )
	{
		switch (opt) {
			case 'i':
			ENTRADA = fopen(optarg, "r");
			if(!ENTRADA)
			{
				fprintf(stderr, "Não foi possível encontrar o arquivo\n");
				exit(1);
			}
			break;
			
			default:
				fprintf(stderr, "Usage: ./wavinfo -i [FILE]\n");
				exit(1);
		}
	}

/*===================================================*/

	ler_cabecalho_wav(ENTRADA, &audio);

	imprimir_cabecalho_wav(&audio);

	fechar_streams(ENTRADA, SAIDA);

	return 0;
}
