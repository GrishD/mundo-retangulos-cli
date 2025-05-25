#include <stdbool.h>
#include <stddef.h>
#include "retangulos.h"

bool dentroMundo(const Retangulos *retangulos, const Retangulo retangulo) {
    return retangulo.x >= 1 && retangulo.x + retangulo.l - 1 <= retangulos->xMaximo &&
           retangulo.y >= 1 && retangulo.y + retangulo.h - 1 <= retangulos->yMaximo;
}

bool existeIntersecao(const Retangulo a, const Retangulo b) {
    // interseção em x
    return a.x < b.x + b.l &&
           a.x + a.l > b.x &&
           // interseção em y
           a.y < b.y + b.h &&
           a.y + a.h > b.y;;
}

int criaRetangulo(Retangulos *retangulos, const int x, const int y, const int l, const int h) {
    if (retangulos->quantidade >= MAX_RETANGULOS)
        return ERRO_CRIAR_MAX_RETANGULOS;
    const Retangulo novoRetangulo = {
        .x = x, .y = y, .l = l, .h = h,
        .id = retangulos->quantidade
    };
    if (!dentroMundo(retangulos, novoRetangulo))
        return ERRO_CRIAR_FORA_LIMITES;
    for (int i = 0; i < retangulos->quantidade; i++) {
        if (existeIntersecao(novoRetangulo, retangulos->lista[i]))
            return ERRO_CRIAR_TEM_INTERSECAO;
    }

    retangulos->lista[retangulos->quantidade] = novoRetangulo;
    retangulos->quantidade++;
    return 0;
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
