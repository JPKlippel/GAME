#ifndef JOGO_H
#define JOGO_H

#include "menu.h"

void digita_nome(Jogador *jog);
void jogo(Mapa *mapa);
void imprime_mapa(Mapa *mapa);
void carrega_mapa(Mapa *mapa);
void cabecalho(Jogador jog);

#endif // JOGO_H
