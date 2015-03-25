#include <stdio.h>
#include <pthread.h>

int g;

void *calculate(void *arg) {
    int i, n = *(int *) arg;
    for(i = 0; i < n; i++)
        g = i;
}

void *do_it_2(void *arg) {
    int i, n = *(int *) arg;
    for(i = 0; i < n; i++)
        printf("%d\n", g);
}

int main( int argc, char **argv) {
    pthread_t th1, th2;
    pthread_t *tid;
    int n = 10;
    int nthr = 0, i=0; //numero de threads a serem criadas (param)
    for (i = 0; i < nthr; i++)
       pthread_create(&tid[i], NULL, calculate, &n);

//    pthread_create(&th1, NULL, do_it_1, &n);
//    pthread_create(&th2, NULL, do_it_2, &n);
	
	printf("acabando...\n");
}
