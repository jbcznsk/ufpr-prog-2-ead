#ifndef __ESTRUTURAS__
#define __ESTRUTURAS__

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <getopt.h>

// Valor divertido :)
#define VOLMAX 32323

// Operaçoes
#define SOMA 1
#define SUBT 2
#define MULT 3

struct Cabecalho_s
{
	struct RIFF_s
	{
		char ChunkID[4];
		uint32_t ChunkSize;
		char Format[4];
	} RIFF;

	struct fmt_s
	{
		char SubChunk1ID[4];
		uint32_t SubChunk1Size;
		uint16_t AudioFormat;
		uint16_t NrChannels;
		uint32_t SampleRate;
		uint32_t ByteRate;
		uint16_t BlockAling;
		uint16_t BitsPerSample;
	} fmt;

	struct data_s
	{
		char SubChunk2ID[4];
		uint32_t SubChunk2Size;
	} data;
};
typedef struct Cabecalho_s Cabecalho_t;

struct Musica_s
{
	Cabecalho_t cab;
	int tamanho;
	int16_t *dados;
};
typedef struct Musica_s Musica_t;

#endif