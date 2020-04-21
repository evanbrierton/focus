#include <stddef.h>
#include <stdbool.h>

#ifndef INIT_H
#define INIT_H

#define BOARD_SIZE 8
#define N_PLAYERS 2
#define MAX_NAME_LENGTH 32

//colors that a piece can have
typedef enum _colour { RED, GREEN } Colour;

//Player
typedef struct _player{
    Colour colour;
    char name[MAX_NAME_LENGTH];
    size_t kept;
    size_t taken;
} Player;

// A piece
typedef struct _piece {
    //the color associated with a piece
    Colour colour;

    // This is a pointer to the next pieces
    // to create a stack. For this lab you do not have to think too much about it.
    struct _piece * next;

} Piece;

// A Square of the board
typedef struct _square {
    // type of the square (VALID/INVALID)
    bool valid;

    //the piece or the top piece on the stack
    Piece * head;
    Piece * tail;

    //number of pieces on the square
    size_t height;
} Square;

void init(Player players[N_PLAYERS], Square board[BOARD_SIZE][BOARD_SIZE]);

#endif
