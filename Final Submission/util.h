/********************************************************************
 * util.h -- Helper fuctions header file                     		*
 ********************************************************************
 * Project: AED project - Burster                    				*
 *                                                                  *
 * Authors: Luís Lopes (ist425416), Miguel Freire (ist425445)  		*
 ********************************************************************/
#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>

/* Memory Safe Function */
void *smalloc(const size_t size);

void *scalloc(const size_t n, const size_t size);

void *srealloc(void *pointer, const size_t newSize);

/*File Helper Functions*/
FILE *sfopen(const char *fileName, const char *mode);

int hasExtension(const char *fileName, const char *extension); 

char *changeFileExtension(const char *fileName, const char *newExtension);

void resetArray(int *array, int size);

int convert(int x, int y, int n); 
#endif