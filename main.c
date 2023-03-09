#include "ranking.h"

int main(void)
{
    int opcao = 0,sair = 0;
    const int screenWidth = LARGURA;
    const int screenHeight = ALTURA;
    float scrollingMid = 0.0f;
    Mapa mapa;
    mapa.fase=1;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - background scrolling");

    Texture2D midground = LoadTexture("images/city art.png");

    SetTargetFPS(120);

    // Main game loop
    while ( (!WindowShouldClose()) && (sair==0))
    {
        if(IsKeyPressed(KEY_ENTER))
        {
            if(opcao==0)
            {
                mapa.fase=1;
                digita_nome(&mapa.jogador);
                jogo(&mapa);
            }
            else if(opcao==1)
            {
                arq_recupera_jogo(&mapa);
                jogo(&mapa);
            }
            else if(opcao==2)
            {
                desenha_ranking();
            }
            else if(opcao==3)
            {
                sair=1;
            }
        }
        if(IsKeyPressed(KEY_UP))
        {
            if(opcao==0)
                opcao=3;
            else
                opcao-=1;
        }
        if(IsKeyPressed(KEY_DOWN))
        {
            if(opcao==3)
                opcao=0;
            else
                opcao+=1;
        }

        scrollingMid -= 0.5;
        if (scrollingMid <= -midground.width*2) scrollingMid = 0;

        BeginDrawing();

        DrawTextureEx(midground, (Vector2)
        {
            scrollingMid, 0
        }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(midground, (Vector2)
        {
            midground.width*2 + scrollingMid, 0
        }, 0.0f, 2.0f, WHITE);

        desenha_menu(opcao);

        EndDrawing();
    }

    CloseWindow();


    return 0;
}



