#include <stdio.h>
#include <stdlib.h>
#include "init.h"

void initPlayers(player players[N_PLAYERS]) {
  colour colours[] = { RED, GREEN };
  for (size_t i = 0; i < N_PLAYERS; i++) {
    players[i].colour = colours[i];
    printf("Player %zu, please enter your name: ", i + 1);
    scanf("%s", players[i].name);
    players[i].kept = players[i].taken = 0;
  }
}

//Set Invalid Squares (where it is not possible to place stacks)
void setInvalid(square * s) {
  s->type = INVALID;
  s->stack = NULL;
  s->num_pieces = 0;
}

//Set Empty Squares (with no pieces/stacks)
void setEmpty(square * s) {
  s->type = VALID;
  s->stack = NULL;
  s->num_pieces = 0;
}

//Set squares  with a GREEN piece
void setGreen(square * s) {
  s->type = VALID;
  s->stack = malloc(sizeof(piece));
  s->stack->p_color = GREEN;
  s->stack->next = NULL;
  s->num_pieces = 1;
}

//Set squares with a RED piece
void setRed(square * s) {
  s->type = VALID;
  s->stack = malloc(sizeof(piece));
  s->stack->p_color = RED;
  s->stack->next = NULL;
  s->num_pieces = 1;
}

size_t distanceFromEdge(size_t i, size_t size) {
  return i >= (size / 2) ? size - 1 - i : i;
}

size_t distanceFromCorner(size_t i, size_t j, size_t size) {
  return distanceFromEdge(i, size) + distanceFromEdge(j, size);
}

//initializes the board
void initBoard(square board[BOARD_SIZE][BOARD_SIZE]) {
  for (size_t i = 0; i < BOARD_SIZE; i++) {
    for (size_t j = 0; j< BOARD_SIZE; j++) {
      size_t horizontalDistance = distanceFromEdge(j, BOARD_SIZE) - 1;
      //invalid squares
      if (distanceFromCorner(i, j, BOARD_SIZE) < 2) setInvalid(&board[i][j]);
      else if (distanceFromEdge(i, BOARD_SIZE) == 0 || distanceFromEdge(j, BOARD_SIZE) == 0) {
        setEmpty(&board[i][j]);
      }
      else if(((i % 2) + (horizontalDistance - (horizontalDistance % 2)) / 2) % 2) {
        setRed(&board[i][j]);
      }
      else setGreen(&board[i][j]);
    }
  }
}
