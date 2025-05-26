#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "retangulos.h"

bool existeIntersecao(const Retangulo a, const Retangulo b) {
    /* interseção em x */
    return a.x < b.x + b.l &&
           a.x + a.l > b.x &&
           /* interseção em y */
           a.y < b.y + b.h &&
           a.y + a.h > b.y;
}

bool existeIntersecaoComOutros(const Retangulos *retangulos, const Retangulo *retangulo) {
    int i;
    for (i = 0; i < retangulos->quantidade; i++) {
        /* testa todos os retângulos, mas evita ele mesmo */
        if (retangulo != &retangulos->lista[i] && existeIntersecao(*retangulo, retangulos->lista[i]))
            return true;
    }
    return false;
}

int estaDentroDoMundo(const Retangulos *retangulos, const Retangulo retangulo) {
    return retangulo.x >= 1 && retangulo.x + retangulo.l - 1 <= retangulos->xMaximo &&
           retangulo.y >= 1 && retangulo.y + retangulo.h - 1 <= retangulos->yMaximo;
}

void acionaGravidadeNoRetangulo(const Retangulos *retangulos, Retangulo *retangulo) {
    while (!existeIntersecaoComOutros(retangulos, retangulo) && estaDentroDoMundo(retangulos, *retangulo)) {
        retangulo->y--; /* anda de um em um, pois pode bater ter interseção a qualquer momento */
    }
    /* se chegou aqui é porque já houve uma interseção ou bateu no limite inferior, portanto vamos anular uma posição */
    retangulo->y++;
}

int comparaPorY(const void *a, const void *b) {
    return ((Retangulo *) a)->y - ((Retangulo *) b)->y;
}

/* Aplicar a gravidade a todos os retângulos, um por um */
void acionaGravidade(const Retangulos *retangulos) {
    int i;
    /* temos de ordenar do mais acima para o mais abaixo para garantir que os de baixo caem primeiro que os de cima
     * senão para a gravidade ser aplicada por ordem, a começar por baixo (a ordem é irrelevante na lista) */
    qsort(retangulos->lista, retangulos->quantidade, sizeof(Retangulo), comparaPorY);
    for (i = 0; i < retangulos->quantidade; i++)
        acionaGravidadeNoRetangulo(retangulos, &retangulos->lista[i]);
}

int criaRetangulo(Retangulos *retangulos, const int x, const int y, const int l, const int h) {
    Retangulo novoRetangulo;
    if (retangulos->quantidade >= MAX_RETANGULOS)
        return ERRO_CRIAR_MAX_RETANGULOS;

    novoRetangulo.x = x;
    novoRetangulo.y = y;
    novoRetangulo.l = l;
    novoRetangulo.h = h;
    novoRetangulo.id = retangulos->quantidade;

    if (!estaDentroDoMundo(retangulos, novoRetangulo))
        return ERRO_CRIAR_FORA_LIMITES;

    if (existeIntersecaoComOutros(retangulos, &novoRetangulo))
        return ERRO_CRIAR_TEM_INTERSECAO;

    retangulos->lista = realloc(retangulos->lista, (retangulos->quantidade + 1) * sizeof(Retangulo));
    if (retangulos->lista == NULL) {
        printf("Erro ao realocar memoria (criaRetangulo)\n");
        exit(1);
    }

    retangulos->lista[retangulos->quantidade] = novoRetangulo;
    retangulos->quantidade++;

    acionaGravidadeNoRetangulo(retangulos, &retangulos->lista[retangulos->quantidade - 1]);

    return 0;
}

bool estaNoContorno(const Retangulo retangulo, const int x, const int y) {
    return x == retangulo.x
           || x == retangulo.x + retangulo.l - 1
           || y == retangulo.y
           || y == retangulo.y + retangulo.h - 1;
}

bool contemPonto(const Retangulo retangulo, const int x, const int y) {
    return x >= retangulo.x && x <= retangulo.x + retangulo.l - 1
           && y >= retangulo.y && y <= retangulo.y + retangulo.h - 1;
}

/* para encontrar o retangulo que contem x,y e devolver o seu apontador */
Retangulo *procuraRetangulo(const Retangulos *retangulos, const int x, const int y) {
    int r;
    for (r = 0; r < retangulos->quantidade; r++) {
        Retangulo *retangulo = &retangulos->lista[r];
        if (contemPonto(*retangulo, x, y))
            return retangulo;
    }
    return NULL;
}

/* mover para a esquerda ou direita (em x), consoante o sinal de ´salto´ */
int move(const Retangulos *retangulos, Retangulo *retangulo, const int p, const int salto) {
    int i, xRetanguloInicial;
    xRetanguloInicial = retangulo->x;

    for (i = 0; i < p; i++) {
        retangulo->x += salto;

        if (existeIntersecaoComOutros(retangulos, retangulo)) {
            retangulo->x = xRetanguloInicial; /* repor valor original, pois houve erro */
            return ERRO_MOVER_INTERSECAO;
        }

        if (!estaDentroDoMundo(retangulos, *retangulo)) {
            retangulo->x = xRetanguloInicial; /* repor valor original */
            return ERRO_MOVER_FORA_LIMITES;
        }
    }

    /* ativar a gravidade só no fim pode ser problemático, pois se houver 2 retangulos, e um terceiro em cima
     * do primeiro, e movermos esse terceiro para a direita, ele deveria cair e não ir para cima do da direita
     * contudo, depende da interpretação do que é mover. para corrigir, era só mover a linha abaixo para dentro
     * do ciclo acima
     */
    acionaGravidade(retangulos);
    return 0;
}

int moveRetangulo(const Retangulos *retangulos, const int x, const int y, const int p, const int salto) {
    Retangulo *retangulo = procuraRetangulo(retangulos, x, y);
    if (!retangulo)
        return ERRO_MOVER_RETANGULO_INEXISTENTE;

    return move(retangulos, retangulo, p, salto);
}

int apagaRetangulo(Retangulos *retangulos, const int x, const int y) {
    int i;
    Retangulo *retangulo, *ultimoRetangulo;

    retangulo = procuraRetangulo(retangulos, x, y);
    if (!retangulo)
        return ERRO_APAGAR_RETANGULO_INEXISTENTE;

    /* coloca o último no ligar do apagado e reduz quantidade total */
    ultimoRetangulo = &retangulos->lista[retangulos->quantidade - 1];
    *retangulo = *ultimoRetangulo;
    retangulos->quantidade--;

    /* se for zero, realloc pode dar problemas, sendo melhor libertar e sair */
    if (retangulos->quantidade == 0) {
        free(retangulos->lista);
        retangulos->lista = NULL;
        return 0;
    }
    /* realoca memória da lista */
    retangulos->lista = realloc(retangulos->lista, retangulos->quantidade * sizeof(Retangulo));
    if (retangulos->lista == NULL) {
        printf("Erro ao realocar memoria (apagaRetangulo)\n");
        exit(2);
    }

    /* reatribuir os ids para evitar ficar com saltos */
    for (i = 0; i < retangulos->quantidade; i++)
        retangulos->lista[i].id = i;

    acionaGravidade(retangulos);

    return 0;
}

bool detetaColisaoLateral(const Retangulo a, const Retangulo b) {
    const bool sobreposicaoY = a.y < b.y + b.h && a.y + a.h > b.y;
    /* verifica se estão encostados lateralmente */
    const bool encostadosDireita = a.x + a.l == b.x;
    const bool encostadosEsquerda = b.x + b.l == a.x;
    return sobreposicaoY && (encostadosDireita || encostadosEsquerda);
}

/* o segundo argumento é para armazenar o output */
void detetaColisoesLaterais(const Retangulos *retangulos, Colisoes *colisoes) {
    int i, j;
    Colisao colisao;

    colisoes->lista = malloc(sizeof(Colisoes) * (retangulos->quantidade - 1));
    colisoes->quantidade = 0;
    if (colisoes->lista == NULL) {
        printf("Erro ao realocar memoria (detetaColisoesLaterais)\n");
        exit(3);
    }

    for (i = 0; i < retangulos->quantidade; i++) {
        for (j = i + 1; j < retangulos->quantidade; j++) {
            /* nao vale a pena detetar para a esquerda pois seria repetitivo */
            if (detetaColisaoLateral(retangulos->lista[i], retangulos->lista[j])) {
                colisao.idA = retangulos->lista[i].id;
                colisao.idB = retangulos->lista[j].id;
                colisoes->lista[colisoes->quantidade] = colisao;
                colisoes->quantidade++;
            }
        }
    }
}
