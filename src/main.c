// Written by Evan Brierton - 19374423
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "utils.h"

int main() {
  // Initialise necessary variables
  Player players[N_PLAYERS];
  Square board[BOARD_SIZE][BOARD_SIZE];
  size_t turn = 0;
  bool won = false;
  Player loser;

  // Initialise the players and board
  init(players, board);

  // While the game has not been won continue the turn cyclse
  while (!won) {
    printPlayerInfo(players);
    printBoard(board);
    // Increment the turn counter if the player selected an action that used up their turn
    turn += prompt(&players[turn % N_PLAYERS], board);
    // Checks if the game has been won and sets the loser player accordingly
    won = checkWin(&loser, players, board);
  }

  // Sets the winner to the other player
  Player winner = loser.colour == GREEN ? players[0] : players[1];

  // Print a message for the winner
  printBoard(board);
  printf("Congratulations %s you won the game!\n", winner.name);

  // Cleanup and end execution
  
  cleanup(board);
  return 0;
}
