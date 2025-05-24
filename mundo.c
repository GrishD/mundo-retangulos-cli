#include <stdio.h>
#include "mundo.h"
#include "retangulos.h"

void limpaMundo(char mundo[][COMPRIMENTO + 1]) {
    for (int y = 1; y <= ALTURA; y++)
        for (int x = 1; x <= COMPRIMENTO; x++)
            mundo[y][x] = ' ';
}

void desenhaRetangulo(char mundo[][COMPRIMENTO + 1], const Retangulo retangulo) {
    for (int y = retangulo.y; y <= retangulo.y + retangulo.h - 1; y++)
        for (int x = retangulo.x; x <= retangulo.x + retangulo.l - 1; x++) {
            if (eContorno(retangulo, x, y))
                mundo[ALTURA + 1 - y][x] = 'X';
            else
                mundo[ALTURA + 1 - y][x] = '+'; // pintar retangulo
        }
    mundo[ALTURA + 1 - (retangulo.y + retangulo.h - 2)][retangulo.x + 1] = (char) ('0' + retangulo.id); // imprimir id
}

void desenhaRetangulos(const Retangulos *retangulos, char mundo[][COMPRIMENTO + 1]) {
    for (int i = 0; i < retangulos->quantidade; i++)
        desenhaRetangulo(mundo, retangulos->lista[i]);
    fflush(stdout);
}

void imprimeMundo(const Retangulos *retangulos) {
    char mundo[ALTURA + 1][COMPRIMENTO + 1];
    // linha/coluna extra para ignorar a primeira linha e primeira coluna (deixando de usar o 0)
    limpaMundo(mundo);
    desenhaRetangulos(retangulos, mundo);
    // imprime
    for (int y = 1; y <= ALTURA; y++) {
        for (int x = 1; x <= COMPRIMENTO; x++)
            printf("%c", mundo[y][x]);
        putchar('\n');
    }
}
