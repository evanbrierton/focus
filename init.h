#include <stddef.h>

#ifndef INIT_H
#define INIT_H

#define BOARD_SIZE 8
#define PLAYERS_NUM 2

//colors that a piece can have
typedef enum _color { RED, GREEN } color;

// Square types
//INVALID: squares that are on the sides and where no piece can be placed
//VALID: squares where it is possible to place a piece or a stack
typedef enum _squareType { VALID, INVALID } squareType;

//Player
typedef struct _player{
    color playerColor;
    char name[32];
    size_t kept;
    size_t taken;
} player;

// A piece
typedef struct _piece {
    //the color associated with a piece
    color p_color;

    // This is a pointer to the next pieces
    // to create a stack. For this lab you do not have to think too much about it.
    struct _piece * next;

} piece;

// A Square of the board
typedef struct square {
    // type of the square (VALID/INVALID)
    squareType type;

    //the piece or the top piece on the stack
    piece * stack;

    //number of pieces on the square
    int num_pieces;

} square;

//Function to create the players
void initPlayers(player players[PLAYERS_NUM]);

//Function to create the board
void initBoard(square board[BOARD_SIZE][BOARD_SIZE]);

#endif



