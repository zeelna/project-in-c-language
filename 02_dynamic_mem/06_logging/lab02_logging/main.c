
#include "struct_helper.h"
#include "main.h"
#include "log_helper.h"

int main(void)
{
	
	// version 1.
	/** Ask user whether they want to log, and choose log-level 
	 * 	(INFO; WARNING; ERROR; OFF)**/
	/** Call setter to rewrite global vairable 'globallySetLogLevel'**/
	int usersLogLevel = PromptEnableDisableLogging();
	LoggerSetLoggingLevel(usersLogLevel); // inner returns type 'enum LogLevel'
	
	/** version 2: Unable to skip PromptLogFileName() when user chose 'OFF' **/
	//~ LoggerSetLoggingLevel(PromptEnableDisableLogging()); // inner returns type 'enum LogLevel'
	
	/** For testing: **/
	//~ LoggerSetLoggingLevel(LOG_INFO);
	//~ LoggerSetLoggingLevel(LOG_WARNING);
	//~ LoggerSetLoggingLevel(LOG_ERROR);	
	//~ LoggerSetLoggingLevel(LOG_OFF);
	

	/** Ask user to select logfile name.**/
	char logfileName[LOG_FILE_NAME_LEN] = {0};
	
	if (usersLogLevel != OFF) /** Avoid asking log-filename if user disabled logging.**/
	{
		PromptLogFileName(logfileName);
	
		/** Call setter to rewrite into  global variable 'globalfileName'**/
		LoggerSetOutputName(logfileName);
	}

	Logger("Starting program.", LOG_INFO); // log entry to logfile.
	//~ Logger("Starting program.", LOG_ERROR); // log entry to logfile.
	//~ Logger("Starting program.", LOG_WARNING); // log entry to logfile.
	//~ Logger("Starting program.", LOG_OFF); // log entry to logfile.


	/** Version 2b: string-copy **/ // LOOK HERE FOR CSV OR SPACE LIMITED
	char fileName[FILE_NAME_LEN] = {0}; // b2
	
	PromptCsvOrSpaceDelimited(fileName);
	
	/** To swap delimiter char, to replace in file. Can be used instead of if there.**/
	//~ char delimiter[DELIMITER_LEN] = {0};
	 //~ char *delimiter = (fileName == FILE_NAME_CSV) ? COMMA : SPACE;
	 //~ char *delimiterChar = (fileName == FILE_NAME_CSV) ? COMMA_C : SPACE_C;
	 
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
		Logger("Closing program. Input file not found.", ERROR);
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
	
	/** IMPORTANT: snprintf() to include variable in log message content. **/
	char message[LOG_MESSAGE_LEN] ={0};
	snprintf(message, LOG_MESSAGE_LEN, "Read %d lines from %s", countRead, fileName);
	
	Logger(message, INFO);
	
	
	
	subject *p = subjects;
	
	//~ int nSubjects = sizeof(subjects) / sizeof(subject);
	//~ for (int i = 0; i < nSubjects; i++)
	
	for (int i = 0; i < countRead; i++)
	{
		
		SplitStringByFirstDelimiter(p->entry, delimiterChar,
									p->name, p->gradesStr,
									p->nameLen, p->gradeStrLen);
		
		int intArr[GRADES_COUNT] = {0}; /** Reset for each struct in struct-array.**/
		
		/** StringToList ==> char[]: "5, 4, 3, 4" --> int[]: [5, 4, 3, 4]**/
		int intArrLen = StringToIntArray(p->gradesStr, intArr, pDelimiter, p); // maybe use instead "delimiter"
		p->gradesLen = intArrLen;
		
		int j = 0;
		for (j = 0; j < intArrLen; j++)
		{
			/** Limit p->grades int-arr[] length. NB: 'intArrLen' will be basis for subject's grades array len ('p->gradesLen')**/
			if (j >= GRADES_COUNT2 - 1) // we want to display 13 grades. j:[0-12]
			//~ if (j >= GRADES_COUNT - 1) // we want to display 13 grades. j:[0-12]
			// remember j: IF j >= 14-1 (GRADES_COUNT == 14).
			// thus, breaks on j:13, not giving space value to p->grades[13].
			{
				/** IMPORTANT: snprintf() to include variable in log message content. **/
				char message[LOG_MESSAGE_LEN] = {0};
				snprintf(message, LOG_MESSAGE_LEN,
				 "Limit %d. Grade '%d' [i:%d] skipped in %s",
									GRADES_COUNT, intArr[j], j, p->name);
				Logger(message, ERROR);
				
				break;
			}
			p->grades[j] = intArr[j]; /** struct's int[] will be populated.**/
		} /** End of p->grades[] loops**/
		
		p->gradesLen = j; // IMPORTANT. Store limited/modified length to struct. 
		
		
		int sum = GetSumOfGrades(p);
		p->gradesSum = sum;
		p->average = GetAverageOfGrades(p, sum);
		
		p++; // Move pointer to next 'subjects' array-element's pointer.
	} /** End of OUTER, structure loop (p++)**/
	
	PrintStructArray(subjects, countRead);

	#ifdef DEBUG
	printf("\n Successfully ran '%s'\n", __FUNCTION__);
	#endif
	
	Logger("Program successfully ran to end.", INFO);
	
	if (usersLogLevel != OFF)
		printf("Log messages can be found in '%s' file.\n", logfileName);
	else
		printf("Logs were not collected due to 'OFF' logging status.\n");

    return EXIT_SUCCESS;
}



/**
 *  Finds the index of delimiter characters index. This is used in 
 * 	function "SplitStringByFirstDelimiter"
 *  **/
int GetIndexOfFirstDelimiter(char *sourceStr, char delimiterChar)
{
	int len = (int)strlen(sourceStr);
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

	
/*
 * Prompts for to read data from CSV or SPACE-DELIMITED
 */

void PromptCsvOrSpaceDelimited(char fileName[FILE_NAME_LEN])
{
	printf("Do you want to read from CSV file '%s'\n", FILE_NAME_CSV);
	if (PromptYesNo() == false)
	{
		strcpy(fileName, FILE_NAME_SPC_DELIM); //b2;
		printf("Data will be read from file '%s'\n", FILE_NAME_SPC_DELIM);
	}
	else
	{
		strcpy(fileName, FILE_NAME_CSV); //b2
		printf("Data will be read from CSV file '%s'\n", FILE_NAME_CSV);
	}
}
