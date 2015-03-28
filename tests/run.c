#include "../include/threads.h"

int main( int argc, char **argv) {
    int nthr = 0;
    printf("Digite o numero de threads: ");
    scanf("%d", &nthr);
    setup(nthr);
    return 1;
}
