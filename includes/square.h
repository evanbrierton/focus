#include "init.h"

#ifndef SQUARE_H
#define SQUARE_H

void setEmpty(Square * s);
void setInvalid(Square * s);

void clear(Square * square);
void pop(Square * square, Player * player);
void merge(Square * origin, Square * target, Player * player);
void push(Square * target, Player * player);

#endif
