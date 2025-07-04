#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retangulos.h"
#include "mundo.h"

void imprimeMenu() {
    printf(" -----------------\n");
    printf("| create x,y+l,h  |\n");
    printf("| moveright x,y+p |\n");
    printf("| moveleft x,y+p  |\n");
    printf("| delete x,y      |\n");
    printf(" -----------------\n");
}

void alertaColisoesLaterais(const Retangulos *retangulos) {
    int i;
    Colisoes colisoes;
    detetaColisoesLaterais(retangulos, &colisoes);
    for (i = 0; i < colisoes.quantidade; i++) {
        printf("“Colisao lateral detetada entre os retangulos %d e %d.\n",
               colisoes.lista[i].idA,
               colisoes.lista[i].idA);
    }
    free(colisoes.lista);
}

void trataCriaRetangulo(Retangulos *retangulos) {
    int x, y, l, h, resultado;

    scanf(" %d , %d + %d , %d", &x, &y, &l, &h);
    resultado = criaRetangulo(retangulos, x, y, l, h);
    if (resultado == ERRO_CRIAR_FORA_LIMITES)
        printf("Erro: criacao fora dos limites.\n");
    else if (resultado == ERRO_CRIAR_MAX_RETANGULOS)
        printf("Erro: numero maximo de retangulos atingido.\n");
    else if (resultado == ERRO_CRIAR_TEM_INTERSECAO)
        printf("Erro: existe intersecao entre retangulos.\n");
    else {
        alertaColisoesLaterais(retangulos);
        imprimeMundo(retangulos);
    }
}

void trataResultadoMover(const Retangulos *retangulos, const int resultado) {
    if (resultado == ERRO_MOVER_INTERSECAO)
        printf("Erro: retangulo tem intersecao com outro.\n");
    else if (resultado == ERRO_MOVER_RETANGULO_INEXISTENTE)
        printf("Erro: retangulo inexistente.\n");
    else if (resultado == ERRO_MOVER_FORA_LIMITES)
        printf("Erro: movimento para fora dos limites.\n");
    else {
        imprimeMundo(retangulos);
        alertaColisoesLaterais(retangulos);
    }
}

void trataMoverDireita(const Retangulos *retangulos) {
    int x, y, p, resultado;
    scanf(" %d , %d + %d", &x, &y, &p);
    resultado = moveRetangulo(retangulos, x, y, p, 1);
    trataResultadoMover(retangulos, resultado);
}

void trataMoverEsquerda(const Retangulos *retangulos) {
    int x, y, p, resultado;
    scanf(" %d , %d + %d", &x, &y, &p);
    resultado = moveRetangulo(retangulos, x, y, p, -1);
    trataResultadoMover(retangulos, resultado);
}

void trataApagar(Retangulos *retangulos) {
    int x, y, resultado;
    scanf(" %d , %d", &x, &y);
    resultado = apagaRetangulo(retangulos, x, y);
    if (resultado == ERRO_APAGAR_RETANGULO_INEXISTENTE)
        printf("Erro: retangulo inexistente.\n");
    else {
        imprimeMundo(retangulos);
        alertaColisoesLaterais(retangulos);
    }
}

int main() {
    char comando[100];
    Retangulos retangulos;

    retangulos.quantidade = 0;
    retangulos.xMaximo = COMPRIMENTO;
    retangulos.yMaximo = ALTURA;

    printf("Bem-vindo/a\n\n");
    imprimeMenu();

    while (1) {
        printf(">>  ");
        scanf(" %s", comando);
        if (strcmp(comando, "create") == 0)
            trataCriaRetangulo(&retangulos);
        else if (strcmp(comando, "moveright") == 0)
            trataMoverDireita(&retangulos);
        else if (strcmp(comando, "moveleft") == 0)
            trataMoverEsquerda(&retangulos);
        else if (strcmp(comando, "delete") == 0)
            trataApagar(&retangulos);
        else {
            printf("Erro: comando invalido.\n");
            imprimeMenu();
        }
    }
}
