#ifndef SQUARE_H
#define SQUARE_H

#include<stdio.h>
#include<stdlib.h>
#include<SDL.h>

typedef struct square
{
  SDL_Rect rcSrc ;
  SDL_Rect rcSprite;
} * square_ptr ;

square_ptr new_square(SDL_Rect rcSrc, SDL_Rect rcSprite);
  

#endif
