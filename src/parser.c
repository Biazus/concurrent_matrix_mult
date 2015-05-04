#include "../include/parser.h"

int convert_file_to_matrix(char *filename, tmatrix_t *matrix_in){
    
    FILE *input;
    char *line = NULL;
    char* token=NULL; //auxiliar para capturar cada valor de col da matriz
    char* line_copy=NULL;  //copia a string da linha pois strtok modifica a string
    size_t len = 0;
    ssize_t read;
    int row_counter=0, col_counter=0;
    input=fopen(filename, FILE_MODE_READ);
    
    if (input==NULL){
        return READ_FILE_ERROR;
    }
    
    //para pegar as duas primeiras linhas que nao sao importantes aqui    
    read = getline(&line, &len, input);
    read = getline(&line, &len, input);

    //lê a linha do arquivo
    while((read = getline(&line, &len, input)) != -1){
        line_copy = strdup(line);//copia para nova string
        token = strtok(line_copy, " ");
        while(token!=NULL){
            matrix_in->matrix[row_counter][col_counter]=atoi(token);

            token = strtok(NULL, " ");
            col_counter++;
        }
        
        if(col_counter-1>matrix_in->columns){
            printf("  %d %d  ",col_counter,matrix_in->columns);
            return READ_COLUMNS_ERROR;
        }
        
        row_counter++;
        col_counter=0;

        if(line_copy){
            free(line_copy);
        }
	
    }
    
    if(row_counter!=matrix_in->rows){
        return READ_ROWS_ERROR;
    }
	
    fclose(input);
    
    if(line){
        free(line);
    }
    
    return READ_FILE_OK;

}

int print_matrix(tmatrix_t *matrix_in){
 
    int i=0,j=0;
    
    //print na matriz para debug
    printf("\nMATRIZ:\n");
    for(i=0;i<matrix_in->rows;i++){
	for (j=0;j<matrix_in->columns;j++)
		printf("%d\t", matrix_in->matrix[i][j]);
        printf("\n");
    }
}

int get_row_and_column(char *file, tmatrix_t *matrix_in){

    FILE *input;
    ssize_t read;
    char *line = NULL;
    char trash[20];//variavel para guardar "lixo" do tipo (LINHAS = ) e (COLUNAS =)
    size_t len = 0;
    
    int read_rows, read_columns;

    input = fopen(file, "r");
    if (input==NULL){
        return READ_FILE_ERROR;
    }
    
    read = getline(&line, &len, input);
    sscanf(line, "%s %*s %d",trash,  &read_rows);
    read = getline(&line, &len, input);
    sscanf(line, "%s %*s %d",trash,  &read_columns);
    
    matrix_in->rows = read_rows;
    matrix_in->columns = read_columns;
    
    if(line){
        free(line);
    }
    
    fclose(input);
    
    return READ_FILE_OK;
    
}

void create_matrix(tmatrix_t *matrix_in){
    
    int i=0;
    matrix_in->matrix = (int**)malloc(sizeof(int*)*matrix_in->rows);
    for(i;i<matrix_in->rows;i++){
        matrix_in->matrix[i] = (int*)malloc(sizeof(int)*matrix_in->columns);
    }
}


void *calculate_first() {
    
    int find = 0;
    int i,j,k;
    
    while(1){
        
        for(i=0;i<matrix_result->rows;i++){
            for(j=0;j<matrix_result->columns;j++){
                if(matrix_result->matrix[i][j]==-1){
                    find = !find;
                    break;
                }
            }
            if(find) break;
        }
        
        if(!find){
            break;
        }
        else{
            find = !find;
        }
        
        matrix_result->matrix[i][j] = 0;
        for(k=0;k<matrix_in1->columns;k++){
                matrix_result->matrix[i][j]+=matrix_in1->matrix[i][k]*matrix_in2->matrix[k][j];
        }
    }
        

}


void *calculate_rowsset(int *arg){
    
    int idx = (int)*arg;
    int i,j,k;
    
    int lin_a, col_a;
    printf("n%d\n",idx);
    
    /*
    for(i=idx;i<matrix_in1->rows;i=i+nThreads){
        for(j=0;j<matrix_in2->columns;j++){
            for(k=0;k<matrix_in1->columns;k++){
                    matrix_result->matrix[i][j]+=matrix_in1->matrix[i][k]*matrix_in2->matrix[k][j];
            }
        }
    }
    */
    for(i=idx;i<matrix_result->rows*matrix_result->columns;i=i+nThreads){
        
        lin_a = i / matrix_in2->columns;
        col_b = i % matrix_in2->columns;
        
        for(k=0;k<matrix_in1->columns;k++){
            matrix_result->matrix[lin_a][col_b]+=matrix_in1->matrix[lin_a][k]*matrix_in2->matrix[k][col_b];
        }
    }
    
}

int export_file(tmatrix_t *matrix, char *filename){

    int i=0;
    FILE *pfile = fopen(filename, FILE_MODE_WRITE);
    
    if(pfile == NULL){
        return EXPORT_ERROR;
    }
    fprintf(pfile, "LINHAS = %d\nCOLUNAS = %d\n",matrix->rows,matrix->columns);
    
    for(i;i<matrix->rows;i++){
        
        int j=0;
        for(j;j<matrix->columns;j++){
            fprintf(pfile,"%d ",matrix->matrix[i][j]);
        }
        
        fprintf(pfile,"\n");
    }
    
    fclose(pfile);
    
    return EXPORT_OK;
}

int export_report(char *report
                  , char type
                  , int rows_in1
                  , int columns_in1
                  , int rows_in2
                  , int columns_in2
                  , int rows_out
                  , int columns_out
                  , int cores
                  , float time){

    int i=0;
    FILE *pfile = fopen(report, FILE_MODE_APPEND);
    
    if(pfile == NULL){
        return EXPORT_ERROR;
    }
    fprintf(pfile, "%c \t ", type);
    fprintf(pfile, "%d \t ", rows_in1);
    fprintf(pfile, "%d \t ", columns_in1);
    fprintf(pfile, "%d \t ", rows_in2);
    fprintf(pfile, "%d \t ", columns_in2);
    fprintf(pfile, "%d \t ", rows_out);
    fprintf(pfile, "%d \t ", columns_out);
    fprintf(pfile, "%d \t ", cores);
    fprintf(pfile, "%3.5f\n" , time);
    
    fclose(pfile);
    
    return EXPORT_OK;
}


