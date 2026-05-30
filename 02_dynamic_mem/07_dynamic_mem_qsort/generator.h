/**
 * File:        generator.h
 * Author:      Frank Christopher Kirch
 * Created:     26.03.2024
 * Modified     30.05.2026
 *
 * Description: Header file to provide the name pools required for the task.
 */
#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "name_pools.h"
#include "filename_helper.h"

#define READ_LIMIT 110

#define FILE_NAME_SPC_DELIM "out.txt"

#define CSV_EXT 0
#define SPC_DELIM_EXT 1

// enumeration to choose delimiter type for the file that will be written
enum Type {CSV, SPACE_DELIMITED};

typedef struct candidate
{
	const char *fName;
	const char *lName;
	const char *code;	
	double points;
	
} candidate;


int GetRand(int numMin, int numMax);

int PromptNumberOfCandidates(void);

/** 
 * Pakun välja kaks erinevat võrdlusfunktsiooni võimalust.
 * Teisel juhul loome lisaviidad, mis võtavad täiendavalt mälu, kuid lihtsustavad koodi loetavust.
 **/
int ComparCandidate(const void *a, const void *b);

/** 
 * Print each structure fields by moving pointer.
 **/
void PrintStructArray(candidate *candidates, int len);

/** 
 * Write to file.
 **/
void WriteToFile(char *filename, int nCandidates, candidate *p);


/**
 * Ask user to choose a filename where logs will be sent. Avoid empty input.
 */
void PromptOutputFileName(char newFilename[FILE_LEN]);

/*
 * Prompts for user confirmation until received
 */
bool PromptYesNo(void);

/**
 * Ask user whether they want to write to csv or .txt (space delimited)
 **/
enum Type PromptCsvOrSpaceDelimited(char fileName[FILE_LEN]);

/*
 * Print debug information of string. Each char, it's index and ASCII.
 */
void DebugString(char *str);


#endif //GENERATOR_H
