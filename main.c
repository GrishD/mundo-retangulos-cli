#include <stdio.h>
#include <string.h>

void imprimeMundo(char mundo[][81]) {
    for (int y = 1; y <= 25; y++) {
        for (int x = 1; x <= 80; x++)
            printf("%c", mundo[y][x]);
        putchar('\n');
    }
}

void criarMundo(char mundo[][81]) {
    for (int y = 1; y <= 25; y++)
        for (int x = 1; x <= 80; x++)
            mundo[y][x] = ' '; // limpar o mundo
}

void desenhaRetangulo(char mundo[][81], int xx, int yy, int ll, int hh) {
    // desenha limite inferior/superior
    for (int x = xx; x <= xx+ ll-1; x++) {
        mundo[26 - yy][x] = 'X'; // limite inferior
        mundo[26 - (yy-1+hh)][x] = 'X'; // limite superior
    }
    // desenha linha esquerda e direita
    for (int y = yy+ 1; y <= yy+hh-2; y++) {
        mundo[26 - y][xx] = 'X';
        mundo[26 - y][xx-1+ll] = 'X';
    }
}

void trataCriarRetangulo(char mundo[][81]) {
    int x, y, l, h;
    scanf("%d %d %d %d", &x, &y, &l, &h);
    printf("%d %d %d %d", x, y, l, h);
    desenhaRetangulo(mundo, x, y, l, h);

    imprimeMundo(mundo);
}

int main(void) {
    char mundo[26][81]; // para ignorar a primeira linha e primeira coluna para retirar o 0
    criarMundo(mundo);
    printf("Bem-vindo/a\n\n");
    char comando[100];
    scanf("%s", comando);
    if (strcmp(comando, "create") == 0)
        trataCriarRetangulo(mundo);
}
