#include <stdbool.h>
#include <stdio.h>
#include "io.h"

int main() {
    Player players[N_PLAYERS];
    Square board[BOARD_SIZE][BOARD_SIZE];
    size_t turn = 0;
    bool won = false;

    init(players, board);

    while (!won) {
      printBoard(board);
      prompt(players[turn % N_PLAYERS], board);
      turn += 1;
    }

    return 0;
}
