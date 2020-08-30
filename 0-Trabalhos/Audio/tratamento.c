#include <stdio.h>
#include "tratamento.h"

void printTag(char *tagName, char *tag, int tam)
{
    printf("%s       : \"", tagName);
    for (int i = 0; i < tam; i++)
        putc(tag[i], stdout);
    fprintf(stdout, "\"\n");
}

void imprimir_cabecalho_wav(Musica_t *msc)
{

    printTag("riff tag", msc->cab.RIFF.ChunkID, 4);
    printf("riff size      : %" PRIu32 "\n", msc->cab.RIFF.ChunkSize);
    printTag("wave tag", msc->cab.RIFF.Format, 4);

    printTag("form tag", msc->cab.fmt.SubChunk1ID, 4);
    printf("fmt_size       : %" PRIu32 "\n", msc->cab.fmt.SubChunk1Size);
    printf("audio_format   : %" PRIu16 "\n", msc->cab.fmt.AudioFormat);
    printf("num_channels   : %" PRIu16 "\n", msc->cab.fmt.NrChannels);
    printf("sample_rate    : %" PRIu32 "\n", msc->cab.fmt.SampleRate);
    printf("byte_rate      : %" PRIu32 "\n", msc->cab.fmt.ByteRate);
    printf("block_align    : %" PRIu16 "\n", msc->cab.fmt.BlockAling);
    printf("bits_per_sample: %" PRIu16 "\n", msc->cab.fmt.BitsPerSample);

    printTag("data tag", msc->cab.data.SubChunk2ID, 4);
    printf("data size      : %" PRIu32 "\n", msc->cab.data.SubChunk2Size);
}

void envia_musica(FILE *SAIDA, Musica_t *msc)
{
    fwrite(&msc->cab, sizeof(Cabecalho_t), 1, SAIDA);
    fwrite(msc->dados, sizeof(int16_t), msc->tamanho, SAIDA);
}

// Ajuste do volume, respeitando os valores máximos
void ajustar_volume(Musica_t *msc, float level)
{
    for (int i = 0; i < msc->tamanho; i++)
    {
        if (msc->dados[i] * level >= VOLMAX)
            msc->dados[i] = VOLMAX;
        else if (msc->dados[i] * level <= -VOLMAX)
            msc->dados[i] = -VOLMAX;
        else
            msc->dados[i] *= level;
    }
}

void normalizar_volume(Musica_t *msc)
{
    int16_t valorAtual, maiorValor = 0;

    for (int i = 0; i < msc->tamanho; i++)
    {
        valorAtual = abs(msc->dados[i]);
        if (valorAtual > maiorValor)
        {
            maiorValor = valorAtual;
        }
    }

    float level = (float)VOLMAX / (float)maiorValor;

    printf("%d\n", maiorValor);
    printf("%.2f\n", level);
    ajustar_volume(msc, level);
}

void troca(int16_t *a, int16_t *b)
{
    int16_t aux = *a;
    *a = *b;
    *b = aux;
}

void reverter_musica(Musica_t *msc)
{
    for (int i = 0; i < msc->tamanho / 2; i++)
    {
        troca(&msc->dados[i], &msc->dados[msc->tamanho - 1 - i]);
    }
}

void ecoar(Musica_t *msc, float level, int delay)
{
    int pontoInicial;
    uint32_t amostragem = msc->cab.fmt.SampleRate;

    pontoInicial = amostragem*delay/1000;
    
    for (int i = pontoInicial; i < msc->tamanho; i++)
    {
        int64_t novoSample = msc->dados[i] + level*msc->dados[i-pontoInicial];
        if (novoSample > VOLMAX)
            msc->dados[i] = VOLMAX;
        else if (novoSample < -VOLMAX)
            msc->dados[i] = -VOLMAX;
        else 
            msc->dados[i] = novoSample;
    }
}

int confere_dois_canais(Musica_t *msc)
{
    if (msc->cab.fmt.NrChannels != 2)
        return 0;
    return 1;
}
void estereo_amplificado(Musica_t *msc, int k)
{
    int16_t diff;

    for (int i = 0; i < msc->tamanho; i+=2)
    {
        diff = msc->dados[i+1] - msc->dados[i];
        msc->dados[i+1] += k*diff; // Canal direito
        msc->dados[i]   -= k*diff; // Canal esquerdo
    }
}

