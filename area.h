#ifndef AREA_H
#define AREA_H

#include "square.h"
#include "file.h"

#define MAXW 30  // max width for the area
#define MAXH 30  // max height for the area 

typedef struct area
{
  char shape[15][15];
  /*because we have 20 pentomino */
  square_ptr square[100];
  SDL_Surface * square_sprite;
  SDL_Surface * contour_sprite;
} * area_ptr;

/*initialization of the area*/
area_ptr init_area (char array_file[1000],int pos_x,int pos_y,SDL_Surface * array_color [14]);

/* draw the area */
void draw_area (char array_file[1000],area_ptr area,SDL_Surface *square_sprite,SDL_Surface *screen);

/*get the shape of the area*/
void get_area(char array_file[1000],char shape[15][15]);

/*get the square of the area*/
void get_square_area(char array_file[1000],char array_area[15][15],square_ptr square[225],int pos_x,int pos_y);

/*get the highest x in of the area*/
int max_x_area(area_ptr area,char array_file[1000]);

/*get the highest y in of the area*/
int max_y_area(area_ptr area,char array_file[1000]);

/*get the smallest x in of the area*/
int min_x_area(area_ptr area,char array_file[1000]);

/*get the smallest y in of the area*/
int min_y_area(area_ptr area,char array_file[1000]);

/*free the area*/
void free_area(area_ptr area,char array_file[1000]);

#endif
