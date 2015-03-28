#include "../include/parser.h"

int convert_file_to_c(char *filename, int row, int col, int matrix[row][col]){
    FILE *input;
    char *mode = "r", *line = NULL;
    char* token=NULL; //auxiliar para capturar cada valor de col da matriz
    char* line_copy=NULL;  //copia a string da linha pois strtok modifica a string
    size_t len = 0;
    ssize_t read;
    int row_counter=0, col_counter=0;
    input=fopen(filename, mode);
    if (input==NULL){
	printf("Erro ao ler arquivo\n");
        return 0;
    }
    
    //para pegar as duas primeiras linhas que nao sao importantes aqui    
    read = getline(&line, &len, input);
    read = getline(&line, &len, input);

    //lê a linha do arquivo
    while((read = getline(&line, &len, input)) != -1){
	line_copy = strdup(line);//copia para nova string
	token = strtok(line_copy, " ");
	while(token!=NULL){
	    matrix[row_counter][col_counter]=atoi(token);
		
	    token = strtok(NULL, " ");
	    col_counter+=1;
	}
	row_counter+=1;
        col_counter=0;

	if(line_copy)
	    free(line_copy);
	
    }
	int i=0,j=0;
    
    //print na matriz para debug
    printf("\nMATRIZ:\n");
    for(i=0;i<row;i++){
	for (j=0;j<col;j++)
		printf("%d\t", matrix[i][j]);
        printf("\n");
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