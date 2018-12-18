/********************************************************************
 * defs.h -- Definitions header file                                *
 ********************************************************************
 * Project: AED project - Burster                    				*
 *                                                                  *
 * Authors: Luís Lopes (ist425416), Miguel Freire (ist425445)  		*
 ********************************************************************/

/* Include guard */
#ifndef DEFS_H
#define DEFS_H

#define PUZZLE_FILE_EXTENSION ".puz" /*Extension of puzzle files*/
#define SOLUTION_FILE_EXTENSION ".moves" /*Extension of solution files*/
#define MAX_STR_LEN 100 /*Max string length*/
#define	MAX_NUM_ELEMENTS 100 /*Max number of colors*/

typedef void *Item;

typedef struct _Path {
	int x;
	int y;
} Path;

#endif /* End include guard */
