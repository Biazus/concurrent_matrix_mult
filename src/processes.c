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

	matrix_create(&product, multiplicand.rows, multiplier.columns);

    matrix_multiply_concurrently(multiplicand, multiplier, nthr, &product);
    
    if(export_file(&product, OUTPUT_FILE_NAME)!=EXPORT_OK){
        
        printf("Erro ao realizar a exportacao da matrix resultante.");
        return SETUP_ERROR;
    }
    
	return SETUP_OK;
}
