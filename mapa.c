#include "mapa.h"

void mapa_carrega(Mapa *mapa)
{
    FILE *arquivo;
    int i, j;
    char c;

    if(mapa->fase==1)
    {
        arquivo=fopen("fase1.txt", "r");

        for(i=0; i<10; i++)
        {
            for(j=0; j<17; j++)
            {
                c = fgetc(arquivo);
                if ( c != '\n' && c != '\r' )
                    mapa->mapas[i][j] = c;
            }
        }
        fclose(arquivo);
    }

    if(mapa->fase==2)
    {
        arquivo=fopen("fase2.txt", "r");

        for(i=0; i<10; i++)
        {
            for(j=0; j<17; j++)
            {
                c = fgetc(arquivo);
                if ( c != '\n' && c != '\r' )
                    mapa->mapas[i][j] = c;
            }
        }

        fclose(arquivo);
    }

    if(mapa->fase==3)
    {
        arquivo=fopen("fase3.txt", "r");

        for(i=0; i<10; i++)
        {
            for(j=0; j<17; j++)
            {
                c = fgetc(arquivo);
                if ( c != '\n' && c != '\r' )
                    mapa->mapas[i][j] = c;
            }
        }

        fclose(arquivo);
    }

    //INICIALIZACAO DO MAPA
    mapa->dimensao.linhas=10;
    mapa->dimensao.colunas=16;
    mapa->escada=0;
    mapa->porta=0;
    mapa->bau=0;
    mapa->jogador.chave=0;
    mapa->jogador.posicao.linhas=8;
    mapa->jogador.posicao.colunas=5;

}

void localiza_porta(Mapa *mapa)
{
    int i, j;
    for(i=0; i<10; i++)
    {
        for(j=0; j<16; j++)
        {
            if (!(i==mapa->jogador.posicao.linhas) && !(j==mapa->jogador.posicao.colunas))
            {

                if((mapa->mapas[i][j]) == (mapa->mapas[mapa->jogador.posicao.linhas][mapa->jogador.posicao.colunas]))
                {
                    mapa->jogador.posicao.linhas = i;
                    mapa->jogador.posicao.colunas = j;
                    return;
                }
            }
        }
    }
}

void abre_bau(Mapa *mapa)
{
    Texture2D ametista = LoadTexture("images/ametista.png");
    Texture2D rubi = LoadTexture("images/rubi.png");
    Texture2D anel = LoadTexture("images/anel.png");
    Texture2D safira = LoadTexture("images/safira.png");
    Texture2D coroa = LoadTexture("images/coroa.png");
    Texture2D bomba = LoadTexture("images/bomba.png");
    Texture2D chave = LoadTexture("images/chave.png");


    SetTargetFPS(5);
    int i,j,joia,contbau=0;

    for(i=0; i<10; i++)
    {
        for(j=0; j<16; j++)
        {
            if(mapa->mapas[i][j]== 'C')
            {
                contbau++;
            }
        }
    }

    srand(time(NULL));
    joia=1 + (rand() % (7 - 1 + 1));

    if(contbau==1 && mapa->jogador.chave==0)
    {
        mapa->jogador.chave=1;
        mapa->jogador.pontuacao+=300;
        mapa->mapas[mapa->jogador.posicao.linhas][mapa->jogador.posicao.colunas]= 'A';
    }
    else
    {
        switch(joia)
        {
        case 1 :
            if(mapa->jogador.chave==1)
            {
                mapa->jogador.pontuacao+=300;
                BeginDrawing();
                for(i=0; i<1000; i++)
                    DrawTexture(coroa,50*mapa->jogador.posicao.colunas,50*mapa->jogador.posicao.linhas,RAYWHITE);
                EndDrawing();
            }
            else
            {
                mapa->jogador.chave=1;
                mapa->jogador.pontuacao+=300;
                BeginDrawing();
                for(i=0; i<1000; i++)
                    DrawTexture(chave,50*mapa->jogador.posicao.colunas,50*mapa->jogador.posicao.linhas,RAYWHITE);
                EndDrawing();
            }

            break;

        case 2:
            mapa->jogador.pontuacao+=50;
            BeginDrawing();
            for(i=0; i<1000; i++)
                DrawTexture(ametista,50*mapa->jogador.posicao.colunas,50*mapa->jogador.posicao.linhas,RAYWHITE);
            EndDrawing();

            break;

        case 3:
            mapa->jogador.pontuacao+=100;
            BeginDrawing();
            for(i=0; i<1000; i++)
                DrawTexture(safira,50*mapa->jogador.posicao.colunas,50*mapa->jogador.posicao.linhas,RAYWHITE);
            EndDrawing();

            break;

        case 4:
            mapa->jogador.vidas-=1;
            if(mapa->jogador.pontuacao<=200)
                mapa->jogador.pontuacao=0;
            else
                mapa->jogador.pontuacao-=200;
            BeginDrawing();
            for(i=0; i<1000; i++)
                DrawTexture(bomba,50*mapa->jogador.posicao.colunas,50*mapa->jogador.posicao.linhas,RAYWHITE);
            EndDrawing();

            break;

        case 5:
            mapa->jogador.pontuacao+=150;
            BeginDrawing();
            for(i=0; i<1000; i++)
                DrawTexture(rubi,50*mapa->jogador.posicao.colunas,50*mapa->jogador.posicao.linhas,RAYWHITE);
            EndDrawing();

            break;
        case 6:
            mapa->jogador.pontuacao+=200;
            BeginDrawing();
            for(i=0; i<1000; i++)
                DrawTexture(anel,50*mapa->jogador.posicao.colunas,50*mapa->jogador.posicao.linhas,RAYWHITE);
            EndDrawing();

            break;
        case 7:
            mapa->jogador.pontuacao+=300;
            BeginDrawing();
            for(i=0; i<1000; i++)
                DrawTexture(coroa,50*mapa->jogador.posicao.colunas,50*mapa->jogador.posicao.linhas,RAYWHITE);
            EndDrawing();

            break;
        }
        mapa->mapas[mapa->jogador.posicao.linhas][mapa->jogador.posicao.colunas]= 'A';
    }
    mapa->bau=0;
    SetTargetFPS(120);
}
