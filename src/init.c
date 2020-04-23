#include <stdio.h>
#include <string.h>
#include "square.h"
#include "utils.h"

// Function to initialise the players of the game
void initPlayers(Player players[N_PLAYERS]) {
  // Array of available colours
  Colour colours[] = { RED, GREEN };
  // For each player initialise their colour, reserved and captured properties
  for (size_t i = 0; i < N_PLAYERS; i++) {
    players[i].colour = colours[i];
    players[i].reserved = players[i].captured = 0;
    // Prompt player to input a name
    printf(
      "%s\bPlayer %zu%s, please enter your name: ",
      getColourString(colours[i]),
      i + 1,
      getColourString(BLANK)
    );

    // Scan input for player namse
    scanf("%s", players[i].name);
    // Buffer for string concatenation
    char buffer[64] = "";
    // Add colour string corresponding to player colour
    strcat(buffer, getColourString(colours[i]));
    // Eliminate colour letter
    strcat(buffer, "\b");
    // Reset colour after name print
    strcat(players[i].name, getColourString(BLANK));
    // Merge strings
    strcat(buffer, players[i].name);
    // Copy to player name
    strcpy(players[i].name, buffer);
  }
}

// Function to initialise the game board
void initBoard(Square board[BOARD_SIZE][BOARD_SIZE]) {
  for (size_t i = 0; i < BOARD_SIZE; i++) {
    for (size_t j = 0; j< BOARD_SIZE; j++) {
      // Set the 3 squares at each corner to invalid
      if (distanceFromCorner(i, j, BOARD_SIZE) < 2) setInvalid(&board[i][j]);
      // Set all the remaining edge squares to be empty
      else if (distanceFromEdge(i, BOARD_SIZE) == 0 || distanceFromEdge(j, BOARD_SIZE) == 0) {
        setEmpty(&board[i][j]);
      }
      else {
        // Set the pieces in the remaining squares in an RRGGRR pattern
        size_t horizontalDistance = distanceFromEdge(j, BOARD_SIZE) - 1;
        setPiece(
          &board[i][j],
          ((i % 2) + (horizontalDistance - (horizontalDistance % 2)) / 2) % 2 ? RED : GREEN
        );
      }
    }
  }
}

// Utility function to initialise both the board and players
void init(Player players[N_PLAYERS], Square board[BOARD_SIZE][BOARD_SIZE]) {
  initPlayers(players);
  initBoard(board);
}
