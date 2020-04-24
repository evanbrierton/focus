#include "init.h"

#ifndef UTILS_H
#define UTILS_H

bool canMove(Player, Square[BOARD_SIZE][BOARD_SIZE]);
bool canPlace(Player);
bool checkWin(Player *, Player[N_PLAYERS], Square[BOARD_SIZE][BOARD_SIZE]);
const char * getColourString(Colour);
size_t taxiCabDistance(position, position);
bool validOrigin(Player, Square);
bool validTarget(position, position, Square[BOARD_SIZE][BOARD_SIZE]);
size_t distanceFromEdge(size_t, size_t);
size_t distanceFromCorner(size_t, size_t, size_t);
void cleanup(Square[BOARD_SIZE][BOARD_SIZE]);

#endif