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

bool existeIntersecaoComOutros(const Retangulos *retangulos, const Retangulo *retangulo) {
    for (int i = 0; i < retangulos->quantidade; i++)
        if (retangulo != &retangulos->lista[i] && existeIntersecao(*retangulo, retangulos->lista[i]))
            return true;
    return false;
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
    if (existeIntersecaoComOutros(retangulos, &novoRetangulo))
        return ERRO_CRIAR_TEM_INTERSECAO;

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

Retangulo *procuraRetangulo(Retangulos *retangulos, const int x, const int y) {
    for (int r = 0; r < retangulos->quantidade; r++) {
        Retangulo *retangulo = &retangulos->lista[r];
        if (retanguloContemPonto(*retangulo, x, y))
            return retangulo;
    }
    return NULL;
}

bool dentroDosLimitesX(const Retangulos *retangulos, const Retangulo *retangulo) {
    return retangulo->x >= 1 && retangulo->x + retangulo->l - 1 <= retangulos->xMaximo;
}

int move(const Retangulos *retangulos, Retangulo *retangulo, const int p, const int salto) {
    const int copiaRetanguloX = retangulo->x;
    for (int i = 0; i < p; i++) {
        retangulo->x += salto;
        if (existeIntersecaoComOutros(retangulos, retangulo)) {
            retangulo->x -= copiaRetanguloX; // repor o valor anterior se der erro
            return ERRO_MOVER_INTERSECAO;
        }
        if (!dentroDosLimitesX(retangulos, retangulo)) {
            retangulo->x -= copiaRetanguloX; // repor o valor anterior se der erro
            return ERRO_MOVER_FORA_LIMITES;
        }
    }
    return 0;
}

int moveRetangulo(Retangulos *retangulos, const int x, const int y, const int p, const int salto) {
    Retangulo *retangulo = procuraRetangulo(retangulos, x, y);
    if (!retangulo)
        return ERRO_MOVER_RETANGULO_INEXISTENTE;

    return move(retangulos, retangulo, p, salto);
}

int apagaRetangulo(Retangulos *retangulos, const int x, const int y) {
    Retangulo *retangulo = procuraRetangulo(retangulos, x, y);
    if (!retangulo)
        return ERRO_APAGAR_RETANGULO_INEXISTENTE;

    const Retangulo *ultimoRetangulo = &retangulos->lista[retangulos->quantidade - 1];
    *retangulo = *ultimoRetangulo;
    retangulos->quantidade--;
    // TODO re-atribuir id do apagado ao copiado do fim
    return 0;
}
