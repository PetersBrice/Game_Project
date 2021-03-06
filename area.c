#include "area.h"
#define SIZE_SQUARE 30 

/* create the area */
area_ptr init_area (char array_file[1000],int pos_x,int pos_y,SDL_Surface * array_color [14])
{
  area_ptr area = (area_ptr) malloc (sizeof(struct area));
  get_area(array_file,area->shape);
  get_square_area(array_file,area->shape,area->square,pos_x,pos_y);
  area->square_sprite = array_color[12];
  SDL_SetAlpha(area->square_sprite, SDL_SRCALPHA | SDL_RLEACCEL, 120 );
  area->contour_sprite = array_color[13];
  SDL_SetColorKey(area->contour_sprite,SDL_RLEACCEL | SDL_SRCCOLORKEY,SDL_MapRGB(area->contour_sprite->format,0,0,0));
  return area;
}

/* draw the area */
void draw_area(char array_file[1000],area_ptr area,SDL_Surface *square_sprite,SDL_Surface *screen)
{
  int i,size ;
  size = size_area(array_file);
  for(i=0;i<size;i++){
    draw_square(area->square[i],area->square_sprite,screen);
    draw_square(area->square[i],area->contour_sprite,screen);
  }
}

/*get the shape of the area*/
void get_area(char array_file[1000],char shape[15][15])
{
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

/*get the square of the area*/
void get_square_area(char array_file[1000],char array_area[15][15],square_ptr square[225],int pos_x,int pos_y)
{
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

/*get the highest x in of the area*/
int max_x_area(area_ptr area,char array_file[1000])
{
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

/*get the highest y in the area*/
int max_y_area(area_ptr area,char array_file[1000])
{
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

/*get the smallest x of the area*/
int min_x_area(area_ptr area,char array_file[1000])
{
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

/*get the smallest y of the area*/
int min_y_area(area_ptr area,char array_file[1000])
{
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

/*free the area*/
void free_area(area_ptr area,char array_file[1000])
{
  int size,i;
  size = size_area(array_file);
  for(i = 0;i < size;i++){
    free_square(area->square[i]);
  }
  SDL_FreeSurface(area->square_sprite);
  SDL_FreeSurface(area->contour_sprite);
  free(area);
}

