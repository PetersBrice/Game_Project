/********************************************/
/* Decolle Anais                            */
/* PA_1.c                                   */
/* The program read, write, modify a text.  */
/********************************************/

#include <stdio.h>
#include <stdlib.h>


int main (void)
{
  FILE *file;
  int i;
  file = fopen ("Graou.txt","w+t");

  // verification of the open success
  if (file == NULL){
    printf ("Fail open file\n");
    system ("pause");
    return 1;
  }

  // write in the file
  fprintf (file, "Blplplp\nTest on %d lines", 2);

  // read the file
  char line1[100], line2[100];
  fgets (line1, 99, file);
  fgets (line2, 99, file);

  // print of the reading
  for (i=0;i<=99;i++){
    printf ("%d ",line1[i]);
  }


  // close the file
  fclose (file);




  return EXIT_SUCCESS;
}
