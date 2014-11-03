#include "area.h"
#define SIZE_SQUARE 30 

area_ptr init_area (char array_file[1000],int pos_x,int pos_y)
{
  area_ptr area = (area_ptr) malloc (sizeof(struct area));
  get_area(array_file,area->shape);
  get_square_area(array_file,area->shape,area->square,pos_x,pos_y);
  return area;
}



void draw_area(char array_file[1000],area_ptr area,SDL_Surface *square_sprite,SDL_Surface *background)
{
  int i,size ;
  size = size_area(array_file);
  for(i=0;i<size;i++){
    draw_square(area->square[i],square_sprite,background);
   
  }
}

void get_area(char array_file[1000],char shape[15][15]){
  int size,i,j,nb_square,pos_file;
  nb_square=0;
  size = size_area(array_file);
  for(i = 0;i<15;i++){
    for(j = 0;j<15;j++){
      shape[i][j] = 'o';
    }
  }
  i = 0;
  j = 0;
  pos_file = 0;
  while(nb_square<size){
    if (array_file[pos_file] == '#'){
      shape[i][j] = '#';
      j++;
      nb_square++;
    }else if(array_file[pos_file] == ' '){
      j++;
    }else{
      j = 0;
      i++;
    }
    pos_file++;
  }
}

void get_square_area(char array_file[1000],char array_area[15][15],square_ptr square[225],int pos_x,int pos_y){
  int i,j,nb_square,size;
  nb_square = 0;
  size = size_area(array_file);
  SDL_Rect rcSrc,rcSprite;
  while (nb_square<size){
    for(i = 0;i < 15;i++){
      for(j = 0;j < 15;j++){
	if (array_area[i][j] == '#'){
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

int max_x_area(area_ptr area,char array_file[1000]){
  int i,max,size;
  max = 0;
  size = size_area(array_file);
  for(i = 0;i < size;i++){
    if(area->square[i]->rcSrc.x>max){
      max = area->square[i]->rcSrc.x;
    }
  }
  return max + SIZE_SQUARE;
}

int max_y_area(area_ptr area,char array_file[1000]){
  int i,max,size;
  max = 0;
  size = size_area(array_file);
  for(i = 0;i < size;i++){
    if(area->square[i]->rcSrc.y>max){
      max = area->square[i]->rcSrc.y;
    }
  }
  return max + SIZE_SQUARE;
}

int min_x_area(area_ptr area,char array_file[1000]){
  int i,min,size;
  min = max_x_area(area,array_file);
  size = size_area(array_file);
  for(i = 0;i < size;i++){
    if(area->square[i]->rcSrc.x<min){
      min = area->square[i]->rcSrc.x;
    }
  }
  return min;
}

int min_y_area(area_ptr area,char array_file[1000]){
  int i,min,size;
  min = max_y_area(area,array_file);
  size = size_area(array_file);
  for(i = 0;i < size;i++){
    if(area->square[i]->rcSrc.y<min){
      min = area->square[i]->rcSrc.y;
    }
  }
  return min;
}


