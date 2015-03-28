#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int number_of_columns;//chamar metodo tambem
int number_of_rows;//chamar metodo paraler esse valor

int get_row_and_column(char *file1, char *file2);
int convert_file_to_c(char *filename, int row, int col, int matrix[row][col]);
