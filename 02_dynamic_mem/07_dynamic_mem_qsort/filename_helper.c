#include "filename_helper.h"
#include "generator.h"

/** 
 * Concat '.log' or '.txt' to globalFilename to be readable fileformat.
 * **/
void ConcatExtention(char fileName[FILE_LEN], char extention[EXT_LEN])
{
	/** Get length of desired globalFilename**/
	int len = (int)strlen(fileName);
	
	/** Truncate "too lengthy" 'desired' globalFilename string in lenght, if its length larger than [LOG_FILE_NAME_LEN] **/
	char truncatedFilename[FILE_LEN - EXT_LEN - 1] = {0};
	
	snprintf(truncatedFilename, (FILE_LEN - EXT_LEN - 1), "%s", fileName);
	/** EXT_LEN is fixed as 5.
	 * .csv OR .txt are both in lenght of 4 + '\0' == 5
	 *  snprinf() requires length to be n-1 to append '\0' to end of string**/
	 
	
	/** Concat .log (or other extention) to 'truncated' globalFilename **/
	snprintf(fileName, (FILE_LEN - 1), "%s%s", truncatedFilename, extention);
	
	/** void Fn.**/
}

/**
 *  String compare entire array of correct formats. Return true if found one match.
 *  **/
bool IsFormatCorrect(char extention[EXT_LEN], char *correctFormats[EXT_LEN])
{
	int nFormats = sizeof(correctFormats) / sizeof(correctFormats[0]);
	
	#ifdef DEBUG_S
	printf("\nnFormats: %d", nFormats);
	#endif
	
	/** Loop through [.txt, .log] array to compare if user chosen ext
	 * 	 is matching, and thus correct log format. If not, return false.**/
	for (int i = 0; i < nFormats; i++) // swap nFormats with N_FORMAT?
	{
		//~ printf("\n'AAA - IsFormatCorrect()': extention -> %s, correctFormats[%d]: %s", extention, i, correctFormats[i]);
		if (strcmp(extention, correctFormats[i]) == 0)
		{
			#ifdef DEBUG_S
			printf("\n'IsFormatCorrect()': extention -> %s, correctFormats[%d]: %s", extention, i, correctFormats[i]);
			#endif
			
			return true;
		}
	}
	return false; /** cannot optimise by <return !strcmp....> because looping an array-**/
}

/**
 *  String compare if user selected filename has correct input.
 *  **/
bool IsExtCorrect(char extention[EXT_LEN], char *userExtention)
{
	if (strcmp(extention, userExtention) == 0) {
		return true;
	} else {
		return false; /** cannot optimise by <return !strcmp....> because looping an array-**/
	}
	//~ return !strcmp(extention, userExtention == 0);
}

/**
 *  Split extention from filename (filetitle and extention) and check if the file extention is correct.
 **/
bool IsValid(char fileName[FILE_LEN], char *userExtention)
{
	/** NB! 'globalFilename' variable is global-variable.**/
	char delimiterChar = '.';
	int delimiterIndex = GetIndexOfLastDelimiter(fileName, delimiterChar);
	
	/** Step 1. Populate string 'fileTitle'.
	 * 		1) Create substring <logfile> from  logfile.txt. 
	 * 		2) Return length of 'logfile' substring. **/
	char fileTitle[FILE_TITLE_LEN] = {0};
	
	int fileTitleLen = SplitFilenameToGetFileTitle(fileName, delimiterIndex, fileTitle);
	
	/** Step 2. Populate string 'extention'.
	 * 		1) Create substring <.txt> from  logfile.txt. 
	 * 		2) Return length of 'extention' substring. **/
	char extention[EXT_LEN] = {0};
	
	#ifdef DEBUG_L
	printf("\nDEBUG: extention: %s", extention);
	#endif 
	
	int extLen = SplitFilenameToGetFileExtention(fileName, delimiterIndex, extention);
	
	
	#ifdef DEBUG_L
	printf("\nDEBUG: extention: %s", extention);
	#endif 
	
	/** Return 'true' if <.txt> is ".txt"**/
	return IsExtCorrect(extention, userExtention); 
}

bool IsValidExtention(char fileName[FILE_LEN], char *correctFormats[EXT_LEN])
{
	/** NB! 'globalFilename' variable is global-variable.**/
	char delimiterChar = '.';
	int delimiterIndex = GetIndexOfLastDelimiter(fileName, delimiterChar);
	
	/** Step 1. Populate string 'fileTitle'.
	 * 		1) Create substring <logfile> from  logfile.txt. 
	 * 		2) Return length of 'logfile' substring. **/
	char fileTitle[FILE_TITLE_LEN] = {0};
	
	int fileTitleLen = SplitFilenameToGetFileTitle(fileName, delimiterIndex, fileTitle);
	
	/** Step 2. Populate string 'extention'.
	 * 		1) Create substring <.txt> from  logfile.txt. 
	 * 		2) Return length of 'extention' substring. **/
	char extention[EXT_LEN] = {0};
	
	#ifdef DEBUG_L
	printf("\nDEBUG: extention: %s", extention);
	#endif 
	
	int extLen = SplitFilenameToGetFileExtention(fileName, delimiterIndex, extention);
	
	
	#ifdef DEBUG_L
	printf("\nDEBUG: extention: %s", extention);
	#endif 
	
	/** Return 'true' if <.txt> is found in const array = [".txt", ".text", ".md"] **/
	return IsFormatCorrect(extention, correctFormats); 
}


/**
 *  Finds the  1st index of delimiter characters. This is used in 
 * 	function "SplitStringByFirstDelimiter"
 *  **/
int GetIndexOfDelimiter(char sourceStr[FILE_LEN], char delimiterChar)
{
	int len = (int)strlen(sourceStr);
	int i = 0;
	for (i = 0; i < len; i++)
	{
		if (IsDelimiter(sourceStr[i], delimiterChar))
		{
			return i;
		}
	}
	return i; // Problem. If not delimiter, returns last index. If length sourceStr empty, tne delimiterIndex = 0;
}


/**
 * Splitting "file.txt" into ".txt" substring, and returning lenght of string (char-array)
 **/
int SplitFilenameToGetFileExtention(char *filename, int delimiterIndex, char extention[EXT_LEN])
{
	int filenameLen = (int)strlen(filename);
	
	#ifdef DEBUG_L
	printf("\nDEBUG: filename's string-length is: %d ('filenameLen')\n", filenameLen);
	#endif
	
	int extLen = GetSubstringByIndexRange(filename, delimiterIndex, filenameLen, extention);
	
	return extLen;
}

/**
 *  substringLen = GetSubStringByIndexRange(soureString, startIndex, endIndex, destinationSubstring)
 *  startIndex is inclusive, but endIndex is not inclusive. *
 * */
int SplitFilenameToGetFileTitle(char *filename, int delimiterIndex, char fileTitle[FILE_TITLE_LEN])
{
	int fileTitleLen = GetSubstringByIndexRange(filename, 0, delimiterIndex, fileTitle); 
	
	#ifdef DEBUG_L
	printf("Dot is at index: %d ('delimiterIndex')\n", delimiterIndex);
	printf("File title without extention is: %s ('filetitle')\n", fileTitle);
	#endif
	
	return fileTitleLen;
}	

/**
 * Function to get a substring ('token') of a source-string, by range of index.
 * 		startIndex is inclusive. EndIndex is NOT inclusive.
 *  **/
int GetSubstringByIndexRange(char sourceStr[FILE_LEN], int startIndex, int endIndex, char *token) 
{
	/** Step 1: Iterate to populate 1st token. tokenOne will be: 'Programming' **/
	int i;
	int cnt = 0;
	
	#ifdef DEBUG_L
	printf("\nDEBUG[%d]: filename: %s\n", cnt, sourceStr);
	#endif
	
	for (i = startIndex; i < endIndex; i++)
	{
		token[cnt] = sourceStr[i]; //~ *(token + cnt) = *(sourceStr + i);
		
		#ifdef DEBUG_L
		printf("DEBUG-i[%d][i: %d]: %c <=>", cnt, i, sourceStr[i]);	
		printf("DEBUG[%d]: %c\n", cnt, token[cnt]);
		#endif
		
		cnt++; // DO NOT FORGET

	}
	putchar('\n'); // for debugging
	
	/** Concat null-terminator to string '\0'**/
	token[cnt] = '\0'; 	//~ *(token + cnt) = '\0';

	#ifdef DEBUG_L
	printf("DEBUG-i[%d][i: %d]: %c <=>", cnt, i, sourceStr[i]);
	printf("DEBUG[%d]: %c \n(P.S this is intentionally going +1 over length to see if has null-terminator ('\\0')\n", cnt, token[cnt]);
	
	printf("\nDEBUG [%d] token's last index + 1 has: %c\n", cnt, token[cnt]);
	printf("\nDEBUG [%d] token is: %s\n", cnt, token);
	
	if(token[cnt] == '\0')
		puts("Token has null-terminator at end");
	else
		puts("Token DOES NOT HAVE null terminator at end");	
	
	if(sourceStr[i] == '\0')
		puts("sourceStr has null terminator at end");
	else
		puts("sourceStr DOES NOT HAVE null terminator at end");
	#endif
	
	return cnt + 1; /** Return the length of substring. [1-9]. Last nr is not inclusive due to '< cnt' in other Fn's.**/
	//~ return cnt; /** Return the length of substring. [1-9]. **/
}

/**
 *  Finds the  n-th (last) index of delimiter characters. This is used in 
 * 	function "SplitStringByFirstDelimiter"
 *  **/

int GetIndexOfLastDelimiter(char sourceStr[FILE_LEN], char delimiterChar)
{
	int len = (int)strlen(sourceStr);

	/** delimiter index:**/
	int delimiterIndex = 0;

	int i = 0;
	for (i = 0; i < len; i++)
	{
		if (IsDelimiter(sourceStr[i], delimiterChar))
		{
			delimiterIndex = i;
		}
	}
	return delimiterIndex; // Problem. If not delimiter, returns last index. If length sourceStr empty, tne delimiterIndex = 0;
}

/**
 *  Compares if a single character is identical to delimiter symbol
 *  **/

bool IsDelimiter(char character, char delimiterChar)
{
	return character == delimiterChar;
}

/**
 * Replaces all characters matching to key to replacement in the given file.
 **/
void ReplaceCharInFile(char *fName, char key, char replacement)
{
	int ch;
	FILE *fp = fopen(fName, "r+");
	
	if (fp != NULL)
	{
		while ((ch = fgetc(fp)) != EOF)
		{
			if (ch == key)
			{
				fseek(fp, ftell(fp) - 1, SEEK_SET);
				fputc(replacement, fp);
			}
		}
		fclose(fp);
	}
}
