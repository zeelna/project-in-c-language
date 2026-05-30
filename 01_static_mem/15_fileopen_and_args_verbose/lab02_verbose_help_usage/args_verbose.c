#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LEN 1
#define FILE_LEN 10

#define ARGS_POS_0 0
#define ARGS_POS_1 1
#define ARGS_POS_2 2

#define MAX_ARGS_CNT 3

#define TRUE 1
#define FALSE 0

#define ERROR_INVALID_ARG_CNT 1
#define ERROR_INVALID_UNKNOWN_ARGS 2
#define ERROR_HELP 3

double AritMean(int sum, int cnt);
int Sum(int sum, int value);

int GetMin(int array[MAX_LEN], int len);
int GetMax(int array[MAX_LEN], int len);

bool IsOneOperandMode(int argc);

void DebugArgs(int argc, char **argv);
void CheckArgs(int argc, char **argv, int requiredCnt);

void ErrorHandler(int errCode);

bool IsHelpMode(char *argv[]);
bool IsVerboseMode(char *argv[]);

void Usage();




int main(int argc, char *argv[])
{
    bool verboseActivated = FALSE;
    
    int argsCnt = MAX_ARGS_CNT;
    /** Checking if enough arguments inserted! **/
    CheckArgs(argc, argv, argsCnt);
    
    /** Iterating argument vectors per character:**/
    DebugArgs(argc, argv);

    if (IsHelpMode(argv))
        ErrorHandler(ERROR_HELP); // --> will exit entire program (wrapper fn).

    if ((argc == MAX_ARGS_CNT) && (IsVerboseMode(argv))) // FIX
        verboseActivated = TRUE;
    
    /** pointer for file stream (input file streams) **/
	FILE *fInputStream;
	
	int temp;
    
	//~ char argv[ARGS_POS_1][MAX_LEN] = argv[ARGS_POS_1]; // NO!!! "error, invalid initializer"
    /** Solution 1) Make a pointer (char * file = argv[1])**/
    /** Solution 2) copy string (strcp(file, argv[1])**/
    //~ const char *file = argv[ARGS_POS_1]
    
    /** Template: for static filename - WORKS!!!!**/
	//~ char argv[ARGS_POS_1][MAX_LEN] = "input.txt";
    
    fInputStream = fopen(argv[ARGS_POS_1], "r");
    /** Check if file stream EMPTY for file "input.txt" **/
	if (fInputStream == NULL)
	{
        printf("Error opening file '%s'\n", argv[ARGS_POS_1]);
		perror("");		// error checking ("permissions denied")
        
        if (verboseActivated)
        {
            //~ printf("File '%s' is empty!'\n", argv[ARGS_POS_1]);
            //~ printf("Closing file: '%s'\n", argv[ARGS_POS_1]);
            printf("Exiting the program '%s'\n", argv[ARGS_POS_0]);
        }
		//~ fclose(fInputStream); // NO! bc filestream NULL, file never opened!
        exit(EXIT_FAILURE);
	}
    if (verboseActivated)
    {
        printf("File '%s' is opened in read-mode!'\n", argv[ARGS_POS_1]);
	}
	/** pointer for file stream (output file streams) **/
	FILE *fOutputEvenNrStream;
	
	//~ const char outputEvenFile[] = {"even.txt"};
	const char outputEvenFile[FILE_LEN] = {"even.txt"};
    
    fOutputEvenNrStream = fopen(outputEvenFile, "w");
	/** Check if file stream EMPTY for file "even.txt" **/
	if (fOutputEvenNrStream == NULL)
	{
        /** Let know of error!**/
		printf("Error opening file '%s'\n", outputEvenFile);
		
		/** Enable error-messages "Permission denied" etc**/
		perror("");		// error checking ("permissions denied")
        
        /** Close input file, eventhough output file cannot be opened**/
        if (verboseActivated)
        {
            //~ printf("File '%s' is empty!'\n", outputEvenFile);
            printf("Closing file: '%s'\n", argv[ARGS_POS_1]);
            printf("Exiting the program '%s'\n", argv[ARGS_POS_0]);
        }
        fclose(fInputStream);
        //~ fclose(fOutputEvenNrStream); // NO! bc filestream NULL, file never opened!
		
		/** Exit**/
		exit(EXIT_FAILURE);
	}
    if (verboseActivated)
    {
        printf("File '%s' is opened in write-mode!'\n", outputEvenFile);
	}
	/** pointer for file stream (output file streams) **/
	FILE *fOutputOddNrStream;
	
	const char outputOddFile[FILE_LEN] = {"odd.txt"};
	fOutputOddNrStream = fopen(outputOddFile, "w");
	/** 3. Check file stream of "odd.txt" **/
	if (fOutputOddNrStream == NULL)
	{
		/** Close input file, eventhough output file cannot be opened**/
		if (verboseActivated)
        {
            //~ printf("File '%s' is empty!'\n", outputOddFile);
            printf("Closing file: '%s'\n", outputEvenFile);
            printf("Closing file: '%s'\n", argv[ARGS_POS_1]);
            printf("Exiting the program '%s'\n", argv[ARGS_POS_0]);
        }
        //~ fclose(fOutputOddNrStream); // NO! bc filestream NULL, file never opened!
        
        fclose(fOutputEvenNrStream); // DO NOT FORGET TO CLOSE ALL!!! OPENED FILES
		fclose(fInputStream);
		
		/** Let know of error!**/
		printf("Error opening file '%s'\n", outputOddFile);
		
		/** Enable error-messages "Permission denied" etc**/
		perror("");		// error checking ("permissions denied")
		
		/** Exit**/
		exit(EXIT_FAILURE);
	}
    if (verboseActivated)
    {
        printf("File '%s' is opened in write-mode!'\n", outputOddFile);
	}

    int total = 0;
    int cnt = 0;
    
    //~ int array[] = {0};
    bool firstIteration = TRUE;
    
    int min;
    int max;
    
	/** Writing contents to file! **/
	while (fscanf(fInputStream, "%d", &temp) == 1) // 1 reads one variable! BETTER!
	{
        if (verboseActivated)
        {
            putchar('\n');
            printf("Read from the file: %d\n", temp); 		// input file
		
            if (temp % 2 == 0 && temp > 0)
            {
                //~ printf("Saving to file '%s'\n", outputEvenFile); 
                puts("Saving to 'even.txt'"); 
                fprintf(fOutputEvenNrStream, "Got %d\n", temp);
                
            }
            else if (temp % 2 == 1 && temp > 0)
            {
                //~ printf("Saving to file %s'\n", outputOddFile);
                puts("Saving to file 'odd.txt");
                fprintf(fOutputOddNrStream, "Got %d\n", temp); //output file
            }
            else
            {
                if (verboseActivated)
                    printf("Discarding value: %d\n", temp); 
            }
        }
        else // Not Verbose mode!
        {
            if (temp % 2 == 0 && temp > 0)
                fprintf(fOutputEvenNrStream, "Got %d\n", temp);
            else if (temp % 2 == 1 && temp > 0)
                fprintf(fOutputOddNrStream, "Got %d\n", temp); //output file
        }
        
        /** Min and Max!**/
        
        if (firstIteration)
        {
            max = temp;
            min = temp;
        }
        firstIteration = FALSE;
        
        if (temp > max)
            max = temp;
            
        if (temp < min)
            min = temp;
            
        //~ array[cnt] = temp;
        
        /** Extra task - sum**/
        total = Sum(total, temp);
        
        cnt++; /** Extra - counting to calc arithmetical mean. **/
	}
	/** Extra task - arithmetic mean **/
    double mean = AritMean(total, cnt);
    
    putchar('\n');
    printf("The sum of all numbers is: %d\n", total);
    printf("The arithmetical mean is: %.2lf\n", mean);
    
    /** Extra task - largest and smallest**/
    //~ int min = GetMin(array, cnt);
    
    printf("The smallest numbers: %d\n", min);
    printf("The largest numbers: %d\n", max);
    //~ int max = GetMax(array, cnt);
    putchar('\n');
    
	/** Close files once terminating program  - DO NOT FORGET!!!**/
    if (verboseActivated)
    {
        printf("Closing file: '%s'\n", argv[ARGS_POS_1]);
        
        puts("Closing file: 'odd.txt'");
        puts("Closing file: 'even.txt'");
        //~ printf("Closing file: '%s'\n", outputOddFile);
        //~ printf("Closing file: '%s'\n", outputEvenFile);
        
    }
	fclose(fInputStream);
	fclose(fOutputOddNrStream);
	fclose(fOutputEvenNrStream);
    
    
	return 0;
	
}

int Sum(int sum, int value)
{
    sum += value;
    return sum;
}

double AritMean(int sum, int cnt)
{
    return (double)sum / cnt;
}

int GetMax(int array[MAX_LEN], int len)
{
    int max = array[0];
    for (int i = 1; i < len; i++)
    {
        if (array[i] > max)
            max = array[i];
    }
    return max;
}

int GetMin(int array[MAX_LEN], int len)
{
    int min = array[0];
    for (int i = 1; i < len; i++)
    {
        if (array[i] < min)
            min = array[i];
    }
    return min;
}

bool IsOneOperandMode(int argc)
{
    return (argc == 2);
}


bool IsVerboseMode(char *argv[])
{
    if ((strcmp(argv[ARGS_POS_2], "-v") == 0) ||
        (strcmp(argv[ARGS_POS_2], "--verbose") == 0))
        return TRUE;
    else
        return FALSE;
}

bool IsHelpMode(char *argv[])
{
    if ((strcmp(argv[ARGS_POS_1], "-h") == 0) ||
        (strcmp(argv[ARGS_POS_1], "--help") == 0))
        return TRUE;
    else
        return FALSE;
}

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


void CheckArgs(int argc, char **argv, int requiredCnt)
{
    if (!IsOneOperandMode(argc) && !IsVerboseMode(argv)) // step?
            ErrorHandler(ERROR_INVALID_UNKNOWN_ARGS);
                            /** ./program input.txt -r
                             *    argv[0]  argv[1]  argv[2]
                             *    argc = 1  argc= 2  argc= 3
                             * **/
    //~ else if (IsOneOperandMode(argc) && IsHelpMode(argv))
    else if (IsOneOperandMode(argc))
            requiredCnt--;  // decrement max-allowed argc (./program --help)
                            //                             argv[0]   argv[1]
                            //                             argc = 1  argc = 2
                            //
                            // if "--help", then we only check for 2 (argc), not 3!!
        
    if (argc != requiredCnt)
        ErrorHandler(ERROR_INVALID_ARG_CNT);
}

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
        default:
            printf("Error %d: Invalid execution.", errCode);
    }
    putchar('\n');
    Usage();
    exit(errCode);
}

void Usage()
{
    puts("\nUsage: ./parity <filename> <mode> ");
    
    puts("\nPossible modes:" 
         "\n -v or --verbose    ----> verbose mode "
         "\n -h or --help       ----> instruction manual");
         
    puts("\n The program must be run with a filename"
         "to read the contents from it. Otherwise program will not run"
         
         "\nExample: './parity input.txt -v'"
         "\nExample: './parity input.txt'"
         "\nExample: './parity --help'");
    
}
