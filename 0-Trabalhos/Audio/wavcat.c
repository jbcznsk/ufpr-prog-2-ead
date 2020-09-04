#include "acesso.h"
#include "tratamento.h"

void tratar_argumentos(int argc, char **argv, FILE *ENTRADA, FILE *SAIDA);

int main(int argc, char **argv)
{

	FILE *ENTRADA = stdin, *SAIDA = stdout;
	Audio_t *audio, *apendice;

	tratar_argumentos(argc, argv, ENTRADA, SAIDA);

	// Checa o numero de argumentos
	if (((SAIDA != stdout) && (argc < 5)) || ((SAIDA == stdout) && (argc < 2)))
	{
		fprintf(stderr, "Faltam argumentos\n");
		exit(1);
	}

	/*===================================================*/

	// Aloca os espaços para os audios
	audio = malloc(sizeof(Audio_t));
	if (!audio)
	{
		fprintf(stderr, "Erro ao alocar espaço para a audio\n");
		exit(1);
	}

	apendice = malloc(sizeof(Audio_t));
	if (!audio)
	{
		free(audio);
		fprintf(stderr, "Erro ao alocar espaço para a audio\n");
		exit(1);
	}

	/*===================================================*/

	int i = 1;
	// Procura o primeiro argumento que não seja -o [file]
	while (i < argc)
	{
		if (!strcmp("-o", argv[i]))
		{
			i++;
		}
		else
		{
			ENTRADA = fopen(argv[i], "r");
			if (!ENTRADA)
			{
				fprintf(stderr, "Nao foi possivel abrir o arquivo");
				free(audio);
				free(apendice);
				exit(1);
			}
			break;
		}
		i++;
	}

	ler_audio_wav(ENTRADA, audio);

	i++;
	while (i < argc)
	{
		if (!strcmp("-o", argv[i]))
		{
			i++;
		}
		else
		{
			ENTRADA = freopen(argv[i], "r", ENTRADA);
			if (!ENTRADA)
			{
				fprintf(stderr, "Nao foi possivel abrir o arquivo");
				free(audio->dados);
				free(audio);
				free(apendice);
				exit(1);
			}

			ler_audio_wav(ENTRADA, apendice);
			concatatenar_audios(audio, apendice);
			free(apendice->dados);
		}

		i++;
	}

	envia_audio(SAIDA, audio);

	fechar_streams(ENTRADA, SAIDA);

	free(audio->dados);
	free(audio);
	free(apendice);
	return 0;
}

void tratar_argumentos(int argc, char **argv, FILE *ENTRADA, FILE *SAIDA)
{
	int opt;
	while ((opt = getopt(argc, argv, "i:o:")) != -1)
	{
		switch (opt)
		{

		// Entrada
		case 'i':
			ENTRADA = freopen(optarg, "r", ENTRADA);
			if (!ENTRADA)
			{
				fprintf(stderr, "Não foi possível encontrar o arquivo\n");
				exit(1);
			}
			break;

		// Saída
		case 'o':
			SAIDA = freopen(optarg, "w+", SAIDA);
			if (!SAIDA)
			{
				fprintf(stderr, "Erro ao criar saída de dados\n");
				exit(1);
			}
			break;

		default:
			fprintf(stderr, "Usage: ./wavcat file1 file2 ... fileN -o [FILE] \n");
			exit(1);
		}
	}
}
