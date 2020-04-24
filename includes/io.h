
#include "init.h"

#ifndef IO_H
#define IO_H

void printPlayerInfo(Player[N_PLAYERS]);
void printBoard(Square[BOARD_SIZE][BOARD_SIZE]);
size_t prompt(Player *, Square[BOARD_SIZE][BOARD_SIZE]);
position promptPosition(Square[BOARD_SIZE][BOARD_SIZE]);

#endif
