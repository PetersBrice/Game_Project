/*******************************************/
/* Decolle Anais - Peters Brice            */
/* main.c                                  */
/* It's the puzzle game.                   */
/*******************************************/

#include "pentomino.h"

SDL_Surface* background;
int WIDTH = 800;
int HEIGHT = 600;

void initSDL(void);
void draw_txt (FILE *file);


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
/*
void controls ()
{
  while (!end){
    SDL_WaitEvent(&event);
    switch (event.type){
      // click on the cross
    case SDL_QUIT:
      end = 1;
      break;
      // left click of the mouse
    case SDL_MOUSEBUTTONUP:
      if (event.button.button == SDL_BUTTON_LEFT){
	position_mouse.x = event.button.x;
	position_mouse.y = event.button.y;
      }
    case SDL_MOUSEMOTION:
      position_square.x = event.motion.x;
      position_square.y = event.motion.y;
      break;
    }
    SDL_Flip(background);
  }
}
*/


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
  SDL_Event event;
  int end = 0;
  FILE *file;
  SDL_Rect position_mouse, position_smiley;
  SDL_Surface *smiley,*square_sprite;
  pentomino_ptr pentomino;
 
  square_sprite = NULL ;
  /* open the pentomino file */
  /* HERE test.txt NOT pentomino.txt*/
  file = fopen("test.txt", "r");

  /* draw the shape in the file */
  //draw_txt(file);

  /* create a pentomino */
  pentomino = create(10, 10, file);
  square_sprite = SDL_LoadBMP("smiley.bmp");
  draw_pentomino(pentomino, square_sprite, background);
  SDL_Flip(background);

  /* close the file */
  fclose(file);

  /* draw a smiley (to test movements) */
  /*
  smiley = SDL_LoadBMP("smiley.bmp");
  square_sprite = SDL_LoadBMP("smiley.bmp");
  position_smiley.x = 500;
  position_smiley.y = 300;
  SDL_FillRect(background, NULL, SDL_MapRGB(background->format, 0, 0, 0));
  SDL_BlitSurface(smiley, NULL, background, &position_smiley);
  SDL_Flip(background);
  */

  /* controls keyboard and mouse */
  while (!end){
    SDL_WaitEvent(&event);
    
    switch (event.type){
      // click on the cross
    case SDL_QUIT:
      end = 1;
      break;
      // left click of the mouse
    case SDL_MOUSEBUTTONUP:
      if (event.button.button == SDL_BUTTON_LEFT){
	position_mouse.x = event.button.x;
	position_mouse.y = event.button.y;
      }
    case SDL_MOUSEMOTION:
      //position_smiley.x = event.motion.x;
      //position_smiley.y = event.motion.y;
      break;
    }
    //SDL_FillRect(background, NULL, SDL_MapRGB(background->format, 255, 255, 255));
    //SDL_BlitSurface(smiley, NULL, background, &position_smiley);
    //SDL_Flip(background);
  }


  //SDL_FreeSurface(smiley);


  return EXIT_SUCCESS;
}

