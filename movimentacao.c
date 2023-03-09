#include "movimentacao.h"

void movimentacao(Mapa *mapa)
{
    if(IsKeyPressed(KEY_RIGHT))
    {
        if(!(mapa->mapas[mapa->jogador.posicao.linhas][mapa->jogador.posicao.colunas+1]=='X'))
        {
            if(mapa->escada)
            {
                mapa->escada=0;
            }
            else if(mapa->bau)
            {
                mapa->bau=0;
            }
            else if(mapa->porta)
            {
                mapa->porta=0;
            }
            mapa->jogador.posicao.colunas=mapa->jogador.posicao.colunas+1;
            if(mapa->mapas[mapa->jogador.posicao.linhas][mapa->jogador.posicao.colunas]==' ')
            {
            }
            else if(mapa->mapas[mapa->jogador.posicao.linhas][mapa->jogador.posicao.colunas]=='H')
            {
                mapa->escada=1;
            }
            else if(mapa->mapas[mapa->jogador.posicao.linhas][mapa->jogador.posicao.colunas]=='C')
            {
                mapa->bau=1;
            }
            else if(mapa->mapas[mapa->jogador.posicao.linhas][mapa->jogador.posicao.colunas]=='A')
            {
            }
            else if(mapa->mapas[mapa->jogador.posicao.linhas][mapa->jogador.posicao.colunas]=='P')
            {
            }
            else
            {
                mapa->porta=1;
            }
        }
    }

    if(IsKeyPressed(KEY_LEFT))
    {
        if(!(mapa->mapas[mapa->jogador.posicao.linhas][mapa->jogador.posicao.colunas-1]=='X'))
        {
            if(mapa->escada)
            {
                mapa->escada=0;
            }
            else if(mapa->bau)
            {
                mapa->bau=0;
            }
            else if(mapa->porta)
            {
                mapa->porta=0;
            }
            mapa->jogador.posicao.colunas=mapa->jogador.posicao.colunas-1;
            if(mapa->mapas[mapa->jogador.posicao.linhas][mapa->jogador.posicao.colunas]==' ')
            {
            }
            else if(mapa->mapas[mapa->jogador.posicao.linhas][mapa->jogador.posicao.colunas]=='H')
            {
                mapa->escada=1;
            }
            else if(mapa->mapas[mapa->jogador.posicao.linhas][mapa->jogador.posicao.colunas]=='C')
            {
                mapa->bau=1;
            }
            else if(mapa->mapas[mapa->jogador.posicao.linhas][mapa->jogador.posicao.colunas]=='A')
            {
            }
            else
            {
                mapa->porta=1;
            }
        }
    }

    if(IsKeyPressed(KEY_UP))
    {
        if(mapa->escada)
        {
            mapa->jogador.posicao.linhas=mapa->jogador.posicao.linhas-1;
            if(mapa->mapas[mapa->jogador.posicao.linhas][mapa->jogador.posicao.colunas]==' ')
            {
                mapa->escada=0;
            }
        }
        else if(mapa->porta)
        {
            localiza_porta(mapa);//if (!i==mapa->jogador.posicao.linhas && !j==mapa->jogador.posicao.colunas) ignorar a porta q o pers está
        }
        else if(mapa->bau)
        {
            abre_bau(mapa);
        }
        else if(mapa->mapas[mapa->jogador.posicao.linhas][mapa->jogador.posicao.colunas] == 'P')
        {
            if( mapa->jogador.chave == 1)
            {
                mapa->fase+=1;
                //if(! mapa->fase == 4)
                mapa_carrega(mapa);
            }
        }
    }

    if(IsKeyPressed(KEY_DOWN))
    {
        if(mapa->mapas[mapa->jogador.posicao.linhas+1][mapa->jogador.posicao.colunas]=='H')
        {
            mapa->jogador.posicao.linhas=mapa->jogador.posicao.linhas+1;
            mapa->escada=1;
        }
    }
}

void queda(Mapa *mapa)
{
    int queda=0;
    while(!(mapa->mapas[mapa->jogador.posicao.linhas+1][mapa->jogador.posicao.colunas]=='X')&&!(mapa->mapas[mapa->jogador.posicao.linhas+1][mapa->jogador.posicao.colunas]=='H'))
    {
        mapa->jogador.posicao.linhas=mapa->jogador.posicao.linhas+1;
        queda++;
        if((mapa->mapas[mapa->jogador.posicao.linhas+1][mapa->jogador.posicao.colunas]==' '))
        {

        }
        else if((mapa->mapas[mapa->jogador.posicao.linhas+1][mapa->jogador.posicao.colunas]=='C'))
        {
            mapa->bau=1;
        }
        else
        {
            mapa->porta=1;
        }
    }
    if(queda>=3)
    {
        mapa->jogador.vidas-=1;
    }
}
