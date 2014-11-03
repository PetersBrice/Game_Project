#include "file.h"

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
