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
  position pos = { x, y };
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

void merge(Square * origin, Square * target) {
  origin->tail->next = target->head;
  target->head = origin->head;
  target->height += origin->height;
}

void move(Player player, Square board[BOARD_SIZE][BOARD_SIZE]) {
  puts("Please enter the coordinates of the stack you'd like to move in the form \"x y\".");
  puts("Keep in mind the top-left corner is (0, 0)");
  position originPos = promptPosition(board);
  Square * origin = &board[originPos.y][originPos.x];
  if (!validOrigin(player, *origin)) {
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

  merge(origin, target);
  clear(origin);
}

void place(Player player, Square board[BOARD_SIZE][BOARD_SIZE]) {
  puts("place");
}

void peek(Player player, Square board[BOARD_SIZE][BOARD_SIZE]) {
  puts("peek");
}
