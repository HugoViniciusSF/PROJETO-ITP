#include <stdio.h>
#include <stdlib.h>
#include "entryFunctions.h"

/**
 * @brief Função para criar uma matriz com os dados do mapa
 *
 * @param h Altura da matriz
 * @param w Largura da matriz
 * @param mapArea Matriz principal com os dados do mapa
 * @param nBots quantidade de bots
 * @param bots os bots existente
 * @param actualPosition a minha posição atual
 * @return int**
 */
int **CreateSuperPosition(int h, int w, int mapArea[h][w], int nBots, Bot bots[nBots], Posicao actualPosition)
{
  // criando uma nova matriz com o height e width 
  int **createSuperPosition = malloc(h * sizeof(int *));
  for (int i = 0; i < h; i++)
    createSuperPosition[i] = malloc(w * sizeof(int));

  // Usando a matrix original e a copiando na nova matrix
  for (int i = 0; i < h; i++)
    for (int j = 0; j < w; j++)
      createSuperPosition[i][j] = mapArea[i][j];

  // Alterando os valores da posição dos inimigos para -1
  for (int i = 0; i < nBots; i++)
    createSuperPosition[bots[i].posicao.x][bots[i].posicao.y] = -1;

  // Guardar posição do meu bot
  createSuperPosition[actualPosition.x][actualPosition.y] = mapArea[actualPosition.x][actualPosition.y];

  return createSuperPosition;
}

// Função fornecida pela questão para armazer dados do BOT
Bot *ReadData(int h, int w, int mapArea[h][w], int *nBots)
{
  // char id[MAX_STR]; UNSED VARIABLE;
  int n;

  // read the fishing area
  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      scanf("%i", &mapArea[i][j]);
    }
  }

  // read the data of the players
  scanf(" BOTS %i", &n); // The ' ' is for the '\n' of the previous line
  *nBots = n;
  Bot *bots = malloc(n * sizeof(Bot));
  for (int i = 0; i < n; i++)
  {
    scanf("%s %i %i", bots[i].id, &bots[i].posicao.x, &bots[i].posicao.y);
  }
  return bots;
}

/**
 * @brief Funçaõ utilitária para verificar se é um número
 *
 * @param line linha para identificação
 * @return int
 */
int lineIsNum(char *line)
{
  int i = 0;
  while (line[i] != '\0')
  {
    if (line[i] < '0' || line[i] > '9')
      return 0;
    i++;
  }
  return 1;
}