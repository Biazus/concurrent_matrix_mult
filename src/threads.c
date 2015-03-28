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
//    pthread_t th1, th2;
    number_of_columns = 0;//chamar metodo tambem
    number_of_rows = 0;//chamar metodo paraler esse valor
    int n = 10;
    int i=0; //auxiliar para percorrer laço
    pthread_t *tid;
    
    if (!get_row_and_column("../tests/in1.txt", "../tests/in2.txt")){
        return 1;
    }
	
    //alocaçao das matrizes em memoria
    int (*matrix_a)[number_of_columns] = (int(*)[number_of_columns]) malloc(sizeof(int)*number_of_rows*number_of_columns);
    int (*matrix_b)[number_of_rows] = (int(*)[number_of_rows]) malloc(sizeof(int)*number_of_columns*number_of_rows);

	//coloca a primeira matriz de arquivo em memoria
    if (!convert_file_to_c("in1.txt", number_of_rows, number_of_columns, matrix_a)){
	return 0;
    }
	//coloca a segunda matriz de arquivo em memoria
    if (!convert_file_to_c("in2.txt", number_of_columns, number_of_rows, matrix_b)){
	return 0;
    }
    
    tid = (pthread_t *)malloc(sizeof(pthread_t)*nthr);
    for (i = 0; i < nthr; i++){
       pthread_create(&tid[i], NULL,(void*) calculate, &n);
      }
    for (i = 0; i < nthr; i++)
       pthread_join(tid[i], NULL);
	
    printf("\nEncerrando programa...\n");
    return 1;
}
void *calculate(void *arg) {
//Funcao que calcula linha x coluna = TODO
//    int i, n = *(int *) arg;
//    for(i = 0; i < n; i++){
//        g = i;
        printf("teste\n");
//    }

}


