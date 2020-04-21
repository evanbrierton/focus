#include <stdbool.h>
#include <stdio.h>
#include "io.h"
#include "utils.h"

int main() {
    Player players[N_PLAYERS];
    Square board[BOARD_SIZE][BOARD_SIZE];
    size_t turn = 0;
    bool won = false;
    Player loser;

    init(players, board);

    while (!won) {
      printPlayerInfo(players);
      printBoard(board);
      loser = checkLoss(players, board);
      if (loser.colour != BLANK) won = true;
      turn += prompt(&players[turn % N_PLAYERS], board);
    }

    Player winner = loser.colour == GREEN ? players[0] : players[1];
    printf("Congratulations %s you won the game.", winner.name);

    return 0;
}
