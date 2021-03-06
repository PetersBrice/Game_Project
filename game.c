/*********************************************/
/* Decolle Anais - Peters Brice              */
/* game.c                                    */
/* This file contains the functions to       */
/* play the game : display, movements of the */ 
/* pentominos, controls with the keyboard    */
/* and the mouse, timer.                     */
/*********************************************/

#include "game.h"
#define SIZE_SQUARE 30

/* tests if the pentomino is in the area */
void test_set (char array_file[1000],pentomino_ptr pento_array[20],area_ptr area,int nb_pento)
{
  int i,j,size,nb_square;
  size = size_area(array_file);
  for(i = 0;i < size;i++){
    area->square[i]->set = false;
  }
  for(i = 0;i < size;i++){
    for(j = 0;j < nb_pento;j++){
      for(nb_square = 0;nb_square<5;nb_square++){
	if((area->square[i]->rcSrc.x == pento_array[j]->square[nb_square]->rcSrc.x) && (area->square[i]->rcSrc.y == pento_array[j]->square[nb_square]->rcSrc.y)){
	  area->square[i]->set = true;
	}
      }
    }
  }
}

/* automatically positions  the pentomino in the area */
void auto_set (char array_file[1000],pentomino_ptr pentomino,pentomino_ptr pento_array[20],area_ptr area,int nb_pento)
{
  bool set = true;
  int nb_set = 0;
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
    if((pentomino->square[i]->rcSrc.x + SIZE_SQUARE >= max_x + 5) || (pentomino->square[i]->rcSrc.y + SIZE_SQUARE >= max_y + 5) || (pentomino->square[i]->rcSrc.x <= min_x - 5) || (pentomino->square[i]->rcSrc.y <= min_y - 5))
      in_area = false;
  }
  if(in_area){
    for(i = 0;i < 5;i++){
      for(j = 0;j < size ;j++){
	if(fabs(pentomino->square[i]->rcSrc.x - area->square[j]->rcSrc.x) < min_next_x){
	  min_next_x = fabs(pentomino->square[i]->rcSrc.x - area->square[j]->rcSrc.x);
	  next_x = pentomino->square[i]->rcSrc.x - area->square[j]->rcSrc.x;
	}
	if(fabs(pentomino->square[i]->rcSrc.y - area->square[j]->rcSrc.y) < min_next_y){
	  min_next_y = fabs(pentomino->square[i]->rcSrc.y - area->square[j]->rcSrc.y);
	  next_y = pentomino->square[i]->rcSrc.y - area->square[j]->rcSrc.y;
	}
      }
    }
    test_set(array_file,pento_array,area,nb_pento);
    for(i = 0;i < 5;i++){
      for(j = 0;j < size;j++){
	if((-next_y + pentomino->square[i]->rcSrc.y == area->square[j]->rcSrc.y) && (-next_x + pentomino->square[i]->rcSrc.x == area->square[j]->rcSrc.x)){
	  nb_set ++;
	  if(area->square[j]->set){
	    set = false;
	  }
	}
      }
    }
    if(set && nb_set == 5){
      for(i = 0;i < 5;i++){
	pentomino->square[i]->rcSrc.y = -next_y + pentomino->square[i]->rcSrc.y;
	pentomino->square[i]->rcSrc.x = -next_x + pentomino->square[i]->rcSrc.x;
      }
    }
  }
}

/* say if the game is finished */
bool final_test (char array_file[1000],pentomino_ptr pento_array[20],area_ptr area,int nb_pento)
{
  int i;
  bool end = true;
  int size = size_area(array_file); 
  test_set(array_file,pento_array,area,nb_pento);
  for(i = 0;i < size;i++){
    if(!area->square[i]->set)
      end = false;
  }
  return end;
}

/* say if there is enough of pentominos */
bool test_pento (char array_file[1000],int nb_pento)
{
  int area = size_area(array_file);
  int dif;
  dif =  nb_pento*5 - area;
  if(dif<0){
    return false;
  }else{
    if (dif == 0){
      return true;
    }else{
      return dif % 5 == 0;
    }
  }
}

/* modifies the array of the pentomino to make the mirror of the pentomino */
void mirror (pentomino_ptr pentomino,int pos_mouse_x,int pos_mouse_y)
{
  int i,j,dif_x,dif_y;
  int max_col = 0;
  int min = 2000;
  int max = 0;
  char new_shape[5][5];
  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      new_shape[i][j] = 'o';
      if(pentomino->array_pent[i][j] == '#' && max_col < j)
	max_col = j ;
    }
    if(pentomino->square[i]->rcSrc.x<min)
      min = pentomino->square[i]->rcSrc.x;
    if(pentomino->square[i]->rcSrc.x>max)
      max = pentomino->square[i]->rcSrc.x;
  }
  for(i = 0;i < 5;i++){
    for(j = 0;j <= max_col;j++){
      new_shape[i][j]=pentomino->array_pent[i][max_col-j];
    }
  }
  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      pentomino->array_pent[i][j] = new_shape[i][j];
    }
  }
  for(i = 0;i < 5;i++){
    if(pentomino->square[i]->rcSrc.x == min){
      pentomino->square[i]->rcSrc.x = max;
    }else if(pentomino->square[i]->rcSrc.x == min + SIZE_SQUARE){
      pentomino->square[i]->rcSrc.x = max-SIZE_SQUARE;
    } else if(pentomino->square[i]->rcSrc.x == min + 2*SIZE_SQUARE){
      pentomino->square[i]->rcSrc.x = max-2*SIZE_SQUARE;
    }else if(pentomino->square[i]->rcSrc.x == min + 3 * SIZE_SQUARE){
      if(pentomino->square[i]->rcSrc.x == max){
	pentomino->square[i]->rcSrc.x = min; 
      }else{  
	pentomino->square[i]->rcSrc.x = min +SIZE_SQUARE;
      }
    }else if (pentomino->square[i]->rcSrc.x == max){
      pentomino->square[i]->rcSrc.x = min; 
    }      
  }
  dif_x = pentomino->square[0]->rcSrc.x - (pos_mouse_x - SIZE_SQUARE / 2) ;
  dif_y = pentomino->square[0]->rcSrc.y - (pos_mouse_y - SIZE_SQUARE / 2) ;
  pentomino->square[0]->rcSrc.x = pos_mouse_x - SIZE_SQUARE / 2;
  pentomino->square[0]->rcSrc.y = pos_mouse_y - SIZE_SQUARE / 2;
  for(i = 1;i < 5;i++){
    pentomino->square[i]->rcSrc.x = pentomino->square[i]->rcSrc.x - dif_x;
    pentomino->square[i]->rcSrc.y = pentomino->square[i]->rcSrc.y - dif_y;
  }
}

/* modifies the array of the pentomino to turn the pentomino */
void turn_pent (pentomino_ptr pentomino,int pos_mouse_x,int pos_mouse_y)
{
  int i,j,temp_x,temp_y,temp_X,temp_Y,nb_square;
  char temp[5][5];
  nb_square = 0;
  temp_X = pos_x_array(pentomino) + 5 * SIZE_SQUARE;
  temp_Y = pos_y_array(pentomino);
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
  temp_x = pos_mouse_x - pos_mouse_y + temp_Y;
  temp_y = pos_mouse_x + pos_mouse_y - temp_X;
  while(nb_square < 5){
    for(i = 0;i < 5;i++){
       for(j = 0;j < 5;j++){
	 if(pentomino->array_pent[i][j] == '#'){
	   pentomino->square[nb_square]->rcSrc.x = temp_x + j * SIZE_SQUARE;
	   pentomino->square[nb_square]->rcSrc.y = temp_y + i * SIZE_SQUARE;
	   nb_square++;
	 }
       }
    }
  }
}

/* initializes and closes SDL and SDL_TTF */
void initSDL (void)
{
  SDL_Surface * background = NULL;
  // SDL_ttf
  if(TTF_Init() < 0){
    fprintf(stderr,"Error initialization of SDL_ttf : %s\n",TTF_GetError());
    exit(EXIT_FAILURE);
  }
  atexit(TTF_Quit);
  // SDL
  if(SDL_Init(SDL_INIT_VIDEO) < 0){
    fprintf(stderr,"Error initialization of SDL : %s\n",SDL_GetError());
    exit(EXIT_FAILURE);
  }
  atexit(SDL_Quit);
  // icon of the game
  SDL_WM_SetIcon(SDL_LoadBMP("icon.bmp"),NULL);
  // load the screen
  screen = SDL_SetVideoMode(WIDTH,HEIGHT,32,SDL_SWSURFACE | SDL_DOUBLEBUF);
  // title of the game
  SDL_WM_SetCaption("PUZZLE",NULL);
}

/* manages all the controls with the keyboard and the mouse */
void controls (int nb_pento,int * end,pentomino_ptr pento_array[20],int *click,int * pos_mouse_x,int * pos_mouse_y,char array_file[1000],area_ptr area)
{
  SDL_Event event;
  int i;
  int selected;
  SDL_PollEvent(&event);
  switch(event.type){
    // click on the cross
    case SDL_QUIT:
      *end = 1;
      break;
      // press the left click of the mouse
    case SDL_MOUSEBUTTONDOWN:
      if(event.button.button == SDL_BUTTON_LEFT){
	*click = 1;
	*pos_mouse_x = event.button.x;
	*pos_mouse_y = event.button.y;
	selected = select_pento(nb_pento,pento_array,*pos_mouse_x,*pos_mouse_y);
	// put the pentomino selected on the first coat
	if(selected != -1)
	  update_coat(pento_array,selected,nb_pento);
      }
      break;
      // loosen the left click of the mouse
    case SDL_MOUSEBUTTONUP:
      if(event.button.button == SDL_BUTTON_LEFT)
	*click = 0;
      selected = select_pento(nb_pento,pento_array,*pos_mouse_x,*pos_mouse_y);
      if(selected != -1)
	auto_set(array_file,pento_array[selected],pento_array,area,nb_pento);
      break;
    case SDL_MOUSEMOTION:
      // if the mouse moves and the left click is pressed
      if (*click == 1){
	selected = select_pento(nb_pento,pento_array,*pos_mouse_x,*pos_mouse_y);
	// if click on a pentomino
	if(selected != -1){
	  // move the pentomino
	  move(selected,pento_array,pos_mouse_x,pos_mouse_y,event);
	}
      }      
      break;
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym){
	//button A for the mirror
      case SDLK_a:
	selected = select_pento(nb_pento,pento_array,*pos_mouse_x,*pos_mouse_y);
	// mirror
	if(selected != -1){
	  mirror(pento_array[selected],*pos_mouse_x,*pos_mouse_y);
	}
	break;
      case SDLK_e:
	selected = select_pento(nb_pento,pento_array,*pos_mouse_x,*pos_mouse_y);
	// turn
	if(selected != -1)
	  turn_pent(pento_array[selected],*pos_mouse_x,*pos_mouse_y);
	break;
      case SDLK_ESCAPE:
	*end = 1;
      }
      break;
    }
}

/* moves the pentomino selected with the mouse */
void move (int selected,pentomino_ptr pento_array[20],int * pos_mouse_x,int * pos_mouse_y,SDL_Event event)
{
  int i;
  for(i = 0;i < 5;i++){
    pento_array[selected]->square[i]->rcSrc.x = pento_array[selected]->square[i]->rcSrc.x + event.motion.x - *pos_mouse_x;
    pento_array[selected]->square[i]->rcSrc.y = pento_array[selected]->square[i]->rcSrc.y + event.motion.y - *pos_mouse_y;
  }
  *pos_mouse_x = event.button.x;
  *pos_mouse_y = event.button.y;
}

/* says what pentomino is selected by the mouse */
int select_pento (int nb_pento,pentomino_ptr pento_array[20],int pos_mouse_x,int pos_mouse_y)
{
  int i,j;
  int selected = -1;
  int coat = 0;
  // verification for all the pentominos
  for(i = 0;i < nb_pento;i++){
    // verification for all the squares of the pentominos
    for(j = 0;j < 5;j++){
      // if collide
      if(pos_mouse_x > pento_array[i]->square[j]->rcSrc.x && pos_mouse_x < pento_array[i]->square[j]->rcSrc.x + SIZE_SQUARE && pos_mouse_y > pento_array[i]->square[j]->rcSrc.y && pos_mouse_y < pento_array[i]->square[j]->rcSrc.y + SIZE_SQUARE){
	  // choose the pentomino on the first coat
	  if(pento_array[i]->coat >= coat){
	    coat = pento_array[i]->coat;
	    selected = i;
	  }
	}
    }
  }
  return selected;
}

/* updates the coats of the pentomino, the order in which they are drawn */
void update_coat (pentomino_ptr pento_array[20],int selected,int nb_pento)
{
  int i;
  pentomino_ptr save_pento = pento_array[selected];
  for(i = selected + 1;i < nb_pento;i++){
    pento_array[i - 1] = pento_array[i];
  }
  pento_array[nb_pento - 1] = save_pento;
}

/* writes the controls on the screen */
SDL_Surface * write_controls (SDL_Color color)
{
  // load the police Orial, size 40, black color
  TTF_Font * police = TTF_OpenFont("orialbold.ttf",20);
  // picture of the text
  SDL_Surface * text_controls = TTF_RenderText_Blended(police,"ESCAPE : quit   A : mirror   E : turn",color);
  TTF_CloseFont(police);
  return text_controls;
}

/* updates and draws the timer */ 
void write_timer (int timer,int *seconds,int *minutes,int *hours,char sec [2],char mn [2],char hr [3],TTF_Font * police,SDL_Color color,SDL_Rect pos_time_h_m_s,SDL_Rect pos_time_s,SDL_Rect pos_time_m,SDL_Rect pos_time_h,SDL_Rect pos_time_inf)
{
  SDL_Surface *time;
  // if 99 hours is not exceed
  if(timer < (3600 * 1000 * 99)){
    // write just "h  mn  s"
    time = TTF_RenderText_Solid(police,"h     mn     s",color);
    SDL_BlitSurface(time,NULL,screen,&pos_time_h_m_s);
    SDL_FreeSurface(time);
    // seconds
    if((timer/1000) - (60 * *minutes) - (3600 * *hours)  == 60){
      *minutes = *minutes + 1;
      *seconds = 0;
    }else{
      *seconds = (timer / 1000) - (60 * *minutes) - (3600 * *hours);
    }
    sprintf(sec,"%d",*seconds);
    time = TTF_RenderText_Solid(police,sec,color);
    SDL_BlitSurface(time,NULL,screen,&pos_time_s);
    SDL_FreeSurface(time);
    // minutes
    if(*minutes == 60){
      *hours = *hours + 1;
      *minutes = 0;
    }
    sprintf(mn,"%d",*minutes);
    time = TTF_RenderText_Solid(police,mn,color);
    SDL_BlitSurface(time,NULL,screen,&pos_time_m);
    SDL_FreeSurface(time);
    // hours
    sprintf(hr,"%d",*hours);
    time = TTF_RenderText_Solid(police,hr,color);
    SDL_BlitSurface(time,NULL,screen,&pos_time_h);
  }else{
    // if 99 hours is exceed
    time = TTF_RenderText_Solid(police,"infinity",color);
    SDL_BlitSurface(time,NULL,screen,&pos_time_inf);
  }
  SDL_FreeSurface(time);
}

/* writes the names of the developers on the end screen */
void write_developers (SDL_Color color,TTF_Font * police)
{
  SDL_Surface * developers = TTF_RenderText_Blended(police,"Developers : Anais Decolle & Brice Peters",color);
  SDL_Rect pos;
  pos.x = 225;
  pos.y = 400;
  SDL_BlitSurface(developers,NULL,screen,&pos);
  SDL_FreeSurface(developers);
}

/* draws the end screen, with the names of the developers and the time put to finish the puzzle */
void draw_end_screen (SDL_Surface * background,SDL_Rect pos_background,int timer,int *seconds,int *minutes,int *hours,char sec [2],char mn [2], char hr [3],TTF_Font * police,SDL_Color color,SDL_Rect pos_time_h_m_s,SDL_Rect pos_time_s,SDL_Rect pos_time_m,SDL_Rect pos_time_h,SDL_Rect pos_time_inf)
{
  SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
  SDL_BlitSurface(background,NULL,screen,&pos_background);
  write_timer(timer,seconds,minutes,hours,sec,mn,hr,police,color,pos_time_h_m_s,pos_time_s,pos_time_m,pos_time_h,pos_time_inf);
  write_developers(color,police);
  SDL_Flip(screen);
}

/* draws the background, the timer, the area, the pentominos, the controls */
void draw_all (char array_file [1000],area_ptr area,SDL_Surface * square_sprite,int array_end,pentomino_ptr pento_array[20],SDL_Surface * background,SDL_Rect pos_background,SDL_Surface * text_controls,SDL_Rect pos_text_controls,int timer,int *seconds,int *minutes,int *hours,char sec [2],char mn [2], char hr [3],TTF_Font * police,SDL_Color color,SDL_Rect pos_time_h_m_s,SDL_Rect pos_time_s,SDL_Rect pos_time_m,SDL_Rect pos_time_h,SDL_Rect pos_time_inf)
{
  SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
  SDL_BlitSurface(background,NULL,screen,&pos_background);
  SDL_BlitSurface(text_controls,NULL,screen,&pos_text_controls);
  write_timer (timer,seconds,minutes,hours,sec,mn,hr,police,color,pos_time_h_m_s,pos_time_s,pos_time_m,pos_time_h,pos_time_inf);
  draw_area (array_file,area,square_sprite,screen);
  draw_array(pento_array,array_file,array_end,screen);
  SDL_Flip(screen);
}

/* frees the pointers of the area and the pentominos */
void free_all (area_ptr area,pentomino_ptr pento_array[20],char array_file[1000],int array_end)
{
  free_area(area,array_file);
  free_pento_array(pento_array,array_file,array_end);
}
