#include <stdbool.h>
#include "retangulos.h"

#include <stddef.h>

void criaRetangulo(Retangulos *retangulos, const int x, const int y, const int l, const int h) {
    // TODO: detetar dentro das margens
    // TODO: detetar quantidade maxima atingida
    // TODO: detetar intersecções
    const Retangulo novoRetangulo = {
        .x = x, .y = y, .l = l, .h = h,
        .id = retangulos->quantidade
    };
    retangulos->lista[retangulos->quantidade] = novoRetangulo;
    retangulos->quantidade++;
}

bool eContorno(const Retangulo retangulo, const int x, const int y) {
    return x == retangulo.x
           || x == retangulo.x + retangulo.l - 1
           || y == retangulo.y
           || y == retangulo.y + retangulo.h - 1;
}

bool retanguloContemPonto(const Retangulo retangulo, const int x, const int y) {
    return x >= retangulo.x && x <= retangulo.x + retangulo.l - 1
           && y >= retangulo.y && y <= retangulo.y + retangulo.h - 1;
}

Retangulo *procuraRetangulo(Retangulos *retangulos, int x, int y) {
    for (int r = 0; r < retangulos->quantidade; r++) {
        Retangulo *retangulo = &retangulos->lista[r];
        if (retanguloContemPonto(*retangulo, x, y))
            return retangulo;
    }
    return NULL;
}

void move(Retangulos *retangulos, Retangulo *retangulo, const int p, const int salto) {
    // o objetivo de utilizar retangulos é para detetar colisões
    for (int i = 0; i < p; i++)
        retangulo->x += salto;
}

void moveRetangulo(Retangulos *retangulos, const int x, const int y, const int p, const int salto) {
    // TODO: detetar intersecções
    Retangulo *retangulo = procuraRetangulo(retangulos, x, y);
    if (!retangulo) return; // TODO: devia retornar um erro

    move(retangulos, retangulo, p, salto);
}

void apagaRetangulo(Retangulos *retangulos, const int x, const int y) {
    Retangulo *retangulo = procuraRetangulo(retangulos, x, y);
    if (!retangulo) return; // TODO: devia retornar um erro

    const Retangulo *ultimoRetangulo = &retangulos->lista[retangulos->quantidade - 1];
    *retangulo = *ultimoRetangulo;
    retangulos->quantidade--;
    // TODO re-atribuir id do apagado ao copiado do fim
}
