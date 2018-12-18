/********************************************************************
 * cluster.c -- Cluster Data Structure                      		*
 ********************************************************************
 * Project: AED project - Burster                    				*
 *                                                                  *
 * Authors: Luís Lopes (ist425416), Miguel Freire (ist425445)  		*
 ********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "defs.h"
#include "cluster.h"
#include "util.h"
#include "matrix.h"


/**
 * Creates a new cluster element
 * @param  x  horizontal coordinates of the element
 * @param  y  vertical coordinates of the element
 * @return    Pointer to new cluster element
 */
ClusterNode *newClusterNode(int x, int y) {
	ClusterNode *new = smalloc(sizeof(ClusterNode));

	new->x = x;

	new->y = y;

	new->next = NULL;

	return new;
}

/**
 * Creates a new cluster
 * @return Pointer to new cluster
 */
Cluster *newCluster() {
	Cluster *new = (Cluster *) smalloc(sizeof(Cluster));

	new->head = NULL;

	new->size = 0;

	new->element = -1;

	new->next = NULL;

	return new;
}


/**
 * Inserts a node in a cluster (linked list)
 * @param node    node to insert
 * @param cluster cluster to insert node
 */
void insertNodeInCluster(ClusterNode *node, Cluster *cluster) {
	if(node == NULL || cluster == NULL) return;
	
	node->next = cluster->head;

	cluster->head = node;
}

/**
 * Inserts a cluster in a linked list
 * @param head Head Cluster of the linked list
 * @param node Node to insert in the cluster
 */
void insertCluster(Cluster *head, Cluster *node) {
	if(head == NULL || node == NULL) return;
	node->next = head;
	head = node;
}

/**
 * Gets a cluster in a matrix location (x,y)
 * @param M        matrix
 * @param x        vertical coordinates
 * @param y        horizontal coordinates
 * @param element  color of the element
 * @param visited  array to control which nodes have been visited
 * @param C        cluster to save elements
 * @param elements array to calculate upper bound
 */
void getCluster(Matrix *M, int x, int y, int element, int *visited, Cluster *C, int elements[MAX_NUM_ELEMENTS]) {
	if(C == NULL) return;
	if(x > (M->rows - 1) || x < 0 || y > (M->cols - 1) || y < 0 || element == -1) return;
	
	visited[convert(x,y,M->cols)] = 1; /*Set this element has visited*/
	elements[element]++;
	C->size++; /*increment the number of elements on this cluster */

	ClusterNode *new = newClusterNode(x,y); /*Create new cluster node */
	
	insertNodeInCluster(new, C); /*Insert new cluster node in cluster*/
	
	/*Search top for the same elements*/
	if((x-1) >= 0 && M->data[x-1][y] == element && visited[convert(x-1,y,M->cols)] == 0) {
		
		getCluster(M, x-1, y, element, visited, C, elements);
	}

	/*Search right for the same elements*/
	if((y+1) < M->cols && M->data[x][y+1] == element && visited[convert(x,y+1,M->cols)] == 0) {
		getCluster(M, x, y+1, element, visited, C, elements);
	}

	/*Search bottom for the same elements*/
	if((x+1) < M->rows && M->data[x+1][y] == element && visited[convert(x+1,y,M->cols)] == 0) {
		getCluster(M, x+1, y, element, visited, C, elements);
	}

	/*Search left for the same elements*/
	if((y-1) >= 0 && M->data[x][y-1] == element && visited[convert(x,y-1,M->cols)] == 0) {
		getCluster(M, x, y-1, element, visited, C, elements);
	}

	return;

	
}

/**
 * Get's all clusters in a puzzle
 * @param  matrix   matrix representing the puzzle
 * @param  clusters linked list of clusters
 * @param  n        pointer to save the number of clusters
 * @param  maxScore pointer to save the max possible score this puzzle can generate
 * @return          cluster node with all clusters elements
 */
Cluster *getPuzzleClusters(Matrix *matrix, Cluster *clusters, int *n, int *maxScore) {
	int i , j;
	int *visited;
	*n = 0;
	visited = scalloc(matrix->cols * matrix->rows, sizeof(int));
	int elements[MAX_NUM_ELEMENTS] = {0};
	int maxElement = 0;
	Cluster *new;
	
	/*For each element in matrix traverse the matrix*/
	for(i = 0; i < matrix->rows; i++) {
		for(j = 0; j < matrix->cols; j++) {
			if(matrix->data[i][j] == -1) continue; /*If the element does not exist discard*/
			if(visited[convert(i, j, matrix->cols)] == 1) continue; /*If the element was already visited discard*/
			
			/*Let's save the matrix largest element for further calculations*/
			if(matrix->data[i][j] > maxElement) maxElement = matrix->data[i][j]; 

			/*Create a new cluster*/
			new = newCluster();
			new->size = 0;

			/*Get elements in those coordiates (x,y) to form a cluster*/
			getCluster(matrix, i, j, matrix->data[i][j], visited, new, elements);

			if(new->size == 1) { /* If the "cluster" found only has 1 element discard, it's not a cluster*/
				free(new->head);
				free(new);
				continue;
			}
			/*Update cluster's pointers*/
			if(clusters == NULL) {
				clusters = new;
			} else {
				new->next = clusters;
				clusters = new;
			}
			
			++(*n); /*Increment number of clusters*/
			
		}
	}
	
	/*Calculate puzzle max possible score*/
	for(i = 0; i <= maxElement; i++){
		if(elements[i] == 0 || elements[i] == 1) continue;
		*maxScore += elements[i]*(elements[i]-1);
	}
	

	free(visited);
	return clusters;
}

/**
 * Free a cluster group
 * @param C pointer to cluster group
 */
void freeClusterGroup(Cluster *C) {
	if(C == NULL) return;
	Cluster *aux, *current;
	current = C;
	while(current != NULL) {
		aux = current->next;
		freeCluster(current);
		current = aux;
	}
}

/**
 * Free a cluster
 * @param C pointer to cluster linked list
 */
void freeCluster(Cluster *C) {
	if(C == NULL) return;

	ClusterNode *current, *aux;
	if(C->head == NULL) {
		free(C);
		return;
	}
	current = C->head;
	while(current != NULL) {
		aux = current->next;
		free(current);
		current = aux;
	}

    if(C != NULL) free(C);
    return;

}

/**
 * Removes a cluster from the puzzle
 * @param  M     matrix represeting puzzle
 * @param  C     cluster head to be removed
 * @param  path  path to save move done
 * @param  score score generated by removing that cluster
 * @return       new head
 */
Cluster* removeCluster(Matrix *M, Cluster *C, Path *path, int *score) {
	if(M == NULL || C == NULL || C->size == 1 || C->head == NULL) return 0;
	ClusterNode *current, *aux;
	Cluster *auxC;
	int x, y, i;
	
	*score = C->size*(C->size - 1); /*Calculate the score of removing this given cluster*/
	path->x = C->head->x; /*Save move path*/
	path->y = C->head->y;
	current = C->head;
	while(current != NULL) { /*Remove every element in this cluster*/
		x = current->x;  
		y = current->y;
		M->data[x][y] = -1;

		M->empty[y]++; /*Update matrix empty column controller array*/

		aux = current;

		current = current->next;

		free(aux);
	}
    auxC = C;
    C = C->next;
    free(auxC);

    fixPuzzle(M); /*Puzzle's gravity effect*/
    
	for (i = 0; i < M->cols; ++i)
	{
		if(M->empty[i] == M->rows) shiftMatrix(M, i); /*Fixes empty columns*/
	}
	

	return C;
}

/**
 * Puzzle Gravity effect  
 * @param M matrix to apply gravity effect
 */
void fixPuzzle(Matrix *M) {
	if(M == NULL) return;
	/*For each element in matrix check if there are no element above them
	If there are shift the elements to the bottom (gravity effect)
	*/
	int tmp = 0, i,j,n;
	for(i = 0; i < M->cols; i++) {
		for(j = 0; j < M->rows-1; j++) {
			if(M->data[j][i] != -1 && M->data[j+1][i] == -1) {
				for(n = j+1; n > 0; n--) {
					tmp = M->data[n][i];
					M->data[n][i] = M->data[n-1][i];
					M->data[n-1][i] = tmp;
				}
			}
		}
	}
}

/**
 * Shifts all empty columns to the left
 * @param M matrix to shift columns
 * @param y column to shift
 */
void shiftMatrix(Matrix *M, int y) {
	if(M == NULL) return;
	int tmp = 0, i, j, aux = 0;
	/*Shifts all columns after column y*/
	for(i = y; i > 0; i--) {
		for(j = 0; j < M->rows; j++) {
			tmp = M->data[j][i];
			M->data[j][i] = M->data[j][i-1];
			M->data[j][i-1] = tmp;
		}
		aux = M->empty[i];
		M->empty[i] = M->empty[i-1];
		M->empty[i-1] = aux;

	}
}

