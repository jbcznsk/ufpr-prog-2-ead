#include "wav.h"

void ler_cabecalho_wav(FILE *ENTRADA, Musica_t *msc)
{
    fread(&msc->cab, sizeof(Cabecalho_t),1,ENTRADA);
}

void printTag(char *tagName, char *tag, int tam)
{
	printf("%s       : \"", tagName);
	for (int i = 0; i < tam; i++)
		putc(tag[i], stdout);
	fprintf(stdout, "\"\n");
}

void imprimir_cabecalho_wav(Musica_t msc)
{

	printTag("riff tag", msc.cab.RIFF.ChunkID,4);
	printf("riff size      : %"PRIu32"\n", msc.cab.RIFF.ChunkSize);
	printTag("wave tag", msc.cab.RIFF.Format,4);

    printTag("form tag", msc.cab.fmt.SubChunk1ID,4);
    printf("fmt_size       : %"PRIu32"\n", msc.cab.fmt.SubChunk1Size);
    printf("audio_format   : %"PRIu16"\n", msc.cab.fmt.AudioFormat);
    printf("num_channels   : %"PRIu16"\n", msc.cab.fmt.NrChannels);
    printf("sample_rate    : %"PRIu32"\n", msc.cab.fmt.SampleRate);
    printf("byte_rate      : %"PRIu32"\n", msc.cab.fmt.ByteRate);
    printf("block_align    : %"PRIu16"\n", msc.cab.fmt.BlockAling);
    printf("bits_per_sample: %"PRIu16"\n", msc.cab.fmt.BitsPerSample);

    printTag("data tag", msc.cab.data.SubChunk2ID,4);
    printf("data size      : %"PRIu32"\n", msc.cab.data.SubChunk2Size);

}

void ler_musica(FILE *ENTRADA, Musica_t *msc)
{

    msc->dados = malloc (msc->cab.data.SubChunk2Size);
    if (!msc->dados)
    {
        fprintf(stderr, "Erro ao alocar espaço para a música\n");
        exit(1);
    }

    msc->tamanho = (msc->cab.data.SubChunk2Size)/(msc->cab.fmt.BitsPerSample/8);
    //printf("%d\n",msc->tamanho);

    fread(msc->dados,sizeof(int16_t),msc->tamanho,ENTRADA);

}
