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

/*create a new pentomino*/
pentomino_ptr new_pentomino(int position);

/*drew a new pentomino*/
void draw_pentomino(pentomino_ptr pentomino,SDL_Surface *square_sprite,SDL_Surface *background);

pentomino_ptr mirror(pentomino_ptr pentomino);

/*create a tab of all the caracters in the file*/
int file_array(char array_file[1000],FILE* file);

pentomino_ptr create(int x, int y, FILE *file);
pentomino_ptr shape (int x, int y, FILE *file);

/*return the position of the first pentomino*/
int begin_pent (char array_file[1000]);

/*return the number of pentopmino*/
int nb_pent(char array_file[1000], int array_end);

/*take the shape of a pentomino in the file*/
int new_array(char array_file[1000],int pos_file,char array_pent[5][5]);

/*test if the number of pentomino can solve the puzzle*/
bool test_pento(char array_file[1000], int array_end);

/*return the size of the area*/
int size_area(char array_file[1000]);

/*transform the shape in a tab of square*/
void get_square(square_ptr square[5],char array_pent[5][5] ,int pos_x,int pos_y);

/*create a table of pentomino*/
void tab_pento (char array_file[1000],pentomino_ptr pento_array[20], int array_end);

void get_area(char array_file[1000],char shape[10][10]);

void draw_array(pentomino_ptr pento_array[20],char array_file[1000],int array_end ,SDL_Surface *square_sprite,SDL_Surface *background);

#endif
