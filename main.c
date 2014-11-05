/*******************************************/
/* Decolle Anais - Peters Brice            */
/* main.c                                  */
/* It's the puzzle game.                   */
/*******************************************/

int WIDTH = 800;
int HEIGHT = 600;
#include "game.h"

/* main */
int main(int argc, char** argv)
{
  initSDL();
  int end,click,nb_pento,array_end = 0;
  FILE *file;
  int i,j;
  char array_file [1000];
  pentomino_ptr pento_array[20];
  area_ptr area = NULL;
  int pos_mouse_x,pos_mouse_y=0;
  SDL_Surface * array_color[12];
  SDL_Surface * background = NULL;
  SDL_Rect pos_background;
  SDL_Surface * square_sprite = NULL;

  // load the background and his position
  background = SDL_LoadBMP("background.bmp");
  pos_background.x = 0;
  pos_background.y = 0;

  square_sprite = SDL_LoadBMP("black.bmp");
  SDL_SetColorKey(square_sprite,SDL_RLEACCEL | SDL_SRCCOLORKEY,SDL_MapRGB(square_sprite->format,0,0,0));

  /* open the pentomino file */  
  file = fopen("pentomino.txt", "r");

  /* beginning of the file */
  rewind(file);

  /* end of the file */
  array_end = file_array(array_file,file);

  /* close the file */
  fclose(file);

 /* say the number of pentominos */
  nb_pento = nb_pent(array_file,array_end);
  area = init_area(array_file,450,400);
  tab_color(array_color);

  /* set the pentominos in an array */
  tab_pento (array_file,pento_array,array_end,array_color);

  /* draw the pentomino, the area and the background */
  draw_all (array_file,area,square_sprite,array_end,pento_array,background,pos_background);

  /* controls keyboard and mouse */
  while (end != 1){
    controls(nb_pento,&end,pento_array,&click,&pos_mouse_x,&pos_mouse_y,array_file,area);
    draw_all(array_file,area,square_sprite,array_end,pento_array,background,pos_background);
    if (final_test(array_file,pento_array,area,array_end)){
      end = 1;
    }
  }
  free_color(array_color);
  SDL_FreeSurface(background);
  return EXIT_SUCCESS;
}

