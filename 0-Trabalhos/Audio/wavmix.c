#include "acesso.h"
#include "tratamento.h"

int main(int argc, char **argv)
{

    FILE *ENTRADA = stdin, *SAIDA = stdout;
    int opt;
    Audio_t *audio, *apendice;
    int saida_selecionada = 0;

    /*===================================================*/

    while ((opt = getopt(argc, argv, "o:")) != -1)
    {
        switch (opt)
        {
        case 'o':
            saida_selecionada = 1;
            SAIDA = fopen(optarg, "w+");
            if (!SAIDA)
            {
                fprintf(stderr, "Erro ao criar saída de dados\n");
                exit(1);
            }
            break;

        default:
            fprintf(stderr, "Usage: ./wavcat file1 file2 ... filen -o [FILE] \n");
            exit(1);
        }
    }

    /*===================================================*/

    // Checa o numero de argumentos, tem que existir pelo menos 2 audios 
    if ((saida_selecionada && (argc < 5)) || (!saida_selecionada && (argc < 2)))
    {
        fprintf(stderr, "Faltam argumentos\n");
        exit(1);
    }

    audio = malloc(sizeof(Audio_t));
    if (!audio)
    {
        fprintf(stderr, "Erro ao alocar espaço para a audio\n");
        exit(1);
    }

    apendice = malloc(sizeof(Audio_t));
    if (!apendice)
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
            ENTRADA = freopen(argv[i], "r",ENTRADA);
            if (!ENTRADA)
            {
                fprintf(stderr, "Nao foi possivel abrir o arquivo");
                free(audio);
                free(apendice);
                exit(1);
            }

            ler_audio_wav(ENTRADA, apendice);
            mixar_audios(audio, apendice);
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
