#ifndef JOGADOR_H
#define JOGADOR_H
#define TAMNOME 21
#include "coordenadas.h"

typedef struct
{
    char nome[21];
    Localizacao posicao;
    int vidas,pontuacao, chave;
} Jogador;

#endif // JOGADOR_H
