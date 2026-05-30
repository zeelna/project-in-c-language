
#include "struct_helper.h"
#include "main.h"

int main(void)
{

	/** Version 2b: string-copy **/
	char fileName[FILE_NAME_LEN] = {0}; // b2
	//~ strcpy(fileName, FILE_NAME_SPC_DELIM); //b2
	strcpy(fileName, FILE_NAME_CSV); //b2
	

	//~ char delimiter[DELIMITER_LEN] = {0};
	 //~ char *delimiter = (fileName == FILE_NAME_CSV) ? COMMA : SPACE;
	 
	char *pDelimiter;
	char delimiterChar;
	
	/** Map correct delimitor according to filename**/
	
	if (strcmp(fileName, FILE_NAME_CSV) == 0)
	{
		pDelimiter = ",";
		delimiterChar = ',';
	} 
	else if (strcmp(fileName, FILE_NAME_SPC_DELIM) == 0)
	{
		pDelimiter = " "; // FIX. DEPENDS ON MODE.
		delimiterChar = ' ';
	}
	else
	{
		return EXIT_FAILURE;
	}
	

	
	// My added code.
	/** Initialize array to each line we read, and limit up to where we read**/
	subject subjects[READ_LIMIT] = {0};
	int limit = READ_LIMIT;
	
	/** Function call: **/
	int countRead = ReadFile(subjects, limit, fileName);
	
	#ifdef DEBUG
	printf("DEBUG: Program read data from file for '%d' lines.\n", countRead);
	#endif
	
	subject *p = subjects;
	
	//~ int nSubjects = sizeof(subjects) / sizeof(subject);
	//~ for (int i = 0; i < nSubjects; i++)
	
	for (int i = 0; i < countRead; i++)
	{
		
		SplitStringByFirstDelimiter(p->entry, delimiterChar,
									p->name, p->gradesStr,
									p->nameLen, p->gradeStrLen);
		
		int intArr[LINE_LEN] = {0}; /** Reset for each struct in struct-array.**/
		
		/** StringToList ==> char[]: "5, 4, 3, 4" --> int[]: [5, 4, 3, 4]**/
		int intArrLen = StringToIntArray(p->gradesStr, intArr, pDelimiter, p); // maybe use instead "delimiter"
		p->gradesLen = intArrLen;
		
		for (int j = 0; j < intArrLen; j++)
		{
			p->grades[j] = intArr[j]; /** struct's int[] will be populated.**/
		}
		

		int sum = GetSumOfGrades(p);
		p->gradesSum = sum;
		p->average = GetAverageOfGrades(p, sum);
		
		p++; // Move pointer to next 'subjects' array-element's pointer.
	}
	
	PrintStructArray(subjects, countRead);
	

	#ifdef DEBUG
	printf("\n Successfully ran '%s'\n", __FUNCTION__);
	#endif

    return EXIT_SUCCESS;
}

/**
 *  Finds the index of delimiter characters index. This is used in 
 * 	function "SplitStringByFirstDelimiter"
 *  **/
int GetIndexOfFirstDelimiter(char *sourceStr, char delimiterChar)
{
	int len = strlen(sourceStr);
	int i;
	for (i = 0; i < len; i++)
	{
		if (IsDelimiterChar(sourceStr[i], delimiterChar))
		{
			#ifdef DEBUG
			printf("\n Successfully ran '%s'\n", __FUNCTION__);
			#endif
			
			return i;
		}
	}
	
	return i;
	//~ fprintf(stderr, "Error: No delimiter characted found\n."); 
	//~ exit(EXIT_FAILURE);

}
/**
 *  Compares if a single character is identical to delimiter symbol
 *  **/
bool IsDelimiterChar(char character, char delimiterChar)
{
	return character == delimiterChar;
}

/**
 *  Split source-string into two tokens (two destination strings) 
 * 		Using delimiter to find delimiter's index and splitting from there.
 * 			Function finds the lengths of token-strings.
 *  **/
void SplitStringByFirstDelimiter(char *sourceStr, char delimiterChar,
								char *tokenOne, char *tokenTwo,
								 int tokenOneLen, int tokenTwoLen)
{
	/** Explain Fn ==> split once when delimiter occurs. **/
	/** sourceStr: "Programming 10 4 5 5 4 ..."**/
	
	/** GetIndex... find index of whitespace/comma whenever occurs 1st time.**/
	int delimiterIndex = GetIndexOfFirstDelimiter(sourceStr, delimiterChar);
	
	/** Step 1: Iterate to populate 1st token. tokenOne will be: 'Programming' **/
	tokenOneLen = GetTokenOneAfterSplit(sourceStr, delimiterIndex, tokenOne);
	
	/** Step 2: Iterate 2nd token. tokenTwo will be: '10 4 5 ...'  **/
	tokenTwoLen = GetTokenTwoAfterSplit(sourceStr, delimiterIndex, tokenTwo);
	
	
	
	#ifdef DEBUG
	printf("DEBUG: tokenOne: %s\n", tokenOne);
	printf("DEBUG: tokenTwo: %s\n", tokenTwo);

	printf("\n Successfully ran '%s'\n", __FUNCTION__);
	#endif
}
/**
 *  Concat all chars UNTIL delimiter met, @delimiterIndex into new string "tokenTwo"
 *  **/
int GetTokenOneAfterSplit(char *sourceStr, int delimiterIndex, char *tokenOne)
{
	/** Step 1: Iterate to populate 1st token. tokenOne will be: 'Programming' **/
	int i;
	for (i = 0; i < delimiterIndex; i++)
	{
		*(tokenOne + i) = *(sourceStr + i);
		
		//~ printf("%c", *(tokenOne + i));
	}
	*(tokenOne + i) = '\0';
	return i;
}

/**
 *  Concat all chars AFTER delimiter met, @delimiterIndex+1 into new string "tokenTwo"
 *  **/
int GetTokenTwoAfterSplit(char *sourceStr, int delimiterIndex, char *tokenTwo)
{
	 /** Step 2: Iterate 2nd token. tokenTwo will be: '10 4 5 ...'  **/

	int cnt = 0; // DO NOT FORGET

	/** Iterating at Index after delimiter.**/
	int j = delimiterIndex + 1; 
	while (sourceStr[j] != '\0') 
	//~ for (int j = (delimiterIndex + 1); j < strlen(sourceStr); j++) 
	{ 
		*(tokenTwo + cnt) = *(sourceStr + j);
		cnt++; // DO NOT FORGET.
		
		j++; // remove if comment-out WHILE_LOOP
		
		printf("%c", *(tokenTwo + cnt));
		
	}
	*(tokenTwo + cnt) = '\0';
	
	return cnt;
}
