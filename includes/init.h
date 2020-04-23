#include <stddef.h>
#include <stdbool.h>

#ifndef INIT_H
#define INIT_H

#define BOARD_SIZE 8
#define N_PLAYERS 2
#define MAX_NAME_LENGTH 32

typedef enum _colour { BLANK = 0, RED = 1, GREEN = 2 } Colour;

typedef struct _player{
    Colour colour;
    char name[MAX_NAME_LENGTH];
    size_t reserved;
    size_t captured;
} Player;

typedef struct _piece {
    Colour colour;

    struct _piece * prev;
    struct _piece * next;

} Piece;

typedef struct _square {
    bool valid;

    Piece * head;
    Piece * tail;

    size_t height;
} Square;

typedef struct _position {
  size_t x;
  size_t y;
} position;

void init(Player players[N_PLAYERS], Square board[BOARD_SIZE][BOARD_SIZE]);
void setPiece(Square *, Colour colour);

#endif
