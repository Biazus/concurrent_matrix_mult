#include "../include/threads.h"

int main(int argc, char **argv) {
    int nthr = 0;
    
    if(argc>1){
        nthr = atoi(argv[1]);
        
        printf("Numero de threads: %d", nthr);
    }
    else {
        printf("Digite o numero de threads: ");
        scanf("%d", &nthr);
    }
    
    if(setup(nthr)!=SETUP_OK){
        printf("\n\nO programa foi encerrado com erros.\n");
    }
    else {
        printf("\n\nO programa foi executado com sucesso!\n");
    }
    
    return 1;
}
