#include "square.h"

square_ptr new_square(SDL_Rect rcSrc,SDL_Rect rcSprite)
{
  square_ptr new_square = (square_ptr)malloc(sizeof(struct square));
  new_square->rcSrc = rcSrc;
  new_square->rcSprite = rcSprite;
}
