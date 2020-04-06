#include <stdio.h>
#include "io.h"

/* FUnction to print the board:
 * Invalid Squares are printed as | - |
 * Valid empty squares are printed as |   |
 * Valid squares with a GREEN piece are printed as | G |
 * Valid squares with a RED piece are printed as | R | */

void printBoard(square board[BOARD_SIZE][BOARD_SIZE]){
    for (size_t i = 0; i < BOARD_SIZE; i ++){
        for (size_t j = 0; j < BOARD_SIZE; j++){
            if (board[i][j].type == VALID) {
                if (board[i][j].stack == NULL) printf("|   ");
                else if (board[i][j].stack->p_color == GREEN) printf("| G ");
                else printf("| R ");
            }
            else printf("| - ");
        }
        printf("|\n");
    }
}
