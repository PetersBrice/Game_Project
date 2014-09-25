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
  background = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);

  SDL_WM_SetCaption("PUZZLE", NULL);
}

/* controls */


/* draw the shape in test.txt */
void draw_txt (FILE *file)
{
  char line [20];
  int i;
  int size_square = 50;
  SDL_Rect position;
  SDL_Surface *square = NULL;
  fgets(line, sizeof line, file);
  position.x = 0;
  position.y = 0;
  while (line[0] != '\n' && line[0] != EOF){
    i = 0;
    while (line[i] != '\n'){
      if (line[i] == '#'){
	// load the sqaure with the dimensions and the color
	square = SDL_CreateRGBSurface(SDL_HWSURFACE, size_square, size_square, 32, 0, 0, 0, 0);
	SDL_FillRect(square, NULL, SDL_MapRGB(background->format, 255, 255, 255));
	// draw the square and update the screen
	SDL_BlitSurface(square, NULL, background, &position);
	SDL_Flip(background);
	SDL_FreeSurface(square);
      }
      position.x = position.x + size_square;
      i++;
    }
    position.x = 0;
    position.y = position.y + size_square;
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

  /* open the pentomino file */
  /* HERE test.txt NOT pentomino.txt*/
  file = fopen("test.txt", "r");

  /* draw the shape in the file */
  draw_txt(file);

  /* close the file */
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

