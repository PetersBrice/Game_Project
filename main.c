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
void draw_framework (FILE *file);


/* initialization of SDL */
void initSDL(void)
{
  if (SDL_Init (SDL_INIT_VIDEO) < 0){
    fprintf(stderr, "Error initialization of SDL : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  atexit(SDL_Quit);

  // load of the background
  background = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);

  SDL_WM_SetCaption("PUZZLE", NULL);
}

/* controls */


/* draw the framework */
void draw_framework (FILE *file)
{
  int col,lines = 0;
  // maximum number of caracters in a line
  int max_carac = 30;
  char line [max_carac];
  SDL_Surface *framework = NULL;
  SDL_Rect position;

  rewind(file);
  // count the number of columns
  while (fgetc(file) != '\n'){
    col++;
  }
  col--;
  // count the number of lines
  rewind(file);
  fgets(line, max_carac, file);
  while (line[1] != '\n'){
    lines++;
    fgets(line, max_carac, file);
  }
  printf("%d col et %d lines\n", col, lines);

  // load the framework with the dimensions and the color
  framework = SDL_CreateRGBSurface(SDL_HWSURFACE, 50*col, 50*lines, 32, 0, 0, 0, 0);
  SDL_FillRect(framework, NULL, SDL_MapRGB(background->format, 255, 255, 255));
  // position of the framework
  position.x = 200;
  position.y = 100; 
  // draw the framework and update the screen
  SDL_BlitSurface(framework, NULL, background, &position);
  SDL_Flip(background);

  SDL_FreeSurface(framework);
}

/* main */
int main(int argc, char** argv)
{
  initSDL();
  SDL_Event event;
  int end = 0;
  FILE *file;

  /* open the pentomino file */
  file = fopen("pentomino.txt", "r");
  /* draw the framework */
  draw_framework(file);
  /* close the pentomino file */
  fclose(file);

  /* controls keyboard and mouse */
  while (!end){
    SDL_WaitEvent(&event);
    switch (event.type){
    case SDL_QUIT:
      end = 1;
      break;
    }
  }


  return EXIT_SUCCESS;
}

