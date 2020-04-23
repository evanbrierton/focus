#include <stdlib.h>
#include "init.h"

// Function to clear the contents of a given square
void clear(Square * square) {
  square->height = 0;
  square->head = NULL;
  square->tail = NULL;
}

// Function to initialise a given square to empty
void setEmpty(Square * square) {
  square->valid = true;
  clear(square);
}

// Function to initialise a square to empty and then set it to invalid
void setInvalid(Square * square) {
  setEmpty(square);
  square->valid = false;
}

// Function to set a square to a given colour
void setPiece(Square * square, Colour colour) {
  square->valid = true;
  square->head = malloc(sizeof(Piece));
  square->tail = malloc(sizeof(Piece));
  square->head->colour = colour;  // Set to the input colour
  square->head->prev = NULL;
  square->head->next = NULL;
  square->tail = square->head;  // Tail is the same as head for a stack of height 1
  square->height = 1;
}

// Function to pop pieces off the bottom of a stack when a player takes it
void pop(Square * square, Player * player) {
  /* If the piece is of the same colour as the player taking the stack, increment that
  player's reserve */
  if (player->colour == square->tail->colour) player->reserved++;
  // If the piece is of a different colour, increment the players capture count
  else player->captured++;
  // Move the tail 1 further up the stack
  square->tail = square->tail->prev; 
  // Set the tails next to NULL effectively removing the bottom piece
  free(square->tail->next);
  square->tail->next = NULL;
  // Decrement the height of the stack
  square->height--;
}

// Function to merge two stackss
void merge(Square * origin, Square * target, Player * player) {
  // If the target is empty just clone the origin to the target
  if (target->height == 0) {
    *target = *origin;
    return;
  }
  // Link the top of the target stack to the bottom of the origin stack
  target->head->prev = origin->tail;
  // Link the bottom of the origin stack to the top of the target stack
  origin->tail->next = target->head;
  // Sets the new head of the target square to what is now the top of the stack
  target->head = origin->head;
  // Sets the new height to the sum of the heights of the two stacks
  target->height += origin->height;

  // Pops pieces off the bottom of the stack until the new stack is of height < 5
  while (target->height > 5) pop(target, player);
}

// Function to push a new piece on top of a stack when it is placed by a player;
void push(Square * target, Player * player) {
  // Initialise a new piece
  Square newPiece;
  // Set the new piece to the colour of the player placing ist
  setPiece(&newPiece, player->colour);
  // Merge it to the target stack
  merge(&newPiece, target, player);
}
