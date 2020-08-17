#include <stdio.h>
#include <locale.h>


int main(int argc, char **argv){

	setlocale(LC_ALL,"pt_BR.ISO-8859-1");

	printf("Olá\n");

	return 0;
}
