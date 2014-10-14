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
  int array_pent[5][5];
  int position;
  square_ptr square[5];
  int set ;
} * pentomino_ptr;

pentomino_ptr new_pentomino(int array_pent[5][5],int position,square_ptr square);

void draw_pentomino(pentomino_ptr pentomino,SDL_Surface *square_sprite,SDL_Surface *background);

pentomino_ptr mirror(pentomino_ptr pentomino);


pentomino_ptr create(int x,int y,FILE *file);
pentomino_ptr shape(int x, int y, FILE *file);


#endif
