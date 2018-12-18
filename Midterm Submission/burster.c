/********************************************************************
 * burster.c -- Main program flow                                   *
 ********************************************************************
 * Project: AED project - Burster                    				*
 *                                                                  *
 * Authors: Luís Lopes (ist425416), Miguel Freire (ist425445)  		*
 ********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "matrix.h"
#include "midterm.h"

#define PUZZLE_FILE_EXTENSION ".puz"
#define SOLUTION_FILE_EXTENSION ".step"
#define MAX_STR_LEN 100

typedef struct _Puzzle {
	int rows;
	int cols;
	int variant;
	Matrix *matrix;
	int r;
	int c;
} Puzzle;


/**
 * @brief      Checks if 'filename' has the extension 'fileExtension'
 *
 * @param      filename       Filename to check
 * @param      fileExtension  Supposed file extension
 *
 * @return     Boolean.
 * @retval     1              If 'filename' ends in 'fileExtension'
 * @retval     0              Otherwise
 */
int hasExtension(char *filename, char *fileExtension){
    size_t nameLen;
    size_t extLen;
    unsigned int index;

    nameLen = strlen(filename);
    extLen = strlen(fileExtension);

    if (nameLen <= extLen){
        return 0;
    } else {
        index = nameLen - extLen;
        if(strcmp(&filename[index], fileExtension) == 0) return 1;
        else return 0;
    }
}

void resetArrayToZero(int *array, int size) {
	int i;

	for (i = 0; i < size; ++i)
	{
		array[i] = 0;
	}
}

int convertCoordinates(int base, int n) {
	return (base - (n - 1));
}


int main(int argc, char *argv[]) {

	
	if(argc != 2){
 	    exit(0);
 	}

	char *puzzleFileName;
	char *solutionFileName;
	char *str;
	
	str = malloc(sizeof(char) * MAX_STR_LEN );

	if(str == NULL) exit(0);

	FILE *puzzleFile;
	FILE *solutionFile;

	
	puzzleFileName = malloc(sizeof(char) * (strlen(argv[1]) + 1));

	if(puzzleFileName == NULL) exit(0);

	strcpy(puzzleFileName, argv[1]);


	if(!hasExtension(puzzleFileName, PUZZLE_FILE_EXTENSION)) {
		free(puzzleFileName);
		free(str);
		exit(0);
	}

	solutionFileName = (char *) malloc( sizeof(char) * (strlen(puzzleFileName) + 2));
    /*Calculate the index right before the . for the file extension*/
    int index = strlen(puzzleFileName) - strlen(PUZZLE_FILE_EXTENSION);
    strcpy(solutionFileName, puzzleFileName); /*Copy problems name*/
    strcpy(&solutionFileName[index], SOLUTION_FILE_EXTENSION); /*Copy extension*/


	puzzleFile = fopen(puzzleFileName, "r");

	if(puzzleFile == NULL) { /*FILE NOT FOUND EXITING */
		free(puzzleFileName);
		free(str);
		exit(0);
	}

	solutionFile = fopen(solutionFileName, "w");

	/*INIT PUZZLE DATA STRUCTURE*/
	Puzzle *puzzle = (Puzzle *) malloc(sizeof(Puzzle));

	if(puzzle == NULL) {
		free(puzzleFileName);
		free(str);
		exit(0);
	}
	/*START WHILE LOOP FROM HERE*/
	/*Read the puzzle config line*/
	while(fscanf(puzzleFile, "%d %d %d %d %d", &(puzzle->rows), 
		&(puzzle->cols), &(puzzle->variant), &(puzzle->r), 
		&(puzzle->c)) != -1) {

		
		int *visited = calloc(puzzle->rows * puzzle->cols, sizeof(int));
		if(visited == NULL) {
			free(puzzleFileName);
			free(str);
			free(puzzle);
			exit(0);
		}
		int *empty = calloc(puzzle->cols, sizeof(int));
		if(empty == NULL) {
			free(puzzleFileName);
			free(str);
			free(puzzle);
			free(visited);
			exit(0);
		}	
		

		Matrix *puzzleMatrix = newMatrix(puzzle->rows,puzzle->cols);

		if(puzzleMatrix == NULL) {
			free(puzzleFileName);
			free(str);
			free(puzzle);
			free(visited);
			free(empty);
			exit(0);
		}
		/*set puzzle struct*/
		puzzle->matrix = puzzleMatrix;
		/*fill puzzle*/
		int i, j;
		for(i = 0; i < puzzle->rows; i++) {
			for(j = 0; j < puzzle->cols; j++) {
				if(fscanf(puzzleFile, "%d", &(puzzle->matrix->data[i][j])) > 1) {
					exit(0);
				}
				if(puzzle->matrix->data[i][j] == -1) empty[j]++;	
			}

		}

		int x = convertCoordinates(puzzle->rows, puzzle->r) - 1;
		int y = puzzle->c - 1 ;

		if(x >= 0 && x < puzzle->rows && y >= 0 && y < puzzle->cols && (puzzle->variant == 1 || puzzle->variant == 2)) {
			int score = 0;

			calculateCluster(puzzle->matrix->data, puzzle->rows, puzzle->cols, x, y,
				puzzle->matrix->data[x][y], &score, visited);

			score = score*(score - 1);
			
			resetArrayToZero(visited, puzzle->cols*puzzle->rows);
			
			if(puzzle->variant == 1) {
				fprintf(solutionFile, "%d %d %d %d %d\n", puzzle->rows, puzzle->cols,
													  puzzle->variant, puzzle->r,
													  puzzle->c);
				
				fprintf(solutionFile, "%d\n", score);
			
			} else if(puzzle->variant == 2) {
				if(score > 0) {
					removeCluster(puzzle->matrix->data, puzzle->rows, puzzle->cols, x, y,
						puzzle->matrix->data[x][y], visited, empty);

				
					fixPuzzle(puzzle->matrix->data, puzzle->rows, puzzle->cols);
					int i;
					for(i = 0; i < puzzle->cols; i++) {
						if(empty[i] == puzzle->rows) {
							shiftMatrix(puzzle->matrix->data, puzzle->rows, i);
						}
						
					}
				

				}

				fprintf(solutionFile, "%d %d %d %d %d\n", puzzle->rows, puzzle->cols,
														  puzzle->variant, puzzle->r,
														  puzzle->c);

				printMatrixToFile(puzzle->matrix, solutionFile);
			
			}

		
		} else {
			fprintf(solutionFile, "%d %d %d %d %d\n", puzzle->rows, puzzle->cols,
													  puzzle->variant, puzzle->r,
													  puzzle->c);
		}

		fprintf(solutionFile, "\n");
		freeMatrix(puzzleMatrix);
		free(empty);
		free(visited);

	}


	/*allocate puzzle matrix*/
		fclose(puzzleFile);
		fclose(solutionFile);
		free(puzzleFileName);
		free(solutionFileName);
		free(str);
		free(puzzle);
		
		exit(0);
	


	
}