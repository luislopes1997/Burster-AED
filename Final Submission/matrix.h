/********************************************************************
 * matrix.h -- Matrix header file                                   *
 ********************************************************************
 * Project: AED project - Burster                    				*
 *                                                                  *
 * Authors: Luís Lopes (ist425416), Miguel Freire (ist425445)  		*
 ********************************************************************/

/* Include guard */
#ifndef MATRIX_H
#define MATRIX_H

typedef struct _Matrix {
	int rows;
	int cols;
	int *empty;
	int **data;
}Matrix;


Matrix *newMatrix(int rows, int cols);

int getNumRows(Matrix *M);

int getNumCols(Matrix *M);

void insertElement(int element, Matrix *M, int row, int col);

void cloneMatrix(Matrix *A, Matrix *B);

void freeMatrix(Matrix *M);

void readMatrixFromFile(Matrix *matrix, FILE *file, int rows, int cols);

#endif