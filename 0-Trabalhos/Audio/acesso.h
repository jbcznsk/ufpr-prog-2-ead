#ifndef __ACESSO__
#define __ACESSO__

#include <stdio.h>
#include "estruturas.h"

void ler_cabecalho_wav(FILE *ENTRADA, Audio_t *msc);

void ler_dados_wav(FILE *ENTRADA, Audio_t *msc);

void ler_audio_wav(FILE *ENTRADA, Audio_t *msc);

#endif