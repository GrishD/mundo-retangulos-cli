#include "retangulos.h"

void criaRetangulo(Retangulos *retangulos, const int x, const int y, const int l, const int h) {
    // TODO: detetar dentro das margens
    // TODO: detetar quantidade maxima atingida
    const Retangulo novoRetangulo = {
        .x = x, .y = y, .l = l, .h = h,
        .id = retangulos->quantidade // TODO: procurar o primeiro id que nao existe
    };
    // TODO: dar erro se nao estiver dentro das margens
    retangulos->lista[retangulos->quantidade] = novoRetangulo;
    retangulos->quantidade++;
}
