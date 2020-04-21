
#include "init.h"

#ifndef IO_H
#define IO_H

//Function to print the board
void printPlayerInfo(Player players[N_PLAYERS]);
void printBoard(Square board[BOARD_SIZE][BOARD_SIZE]);
size_t prompt(Player *, Square board[BOARD_SIZE][BOARD_SIZE]);

#endif
