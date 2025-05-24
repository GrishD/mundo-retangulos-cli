#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "retangulos.h"

// TODO: modulo mundo
void limpaMundo(char mundo[][81]) {
    for (int y = 1; y <= 25; y++)
        for (int x = 1; x <= 80; x++)
            mundo[y][x] = ' ';
}

// TODO: modulo mundo
void desenhaRetangulo(char mundo[][81], const Retangulo retangulo) {
    for (int y = retangulo.y; y <= retangulo.y + retangulo.h - 1; y++)
        for (int x = retangulo.x; x <= retangulo.x + retangulo.l - 1; x++) {
            if (x == retangulo.x // TODO: criar funcao modulo retangulo "noContorno"
                || x == retangulo.x + retangulo.l - 1
                || y == retangulo.y
                || y == retangulo.y + retangulo.h - 1
            ) // é extremidade?
                mundo[26 - y][x] = 'X'; // TODO: criar funcao no modulo mundo para fazer set
            else
                mundo[26 - y][x] = '+'; // pintar retangulo
        }
    mundo[26 - (retangulo.y + retangulo.h - 2)][retangulo.x + 1] = (char) ('0' + retangulo.id); // imprimir id
}

// TODO: modulo mundo
void desenhaRetangulos(const Retangulos *retangulos, char mundo[][81]) {
    for (int i = 0; i < retangulos->quantidade; i++)
        desenhaRetangulo(mundo, retangulos->lista[i]);
    fflush(stdout);
}

// TODO: modulo mundo
void imprimeMundo(const Retangulos *retangulos) {
    char mundo[26][81]; // linha/coluna extra para ignorar a primeira linha e primeira coluna (deixando de usar o 0)
    limpaMundo(mundo);
    desenhaRetangulos(retangulos, mundo);
    // imprime
    for (int y = 1; y <= 25; y++) {
        // TODO: definir constantes
        for (int x = 1; x <= 80; x++)
            printf("%c", mundo[y][x]);
        putchar('\n');
    }
}

void trataCriaRetangulo(Retangulos *retangulos) {
    int x, y, l, h;
    scanf("%d %d %d %d", &x, &y, &l, &h); // TODO: aceitar o formato certo
    criaRetangulo(retangulos, x, y, l, h);
    imprimeMundo(retangulos);
}

int main() {
    printf("Bem-vindo/a\n\n");

    Retangulos retangulos = {.quantidade = 0};
    char comando[100];
    while (true) {
        // TODO: imprimir menu
        printf(">>  ");
        scanf("%s", comando);
        if (strcmp(comando, "create") == 0)
            trataCriaRetangulo(&retangulos);
    }
}
