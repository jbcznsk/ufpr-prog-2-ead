#ifndef __TRATAMENTO__
#define __TRATAMENTO__

#include "estruturas.h"

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

// Estereo Ampliado

// Concatenar

// Mistura


#endif