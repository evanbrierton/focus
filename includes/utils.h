#include "init.h"

#ifndef UTILS_H
#define UTILS_H

bool canMove(Player player, Square board[BOARD_SIZE][BOARD_SIZE]);
bool canPlace(Player player);
bool checkWin(Player * loser, Player players[N_PLAYERS], Square board[BOARD_SIZE][BOARD_SIZE]);
const char * getColourString(Colour colour);
size_t taxiCabDistance(position origin, position destination);
bool validOrigin(Player player, Square square);
bool validTarget(position target, position origin, Square board[BOARD_SIZE][BOARD_SIZE]);
size_t distanceFromEdge(size_t i, size_t size);
size_t distanceFromCorner(size_t i, size_t j, size_t size);

#endif