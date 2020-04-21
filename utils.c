#include "init.h"

bool boardContainsColour(Square board[BOARD_SIZE][BOARD_SIZE], Colour colour) {
  for (size_t i = 0; i < BOARD_SIZE; i++) {
      for (size_t j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j].head && board[i][j].head->colour == colour) return true;
    }
  }
  return false;
}

Player checkLoss(Player players[N_PLAYERS], Square board[BOARD_SIZE][BOARD_SIZE]) {
  for (size_t i = 0; i < N_PLAYERS; i++) {
    if (players[i].reserved == 0 && !boardContainsColour(board, players[i].colour)) {
      return players[i];
    }
  }
  Player blankPlayer = { BLANK, "", 0, 0 };
  return blankPlayer;
}