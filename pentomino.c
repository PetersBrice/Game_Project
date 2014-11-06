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

void draw_pentomino(pentomino_ptr pentomino,SDL_Surface *screen)
{
  int i ;
  for(i=0;i<5;i++){
    draw_square(pentomino->square[i],pentomino->square_sprite,screen);
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

void tab_pento (char array_file[1000],pentomino_ptr pento_array[20], int array_end,SDL_Surface * array_color[14]){
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
     

      
void draw_array(pentomino_ptr pento_array[20],char array_file[1000],int array_end ,SDL_Surface *screen){
  int i,nb_pento;
  nb_pento = nb_pent(array_file,array_end);
    for (i = 0;i<nb_pento;i++){
      pento_array[i]->coat = i;
      draw_pentomino(pento_array[i],screen);
    }
}



int pos_x_array(pentomino_ptr pent){
  int i,j,pos_x,pos_y;
  bool find;
  pos_x = 10000;
  pos_y = min_y_pent(pent);
  for (i = 0;i < 5;i++){
    if(pent->square[i]->rcSrc.y == pos_y && pent->square[i]->rcSrc.x < pos_x){
      printf("oui\n");
      pos_x = pent->square[i]->rcSrc.x ;
    }
  }
  i = 0;
  j = 0;
  while (i < 5 && j < 5 && find == false){
    if (pent->array_pent[i][j] == '#'){
      find = true ;
    }
    if (!find){
      j++;
      if (j == 5){
	i++;
	j = 0;
      }
    }
  }
  pos_x = pos_x - j * SIZE_SQUARE;
  return pos_x;
}

int pos_y_array(pentomino_ptr pent){
  int i,j,pos_y;
  bool find;
  i = 0;
  j = 0;
  pos_y = min_y_pent(pent);
  while (i < 5 && j < 5 && find == false){
    if (pent->array_pent[i][j] == '#'){
      find = true ;
    }
    if (!find){
      j++;
      if (j == 5){
	i++;
	j = 0;
      }
    }
  }
  pos_y = pos_y - i * SIZE_SQUARE;
  return pos_y;
}

int min_x_pent(pentomino_ptr pent){
  int i;
  int min_x = 10000;
  for(i = 0 ; i < 5 ; i++){
    printf("min_x %d\n",min_x);
    printf("x %d\n",pent->square[i]->rcSrc.x);
    if (pent->square[i]->rcSrc.x < min_x){
      printf("oui\n");
      min_x = pent->square[i]->rcSrc.x ;
    }
  }
  return min_x;
}

int min_y_pent(pentomino_ptr pent){
  int i;
  int min_y = 10000;
  for(i = 0 ; i < 5 ; i++){
    if (pent->square[i]->rcSrc.y < min_y){
      min_y = pent->square[i]->rcSrc.y ;
    }
  }
  return min_y;
}

void free_pentomino(pentomino_ptr pentomino){
  int i;
  for(i = 0 ;i < 5;i ++){
    free_square(pentomino->square[i]);
  }
  free(pentomino);
}

void free_pento_array(pentomino_ptr pento_array[20],char array_file[1000],int array_end){
  int i,nb_pento;
  nb_pento = nb_pent(array_file,array_end); 
  for(i = 0;i<nb_pento;i++){
    free_pentomino(pento_array[i]);
  }
}
