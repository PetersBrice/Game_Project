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
void draw_txt (FILE *file);
int controls(void);


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

int controls (void)
{
  SDL_Event event;
    SDL_WaitEvent(&event);
    switch (event.type){
      // click on the cross
    case SDL_QUIT:
      return 1;
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym){

      case SDLK_a:
	printf("A\n");
	return 2;
	break;
      }
      break;
      // left click of the mouse
    case SDL_MOUSEBUTTONUP:
      if (event.button.button == SDL_BUTTON_LEFT){
	//position_mouse.x = event.button.x;
	//position_mouse.y = event.button.y;
      }
    case SDL_MOUSEMOTION:
      //position_square.x = event.motion.x;
      //position_square.y = event.motion.y;
      break;
    }
    SDL_Flip(background);
    return 0;
}



/* draw the shape in test.txt */
void draw_txt (FILE *file)
{
  char line [20];
  int i;
  int size_square = 50;
  SDL_Rect position_square;
  SDL_Surface *square = NULL;
  fgets(line, sizeof line, file);
  position_square.x = 0;
  position_square.y = 0;
  while (line[0] != '\n' && line[0] != EOF){
    i = 0;
    while (line[i] != '\n'){
      if (line[i] == '#'){
	// load the square with the dimensions and the color
	square = SDL_CreateRGBSurface(SDL_HWSURFACE, size_square, size_square, 32, 0, 0, 0, 0);
	SDL_FillRect(square, NULL, SDL_MapRGB(background->format, 255, 255, 255));
	// draw the square and update the screen
	SDL_BlitSurface(square, NULL, background, &position_square);
	SDL_Flip(background);
	SDL_FreeSurface(square);
      }
      position_square.x = position_square.x + size_square;
      i++;
    }
    position_square.x = 0;
    position_square.y = position_square.y + size_square;
    fgets(line, sizeof line, file);
  }
}

/* main */
int main(int argc, char** argv)
{
  initSDL();
  //SDL_Event event;
  int end = 0;
  FILE *file;
  int i,j;
  char array_file [1000];
  int array_end = 0;
  SDL_Surface *square_sprite;
  pentomino_ptr pento_array[20];
  area_ptr area = NULL; 
  square_sprite = NULL ;
  /* open the pentomino file */
  /* HERE test.txt NOT pentomino.txt*/
  file = fopen("pentomino.txt", "r");
  rewind(file);
  array_end = file_array(array_file,file);
  /* close the file */
  fclose(file);
  tab_pento (array_file,pento_array, array_end);
  area = init_area(array_file,0,0);
  //printf("END\n");
  square_sprite = SDL_LoadBMP("smiley.bmp");
  printf("x %d \n",pento_array[2]->square[0]->rcSrc.x);
  /*mirror(pento_array[0]);
  mirror(pento_array[1]);
  mirror(pento_array[2]);
  mirror(pento_array[3]);
  turn_pent(pento_array[0]);
  turn_pent(pento_array[1]);
  turn_pent(pento_array[2]);
  turn_pent(pento_array[3]);*/
  printf("x %d \n",pento_array[2]->square[0]->rcSrc.x);
  draw_array(pento_array,array_file,array_end,square_sprite,background);
  //draw_area (array_file,area,square_sprite,background);
  SDL_Flip(background);

  


  /*area_ptr area = init_area();
  array_area(area,file);
  draw_area(area,background);*/

  /* controls keyboard and mouse */
  while (end!=1){
    end=controls();
    if (controls() == 2){
      //pentomino = mirror(pentomino);
      //draw_pentomino(pentomino, square_sprite, background);
      SDL_Flip(background);
    }
  }
  return EXIT_SUCCESS;
}

