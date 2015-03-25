#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int g;

void *calculate(void *arg) {
    int i, n = *(int *) arg;
    for(i = 0; i < n; i++){
        g = i;
            sleep(30);
        printf("over\n");
    }
}

/*void *do_it_2(void *arg) {
    int i, n = *(int *) arg;
    for(i = 0; i < n; i++)
        printf("%d\nhaushe", g);
}
*/
int main( int argc, char **argv) {
//    pthread_t th1, th2;
    pthread_t *tid;
    int n = 10;
    int nthr = 1, i=0; //numero de threads a serem criadas (param)
    tid = (pthread_t *)malloc(sizeof(pthread_t)*nthr);
    for (i = 0; i < nthr; i++){
       pthread_create(&tid[i], NULL,(void*) calculate, &n);
      }
    for (i = 0; i < nthr; i++)
       pthread_join(tid[i], NULL);
	
	printf("acabando...\n");
}
