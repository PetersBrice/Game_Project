/*******************************************/
/* Decolle Anais - Peters Brice            */
/* main.c                                  */
/* It's the puzzle game.                   */
/*******************************************/

#include "pentomino.h"
#include "area.h"

SDL_Surface* background;
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
  SDL_Surface *square_sprite;
  pentomino_ptr pentomino;
 
  square_sprite = NULL ;
  /* open the pentomino file */
  /* HERE test.txt NOT pentomino.txt*/
  file = fopen("test.txt", "r");
  rewind(file);
  /* draw the shape in the file */
  //draw_txt(file);

  /* create a pentomino */
  
  //pentomino = create(10,10,file);
  /*
  square_sprite = SDL_LoadBMP("smiley.bmp");
  draw_pentomino(pentomino, square_sprite, background);
  SDL_Flip(background);
  */

  pentomino = shape(10, 10, file);
  square_sprite = SDL_LoadBMP("smiley.bmp");
  draw_pentomino(pentomino, square_sprite, background);
  SDL_Flip(background);
  


  area_ptr area = init_area();
  array_area(area,file);
  draw_area(area,background);

  /* close the file */
  fclose(file);

  /* controls keyboard and mouse */
  while (end!=1){
    end=controls();
    if (controls() == 2){
      pentomino = mirror(pentomino);
      draw_pentomino(pentomino, square_sprite, background);
      SDL_Flip(background);
    }


  }



  return EXIT_SUCCESS;
}

