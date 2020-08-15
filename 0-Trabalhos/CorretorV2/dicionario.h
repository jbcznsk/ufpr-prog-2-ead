// GRR20190372 Jorge Lucas Vicilli Jabczenski

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#define MAX_PALAVRAS 10000
#define TAM_PALAVRA 50

typedef char* String;

String *carregaDicionario(FILE *dic, unsigned long int *contador);

int funcaoComparacao(const void *p1, const void *p2);

void processaTexto(String *dicionario, int tamanho_dicionario);