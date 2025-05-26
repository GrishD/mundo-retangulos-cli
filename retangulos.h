#ifndef RETANGULOS_H
#define RETANGULOS_H

#define bool int
#define true 1
#define false 0

#define MAX_RETANGULOS 10

#define ERRO_CRIAR_FORA_LIMITES 1
#define ERRO_CRIAR_MAX_RETANGULOS 2
#define ERRO_CRIAR_TEM_INTERSECAO 3
#define ERRO_MOVER_INTERSECAO 4
#define ERRO_MOVER_RETANGULO_INEXISTENTE 5
#define ERRO_MOVER_FORA_LIMITES 6
#define ERRO_APAGAR_RETANGULO_INEXISTENTE 7

typedef struct {
    int id, x, y, l, h;
} Retangulo;

typedef struct {
    int quantidade;
    Retangulo *lista;
    /* aqui evita-se referenciar as constantes que estão no mundo para não criar uma dep circular e porque o módulo
     * mundo serve só para visualizar */
    int xMaximo;
    int yMaximo;
} Retangulos;

int criaRetangulo(Retangulos *retangulos, int x, int y, int l, int h);

bool estaNoContorno(Retangulo retangulo, int x, int y);

int moveRetangulo(const Retangulos *retangulos, int x, int y, int p, int salto);

int apagaRetangulo(Retangulos *retangulos, int x, int y);

typedef struct {
    int idA, idB;
} Colisao;

typedef struct {
    Colisao *lista;
    int quantidade;
} Colisoes;

void detetaColisoesLaterais(const Retangulos *retangulos, Colisoes *colisoes);

#endif
