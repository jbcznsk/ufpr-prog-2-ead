// GRR20190372 Jorge Lucas Vicilli Jabczenski

#ifndef DICIONARIO_H
#define DICIONARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#define MAX_PALAVRAS 10000
#define TAM_PALAVRA 50

typedef char* String;

// Carrega o dicionario em RAM
String *carregaDicionario(FILE *dic, unsigned long int *contador);

// Funcao utilizada no qsort e bsearch
int funcaoComparacao(const void *p1, const void *p2);

// Acha as palavras erradas no texto e bota elas entre []
void processaTexto(String *dicionario, unsigned long int tamanho_dicionario);

// Libera o espaco alocado pelo dicionario
void desalocaDicionario(String *dicionario, unsigned long int tamanho_dicionario);

#endif
