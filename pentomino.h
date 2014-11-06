/********************************************/
/* Decolle Anais-Peters Brice               */
/* pentomino.h                              */
/* Structure of pentomino                   */
/********************************************/
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "area.h"
#include "file.h"

#ifndef PENTOMINO_H
#define PENTOMINO_H


#include "square.h"

typedef struct pentomino
{
  char array_pent[5][5];
  int position;
  square_ptr square[5];
  int set ;
  int coat;
  SDL_Surface * square_sprite;
} * pentomino_ptr;

/*create a new pentomino*/
pentomino_ptr new_pentomino(int position);

/*drew a new pentomino*/
void draw_pentomino(pentomino_ptr pentomino,SDL_Surface *screen);

/*take the shape of a pentomino in the file*/
int new_array(char array_file[1000],int pos_file,char array_pent[5][5]);

/*transform the shape in a tab of square*/
void get_square(square_ptr square[5],char array_pent[5][5] ,int pos_x,int pos_y);

/*create a table of pentomino*/
void tab_pento (char array_file[1000],pentomino_ptr pento_array[20], int array_end,SDL_Surface * array_color[14]);


void draw_array(pentomino_ptr pento_array[20],char array_file[1000],int array_end ,SDL_Surface *screen);

void free_pento(pentomino_ptr pentomino);

int min_x_pent(pentomino_ptr pent);

int min_y_pent(pentomino_ptr pent);

int pos_x_array(pentomino_ptr pent);

int pos_y_array(pentomino_ptr pent);

void free_pentomino(pentomino_ptr pentomino);

void free_pento_array(pentomino_ptr pento_array[20],char array_file[1000],int array_end);

#endif

