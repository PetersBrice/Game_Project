/*******************************************/
/* Decolle Anais - Peters Brice            */
/* main.c                                  */
/* It's the puzzle game.                   */
/*******************************************/

#include "pentomino.h"

SDL_Surface* background;
int WIDTH = 500;
int HEIGHT = 300;

void initSDL(void);


// initialization of SDL
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

// main
int main(int argc, char** argv)
{
  initSDL();
  SDL_Event event;
  int end = 0;

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

