/********************************************/
/* Decolle Anais-Peters Brice               */
/* pentomino.h                              */
/* Structure of pentomino                   */
/********************************************/
#include <string.h>

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

void file_array(char array_file[1000],FILE* file);

pentomino_ptr create(int x, int y, FILE *file);
pentomino_ptr shape (int x, int y, FILE *file);

int new_pent(char array_file[1000],int pos_file,int position,int x,int y);


#endif
