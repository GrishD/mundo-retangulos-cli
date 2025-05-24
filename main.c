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

void imprimeMenu() {
    printf(" ------------------\n");
    printf("| create x,y+l,h   |\n");
    printf("| moveright x,y+p  |\n");
    printf("| moveleft x,y+p   |\n");
    printf(" ------------------\n");
}

int main() {
    printf("Bem-vindo/a\n\n");
    imprimeMenu();
    Retangulos retangulos = {.quantidade = 0};

    char comando[100];
    while (true) {
        printf(">>  ");
        scanf("%s", comando);
        if (strcmp(comando, "create") == 0)
            trataCriaRetangulo(&retangulos);
        else
            imprimeMenu();
        //else if (strcmp(comando, "moveleft") == 0)
        //trataMover(retangulos, -1);
        //else if (strcmp(comando, "moveright") == 0)
        //trataMover(retangulos, 1);
    }
}
