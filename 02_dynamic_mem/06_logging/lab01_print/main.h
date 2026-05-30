#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//~ #define DEBUG 1

// predefined output file names depending on type
#define FILE_NAME_CSV "data_grades.csv"
#define FILE_NAME_SPC_DELIM "data_grades.txt"

#define COMMA " "
#define SPACE ","

// enumeration to choose delimiter type for the file that will be written
enum Type {CSV, SPACE_DELIMITED};

/** Ternary operation inside strcpy **/
//~ char *pFilename = fileName;
//~ char *foundDelimiter = (strcmp(fileName, FILE_NAME_CSV) ? COMMA : SPACE;
//~ char foundDelimiter[DELIMITER_LEN] = {0};
//~ strcpy(delimiter, (fileName == FILE_NAME_CSV) ? COMMA : SPACE)) 
	
#endif // MAIN_H
