/********************************************/
/* Decolle Anais-Peters Brice               */
/* pentomino.h                              */
/* Structure of pentomino                   */
/********************************************/

#ifndef PENTOMINO_H
#define PENTOMINO_H


#include<stdio.h>
#include<stdlib.h>
#include<SDL.h>
typedef struct pentomino
{
  char array_pent[5][5];
  double angle;
  SDL_Rect rcSrc;
  SDL_Rect rcSprite;
  int set ;
} * pentomino_ptr;

pentomino_ptr new_pentomino(char array_pent[5][5],double angle,SDL_Rect rcSrc,SDL_Rect rcSprite);

pentomino_ptr mirror(pentomino_ptr pentomino);

#endif
