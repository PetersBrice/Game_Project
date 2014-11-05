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
void tab_pento (char array_file[1000],pentomino_ptr pento_array[20], int array_end,SDL_Surface * array_color[12]);


void draw_array(pentomino_ptr pento_array[20],char array_file[1000],int array_end ,SDL_Surface *screen);

void free_pento(pentomino_ptr pentomino);

int min_x_pent(pentomino_ptr pent);

int min_y_pent(pentomino_ptr pent);

int pos_x_array(pentomino_ptr pent);

int pos_y_array(pentomino_ptr pent);

#endif

/*void mirror(pentomino_ptr pentomino)
{
  int i,j,max_col;
  max_col = 0;
  int min = 2000;
  int max = 0;
  char new_shape[5][5];
  for (i = 0;i < 5;i++){

    for (j = 0;j < 5;j++){
      new_shape[i][j] = 'o';
      if (pentomino->array_pent[i][j] == '#' && max_col < j){
	max_col = j ;
      }
    }

    if (pentomino->square[i]->rcSrc.x<min){
      min = pentomino->square[i]->rcSrc.x;
    }
    if (pentomino->square[i]->rcSrc.x>max){
      max = pentomino->square[i]->rcSrc.x;
    }
  }

  for (i = 0;i < 5;i++){
    for (j = 0;j <= max_col;j++){
      new_shape[i][j]=pentomino->array_pent[i][max_col-j];
    }
  }
  for (i = 0;i < 5;i++){
    for (j = 0;j < 5;j++){
      pentomino->array_pent[i][j] = new_shape[i][j];
    }
  }
  
  for (i = 0;i < 5;i++){
    if (pentomino->square[i]->rcSrc.x == min){
      pentomino->square[i]->rcSrc.x = max;
    }else if (pentomino->square[i]->rcSrc.x == min + SIZE_SQUARE){
      pentomino->square[i]->rcSrc.x = max-SIZE_SQUARE;
    } else if (pentomino->square[i]->rcSrc.x == min + 2*SIZE_SQUARE){
      pentomino->square[i]->rcSrc.x = max-2*SIZE_SQUARE;
    }else if (pentomino->square[i]->rcSrc.x == min + 3 * SIZE_SQUARE){
      if (pentomino->square[i]->rcSrc.x == max){
	pentomino->square[i]->rcSrc.x = min; 
      }else{  
	pentomino->square[i]->rcSrc.x = min +SIZE_SQUARE;
      }
    }else if (pentomino->square[i]->rcSrc.x == max){
      pentomino->square[i]->rcSrc.x = min; 
    }      
  }
}*/
