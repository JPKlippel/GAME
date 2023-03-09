#include "ranking.h"


void desenha_ranking()
{
    FILE *arquivo;
    Jogador jog[5];
    Texture2D midground = LoadTexture("images/city art.png");
    float scrollingMid = 0.0f;

    arquivo = fopen("pontuacao.dat", "r");
    for(int i=0; i <5; i++)
    {
        fread(&jog[i].nome, 21, 1, arquivo);
        fread(&jog[i].pontuacao, sizeof(int), 1, arquivo);
    }

    while(!IsKeyPressed(KEY_M))
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

        DrawText(TextFormat("RANKING"), 20, 10, 70, RED);

        for(int i=0; i<5; ++i)
        {
            DrawText(TextFormat("%s : %i", jog[i].nome, jog[i].pontuacao), 30, 150+50*i, 40, RED);
        }
        DrawText(TextFormat("APERTE 'M' PARA IR AO MENU"), 30, 500, 40, RED);

        EndDrawing();
    }
}


void verifica_ranking(Mapa mapa)
{
    FILE *arquivo;
    Jogador jog[6];

    arquivo = fopen("pontuacao.dat", "r+");

    for(int i=0; i <5; i++)
    {
        fread(&jog[i].nome, sizeof(jog->nome), 1, arquivo);
        fread(&jog[i].pontuacao, sizeof(jog->pontuacao), 1, arquivo);
    }
    fclose(arquivo);

    arquivo = fopen("pontuacao.dat", "w");

    strcpy(jog[5].nome, mapa.jogador.nome);
    jog[5].pontuacao = mapa.jogador.pontuacao;

    ordenamento_bolha(jog, 6);

    for(int i=5; i>0; i--)
    {
        fwrite(&jog[i].nome, 21, 1, arquivo);
        fwrite(&jog[i].pontuacao, sizeof(int), 1, arquivo);
    }

    fclose(arquivo);

}

void ordenamento_bolha(Jogador *v, int tamanho)
{
    int i, trocou, fim;
    fim = tamanho - 1;
    Jogador aux;

    do
    {
        trocou = 0;
        for (i = 0; i < fim; i++)
        {
            if (v[i].pontuacao > v[i + 1].pontuacao)
            {
                aux = v[i];
                v[i] = v[i + 1];
                v[i + 1] = aux;
                trocou = 1;
            }
        }
        fim--;
    }
    while (trocou == 1);
}
