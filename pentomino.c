#include "pentomino.h"

pentomino_ptr new_pentomino(char array_pent[5][5],int position,square_ptr square)
{
  int i,j;
  pentomino_ptr new_pent = (pentomino_ptr)malloc(sizeof(struct pentomino));
  for (i = 0;i < 4;i++){
    for(j = 0;j < 4;j++){
      new_pent->array_pent[i][j] = array_pent[i][j];
    }
  }
  new_pent->position = position;
  return new_pent;
}

pentomino_ptr mirror(pentomino_ptr pentomino){
  int i,j;
  for (i = 0;i < 3;i++){
    for (j = 0;j < 3;j++){
      pentomino->array_pent[i][j]=pentomino->array_pent[i][j-1];
    }
  }
  return pentomino;
}
