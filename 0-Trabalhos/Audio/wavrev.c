#include "acesso.h"
#include "tratamento.h"


int main(int argc, char **argv){

	FILE *ENTRADA = stdin, *SAIDA = stdout;
	int opt;
	Musica_t *musica;

/*===================================================*/

	while((opt = getopt(argc, argv, "i:o:"))!= -1 )
	{
		switch (opt) {

            // Entrada
			case 'i':
			ENTRADA = fopen(optarg, "r");
			if(!ENTRADA)
			{
				fprintf(stderr, "Não foi possível encontrar o arquivo\n");
				exit(1);
			}
			break;

			// Saída
			case 'o':
				SAIDA = fopen(optarg,"w+");
		  		if (!SAIDA)
				{
					fprintf(stderr, "Erro ao criar saída de dados\n");
					exit(1);
				}
			break;

			default:
				fprintf(stderr, "Usage: ./wavrev -i [FILE] -o [FILE]\n");
				exit(1);
		}
	}

/*===================================================*/

    musica =  malloc(sizeof(Musica_t));
	if (!musica)
	{
		fprintf(stderr, "Erro ao alocar espaço para a musica\n");
		exit(1);
	}

	
	ler_musica_wav(ENTRADA, musica);

	// Reverte a musica
	reverter_musica(musica);

	envia_musica(SAIDA, musica);

	fclose(ENTRADA);
	fclose(SAIDA);
	free(musica);


	return 0;
}
