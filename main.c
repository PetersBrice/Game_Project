/*******************************************/
/* Decolle Anais - Peters Brice            */
/* main.c                                  */
/* It's the puzzle game.                   */
/*******************************************/

#include "pentomino.h"
#include "area.h"

SDL_Surface *background;
int WIDTH = 800;
int HEIGHT = 600;

void initSDL(void);
void controls(int * end,struct pentomino ** pento_array,int *click,int * pos_mouse_x,int * pos_mouse_y);


/* initialization of SDL */
void initSDL(void)
{
  if (SDL_Init (SDL_INIT_VIDEO) < 0){
    fprintf(stderr, "Error initialization of SDL : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  atexit(SDL_Quit);

  // load of the background
  background = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);

  SDL_WM_SetCaption("PUZZLE", NULL);
}

/* controls */

void controls (int * end,struct pentomino ** pento_array, int *click, int * pos_mouse_x, int * pos_mouse_y)
{
  SDL_Event event;
  int i;
  SDL_WaitEvent(&event);
  switch (event.type){
    // click on the cross
    case SDL_QUIT:
      *end = 1;
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym){
	//button A for the mirror
      case SDLK_a:
	printf("A\n");
	break;
      }
      break;
      // press the left click of the mouse
    case SDL_MOUSEBUTTONDOWN:
      if (event.button.button == SDL_BUTTON_LEFT){
	*click = 1;
	*pos_mouse_x = event.button.x;
	*pos_mouse_y = event.button.y;
      }
      break;
      // loosen the left click of the mouse
    case SDL_MOUSEBUTTONUP:
      if (event.button.button == SDL_BUTTON_LEFT){
	*click = 0;
      }
      break;
    case SDL_MOUSEMOTION:
      // if the mouse moves and the left click is pressed
      if (*click == 1){
	// move the pentomino
	for (i=0;i<5;i++){ 
	  pento_array[0]->square[i]->rcSrc.x = pento_array[0]->square[i]->rcSrc.x + event.motion.x - *pos_mouse_x;
	  pento_array[0]->square[i]->rcSrc.y = pento_array[0]->square[i]->rcSrc.y + event.motion.y - *pos_mouse_y; 
	}
	*pos_mouse_x=event.button.x;
	*pos_mouse_y=event.button.y;
      }      
      break;
    }
}

/* main */
int main(int argc, char** argv)
{
  initSDL();
  int end,click = 0;
  FILE *file;
  char array_file [1000];
  int array_end = 0;
  SDL_Surface *square_sprite;
  pentomino_ptr pento_array[20];
  int pos_mouse_x,pos_mouse_y=0;


  /* open the pentomino file */  
  file = fopen("pentomino.txt", "r");
  /* beginning of the file */
  rewind(file);
  /* end of the file */
  array_end = file_array(array_file,file);
  /* close the file */
  fclose(file);

  /* set the pentominos in an array */
  tab_pento (array_file,pento_array,array_end);
  /* load the sprite and draw the pentominos */
  square_sprite = SDL_LoadBMP("smiley.bmp");
  draw_array(pento_array,array_file,array_end,square_sprite,background);
  SDL_Flip(background);
  
  /*area_ptr area = init_area();
  array_area(area,file);
  draw_area(area,background);*/

  /* controls keyboard and mouse */
  while (end!=1){
    controls(&end,pento_array,&click,&pos_mouse_x,&pos_mouse_y);
	SDL_FillRect(background,NULL,SDL_MapRGB(background->format,0,0,0));
	draw_array(pento_array,array_file,array_end,square_sprite,background);
	SDL_Flip(background);
  }
  return EXIT_SUCCESS;
}

