/********************************************/
/* Decolle Anais-Peters Brice               */
/* pentomino.h                              */
/* Structure of pentomino                   */
/********************************************/

#ifndef PENTOMINO_H
#define PENTOMINO_H


#include "square.h"

typedef struct pentomino
{
  char array_pent[5][5];
  int position;
  square_ptr square[5];
  int set ;
} * pentomino_ptr;

pentomino_ptr new_pentomino(char array_pent[5][5],int position,square_ptr square);

pentomino_ptr mirror(pentomino_ptr pentomino);

#endif
