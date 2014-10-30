#include "pentomino.h"
#include <assert.h>
#define SIZE_SQUARE 30

pentomino_ptr new_pentomino(int position)
{
  int i,j;
  pentomino_ptr new_pent = (pentomino_ptr)malloc(sizeof(struct pentomino));
  for (i = 0;i <= 4;i++){
    for(j = 0;j <= 4;j++){
      new_pent->array_pent[i][j] = 'o';
    }
  }
  for (i=0; i<5; i++) {
    new_pent->square[i] = NULL;
  }
  new_pent->position = position;
  return new_pent;
}

void draw_pentomino(pentomino_ptr pentomino,SDL_Surface *background)
{
  int i ;
  for(i=0;i<5;i++){
    draw_square(pentomino->square[i],pentomino->square_sprite,background);
  }
}


void mirror(pentomino_ptr pentomino){
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
  printf("%d\n",max_col);
  //ok
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

	
int file_array(char array_file[1000],FILE *file) {
  int i = -1;
  while(!feof(file) && i++<1000) {
    array_file[i] = (char)fgetc(file);
  }
  return i;
}

int begin_pent (char array_file[1000]){
  bool start = false;
  int i = 0;
  while(!start && i<1000){
    if(array_file[i] == '\n' && array_file[i+1] == '\n'){
      start = true;
    }
    i++;
  }
  return i+1;
}

int nb_pent(char array_file[1000], int array_end) {
  int nb_square,i;
  nb_square = 0;
  i = begin_pent(array_file);
  for (;i<array_end; i++) {
    if (array_file[i]=='#') {
       nb_square++;
    }
  }
  assert((nb_square/5)*5 == nb_square);
  return nb_square/5;
}

int new_array(char array_file[1000],int pos_file,char array_pent[5][5]){
  int i,j,Nb_square=0;
  for(i=0;i<5;i++){
    for(j=0;j<5;j++){
      array_pent[i][j] = 'o';
    }
  }
  i = 0;
  j = 0;
  while(Nb_square<5){
    if (array_file[pos_file] =='\n'){
      i++;
      j = 0;
    }else if(array_file[pos_file] == '#'){
      array_pent[i][j] = '#';
      j++;
      Nb_square++;
    } else {
      j++;
    }
    pos_file++ ;
  }
  return pos_file+2;
}

bool test_pento(char array_file[1000], int array_end){
  int area = size_area(array_file);
  int nb_pento = nb_pent(array_file, array_end);
  return area % nb_pento == 0;
}

int size_area(char array_file[1000]){
  bool end = false;
  int area_size,i;
  i = 0;
  area_size = 0;
  while (!end){
    if(array_file[i] == '\n' && array_file[i+1]=='\n'){
      end=true;
    }else if (array_file[i] == '#'){
      area_size ++;
    }
    i++;
  }
  return area_size;
}

void get_square(square_ptr square[5] ,char array_pent[5][5],int pos_x,int pos_y){
  int i,j,nb_square;
  nb_square = 0;
  SDL_Rect rcSrc,rcSprite;
  while (nb_square<5){
    for(i = 0;i < 5;i++){
      for(j = 0;j < 5;j++){
	if (array_pent[i][j] == '#'){
	  rcSrc.x = pos_x + j*SIZE_SQUARE;
	  rcSrc.y = pos_y + i*SIZE_SQUARE;
	  rcSprite.x = 0 ;
	  rcSprite.y = 0 ;
	  rcSprite.w = 30 ;
	  rcSprite.h = 30 ;
	  square[nb_square]= new_square(rcSrc,rcSprite);
	  nb_square++;
	}
      }
    }
  }
}

void tab_pento (char array_file[1000],pentomino_ptr pento_array[20], int array_end,SDL_Surface * array_color[12]){
  int nb_pento,i,pos_file;
  int j = 0;
  nb_pento = nb_pent(array_file, array_end) ;
  pos_file = begin_pent(array_file);
  for(i=0;i<nb_pento;i++){
    pento_array[i] = new_pentomino(nb_pento) ;
    pos_file = new_array(array_file,pos_file,pento_array[i]->array_pent);
    get_square(pento_array[i]->square,pento_array[i]->array_pent,5,5+i*5*SIZE_SQUARE);
    if(j == 12){
      j = 0;
    }
    pento_array[i]->square_sprite = array_color[j];
    j++;
  }
} 
     

      
void draw_array(pentomino_ptr pento_array[20],char array_file[1000],int array_end ,SDL_Surface *background){
  int i,nb_pento;
  nb_pento = nb_pent(array_file,array_end);
    for (i = 0;i<nb_pento;i++){
      pento_array[i]->coat = i;
      draw_pentomino(pento_array[i],background);
    }
}

void turn_pent(pentomino_ptr pentomino){
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
      printf("%c",pentomino->array_pent[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void free_pento (pentomino_ptr pentomino)
{
  free(pentomino->square_sprite);
  free(pentomino);
}
