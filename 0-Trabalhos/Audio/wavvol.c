#include "wav.h"

int main(int argc, char **argv){

	FILE *ENTRADA = stdin, *SAIDA = stdout;
	int opt;
	float level = 1.0;
	Musica_t *musica;

/*===================================================*/

	while((opt = getopt(argc, argv, "i:o:l:"))!= -1 )
	{
		switch (opt)
		{
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

			// Volume
		  	case 'l':
				level = atof(optarg);
				if (level < 0.0 || level > 10.0){
					fprintf(stderr, "Level deve ser um valor entre 0.0 e 10.0\n");
					exit(1);
				}
		  	break;

			default:
				fprintf(stderr, "Usage: ./wavvol -i [FILE] -o [FILE] -l V\n");
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

	ler_cabecalho_wav(ENTRADA, musica);
	ler_musica(ENTRADA, musica);


	// Ajuste do volume, respeitando os valores máximos
	for (int i = 0; i < musica->tamanho; i++){

		if (musica->dados[i] * level >= VOLMAX)
			musica->dados[i] = VOLMAX;
		else if (musica->dados[i] * level <= -VOLMAX)
			musica->dados[i]=  -VOLMAX;
		else 
			musica->dados[i] *= level;
	}


	fwrite(&musica->cab, sizeof(Cabecalho_t),1, SAIDA);
	fwrite(musica->dados, sizeof(int16_t),musica->tamanho, SAIDA);

	fclose(ENTRADA);
	fclose(SAIDA);
	free(musica);

  return 0;
}
