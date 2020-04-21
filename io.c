#include <stdio.h>
#include <string.h>
#include "io.h"
#include "actions.h"

void printPlayerInfo(Player players[N_PLAYERS]) {
  for (size_t i = 0; i < N_PLAYERS; i++) {
    printf(
      "%s has captured %zu pieces and has %zu pieces in reserve.\n",
      players[i].name,
      players[i].captured,
      players[i].reserved
    );
  }
}

void printBoard(Square board[BOARD_SIZE][BOARD_SIZE]) {
  puts("");
  printf("-  ");
  for (size_t j = 0; j < BOARD_SIZE; j++) printf("|  %zu  ", j + 1);
  puts("|");
  for (size_t i = 0; i < BOARD_SIZE; i ++) {
    printf("%zu  ", i + 1);
    for (size_t j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j].valid) {
        if (board[i][j].head == NULL) printf("|     ");
        else if (board[i][j].head->colour == GREEN) printf("| \033[1;32mG-%zu\033[0m ", board[i][j].height);
        else printf("| \033[1;31mR-%zu\033[0m ", board[i][j].height);
      }
      else printf("|  -  ");
    }
    puts("|");
  }
  puts("");
}

size_t prompt(Player * player, Square board[BOARD_SIZE][BOARD_SIZE]) {
  void (*actions[])() = { move, place, peek };
  char * key[] = { "move", "place", "peek" };
  const size_t nActions = sizeof(key) / sizeof(char *);
  char action[6];

  printf("%s it's your turn!\n", player->name);
  puts("Actions available to you:\n");
  puts("  \033[1mmove\033[0m  Move a stack to another square on the board");
  puts("  \033[1mplace\033[0m Place a piece from your reserve onto the board");
  puts("  \033[1mpeek\033[0m  Display the contents of a stack at a particular location");
  printf("\nWhat would you like to do: ");
  scanf("%s", action);

  size_t i;
  for (i = 0; i < nActions && strcmp(action, key[i]); i++);
  if (i == nActions) {
    puts("\nInvalid action!");
    prompt(player, board);
    return 0;
  } 
  if (actions[i] == place && player->reserved == 0) {
    puts("\nYou have no pieces in reserve to place!");
    prompt(player, board);
    return 0;
  } 

  actions[i](player, board);
  if (actions[i] == peek) return 0;
  return 1;
}
