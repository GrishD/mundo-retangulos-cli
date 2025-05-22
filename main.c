#include <stdio.h>
#include <string.h>


typedef struct {
    int x, y, l, h;
} Retangulo;


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

void desenhaRetangulo(char mundo[][81], Retangulo retangulo) {
    for (int y = retangulo.y; y <= retangulo.y + retangulo.h - 1; y++)
        for (int x = retangulo.x; x <= retangulo.x + retangulo.l - 1; x++) {
            if (x == retangulo.x || x == retangulo.x + retangulo.l - 1 || y == retangulo.y || y == retangulo.y +
                retangulo.h - 1) // é extremidade?
                mundo[26 - y][x] = 'X';
            else
                mundo[26 - y][x] = '+';
        }
}


void trataCriarRetangulo(char mundo[][81]) {
    Retangulo retangulo = {0};
    scanf("%d %d %d %d", &retangulo.x, &retangulo.y, &retangulo.l, &retangulo.h);
    desenhaRetangulo(mundo, retangulo);

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
