#include "area.h"

area_ptr init_area (void)
{
  area_ptr area = (area_ptr) malloc (sizeof(struct area));
  area->pos_area.x = 0;
  area->pos_area.y = 0;
  area->nb_pent = 0;
  return area;
}

// return the array for the shape of the area
void array_area (area_ptr area, FILE *file)
{
  area->array_area[MAXW][MAXH];
  memset(*area->array_area,0,sizeof(area->array_area));
  char line [MAXW];
  line[0] = 2;
  int col,row = 0;
  rewind(file);
  while(line[0] != '\n' && row<MAXH){
    fgets(line, sizeof line, file);
    col = 0;
    while(line[col] != '\n'){
      if(line[col] == '#'){
	area->array_area[col][row] = 1;
	printf("tab 1 ; col=%d ; row=%d\n",col,row);
      }
      col++;
    }
    row++;    
  }
}

void draw_area (area_ptr area,SDL_Surface *background)
{
  int col,row = 0;
  int size_square = 30;
  SDL_Rect pos_square;
  pos_square.x = area->pos_area.x;
  pos_square.y = area->pos_area.y;
  SDL_Surface *square = SDL_CreateRGBSurface(SDL_HWSURFACE,size_square,size_square,32,0,0,0,0);
  SDL_FillRect(square,NULL,SDL_MapRGB(background->format,255,255,255));
  for(row=0;row<MAXH;row++){
    for(col=0;col<MAXW;col++){
      if(area->array_area[col][row] == 1){
	pos_square.x = area->pos_area.x + col * size_square;
	pos_square.y = area->pos_area.y + row * size_square;
        SDL_BlitSurface(square,NULL,background,&pos_square);
      }
    }
  }
  SDL_Flip(background);
  SDL_FreeSurface(square);
}
