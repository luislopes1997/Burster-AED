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
#include "util.h"
#include "cluster.h"
#include "move.h"

/** TYPEDEFS AND CONSTS */
#include "defs.h"
/**
 * Prints the puzzle solution to file
 * @param outFile   output file
 * @param rows      number of puzzle's rows
 * @param cols      number of puzzle's cols
 * @param objective variant of the problem
 * @param numMoves  number of moves done
 * @param score     score of the solution
 * @param path      path with moves 
 */
void printSolution(FILE *outFile, int rows, int cols, int objective, int numMoves, int score, Path *path) {
	int i;

	fprintf(outFile, "%d %d %d\n", rows, cols, objective);
	if(objective < 0 && objective != -3 && objective != -1) {
		fprintf(outFile, "\n");
		return;
	}
	fprintf(outFile, "%d %d\n", numMoves, score);
	for(i = 0; i < numMoves;i++) {
		fprintf(outFile, "%d %d\n", (rows - path[i].x), (path[i].y + 1));
	}
	
	fprintf(outFile, "\n");
}


/**
 * Solves a puzzle problem
 * @param rows         number of puzzle's rows
 * @param cols         number of puzzle's cols
 * @param variant      variant of the problem
 * @param puzzleFile   puzzle file
 * @param solutionFile output file
 */
void solveProblem(int rows, int cols, int variant, FILE *puzzleFile, FILE *solutionFile) {
	Path *path, *maxPath = NULL;
	Move **mvs = NULL;
	
	int numMoves = 0;
	int i = 0;
	int found = 0;
	
	path = scalloc(cols * rows / 2, sizeof(Path));
	maxPath = scalloc(cols * rows / 2, sizeof(Path));
	mvs = (Move **) smalloc(cols * rows / 2 * sizeof(Move*));
	
	for(i = 0; i < cols * rows / 2; i++) {
		mvs[i] = newMove(rows, cols); /*Alloc all possible moves*/
	}
	
	initMove(mvs[0], puzzleFile, rows, cols); /*Init first move*/
	numMoves++;
	

	if(variant > mvs[0]->maxScore) { /*If objective is bigger than max possible solution -> impossible solution*/
		printSolution(solutionFile, rows, cols, variant, 0, -1, path);
	} else {
		if(variant >= 0 || variant == -3 || variant == -1) /*If is a valid variant*/
			findSolution(mvs, 0, variant, &numMoves, path, &found); /*Try to find solution to the puzzle*/
		
		if(variant > 0 && found) /*If the problem is variant 2*/
			printSolution(solutionFile, rows, cols, variant, numMoves-1, mvs[numMoves-1]->score, path);
		else if(variant == 0 || variant == -1) /*If the problem is variant 1*/
			printSolution(solutionFile, rows, cols, variant, numMoves-1, mvs[numMoves-1]->score, path);
		else printSolution(solutionFile, rows, cols, variant, 0, -1, path); /*Every other negative variant will produce an error*/
	}
	
	freeMoves(mvs, cols*rows/2);
	free(path);
	free(maxPath);
}


int main(int argc, char **argv) {
	
	if(argc != 2) {
		exit(0);
	}

	/*FILE VARS */
	FILE *puzzleFile, *solutionFile;
	char *solutionFileName;

	int rows, cols, variant;
	/* Check if arguments have the correct file extension */
	if(!hasExtension(argv[1], PUZZLE_FILE_EXTENSION)) exit(0);

	/* Open Files*/
	puzzleFile = sfopen(argv[1], "r");

	solutionFileName = changeFileExtension(argv[1], SOLUTION_FILE_EXTENSION);

	solutionFile = sfopen(solutionFileName, "w");

	free(solutionFileName);

	
	/*Get puzzle's and solve them */
	while(fscanf(puzzleFile, "%d %d %d", &rows, &cols, &variant) != -1) {
		solveProblem(rows, cols, variant, puzzleFile, solutionFile);
	}
	
	/*Close the files*/
	fclose(puzzleFile);
	fclose(solutionFile);
	
	return 0;

}

