#include "square.h"

square_ptr new_square(SDL_Rect rcSrc,SDL_Rect rcSprite)
{
  square_ptr new_square = (square_ptr)malloc(sizeof(struct square));
  new_square->rcSrc = rcSrc;
  new_square->rcSprite = rcSprite;
}

void draw_square(square_ptr square,SDL_Surface *square_sprite,SDL_Surface *background)
{
  SDL_Rect pos_square;
  pos_square.x = square->rcSrc.x ; 
  printf("x %d\n",pos_square.x);
  pos_square.y = square->rcSrc.y ; 
  printf("y %d\n",pos_square.x);
  SDL_BlitSurface(square_sprite,NULL,background,&pos_square);  
}
