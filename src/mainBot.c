#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "defs.h"
#include "entryFunctions.h"
#include "distanceFunctions.h"

int main()
{
  char line[MAX_STR]; // dados temporários
  // removida a leitura do identificador do bot
  int nBots; // quantidade de bots
  Bot *bots; // vetor de bots
  // personalizados
  char *act; // ações a serem executadas
  MyBot myBot;  // estrutura personalizada para armazenar dados do bot

  setbuf(stdin, NULL);  // stdin, stdout e stderr não terão buffers
  setbuf(stdout, NULL); // assim, nada é "guardado temporariamente"
  setbuf(stderr, NULL);

  // ====== INÍCIO DA PARTIDA ======
  int h, w;                    // tamanho em questão de altura (height) e largura (width)
  scanf("AREA %i %i", &h, &w); // lê a dimensão da área de pesca: altura (h) x largura (w)
  int mapArea[h][w];
  int **fishingSuperPosition = NULL;
  scanf(" ID %s", myBot.bot.id); // obs: o " " antes de ID é necessário para ler o '\n' da linha anterior

  // === PARTIDA ===
  // O bot entra num laço infinito, mas não se preocupe porque o simulador irá matar
  // o processo quando o jogo terminar.
  while (1)
  {
    memset(mapArea, 0, sizeof(mapArea)); // zera a área de pesca

    // LÊ OS DADOS DO JOGO E ATUALIZA OS DADOS DO BOT
    bots = ReadData(h, w, mapArea, &nBots);

    // PEGA A POSIÇÃO DO BOT DENTRO DA ÁREA DE PESCA
    for (int i = 0; i < nBots; i++)
    {
      if (strcmp(bots[i].id, myBot.bot.id) == 0)
      {
        strcpy(myBot.bot.id, bots[i].id);
        myBot.bot.posicao = bots[i].posicao;
        break;
      }
    }
    // INSIRA UMA LÓGICA PARA ESCOLHER UMA AÇÃO A SER EXECUTADA
    fishingSuperPosition = CreateSuperPosition(h, w, mapArea, nBots, bots, myBot.bot.posicao);
    if (myBot.charge < 10)
    {
      Posicao objPos = FindNeastFishingSpot(h, w, fishingSuperPosition, myBot.bot.posicao);
      if (objPos.x == myBot.bot.posicao.x && objPos.y == myBot.bot.posicao.y)
      {
        // envia a ação escolhida (nesse exemplo, pescar)
        act = "FISH";
      }
      else
      {
        // envia a ação escolhida (nesse exemplo, ir para cima, baixo, esquerda ou direita)
        act = adequatePath(h, w, fishingSuperPosition, myBot.bot.posicao, objPos);
      }
    }
    else
    {
      Posicao objPos = LeastDistantPort(h, w, fishingSuperPosition, myBot.bot.posicao);
      if (objPos.x == myBot.bot.posicao.x && objPos.y == myBot.bot.posicao.y)
      {
        act = "SELL";
      }
      else
      {
        act = adequatePath(h, w, fishingSuperPosition, myBot.bot.posicao, objPos);
      }
    }
    printf("%s\n", act);

    // leia a resposta da ação do bot e atualize seu status
    scanf("%s", line);
    if (lineIsNum(line))
    {
      myBot.charge = 0;
    }
    else if (strcmp(line, "SNAPPER") == 0 || strcmp(line, "MULLET") == 0 || strcmp(line, "SEABASS") == 0)
      myBot.charge++;
  }

  return 0;
}