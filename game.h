#ifndef GAME_H
#define GAME_H
#define  WIDTH  800
#define HEIGHT  600
#include "pentomino.h"
#include "area.h"

SDL_Surface *screen;

void test_set (char array_file[1000],pentomino_ptr pento_array[20],area_ptr area,int array_end);

void auto_set(char array_file[1000],pentomino_ptr pentomino,pentomino_ptr pento_array[20],area_ptr area,int array_end);

bool final_test(char array_file[1000],pentomino_ptr pento_array[20],area_ptr area,int array_end);

void mirror(pentomino_ptr pentomino ,int pos_mouse_x,int pos_mouse_y);

bool test_pento(char array_file[1000], int array_end);

void turn_pent(pentomino_ptr pentomino,int pos_mouse_x ,int pos_mouse_y);

void initSDL(void);

void controls(int nb_pento,int * end,pentomino_ptr pento_array[20], int *click, int * pos_mouse_x, int * pos_mouse_y,char array_file[1000],area_ptr area,int array_end);

void move (int selected,pentomino_ptr pento_array[20],int * pos_mouse_x,int * pos_mouse_y,SDL_Event event);

int select_pento (int nb_pento,pentomino_ptr pento_array[20],int pos_mouse_x, int pos_mouse_y);

void update_coat (pentomino_ptr pento_array[20],int selected,int nb_pento);

/* write the controls */
SDL_Surface * write_controls (void);

void draw_all (char array_file [1000],area_ptr area,SDL_Surface * square_sprite,int array_end,pentomino_ptr pento_array[20],SDL_Surface * background,SDL_Rect pos_background,SDL_Surface * text_controls,SDL_Rect pos_text_controls);

void free_all(area_ptr area,pentomino_ptr pento_array[20],char array_file[1000],int array_end);
#endif
