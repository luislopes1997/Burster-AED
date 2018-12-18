/********************************************************************
 * cluster.h -- Cluster Data Structure Header File                  *
 ********************************************************************
 * Project: AED project - Burster                    				*
 *                                                                  *
 * Authors: Luís Lopes (ist425416), Miguel Freire (ist425445)  		*
 ********************************************************************/
#ifndef CLUSTER_H
#define CLUSTER_H

#include "matrix.h"
#include "defs.h"

typedef struct _Cluster { /*Cluster linked list*/
	struct _ClusterNode *head;
	int size;
	int element;
	struct _Cluster *next;
} Cluster;

typedef struct _ClusterNode {/*ClusterNode linked list*/
	int x;
	int y;
	struct _ClusterNode *next;
} ClusterNode;

ClusterNode *newClusterNode(int x, int y);

Cluster *newCluster();

void insertNodeInCluster(ClusterNode *node, Cluster *cluster);

void insertCluster(Cluster *head, Cluster *node);

void getCluster(Matrix *M, int x, int y, int element, int *visited, Cluster *C, int elements[MAX_NUM_ELEMENTS]);

Cluster *getPuzzleClusters(Matrix *matrix, Cluster *clusters, int *n, int *maxScore);

Cluster *removeCluster(Matrix *M, Cluster *C, Path *path, int *score);

void freeCluster(Cluster *C);

void freeClusterGroup(Cluster *C);

void fixPuzzle(Matrix *M);

void shiftMatrix(Matrix *M, int y);


#endif