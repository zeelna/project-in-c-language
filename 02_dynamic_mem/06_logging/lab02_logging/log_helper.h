#ifndef LOG_HELPER_H
#define LOG_HELPER_H

#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "struct_helper.h"

//~ #define DEBUG_L 1

//~ #define PRINT_TERMINAL 1

#define LOG_ENTRY_LEN 100
#define TIMESTAMP_LEN 32
#define LOG_MESSAGE_LEN (LOG_ENTRY_LEN - TIMESTAMP_LEN) 

#define LOG_FILE_NAME_LEN 20

#define N_FORMATS 2
#define FORMAT_LEN 10

#define EXT_LEN 5

#define USER_EXT_LEN 10

#define N_LVLS 4
#define N_LVL_STR_LEN 8

#define LVL_INPUT 10

enum LogLevel {OFF, ERROR, WARNING, INFO};

/**
 * Description:		Prompt user to select log level. If choses unknow value,
 * 					then default logging value is hardcoded 'WARNING'
 * 
 * Parameters:		void
 * 	
 * Returns:			enum LogLevel:  user's chosen loglevel for program.		
 * */
enum LogLevel PromptEnableDisableLogging(void);

/**
 * Description:		Prompt user to select 'Yes' or 'No' to logging,
 * 
 * Parameters:		
 * 	
 * Returns:			Yes is true, No is false,	
 * */
bool PromptYesNo(void);

/**
 * Description:		Prompt user to select log level. If choses unknow value,
 * 					then default logging value is hardcoded 'WARNING'
 * 					
 * V				alues to select (INFO; WARNING; ERROR; OFF)
 * 
 * Parameters:		-
 * 	
 * Returns:			enum LogLevel:  user's chosen loglevel for program.		
 * */
enum LogLevel PromptLogLevel(void);

/**
 * Description:		1. Sets the logging level by user's input. (setter)
 * 					Writes the value as 'globallySetLogLevel'.
 * 
 * Parameters:		char[]: 		logMessage - the message we want to log file
 * 					enum LogLevel:  newLogLvl - 'messageLoglevel'
 * 	
 * Returns:			(void) writes timestap + log message to file		
 * */
void LoggerSetLoggingLevel(enum LogLevel newLogLvl);

/**
 * Description:		Function checks if LoggingLevel chosen by user,
 * 						allows this log-message to be logged into a file.
 * 
 * 					This function worsk two fold: 	
 * 					1) switch to verify loglevels
 * 
 *					2) wrapper function for two subfunctions:
 * 						Functions that will be called out:
 * 						1. Creates a log with timestamp and message.
 * 							 Truncates if too long.
 * 						2. Writes to logfile. 
 * 							if logfile cannot be opened, print message
 * 
 * Parameters:		char[]: 		logMessage - the message we want to log file
 * 					enum LogLevel:  chosenLogLevel - 'messageLoglevel'
 * 	
 * Returns:			(void) writes timestap + log message to file		
 * */
//~ void Logger(char *logMessage);
void Logger(char *logMessage, enum LogLevel messageLogLevel);

/**
 * Description:		1. Timestamp log message
 * 					2. Concat log level of message ("ERROR:", "INFO:" or "WARNING:")
 * 					3. Concat message to log-line ('logEntry'), but Truncates if too long.
 * 					
 * Parameters:		char[]: 			logMessage - the message we want to log file
 * 					enum LogLevel:  	chosenLogLevel - 'messageLoglevel'
 * 					char[] logEntry: 	final message with timestamp & loglevel.
 * 	
 * Returns:			(void) populates final log, the variable 'logEntry'
 * 									 (to be later written to logfile)
 * */
void TimestampLogMessage(char *logMessage, enum LogLevel messageLogLevel, char logEntry[LOG_ENTRY_LEN]);

/**
 * Description:		
 * 					2. Writes log message to logfile.
 * 					 if logfile cannot be opened, print message in terminal
 * 
 * Parameters:		char[]: 		logMessage - the message we want to log file
 * 					enum LogLevel:  chosenLogLevel - 'messageLoglevel'
 * 	
 * Returns:			(void) writes timestap + log message to file		
 * */
void WriteLogToFile(char logEntry[LOG_ENTRY_LEN]);

/**
 * Description:		Set logfile name where logs are written to.
 * 					This function calls helper functions.
 * 
 * 					If user's chosen filename is matchin .txt or .log
 * 					then add ".log" extention by default.
 * 					 * if necessary, truncate by length to fit ".log"
 * 					
 * Parameters:		char[]: newFilename <= user's chosen filename
 * 	
 * Returns:			(void) global-variable 'globalFilename' is set (rewritten)
 * */

void LoggerSetOutputName(char newFilename[LOG_FILE_NAME_LEN]);
//~ void LoggerSetOutputName(char *newFilename);

/**
 * Description:		Initializes Global variables with static values

 * Parameters:		(void). P.S: values are statically assigned
 * 	
 * Returns:			(void) Initializes values to global variables		
 * */
 
 
 /**
 * Ask user to choose a filename where logs will be sent. Avoid empty input.
 */
void PromptLogFileName(char newFilename[LOG_FILE_NAME_LEN]);

/**
 * Intialize values to global variables.
 **/
void InitGlobalVariables(void);


/** Prototype's for functions. Aim is to validate if user's chosen
 *  file extention is ".log" or ".txt"**/


/**
 * Description:		Find the delimiter in source string.
 * 					 In this case, we find dot (.) in "filename.txt"
 * 
 * Parameters:		char[]: sourceStr   <= string where we find delimiter's index
 * 					char: delimiterChar <= delimiter char we are seeking
 * 	
 * Returns:			index of delimiter (dot)
 * */
//~ int GetSubstringByIndexRange(char sourceStr[LOG_FILE_NAME_LEN], int startIndex, int endIndex, char token[LOG_FILE_NAME_LEN]);
int GetSubstringByIndexRange(char sourceStr[LOG_FILE_NAME_LEN], int startIndex, int endIndex, char *token);
 
 
 
/**
 * Description:		Find first delimiter in source string.
 * 					 In this case, we find dot (.) in "filename.txt"
 * 
 * Parameters:		char[]: sourceStr   <= string where we find delimiter's index
 * 					char: delimiterChar <= delimiter char we are seeking
 * 	
 * Returns:			index of delimiter (dot), first occurence
 * */
int GetIndexOfDelimiter(char sourceStr[LOG_FILE_NAME_LEN], char delimiterChar);


// Version two. Aim: find last delimiter's index
// (example log.today.txt)
// last index is 8 AND return that.  (NB: first index is 3).
/**
 * Description:		Find last delimiter in source string.
 * 					 In this case, we find dot (.) in "filename.txt"
 * 
 * Parameters:		char[]: sourceStr   <= string where we find delimiter's index
 * 					char: delimiterChar <= delimiter char we are seeking
 * 	
 * Returns:			index of delimiter (dot), last occurence
 * */
int GetIndexOfLastDelimiter(char sourceStr[LOG_FILE_NAME_LEN], char delimiterChar);



/**
 * Description:		Compares if characted (in string) matches with delimiter.
 * 					'.' is the delimiter here. Example: [log.txt]
 * 
 * Parameters:		char: 'character' we compare
 * 					char: 'delimiterChar' is what we compare to.
 * 	
 * Returns:			true or false		
 * */
bool IsDelimiter(char character, char delimiterChar);


 /** Description:		Wrapper Fn: 
 * 					1. Firstly, finds global-variable 'globalFilename' length.
 * 					2. Secondly, Calls out 'GetSubstringByIndexRange' to 
 * 						to populate 'extention' string with symbols starting
 * 						from delimiter (.) to end of substring, AND adding \0 
 * 						as null-terminator to end of substring.
 * 
 * Parameters:		char: 'character' we compare
 * 					char: 'extention' (null-initialized) is populated/filled with 
 * 	
 * Returns:			int: 'extLen'. The length of substring containing extention
 * 									example: [.txt] <== extLen = 4 ( +1 for '\0')
 * */
int SplitFilenameToGetFileExtention(char extention[USER_EXT_LEN], int delimiterIndex);

 
 /**
 * Description:		Wrapper Fn: 
 * 					1. Firstly, Calls out 'GetSubstringByIndexRange' to 
 * 						to populate string 'fileTitle' (example "[log2].txt")
 * 						with symbols starting index=0 until delimiter found.
 * 					2.  Adding null-terminator to end of substring 'fileTitle'.
 * 
 * Parameters:		char: 'fileTitle' (null-initialized) to be  populated/filled 
 * 					int: 'delimiterIndex'. This is the index where we stop populating array.
 * 	
 * Returns:			int: 'fileTitleLen'. The length of substring containing 'fileTitle'
 * 									example: [2log] <== lenght = 4 ( +1 for '\0')
 * */
int SplitFilenameToGetFileTitle(char* fileTitle, int delimiterIndex);


/**
 * Description:		Concat '.log' or '.txt' to globalFilename to be readable fileformat.
 * 
 * 					1. Context, this Function is called out if
 * 						"IsValidLogExtention" is FALSE.
 * 							meaning that user-chosen filename does NOT
 * 							match with log-formats ('.txt' OR '.log')
 * 
 * 					2. Firstly, forcefully truncate the user 
 * 						chosen filename to max-length,
 * 						 but minus ".log" / ".txt" length
 * 
 * 					3. Secodly, use the 'truncated' filename
 * 						AND concat the default log-format,
 * 						that is statically/by default ".log"
 *
 * Parameters:		char: fileName[LOG_FILE_NAME_LEN]. <== user's chosen filename
 * 
 * 					char: concattedFileNameWithExtention[LOG_FILE_NAME_LEN] 
 * 						<== truncated in length and concatted with '.log'
 * 
 *  				char: logExt[EXT_LEN]) <=== '.log'
 * 
 * Returns:			void (populate 'concattedFileNameWithExtention')
 * */
void ConcatLogExtention(char fileName[LOG_FILE_NAME_LEN], char concattedFileNameWithExtention[LOG_FILE_NAME_LEN - EXT_LEN - 1], char logExt[EXT_LEN]);

/**
 * Description:		Concat '.log' or '.txt' to globalFilename to be readable fileformat.
 * 
 * 					1. Context, this Function is called out verify
 * 						"Is user's chosen filename extention matching
 * 						 one of these: {".txt", ".log"}?"
 * 						
 * 
 * 					2. Firstly, get the index of delimiter (dot)
 * 						that helps separate <filename.txt>
 * 
 * 					3. Secodly, split by index to <filename> AND <.txt>
 * 					4. Thirdly, populate these two substrings 
 * 									fileTitle = <filename>
 * 									extention = <.txt>
 * 					5. Fourtly, get the length of these substring
 * 					6. Lastly, check if 'extention' (.txt) is allowed-format
 * 						* allowed formats are {.log, .txt}
 *
 * Parameters:		char: fileName[LOG_FILE_NAME_LEN]. <== user's chosen filename

 * Returns:			truth-value by calling out 'IsLogFormatCorrect()'
 * */

bool IsValidLogExtention(char fileName[LOG_FILE_NAME_LEN]);

 
/**
 * Description:		Check whether user's chosen filename extention
 * 					is matching with allowed log-format extentions
 * 
 * 					"Is user's chosen filename extention matching
 * 						 one of these: {".txt", ".log"}?"

 * Parameters:		char: 'extention'. The populated string. Example ".log"

 * Returns:			true or false
 * */
bool IsLogFormatCorrect(char extention[USER_EXT_LEN]);


#endif // LOG_HELPER_H
