#include <stdio.h>
#include <string.h>

#define MAX_RETANGULOS 10

typedef struct {
    int id, x, y, l, h;
} Retangulo;

typedef struct {
    int quantidade;
    Retangulo lista[MAX_RETANGULOS];
} Retangulos;


void limpaMundo(char mundo[][81]) {
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
            else if (x == retangulo.x + 1 && y == retangulo.y + retangulo.h - 2) // imprimir id
                mundo[26 - y][x] = (char) ('0' + retangulo.id);
            else // pintar retangulo
                mundo[26 - y][x] = '+';
        }
}

void desenhaRetangulos(const Retangulos *retangulos, char mundo[][81]) {
    for (int i = 0; i < retangulos->quantidade; i++)
        desenhaRetangulo(mundo, retangulos->lista[i]);
    fflush(stdout);
}

void imprimeMundo(const Retangulos *retangulos) {
    char mundo[26][81]; // para ignorar a primeira linha e primeira coluna para retirar o 0
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

void criaRetangulo(Retangulos *retangulos, Retangulo retangulo) {
    // TODO: detetar dentro das margens
    // TODO: dar erro se chegarmos ao limite
    retangulo.id = retangulos->quantidade; // TODO: procurar o primeiro id que nao existe
    retangulos->lista[retangulos->quantidade] = retangulo;
    retangulos->quantidade++;
}

void trataCriaRetangulo(Retangulos *retangulos) {
    Retangulo retangulo = {0};
    // TODO: aceitar o formato certo
    scanf("%d %d %d %d", &retangulo.x, &retangulo.y, &retangulo.l, &retangulo.h);
    criaRetangulo(retangulos, retangulo);
    imprimeMundo(retangulos);
}

int main() {
    printf("Bem-vindo/a\n\n");

    Retangulos retangulos = {.quantidade = 0};
    char comando[100];
    while (1) {
        scanf("%s", comando);
        if (strcmp(comando, "create") == 0)
            trataCriaRetangulo(&retangulos);
    }
}
