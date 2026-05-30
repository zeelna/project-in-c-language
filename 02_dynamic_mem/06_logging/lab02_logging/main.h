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

#define FILE_NAME_LEN 50

#define COMMA " "
#define SPACE ","

#define COMMA_C ' '
#define SPACE_C ' '

// enumeration to choose delimiter type for the file that will be written
enum Type {CSV, SPACE_DELIMITED};


/*
 * Returns the index of a delimiting character in a string. Will help split string into substring.
 */	
int GetIndexOfFirstDelimiter(char *sourceStr, char delimiterChar);

/*
 * Checks if character (in string) is a delimiting character (can be chosen by parameter)
 */	
bool IsDelimiterChar(char character, char delimiterChar);


/*
 * Prompts for to read data from CSV or SPACE-DELIMITED
 */
void PromptCsvOrSpaceDelimited(char fileName[FILE_NAME_LEN]);


/**
 *  Split source-string into two tokens (two destination strings) 
 * 		Using delimiter to find delimiter's index and splitting from there.
 * 			Function finds the lengths of token-strings.
 *  **/
void SplitStringByFirstDelimiter(char *sourceStr, char delimiterChar,
								char *tokenOne, char *tokenTwo,
								 int tokenOneLen, int tokenTwoLen);
								 
								 

/**
 *  Concat all chars AFTER delimiter met, @delimiterIndex+1 into new string "tokenTwo"
 *  **/
int GetTokenTwoAfterSplit(char *sourceStr, int delimiterIndex, char *tokenTwo);
/**
 *  Concat all chars UNTIL delimiter met, @delimiterIndex into new string "tokenTwo"
 *  **/
int GetTokenOneAfterSplit(char *sourceStr, int delimiterIndex, char *tokenOne);

/** Ternary operation inside strcpy **/
//~ char *pFilename = fileName;
//~ char *foundDelimiter = (strcmp(fileName, FILE_NAME_CSV) ? COMMA : SPACE;
//~ char foundDelimiter[DELIMITER_LEN] = {0};
//~ strcpy(delimiter, (fileName == FILE_NAME_CSV) ? COMMA : SPACE)) 
	
#endif // MAIN_H
