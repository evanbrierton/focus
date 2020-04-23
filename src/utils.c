#include "init.h"
#include <stdlib.h>

// Function to determine whether there are any stacks a player can move remaining on the board
bool canMove(Player player, Square board[BOARD_SIZE][BOARD_SIZE]) {
  // Iterate over each square of the board
  for (size_t i = 0; i < BOARD_SIZE; i++) {
    for (size_t j = 0; j < BOARD_SIZE; j++) {
      // Checks if the player can move each stack on the board
      if (board[i][j].head && board[i][j].head->colour == player.colour) return true;
    }
  }
  // Returns false if the player cannot move any stacks
  return false;
}

// Function to determine if a player can place any pieces from their reserve
bool canPlace(Player player) {
  // Return true if the player has pieces in the reserve, return false otherwise.
  return player.reserved != 0;
}

// Function to check if the game has been one by checking if either player has lost
bool checkWin(Player * loser, Player players[N_PLAYERS], Square board[BOARD_SIZE][BOARD_SIZE]) {
  /* For each player check if they are unable to place a piece and unable to move a piece, if so
  mark them as a loser and return true */
  for (size_t i = 0; i < N_PLAYERS; i++) {
      if (!canPlace(players[i]) && !canMove(players[i], board)) {
        *loser = players[i];
        return true;
      }
    }
  return false; // Otherwise return false
}

// Function to return the colour code and first letter of the colour given a colour enum
const char * getColourString(Colour colour) {
  // Key of colour codes corresponding to the values of the colour enum
  const char * colourCodes[N_PLAYERS + 1] = { "\033[0m" , "\033[1;31mR", "\033[1;32mG" };
  return colourCodes[colour];
}

// Function to calculate the taxi-cab distance between two points on a grid
size_t taxiCabDistance(position origin, position destination) {
  return (size_t)abs(abs((int)destination.x - (int)origin.x) + abs((int)destination.y - (int)origin.y));
}

// Function to calculate the distance a point is from the edge of a square
size_t distanceFromEdge(size_t i, size_t size) {
  return i >= (size / 2) ? size - 1 - i : i;
}

// Function to calculate the distance a point is from the corner of a square
size_t distanceFromCorner(size_t i, size_t j, size_t size) {
  return distanceFromEdge(i, size) + distanceFromEdge(j, size);
}

// Function to determine whether a given player can move a piece from a given square
bool validOrigin(Player player, Square square) {
  /* Check that the square is valid, that it contains a stack and that the top piece of the stack
  belongs to the player */
  return square.valid && square.head && square.head->colour == player.colour;
}

// Function to determine whether a player can move a stack to a given target position
bool validTarget(position target, position origin, Square board[BOARD_SIZE][BOARD_SIZE]) {
  // Calculate the taxi-cab distance between origin and targest
  size_t distance = taxiCabDistance(origin, target);
  /* Check that the target is a valid square, check that the distance is less than or equal to the
  height of the stack and check that the target square is not the same as the orign square */
  return board[target.y][target.x].valid && distance <= board[origin.y][origin.x].height && distance != 0;
}