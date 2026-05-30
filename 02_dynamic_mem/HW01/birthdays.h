
/** Header-file **/
#ifndef LIB_H
#define LIB_H

#include <stdio.h> 
#include <stdbool.h> 
#include <stdlib.h>
#include <stdbool.h> 
#include <stdint.h>
#include <ctype.h>
#include <string.h>

//~ #define DEBUG 1
#define MONTHS_12 13	

#define OUTPUT_FILENAME "output.txt"  // base solution

#define STR_NAME_LEN 100	

#define DATE_LEN 11		

#define ARGS_CNT 4
#define ARGS_FILE_OUTPUT_FILENAME argv[2]
#define ARGS_FILE_INPUT_FILENAME argv[1]
#define ARGS_EXEC_NAME argv[0]

#define MAX_PERSON 64	
#define MAX_STR 256		
#define MAX_STR_512 1024

/** Bubble Sort function**/
#define NOT_ALREADY_SORTED 1
#define ALREADY_SORTED 0

#define MAX 100 	

/** Date verification **/
#define MIN_DAYS 1 
#define MIN_MONTH 1 
#define MAX_MONTH 12 
#define YEAR_MIN 1900 
#define YEAR_MAX 2100 
#define DATE_INVALID 0 
#define DATE_VALID 1 
#define ZERO 0

/** For function isCorrectInputFormat **/
#define DAY_DOT_INDEX 2
#define MONTH_DOT_INDEX 5

/** Length for char-array variable "formatForSorting" **/
#define FORMAT_LEN 11
#define DAY_2DIGIT_LEN 2
#define MONTH_2DIGIT_LEN 2
#define YEAR_4DIGIT_LEN 4

/** Booleans **/	
#define IS_CORRECT 1 
#define NOT_CORRECT 0

/** User input max allowed attempts**/
#define MAX_ATTEMPTS 3

/** For printing SeparatingLines.**/
#define BUFFER 9

/** Extra-Task:**/
#define ARGS_POS_0 0
#define ARGS_POS_1 1
#define ARGS_POS_2 2
#define ARGS_POS_3 3

#define MAX_ARG_LEN 100

#define PROMPT_NOT_DISABLED 0
#define PROMPT_DISABLED 1


typedef struct birthdate
{
	int day;
	int month;
	int year;
	
	char dateStr[DATE_LEN];
	bool isValidBirthDate;
	bool isBirthDay;
	bool isBirthDayInTwoWeeks;
	
	char formatForSorting[FORMAT_LEN];
} birthdate;

 
typedef struct person
{
	char firstName[STR_NAME_LEN];
	birthdate dateOfBirth;
	int age;
} person;


enum Months 
{
	INVALID_MONTH_0, 
	JAN, FEB, MARCH, APR, MAY, JUN, JUL, AUG, SEPT, OCT, NOV, DEC
};

int GetDaysInMonthEnum(int month, int year); 

void AskInputDate(char *pInput, int maxAttempts);

bool IsValidDate(int day, int month, int year);
bool IsCorrectInputFormat(char str[DATE_LEN], int limit);

void ZeroInitializeBooleansAndIntegers(person *pPerson);

int ReadFileToStruct(person *pStr, int limit, char *filename);

int GetDaysInMonth(int inputMonth, int inputYear);
bool IsLeapYear(int year);

bool isBirthday(person *pPerson, int inputDay, int inputMonth, int inputYear);
bool IsBirthdayInTwoWeeks(person *pPerson, int inputDay, int inputMonth, int inputYear);

void WriteToFile(person *pPerson, int personCount, int limit,
			char *filename, int birthdayCount, int birthdayIn14daysCnt,
			int inputDay, int inputMonth, int inputYear); 
			
void InitializeStructWithValidBirthDate(person *pPerson, int personCount);	
int PersonsWithBirthdays(person *pPerson, int personCount, int inputDay, int inputMonth, int inputYear);			
int PersonsWithBirthdaysInTwoWeeks(person *pPerson, int personCount, int inputDay, int inputMonth, int inputYear);			

void InitializeFieldForDateSorting(person *pPerson, int personCount);
void BubbleSortStruct(person *pStr, int len);


void CreateSeparatingPrintLn(char headerLine[MAX_STR], int buffer, char *pSeparatingLine);

int CreateOutputString(char stdoutStream[MAX_STR_512], person *pPerson,
								 int personCount, int limit, 
								 int cntBirthdayPeople,
								 int cntBirthdayInTwoWeeksPeople,
								 int inputDay, int inputMonth, int inputYear);
								 
void WriteStdoutToFile(int size, char stdoutStream[MAX_STR_512], char filename[STR_NAME_LEN]);

/** Program's modes**/
bool IsHelpMode(char *argv[MAX_ARG_LEN]);
void RunHelpMode();

bool IsPromptDisabledMode(char *argv[MAX_ARG_LEN], int index);

void GetProgramModeSuffix(char *argv[MAX_ARG_LEN], char cliArgument[STR_NAME_LEN], int argsIndex);
bool IsDefaultFileInputMode(char cliArgument[STR_NAME_LEN]);


bool IsOutputFileMode(char cliSuffix[STR_NAME_LEN]);

void GetFilename(char *argv[MAX_ARG_LEN], char cliSuffix[STR_NAME_LEN],
                 char filename[STR_NAME_LEN], int argIndex);
                 
                 
int ParseAllEntriesToStructFromInputFile(char inputFile[STR_NAME_LEN], 
									char stdoutStream[MAX_STR_512]);
	
void RunProgram(char inputFile[STR_NAME_LEN],
									char *outputFile,
									bool isPromptModeDisabled);

void Usage();

void DebugString(char str[STR_NAME_LEN]);                 

void DebugArgs(int argc, char **argv);

/** Contents here // **/
#endif // LIBRARY_H

