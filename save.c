#include "save.h"

void arq_salva_jogo(Mapa mapa)
{
    FILE *arquivo;

    arquivo = fopen("jogo.dat", "w");

    if (arquivo == NULL)
    {
        printf("O arquivo nao pode ser aberto. \n");
        return;
    }
    else
    {
        fwrite(&mapa, sizeof(Mapa), 1, arquivo);

        fclose(arquivo);
        while(!IsKeyPressed(KEY_A))
        {
            BeginDrawing();

            DrawText(TextFormat("JOGO SALVO"), 300, 250, 30, RED);
            DrawText(TextFormat("PRESS A TO CONTINUE"), 220, 300, 30, RED);

            EndDrawing();
        }

        return;
    }
}


void arq_recupera_jogo(Mapa *mapa)
{
    FILE *arquivo;

    arquivo = fopen("jogo.dat", "r");
    if (arquivo == NULL)
    {
        printf("O arquivo nao pode ser aberto.\n");
        return;
    }
    else
    {
        fread(mapa, sizeof(Mapa), 1, arquivo);

        fclose(arquivo);

        return;
    }
}
