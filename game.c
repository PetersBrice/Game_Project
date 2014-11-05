#include "game.h"
#define SIZE_SQUARE 30

void auto_set(char array_file[1000],pentomino_ptr pentomino,area_ptr area)
{
  int i,j,min_x,min_y,max_x,max_y,min_next_x,min_next_y,next_x,next_y,size;
  size = size_area(array_file);
  min_next_x = SIZE_SQUARE;
  min_next_y = SIZE_SQUARE;
  min_x = min_x_area(area,array_file);
  min_y = min_y_area(area,array_file);
  max_x = max_x_area(area,array_file);
  max_y = max_y_area(area,array_file);
  bool in_area = true;
  for(i = 0;i < 5;i++){
    if ((pentomino->square[i]->rcSrc.x >= max_x) || (pentomino->square[i]->rcSrc.y >= max_y) || (pentomino->square[i]->rcSrc.x <= min_x) || (pentomino->square[i]->rcSrc.y <= min_y)){
      in_area = false;
    }
  }
  if (in_area == true){
    for(i = 0;i < 5;i++){
      for(j = 0;j < size ;j++){
	if(fabs(pentomino->square[i]->rcSrc.x-area->square[j]->rcSrc.x)<min_next_x){
	  min_next_x = fabs(pentomino->square[i]->rcSrc.x-area->square[j]->rcSrc.x);
	  next_x = pentomino->square[i]->rcSrc.x-area->square[j]->rcSrc.x;
	}
	if(fabs(pentomino->square[i]->rcSrc.y-area->square[j]->rcSrc.y)<min_next_y){
	  min_next_y = fabs(pentomino->square[i]->rcSrc.y-area->square[j]->rcSrc.y);
	  next_y = pentomino->square[i]->rcSrc.y-area->square[j]->rcSrc.y;
	}
      }
    }
    for (i = 0;i<5;i++){
      pentomino->square[i]->rcSrc.y = -next_y+pentomino->square[i]->rcSrc.y;
      pentomino->square[i]->rcSrc.x = -next_x+pentomino->square[i]->rcSrc.x;
    }
  }
}

bool final_test(char array_file[1000],pentomino_ptr pento_array[20],area_ptr area,int array_end)
{
  bool end = true;
  int i,j,size,nb_square,nb_pento;
  size = size_area(array_file);
  nb_pento = nb_pent(array_file,array_end);
  for(i = 0;i< size;i++){
    area->square[i]->set = false;
  }
  for(i = 0;i < size;i++){
    for(j = 0;j < nb_pento;j++){
      for(nb_square = 0;nb_square<5;nb_square++){
	if((area->square[i]->rcSrc.x == pento_array[j]->square[nb_square]->rcSrc.x) && (area->square[i]->rcSrc.y == pento_array[j]->square[nb_square]->rcSrc.y)){
	  area->square[i]-> set = true;
	}
      }
    }
  }
  for(i = 0;i < size;i++){
    if(area->square[i]->set == false){
      end = false;
    }
  }
  return end;
}

void mirror(pentomino_ptr pentomino)
{
  int i,j,max_col;
  max_col = 0;
  int min = 2000;
  int max = 0;
  char new_shape[5][5];
  for (i = 0;i < 5;i++){
    for (j = 0;j < 5;j++){
      new_shape[i][j] = 'o';
      if (pentomino->array_pent[i][j] == '#' && max_col < j){
	max_col = j ;
      }
    }
    if (pentomino->square[i]->rcSrc.x<min){
      min = pentomino->square[i]->rcSrc.x;
    }
    if (pentomino->square[i]->rcSrc.x>max){
      max = pentomino->square[i]->rcSrc.x;
    }
  }
  for (i = 0;i < 5;i++){
    for (j = 0;j <= max_col;j++){
      new_shape[i][j]=pentomino->array_pent[i][max_col-j];
    }
  }
  for (i = 0;i < 5;i++){
    for (j = 0;j < 5;j++){
      pentomino->array_pent[i][j] = new_shape[i][j];
    }
  }
  for (i = 0;i < 5;i++){
    if (pentomino->square[i]->rcSrc.x == min){
      pentomino->square[i]->rcSrc.x = max;
    }else if (pentomino->square[i]->rcSrc.x == min + SIZE_SQUARE){
      pentomino->square[i]->rcSrc.x = max-SIZE_SQUARE;
    } else if (pentomino->square[i]->rcSrc.x == min + 2*SIZE_SQUARE){
      pentomino->square[i]->rcSrc.x = max-2*SIZE_SQUARE;
    }else if (pentomino->square[i]->rcSrc.x == min + 3 * SIZE_SQUARE){
      if (pentomino->square[i]->rcSrc.x == max){
	pentomino->square[i]->rcSrc.x = min; 
      }else{  
	pentomino->square[i]->rcSrc.x = min +SIZE_SQUARE;
      }
    }else if (pentomino->square[i]->rcSrc.x == max){
      pentomino->square[i]->rcSrc.x = min; 
    }      
  }
}

bool test_pento(char array_file[1000], int array_end)
{
  int area = size_area(array_file);
  int nb_pento = nb_pent(array_file, array_end);
  return area % nb_pento == 0;
}

void turn_pent(pentomino_ptr pentomino)
{
  int i,j,temp_x,temp_y,nb_square;
  char temp[5][5];
  nb_square = 0;
  temp_x = pentomino->square[0]->rcSrc.x;
  temp_y = pentomino->square[0]->rcSrc.y;
  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      temp[i][j] = pentomino->array_pent[j][4-i];
    }
  }
  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      pentomino->array_pent[i][j] = temp[i][j];
    }
  }
  while(nb_square<5){
    for(i = 0;i<5;i++){
      for(j = 0;j<5;j++){
	if(pentomino->array_pent[i][j] == '#'){
	  pentomino->square[nb_square]->rcSrc.x =  j*SIZE_SQUARE+temp_x;
	  pentomino->square[nb_square]->rcSrc.y = i*SIZE_SQUARE +temp_y;
	  nb_square++;
	}
      }
    }
  }
  for(i = 0;i<5;i++){
    for(j = 0;j<5;j++){
    }
  }
}

/* initialization of SDL */
void initSDL(void)
{
  SDL_Surface * background = NULL;
  if (SDL_Init (SDL_INIT_VIDEO) < 0){
    fprintf(stderr, "Error initialization of SDL : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  atexit(SDL_Quit);
  // load the screen
  screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
  SDL_WM_SetCaption("PUZZLE", NULL);
}

/* controls */
void controls (int nb_pento,int * end,pentomino_ptr pento_array[20], int *click, int * pos_mouse_x, int * pos_mouse_y,char array_file[1000],area_ptr area)
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
      }
      break;
    case SDL_MOUSEMOTION:
      // if the mouse moves and the left click is pressed
      if (*click == 1){
	selected = select_pento (nb_pento,pento_array,*pos_mouse_x,*pos_mouse_y);
	// if click on a pentomino
	if (selected != -1){
	  // move the pentomino
	  move (selected,pento_array,pos_mouse_x,pos_mouse_y,event);
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
	}
	break;
      case SDLK_e:
	selected = select_pento (nb_pento,pento_array,*pos_mouse_x,*pos_mouse_y);
	// turn and draw
	if(selected != -1){
	  turn_pent(pento_array[selected]);
	}
	break;
      }
      break;
    }
}

/* move the pentomino selected */
void move (int selected,pentomino_ptr pento_array[20],int * pos_mouse_x,int * pos_mouse_y,SDL_Event event)
{
  int i;
  for (i=0;i<5;i++){
    pento_array[selected]->square[i]->rcSrc.x = pento_array[selected]->square[i]->rcSrc.x + event.motion.x - *pos_mouse_x;
    pento_array[selected]->square[i]->rcSrc.y = pento_array[selected]->square[i]->rcSrc.y + event.motion.y - *pos_mouse_y;
  }
  *pos_mouse_x=event.button.x;
  *pos_mouse_y=event.button.y;
}

/* return the pentomino selected */
int select_pento (int nb_pento,pentomino_ptr pento_array[20], int pos_mouse_x, int pos_mouse_y)
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

/* update the coats of the pentomino to draw */
void update_coat (pentomino_ptr pento_array[20],int selected,int nb_pento)
{
  int i;
  pentomino_ptr save_pento = pento_array[selected];
  for (i=selected+1;i<nb_pento;i++){
    pento_array[i-1] = pento_array[i];
  }
  pento_array[nb_pento-1] = save_pento;
}

/* draw the pentomino, the area and the background */
void draw_all (char array_file [1000],area_ptr area,SDL_Surface * square_sprite,int array_end,pentomino_ptr pento_array[20],SDL_Surface * background,SDL_Rect pos_background)
{
  SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
  SDL_BlitSurface(background,NULL,screen,&pos_background);
  draw_area (array_file,area,square_sprite,screen);
  draw_array(pento_array,array_file,array_end,screen);
  SDL_Flip(screen);
}
