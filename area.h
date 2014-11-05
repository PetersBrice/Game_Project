#ifndef AREA_H
#define AREA_H

#include "square.h"
#include "file.h"

#define MAXW 30  // max width for the area
#define MAXH 30  // max height for the area 

typedef struct area
{
  char shape[15][15];
  square_ptr square[225];
} * area_ptr;

//initialization of the area
area_ptr init_area (char array_file[1000],int pos_x,int pos_y);

void draw_area (char array_file[1000],area_ptr area,SDL_Surface *square_sprite,SDL_Surface *screen);

void get_area(char array_file[1000],char shape[15][15]);

void get_square_area(char array_file[1000],char array_area[15][15],square_ptr square[225],int pos_x,int pos_y);

int max_x_area(area_ptr area,char array_file[1000]);

int max_y_area(area_ptr area,char array_file[1000]);

int min_x_area(area_ptr area,char array_file[1000]);

int min_y_area(area_ptr area,char array_file[1000]);

#endif
