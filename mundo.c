#include <stdio.h>
#include "mundo.h"
#include "retangulos.h"

void limpaMundo(char mundo[][COMPRIMENTO + 1]) {
    int y, x;
    for (y = 1; y <= ALTURA; y++)
        for (x = 1; x <= COMPRIMENTO; x++)
            mundo[y][x] = ' ';
}

/* para desenhar um retangulo, temos de saber quais sao os seus pixeis e coloca-los
 * na matriz */
void desenhaRetangulo(char mundo[][COMPRIMENTO + 1], const Retangulo retangulo) {
    int x, y;
    for (y = retangulo.y; y <= retangulo.y + retangulo.h - 1; y++)
        for (x = retangulo.x; x <= retangulo.x + retangulo.l - 1; x++) {
            if (estaNoContorno(retangulo, x, y))
                mundo[ALTURA + 1 - y][x] = 'X'; /* contorno retangulo */
            else
                mundo[ALTURA + 1 - y][x] = '+'; /* interior retangulo */
        }
    /* imprimir id */
    mundo[ALTURA + 1 - (retangulo.y + retangulo.h - 2)][retangulo.x + 1] = (char) ('0' + retangulo.id);
}

/* pegamos no modelo dos retangulos e iteramos todos, desenhando um por um */
void desenhaRetangulos(const Retangulos *retangulos, char mundo[][COMPRIMENTO + 1]) {
    int i;
    for (i = 0; i < retangulos->quantidade; i++)
        desenhaRetangulo(mundo, retangulos->lista[i]);
}

void imprimeMundo(const Retangulos *retangulos) {
    int x, y;
    char mundo[ALTURA + 1][COMPRIMENTO + 1];
    /* linha/coluna extra para ignorar a primeira linha e primeira coluna (deixando de usar o 0) */
    limpaMundo(mundo);
    desenhaRetangulos(retangulos, mundo);
    /* imprime */
    for (y = 1; y <= ALTURA; y++) {
        for (x = 1; x <= COMPRIMENTO; x++)
            printf("%c", mundo[y][x]);
        putchar('\n');
    }
    fflush(stdout);
}
