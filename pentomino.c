#include "pentomino.h"

pentomino_ptr new_pentomino(char array_pent[5][5],double angle,SDL_Rect rcSrc,SDL_Rect rcSprite)
{
  int i,j;
  pentomino_ptr new_pent = (pentomino_ptr)malloc(sizeof(struct pentomino));
  for (i = 0;i < 4;i++){
    for(j = 0;j < 4;j++){
      new_pent->array_pent[i][j] = array_pent[i][j];
    }
  }
  new_pent->angle = angle;
  new_pent->rcSrc = rcSrc;
  new_pent->rcSprite = rcSprite;
  return new_pent;
}

pentomino_ptr mirror(pentomino_ptr pentomino){
}
