#include "log_helper.h"

//~ #include "struct_helper.h"
#include "main.h"

#include <stdio.h>

char globalFilename[LOG_FILE_NAME_LEN] = "log.txt";
int globallySetLogLevel = OFF;


/**
void InitGlobalVariables(void)
{
	globalFilename = "log.txt";
	globalDefaultLogExtention = ".log"
}
**/


/**
 * Ask user to choose a filename where logs will be sent. Avoid empty input.
 */
void PromptLogFileName(char newFilename[LOG_FILE_NAME_LEN])
{
	puts("Please enter a filename where logs will be sent to.");
	putchar('>');
	
	while (true)
	{
		//~ char newFilename[LOG_FILE_NAME_LEN] = {0}; // reset.
		scanf("%s", newFilename);
		
		if (strcmp(newFilename, "") != 0)
			break;
	}
	printf("Log messages will be written to '%s' file.", newFilename);
}

/** 
 * Ask user to choose to allow logging, and prompt to choose level.
 **/
enum LogLevel PromptEnableDisableLogging(void)
{
	int newLogLevel = 0;
	/** Firstly, ask if user wants to log or not**/
	puts("Do you want to enable logging?");
	if (PromptYesNo() == false)
	{
		newLogLevel = OFF;
		//~ return; /** week05 template - csv stasttics (covid)**/
	}
	else /** If user wants, then ask for log level. **/
	{
		newLogLevel = PromptLogLevel();
	}
	putchar('\n'); /** Tip: After scanf() function calls, use putchar() always.**/
	
	/** Constant array gives string to concat to log message, by indexing with 'enum logLevel' **/
	const char globalLogLvls[N_LVLS][N_LVL_STR_LEN]  = {
										[OFF] = "OFF",
										[ERROR] = "ERROR",
										[WARNING] = "WARNING",
										[INFO] = "INFO",
										};
	
	printf("Program will continue with logging level '%s'.\n", globalLogLvls[newLogLevel]);
	return newLogLevel;
}

/*
 * Prompts for user confirmation until received
 */
bool PromptYesNo(void)
{
	puts("Enter [Y] or [N]");
	putchar('>');
	char c;
	while (true)
	{
		c = (char)getchar();
		if (c == '\n')
			continue;
		if (c == 'y' || c == 'Y')
			return true;
		else if (c == 'n' || c == 'N')
			return false;
		else
			printf("Please enter y or n!\n");
	}
}

/*
 * Prompts for user confirmation until received
 */
enum LogLevel PromptLogLevel(void)
{
	puts("\nChoose level of log messages you want to see. \nType one of these options: "
		 "\n* 'INFO'  	<- log all log messages (categories: INFO, WARNING, ERROR)"
		 "\n* 'WARNING'  	<- log warnings and error log messages (categories: strictly WARNING and ERROR)"
		 "\n* 'ERROR'  	<- log only error log messages (categories: ERROR)"
		 "\n* 'OFF'  	<- do not log any messages (categories: -)\n");
	putchar('>');
	
	char userChosenLevel[LVL_INPUT] = {0};
	
	//~ if (scanf("%s", userChosenLevel) == 1) // WRONG : takes entire string with spaces.
	
	scanf("%s", userChosenLevel);
	if (strcmp(userChosenLevel, "INFO") == 0 
		|| strcmp(userChosenLevel, "info") == 0)
		return INFO;
		
	else if (strcmp(userChosenLevel, "WARNING") == 0 
		|| strcmp(userChosenLevel, "warning") == 0)
		return WARNING;
		
	else if (strcmp(userChosenLevel, "ERROR") == 0 
		|| strcmp(userChosenLevel, "error") == 0)
		return ERROR;
		
	else if (strcmp(userChosenLevel, "OFF") == 0 
		|| strcmp(userChosenLevel, "off") == 0)
		return OFF;
		
	/** Reaches here if user inserts anything else (not INFO, WARNING ERROR or OFF)**/
	printf("Your selected value is not matching. Default logging level 'WARNING' is set.\n");
	return WARNING;
}


/**
 * Assign new logging level, and storing into global variable. (setter function)
 **/
void LoggerSetLoggingLevel(enum LogLevel newLogLvl)
{
	#ifdef DEBUG_L 
	printf("\nGloballySetLogLevel: %d, newLogLevel: %d\n", globallySetLogLevel, newLogLvl);
	#endif
	
	/** Setter function. Do not return. Storing value to global variable.**/
	globallySetLogLevel = newLogLvl;
}



void LoggerSetOutputName(char newFilename[LOG_FILE_NAME_LEN])
//~ void LoggerSetOutputName(char *newFilename)
{
	/** Checks if user-chosen 'globalFilename.<ext>' is **/
	//~ globalFilename = newFilename;
	strncpy(globalFilename, newFilename, LOG_FILE_NAME_LEN - 1);
	
	if (!IsValidLogExtention(newFilename))
	{
		char globalDefaultLogExtention[EXT_LEN] = ".log";
		
		char concattedFileName[LOG_FILE_NAME_LEN] = {0};
		ConcatLogExtention(newFilename, concattedFileName, globalDefaultLogExtention);

		strncpy(globalFilename, concattedFileName, LOG_FILE_NAME_LEN - EXT_LEN - 1); // REMOVE -1?
		//~ globalFileName = concattedFileName;
		//~ snprintf(globalFilename, LOG_FILE_NAME_LEN, "%s", concattedFileName);
		
	}
	else
	{
		//~ globalFilename = newFilename;
		strncpy(globalFilename, newFilename, LOG_FILE_NAME_LEN - EXT_LEN - 1); // THIS BROKEN
		//~ snprintf(globalFilename, LOG_FILE_NAME_LEN - 1, "%s", newFilename); // THIS BROKEN!
		
	}
}

bool IsLogFormatCorrect(char extention[USER_EXT_LEN])
{
	const char allowedLogfileExtentions[N_FORMATS][FORMAT_LEN] = {".txt", ".log"}; 
	
	int nFormats = sizeof(allowedLogfileExtentions) / sizeof(allowedLogfileExtentions[0]);
	
	/** Loop through [.txt, .log] array to compare if user chosen ext
	 * 	 is matching, and thus correct log format. If not, return false.**/
	for (int i = 0; i < nFormats; i++) // swap nFormats with N_FORMAT?
	{
		if (strcmp(extention, allowedLogfileExtentions[i]) == 0)
		{
			return true;
		}
	}
	return false; /** cannot optimise by <return !strcmp....> because looping an array-**/
}

bool IsValidLogExtention(char fileName[LOG_FILE_NAME_LEN])
{
	/** NB! 'globalFilename' variable is global-variable.**/
	char delimiterChar = '.';
	int delimiterIndex = GetIndexOfLastDelimiter(fileName, delimiterChar);
	
	/** Step 1. Populate string 'fileTitle'.
	 * 		1) Create substring <logfile> from  logfile.txt. 
	 * 		2) Return length of 'logfile' substring. **/
	char fileTitle[LOG_FILE_NAME_LEN] = {0};
	int fileTitleLen = SplitFilenameToGetFileTitle(fileTitle, delimiterIndex); 
	
		
	#ifdef DEBUG_L
	printf("\nDEBUG: fileTtitle: %s. extLen: %s", fileTitle, fileTitleLen);
	#endif 
	
	/** Step 2. Populate string 'extention'.
	 * 		1) Create substring <.txt> from  logfile.txt. 
	 * 		2) Return length of 'extention' substring. **/
	
	char extention[USER_EXT_LEN] = {0};
	
	#ifdef DEBUG_L
	printf("\nDEBUG: extention: %s", extention);
	#endif 
	
	int extLen = SplitFilenameToGetFileExtention(extention, delimiterIndex); // unused
	
	
	#ifdef DEBUG_L
	printf("\nDEBUG: extention: %s. extLen: %s", extention, extLen);
	#endif 
	
	/** Return 'true' if <.txt> is found in const array = [".txt", ".text", ".md"] **/
	return IsLogFormatCorrect(extention); 
}

/** 
 * Concat '.log' or '.txt' to globalFilename to be readable fileformat.
 * **/
void ConcatLogExtention(char fileName[LOG_FILE_NAME_LEN], char concattedFileNameWithExtention[LOG_FILE_NAME_LEN - EXT_LEN - 1], char logExt[EXT_LEN])
{
	/** Get length of desired globalFilename**/
	//~ int len = (int)strlen(fileName);
	
	/** Truncate "too lengthy" 'desired' globalFilename string in lenght, if its length larger than [LOG_FILE_NAME_LEN] **/
	char truncatedFilename[LOG_FILE_NAME_LEN - EXT_LEN - 1] = {0};
	
	snprintf(truncatedFilename, (LOG_FILE_NAME_LEN - EXT_LEN - 1), "%s", fileName);
	/** EXT_LEN is fixed as 5.
	 * .log OR .txt are both in lenght of 4 + '\0' == 5
	 *  snprinf() requires length to be n-1 to append '\0' to end of string**/
	 
	
	/** Concat .log (or other extention) to 'truncated' globalFilename **/
	snprintf(concattedFileNameWithExtention, (LOG_FILE_NAME_LEN - 1), "%s%s", truncatedFilename, logExt);
	
	/** void Fn.**/
}


/**
 *  substringLen = GetSubStringByIndexRange(soureString, startIndex, endIndex, destinationSubstring)
 *  startIndex is inclusive, but endIndex is not inclusive. *
 * */
int SplitFilenameToGetFileTitle(char *fileTitle, int delimiterIndex)
{
	

	
	int fileTitleLen = GetSubstringByIndexRange(globalFilename, 0, delimiterIndex, fileTitle); 
	
	#ifdef DEBUG_L
	printf("Dot is at index: %d ('delimiterIndex')\n", delimiterIndex);
	printf("File title without extention is: %s ('filetitle')\n", fileTitle);
	#endif
	
	return fileTitleLen;
}	

/**
 * Splitting "file.txt" into ".txt" substring, and returning lenght of string (char-array)
 **/
int SplitFilenameToGetFileExtention(char extention[USER_EXT_LEN], int delimiterIndex)
{
	int globalFilenameLen = (int)strlen(globalFilename);
	
	#ifdef DEBUG_L
	printf("\nDEBUG: Global variable's string-length is: %d ('globalFilenameLen')\n", globalFilenameLen);
	#endif
	
	int extLen = GetSubstringByIndexRange(globalFilename, delimiterIndex, globalFilenameLen, extention);
	
	return extLen;
}

//~ void Logger(char logMessage[MES_LEN])
/**
 * Logging message, if message's loglevel matches by the previously set-loglevel
 * 	 ('globallySetLogLevel') == 'chosenLogLevel')
 **/
void Logger(char *logMessage, enum LogLevel messageLogLevel)
{
	
	char logEntry[LOG_ENTRY_LEN] = {0};

	switch (globallySetLogLevel)
	//~ switch (messageLogLevel)
	{
		case OFF: // should I move this to default?
			#ifdef DEBUG_L
			puts("\nOFF match\n");
			#endif
			
			break;
		case ERROR: /** ERROR level means write log-messages with only ERROR level **/
			//~ if (globallySetLogLevel == messageLogLevel)
			if (messageLogLevel == ERROR) // enum type.
			{
				#ifdef DEBUG_L
				puts("\nerror match\n");
				#endif
				
				TimestampLogMessage(logMessage, messageLogLevel, logEntry);
				WriteLogToFile(logEntry);
			}
			break;
		case WARNING: /** Warning lvel means write log-message with lvl either ERROR or WARNING, but not anything else (not INFO!!) **/
			//~ if (globallySetLogLevel == messageLogLevel
			if (messageLogLevel == WARNING
			|| messageLogLevel == ERROR)
			//~ if (globallySetLogLevel == WARNING
			//~ || globallySetLogLevel == ERROR)
			{
				#ifdef DEBUG_L
				puts("\nwarning+error match\n");
				#endif
				
				TimestampLogMessage(logMessage, messageLogLevel, logEntry);
				WriteLogToFile(logEntry);
			}
			break;
		case INFO: /** INFO level means write any message with any level 
					This does not mean outside scope (example: LOG_OFF, LOG_UNKNOWN, etc undefined.)**/
			if (messageLogLevel == WARNING
			|| messageLogLevel == ERROR
			|| messageLogLevel == INFO)
			{
								
				#ifdef DEBUG_L
				puts("\ninfo match\n");
				#endif
				
				TimestampLogMessage(logMessage, messageLogLevel, logEntry);
				WriteLogToFile(logEntry);
			}
			break;
		default:
		
			#ifdef DEBUG_L
			puts("\nunknown match\n");
			#endif
			
			break;
	}	
}

/**
 * Writing a log message to file. Opens file, writes and then closes file.
 **/

void TimestampLogMessage(char *logMessage, enum LogLevel messageLogLevel, char logEntry[LOG_ENTRY_LEN])
{
	/** Time-stamps implemented if 'strftime' library function.
	 * https://cplusplus.com/reference/ctime/strftime/
	 * **/
	//~ char logEntry[LOG_ENTRY_LEN] = {0};
	
	// Step 1: Create time-entry
	time_t currentTime;
	struct tm *currentTimeStruct;
	char bufferTime[TIMESTAMP_LEN];
	
	time(&currentTime);
	currentTimeStruct = localtime(&currentTime);
	
	/** %F => 2001-08-23. Equivalent to %Y-%m-%d**/
	/** %T => 14:55:02. Equivalent to %H:%M:%S  ISO-8601 time format. **/
	/** %Z => Timezone abbreviation or name. **/
	strftime(bufferTime, TIMESTAMP_LEN, "%F %T %Z", currentTimeStruct);
	
	/**
	//~ // %R is for HH:MM and %Z shows timezone if available
	//~ strftime(buf, 64, "%R %Z", currentTimeStruct);
	//~ printf("Time is %s\n", buf);
	
	//~ // %d - day without preceding 0, %b - full month name 
	//~ strftime(buf, 64, "%d. %B", currentTimeStruct);
	//~ printf("Today is %s\n", buf);
	**/ 

		 
	/** Constant array gives string to concat to log message, by indexing with 'enum logLevel' **/
	const char globalLogLvls[N_LVLS][N_LVL_STR_LEN]  = {
										[OFF] = "OFF",
										[ERROR] = "ERROR",
										[WARNING] = "WARNING",
										[INFO] = "INFO",
										};
	
	//~ snprintf(logEntry, LOG_ENTRY_LEN, "%s %s %s", bufferTime, globalLogLvls[globallySetLogLevel], logMessage);
	
	snprintf(logEntry, LOG_ENTRY_LEN, "%s %s: %s", bufferTime, globalLogLvls[messageLogLevel], logMessage);
	/** A terminating null character is automatically appended after the content written.**/
	/** https://cplusplus.com/reference/cstdio/snprintf/ **/
	
	#ifdef PRINT_TERMINAL
	printf("\n%s\n", logEntry); // Printing to terminal
	#endif
}



/**
 * Writing a log message to file. Opens file, writes and then closes file.
 **/	
void WriteLogToFile(char logEntry[LOG_ENTRY_LEN])
{
	/** pointer for file stream (input file streams) **/
	FILE *fOutStream;
    fOutStream = fopen(globalFilename, "a");
    
    /** Check if file stream EMPTY for file "input.txt" **/
	if (fOutStream == NULL)
	{
		/** Logifaili avamise ebaõnnestumisel peab programm jätkama tööd, mitte väljuma! 
		 * Teavita kasutajat logimise ebaõnnestumisest.**/
		 
		snprintf(logEntry, LOG_ENTRY_LEN, "Error opening logfile '%s'", globalFilename);
		printf("\n%s\n", logEntry); /** Informint user that we cannot open logfile**/
	}
	else
	{
		fprintf(fOutStream, "\n%s\n", logEntry); /** Write to file **/
		/** Closing file-stream **/
		fclose(fOutStream);
	}	
}

/**
 *  Compares if a single character is identical to delimiter symbol
 *  **/

bool IsDelimiter(char character, char delimiterChar)
{
	return character == delimiterChar;
}

/**
 *  Finds the  1st index of delimiter characters. This is used in 
 * 	function "SplitStringByFirstDelimiter"
 *  **/
int GetIndexOfDelimiter(char sourceStr[LOG_FILE_NAME_LEN], char delimiterChar)
{
	int len = (int)strlen(sourceStr);
	int i = 0;
	for (i = 0; i < len; i++)
	{
		if (IsDelimiter(sourceStr[i], delimiterChar))
		{
			#ifdef DEBUG
			printf("\n Successfully ran '%s'\n", __FUNCTION__);
			#endif
			
			return i;
		}
	}
	
	return i; // Problem. If not delimiter, returns last index. If length sourceStr empty, tne delimiterIndex = 0;
	
	//~ fprintf(stderr, "Error: No delimiter characted found\n."); 
	//~ exit(EXIT_FAILURE);
}
/**
 *  Finds the  n-th (last) index of delimiter characters. This is used in 
 * 	function "SplitStringByFirstDelimiter"
 *  **/

int GetIndexOfLastDelimiter(char sourceStr[LOG_FILE_NAME_LEN], char delimiterChar)
{
	int len = (int)strlen(sourceStr);

	/** delimiter index:**/
	int delimiterIndex = 0;

	int i = 0;
	for (i = 0; i < len; i++)
	{
		if (IsDelimiter(sourceStr[i], delimiterChar))
		{
			//~ #ifdef DEBUG
			//~ printf("\n Successfully ran '%s'\n", __FUNCTION__);
			//~ #endif
			
			delimiterIndex = i;
		}
	}
	
	return delimiterIndex; // Problem. If not delimiter, returns last index. If length sourceStr empty, tne delimiterIndex = 0;
	
	//~ fprintf(stderr, "Error: No delimiter characted found\n."); 
	//~ exit(EXIT_FAILURE);
}

/**
 * Function to get a substring ('token') of a source-string, by range of index.
 * 		startIndex is inclusive. EndIndex is NOT inclusive.
 *  **/
int GetSubstringByIndexRange(char sourceStr[LOG_FILE_NAME_LEN], int startIndex, int endIndex, char *token) 
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
	
	//~ token[cnt + 1] = '\0';
	//~ int len = strlen(token);
	
	//~ printf("len: %d\n", len);
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
