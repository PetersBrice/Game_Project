#ifndef FILE_H
#define FILE_H
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int file_array(char array_file[1000],FILE *file);

int begin_pent (char array_file[1000]);

int nb_pent(char array_file[1000], int array_end);

int size_area(char array_file[1000]);

#endif




