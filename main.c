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
  /* open the pentomino file */
  /* HERE test.txt NOT pentomino.txt*/
  int pos_mouse_x,pos_mouse_y=0;
  SDL_Surface * array_color[12];
  SDL_Surface * square_sprite;
  square_sprite = NULL ;

  square_sprite = SDL_LoadBMP("smiley.bmp");
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
  /* draw the pentominos and the area */
  draw_area (array_file,area,square_sprite,background);
  draw_array(pento_array,array_file,array_end,background);
  SDL_Flip(background);
  //test
  /*mirror(pento_array[0]);
  mirror(pento_array[1]);
  mirror(pento_array[2]);
  mirror(pento_array[3]);
  turn_pent(pento_array[0]);
  turn_pent(pento_array[1]);
  turn_pent(pento_array[2]);
  turn_pent(pento_array[3]);*/
  
 

  /* controls keyboard and mouse */
  while (end!=1){
    controls(nb_pento,&end,pento_array,&click,&pos_mouse_x,&pos_mouse_y,array_file,array_end,area,square_sprite);
    if (final_test(array_file,pento_array,area,array_end)==true){
      printf("go\n");
      end = 1;
    }
  }
  return EXIT_SUCCESS;
}

