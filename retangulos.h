#pragma once

#include "stdbool.h"

#define MAX_RETANGULOS 10

#define ERRO_CRIAR_FORA_LIMITES 1
#define ERRO_CRIAR_MAX_RETANGULOS 2
#define ERRO_CRIAR_TEM_INTERSECAO 3

typedef struct {
    int id, x, y, l, h;
} Retangulo;

typedef struct {
    int quantidade;
    Retangulo lista[MAX_RETANGULOS];
    int xMaximo;
    int yMaximo;
} Retangulos;

int criaRetangulo(Retangulos *retangulos, int x, int y, int l, int h);

bool eContorno(Retangulo retangulo, int x, int y);

void moveRetangulo(Retangulos *retangulos, int x, int y, int p, int salto);

void apagaRetangulo(Retangulos *retangulos, int x, int y);

