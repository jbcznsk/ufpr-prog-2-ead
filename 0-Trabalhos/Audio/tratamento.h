#ifndef __TRATAMENTO__
#define __TRATAMENTO__

#include "estruturas.h"
#include <string.h>

// Realiza uma operação com os valores limites de +- limite
// int op_com_limite(int op, int16_t a, int16_t b, int16_t lim);
int16_t soma_com_limite(int16_t a, int16_t b, int16_t lim);
int16_t mult_com_limite(int16_t a, float b, int16_t lim);

// Função auxiliar para imprimir_cabecalho_wav
void printTag(char *tagName, char *tag, int tam);
void imprimir_cabecalho_wav(Audio_t *msc);

// Escreve Musica na saida
void envia_audio(FILE *SAIDA, Audio_t *msc);

// Mudar Volume
void ajustar_volume(Audio_t *msc, float level);

// Normalizar
void normalizar_volume(Audio_t *msc);

// Reverter
void troca(int16_t *a, int16_t *b);
void reverter_audio(Audio_t *msc);

// Eco
void ecoar(Audio_t *msc, float level, int delay);

// Estereo Ampliado
int confere_dois_canais(Audio_t *msc);
void estereo_amplificado(Audio_t *msc, int k);

// Função auxiliar utilizada em "concatenar" e "mixar"
int audios_compativeis(Audio_t *mscA, Audio_t *mscB);

// Retorna a concatenação das duas músicas na música A
void concatatenar_audios(Audio_t *mscA, Audio_t *mscB);

// Retorna a mixagem nas duas músicas na mscA
void mixar_audios(Audio_t *mscA, Audio_t *mscB);

// Fecha os arquivos de streams
void fechar_streams(FILE *ENTRADA, FILE *SAIDA);

#endif