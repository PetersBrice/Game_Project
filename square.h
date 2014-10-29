#ifndef SQUARE_H
#define SQUARE_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<SDL.h>

typedef struct square
{
  SDL_Rect rcSrc ;
  SDL_Rect rcSprite;
  bool set;
} * square_ptr ;

square_ptr new_square(SDL_Rect rcSrc, SDL_Rect rcSprite);

void draw_square(square_ptr square,SDL_Surface *square_sprite,SDL_Surface *background);

void tab_color (SDL_Surface * array_color[12]);

#endif
