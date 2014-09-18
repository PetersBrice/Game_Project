#include <stdlib.h>
#include <stdio.h>

int main(){
  FILE *file ;
  char Ligne1 [10], Ligne2 [10], Ligne3 [10], Ligne4 [10] ;
  int i;
  file = fopen ("pentomino.txt","w+t") ;
  rewind (F) ;
  if (file == NULL) {
    printf ("fail to open pentomino.txt\n") ;
    system ("pause") ;
    return 1 ;
  }
  //write

  //vidage du tampon avant les léctures a venir
  ffluch(file);

  //read
  rewind (F) ;
  fgets (Ligne1,9,file) ;
  fgets (Ligne2,9,file) ;
  fgets (Ligne3,9,file) ;
  fgets (Ligne4,9,file) ;  
}
  
