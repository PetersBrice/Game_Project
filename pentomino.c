#include "pentomino.h"
#define SIZE_SQUARE 30
#define MAXP 5 // maximum of pentomino

pentomino_ptr new_pentomino(int array_pent[5][5],int position,square_ptr square)
{
  int i,j;
  pentomino_ptr new_pent = (pentomino_ptr)malloc(sizeof(struct pentomino));
  for (i = 0;i < 4;i++){
    for(j = 0;j < 4;j++){
      new_pent->array_pent[i][j] = array_pent[i][j];
    }
  }
  new_pent->position = position;
  return new_pent;
}

void draw_pentomino(pentomino_ptr pentomino,SDL_Surface *square_sprite,SDL_Surface *background)
{
  int i ;
  for(i=0;i<5;i++){
    draw_square(pentomino->square[i],square_sprite,background);
   
  }
}


pentomino_ptr mirror(pentomino_ptr pentomino){
  int i;
  int min = 2000;
  int max = 0;
  for (i = 0;i < 5;i++){
    if (pentomino->square[i]->rcSrc.x<min){
      min = pentomino->square[i]->rcSrc.x;
    }
  }
  for (i = 0;i < 5;i++){
    if (pentomino->square[i]->rcSrc.x == min){
      pentomino->square[i]->rcSrc.x = pentomino->square[i]->rcSrc.x + SIZE_SQUARE *4;
    }
    if (pentomino->square[i]->rcSrc.x == min + SIZE_SQUARE){
      pentomino->square[i]->rcSrc.x = pentomino->square[i]->rcSrc.x + SIZE_SQUARE * 2;
    }
    if (pentomino->square[i]->rcSrc.x == min + 3 * SIZE_SQUARE){
      pentomino->square[i]->rcSrc.x = pentomino->square[i]->rcSrc.x - SIZE_SQUARE * 2; 
    }
    if (pentomino->square[i]->rcSrc.x == min + 4 * SIZE_SQUARE){
      pentomino->square[i]->rcSrc.x = pentomino->square[i]->rcSrc.x - SIZE_SQUARE * 4; 
    }      
  }
  return pentomino;
}

pentomino_ptr create(int x, int y, FILE *file){
  int i,j,find = 0;
  char line[5];
  SDL_Rect rcSrc,rcSprite;
  pentomino_ptr pentomino = (pentomino_ptr)malloc(sizeof(struct pentomino));
  file = fopen("test.txt","r");
  while(find == 0){
    fgets(line,5,file);
    for(i = 0;i < 5;i++){
      if(line[i] == '#'){
	find = 1 ;
      }
    }
  }
  int nb_square = 0;
  while (nb_square < 5){
    i=0;
    while(i<5){
      j=0;
      while(j<5){
	if (pentomino->array_pent[i][j] == '#'){
	  rcSrc.x = x+j*SIZE_SQUARE;
	  rcSrc.y = y+i*SIZE_SQUARE;
	  rcSprite.x = 0 ;
	  rcSprite.y = 0 ;
	  rcSprite.w = 30 ;
	  rcSprite.h = 30 ;
	  pentomino->square[nb_square]=new_square(rcSrc,rcSprite);
	  printf("x %d\n",pentomino->square[nb_square]->rcSrc.x);
	  nb_square++;
	  printf("+1\n");
	  j++;
	}
	i++;
      }
    }
  }
  return pentomino;
}


// fonctionne tant que i<4 et j<5...
pentomino_ptr shape (int x, int y, FILE *file)
{
  pentomino_ptr pentomino = (pentomino_ptr)malloc(sizeof(struct pentomino));
  char line[5];
  int find,i,j,nb_square = 0;
  SDL_Rect rcSrc,rcSprite;

  // search the first #
  while (!find){
    fgets(line,MAXP,file);
    for (i = 0;i < 5;i++){
      if (line[i] == '#'){
	find = 1;
      }
    }
  }
  // put the first line of # in the array
  for (i=0;i<5;i++){
    pentomino->array_pent[i][0] = line[i];
  }
  // put all the rest of # in the array on 4 lines (pentomino 5*5 max)
  for (j=1;j<5;j++){
    fgets(line,MAXP,file);
    for (i=0;i<5;i++){
      pentomino->array_pent[i][j] = line[i];
    }
  }
  j=0;
  // while there isn't 5 squares for the pentomino
  while (nb_square < 5){
    for (j=0;j<5;j++){
      if(nb_square < 5){
	for (i=0;i<5;i++){
	  // create a square if we find a '#' in the array
	  if (pentomino->array_pent[i][j] == '#' && nb_square < 5){
	    // position of the square in x
	    rcSrc.x = x + i*SIZE_SQUARE;
	    printf("rcSrc.x = %d et i = %d\n",rcSrc.x,i);
	    // position of the square in y (boucle for wan't begin with j=0 so I use j-1 to have the good position)
	    rcSrc.y = y + (j-1)*SIZE_SQUARE;
	    printf("rcSrc.y  = %d et j = %d\n",rcSrc.y,j);
	    // position et dimensions of the square in the .bmp
	    rcSprite.x = 0 ;
	    rcSprite.y = 0 ;
	    rcSprite.w = 30 ;
	    rcSprite.h = 30 ;
	    // create the square
	    pentomino->square[nb_square]= new_square(rcSrc,rcSprite);
	    nb_square++;
	    printf("+1\n");
	  }
	}
      }
    }
  }  
  return pentomino;
}
	
void file_array(char array_file[1000],FILE *file){
  int i = 0;
  char array_temp[100] = "";
  while(fgets(array_temp,100,file) != NULL){
    strcat(array_file,array_temp);
    i++;
  }
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
  return i;
}

int nb_pent(char array_file[1000]){
  int nb_pent,nb_square,i;
  nb_pent = 0;
  nb_square = 0;
  i = begin_pent(array_file);
  for (i;i<1000;i++){
    if(array_file[i]=='#'){
      nb_square++;
    }else if(array_file[i]='\n' && array_file[i+1]=='\n' && nb_square %5 ==0){
      nb_pent++;
    }
  }
  return nb_pent;
}


int new_array(char array_file[1000],int pos_file,int position,int x,int y,char array_pent[5][5]){
  int i,j,Nb_square=0;
  for(i=0;i<5;i++){
    for(j=0;j<5;j++){
      array_pent[i][j] = 'o';
    }
  }
  i = 0;
  j = 0;
  while(Nb_square<5){
    if (array_file[pos_file] ==' '){
      j++;
    }else if(array_file[pos_file] == '#'){
      array_pent[i][j] = '#';
      j++;
    } else {
      i++;
      j = 0;
    }
    pos_file++ ;
  }
  return pos_file;
}

bool test_pento(char array_file[1000]){
  int area = size_area(array_file);
  int nb_pento = nb_pent(array_file);
  return area % nb_pento == 0;
}

/*maybe move it to area.c*/

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
