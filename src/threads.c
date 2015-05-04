/*
Names:FELIPE BUENO DA ROSA
      MILLER BIAZUS
      PEDRO HENRIQUE FROZI DE CASTRO E SOUZA

Operating Systems 2 - Prof Alberto
THREADS
*/

//#define _GNU_SOURCE
#include "../include/threads.h"

int setup(int nthr){
        
    pthread_t *tid;
    
    matrix_in1 = (tmatrix_t*)malloc(sizeof(tmatrix_t));
    matrix_in2 = (tmatrix_t*)malloc(sizeof(tmatrix_t));
    matrix_result = (tmatrix_t*)malloc(sizeof(tmatrix_t));
    
    if(get_row_and_column(FILE_IN1, matrix_in1) != READ_FILE_OK){
        
        printf("Erro ao ler header do arquivo in1.");
        return SETUP_ERROR;
    }
	if(get_row_and_column(FILE_IN2, matrix_in2) != READ_FILE_OK){
        
        printf("Erro ao ler  header do arquivo in2.");
        return SETUP_ERROR;
        
    }
    
    if(matrix_in1->rows != matrix_in2->columns){
        printf("Quantidade de linhas em in1 diferente da quantidade de colunas em in2.");
        return SETUP_ERROR;
    }
    
    
    matrix_result->rows = matrix_in1->rows;
    matrix_result->columns = matrix_in2->columns;
    
    create_matrix(matrix_in1);
    create_matrix(matrix_in2);
        
    create_matrix(matrix_result);
    
    int i,j;
    for(i=0;i<matrix_result->rows;i++){
        for(j=0;j<matrix_result->columns;j++){
            matrix_result->matrix[i][j]=0;
        }
    }
        
    int ret;
    ret = convert_file_to_matrix(FILE_IN1, matrix_in1);
    
    if (ret != READ_FILE_OK){
        switch(ret){
            case READ_FILE_ERROR:{
                printf("Erro ao abrir arquivo in1."); 
                break;
            }
            case READ_COLUMNS_ERROR:{
                printf("Erro ao ler colunas da matrix in1."); 
                break;
            }
            case READ_ROWS_ERROR:{
                printf("Erro ao ler linhas da matrix in1."); 
                break;
            }
            default:{
                printf("Erro desconhecido ao ler matrix in1."); 
                break;
            }
        }
        
        return SETUP_ERROR;
    }
    //print_matrix(matrix_in1);
    
    ret = convert_file_to_matrix(FILE_IN2, matrix_in2);
    if (ret != READ_FILE_OK){
        switch(ret){
            case READ_FILE_ERROR:{
                printf("Erro ao abrir arquivo in2."); 
                break;
            }
            case READ_COLUMNS_ERROR:{
                printf("Erro ao ler colunas da matrix in2."); 
                break;
            }
            case READ_ROWS_ERROR:{
                printf("Erro ao ler linhas da matrix in2."); 
                break;
            }
            default:{
                printf("Erro desconhecido ao ler matrix in2."); 
                break;
            }
        }
        
        return SETUP_ERROR;
    }
    //print_matrix(matrix_in2);
    
    
    //printf("\n\nIniciando execucao - algoritmo calculate_rowsset...\n");
    startClock = clock();
    
    tid = (pthread_t *)malloc(sizeof(pthread_t)*nthr);
    
    
    nThreads = nthr;
    
    int idx_threads[nthr];
    for (i = 0; i < nthr; i++){
        idx_threads[i] = i;
        pthread_create(&tid[i], NULL,(void*) calculate_rowsset, &idx_threads[i]);
    }
    
    for (i = 0; i < nthr; i++){
        pthread_join(tid[i], NULL);
    }
    
    endClock = clock();
    
    // printf("\n\tQuantidade de threads: %d", nthr);
    // printf("\n\tTempo de execucao: %f segundos",((float)endClock-startClock)/CLOCKS_PER_SEC);
    
    // print_matrix(matrix_result);
    /*
    export_report(FILE_REPORT
                  , 'T'
                  , matrix_in1->rows
                  , matrix_in1->columns
                  , matrix_in2->rows
                  , matrix_in2->columns
                  , matrix_result->rows
                  , matrix_result->columns
                  , nthr
                  , ((float)endClock-startClock)/CLOCKS_PER_SEC);
    */
    if(export_file(matrix_result, OUTPUT_FILE_NAME)!=EXPORT_OK){
        
        printf("Erro ao realizar a exportacao da matrix resultante.");
        return SETUP_ERROR;
    }
    
    return SETUP_OK;
}




