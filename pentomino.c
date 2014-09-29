#include "pentomino.h"
#define SIZE_SQUARE 30

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
  int i;
  int min = 2000;
  int max = 0;
  for (i = 0;i < 5;i++){
    if (pentomino->square[i]->rcSrc.x<min){
      min = pentomino->square[i]->rcSrc.x;
    }
  }
  for (i = 0;i < 5;i++){
    if (pentomino->square[i]->rcSrc.x == min){
      pentomino->square[i]->rcSrc.x = pentomino->square[i]->rcSrc.x + SIZE_SQUARE *4;
    }
    if (pentomino->square[i]->rcSrc.x == min + SIZE_SQUARE){
      pentomino->square[i]->rcSrc.x = pentomino->square[i]->rcSrc.x + SIZE_SQUARE * 2;
    }
    if (pentomino->square[i]->rcSrc.x == min + 3 * SIZE_SQUARE){
      pentomino->square[i]->rcSrc.x = pentomino->square[i]->rcSrc.x - SIZE_SQUARE * 2; 
    }
    if (pentomino->square[i]->rcSrc.x == min + 4 * SIZE_SQUARE){
      pentomino->square[i]->rcSrc.x = pentomino->square[i]->rcSrc.x - SIZE_SQUARE * 4; 
    }      
  }
  return pentomino;
}

pentomino_ptr create(pentomino_ptr pentomino,int x,int y){
  int i = 0;
  int j = 0;
  int nb_square = 0;
  while (nb_square < 5){
    for(i = 0;i < 5;i++){
      for (j = 0 ; j < 5 ;j++){
	if (pentomino->array_pent[i][j] == "#"){
	  pentomino->square[nb_square]->rcSrc.x=x+j*SIZE_SQUARE;
	  pentomino->square[nb_square]->rcSrc.y=y+i*SIZE_SQUARE;
	  nb_square++;
	}
      }
    }
  }
  return pentomino;
}
	  
	  
