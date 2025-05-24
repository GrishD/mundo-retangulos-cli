#ifndef RETANGULOS_H
#define RETANGULOS_H
#include "stdbool.h"

#define MAX_RETANGULOS 10


typedef struct {
    int id, x, y, l, h;
} Retangulo;


typedef struct {
    int quantidade;
    Retangulo lista[MAX_RETANGULOS];
} Retangulos;

void criaRetangulo(Retangulos *retangulos, int x, int y, int l, int h);

bool eContorno(Retangulo retangulo, int x, int y);

#endif
