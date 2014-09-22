/********************************************/
/* Decolle Anais - Peters Brice             */
/* manip_text.c                             */
/* The program read, write, modify a text.  */
/********************************************/

#include <stdio.h>
#include <stdlib.h>


int main(void)
{
  FILE *file;
  char line [512];

  // open the file
  file = fopen("Graou.txt","w+t");

  // verification of the open success
  if (file == NULL){
    printf("Fail open file\n");
    system("pause");
    return 1;
  }

  // write in the file
  fprintf(file, "Blplplp\nTest on %d lines",2);

  // read the file
  rewind(file);
  while(fgets(line, 512, file) != NULL){
    printf("\t%s", line);
  }
  printf ("\n");

  // close the file
  if(fclose(file) == EOF){
    printf("Fail close file\n");
    exit(1);
  }

  return 0;
}
