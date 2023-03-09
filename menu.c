#include "menu.h"

void desenha_menu(int selecionada)
{

    char menu[OPCOES][TAM_TEXTO] = {"NOVO JOGO","CARREGAR JOGO","RANKING PONTOS","SAIR"};
    int x,i;
    char res[TAM_TEXTO];

    sprintf(res,"[%s]",menu[selecionada]);
    strcpy(menu[selecionada],res);

    for(i=0; i<OPCOES; i++)
    {

        x=MeasureText(menu[i], TAM_FONTE);
        if(strlen(res)==strlen(menu[i]))
            DrawText(menu[i],(LARGURA/2)-(x/2), 100+i*2*TAM_FONTE, TAM_FONTE, GRAY);
        else
            DrawText(menu[i],(LARGURA/2)-(x/2), 100+i*2*TAM_FONTE, TAM_FONTE, WHITE);
    }
}


