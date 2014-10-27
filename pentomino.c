#include "pentomino.h"
#include <assert.h>
#define SIZE_SQUARE 30

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

void draw_pentomino(pentomino_ptr pentomino,SDL_Surface *square_sprite,SDL_Surface *background)
{
  int i ;
  for(i=0;i<5;i++){
    draw_square(pentomino->square[i],square_sprite,background);
   
  }
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

	
int file_array(char array_file[1000],FILE *file) {
  int i = -1;
  while(!feof(file) && i++<1000) {
    array_file[i] = (char)fgetc(file);
  }
  return i;
}

int begin_pent (char array_file[1000]){
  bool start = false;
  int i = 0;
  while(!start && i<1000){
    if(array_file[i] == '\n' && array_file[i+1] == '\n'){
      start = true;
    }
    i++;
  }
  return i+1;
}

int nb_pent(char array_file[1000], int array_end) {
  int nb_square,i;
  nb_square = 0;
  i = begin_pent(array_file);
  for (;i<array_end; i++) {
    if (array_file[i]=='#') {
       nb_square++;
    }
  }
  assert((nb_square/5)*5 == nb_square);
  return nb_square/5;
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

bool test_pento(char array_file[1000], int array_end){
  int area = size_area(array_file);
  int nb_pento = nb_pent(array_file, array_end);
  return area % nb_pento == 0;

}

/*maybe move it to area.c*/

int size_area(char array_file[1000]){
  bool end = false;
  int area_size,i;
  i = 0;
  area_size = 0;
  while (!end){
    if(array_file[i] == '\n' && array_file[i+1]=='\n'){
      end=true;
    }else if (array_file[i] == '#'){
      area_size ++;
    }
    i++;
  }
  return area_size;
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

void tab_pento (char array_file[1000],pentomino_ptr pento_array[20], int array_end){
  int nb_pento,i,j,k,pos_file;
  nb_pento = nb_pent(array_file, array_end) ;
  pos_file = begin_pent(array_file);
  for(i=0;i<nb_pento;i++){
    pento_array[i] = new_pentomino(nb_pento) ;
    pos_file = new_array(array_file,pos_file,pento_array[i]->array_pent);
    get_square(pento_array[i]->square,pento_array[i]->array_pent,5,5+i*5*SIZE_SQUARE);
  }
} 
     
void get_area(char array_file[1000],char shape[10][10]){
  int size,i,j,nb_square,pos_file;
  nb_square=0;
  size = size_area(array_file);
  for(i = 0;i<10;i++){
    for(j = 0;j<10;j++){
      shape[i][j] = 'o';
    }
  }
  i = 0;
  j = 0;
  pos_file = 0;
  while(nb_square<size){
    if (array_file[pos_file] == '#'){
      shape[i][j] = '#';
      i++;
      nb_square++;
    }else if(array_file[pos_file] == ' '){
      i++;
    }else{
      i = 0;
      j++;
    }
    pos_file++;
  }
}
      
void draw_array(pentomino_ptr pento_array[20],char array_file[1000],int array_end ,SDL_Surface *square_sprite,SDL_Surface *background){
  int i,nb_pento;
  nb_pento = nb_pent(array_file,array_end);
    for (i = 0;i<nb_pento;i++){
      draw_pentomino(pento_array[i],square_sprite,background);
    }
}
