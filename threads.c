/*
Names:FELIPE BUENO DA ROSA
      MILLER BIAZUS
      PEDRO HENRIQUE FROZI DE CASTRO E SOUZA

Operating Systems 2 - Prof Alberto
THREADS
*/


#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int g;
int col;
int current_line = 2;//inicializado com a primeira linha da matriz
int current_column = 0;//primeira coluna da matriz
int number_of_rows = 0;//chamar metodo paraler esse valor
int number_of_columns = 0;//chamar metodo tambem

int convert_file_to_c(char *filename, int row, int col, int matrix[row][col]){
    FILE *input;
    char *mode = "r", *line = NULL;
    size_t len = 0;
    ssize_t read;
    input=fopen(filename, mode);
    if (input==NULL){
	printf("Erro ao ler arquivo\n");
        return 0;
    }
    
    //lê a linha do arquivo
    while((read = getline(&line, &len, input)) != -1){
	//****criar o parser aqui -- TODO
	//printf("Linha de tamanho %zu :\n", read);
        //printf("%s", line);
	//****
    }
	
    fclose(input);
    if(line)
	free(line);
    return 1;

}

int get_row_and_column(char *file1, char *file2){
//Essa funcao basicamente guarda os valores do numero de linhas e colunas especificados nos arquivos,
//e verifica se são consistentes
    int aux_row=0;
    int aux_col=0;
    FILE *input;
    FILE *input2;
    ssize_t read;
    char *line = NULL;
    char trash[20];//variavel para guardar "lixo" do tipo (LINHAS = ) e (COLUNAS =)
    size_t len = 0;

    input = fopen(file1, "r");
    if (input==NULL){
	printf("Erro ao ler arquivo1\n");
        return 0;
    }
    input2 = fopen(file2, "r");
    if (input==NULL){
	printf("Erro ao ler arquivo2\n");
        return 0;
    }
    read = getline(&line, &len, input);
    sscanf(line, "%s %*s %d",trash,  &number_of_rows);
    read = getline(&line, &len, input);
    sscanf(line, "%s %*s %d",trash,  &number_of_columns);
     
    read = getline(&line, &len, input2);
    sscanf(line, "%s %*s %d",trash,  &aux_row);
    read = getline(&line, &len, input2);
    sscanf(line, "%s %*s %d",trash,  &aux_col);

    if(number_of_columns!=aux_row || number_of_rows!=aux_col){
    	printf("\nErro nas dimensoes da matriz\n");
	return 0;
    }
    return 1;
}

void *calculate(void *arg) {
//Funcao que calcula linha x coluna = TODO
//    int i, n = *(int *) arg;
//    for(i = 0; i < n; i++){
//        g = i;
//        printf("teste\n");
//    }
}

int main( int argc, char **argv) {
//    pthread_t th1, th2;
    pthread_t *tid;
    int n = 10;
    int nthr = 0; //numero de threads a serem criadas (param)
    printf("Digite o numero de threads: ");
    scanf("%d", &nthr);
    int i=0; //auxiliar para percorrer laço
    if (!get_row_and_column("in1.txt", "in2.txt")){
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
}
