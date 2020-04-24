#include "init.h"

#ifndef SQUARE_H
#define SQUARE_H

void setEmpty(Square *);
void setInvalid(Square *);

void clear(Square *);
void pop(Square *, Player *);
void merge(Square *, Square *, Player *);
void push(Square *, Player *);

#endif
