#ifndef RETANGULOS_H
#define RETANGULOS_H
#define MAX_RETANGULOS 10


typedef struct {
    int id, x, y, l, h;
} Retangulo;


typedef struct {
    int quantidade;
    Retangulo lista[MAX_RETANGULOS];
} Retangulos;

#endif //RETANGULOS_H


