/********************************************************************
 * matrix.c -- Matrix ADT implementation file                               *
 ********************************************************************
 * Project: AED project - Burster                    				*
 *                                                                  *
 * Authors: Luís Lopes (ist425416), Miguel Freire (ist425445)  		*
 ********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "matrix.h"


Matrix *newMatrix(int rows, int cols) {
	Matrix *M = (Matrix *) malloc(sizeof(Matrix));

	if(M == NULL) return (Matrix *) NULL;

	M->rows = rows;

	M->cols = cols;

	M->data = (int **) malloc(sizeof(int*) * cols * rows);

	if(M->data == NULL) {
		free(M);
		return (Matrix *) NULL;
	}
	int i;
	for(i = 0; i < rows; i++) {
		M->data[i] = (int *) malloc(sizeof(int) * cols);
		if(M->data[i] == NULL) {
			free(M);
			return (Matrix *) NULL;
		}
	}

	return M;
}

int getNumRows(Matrix *M) {
	if(M == NULL) return 0;

	return M->rows;
}

int getNumCols(Matrix *M) {
	if(M == NULL) return 0;

	return M->cols;
}

void insertElement(int element, Matrix *M, int row, int col) {

	if(M == NULL ||
	   (row < 0  || row > getNumRows(M))  ||
	   (col < 0 || col > getNumCols(M)))	return;

	M->data[row][col] = element;

	return; 

}

void freeMatrix(Matrix *M) {
	int i;
	for(i = 0; i < M->rows; i++) {
		free(M->data[i]);
	}

	free(M->data);
	free(M);
}

void printMatrix(Matrix *M) {
	int i, j;
	for(i = 0; i < M->rows; i++) {
		for(j = 0; j < M->cols; j++) {
			printf("|%d", M->data[i][j]);
		}
		printf("|\n");
	}
}

void printMatrixToFile(Matrix *M, FILE* f) {
	int i, j;
	for(i = 0; i < M->rows; i++) {
		for(j = 0; j < M->cols; j++) {
			fprintf(f, "%d", M->data[i][j]);
			if(j < (M->cols-1)) fprintf(f, " ");
		}
		fprintf(f, "\n");
	}
}