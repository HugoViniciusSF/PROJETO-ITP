
#ifndef DISTANCE_H
#define DISTANCE_H

Posicao LeastDistantPort(int h, int w, int **fishingSuperPosition, Posicao actualPosition);
Posicao FindNeastFishingSpot(int h, int w, int **fishingSuperPosition, Posicao actualPosition);
int getPrice(int x);
char *adequatePath(int h, int w, int **fishingSuperPosition, Posicao actualPosition, Posicao objPos);

#endif