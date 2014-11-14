#include "file.h"

/*get a table with all the char in the file and return the end of the file*/
int file_array(char array_file[1000],FILE *file) 
{
  int i = -1;
  while(!feof(file) && i++<1000) {
    /*put one char on the file*/
    array_file[i] = (char)fgetc(file);
  }
  return i;
}
/*get the pos in the array where the pentomino begin*/
int begin_pent (char array_file[1000])
{
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

/*return the number of pent*/
int nb_pent(char array_file[1000], int array_end) 
{
  int nb_square,i;
  nb_square = 0;
  i = begin_pent(array_file);
  for (;i<array_end; i++) {
    if (array_file[i]=='#') {
       nb_square++;
    }
  }
  //assert((nb_square/5)*5 == nb_square);
  return nb_square/5;
}

/*return the number of square in the area*/
int size_area(char array_file[1000])
{
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

/*see if there's something else than #*/
bool test_file(char array_file[1000],int array_end)
{
  int nb_square = 0;
  int i;
  bool dim_pento ;
  bool format = true;
  for(i = 0;i < array_end;i++){
    if (!(array_file[i] == '#' || array_file[i] == '\n' || array_file[i] == ' ')){
      format = false;
    }
  }
  for(i = begin_pent(array_file);i < array_end;i++){
    if(array_file[i] == '#'){
    nb_square ++;
    }
  }
  if(nb_square%5 != 0){
    format = false;
  }
  return format;
}
  


