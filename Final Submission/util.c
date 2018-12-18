/********************************************************************
 * util.c -- Some helper functions                     		        *
 ********************************************************************
 * Project: AED project - Burster                    				*
 *                                                                  *
 * Authors: Luís Lopes (ist425416), Miguel Freire (ist425445)  		*
 ********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

/* Memory Safe Function */
/**
 * Safely allocates memory using malloc
 * @param  size size to alloc
 * @return      pointer to newly allocated object
 */
void *smalloc(const size_t size) {
	void *pointer = (void *) malloc(size);

	if(pointer == NULL) exit(0);

	return pointer;
}

/**
 * Safely allocates memory using calloc
 * @param  n    number of elements to alloc
 * @param  size size of datatype
 * @return      pointer to newly allocated object
 */
void *scalloc(const size_t n, const size_t size) {
	void *pointer = (void *) calloc(n, size);

	if(pointer == NULL) exit(0);

	return pointer;
}

/**
 * Safely allocates memory using realloc
 * @param  pointer pointer to reallocate
 * @param  newSize new size to reallocate
 * @return      pointer to reallocated object
 */
void *srealloc(void *pointer, const size_t newSize) {
	pointer = realloc(pointer, newSize);

	if(pointer == NULL) {
		exit(0);
	}

	return pointer;
}

/*File Helper Functions*/
/**
 * Opens files safely
 * @param  fileName name of the file to open
 * @param  mode     mode to open the file (read,write,etc)
 * @return          pointer to the opened file or NULL if it doens't exist
 */
FILE *sfopen(const char *fileName, const char *mode) {
	FILE *file = fopen(fileName, mode);

	if(file == NULL) {
		exit(0);
	} 

	return file;
}

/**
 * Checks if a file has a certain extension
 * @param  fileName  name of the file
 * @param  extension extension to check existence
 * @return           boolean
 */
int hasExtension(const char *fileName, const char *extension) {
	
	char *fileExtension;

	fileExtension = strrchr(fileName, '.'); /*get the file extension ".XXX" */

	if(fileExtension == NULL) return 0; /*If the "." is not found just return false */

	if(strcmp(fileExtension, extension) == 0) return 1; /*If the extensions are the same return true */

	return 0; /* else false */
}

/**
 * Changes the file extension
 * @param  fileName     (string) name of the file to change extension
 * @param  newExtension new extension
 * @return              (string) name of the file with the new extension
 */
char *changeFileExtension(const char *fileName, const char *newExtension) {
	size_t fileNameSize;

	char *newFileName;

	char *extension;

	extension = strrchr(fileName, '.');

	if(extension == NULL) return NULL;

	fileNameSize = strlen(fileName) - strlen(extension);

	newFileName = scalloc(fileNameSize + strlen(newExtension) + 1 , sizeof(char));

	strncpy(newFileName, fileName, fileNameSize);

	strcat(newFileName, newExtension);

	return newFileName;
}

/**
 * Resets all elements of an int array to 0
 * @param array array to reset
 * @param size  size of the array
 */
void resetArray(int *array, int size) {
	int i;

	if(array == NULL) return;

	for(i = 0; i < size; i++) {
		array[i] = 0;
	}
}

/**
 * Converts 2D coordidates to 1D
 * @param  x vertical coordinate
 * @param  y horizontal coordinate
 * @param  n size of the 2D matrix
 * @return   1D coordinates 
 */
int convert(int x, int y, int n) {
	return x*n+y;
}