/********************************************/
/* Decolle Anais-Peters Brice               */
/* pentomino.h                              */
/* Structure of pentomino                   */
/********************************************/
#define PENTOMINO_H
#ifndef PENTOMINO_H

#include<stdio.h>
#include<stdlib.h>
#include<SDL/SDL.h>
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
