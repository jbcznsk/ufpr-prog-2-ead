#include "acesso.h"
#include "tratamento.h"

int main(int argc, char **argv)
{

	FILE *ENTRADA = stdin, *SAIDA = stdout;
	int opt;
	Musica_t *musica;
	float k = 1.0;

	/*===================================================*/

	while ((opt = getopt(argc, argv, "i:o:l:")) != -1)
	{
		switch (opt)
		{

		// Entrada
		case 'i':
			ENTRADA = fopen(optarg, "r");
			if (!ENTRADA)
			{
				fprintf(stderr, "Não foi possível encontrar o arquivo\n");
				exit(1);
			}
			break;

		// Saída
		case 'o':
			SAIDA = fopen(optarg, "w+");
			if (!SAIDA)
			{
				fprintf(stderr, "Erro ao criar saída de dados\n");
				exit(1);
			}
			break;

		case 'l':
			k = atof(optarg);
			if (k < 0.0 || k > 10.0)
			{
				fprintf(stderr, "Level deve ser um valor entre 0.0 e 1\n");
				exit(1);
			}
			break;

		default:
			fprintf(stderr, "Usage: ./wavwide -i [FILE] -o [FILE] -l k\n");
			exit(1);
		}
	}

	/*===================================================*/

	musica = malloc(sizeof(Musica_t));
	if (!musica)
	{
		fprintf(stderr, "Erro ao alocar espaço para a musica\n");
		exit(1);
	}

	ler_musica_wav(ENTRADA, musica);

    // Confere se o efeito é aplicavel
    if(!confere_dois_canais(musica))
    {
        fclose(ENTRADA);
        fclose(SAIDA);
        free(musica->dados);
        free(musica);
    }

	// Aplica o eco
	estereo_amplificado(musica, k);

	envia_musica(SAIDA, musica);

	fclose(ENTRADA);
	fclose(SAIDA);
    free(musica->dados);
	free(musica);

	return 0;
}
