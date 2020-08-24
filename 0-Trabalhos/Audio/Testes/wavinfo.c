#include "wav.h"

int main(){

    FILE *ENTRADA = stdin;

    Cabecalho_t c = ler_cabecalho_wav(ENTRADA);
    
    print_cabecalho_wav(c);

    return 0;
}