#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define READ_FILE_ERROR 0
#define READ_FILE_OK 1

#define READ_COLUMNS_ERROR 2
#define READ_ROWS_ERROR 3

#define EXPORT_ERROR    1
#define EXPORT_OK       0

#define FILE_MODE_READ "r"
#define FILE_MODE_WRITE "w"
#define FILE_MODE_APPEND "a+"

#define FILE_IN1 "in1.txt"
#define FILE_IN2 "in2.txt"

#define FILE_REPORT "../report.txt"


#define OUTPUT_FILE_NAME "out.txt"

typedef struct tmatrix
{
    int   rows;
    int   columns;
    int   **matrix;
}tmatrix_t;


//int number_of_columns;//chamar metodo tambem
//int number_of_rows;//chamar metodo paraler esse valor

//int get_row_and_column(char *file1, char *file2);

tmatrix_t *matrix_in1, *matrix_in2, *matrix_result;
int nThreads;

void create_matrix(tmatrix_t *matrix_in);

int get_row_and_column(char *file, tmatrix_t *matrix_in);
int convert_file_to_matrix(char *filename, tmatrix_t *matrix_in);
int print_matrix(tmatrix_t *matrix_in);

int export_file(tmatrix_t *matrix, char *filename);
int export_report(char *report, char type
                  , int rows_in1
                  , int columns_in1
                  , int rows_in2
                  , int columns_in2
                  , int rows_out
                  , int columns_out
                  , int cores
                  , float time);

void *calculate_first();
void *calculate_rowsset(int *arg);