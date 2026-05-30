#ifndef FILENAME_HELPER_H
#define FILENAME_HELPER_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

//~ #define DEBUG_L 1
//~ #define DEBUG_S 1

#define EXT_LEN 5
#define FILE_LEN 30
#define N_FORMATS 3

#define FILE_TITLE_LEN 26

/** 
 * Concat '.log' or '.txt' to globalFilename to be readable fileformat.
 * **/
void ConcatExtention(char fileName[FILE_LEN], char extention[EXT_LEN]);

/**
 * Check if extentions is one of: {".txt", ".csv"}; 
 **/
bool IsFormatCorrect(char extention[EXT_LEN], char *correctFormats[EXT_LEN]);

/**
 * Finds delimiter (.), populates fileTitle and extention. Returns true if extention ".txt" or ".csv".
*/
bool IsValidExtention(char fileName[FILE_LEN], char *correctFormats[EXT_LEN]);

/**
 *  Finds the  1st index of delimiter characters. This is used in 
 * 	function "SplitStringByFirstDelimiter"
 *  **/
int GetIndexOfDelimiter(char sourceStr[FILE_LEN], char delimiterChar);

/**
 * Splitting "file.txt" into ".txt" substring, and returning lenght of string (char-array)
 **/
int SplitFilenameToGetFileExtention(char *filename, int delimiterIndex, char extention[EXT_LEN]);

/**
 *  substringLen = GetSubStringByIndexRange(soureString, startIndex, endIndex, destinationSubstring)
 *  startIndex is inclusive, but endIndex is not inclusive. *
 * */
int SplitFilenameToGetFileTitle(char *filename, int delimiterIndex, char fileTitle[FILE_TITLE_LEN]);


/**
 * Function to get a substring ('token') of a source-string, by range of index.
 * 		startIndex is inclusive. EndIndex is NOT inclusive.
 *  **/
int GetSubstringByIndexRange(char sourceStr[FILE_LEN], int startIndex, int endIndex, char *token);

/**
 *  Finds the  n-th (last) index of delimiter characters. This is used in 
 * 	function "SplitStringByFirstDelimiter"
 *  **/

int GetIndexOfLastDelimiter(char sourceStr[FILE_LEN], char delimiterChar);


/**
 *  Compares if a single character is identical to delimiter symbol
 *  **/

bool IsDelimiter(char character, char delimiterChar);

/**
 *  String compare if correct format.
 *  **/
bool IsExtCorrect(char extention[EXT_LEN], char *userExtention);

/**
 * Replaces all characters matching to key to replacement in the given file.
**/
void ReplaceCharInFile(char *fName, char key, char replacement);

/**
 *  Split extention from filename (filetitle and extention) and check if the file extention is correct.
 **/
bool IsValid(char fileName[FILE_LEN], char *userExtention);

#endif //FILENAME_HELPER_H
