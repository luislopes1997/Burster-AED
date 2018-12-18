/********************************************************************
 * matrix.c -- Matrix implementation file                           *
 ********************************************************************
 * Project: AED project - Burster                    				*
 *                                                                  *
 * Authors: Luís Lopes (ist425416), Miguel Freire (ist425445)  		*
 ********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "matrix.h"

/**
 * Creates a new matrix (2D array)
 * @param  rows number of matrix rows
 * @param  cols number of matrix cols
 * @return      pointer to the new matrix
 */
Matrix *newMatrix(int rows, int cols) {
	Matrix *M = (Matrix *) malloc(sizeof(Matrix));

	if(M == NULL) return (Matrix *) NULL;

	M->rows = rows;

	M->cols = cols;

	M->data = (int **) calloc(rows, sizeof(int*));

	M->empty = (int *) calloc(cols, sizeof(int));

	if(M->data == NULL || M->empty == NULL) {
		return (Matrix *) NULL;
	}
	int i;
	for(i = 0; i < rows; i++) {
		M->data[i] = (int *) calloc(cols, sizeof(int));
		if(M->data[i] == NULL) {
			return (Matrix *) NULL;
		}
	}
	
	return M;
}

/**
 * Get's the number of matrix's rows
 * @param  M matrix
 * @return   number of rows
 */
int getNumRows(Matrix *M) {
	if(M == NULL) return 0;

	return M->rows;
}

/**
 * Get's the number of matrix's cols
 * @param  M matrix
 * @return   number of cols
 */
int getNumCols(Matrix *M) {
	if(M == NULL) return 0;

	return M->cols;
}

/**
 * Insert's element in the matrix
 * @param element number to insert
 * @param M       matrix
 * @param row     row number
 * @param col     col number
 */
void insertElement(int element, Matrix *M, int row, int col) {

	if(M == NULL ||
	   (row < 0  || row > getNumRows(M))  ||
	   (col < 0 || col > getNumCols(M)))	return;

	M->data[row][col] = element;

	return; 

}

/**
 * Free's the matrix
 * @param M matrix
 */
void freeMatrix(Matrix *M) {
	int i;
	for(i = 0; i < M->rows; i++) {
		free(M->data[i]);
	}

	free(M->data);
	free(M->empty);
	free(M);
}

/**
 * Clone's matrix A content to matrix B
 * @param A source matrix
 * @param B destination matrix
 */
void cloneMatrix(Matrix *A, Matrix *B) {
	if(A == NULL || B == NULL) return;
	int i,j;
	for(i = 0; i < A->cols; i++){
		B->empty[i] = A->empty[i];
		
		for(j = 0; j < A->rows; j++) {
			B->data[j][i] = A->data[j][i];
		}
	}
}

/**
 * Read's a matrix from file
 * @param matrix matrix
 * @param file   file to read matrix from
 * @param rows   number of matrix's rows
 * @param cols   number of matrix's cols
 */
void readMatrixFromFile(Matrix *matrix, FILE *file, int rows, int cols) {

	int element;
	int i, j;

	for(i = 0; i < rows; i++) {
		for(j = 0; j < cols; j++) {
			if(fscanf(file, "%d", &element) == 1 ) {
				matrix->data[i][j] = element;
			}
			if(element == -1) matrix->empty[j]++;
		}
	}

	return;
}