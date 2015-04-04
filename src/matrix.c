#include "../include/parser.h"
#include "matrix.h"
#include <stddef.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int
matrix_load(tmatrix_t *matrix,
            char *filename)
{
	if (get_row_and_column(filename, matrix) != READ_FILE_OK) {
		return 0;
	}

	create_matrix(matrix);

	if (convert_file_to_matrix(filename, matrix) != READ_FILE_OK) {
		return 0;
	}

	return 1;
}

void
matrix_create(tmatrix_t *matrix,
		      const int num_rows,
			  const int num_cols)
{
	matrix->rows = num_rows;
	matrix->columns = num_cols;
	create_matrix(matrix);
}

void
matrix_multiply_concurrently(const tmatrix_t multiplicand,
		                     const tmatrix_t multiplier,
			                 const size_t num_processes,
			                 tmatrix_t *product)
{
	pid_t pids[num_processes];
	size_t p;
	int pipefds[num_processes][2];
	tmatrix_t multiplicand_stripes[num_processes];
	tmatrix_t product_stripes[num_processes];

	matrix_split_into_stripes(multiplicand, num_processes,
			multiplicand_stripes);

	for (p = 0; p != num_processes; p++) {
		pid_t pid;

		pipe(pipefds[p]);
		pid = fork();
		if (pid == 0) {
			tmatrix_t product_stripe;

			matrix_create(&product_stripe, multiplicand_stripes[p].rows,
					multiplier.columns);

			matrix_multiply(multiplicand_stripes[p], multiplier,
					&product_stripe);

            close(pipefds[p][0]);
			matrix_write_through_pipe(pipefds[p], &product_stripe);

			exit(0);
		} else {
			pids[p] = pid;
		}
	}

	for (p = 0; p != num_processes; p++) {
		close(pipefds[p][1]);
		matrix_read_through_pipe(pipefds[p], &product_stripes[p]);

		waitpid(pids[p], NULL, 0);
	}

	matrix_join_stripes(product_stripes, num_processes, product);
}

void
matrix_write_through_pipe(int pipefd[2],
		                  tmatrix_t *matrix)
{
	size_t r;
	size_t c;

	write(pipefd[1], &(matrix->rows),
			sizeof(matrix->rows));

	write(pipefd[1], &(matrix->columns),
			sizeof(matrix->columns));

	for (r = 0; r != matrix->rows; r++) {
		for (c = 0; c != matrix->columns; c++) {
			write(pipefd[1], &(matrix->matrix[r][c]),
					sizeof(matrix->matrix[r][c]));
		}
	}
}

void
matrix_read_through_pipe(int pipefd[2],
		                 tmatrix_t *matrix)
{
	size_t r;
	size_t c;
	int num_rows;
	int num_cols;

	read(pipefd[0], &num_rows,
			sizeof(matrix->rows));

	read(pipefd[0], &num_cols,
			sizeof(matrix->columns));

	matrix_create(matrix, num_rows, num_cols);

	for (r = 0; r != matrix->rows; r++) {
		for (c = 0; c != matrix->columns; c++) {
			read(pipefd[0], &(matrix->matrix[r][c]),
				sizeof(matrix->matrix[r][c]));
		}
	}
}

void
matrix_multiply(const tmatrix_t multiplicand,
		        const tmatrix_t multiplier,
				tmatrix_t *product)
{
	size_t r;
	size_t c;
	size_t k;

	for (r = 0; r != multiplicand.rows; r++) {
		for (c = 0; c != multiplier.columns; c++) {
			product->matrix[r][c] = 0;
			for (k = 0; k != multiplicand.columns; k++) {
				product->matrix[r][c] +=
					multiplicand.matrix[r][k] * multiplier.matrix[k][c];
			}
		}
	}
}

void
matrix_join_stripes(const tmatrix_t *stripes,
                    const size_t num_stripes,
		            tmatrix_t *matrix)
{
	size_t i;
	size_t s;
	size_t r;
	size_t c;

	i = 0;
	for (s = 0; s != num_stripes; s++) {
		for (r = 0; r != stripes[s].rows; r++) {
			for (c = 0; c != stripes[s].columns; c++) {
				matrix->matrix[i][c] = stripes[s].matrix[r][c];
			}
			i++;
		}
	}
}

void
matrix_split_into_stripes(const tmatrix_t matrix,
                          const size_t num_stripes,
						  tmatrix_t *stripes)
{
	size_t stripes_num_rows[num_stripes];
	size_t s;
	size_t r;

	matrix_compute_equal_sized_stripes(matrix, num_stripes,
			stripes_num_rows);

	for (s = 0; s != num_stripes; s++) {
		matrix_create(&stripes[s], stripes_num_rows[s], matrix.columns);
	}

	r = 0;
	for (s = 0; s != num_stripes; s++) {
		matrix_get_stripe(r, stripes_num_rows[s], matrix, &stripes[s]);
		r += stripes_num_rows[s];
	}
}

void
matrix_compute_equal_sized_stripes(const tmatrix_t matrix,
								   const size_t num_stripes,
							       size_t *stripes_num_rows)
{
	size_t s;

	for (s = 0; s != num_stripes; s++) {
		stripes_num_rows[s] = 0;
	}

	for (s = 0; s != num_stripes; s++) {
		stripes_num_rows[s] +=	matrix.rows / num_stripes;
	}

	for (s = 0; s != matrix.rows % num_stripes; s++) {
		stripes_num_rows[s]++;
	}
}

void
matrix_get_stripe(const int first_row,
		          const size_t num_rows,
				  const tmatrix_t matrix,
				  tmatrix_t *stripe)
{
	size_t r;
	size_t i;
	size_t c;

	i = 0;
	for (r = first_row; r != first_row + num_rows; r++) {
		for (c = 0; c != matrix.columns; c++) {
			stripe->matrix[i][c] = matrix.matrix[r][c];
		}
		i++;
	}
}
