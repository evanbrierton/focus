#include <stdio.h>
#include "io.h"
#include "utils.h"
#include "square.h"

// Function to execute a player's "move" action
void move(Player * player, Square board[BOARD_SIZE][BOARD_SIZE]) {
  // Prompt the player for which piece to move
  puts("Please enter the coordinates of the stack you'd like to move in the form \"x y\".");
  position originPos = promptPosition(board);

  // Find the square at the position entered by the player
  Square * origin = &board[originPos.y][originPos.x];

  // If the square is not a valid origin, prompt the player to try again
  if (!validOrigin(*player, *origin)) {
    puts("Invalid origin, try another square.");
    printBoard(board);
    move(player, board);
    return;
  }

  // Prompt the player to input a target square
  INPUT_TARGET: puts("Please enter the coordinates on which you'd like to place your stack in the form \"x y\".");
  position targetPos = promptPosition(board);

  // If the square is not a valid target prompt the player to try again
  if (!validTarget(targetPos, originPos, board)) {
    puts("Invalid target, try another square.");
    printBoard(board);
    goto INPUT_TARGET;
  }

  // Merge the target and origin stacks onto the target square
  merge(origin, &board[targetPos.y][targetPos.x], player);
  // Remove the stack at the origin square
  clear(origin);
}

// Function to execute a player's "place" action
void place(Player * player, Square board[BOARD_SIZE][BOARD_SIZE]) {
  // Prompts the player for the position on the board they would like to place their piece
  puts("Please enter the coordinates you'd like to place a piece on in the form \"x y\".");
  position pos = promptPosition(board);

  // Targets the square at the coordinates input by the player
  Square * target = &board[pos.y][pos.x];
  // Checks if the square is valid and prompts the player to try again if it isn't
  if (!target->valid) {
    puts("Invalid target, try another square.");
    printBoard(board);
    place(player, board);
    return;
  }

  push(target, player); // Push the player's piece onto the top of the stack
  player->reserved--;   // Decrenment the player's reserve
}

// Function to execute a player's "peek" action
void peek(Player * player, Square board[BOARD_SIZE][BOARD_SIZE]) {
  // Prompts the player to enter the position they'd like to peek
  puts("Please enter the coordinates you'd like to peek in the form \"x y\".");
  position pos = promptPosition(board);

  // Targets the square to peek and gets the piece at the top of that square's stack
  Square target = board[pos.y][pos.x];
  Piece * current = target.head;

  // Print the name and colour of the player who peeked
  printf(
    "%s\b%s%s peeked the stack at %zu, %zu\n",
    getColourString(player->colour),
    player->name,
    getColourString(BLANK),
    pos.x,
    pos.y
  );

  // Print the stack by iterating through it until reaching a null pointer
  printf("<Top>  ");

  while (current) {
    printf("%s%s%s", getColourString(current->colour), getColourString(BLANK), current->next ? " --> " : "");
    current = current->next;
  }

  puts("  <Bottom>\n");
}
