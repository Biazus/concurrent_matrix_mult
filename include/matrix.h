#ifndef MATRIX_H
#define MATRIX_H

#include "parser.h"
#include <stddef.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int
matrix_load(tmatrix_t *matrix,
            char * filename);

void
matrix_create(tmatrix_t *matrix,
		      const int num_rows,
			  const int num_cols);

void
matrix_multiply_concurrently(const tmatrix_t multiplicand,
                             const tmatrix_t multiplier,
			                 const size_t num_processes,
			                 tmatrix_t *product);

void
matrix_write_through_pipe(int pipefd[2],
		                  tmatrix_t *matrix);

void
matrix_read_through_pipe(int pipefd[2],
		                 tmatrix_t *matrix);

void
matrix_multiply(const tmatrix_t multiplicand,
		        const tmatrix_t multiplier,
				tmatrix_t *product);

void
matrix_join_stripes(const tmatrix_t *stripes,
                    const size_t num_stripes,
		            tmatrix_t *matrix);

void
matrix_split_into_stripes(const tmatrix_t matrix,
		                  const size_t num_stripes,
                          tmatrix_t *stripes);
void
matrix_compute_equal_sized_stripes(const tmatrix_t matrix,
		                           const size_t num_stripes,
							       size_t *stripes_num_rows);
void
matrix_get_stripe(const int first_row,
		          const size_t num_rows,
				  const tmatrix_t matrix,
				  tmatrix_t *stripe);

#endif
