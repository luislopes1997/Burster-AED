#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "midterm.h"

/*
Direction:
0 - top
1 - right
2 - bottom
3 - left
*/

int TwoDToOneD(int x, int y, int n) {
	return x*n+y;
}

void calculateCluster(int **matrix, int rows, int cols, int x, int y, int element, int *score, int *visited) {
	if(x > (rows - 1)  || x < 0 || y > (cols - 1) || y < 0 || element == -1) return;
	visited[TwoDToOneD(x,y,cols)] = 1;
	(*score)++;
	if((x-1) >= 0 && matrix[x-1][y] == element && visited[TwoDToOneD(x-1,y,cols)] == 0) {
		calculateCluster(matrix, rows, cols, x-1, y, element, score, visited);
	}

	if((y+1) < cols && matrix[x][y+1] == element && visited[TwoDToOneD(x,y+1,cols)] == 0) {
		calculateCluster(matrix, rows, cols, x, y+1, element, score, visited);
	}

	if(x+1 < rows && matrix[x+1][y] == element && visited[TwoDToOneD(x+1,y,cols)] == 0) {
		calculateCluster(matrix, rows, cols, x+1, y, element, score, visited);
	}

	if((y-1) >= 0 && matrix[x][y-1] == element && visited[TwoDToOneD(x,y-1,cols)] == 0) {
		calculateCluster(matrix, rows, cols, x, y-1, element, score, visited);
	}
	return;
}

void removeCluster(int **matrix, int rows, int cols, int x, int y, int element, int *visited, int *empty) {
	if(x > (rows - 1)  || x < 0 || y > (cols - 1) || y < 0 || element == -1) return;


	visited[TwoDToOneD(x,y,cols)] = 1;
	matrix[x][y] = -1; /*remove item*/
	empty[y]++;


	if((x-1) >= 0 && matrix[x-1][y] == element && visited[TwoDToOneD(x-1,y,cols)] == 0) {
		removeCluster(matrix, rows, cols, x-1, y, element, visited, empty);
	}

	if((y+1) < cols && matrix[x][y+1] == element && visited[TwoDToOneD(x,y+1,cols)] == 0) {
		removeCluster(matrix, rows, cols, x, y+1, element, visited, empty);
	}

	if(x+1 < rows && matrix[x+1][y] == element && visited[TwoDToOneD(x+1,y,cols)] == 0) {
		removeCluster(matrix, rows, cols, x+1, y, element, visited, empty);
	}

	if((y-1) >= 0 && matrix[x][y-1] == element && visited[TwoDToOneD(x,y-1,cols)] == 0) {
		removeCluster(matrix, rows, cols, x, y-1, element, visited, empty);
	}
	return;
}

void fixPuzzle(int **matrix, int rows, int cols) {
	int tmp = 0, i,j,n;
	for(i = 0; i < cols; i++) {
		for(j = 0; j < rows-1; j++) {
			if(matrix[j][i] != -1 && matrix[j+1][i] == -1) {
				for(n = j+1; n > 0; n--) {
					tmp = matrix[n][i];
					matrix[n][i] = matrix[n-1][i];
					matrix[n-1][i] = tmp;
				}
			}
		}
	}
}

void shiftMatrix(int **matrix, int rows, int y) {
	int tmp = 0, i, j;
	
	for(i = y; i > 0; i--) {
		for(j = 0; j < rows; j++) {
			tmp = matrix[j][i];
			matrix[j][i] = matrix[j][i-1];
			matrix[j][i-1] = tmp;
		}
	}
}

