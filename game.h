/*******************************************/
/* Decolle Anais - Peters Brice            */
/* game.h                                  */
/* It's the header of game.c .             */
/*******************************************/

#ifndef GAME_H
#define GAME_H
#define WIDTH  800
#define HEIGHT  600
#include "pentomino.h"
#include "area.h"

SDL_Surface *screen;

/* tests if the pentomino is in the area */
void test_set (char array_file[1000],pentomino_ptr pento_array[20],area_ptr area,int nb_pento);

/* automatically positions  the pentomino in the area */
void auto_set (char array_file[1000],pentomino_ptr pentomino,pentomino_ptr pento_array[20],area_ptr area,int nb_pento);

/* say if the game is finished */
bool final_test (char array_file[1000],pentomino_ptr pento_array[20],area_ptr area,int nb_pento);

/* say if there is enough of pentominos */
bool test_pento (char array_file[1000],int nb_pento);

/* modifies the array of the pentomino to make the mirror of the pentomino */
void mirror (pentomino_ptr pentomino,int pos_mouse_x,int pos_mouse_y);

/* modifies the array of the pentomino to turn the pentomino */
void turn_pent (pentomino_ptr pentomino,int pos_mouse_x,int pos_mouse_y);

/* initializes and closes SDL and SDL_TTF */
void initSDL (void);

/* manages all the controls with the keyboard and the mouse */
void controls (int nb_pento,int * end,pentomino_ptr pento_array[20],int *click,int * pos_mouse_x,int * pos_mouse_y,char array_file[1000],area_ptr area);

/* moves the pentomino selected with the mouse */
void move (int selected,pentomino_ptr pento_array[20],int * pos_mouse_x,int * pos_mouse_y,SDL_Event event);

/* says what pentomino is selected by the mouse */
int select_pento (int nb_pento,pentomino_ptr pento_array[20],int pos_mouse_x,int pos_mouse_y);

/* updates the coats of the pentomino, the order in which they are drawn */
void update_coat (pentomino_ptr pento_array[20],int selected,int nb_pento);

/* writes the controls on the screen */
SDL_Surface * write_controls (SDL_Color color);

/* updates and draws the timer */ 
void write_timer (int timer,int *seconds,int *minutes,int *hours,char sec [2],char mn [2],char hr [3],TTF_Font * police,SDL_Color color,SDL_Rect pos_time_h_m_s,SDL_Rect pos_time_s,SDL_Rect pos_time_m,SDL_Rect pos_time_h,SDL_Rect pos_time_inf);

/* writes the names of the developers on the end screen */
void write_developers (SDL_Color color,TTF_Font * police);

/* draws the end screen, with the names of the developers and the time put to finish the puzzle */
void draw_end_screen (SDL_Surface * background,SDL_Rect pos_background,int timer,int *seconds,int *minutes,int *hours,char sec [2],char mn [2],char hr [3],TTF_Font * police,SDL_Color color,SDL_Rect pos_time_h_m_s,SDL_Rect pos_time_s,SDL_Rect pos_time_m,SDL_Rect pos_time_h,SDL_Rect pos_time_inf);

/* draws the background, the timer, the area, the pentominos, the controls */
void draw_all (char array_file [1000],area_ptr area,SDL_Surface * square_sprite,int array_end,pentomino_ptr pento_array[20],SDL_Surface * background,SDL_Rect pos_background,SDL_Surface * text_controls,SDL_Rect pos_text_controls,int timer,int *seconds,int *minutes,int *hours,char sec [2],char mn [2], char h [3],TTF_Font * police,SDL_Color color,SDL_Rect pos_time_h_m_s,SDL_Rect pos_time_s,SDL_Rect pos_time_m,SDL_Rect pos_time_h,SDL_Rect pos_time_inf);

/* frees the pointers of the area and the pentominos */
void free_all(area_ptr area,pentomino_ptr pento_array[20],char array_file[1000],int array_end);

#endif
