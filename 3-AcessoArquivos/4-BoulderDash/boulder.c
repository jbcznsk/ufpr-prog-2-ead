#include <stdio.h>
#include <stdlib.h>
#include <strings.h>


int main(int argc, char **argv)
{

    int lin, col;
    char **map;
    FILE *mapa;

    mapa = fopen("mapa.txt", "r");
    if (!mapa)
    {
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    fscanf(mapa, "%d %d\n", &lin, &col);

    col++;

    map = (char **) malloc (sizeof(char*)*lin);
    for (int i = 0; i < lin; i++)
        map[i] = (char*) malloc (sizeof(char)*col);

    if (map == NULL)
        exit(1);

    for (int i = 0; i < lin; i++){
        for (int j = 0; j < col; j++){
            map[i][j] = fgetc(mapa);
        }
    }

    for (int i = 0; i < lin; i++){
        for (int j = 0; j < col; j++){
            putc(map[i][j], stdout);
        }
        putc('\n', stdout);
    }


    printf("%d %d\n", lin, col);

    fclose(mapa);


    return 0;
}