#ifndef SQUARE_H
#define SQUARE_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<SDL/SDL_ttf.h>
#include<SDL.h>

typedef struct square
{
  SDL_Rect rcSrc ;
  SDL_Rect rcSprite;
  bool set;
} * square_ptr ;

/*add new square*/
square_ptr new_square(SDL_Rect rcSrc, SDL_Rect rcSprite);

/*draw square*/
void draw_square(square_ptr square,SDL_Surface *square_sprite,SDL_Surface *background);

/*create a tab with all the sprite*/
void tab_color (SDL_Surface * array_color[14]);

/*free the array of color*/
void free_color(SDL_Surface * array_color[14]);

/*free the square*/
void free_square(square_ptr square);

#endif
