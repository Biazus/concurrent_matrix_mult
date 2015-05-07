#include "../include/processes.h"

int main(int argc, char **argv) {
    int nthr = 0;
    
    if(argc>1){
        nthr = atoi(argv[1]);
        
        //printf("Numero de Processos: %d", nthr);
    }
    else {
        printf("Digite o numero de processos: ");
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
