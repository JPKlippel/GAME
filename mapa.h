#ifndef MAPA_H
#define MAPA_H
#include "jogador.h"
#define MAPA_L 10
#define MAPA_C 20

typedef struct
{
    char mapas[MAPA_L][MAPA_C];
    Localizacao dimensao;
    int escada;
    int porta, bau, fase;
    Jogador jogador;
} Mapa;

void mapa_carrega(Mapa *mapa);
void localiza_porta(Mapa *mapa);
void abre_bau(Mapa *mapa);

#endif // MAPA_H
