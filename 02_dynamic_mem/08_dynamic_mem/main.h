#ifndef MAIN_H
#define MAIN_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define CODE_LEN 5

typedef struct candidate
{
	int ID;
	char *fName;
	char *lName;
	char code[CODE_LEN];	
	double points;
	
} candidate;

/**
 * Function to check if allocated memory can be free without memory leaks.
 **/
void SafeFree(void **p);

/**
 * Function to allocate memory dynamically dependant of size.
 **/
void ReallocateData(candidate **pData, int len, candidate **pTemp);

/**
 * Function to allocate memory dynamically dependant of size.
 **/
void AllocateData(int **data, int n);

void FreeStruct(candidate *p, int n);

#endif // MAIN_H
