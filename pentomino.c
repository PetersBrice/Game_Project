#include "pentomino.h"
#include <assert.h>
#define SIZE_SQUARE 30
int width = 800;
int height = 600;

pentomino_ptr new_pentomino(int position)
{
  int i,j;
  pentomino_ptr new_pent = (pentomino_ptr)malloc(sizeof(struct pentomino));
  for (i = 0;i <= 4;i++){
    for(j = 0;j <= 4;j++){
      new_pent->array_pent[i][j] = 'o';
    }
  }
  for (i=0; i<5; i++) {
    new_pent->square[i] = NULL;
  }
  new_pent->position = position;
  return new_pent;
}

void draw_pentomino(pentomino_ptr pentomino,SDL_Surface *background)
{
  int i ;
  for(i=0;i<5;i++){
    draw_square(pentomino->square[i],pentomino->square_sprite,background);
  }
}

int new_array(char array_file[1000],int pos_file,char array_pent[5][5]){
  int i,j,Nb_square=0;
  for(i=0;i<5;i++){
    for(j=0;j<5;j++){
      array_pent[i][j] = 'o';
    }
  }
  i = 0;
  j = 0;
  while(Nb_square<5){
    if (array_file[pos_file] =='\n'){
      i++;
      j = 0;
    }else if(array_file[pos_file] == '#'){
      array_pent[i][j] = '#';
      j++;
      Nb_square++;
    } else {
      j++;
    }
    pos_file++ ;
  }
  return pos_file+2;
}


void get_square(square_ptr square[5] ,char array_pent[5][5],int pos_x,int pos_y){
  int i,j,nb_square;
  nb_square = 0;
  SDL_Rect rcSrc,rcSprite;
  while (nb_square<5){
    for(i = 0;i < 5;i++){
      for(j = 0;j < 5;j++){
	if (array_pent[i][j] == '#'){
	  rcSrc.x = pos_x + j*SIZE_SQUARE;
	  rcSrc.y = pos_y + i*SIZE_SQUARE;
	  rcSprite.x = 0 ;
	  rcSprite.y = 0 ;
	  rcSprite.w = 30 ;
	  rcSprite.h = 30 ;
	  square[nb_square]= new_square(rcSrc,rcSprite);
	  nb_square++;
	}
      }
    }
  }
}

void tab_pento (char array_file[1000],pentomino_ptr pento_array[20], int array_end,SDL_Surface * array_color[12]){
  int nb_pento,i,pos_file,pos_pento;
  int j = 0;
  pos_pento = 50;
  nb_pento = nb_pent(array_file, array_end) ;
  pos_file = begin_pent(array_file);
  for(i=0;i<nb_pento;i++){
    pento_array[i] = new_pentomino(nb_pento) ;
    pos_file = new_array(array_file,pos_file,pento_array[i]->array_pent);
    get_square(pento_array[i]->square,pento_array[i]->array_pent,5,pos_pento);
    pos_pento =pos_pento+5*SIZE_SQUARE;
    if (pos_pento > height){
      pos_pento = 50 ;
    }
    if(j == 12){
      j = 0;
    }
    pento_array[i]->square_sprite = array_color[j];
    j++;
  }
} 
     

      
void draw_array(pentomino_ptr pento_array[20],char array_file[1000],int array_end ,SDL_Surface *background){
  int i,nb_pento;
  nb_pento = nb_pent(array_file,array_end);
    for (i = 0;i<nb_pento;i++){
      pento_array[i]->coat = i;
      draw_pentomino(pento_array[i],background);
    }
}

void free_pento (pentomino_ptr pentomino)
{
  free(pentomino->square_sprite);
  free(pentomino);
}
