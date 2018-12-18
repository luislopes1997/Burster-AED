/********************************************************************
 * move.h -- Moves header file                                      *
 ********************************************************************
 * Project: AED project - Burster                    				*
 *                                                                  *
 * Authors: Luís Lopes (ist425416), Miguel Freire (ist425445)  		*
 ********************************************************************/
#ifndef MOVE_H
#define MOVE_H

#include "defs.h"
#include "matrix.h"
#include "cluster.h"

typedef struct _Move {
	Matrix *puzzle;
	Cluster *clusters;
	int score;
	int numClusters;
	int availableCluster;
	int maxScore;
} Move;

void initMove(Move *firstMove, FILE *puzzleFile, int rows, int cols);

Move *newMove(int rows, int cols);

void freeMoves(Move **moves, int numMoves);

void findSolution(Move **moves, int k, int objective, int *numMoves, Path *path, int *found);

#endif