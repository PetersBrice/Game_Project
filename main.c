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
void controls(int nb_pento,int * end,pentomino_ptr pento_array[20], int *click, int * pos_mouse_x, int * pos_mouse_y,char array_file[1000],int array_end,area_ptr area,SDL_Surface * square_sprite);
void move (int selected,pentomino_ptr pento_array[20],int * pos_mouse_x,int * pos_mouse_y,char array_file [1000],int array_end,SDL_Event event,area_ptr area,SDL_Surface * square_sprite);
int select_pento (int nb_pento,struct pentomino ** pento_array,int pos_mouse_x, int pos_mouse_y);
void update_coat (struct pentomino ** pento_array,int selected,int nb_pento);


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
void controls (int nb_pento,int * end,pentomino_ptr pento_array[20], int *click, int * pos_mouse_x, int * pos_mouse_y,char array_file[1000],int array_end,area_ptr area,SDL_Surface * square_sprite)
{
  SDL_Event event;
  int i;
  int selected;
  SDL_WaitEvent(&event);
  switch (event.type){
    // click on the cross
    case SDL_QUIT:
      *end = 1;
      break;
      // press the left click of the mouse
    case SDL_MOUSEBUTTONDOWN:
      if (event.button.button == SDL_BUTTON_LEFT){
	*click = 1;
	*pos_mouse_x = event.button.x;
	*pos_mouse_y = event.button.y;
	selected = select_pento (nb_pento,pento_array,*pos_mouse_x,*pos_mouse_y);
	// put the pentomino selected on the first coat
	if (selected != -1)
	  update_coat(pento_array,selected,nb_pento);
      }
      break;
      // loosen the left click of the mouse
    case SDL_MOUSEBUTTONUP:
      if (event.button.button == SDL_BUTTON_LEFT)
	*click = 0;
      selected = select_pento (nb_pento,pento_array,*pos_mouse_x,*pos_mouse_y);
      if(selected != -1){
	auto_set(array_file,pento_array[selected],area);
	SDL_FillRect(background,NULL,SDL_MapRGB(background->format,0,0,0));
	draw_area (array_file,area,square_sprite,background);
	draw_array(pento_array,array_file,array_end,background);
	SDL_Flip(background);
      }
      break;
    case SDL_MOUSEMOTION:
      // if the mouse moves and the left click is pressed
      if (*click == 1){
	selected = select_pento (nb_pento,pento_array,*pos_mouse_x,*pos_mouse_y);
	// if click on a pentomino
	if (selected != -1){
	  // move the pentomino
	  move (selected,pento_array,pos_mouse_x,pos_mouse_y,array_file,array_end,event,area,square_sprite);
	}
      }      
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym){
	//button A for the mirror
      case SDLK_a:
	selected = select_pento (nb_pento,pento_array,*pos_mouse_x,*pos_mouse_y);
	// mirror and draw
	if(selected != -1){
	  mirror(pento_array[selected]);
	  SDL_FillRect(background,NULL,SDL_MapRGB(background->format,0,0,0));
	  draw_area (array_file,area,square_sprite,background);
	  draw_array(pento_array,array_file,array_end,background);
	  SDL_Flip(background);
	}
	break;
      case SDLK_e:
	selected = select_pento (nb_pento,pento_array,*pos_mouse_x,*pos_mouse_y);
	// turn and draw
	if(selected != -1){
	  turn_pent(pento_array[selected]);
	  SDL_FillRect(background,NULL,SDL_MapRGB(background->format,0,0,0));
	  draw_area (array_file,area,square_sprite,background);
	  draw_array(pento_array,array_file,array_end,background);
	  SDL_Flip(background);
	}
	break;
      }
      break;
    }
}

/* move the pentomino selected */
void move (int selected,pentomino_ptr pento_array[20],int * pos_mouse_x,int * pos_mouse_y,char array_file [1000],int array_end,SDL_Event event,area_ptr area,SDL_Surface * square_sprite)
{
  int i;
  //SDL_Surface * save_sprite;
  for (i=0;i<5;i++){
    pento_array[selected]->square[i]->rcSrc.x = pento_array[selected]->square[i]->rcSrc.x + event.motion.x - *pos_mouse_x;
    pento_array[selected]->square[i]->rcSrc.y = pento_array[selected]->square[i]->rcSrc.y + event.motion.y - *pos_mouse_y;
  }
  *pos_mouse_x=event.button.x;
  *pos_mouse_y=event.button.y;
  SDL_FillRect(background,NULL,SDL_MapRGB(background->format,0,0,0));
  draw_area (array_file,area,square_sprite,background);
  draw_array(pento_array,array_file,array_end,background);
  //save_sprite = pento_array[selected]->square_sprite;
  //SDL_FreeSurface(pento_array[selected]->square_sprite);
  //pento_array[selected]->square_sprite = save_sprite;
  //draw_pentomino(pento_array[selected],background);
  SDL_Flip(background);
}

int select_pento (int nb_pento,struct pentomino ** pento_array, int pos_mouse_x, int pos_mouse_y)
{
  int i,j;
  int selected = -1;
  int coat = 0;
  // verification for all the pentominos
  for (i=0;i<nb_pento;i++){
    // verification for all the squares of the pentominos
    for (j=0;j<5;j++){
      // if collide
      if (pos_mouse_x > pento_array[i]->square[j]->rcSrc.x && pos_mouse_x < pento_array[i]->square[j]->rcSrc.x + 30 && pos_mouse_y > pento_array[i]->square[j]->rcSrc.y && pos_mouse_y < pento_array[i]->square[j]->rcSrc.y + 30){
	  // choose the pentomino on the first coat
	  if (pento_array[i]->coat >= coat){
	    coat = pento_array[i]->coat;
	    selected = i;
	  }
	}
    }
  }
  return selected;
}

void update_coat (struct pentomino ** pento_array,int selected,int nb_pento)
{
  int i;
  pentomino_ptr save_pento = pento_array[selected];
  for (i=selected+1;i<nb_pento;i++){
    pento_array[i-1] = pento_array[i];
  }
  pento_array[nb_pento-1] = save_pento;
}

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
    
  }
  return EXIT_SUCCESS;
}

