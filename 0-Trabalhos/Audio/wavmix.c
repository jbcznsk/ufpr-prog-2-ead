#include "acesso.h"
#include "tratamento.h"

int main(int argc, char **argv)
{

    FILE *ENTRADA = stdin, *SAIDA = stdout;
    int opt;
    Musica_t *musica, *apendice;
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

    musica = malloc(sizeof(Musica_t));
    if (!musica)
    {
        fprintf(stderr, "Erro ao alocar espaço para a musica\n");
        exit(1);
    }

    apendice = malloc(sizeof(Musica_t));
    if (!apendice)
    {
        free(musica);
        fprintf(stderr, "Erro ao alocar espaço para a musica\n");
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
            if (!musica)
            {
                fprintf(stderr, "Nao foi possivel abrir o arquivo");
                free(musica);
                free(apendice);
                exit(1);
            }
            break;
        }
        i++;
    }

    ler_musica_wav(ENTRADA, musica);

    i++;
    while (i < argc)
    {
        if (!strcmp("-o", argv[i]))
        {
            i++;
        }
        else
        {
            ENTRADA = fopen(argv[i], "r");
            if (!musica)
            {
                fprintf(stderr, "Nao foi possivel abrir o arquivo");
                free(musica);
                free(apendice);
                exit(1);
            }

            ler_musica_wav(ENTRADA, apendice);
            mixar_musicas(musica, apendice);
        }

        i++;
    }

    envia_musica(SAIDA, musica);

    fclose(ENTRADA);
    fclose(SAIDA);
    free(musica->dados);
    free(musica);

    return 0;
}
