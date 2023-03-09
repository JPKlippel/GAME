#include "ranking.h"

void digita_nome(Jogador *jog)
{

    char name[20] = "\0";
    int letterCount = 0;
    Rectangle textBox = {150, 180, 500, 50 };
    bool mouseOnText = true;
    int framesCounter = 0;

    Texture2D midground = LoadTexture("images/city art.png");
    float scrollingMid = 0.0f;

    do
    {
        scrollingMid -= 0.5;
        if (scrollingMid <= -midground.width*2) scrollingMid = 0;

        if (mouseOnText)
        {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
            int key = GetCharPressed();
            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (letterCount < 20))
                {
                    name[letterCount] = (char)key;
                    name[letterCount+1] = '\0';
                    letterCount++;
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                name[letterCount] = '\0';
            }
        }
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (mouseOnText) framesCounter++;
        else framesCounter = 0;


        BeginDrawing();

        DrawTextureEx(midground, (Vector2)
        {
            scrollingMid, 0
        }, 0.0f, 2.0f, WHITE);

        DrawTextureEx(midground, (Vector2)
        {
            midground.width*2 + scrollingMid, 0
        }, 0.0f, 2.0f, WHITE);

        ClearBackground(RAYWHITE);

        DrawText("DIGITE SEU NOME", (LARGURA/2)-(MeasureText("DIGITE SEU NOME", 20)/2), 140, 20, WHITE);

        DrawRectangleRec(textBox, LIGHTGRAY);
        if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, GRAY);
        else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, BLACK);

        DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, WHITE);

        DrawText(TextFormat("Caracteres: %i/%i", letterCount, 20), 300, 250, 20, WHITE);
        DrawText(TextFormat("PRESSIONE ENTER PARA CONTINUAR"), 0, 530, 20, WHITE);

        if (mouseOnText)
        {
            if (letterCount < 20)
            {
                if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, BLACK);
            }
            else DrawText("Limite de Caracteres Atingido", 260, 300, 20, BLACK);
        }



        EndDrawing();
    }
    while (!IsKeyPressed(KEY_ENTER));

    //INICIALIZACAO DO JOGADOR
    strcpy( jog->nome, name);
    jog->vidas=3;
    jog->pontuacao=0;
    jog->posicao.linhas=8;
    jog->posicao.colunas=5;
    jog->chave=0;

    return;
}


void jogo(Mapa *mapa)
{
    float scrollingMid = 0.0f;
    int i, j;

    Texture2D midground = LoadTexture("images/city art.png");
    Texture2D porta = LoadTexture("images/porta.png");
    Texture2D parede = LoadTexture("images/parede.png");
    Texture2D escada = LoadTexture("images/escada.png");
    Texture2D bau = LoadTexture("images/bau.png");
    Texture2D costa = LoadTexture("images/costa.png");
    Texture2D frente = LoadTexture("images/frente.png");
    Texture2D portao = LoadTexture("images/portao.png");
    Texture2D bauaberto = LoadTexture("images/bauaberto.png");

    mapa_carrega(mapa);

    do
    {
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

        for(i=0; i<mapa->dimensao.linhas; i++)
        {
            for(j=0; j<mapa->dimensao.colunas; j++)
            {
                if(mapa->mapas[i][j]=='X')
                {
                    DrawTexture(parede,50*j,50+50*i,RAYWHITE);
                }
                else if(mapa->mapas[i][j]=='H')
                {
                    DrawTexture(escada,50*j,50+50*i,RAYWHITE);
                }
                else if(mapa->mapas[i][j]==' ')
                {
                }
                else if(mapa->mapas[i][j]=='C')
                {
                    DrawTexture(bau,50*j,50+50*i,RAYWHITE);
                }
                else if(mapa->mapas[i][j]=='P')
                {
                    if(mapa->jogador.chave)
                    {
                        DrawTexture(portao,50*j,50+50*i,RAYWHITE);
                    }
                }
                else if(mapa->mapas[i][j]== 'A')
                {
                    DrawTexture(bauaberto,50*j,50+50*i,RAYWHITE);
                }
                else
                {
                    DrawTexture(porta,50*j,50+50*i,RAYWHITE);
                }
            }
        }

        cabecalho(mapa->jogador);

        if(mapa->escada)
        {
            DrawTexture(costa,50*mapa->jogador.posicao.colunas,50+50*mapa->jogador.posicao.linhas,RAYWHITE);
        }
        else
        {
            DrawTexture(frente,50*mapa->jogador.posicao.colunas,50+50*mapa->jogador.posicao.linhas,RAYWHITE);
        }

        queda(mapa);

        movimentacao(mapa);

        DrawText(TextFormat("FASE: %i", mapa->fase),265, 10, 30, LIME);
        DrawText("SALVAR -> PRESS 'S'      MENU -> PRESS 'M' ", 0, 530, 25, WHITE);

        if(IsKeyPressed(KEY_S))
        {
            arq_salva_jogo(*mapa);
        }

        EndDrawing();

    }
    while (!IsKeyPressed(KEY_M) && mapa->jogador.vidas>0 && mapa->fase<4);


    if(mapa->jogador.vidas==0)
    {
        while (!IsKeyPressed(KEY_R))
        {
            BeginDrawing();

            DrawTextureEx(midground, (Vector2)
            {
                scrollingMid, 0
            }, 0.0f, 2.0f, WHITE);

            DrawTextureEx(midground, (Vector2)
            {
                midground.width*2 + scrollingMid, 0
            }, 0.0f, 2.0f, WHITE);

            DrawText(TextFormat("VOCE MORREU"), 130, 150, 70, RED);
            DrawText(TextFormat("APERTE 'R' PARA VER O RANKING"), 40, 500, 40, RED);

            EndDrawing();
        }
        desenha_ranking();
    }
    else if(mapa->fase==4)
    {
        while (!IsKeyPressed(KEY_R))
        {
            BeginDrawing();

            DrawTextureEx(midground, (Vector2)
            {
                scrollingMid, 0
            }, 0.0f, 2.0f, WHITE);

            DrawTextureEx(midground, (Vector2)
            {
                midground.width*2 + scrollingMid, 0
            }, 0.0f, 2.0f, WHITE);

            DrawText(TextFormat("VOCE GANHOU"), 130, 150, 70, GREEN);
            DrawText(TextFormat("APERTE 'R' PARA VER O RANKING"), 40, 500, 40, GREEN);
            EndDrawing();

        }
        verifica_ranking(*mapa);
        desenha_ranking();
    }
}


void cabecalho(Jogador jog)
{
    char nome[21];
    strcpy(nome, jog.nome);
    Rectangle rec= {0,0,800,50};
    DrawRectangle(0, 0, 800, 50, RAYWHITE);
    DrawRectangleLinesEx(rec,5, DARKBLUE);
    DrawText(nome,20, 10, 30, BLACK);
    DrawText(TextFormat("VIDAS: %i", jog.vidas),400, 10, 30, RED);
    DrawText(TextFormat("PONTOS: %i", jog.pontuacao),560, 10, 30, GOLD);
}










