#include <stdio.h>
#include "tratamento.h"

int16_t soma_com_limite(int16_t a, int16_t b, int16_t lim)
{
	if ((a + b) > lim)
		return (lim);
	else if ((a + b) < -lim)
		return (-lim);
	else
		return a + b;
}

int16_t mult_com_limite(int16_t a, float b, int16_t lim)
{
	if ((a * b) > lim)
		return (lim);
	else if ((a * b) < -lim)
		return (-lim);
	else
		return a * b;
}

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
		msc->dados[i] = mult_com_limite(msc->dados[i], level, VOLMAX);
}

void normalizar_volume(Musica_t *msc)
{
	int16_t valorAtual, maiorValor = 0;

	// Acha o maior valor absoluto
	for (int i = 0; i < msc->tamanho; i++)
	{
		valorAtual = abs(msc->dados[i]);
		if (valorAtual > maiorValor)
			maiorValor = valorAtual;
	}

	float level = (float)VOLMAX / (float)maiorValor;
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
		troca(&msc->dados[i], &msc->dados[msc->tamanho - 1 - i]);
}

void ecoar(Musica_t *msc, float level, int delay)
{
	int pontoInicial;
	uint32_t amostragem;

	amostragem = msc->cab.fmt.SampleRate;
	pontoInicial = amostragem * delay / 1000;

	for (int i = pontoInicial; i < msc->tamanho; i++)
		msc->dados[i] = soma_com_limite(msc->dados[i], level * msc->dados[i - pontoInicial], VOLMAX);
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

	for (int i = 0; i < msc->tamanho; i += 2)
	{
		diff = msc->dados[i + 1] - msc->dados[i];
		msc->dados[i + 1] = soma_com_limite(msc->dados[i + 1], k * diff, VOLMAX); // Canal direito
		msc->dados[i] = soma_com_limite(msc->dados[i + 1], -(k * diff), VOLMAX);  // Canal esquerdo
	}
}

int musicas_compativeis(Musica_t *mscA, Musica_t *mscB)
{
	// Nr de canais
	if (mscA->cab.fmt.NrChannels != mscB->cab.fmt.NrChannels)
		return 0;

	// Taxa de amostragem
	if (mscA->cab.fmt.SampleRate != mscB->cab.fmt.SampleRate)
		return 0;

	// Codificação utilizada
	if (mscA->cab.fmt.AudioFormat != mscB->cab.fmt.AudioFormat)
		return 0;

	// Bits por sample
	if (mscA->cab.fmt.BitsPerSample != mscB->cab.fmt.BitsPerSample)
		return 0;

	return 1;
}

// Retorna a concatenação das duas músicas na música A
void concatatenar_musicas(Musica_t *mscA, Musica_t *mscB)
{

	// Conferir compatibilidade
	if (!musicas_compativeis(mscA, mscB))
	{
		// Desaloca tudo

		// Imprime mensagem de erro
		fprintf(stderr, "Arquivos nao compativeis\n");

		// Encerrar o programa
		exit(1);
	}

	// Modificar o cabeçalho da musica destino
	//// RIFF ChunkSize
	mscA->cab.RIFF.ChunkSize += mscB->cab.data.SubChunk2Size;

	//// Data SubChunk2Size
	mscA->cab.data.SubChunk2Size += mscB->cab.data.SubChunk2Size;

	// Realocar musica->dados da musica destino
	mscA->dados = realloc(mscA->dados, mscA->cab.data.SubChunk2Size);

	// Concatenar os musica->dados
	for (int i = 0; i < mscB->tamanho; i++)
	{
		mscA->dados[i + mscA->tamanho - 1] = mscB->dados[i];
	}

	mscA->tamanho += mscB->tamanho;
}

// Retorna a mixagem nas duas músicas na mscA
void mixar_musicas(Musica_t *mscA, Musica_t *mscB)
{
	// Conferir compatibilidade
	if (!musicas_compativeis(mscA, mscB))
	{
		// Desaloca tudo

		// Imprime mensagem de erro
		fprintf(stderr, "Arquivos nao compativeis\n");

		// Encerrar o programa
		exit(1);
	}

	// Começa assumindo que o audio B é menor
	int menor = mscB->tamanho;

	// Caso não seja, arruma o audio A para que ele comporte o tamanho de B
	if (mscA->tamanho < mscB->tamanho)
	{
		menor = mscA->tamanho;
		mscA->tamanho = mscB->tamanho;
		mscA->cab = mscB->cab;
		mscA->dados = realloc(mscA->dados, mscB->cab.data.SubChunk2Size);

		for (int i = menor; i < mscB->tamanho; i++)
			mscA->dados[i] = mscB->dados[i];
	}

	for (int i = 0; i < menor; i++)
		mscA->dados[i] = soma_com_limite(mscA->dados[i], mscB->dados[i], VOLMAX);
}
