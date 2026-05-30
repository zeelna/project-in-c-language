#ifndef WRITE_OUTPUT_H
#define WRITE_OUTPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//~ #define DEBUG 1

#define NAME_LEN 15

/** 
 * Print each structure fields by moving pointer.
 **/
void PrintStructArray(candidate *candidates, int len);

/** 
 * Write to file.
 **/
void WriteToFile(char *filename, int nCandidates, candidate *p);

/**
 * Comparing persons by their points.
 */ 
int ComparPersonByPoints(const void *a, const void *b);


/**
 *  Read statistics from file until limit is reached or ends before that.
 *  **/


void DebugString(char str[]);
int ReadData(candidate **ppCandidateData, int *pLineCount, char *fileName);

#endif // WRITE_OUTPUT
