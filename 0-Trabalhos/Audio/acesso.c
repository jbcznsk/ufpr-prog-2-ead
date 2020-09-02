#include "acesso.h"

void ler_cabecalho_wav(FILE *ENTRADA, Audio_t *msc)
{
    fread(&msc->cab, sizeof(Cabecalho_t), 1, ENTRADA);
}

void ler_dados_wav(FILE *ENTRADA, Audio_t *msc)
{

    msc->dados = malloc(msc->cab.data.SubChunk2Size);
    if (!msc->dados)
    {
        fprintf(stderr, "Erro ao alocar espaço para a música\n");
        exit(1);
    }

    msc->tamanho = (msc->cab.data.SubChunk2Size) / (msc->cab.fmt.BitsPerSample / 8);

    fread(msc->dados, sizeof(int16_t), msc->tamanho, ENTRADA);
}

void ler_audio_wav(FILE *ENTRADA, Audio_t *msc)
{
    ler_cabecalho_wav(ENTRADA, msc);
    ler_dados_wav(ENTRADA, msc);
}