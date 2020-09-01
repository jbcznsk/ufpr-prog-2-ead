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
void imprimir_cabecalho_wav(Musica_t *msc);

// Escreve Musica na saida
void envia_musica(FILE *SAIDA, Musica_t *msc);

// Mudar Volume
void ajustar_volume(Musica_t *msc, float level);

// Normalizar
void normalizar_volume(Musica_t *msc);

// Reverter
void troca(int16_t *a, int16_t *b);
void reverter_musica(Musica_t *msc);

// Eco
void ecoar(Musica_t *msc, float level, int delay);

// Estereo Ampliado
int confere_dois_canais(Musica_t *msc);
void estereo_amplificado(Musica_t *msc, int k);

// Função auxiliar utilizada em "concatenar" e "mixar"
int musicas_compativeis(Musica_t *mscA, Musica_t *mscB);

// Retorna a concatenação das duas músicas na música A
void concatatenar_musicas(Musica_t *mscA, Musica_t *mscB);

// Retorna a mixagem nas duas músicas na mscA
void mixar_musicas(Musica_t *mscA, Musica_t *mscB);

#endif