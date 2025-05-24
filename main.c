#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "retangulos.h"
#include "mundo.h"

void trataCriaRetangulo(Retangulos *retangulos) {
    int x, y, l, h;
    scanf(" %d , %d + %d , %d", &x, &y, &l, &h);
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
