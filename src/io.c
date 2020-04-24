#include <stdio.h>
#include <string.h>
#include "actions.h"
#include "utils.h"

/* Function to print information about each player including name, number of captured pieces and
number of pieces in reserve */
void printPlayerInfo(Player players[N_PLAYERS]) {
  for (size_t i = 0; i < N_PLAYERS; i++) {
    printf(
      "%s has captured \033[1m%zu\033[0m pieces and has \033[1m%zu\033[0m pieces in reserve.\n",
      players[i].name,
      players[i].captured,
      players[i].reserved
    );
  }
}

// Function to print the game board after each move
void printBoard(Square board[BOARD_SIZE][BOARD_SIZE]) {
  puts("");
  printf("-  ");
  // Print the x-axis
  for (size_t j = 0; j < BOARD_SIZE; j++) printf("|  %zu  ", j + 1);
  puts("|");
  for (size_t i = 0; i < BOARD_SIZE; i ++) {
    // Print the y-axis
    printf("%zu  ", i + 1);
    for (size_t j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j].valid) {
        // If a square is empty print a gap
        if (board[i][j].head == NULL) printf("|     ");
        // Otherwise print the first letter of the colour followed by the height of the stack
        else {
          printf(
            "| %s-%zu%s ",
            getColourString(board[i][j].head->colour),
            board[i][j].height,
            getColourString(BLANK)
          );
        }
      }
      // If a square is invalid print a -
      else printf("|  -  ");
    }
    puts("|");
  }
  puts("");
}

// Function to prompt the player for an action
size_t prompt(Player * player, Square board[BOARD_SIZE][BOARD_SIZE]) {
  // Array of action functions
  void (*actions[])(Player *, Square[BOARD_SIZE][BOARD_SIZE]) = { move, place, peek };
  // Key to match user input to function
  char * key[] = { "move", "place", "peek" };
  const size_t nActions = sizeof(key) / sizeof(char *);
  // String to store user input
  char action[6];

  // Prompt the user for an action
  printf("%s it's your turn!\n", player->name);
  puts("Actions available to you:\n");
  puts("  \033[1mmove\033[0m  Move a stack to another square on the board");
  puts("  \033[1mplace\033[0m Place a piece from your reserve onto the board");
  puts("  \033[1mpeek\033[0m  Display the contents of a stack at a particular location");
  printf("\nWhat would you like to do: ");
  scanf("%s", action);
  fflush(stdin);
  
  // Match the users action to it's function
  size_t i;
  for (i = 0; i < nActions && strcmp(action, key[i]) != 0; i++);

  // Check if the action is invalid or if the user cannot perform the input action
  if (i == nActions) puts("\nInvalid action!");
  else if (actions[i] == move && !canMove(*player, board)) puts("You have no stacks to move!");
  else if (actions[i] == place && !canPlace(*player)) puts("\nYou have no pieces in reserve to place!");
  // If the action is valid execute the action and return the value to increment turns with
  else {
    actions[i](player, board);
    if (actions[i] == peek) return 0;
    return 1;
  }

  // Otherwise reprompt the user for action
  printBoard(board);
  return prompt(player, board);
}

// Function to prompt a user to input a position, used in various actions
position promptPosition(Square board[BOARD_SIZE][BOARD_SIZE]) {
  // Initialise variables
  size_t x, y;
  
  // Prompt user for input
  printf("Coordinates: ");
  fflush(stdin);
  int result = scanf("%zu %zu", &x, &y); // NOLINT
  puts("\n");

  // Checks that the square is within the bounds of the board and reprompts otherwise
  if (result != 2 || x <= 0 || BOARD_SIZE < x  || y <= 0 || BOARD_SIZE < y)  {
    puts("Invalid position, try another one.");
    return promptPosition(board);
  }

  // Create a position struct given the input coordinates and return it
  position pos = { x - 1, y - 1 };
  return pos;
}
