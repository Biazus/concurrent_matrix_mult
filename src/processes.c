/*
Names:FELIPE BUENO DA ROSA
      MILLER BIAZUS
      PEDRO HENRIQUE FROZI DE CASTRO E SOUZA

Operating Systems 2 - Prof Alberto
THREADS
*/
#include "../include/processes.h"

int
setup(int nthr)
{
	tmatrix_t multiplicand;
	tmatrix_t multiplier;
	tmatrix_t product;

	if (!matrix_load(&multiplicand, FILE_IN1)) {
		return SETUP_ERROR;
	}

	if (!matrix_load(&multiplier, FILE_IN2)) {
		return SETUP_ERROR;
	}
    
    startClock = clock();
	matrix_create(&product, multiplicand.rows, multiplier.columns);

    matrix_multiply_concurrently(multiplicand, multiplier, nthr, &product);
    endClock = clock();
    
    if(export_file(&product, OUTPUT_FILE_NAME)!=EXPORT_OK){
        
        printf("Erro ao realizar a exportacao da matrix resultante.");
        return SETUP_ERROR;
    }
    
    export_report(FILE_REPORT
                  , 'P'
                  , multiplicand.rows
                  , multiplicand.columns
                  , multiplier.rows
                  , multiplier.columns
                  , product.rows
                  , product.columns
                  , nthr
                  , ((float)endClock-startClock)/CLOCKS_PER_SEC);
    
	return SETUP_OK;
}
