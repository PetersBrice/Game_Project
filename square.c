#include "square.h"
#include <assert.h>

square_ptr new_square(SDL_Rect rcSrc,SDL_Rect rcSprite)
{
  square_ptr new_square = (square_ptr)malloc(sizeof(struct square));
  new_square->rcSrc = rcSrc;
  new_square->rcSprite = rcSprite;
  new_square->set = NULL;
  return new_square;
}

void draw_square(square_ptr square,SDL_Surface *square_sprite,SDL_Surface *background)
{
  assert(square);
  SDL_Rect pos_square;
  pos_square.x = square->rcSrc.x ; 
  pos_square.y = square->rcSrc.y ; 
  SDL_BlitSurface(square_sprite,NULL,background,&pos_square);
}

void tab_color(SDL_Surface * array_color[14])
{
  array_color[0] = SDL_LoadBMP("blue.bmp");
  array_color[1] = SDL_LoadBMP("lightgreen.bmp");
  array_color[2] = SDL_LoadBMP("brown.bmp");
  array_color[3] = SDL_LoadBMP("gray.bmp");
  array_color[4] = SDL_LoadBMP("green.bmp");
  array_color[5] = SDL_LoadBMP("lightblue.bmp");
  array_color[6] = SDL_LoadBMP("orange.bmp");
  array_color[7] = SDL_LoadBMP("pink.bmp");
  array_color[8] = SDL_LoadBMP("purple.bmp");
  array_color[9] = SDL_LoadBMP("red.bmp");
  array_color[10] = SDL_LoadBMP("white.bmp");
  array_color[11] = SDL_LoadBMP("yellow.bmp");
  array_color[12] = SDL_LoadBMP("all_white.bmp");
  array_color[13] = SDL_LoadBMP("black.bmp");
}

/* free the sprites of the pentominos's squares */
void free_color(SDL_Surface * array_color[14])
{
  int i;
  for (i=0;i<12;i++){
    SDL_FreeSurface(array_color[i]);
  }
}

void free_square(square_ptr square){
  free(square);
}
