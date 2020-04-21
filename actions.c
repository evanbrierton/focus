#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "init.h"

typedef struct _position {
  size_t x;
  size_t y;
} position;

position promptPosition(Square board[BOARD_SIZE][BOARD_SIZE]) {
  size_t x, y;
  printf("Coordinates: ");
  scanf("%zu %zu", &x, &y);
  puts("\n");
  if (x >= BOARD_SIZE || y >= BOARD_SIZE) {
    puts("Position out of bounds");
    promptPosition(board);
  }
  position pos = { x - 1, y - 1 };
  return pos;
}

void printBool(bool value) {
  printf("%s\n", value ? "true" : "false");
}

bool validOrigin(Player player, Square square) {
  return square.valid && square.head && square.head->colour == player.colour;
}

size_t taxiCabDistance(position origin, position destination) {
  return abs((int)origin.x - (int)destination.x) + abs((int)origin.y - (int)destination.y);
}

void clear(Square * square) {
  square->height = 0;
  square->head = NULL;
  square->tail = NULL;
}

void pop(Square * square, Player * player) {
  if (player->colour == square->tail->colour) player->reserved++;
  else player->captured++;
  square->tail = square->tail->prev;
  square->tail->next = NULL;
  square->height--;
}

void merge(Square * origin, Square * target, Player * player) {
  if (target->height == 0) {
    *target = *origin;
    return;
  }
  target->head->prev = origin->tail;
  origin->tail->next = target->head;
  target->head = origin->head;
  if(target->height == 1) target->tail->prev = origin->tail;
  target->height += origin->height;
  while (target->height > 5) pop(target, player);
}

void push(Square * target, Player * player) {
  Square newPiece;
  if (player->colour == GREEN) setGreen(&newPiece);
  else setRed(&newPiece);
  merge(&newPiece, target, player);
}

void move(Player * player, Square board[BOARD_SIZE][BOARD_SIZE]) {
  puts("Please enter the coordinates of the stack you'd like to move in the form \"x y\".");
  puts("Keep in mind the top-left corner is (1, 1)");
  position originPos = promptPosition(board);
  Square * origin = &board[originPos.y][originPos.x];
  if (!validOrigin(*player, *origin)) {
    puts("Invalid origin, try another square.");
    move(player, board);
    return;
  };

  puts("Please enter the coordinates on which you'd like to place your stack \"x y\".");
  position targetPos = promptPosition(board);
  Square * target = &board[targetPos.y][targetPos.x];
  if (!origin->valid || taxiCabDistance(originPos, targetPos) > origin->height) {
    puts("Invalid target, try another square.");
    move(player, board);
    return;
  }

  merge(origin, target, player);
  clear(origin);
}

void place(Player * player, Square board[BOARD_SIZE][BOARD_SIZE]) {
  puts("Please enter the coordinates you'd like to place a piece on in the form \"x y\".");
  position pos = promptPosition(board);
  Square * target = &board[pos.y][pos.x];
  if (!target->valid) {
    puts("Invalid target, try another square.");
    place(player, board);
    return;
  }
  push(target, player);
  player->reserved--;
}

char * getColourString(Piece * piece) {
  return piece->colour == GREEN ? "\033[1;32mG\033[0m" : "\033[1;31mR\033[0m";
}

void peek(Player player, Square board[BOARD_SIZE][BOARD_SIZE]) {
  puts("Please enter the coordinates you'd like to peek in the form \"x y\".");
  position pos = promptPosition(board);
  Square target = board[pos.y][pos.x];
  Piece * current = target.head;
  
  printf("<Top>  ");

  while (current) {
    printf("%s%s", getColourString(current), current->next ? " --> " : "");
    current = current->next;
  }

  puts("  <Bottom>");
}
