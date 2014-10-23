#ifndef AREA_H
#define AREA_H

#include "square.h"

#define MAXW 30  // max width for the area
#define MAXH 30  // max height for the area 

typedef struct area
{
  char shape[10][10];
  square_ptr square[100];
  SDL_Rect pos_area;
  int array_area[MAXW][MAXH];
} * area_ptr;

//initialization of the area
area_ptr init_area (void);

// return the array for the shape of the area
void array_area (area_ptr area, FILE *file);

// draw the area
void draw_area (area_ptr area, SDL_Surface *background);

// center the area
void center_area (area_ptr area, int width, int height);

#endif
