#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "distanceFunctions.h"

/**
 * @brief Função para pegar a distancia entre duas posição
 *
 * @param i Posição do X matriz na for
 * @param j Posição do Y matriz na for
 * @param Posicao actualPosition
 */
int getDistance(int i, int j, Posicao actualPosition)
{
  return abs(actualPosition.x - i) + abs(actualPosition.y - j);
}

/**
 * @brief Essa função serve para pegar o preço do peixe
 *
 * @param x o peixe
 * @return int
 */
int getPrice(int x)
{
  switch (x)
  {
  case 1:
    return MULLET;
    break;
  case 2:
    return SNAPPER;
    break;
  case 3:
    return SEABASS;
    break;
  default:
    return 0;
    break;
  }
}

/**
 * @brief Função para achar o porto mais próximo ao barco
 *
 * @param h Altura da matriz
 * @param w Largura da matriz
 * @param fishingSuperPosition Matriz sobreposta com dados do mapa
 * @param actualPosition Posição atual do BOT
 * @return Posicao
 */
Posicao LeastDistantPort(int h, int w, int **fishingSuperPosition, Posicao actualPosition)
{
  Posicao LeastDPort = actualPosition;
  // Buscará o porto mais próximo
  int distance = __INT_MAX__;
  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      if (fishingSuperPosition[i][j] == 1)
      {
        if (getDistance(i, j, actualPosition) < distance)
        {
          distance = getDistance(i, j, actualPosition);
          LeastDPort.x = i;
          LeastDPort.y = j;
        }
      }
    }
  }

  return LeastDPort;
}

/**
 * @brief Função para procurar a posição mais proxima de uma ponto com pesca
 *
 * @param h Altura da matriz
 * @param w Largura da matriz
 * @param fishingSuperPosition Matriz sobreposta com dados do mapa
 * @param actualPosition Posição do meu bot
 * @return Position
 */
Posicao FindNeastFishingSpot(int h, int w, int **fishingSuperPosition, Posicao actualPosition)
{
  Posicao nearFS = actualPosition;

  // Achar a posição da ponto de pesca mais proximo
  int distance = __INT_MAX__;
  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      // Caso ache a ponto verifica a quantidade de peixes
      if (fishingSuperPosition[i][j] >= 12 && fishingSuperPosition[i][j] % 10 > 1)
      {
        // Calcula a distância entre a ponto de pesca e a posição atual
        if (getDistance(i, j, actualPosition) < distance)
        { // Se a distância deste ponto de pesca for menor que o anterior
          distance = getDistance(i, j, actualPosition);
          // Salva esse ponto de pesca
          nearFS.x = i;
          nearFS.y = j;
        }
        else if (distance == getDistance(i, j, actualPosition))
        { // Se a distância deste ponto de pesca for igual ao anterior
          // Verifica qual ponto de pesca tem mais peixes
          int currentCostBenefitRatio = getPrice(fishingSuperPosition[i][j] / 10) * (fishingSuperPosition[i][j] % 10);
          int previousCostBenefitRatio = getPrice(fishingSuperPosition[nearFS.x][nearFS.y] / 10) * (fishingSuperPosition[nearFS.x][nearFS.y] % 10);
          if (currentCostBenefitRatio > previousCostBenefitRatio)
          {
            // Salva esse ponto de pesca melhor
            nearFS.x = i;
            nearFS.y = j;
          }
        }
      }
    }
  }

  return nearFS; // Caso não ache, apenas retornara o ponto atual
}

/**
 * @brief Função para avaliar o melhor caminho para o ponto de pesca e/ou porto
 *
 * @param h Altura da matriz
 * @param w Largura da matriz
 * @param fishingSuperPosition Matriz sobreposta com dados do mapa
 * @param actualPosition Posição do meu bot
 * @param objectivePoint Posição do objetivo
 * @return char*
 */
char *adequatePath(int h, int w, int **fishingSuperPosition, Posicao actualPosition, Posicao objectivePoint)
{
  if (actualPosition.x > objectivePoint.x)
  { // Acima
    if (fishingSuperPosition[actualPosition.x - 1][actualPosition.y] != -1)
      return "UP"; // e não há obstáculo
    else if (actualPosition.y == objectivePoint.y)
    { // se houver obstáculo, mas o obstáculo estiver na mesma coluna (caso o ponto não esteja na mesma coluna isso será tratado nos próximos ifs)
      if (actualPosition.y < w - 1)
      {
        if (fishingSuperPosition[actualPosition.x][actualPosition.y + 1] != -1)
          return "RIGHT";
        else
          return "UP";
      }
      else if (actualPosition.y > 0)
      {
        if (fishingSuperPosition[actualPosition.x][actualPosition.y - 1] != -1)
          return "LEFT";
        else
          return "UP";
      }
      else
        return "WAIT"; // Ele esperará o proximo participante jogar
    }
  }
  if (actualPosition.x < objectivePoint.x)
  { // Abaixo
    if (fishingSuperPosition[actualPosition.x + 1][actualPosition.y] != -1)
      return "DOWN";
    else if (actualPosition.y == objectivePoint.y)
    {
      if (actualPosition.y < w - 1)
      {
        if (fishingSuperPosition[actualPosition.x][actualPosition.y + 1] != -1)
          return "RIGHT";
        else
          return "DOWN";
      }
      else if (actualPosition.y > 0)
      {
        if (fishingSuperPosition[actualPosition.x][actualPosition.y - 1] != -1)
          return "LEFT";
        else
          return "DOWN";
      }
      else
        return "WAIT"; // Ele esperará o proximo participante jogar
    }
  }
  if (actualPosition.y < objectivePoint.y)
  { // Direita
    if (fishingSuperPosition[actualPosition.x][actualPosition.y + 1] != -1)
      return "RIGHT"; // e não tem obstaculo
    else if (actualPosition.x < h - 1)
    {
      if (fishingSuperPosition[actualPosition.x + 1][actualPosition.y] != -1)
        return "DOWN";
      else
        return "WAIT";
    }
    else if (actualPosition.x > 0)
    {
      if (fishingSuperPosition[actualPosition.x - 1][actualPosition.y] != -1)
        return "UP";
      else
        return "RIGHT";
    }
    else
      return "WAIT"; // Ele esperará o proximo participante jogar
  }
  if (actualPosition.y > objectivePoint.y)
  { // Esquerda
    if (fishingSuperPosition[actualPosition.x][actualPosition.y - 1] != -1)
      return "LEFT";
    else if (actualPosition.x < h - 1)
    {
      if (fishingSuperPosition[actualPosition.x + 1][actualPosition.y] != -1)
        return "DOWN";
      else
        return "LEFT";
    }
    else if (actualPosition.x > 0)
    {
      if (fishingSuperPosition[actualPosition.x - 1][actualPosition.y] != -1)
        return "UP";
      else
        return "LEFT";
    }
    else
      return "WAIT"; // Ele esperará o proximo participante jogar
  }
  return "WAIT";
}