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
  int end,click,nb_pento,array_end,i,j;
  end = 0;
  FILE *file;
  int timer = 0;
  char array_file [1000];
  pentomino_ptr pento_array[20];
  area_ptr area = NULL;
  int pos_mouse_x = 0;
  int pos_mouse_y = 0;
  SDL_Surface * array_color[14];
  SDL_Surface * background = NULL;
  SDL_Surface * text_controls = NULL;
  SDL_Rect pos_background;
  SDL_Rect pos_text_controls;
  SDL_Color color = {0,0,0,0};
  char sec [2] = "";
  char mn [2] = "";
  char hr [2] = "";
  int seconds = 0;
  int minutes = 0;
  int hours = 0;
  TTF_Font * police = TTF_OpenFont("CaviarDreams_Bold.ttf",16);
  SDL_Rect pos_time_h_m_s;
  pos_time_h_m_s.x = 685;
  pos_time_h_m_s.y = 5;
  SDL_Rect pos_time_s;
  pos_time_s.x = 750;
  pos_time_s.y = 5;
  SDL_Rect pos_time_m;
  pos_time_m.x = 700;
  pos_time_m.y = 5;
  SDL_Rect pos_time_h;
  pos_time_h.x = 660;
  pos_time_h.y = 5;
  SDL_Rect pos_time_inf;
  pos_time_inf.x = 740;
  pos_time_inf.y = 5;

  // load the text for the controls and his position
  text_controls =  write_controls(color);
  pos_text_controls.x = 10;
  pos_text_controls.y = 4;

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
  draw_all (array_file,area,area->square_sprite,array_end,pento_array,background,pos_background,text_controls,pos_text_controls,timer,&seconds,&minutes,&hours,sec,mn,hr,police,color,pos_time_h_m_s,pos_time_s,pos_time_m,pos_time_h,pos_time_inf);

  while (end != 1){
    /* update the timer */
    timer = SDL_GetTicks();
    /* wait an action of the player */
    controls(nb_pento,&end,pento_array,&click,&pos_mouse_x,&pos_mouse_y,array_file,area,array_end);
    /* update the screen */
    draw_all(array_file,area,area->square_sprite,array_end,pento_array,background,pos_background,text_controls,pos_text_controls,timer,&seconds,&minutes,&hours,sec,mn,hr,police,color,pos_time_h_m_s,pos_time_s,pos_time_m,pos_time_h,pos_time_inf);
    /* end of the game */
    if (final_test(array_file,pento_array,area,array_end)){
      pos_time_h_m_s.x = 350;
      pos_time_h_m_s.y = 150;
      pos_time_s.x = 415;
      pos_time_s.y = 150;
      pos_time_m.x = 365;
      pos_time_m.y = 150;
      pos_time_h.x = 325;
      pos_time_h.y = 150;
      pos_time_inf.x = 405;
      pos_time_inf.y = 150;
      draw_end_screen (background,pos_background,timer,&seconds,&minutes,&hours,sec,mn,hr,police,color,pos_time_h_m_s,pos_time_s,pos_time_m,pos_time_h,pos_time_inf);
      SDL_Delay(3000);
      end = 1;
      }
  }

  /* free all */
  free_color(array_color);
  free_all(area,pento_array,array_file,array_end);
  SDL_FreeSurface(text_controls);
  SDL_FreeSurface(background);
  TTF_CloseFont(police);
  return EXIT_SUCCESS;
}

