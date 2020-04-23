#include "init.h"

#ifndef ACTIONS_H
#define ACTIONS_H

void move(Player *, Square board[BOARD_SIZE][BOARD_SIZE]);
void place(Player *, Square board[BOARD_SIZE][BOARD_SIZE]);
void peek(Player *, Square board[BOARD_SIZE][BOARD_SIZE]);

#endif
