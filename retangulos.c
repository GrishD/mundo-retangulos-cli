#include <stdbool.h>
#include "retangulos.h"

void criaRetangulo(Retangulos *retangulos, const int x, const int y, const int l, const int h) {
    // TODO: detetar dentro das margens
    // TODO: detetar quantidade maxima atingida
    const Retangulo novoRetangulo = {
        .x = x, .y = y, .l = l, .h = h,
        .id = retangulos->quantidade // TODO: procurar o primeiro id que nao existe
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
