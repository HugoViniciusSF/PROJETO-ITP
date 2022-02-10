#ifndef ENTRY_H
#define ENTRY_H
#include "defs.h"

int **CreateSuperPosition(int h, int w, int mapArea[h][w], int nBots, Bot bots[nBots], Posicao actualPosition);
Bot *ReadData(int h, int w, int mapArea[h][w], int *nBots);
int lineIsNum(char *line);

#endif