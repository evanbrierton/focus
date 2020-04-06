
#include <stdio.h>
#include "io.h"

int main() {
    player players[N_PLAYERS];
    square board[BOARD_SIZE][BOARD_SIZE];

    initPlayers(players);
    printf("%s\n", players[0].name);

    initBoard(board);
    printBoard(board);

    return 0;
}
