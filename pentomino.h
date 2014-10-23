/********************************************/
/* Decolle Anais-Peters Brice               */
/* pentomino.h                              */
/* Structure of pentomino                   */
/********************************************/
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "area.h"

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

pentomino_ptr new_pentomino(int position);

void draw_pentomino(pentomino_ptr pentomino,SDL_Surface *square_sprite,SDL_Surface *background);

pentomino_ptr mirror(pentomino_ptr pentomino);

void file_array(char array_file[1000],FILE* file);

pentomino_ptr create(int x, int y, FILE *file);
pentomino_ptr shape (int x, int y, FILE *file);

int new_pent(char array_file[1000],int pos_file,int position,int x,int y);

int begin_pent (char array_file[1000]);

int nb_pent(char array_file[1000]);

int new_array(char array_file[1000],int pos_file,char array_pent[5][5]);

bool test_pento(char array_file[1000]);

int size_area(char array_file[1000]);

pentomino_ptr get_square(pentomino_ptr pentomino ,int pos_x,int pos_y);

void tab_pento (char array_file[1000],pentomino_ptr pento_array[20]);

#endif
