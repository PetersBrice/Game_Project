#ifndef FILE_H
#define FILE_H
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*get a table with all the char in the file and return the end of the file*/
int file_array(char array_file[1000],FILE *file);

/*get the pos in the array where the pentomino begin*/
int begin_pent (char array_file[1000]);

/*return the number of pentomino*/
int nb_pent(char array_file[1000], int array_end);

/*return the number of square in the area*/
int size_area(char array_file[1000]);

#endif




