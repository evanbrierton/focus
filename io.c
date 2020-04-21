#include <stdio.h>
#include <string.h>
#include "io.h"
#include "actions.h"

void printBoard(Square board[BOARD_SIZE][BOARD_SIZE]){
    for (size_t i = 0; i < BOARD_SIZE; i ++){
        for (size_t j = 0; j < BOARD_SIZE; j++){
            if (board[i][j].valid) {
                if (board[i][j].head == NULL) printf("|     ");
                else if (board[i][j].head->colour == GREEN) printf("| \033[1;32mG-%zu\033[0m ", board[i][j].height);
                else printf("| \033[1;31mR-%zu\033[0m ", board[i][j].height);
            }
            else printf("|  -  ");
        }
        printf("|\n");
    }
}

void prompt(Player player, Square board[BOARD_SIZE][BOARD_SIZE]) {
  void (*actions[])() = { move, place, peek };
  char * key[] = { "move", "place", "peek" };
  const size_t nActions = sizeof(key) / sizeof(char *);
  char action[6];

  printf("%s it's your turn!\n", player.name);
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
  } else actions[i](player, board);
}
