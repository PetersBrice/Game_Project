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
  end = 0;
  FILE *file;
  int i,j;
  char array_file [1000];
  pentomino_ptr pento_array[20];
  area_ptr area = NULL;
  int pos_mouse_x,pos_mouse_y=0;
  SDL_Surface * array_color[14];
  SDL_Surface * background = NULL;
  SDL_Surface * text_controls = NULL;
  SDL_Rect pos_background;
  SDL_Rect pos_text_controls;

  // load the text for the controls and his position
  text_controls =  write_controls();
  pos_text_controls.x = 10;
  pos_text_controls.y = 10;

  // load the background and his position
  background = SDL_LoadBMP("background.bmp");
  pos_background.x = 0;
  pos_background.y = 0;

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
  /* load the sprites */
  tab_color(array_color);
  /* create the area */
  area = init_area(array_file,230,100,array_color);
  /* set the pentominos in an array */
  tab_pento (array_file,pento_array,array_end,array_color);

  /* draw the pentomino, the area and the background */
  draw_all (array_file,area,area->square_sprite,array_end,pento_array,background,pos_background,text_controls,pos_text_controls);

  while (end != 1){
    /* wait an action of the player */
    controls(nb_pento,&end,pento_array,&click,&pos_mouse_x,&pos_mouse_y,array_file,area,array_end);
    /* update the screen */
    draw_all(array_file,area,area->square_sprite,array_end,pento_array,background,pos_background,text_controls,pos_text_controls);
    /* end of the game */
    if (final_test(array_file,pento_array,area,array_end)){
      end = 1;
    }
  }
  /* free all */
  free_color(array_color);
  free_all(area,pento_array,array_file,array_end);
  SDL_FreeSurface(background);
  return EXIT_SUCCESS;
}

