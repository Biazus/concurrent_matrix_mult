#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int g;

int convert_file_to_c(){
    FILE *input;
    char *mode = "r";
    input=fopen("teste.txt", mode);
    if (input==NULL){
	printf("Erro ao ler arquivo\n");
        return 0;
    }
    return 1;

}

void *calculate(void *arg) {
    int i, n = *(int *) arg;
    for(i = 0; i < n; i++){
        g = i;
        printf("over\n");
    }
}

int main( int argc, char **argv) {
//    pthread_t th1, th2;
    pthread_t *tid;
    int n = 10;
    int nthr = 1, i=0; //numero de threads a serem criadas (param)
 
    if (!convert_file_to_c()){
	return 0;
    }
    
    tid = (pthread_t *)malloc(sizeof(pthread_t)*nthr);
    for (i = 0; i < nthr; i++){
       pthread_create(&tid[i], NULL,(void*) calculate, &n);
      }
    for (i = 0; i < nthr; i++)
       pthread_join(tid[i], NULL);
	
	printf("acabando...\n");
}
