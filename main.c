/*******************************************/
/* Decolle Anais - Peters Brice            */
/* main.c                                  */
/* It's the puzzle game.                   */
/*******************************************/

#include "pentamino.h"

SDL_Surface* background;
int WIDTH = 500;
int HEIGHT = 300;

void initSDL(void);
void wait_event (void);

// initialization of SDL
void initSDL(void)
{
  if (SDL_Init (SDL_INIT_VIDEO) < 0){
    fprintf(stderr, "Error initialization of SDL : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  atexit(SDL_Quit);
  background = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);

  if (background == NULL){
    fprintf(stderr, "Error grafic mode SDL : %s\n", SDL_GetError);
    exit(EXIT_FAILURE);
  }

  SDL_WM_SetCaption("PUZZLE", NULL);
}

// wait an event with the mouse of the keyboard
void wait_event(void)
{
  SDL_Event event;

do
  SDL_WaitEvent(&event);
 while(event.type != SDL_QUIT && event.type != SDL_KEYDOWN);
}

// main
int main(int argc, char** argv)
{
  initSDL();
  wait_event();
  return EXIT_SUCCESS;
}

