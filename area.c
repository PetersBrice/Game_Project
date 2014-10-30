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

void auto_set(char array_file[1000],pentomino_ptr pentomino,area_ptr area){
  int i,j,min_x,min_y,max_x,max_y,min_next_x,min_next_y,next_x,next_y,size;
  size = size_area(array_file);
  min_next_x = SIZE_SQUARE;
  min_next_y = SIZE_SQUARE;
  min_x = min_x_area(area,array_file);
  min_y = min_y_area(area,array_file);
  max_x = max_x_area(area,array_file);
  max_y = max_y_area(area,array_file);
  bool in_area = true;
  for(i = 0;i < 5;i++){
    if ((pentomino->square[i]->rcSrc.x >= max_x) || (pentomino->square[i]->rcSrc.y >= max_y) || (pentomino->square[i]->rcSrc.x <= min_x) || (pentomino->square[i]->rcSrc.y <= min_y)){
      in_area = false;
      printf("dedan\n");
    }
  }
  if (in_area == true){
    printf("dehors\n");
    for(i = 0;i < 5;i++){
      for(j = 0;j < size ;j++){
	if(fabs(pentomino->square[i]->rcSrc.x-area->square[j]->rcSrc.x)<min_next_x){
	  min_next_x = fabs(pentomino->square[i]->rcSrc.x-area->square[j]->rcSrc.x);
	  next_x = pentomino->square[i]->rcSrc.x-area->square[j]->rcSrc.x;
	}
	if(fabs(pentomino->square[i]->rcSrc.y-area->square[j]->rcSrc.y)<min_next_y){
	  min_next_y = fabs(pentomino->square[i]->rcSrc.y-area->square[j]->rcSrc.y);
	  next_y = pentomino->square[i]->rcSrc.y-area->square[j]->rcSrc.y;
	}
      }
    }
    printf("next_x %d\n",next_x);
    printf("pos_x %d\n",pentomino->square[0]->rcSrc.x);
    for (i = 0;i<5;i++){
      pentomino->square[i]->rcSrc.y = -next_y+pentomino->square[i]->rcSrc.y;
      pentomino->square[i]->rcSrc.x = -next_x+pentomino->square[i]->rcSrc.x;
    }
  }
}

bool final_test(char array_file[1000],pentomino_ptr pento_array[20],area_ptr area,int array_end){
  bool end = true;
  int i,j,size,nb_square,nb_pento;
  size = size_area(array_file);
  nb_pento = nb_pent(array_file,array_end);
  for(i = 0;i< size;i++){
    area->square[i]->set = false;
  }
  for(i = 0;i < size;i++){
    for(j = 0;j < nb_pento;j++){
      for(nb_square = 0;nb_square<5;nb_square++){
	if((area->square[i]->rcSrc.x == pento_array[j]->square[nb_square]->rcSrc.x) && (area->square[i]->rcSrc.y == pento_array[j]->square[nb_square]->rcSrc.y)){
	  area->square[i]-> set = true;
	}
      }
    }
  }
  for(i = 0;i < size;i++){
    if(area->square[i]->set == false){
      end = false;
    }
  }
  return end;
}
