#include "acesso.h"
#include "tratamento.h"

int main(int argc, char **argv)
{

	FILE *ENTRADA = stdin, *SAIDA = stdout;
	int opt;
	Audio_t *audio;
	int delay = 1000;
	float level = 0.5;

	/*===================================================*/

	while ((opt = getopt(argc, argv, "i:o:l:t:")) != -1)
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
			level = atof(optarg);
			if (level < 0.0 || level > 1.0)
			{
				fprintf(stderr, "Level deve ser um valor entre 0.0 e 1.0\n");
				exit(1);
			}
			break;

		case 't':
			delay = atoi(optarg);
			if (delay < 0)
			{
				fprintf(stderr, "time deve ser um valor maior que 0\n");
				exit(1);
			}
			break;

		default:
			fprintf(stderr, "Usage: ./wavecho -i [FILE] -o [FILE] -t delay -l level\n");
			exit(1);
		}
	}

	/*===================================================*/

	audio = malloc(sizeof(Audio_t));
	if (!audio)
	{
		fprintf(stderr, "Erro ao alocar espaço para a audio\n");
		exit(1);
	}

	ler_audio_wav(ENTRADA, audio);

	// Aplica o eco
	ecoar(audio, level, delay);

	envia_audio(SAIDA, audio);

	fechar_streams(ENTRADA, SAIDA);

	free(audio->dados);
	free(audio);

	return 0;
}
