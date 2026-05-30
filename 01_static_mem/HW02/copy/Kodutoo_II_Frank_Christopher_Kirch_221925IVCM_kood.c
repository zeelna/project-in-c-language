#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define ONE 1
#define INTERACTIVE 1
#define DISABLED 0

#define MAX_SIZE 15
#define IS_EMPTY 1

#define NOT_ALREADY_SORTED 1
#define ALREADY_SORTED 0

#define LEADERBOARD 3

#define MIN_POINTS 0
#define MAX_POINTS 100

#define MAX_LEN 1
#define FILE_LEN 15

#define STR_MAX_LEN 20

#define ARGS_POS_0 0
#define ARGS_POS_1 1
#define ARGS_POS_2 2
#define ARGS_POS_3 3

#define MAX_ARGS_CNT 4

#define TRUE 1
#define FALSE 0

#define ERROR_INVALID_ARG_CNT 1
#define ERROR_INVALID_UNKNOWN_ARGS 2
#define ERROR_HELP 3
#define ERROR_INVALID_NAME 4 
#define ERROR_INVALID_SCORE 5 

#define INDEX_0 0

/** Base task Function prototypes: **/
void BaseTaskTemplate(bool isInteractiveMode, bool isDebugMode);

void Solution(int indicesArray[MAX_SIZE], int lenCnt,
              char names[MAX_SIZE][MAX_SIZE],
              double nums[MAX_SIZE], bool isInteractiveMode, bool isDebugMode);

              
int ReadArray(char names[MAX_SIZE][MAX_SIZE], double nums[MAX_SIZE],
              int max, bool isInteractiveMode, bool isDebugMode);

/** Helper function for names before sort**/
void DisplayNames(char names[MAX_SIZE][MAX_SIZE], int lenCnt);

/** Helper function for points before sort**/
void DisplayPoints(double nums[MAX_SIZE], int lenCnt);

/** Wrapper function to initiate Bubble Sort!**/
void SortCompetitors(char names[MAX_SIZE][MAX_SIZE],
                     double nums[MAX_SIZE], int indicesArray[MAX_SIZE],
                     int len, bool isInteractiveMode, bool isDebugMode);

/** Bubble sort standard Functions**/
void BubbleSort(double nums[MAX_SIZE], int indicesArray[MAX_SIZE], int len,
                bool isInteractiveMode, bool isDebugMode);
                
void PrintDescendingOrder(double nums[MAX_SIZE], int lenCnt);
void PrintAscendingOrder(double nums[MAX_SIZE], int lenCnt);

/** Mapping sorted Photography points to names, 
 *  to print Photographers names in sorted**/
void PrintDescendingNames(char names[MAX_SIZE][MAX_SIZE],
                          double nums[MAX_SIZE], int indicesArray[MAX_SIZE],
                          int len);
void PrintAscendingNames(char names[MAX_SIZE][MAX_SIZE],
                         double nums[MAX_SIZE], int indicesArray[MAX_SIZE],
                         int len);

/** Priting results**/
void DisplayTopLeaderboard(char names[MAX_SIZE][MAX_SIZE], 
                           double nums[MAX_SIZE], int indicesArray[MAX_SIZE], 
                           int lenCnt, int topCount, bool isDebugMode);
                           
void DisplayDisqualifiedCompetitors(char names[MAX_SIZE][MAX_SIZE],
                                    double nums[MAX_SIZE], 
                                    int indicesArray[MAX_SIZE],
                                    int lenCnt, bool isDebugMode);

int GetPosRearrangedPhotographer(int indicesArray[MAX_SIZE], int i);

/** Interactive mode (base task)**/
void AskNameInput(char names[MAX_SIZE][MAX_SIZE], int i,
                    bool isInteractiveMode, bool isDebugMode);

void AskDoubleInput(double nums[MAX_SIZE], int i,
                    bool isInteractiveMode, bool isDebugMode);
                    
/** Extra task Function prototypes **/
void GetString(char str[], int n);
void DebugString(char str[]);
int GetLength(char str[]);

bool IsOneOperandMode(int argc);

void DebugArgs(int argc, char **argv);
void CheckArgs(int argc, char **argv, int requiredCnt);

void ErrorHandler(int errCode);

bool IsHelpMode(char *argv[]);
bool IsVerboseMode(char *argv[]);

bool IsDebugMode(int argc, char **argv);

bool IsFileInputMode(char *argv[], char cliArgument[STR_MAX_LEN],
                     bool isDebugMode);
void GetFilename(char *argv[], char cliArgument[STR_MAX_LEN],
                 char inputFile[STR_MAX_LEN], bool isDebugMode);

bool IsPromptDisabledMode(char *argv[]);
bool IsPromptInteractiveMode(int argc, char *argv[]);


void RunPromptDisabledMode(char **argv);
void RunPromptInteractiveMode(char **argv);

void RunFileMode(int argc, char **argv, char inputFile[STR_MAX_LEN],
                bool isVerboseMode, bool isDebugMode);
                            
void RunVerboseMode(int argc, char **argv);
void RunHelpMode();
void Usage();

bool IsValidName(char name[MAX_SIZE], bool isInteractiveMode, bool isDebugMode);
bool IsValidScore(char strScore[MAX_SIZE], bool isInteractiveMode, bool isDebugMode);
double ConvertStrToDouble(char strScore[MAX_SIZE]);

bool IsPlus(char operand[MAX_SIZE], int i);

bool IsHyphen(char operand[MAX_SIZE], int i);
bool IsDot(char operand[MAX_SIZE], int i);

/** Description:    Main program
 * 
 *  Parameters:     command line argument count and vector              
 * 
 *  Result:         return 0 (success) 
 **/
int main(int argc, char *argv[])
{
    char cliArgument[STR_MAX_LEN];
    char inputFile[STR_MAX_LEN];
    
    bool isInteractiveMode = TRUE;
    bool isDebugMode = FALSE;
    bool isVerboseMode= FALSE;
    
    //~ DebugArgs(argc, argv);
    
    /** ./contest **/
    if (argc == 1)
        BaseTaskTemplate(isInteractiveMode, isDebugMode);
        
    else if (argc == 2)
    {
        /** ./contenst --help or ./contest -h**/
        if (IsHelpMode(argv))
        {
            RunHelpMode();
            exit(EXIT_SUCCESS); 
        }
        
        /** ./contest --input=file_name.txt**/    
        else if (IsFileInputMode(argv, cliArgument, isDebugMode))
        {
            bool isVerboseMode = FALSE;
            
            GetFilename(argv, cliArgument, inputFile, isDebugMode);
            /** Extra task **/
            RunFileMode(argc, argv, inputFile, isVerboseMode, isDebugMode);
        }

        else if (IsDebugMode(argc, argv))
        {
            isDebugMode = TRUE;
            DebugArgs(argc, argv); 
            BaseTaskTemplate(isInteractiveMode, isDebugMode);
        }
        /** ./contest --prompt=interactive**/
        else if (IsPromptInteractiveMode(argc, argv))
        {
            BaseTaskTemplate(isInteractiveMode, isDebugMode);
            isInteractiveMode = TRUE;
        }   
        /** ./contest --prompt=disabled **/ 
        else if (IsPromptDisabledMode(argv))
        {    
            isInteractiveMode = FALSE;    
            BaseTaskTemplate(isInteractiveMode, isDebugMode);
        }
        else
            ErrorHandler(ERROR_INVALID_UNKNOWN_ARGS);
    }
    else if (argc == 3)
    {
        /** ./contest -input=file_name.txt --verbose**/    
        if (IsFileInputMode(argv, cliArgument, isDebugMode) &&
            IsVerboseMode(argv))
        {
            isVerboseMode = TRUE;
            DebugArgs(argc, argv);
            GetFilename(argv, cliArgument, inputFile, isDebugMode);
            RunFileMode(argc, argv, inputFile, isVerboseMode, isDebugMode);
        }
        /** ./contest -input=file_name.txt --debug**/    
        else if (IsFileInputMode(argv, cliArgument, isDebugMode) &&
                 IsDebugMode(argc, argv))
        {
            isDebugMode = TRUE;
            DebugArgs(argc, argv);
            GetFilename(argv, cliArgument, inputFile, isDebugMode);
            RunFileMode(argc, argv, inputFile, isVerboseMode, isDebugMode);
        }
        /** ./contest --prompt=disabled --debug**/  
        else if (IsPromptDisabledMode(argv) && IsDebugMode(argc, argv))
        {
            isDebugMode = TRUE;
            DebugArgs(argc, argv);
            BaseTaskTemplate(isInteractiveMode, isDebugMode); 
        }
        else if (IsPromptInteractiveMode(argc, argv) &&
                 IsDebugMode(argc, argv) && !IsHelpMode(argv))
        {
            isInteractiveMode = TRUE;    
            isDebugMode = TRUE;    
            DebugArgs(argc, argv);
            BaseTaskTemplate(isInteractiveMode, isDebugMode);
        }
        else
            ErrorHandler(ERROR_INVALID_UNKNOWN_ARGS);
    }
    /** ./contest -input=file_name.txt --verbose --debug**/ 
    else if (argc == 4)
    {
        /** ./contest -input=file_name.txt --verbose (¬ --debug)**/  
        if (!IsDebugMode(argc, argv))
            ErrorHandler(ERROR_INVALID_UNKNOWN_ARGS);
            
        else
        {
            isDebugMode = TRUE;
            DebugArgs(argc, argv);
            /** ./contest (¬ -i=file_name.txt) --verbose --debug**/ 
            if (!IsFileInputMode(argv, cliArgument, isDebugMode))
                ErrorHandler(ERROR_INVALID_UNKNOWN_ARGS);
                
            else
            {
                 /** ./contest -i=file_name.txt (¬ --verbose) --debug**/
                if (!IsVerboseMode(argv))
                    ErrorHandler(ERROR_INVALID_UNKNOWN_ARGS);
                    
                /** ./contest -input=file_name.txt --verbose --debug**/ 
                else
                {
                    GetFilename(argv, cliArgument, inputFile, isDebugMode);
                    RunFileMode(argc, argv, inputFile, isVerboseMode, isDebugMode);
                }
            }
        }
    }
    else
        ErrorHandler(ERROR_INVALID_ARG_CNT);
    //~ /** Checking if correct command-line argumets are inserted! **/
    //~ CheckArgs(argc, argv, MAX_ARGS_CNT);
    
    /** Iterating argument vectors per character:**/
    
	return 0;
}

/** Description:    Identify if user inserted command line argument
 *                  "--debug" or "-d"
 * 
 *  Parameters:     command line argument count and command line argument vector              
 * 
 *  Result:         boolean: True/False
 **/
bool IsDebugMode(int argc, char **argv)
{
    int pos = argc;
    return ((strcmp(argv[pos-1], "-d") == 0) ||
    (strcmp(argv[pos-1], "--debug") == 0)); 
}

/** Description:    Identify if user inserted 1 command line argument
 * 
 *  Parameters:     command line argument count           
 * 
 *  Result:         boolean: True/False
 **/
bool IsOneOperandMode(int argc)
{
    return (argc == 2);
}

/** Description:    Identify if user inserted command line argument
 *                  "--help" or "-h"
 * 
 *  Parameters:     command line argument vector              
 * 
 *  Result:         boolean: True/False
 **/
bool IsHelpMode(char *argv[])
{
    return ((strcmp(argv[ARGS_POS_1], "-h") == 0) ||
        (strcmp(argv[ARGS_POS_1], "--help") == 0));
}

/** Description:    Identify if user inserted command line argument
 *                  "--verbose" or "-v"
 * 
 *  Parameters:      command line argument vector              
 * 
 *  Result:         boolean: True/False
 **/
bool IsVerboseMode(char *argv[])
{
    return ((strcmp(argv[ARGS_POS_2], "-v") == 0) ||
        (strcmp(argv[ARGS_POS_2], "--verbose") == 0));
}

/** Description:    Identify if user inserted command line argument
 *                  "-p=interactive" or --prompt=interactive"
 * 
 *  Parameters:     command line argument count, and command line argument vector              
 * 
 *  Result:         boolean: True/False
 **/
bool IsPromptInteractiveMode(int argc, char *argv[])
{
    return ((strcmp(argv[ARGS_POS_1], "-p=interactive") == 0) ||
            (strcmp(argv[ARGS_POS_1], "--prompt=interactive") == 0)) ;
}

bool IsPromptDisabledMode(char *argv[])
{
    return ((strcmp(argv[ARGS_POS_1], "-p=disabled") == 0) ||
        (strcmp(argv[ARGS_POS_1], "--prompt=disabled") == 0));
}


/** Description:    Identify if program is initiated in file-reading mode.
 *                  -i=filename or --input=filename
 * 
 *  Parameters:     char *argv[]:   pointer of argument vector (CL args)
 *  Result:         boolean:        TRUE or FALSE (not file-reading mode)
 **/
bool IsFileInputMode(char *argv[], char cliArgument[STR_MAX_LEN],
                     bool isDebugMode)
{
    /** Step 1: Parsing CLI ('-i=' or '--input='), **/
    for (int i = 0; i < strlen(argv[ARGS_POS_1]); i++)
    {
        cliArgument[i] = argv[ARGS_POS_1][i];
        
        if (argv[ARGS_POS_1][i] == '=')
        {
            if (isDebugMode)
                printf("\n DEBUG: str[%d]= '%c' "
                        "\n Found delimiting '=' to parse filename "
                        "from entire command line argument.", i, argv[ARGS_POS_1][i]);
            break;
        }
        if (isDebugMode)
            printf("\n DEBUG: str[%d] = %c ", i, argv[ARGS_POS_1][i]);
    }
    /** Step 2: Concatinating chars to "inputFile" array-variable 
     *          after "=" detected.**/
    return ((strcmp(cliArgument, "-i=") == 0) ||
    (strcmp(cliArgument, "--input=") == 0));
}

/** Description:    Parsing filename from command-line argument 
 *                  "--input=<filename>" or "-i=<filename>"
 *                  
 *                  Will start iterating from '=' symbol
 *                           (in -i=filename) or
 *                           (in --input=filename)
 *
 *                  Thus, we locate correct index -> j = strlen(string)
 * 
 *  Parameters:     argument vector - *argv[]
 *                  string containing -i or --input
 *                  filename (that we populate with this Function)
 *
 *  Result:         return: void (nothing). 
 *                  We will populate filename array-variable.
 **/
void GetFilename(char *argv[], char cliArgument[STR_MAX_LEN],
                 char inputFile[STR_MAX_LEN], bool isDebugMode)
{
    int idx = 0;
    for (int j = strlen(cliArgument); j < strlen(argv[ARGS_POS_1]); j++)
    {
        inputFile[idx] = argv[ARGS_POS_1][j];
        idx++;
        
    }
    if (isDebugMode)
        DebugString(inputFile);
}

/** Description:    Print debugging information about command line arguments
 * 
 *  Parameters:     command line argument count
 *                  command line arguement vector            
 * 
 *  Result:         void; print command line argument count and vector by each char
 **/
void DebugArgs(int argc, char **argv)
{
    int i, j, n;
    printf("Got %d command line arguments\n", argc);
    
    /** Accessing arguments one by one as strings **/
    for (i = 0; i < argc; i++)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    putchar('\n');
    
    /** Accessing arguments, character at a time **/
    for (i = 0; i < argc; i++)
    {
        for (j = 0, n = strlen(argv[i]); j < n; j++)
        {
            printf("%c ", argv[i][j]);
        }
       putchar('\n');
    }
}
/** Description:    Exit program on specific error-induced use-cases
 * 
 *  Parameters:     error code
 * 
 *  Result:         void (exit program)
 **/

void ErrorHandler(int errCode)
{
    switch(errCode)
    {
        case ERROR_INVALID_ARG_CNT:
            printf("Error %d Invalid argument count.", errCode);
            break;
        case ERROR_INVALID_UNKNOWN_ARGS:
            printf("Error %d! Unknown argument(s).", errCode);
            break;
        case ERROR_HELP:
            printf("Entering help mode.");
            break;
        case ERROR_INVALID_NAME:
            printf("Error %d Invalid name", errCode);
            break;
        case ERROR_INVALID_SCORE:
            printf("Error %d Invalid score", errCode);
            break;
        default:
            printf("Error %d: Invalid execution.", errCode);
    }
    putchar('\n');
    Usage();
    exit(errCode);
}
/** Description:    Print concise command line arguments of the program (--help or -h)
 *                  Not a manual / help page.
 *  Parameters:     void                  
 * 
 *  Result:         void
 **/
void Usage()
{
    puts("\nUsage: ./contest <mode> ");

    puts("\n\nAll possible operations."
         "\n Example: './contest -i=filename.txt"
         "\n Example: './contest --input=filename.txt'\n"
         
         "\n Example: './contest -p=interactive'"
         "\n Example: './contest --prompt=interactive'\n"
         
         "\n Example: './contest -p=disabled'"
         "\n Example: './contest --prompt=disabled'\n"
         
         "\n Example: './contest -i=filename.txt -v'"
         "\n Example: './contest -i=filename.txt --verbose'"
         "\n Example: './contest --input=filename.txt -v'"
         "\n Example: './contest --input=filename.txt --verbose'\n"
         
         "\n Example: './contest --help'"
         "\n Example: './contest -h'\n"
         
         "\n Example: './contest -d or --debug'"
         "\n Example: './contest  --debug'\n"
         "\n More options with debugging mode: "
         "\n Example: './contest -i=input.txt -d'"
         "\n Example: './contest -i=input.txt --debug\n"
         "\n Example: './contest -i=input.txt -v -d'"
         "\n Example: './contest -i=input.txt --verbose --debug'"
         "\n Example: './contest --input=input.txt -p=interactive -d'"
         "\n Example: './contest --input=input.txt -prompt=interactive --debug'"
         "\n Example: './contest --input=input.txt -p=disabled -d'"
         "\n Example: './contest --input=input.txt -prompt=disabled --debug'");
    
}

/** Description:    Replace redundant newline character \n wit terminating null \0
 * 
 *  Parameters:     array of chars,
 *                  lenght of array                     
 * 
 *  Result:         void (run DebugString to verify success)
 **/
void GetString(char str[], int n)
{
	// Read the string from keyboard
	fgets(str, n, stdin);
	
	// TODO: Find the length of the actual string we just read
	size_t len = strlen(str); // replace with GetLenght Fn?
	
	// TODO: Write the string terminator in place of the newline to fix the string
	str[len-1] = '\0'; // Between ' ' (bc \0 is 1 byte, char; DO NOT " ")
	
	DebugString(str);
}

/** Description:    Print each character in array of characters
 * 
 *  Parameters:     array of chars,                   
 * 
 *  Result:         void 
 **/
void DebugString(char str[])
{
    int i = 0;
    printf("\nString is: '%s'\n", str);
    while (str[i] != '\0')
    {
        printf("str[%d] = %3hhu %c\n", i, str[i], str[i]);
        i++;
    }
    printf("\n");
}

/** Description:    Get length of array of chars
 * 
 *  Parameters:     array of chars,                   
 * 
 *  Result:         lenght of the array as integer
 **/
int GetLength(char str[])
{
	//~ size_t len = strlen(str);
	int len = strlen(str);
	return len;
}

/** Description:    Print instructions of the program (--help or -h)
 * 
 *  Parameters:     void                  
 * 
 *  Result:         void
 **/
void RunHelpMode()
{
        
    puts("\n Manual page of the program ./contest:" 
         "\n Program reads input from standard stream (stdin) or file.\n"
         "\n The default mode 'interactive'."
         "\n 'Interactive' mode will display user prompts to insert input."
         "\n  Example: './contest'"
         "\n  Example: './contest < input.txt'"
         "\n  Example: './contest -p=interactive'"
         "\n  Example: './contest --prompt=interactive'"
         
         
         "\n\n -i=file_name or --input=file_name"
         "\n\t Program reads the input from the given file"
         "\n\t and prints the results immediately."
         "\n\t  Example: './contest -i=input.txt"
         "\n\t  Example: './contest --input=input.txt"


         "\n\n -p=disabled or --prompt=disabled"
         "\n\t Program reads input from  stdin  standard stream."
         "\n\t The program will not present the user with any prompts for input."
         "\n\t Only the results are displayed."
         "\n\t  Example: './contest -p=disabled'"
         "\n\t  Example: './contest --prompt=disabled'"
         
         "\n\n -h or --help"
         "\n\t Prints a manual of the programs modes and explanations.."
         "\n\t  Example: './contest --help'"
         "\n\t  Example: './contest -h'"
         
         "\n\n -v or --verbose"
         "\n\t Display verbose description of programs operations"
         "\n\t  Example: './contest -i=input.txt -v'"
         "\n\t  Example: './contest --input=input.txt --verbose'"
         
        "\n\n -d or --debug'"
         "\n\t Display debugging messages for developer of the programs operations'"
         "\n\t  Example: './contest -i=input.txt -d'"
         "\n\t  Example: './contest -i=input.txt --debug'\n"
         "\n\t  Example: './contest -i=input.txt -v -d'"
         "\n\t  Example: './contest -i=input.txt --verbose -debug'"
         "\n\t  Example: './contest --input=input.txt -p=interactive -d'"
         "\n\t  Example: './contest --input=input.txt -prompt=interactive -debug'"
         "\n\t  Example: './contest --input=input.txt -p=disabled -d'"
         "\n\t  Example: './contest --input=input.txt -prompt=disabled -debug'");
}

/** Description:    Run program to parse a specific file.
 *                  
 *                  Precondition: user inserted command line argument "-i=filename.txt"
 *                                                               "--input=filename.txt"
 * 
 *  Parameters:     command line argument count and vector
 *                  filename as character array
 *                  boolean if program was run in verbose-mode (-v or --verbose)              
 *                  boolean if program was run in debug-mode (-d or --debug)              
 * 
 *  Result:         void
 **/
void RunFileMode(int argc, char **argv, char inputFile[STR_MAX_LEN],
                bool isVerboseMode, bool isDebugMode)
{

    char names[MAX_SIZE][MAX_SIZE];
    int indicesArray[MAX_SIZE] = {0};
    char name[MAX_SIZE];
 
    double nums[STR_MAX_LEN] = {0};

    char pointNr[MAX_SIZE];
    int index = 0;
    
    FILE *fInputStream;
	
    /** inputFile is array populated in Fn "IsFileMode()" "**/
    fInputStream = fopen(inputFile, "r");
    
    /** Check if file stream EMPTY for file "input.txt" **/
	if (fInputStream == NULL)
	{
        printf("Error opening file '%s'\n", inputFile);
		perror("");		// error checking ("permissions denied")
        
        if (isVerboseMode)
            printf("Exiting the program '%s'\n", argv[ARGS_POS_0]);
        puts("\nDEBUG: Stream NULL");
        ErrorHandler(EXIT_FAILURE); // new type, file empty?
	}
    
    if (isVerboseMode)
        printf("File '%s' is opened in read-mode!'\n", inputFile);
         
        
    int count = 0;
     /** Read first line, unique content (count of lines)**/
    fscanf(fInputStream, "%d", &count);
    
    /** Version 1: Ternary operation to decrease lenCnt
     *  if is larger than MAX_SIZE 15 (parameter "max")**/ 
    //~ count = (count > MAX_SIZE) ? MAX_SIZE : count;
    
    /** Version 2: DEBUG-message**/
    if (count > MAX_SIZE)
    {
        count = MAX_SIZE;
        if (isDebugMode)
            printf("\n DEBUG: Mismatch in actual line count "
                    "and maximul allowed line count."
                " Rewriting the size of the array from '%d' to '%d'.",
                    count, MAX_SIZE);
    }

    /** Now loop until we cannot find two values with  fscanf**/
	while (fscanf(fInputStream, "%s %s", name, pointNr) == 2)
	{
        if (isVerboseMode || isDebugMode)
            printf("\nRead line '%d' from the file '%s' "
            "to see following contents:"
            "\n Photographer: %s"
            "\n Points: %s\n", index+1, inputFile, name, pointNr);
		
        if (!IsValidName(name, isVerboseMode, isDebugMode) ||
            !IsValidScore(pointNr, isVerboseMode, isDebugMode))
        {
            if (isVerboseMode)
                printf("\nIncorrect submission. Wrong format details!");
        }    
        double scoreDouble = ConvertStrToDouble(pointNr);

        strcpy(names[index], name);
        indicesArray[index] = index;
        nums[index] = scoreDouble;
        
        index++;
        
    }
    /** Version 1: Ternary operation to increase count if more lines read!**/
    //~ count = (index < count) ? index : count;
    
    /** Version 2: DEBUG-message**/
    if (index < count)
    {
        if (isDebugMode)
            printf("\n DEBUG: Mismatch in actual line count and"
                    " expected line count (from file)."
                    " There are less actual lines then the file content states."
                    " Rewriting the size of the array from '%d' to '%d'.",
                        count, index);
        count = index;
    }
    else
    {
        if (isDebugMode)
            printf("\n DEBUG: Found %d lines of content in the file '%s'. "
                    "and the file states there are supposed to be"
                    " '%d' line-entries\n", index, inputFile, count);
    
    }

    
    printf("\nPhotographers in total: %d", count);
    putchar('\n');
    
	/** Close files once terminating program  - DO NOT FORGET!!!**/
    if (isVerboseMode)
    {
        printf("Closing file: '%s'\n", inputFile);
    }    
	fclose(fInputStream);
    
    bool isInteractiveMode = FALSE;
    Solution(indicesArray, count, names, nums, isInteractiveMode, isDebugMode);
}


/** Description:    Run program without file inputted as command line arguments
 *  
 *  Parameters:     boolean (was program run in "Interactive" mode
 *  Parameters:     boolean (was program run in "Debugging" mode
 *  Result:         none
 **/
void BaseTaskTemplate(bool isInteractiveMode, bool isDebugMode)
{
    char names[MAX_SIZE][MAX_SIZE];
    double nums[MAX_SIZE];
    int indicesArray[MAX_SIZE] = {0};
    
    int lenCnt = ReadArray(names, nums, MAX_SIZE, isInteractiveMode, isDebugMode);
    if (isInteractiveMode)
    {
        DisplayNames(names, lenCnt);
        DisplayPoints(nums, lenCnt);
    }
    Solution(indicesArray, lenCnt, names, nums, isInteractiveMode, isDebugMode);
}

/** Description:    Run program main body
 *  
 *  Parameters:     array populated by indexes
 *                  length of array
 *                  array of photgraphers' names
 *                  array of photographers' scores

 *                  boolean (was program run in "Interactive" mode
 *                  boolean (was program run in "Debugging" mode
 * 
 *  Result:         none
 **/
void Solution(int indicesArray[MAX_SIZE], int lenCnt,
              char names[MAX_SIZE][MAX_SIZE],
              double nums[MAX_SIZE], bool isInteractiveMode, bool isDebugMode)
{
    CreatePositionalArray(indicesArray, lenCnt);
    
    SortCompetitors(names, nums, indicesArray, lenCnt, isInteractiveMode, isDebugMode);
    
    DisplayTopLeaderboard(names, nums, indicesArray, lenCnt, LEADERBOARD, isDebugMode);
                          
    DisplayDisqualifiedCompetitors(names, nums, indicesArray, lenCnt, isDebugMode);
}


/** Description:    Read input from from file into arrays
 * 
 *  Parameters:     names[] - name of photographers
 *                  nums[] - points given to photographers
 *                  max - maximum allower number of photographers
 * 
 *                  boolean (was program run in "Interactive" mode
 *                  boolean (was program run in "Debugging" mode
 * 
 *  Result:         Length of array
 **/
int ReadArray(char names[MAX_SIZE][MAX_SIZE], double nums[MAX_SIZE],
              int max, bool isInteractiveMode, bool isDebugMode) // max == MAX_SIZE
{
    int lenCnt;
    
    if (isInteractiveMode)
        printf("\nPlease enter the number of photographers attending: ");
    scanf("%d", &lenCnt);

    /** Ternary operation to decrease lenCnt
     *  if is larger than MAX_SIZE 15 (parameter "max")**/
    lenCnt = (lenCnt > max) ? max : lenCnt;
    
    for (int i = 0; i < lenCnt; i++)
    {
        AskNameInput(names, i, isInteractiveMode, isDebugMode);
        AskDoubleInput(nums, i, isInteractiveMode, isDebugMode); 
    }
    if (isInteractiveMode)
        printf("\nPhotographers in total: %d", lenCnt);
        
    return lenCnt;
}

/** 
 * Description:     Ask for photographer's score
 * Parameter:       array of photographers' scores,
 *                  index of particular name
 * 
 *                  boolean (was program run in "Interactive" mode
 *                  boolean (was program run in "Debugging" mode
 * 
 * Return:          void (store score as string into character array of chars)
 * **/
void AskDoubleInput(double nums[MAX_SIZE], int i,
                    bool isInteractiveMode, bool isDebugMode)
{
    char numStr[MAX_SIZE];
    double num = 0.00;
    while(1)
    {
        if (isInteractiveMode)
            printf("\nEnter photographers score: ");
            
        /** Asking input and breaking if correctly typed**/
        scanf("%s", numStr);
        if (IsValidScore(numStr, isInteractiveMode, isDebugMode))
            break;
            
        else
        {
            if (isInteractiveMode || isDebugMode)
                printf("\nPhotographer's score cannot contain alphabetical characters\n");
        }    
    } 
    num = ConvertStrToDouble(numStr);
    nums[i] = num;
}
/** 
 * Description:     Ask for photographer's name
 * Parameter:       array of photographers' names,
 *                  index of particular name
 * 
 *                  boolean (was program run in "Interactive" mode
 *                  boolean (was program run in "Debugging" mode
 * 
 * Return:         void (store name as string into character-array of chars)
 * **/
void AskNameInput(char names[MAX_SIZE][MAX_SIZE], int i,
                    bool isInteractiveMode, bool isDebugMode)
{
    while(1)
    {
        if (isInteractiveMode)
            printf("\nEnter photographers name: "); 
            
        scanf("%s", names[i]);
        if (IsValidName(names[i], isInteractiveMode, isDebugMode))
            break;
        else
        {
            if (isInteractiveMode || isDebugMode)
                printf("\nPhotographers's name cannot contain "
                        "non-alphabetical characters.\n");
        }
        /** Store into array,
         *  remember cannot return an array or string (char array) **/
    } 
}

/** Description:    Create a temporary array
 *                  to re-arrange the photographers names by their points.
 *                  Use the temporary array in BubbleSort Function!
 * 
 *  Parameters:     temporary array (to map names and points together);
 *                  length of array
 *  Result:         none
 **/
 
void CreatePositionalArray(int indicesArray[MAX_SIZE], int lenCnt)
{
    for (int i = 0; i < lenCnt; i++)
    {
        indicesArray[i] = i;
    }
}
/** Description:    Print names of all photographers
 * 
 *  Parameters:     array of photographers' names
 *                  length of an array
 * 
 *  Result:         void
 **/
void DisplayNames(char names[MAX_SIZE][MAX_SIZE], int lenCnt)
{
    printf("\nPhotographers: ");
    for (int i = 0; i < lenCnt; i++)
    {
        printf(" %s", names[i]); 
    }
}

/** Description:    Print scores of all photographers
 * 
 *  Parameters:     array of photographers' scores
 *                  length of an array
 * 
 *  Result:         void
 **/
void DisplayPoints(double nums[MAX_SIZE], int lenCnt)
{
    printf("\nPoints: ");
    for (int i = 0; i < lenCnt; i++)
    {
        printf(" %0.1f", nums[i]);
    }
    printf("\n"); 
}

/** Description:    Sort the competitors by valid score
 *                   (use index-array to help sort).
 * 
 *  Parameters:     array of photographer's names.
 *                  array of scores (double)
 *                  array of indexes
 *                  lenght of the arrays
 * 
 *                  boolean whether run in "Interactive Mode"
 *                  boolean whether run in "Debugging Mode"
 *  Result:         none
 **/
void SortCompetitors(char names[MAX_SIZE][MAX_SIZE],
                     double nums[MAX_SIZE], int indicesArray[MAX_SIZE],
                     int lenCnt, bool isInteractiveMode, bool isDebugMode)
{
    BubbleSort(nums, indicesArray, lenCnt, isInteractiveMode, isDebugMode);
    
    if (isInteractiveMode || isDebugMode)
    {
        PrintAscendingNames(names, nums, indicesArray, lenCnt);
        PrintDescendingNames(names, nums, indicesArray, lenCnt);
    }
}


/** Description:    Run Bubble Sort (use index-array to help sort).
 * 
 *  Parameters:     array of photographer's scores.
 *                  array of indexes
 *                  lenght of the arrays
 * 
 *                  boolean whether run in "Interactive Mode"
 *                  boolean whether run in "Debugging Mode"
 *  Result:         none
 **/
void BubbleSort(double nums[MAX_SIZE], int indicesArray[MAX_SIZE],
                int len, bool isInteractiveMode, bool isDebugMode)
{
	double temp = 0.0f;
    int temp_index = 0;
    
	int booleanTag = ALREADY_SORTED; //~ int booleanTag = 0; // without macro
	int i, j;
	int comparison_cnt = 0;
	int swapCount = 0;
	
	for (i = 0; i < (len - 1); i++)
	{
		/** Reset boolean for outer loop to find triggers inside
		 * the inner loop
		 * so that we know we are allowed skip outer-loop.**/
		booleanTag = ALREADY_SORTED; //~ booleanTag = 0; // without macro
		for (j = 0; j < ((len - 1) - i); j++)
		{
			/** Buublesort with my own twist (not optimal, but fascinating.)**/
            //~ if ((nums[j - 1] > nums[j + 1]) && (j >= 1))
			//~ {
				//~ booleanTag = NOT_ALREADY_SORTED; //~ booleanTag = 1;
			//~ }
			
			/** Swapping elements inside the array inside the inner-loop**/
			if (nums[j] > nums[j + 1])
			{
				/** Swapping places after if next value is larger than curr **/
				temp = nums[j];
				nums[j] = nums[j + 1];
				nums[j + 1] = temp;
                
                /** Most Important (non-standard to bubble sort!)
                * mapping index to names, to re-arrange Photographer's names**/
                temp_index = indicesArray[j];
                indicesArray[j] = indicesArray[j + 1];
                indicesArray[j + 1] = temp_index;
				
				booleanTag = NOT_ALREADY_SORTED;
				/** Counting whenever we swap the numbers in inner-array**/
				swapCount++;
			}
			/** Counting all comparisons. Means all iterations, 
             *  regardless if swapping
			 *  (NB! not same as nr. of swaps. **/
			comparison_cnt++;
		}
		//~ PrintAscendingOrder(nums, len); //skip, printed in "Interactive"
        
		/** Checking boolean value, breaking if sorted **/
		if (booleanTag == ALREADY_SORTED)
			break;	/** Breaking out of outer-loop 
                    because current inner-loop showed we have final order!**/
	}
    if (isDebugMode)
    {
        putchar('\n');
        printf("Comparison made during sorting: %d\n", comparison_cnt);
        printf("Swaps made during sorting: %d\n", swapCount);
    }
}

/** Description:    Print ascending order of photographers by their score-points
 * 
 *  Parameters:     array of scores (double)
 *                  length of array
 *  Result:         none
 **/
void PrintAscendingOrder(double nums[MAX_SIZE], int len)
{
	printf("\nContestant scores in ascending order:");
	for (int i = 0; i < len; i++)
	{
		printf(" %0.1lf", nums[i]);
	}	
}

/** Description:    Print descending order of photographers names (by their score-points)
 * 
 *  Parameters:     array of scores (double)
 *                  length of array
 *  Result:         none
 **/
void PrintDescendingOrder(double nums[MAX_SIZE], int len)
{
	printf("\nContestant scores in descending order:");
	for (int i = len-1; i >= 0; i--)
	{
		printf(" %0.1lf", nums[i]);
	}
}

/** Description:    Print ascending order of photographers names (by their score-points)
 * 
 *  Parameters:     array of scores (double)
 *                  length of array
 *  Result:         none
 **/
void PrintAscendingNames(char names[MAX_SIZE][MAX_SIZE],
                         double nums[MAX_SIZE], int indicesArray[MAX_SIZE], 
                         int lenCnt)
{
    int nameIndex;
    printf("\nContestants in ascending order:");
    for (int i = 0; i < lenCnt; i++)
    {
        nameIndex = indicesArray[i];
        printf(" {%s: %0.1lf}", names[nameIndex], nums[i]);
    }
}

/** Description:    Print descending order of photographers names (by their score-points)
 * 
 *  Parameters:     array of scores (double)
 *                  length of array
 *  Result:         none
 **/
void PrintDescendingNames(char names[MAX_SIZE][MAX_SIZE],
                          double nums[MAX_SIZE], int indicesArray[MAX_SIZE],
                          int lenCnt)
{
    int nameIndex;
    printf("\nContestants in descending order:");
    for (int i = lenCnt -1; i >= 0; i--) // why 0 here?
    {
        nameIndex = indicesArray[i];
        printf(" {%s: %0.1lf}", names[nameIndex], nums[i]);
    }
}

/** Description:    Get the index of a photographer and save into temporary array
 * 
 *  Parameters:     array containing indexes, 
 *                  index
 * 
 *  Result:         index of a particular photographer
 **/
int GetPosRearrangedPhotographer(int indicesArray[MAX_SIZE], int i)
{
    return indicesArray[i];
}

/** Description:    Print the leaderboard of best scores by photographers
 * 
 *  Parameters:     array (photographers by their name)
 *                  array (photographers by their score)
 *                  array (index before sorting array)
 *                  lenght of arrays
 *                  leaderboard/podium size (Top 3)
 *                  
 *                  boolean whether program run in debugging mode.
 * 
 *  Result:         none
 **/
void DisplayTopLeaderboard(char names[MAX_SIZE][MAX_SIZE],
                           double nums[MAX_SIZE], int indicesArray[MAX_SIZE],
                           int lenCnt, int topCount, bool isDebugMode)
{
    int cnt = 0;
    int nameIndex;

    printf("\n\nTop %d: ", topCount);
    /** Ternary to define how many we iterate to avoid segment-fail (negative i-s)**/
    int lowerBound = (lenCnt > topCount) ? (lenCnt-1 - topCount+1) : 0;

    for (int i = lenCnt - 1; i >= lowerBound; i--)
    {
        /** version 1 without function **/ 
        nameIndex = indicesArray[i];
        if (nums[i] <= MIN_POINTS || nums[i] > MAX_POINTS)
            continue;
        printf("\nNo%d: %s with %0.1f points", ++cnt, names[nameIndex], 
                                               nums[i]); 
    }

    if (cnt < topCount)
    {
        for (int j = cnt+1; j <= topCount; j++)
        {
            printf("\nNo%d: None", j);
        }
        printf("\nDeclaring %d winning photographer(s), but "
                "the there were awards for %d contestants.", cnt, topCount);
    }
}
/** Description:    Create a temporary array
 *                  to re-arrange the photographers names by their points.
 *                  Use the temporary array in BubbleSort Function!
 * 
 *  Parameters:     array (photograhers' names)
 *                  array of photographers' score
 *                  temporary array containing index,
 *                  length of array
 * 
 *                  boolean whether debugging-mode is run.
 *  Result:         none
 **/
void DisplayDisqualifiedCompetitors(char names[MAX_SIZE][MAX_SIZE],
                                    double nums[MAX_SIZE], 
                                    int indicesArray[MAX_SIZE], int lenCnt,
                                    bool isDebugMode)
{
    int disqualifiedCnt = 0;
    int nameIndex = 0;
    
    int isFirst = TRUE;
    
    printf("\n\nDisqualified:");
    for (int i = 0; i < lenCnt; i++)
    {
        if (nums[i] <= MIN_POINTS || nums[i] > MAX_POINTS)
        {
            
            /** Add comma before this name, if not the disqualified.**/
            if (!isFirst)
                putchar(',');
                
            /** version 1 without function **/ 
            //~ nameIndex = indicesArray[i];
            
            /** version 2 with function **/ 
            nameIndex = GetPosRearrangedPhotographer(indicesArray, i);
            printf(" %s", names[nameIndex]);
 
            if (isDebugMode)
                printf(" (score: %.2lf)", nums[i]);
 
            disqualifiedCnt++;
            
        }
        isFirst = FALSE;
    }
    if (disqualifiedCnt == 0)
        puts(" none");
    printf("\n");
}

/** Description:    Check whether the Photographer's name contais
 *                  valid characters (a-z and symbols: -) example Ly-Anne
 * 
 *  Parameters:     score as array of chars,
 *                  boolean whether program run with CL arguments --prompt=interactive
 *                  boolean whether program run with CL arguments  --debug CL
 *  Result:         return score (type: double)
 **/
bool IsValidName(char operand[MAX_SIZE], bool isInteractiveMode, 
                bool isDebugMode)
{
    /** Look every char and find if numerical or not**/
    bool hyphenOccured = FALSE;
    
    /** Loop each char to verify all are numbers (or negative or decimal dot.)**/
    int n = strlen(operand);
    for (int i = 0; i < n; i++)
    {
        /** Check if character is a digit
        * Hint: use isdigit() **/
        if (!isalpha(operand[i])) // example: Ly-Susanna
        {
            
            /** 1) If char is hyphen ( - ),
             *       and not yet occured, assign boolean-flag "hyphenOccured" = True
             *  2) if another char is hyphen, then hyphenOccured boolean is true,
             *       and will parse through isalpha() **/
            if (IsHyphen(operand, i) && (!hyphenOccured) && i >= 2)
            {
                hyphenOccured = TRUE;
                continue;
            }
            if (isInteractiveMode || isDebugMode)
                printf("Character '%c' is not a alphabetical letter\n", operand[i]);
            return FALSE;
        }
    }
    return TRUE;
}
/** Description:    Check whether characther is a minus-sign (negative integer)
 * 
 *  Parameters:     array of chars (string)
 *                  index of array
 * 
 *  Result:         boolean: True/False
 **/
bool IsHyphen(char operand[MAX_SIZE], int i)
{
    return operand[i] == '-';
}

/** Description:    Check whether characther is a plus-sign (positive integer)
 * 
 *  Parameters:     array of chars (string)
 *                  index of array
 * 
 *  Result:         boolean: True/False
 **/
bool IsPlus(char operand[MAX_SIZE], int i)
{
    return operand[i] == '+';
}

/** Description:    Check whether characther is a dot (decimal dot.)
 * 
 *  Parameters:     array of chars (string))
 *                  index of array
 * 
 *  Result:         boolean: True/False
 **/
bool IsDot(char operand[MAX_SIZE], int i)
{
    return operand[i] == '.';
}

/** Description:    Check whether the Photographer's score contais
 *                  valid digits (0-9 and symbols: - + .
 * 
 *  Parameters:     score as array of chars,
 *                  boolean whether program run with CL arguments --prompt=interactive
 *                  boolean whether program run with CL arguments  --debug CL
 *  Result:         return score (type: double)
 **/
bool IsValidScore(char score[MAX_SIZE],
                    bool isInteractiveMode, bool isDebugMode)
{
    /** Look every char and find if numerical or not**/
    bool isNegative = FALSE;
    bool isPositive = FALSE;
    
    bool dotOccured = FALSE;
    
    /** Check whether negative number (- symbol before number (index = [0])**/
    if (IsHyphen(score, INDEX_0))
    {
        isNegative = TRUE;
        isPositive = FALSE;
    }
    else if (IsPlus(score, INDEX_0))
        isPositive = TRUE;
    
    /** Loop each char to verify all are numbers (or negative or decimal dot.)**/
    int n = strlen(score);
    for (int i = 0; i < n; i++)
    {
        /** Check if character is a digit
        * Hint: use isdigit() **/
        if (!isdigit(score[i]))
        {
            /** If number is negative (- symbol at index 0, then skip isdigit())**/
            if (i == 0 && (isNegative || isPositive)) 
            {
                continue;
            }

            /** 1) If char is decimal dot,
             *       and not yet occured, assign boolean-flag "dotOccured" = True
             *  2) if another char is dot, then dotOccured boolean is true,
             *       and will parse through isdigit() **/
            if (IsDot(score, i) && (!dotOccured))
            {
                dotOccured = TRUE;
                continue;
            }
            if (isInteractiveMode)
                puts("Invalid score detected.");
            
            if (isDebugMode)
                printf("Symbol '%c' is not a digit on position '%d'.\n", score[i], i+1);
            return FALSE;
        }
    }
    return TRUE;
}

/** Description:    Convert an array of characters to a double type variable
 * 
 *  Parameters:     array of chars (string) 
 *  Result:         return score (type: double)
 **/
double ConvertStrToDouble(char strScore[MAX_SIZE])
{
    double doubleScore = atof(strScore);
    return doubleScore;
}
