
#include <stdio.h>
#include "io.h"

int main() {
    player players[PLAYERS_NUM];
    square board[BOARD_SIZE][BOARD_SIZE];

    // initPlayers(players);

    initBoard(board);
    printBoard(board);

    return 0;
}
