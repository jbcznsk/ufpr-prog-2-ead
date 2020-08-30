#ifndef __ACESSO__
#define __ACESSO__

#include <stdio.h>
#include "estruturas.h"

void ler_cabecalho_wav(FILE *ENTRADA, Musica_t *msc);

void ler_dados_wav(FILE *ENTRADA, Musica_t *msc);

void ler_musica_wav(FILE *ENTRADA, Musica_t *msc);

#endif