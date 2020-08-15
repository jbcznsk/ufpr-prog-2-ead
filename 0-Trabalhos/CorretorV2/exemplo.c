#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 100000000

char *carregaDicionario(FILE *dic){
  
  char *p, c;
  unsigned int contador = 0, volta = 1;
  
  p = (char*) malloc (TAM * sizeof(char)); // Aloca o tamanho inicial do vetor de palavras
  
  c = fgetc(dic);
  while(c != EOF){
    p[contador++] = c;
    if (contador >= volta*TAM){
      p = realloc(p, 2*volta*TAM);
      volta++;
    }
    c = fgetc(dic);
  }
  printf("Voltas: %u \nContador: %u",volta, contador);
  //printf("%s", p);
  return p;
}

int main ()
{

  char *palavras;
  FILE *dicionario;
  
  dicionario = fopen("brazilian", "r"); // Carrega o dicionario
  
  if (!dicionario){ // Teste para verificar se o dicionario foi carregado
    perror("Dicionario nao carregado");
    exit(1);
  }


  palavras = carregaDicionario(dicionario);


  printf("%s", palavras);

  fclose (dicionario);
  return (0) ;
}

