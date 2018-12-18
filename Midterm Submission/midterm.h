#ifndef MIDTERM_H
#define MIDTERM_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum {
	NONE,
	TOP,
	RIGHT,
	BOTTOM,
	LEFT
} Direction;

int TwoDToOneD(int x, int y, int n);

void calculateCluster(int **matrix, int rows, int cols, int x, int y, int element, int *score, int *visited);

void removeCluster(int **matrix, int rows, int cols, int x, int y, int element, int *visited, int *empty);

void fixPuzzle(int **matrix, int rows, int cols);

void shiftMatrix(int **matrix, int rows, int y);

#endif
