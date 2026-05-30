#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_FINE 300
#define FINE_UNIT 5
#define UNCERTAINTY 4
#define MIN_SPEEDING 3

#define REG_LEN 9
#define MAX_LEN 1
#define FILE_LEN 30

#define ARGS_POS_0 0
#define ARGS_POS_1 1
#define ARGS_POS_2 2

#define MAX_ARGS_CNT 3

#define TRUE 1
#define FALSE 0

#define ERROR_INVALID_ARG_CNT 2
#define ERROR_INVALID_UNKNOWN_ARGS 3
#define ERROR_HELP 4

#define GENERAL_PROCEDURE_LOWER_THRESHOLD 50

void Usage();
void ErrorHandler(int errCode);
void CheckArgs(int argc, char **argv, int requiredCnt);
void DebugArgs(int argc, char **argv);

bool IsHelpMode(char *argv[]);
bool IsVerboseMode(char *argv[]);
bool IsOneOperandMode(int argc);
bool IsGeneralProcedure(int excessSpeed);

double GetFineAmount(int excessSpeed, int fineUnit);
int GetExcessSpeed(int speed, int limit);


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

    if ((argc == MAX_ARGS_CNT) && (IsVerboseMode(argv))) // MUST INCLUDE!
        verboseActivated = TRUE;
    
    /** pointer for file stream (input file streams) **/
	FILE *fInputStream;
    
	//~ char argv[ARGS_POS_1][MAX_LEN] = argv[ARGS_POS_1]; // NO!!! "error, invalid initializer"
    /** Solution 1) Make a pointer 
     *                                  (char * file = argv[1])**/
    /** Solution 2) copy string 
     *                                  (strcp(file, argv[1])**/
    //~ const char *file = argv[ARGS_POS_1]
    
    /** Template: for static filename - WORKS!!!!**/
	//~ char argv[ARGS_POS_1][MAX_LEN] = "input.txt";
    
    fInputStream = fopen(argv[ARGS_POS_1], "r");
    /** Check if file stream EMPTY for file "input.txt" **/
	if (fInputStream == NULL)
	{
        if (verboseActivated)
        {
            printf("Failure to execute program '%s'\n", argv[ARGS_POS_0]);
        }
        
        printf("Error opening file '%s'\n", argv[ARGS_POS_1]);
		perror("");		// error checking ("permissions denied")
		//~ fclose(fInputStream); // NO! bc filestream NULL, file never opened!
        exit(EXIT_FAILURE);
	}
    if (verboseActivated)
    {
        printf("File '%s' is opened in read-mode!'\n", argv[ARGS_POS_1]);
	}
	/** pointer for file stream (output file streams) **/
	FILE *fGeneralProcedureStream;
    
	const char outputGeneralProcedureFile[FILE_LEN] = {"general_procedure.txt"};
    
    fGeneralProcedureStream = fopen(outputGeneralProcedureFile, "w");

	/** Check if file stream EMPTY for file "even.txt" **/
	if (fGeneralProcedureStream == NULL)
	{
        /** Let know of error!**/
		printf("Error opening file '%s'\n", outputGeneralProcedureFile);
		
		/** Enable error-messages "Permission denied" etc**/
		perror("");		// error checking ("permissions denied")
        
        /** Close input file, eventhough output file cannot be opened**/
        if (verboseActivated)
        {
            printf("Closing file: '%s'\n", argv[ARGS_POS_1]);
            printf("Failure to execute program '%s'\n", argv[ARGS_POS_0]);
        }
        fclose(fInputStream);
        //~ fclose(fGeneralProcedureStream); // NO! bc filestream NULL, file never opened!
		
		/** Exit**/
		ErrorHandler(EXIT_FAILURE);
	}
    if (verboseActivated)
    {
        printf("File '%s' is opened in write-mode!'\n", outputGeneralProcedureFile);
	}
	/** pointer for file stream (output file streams) **/
	FILE *fFineNoticeStream;
	
	const char outputFineNoticeFile[FILE_LEN] = {"fine_notice.txt"};
	fFineNoticeStream = fopen(outputFineNoticeFile, "w");
	/** 3. Check file stream of "odd.txt" **/
	if (fFineNoticeStream == NULL)
	{
		/** Let know of error!**/
		printf("Error opening file '%s'\n", outputFineNoticeFile);
		
		/** Enable error-messages "Permission denied" etc**/
		perror("");		// error checking ("permissions denied")
		
        /** Close input file, eventhough output file cannot be opened**/
		if (verboseActivated)
        {
            //~ printf("File '%s' is empty!'\n", outputFineNoticeFile);
            printf("Closing file: '%s'\n", outputGeneralProcedureFile);
            printf("Closing file: '%s'\n", argv[ARGS_POS_1]);
            printf("Exiting the program '%s'\n", argv[ARGS_POS_0]);
        }
        //~ fclose(fFineNoticeStream); // NO! bc filestream NULL, file never opened!
        
        fclose(fGeneralProcedureStream); // DO NOT FORGET TO CLOSE ALL!!! OPENED FILES
		fclose(fInputStream);
        
		/** Exit**/
		ErrorHandler(EXIT_FAILURE);
	}

    int speed;
    int limit;
    char regNr[REG_LEN];
    
    if (verboseActivated)
    {
        printf("File '%s' is opened in write-mode!'\n", outputFineNoticeFile);
	}
	/** Writing contents to file! **/
	while (fscanf(fInputStream, "%s %d %d", regNr, &speed, &limit) == 3) // 1 reads one variable! BETTER!
	{
        int excessSpeed = GetExcessSpeed(speed, limit);
        double fine = GetFineAmount(excessSpeed, FINE_UNIT);
        
        if (verboseActivated)
            printf("\n\nRead from the file: "
            "\n reg-number: '%s'\n Speed: '%d km/h'"
            "\n Speed-limit: '%d km/h'\n", regNr, speed, limit); 		// input file
        if (IsGeneralProcedure(excessSpeed) && (excessSpeed >= MIN_SPEEDING))
        {
            if (verboseActivated)
                printf("*General fine procedure ISSUED!"
                "\nDriver '%s' exceeded %d km/h, "
                "by driving %d km/h in speed-limit zone %d km/h \n"
                "Saving to file 'general.txt'", regNr, excessSpeed, speed, limit);
                
            fprintf(fGeneralProcedureStream, "<%s>\n", regNr); //output file
            fprintf(fGeneralProcedureStream, "Speed limit: %d km/h \n", limit); //output file
            fprintf(fGeneralProcedureStream, "Measured speed: %d km/h \n", speed); //output file
            fprintf(fGeneralProcedureStream, "Exceeded: %d km/h \n", excessSpeed); //output file
        }
        
        else if ((!IsGeneralProcedure(excessSpeed)) && (excessSpeed >= MIN_SPEEDING))
        {
            if (verboseActivated)
            {
                printf("*General fine procedure AVOIDED."
                "\nDriver '%s' exceeded %d km/h, "
                "by driving %d km/h in speed-limit zone %d km/h \n", regNr, excessSpeed, speed, limit);
                
                puts("*Fine notice ISSUED!");
                puts("\nSaving to 'fine_notice.txt'"); 
                
            }    
            fprintf(fFineNoticeStream, "<%s> ", regNr);
            fprintf(fFineNoticeStream, "%d km/h ", excessSpeed);
            fprintf(fFineNoticeStream, "%.2lf EUR\n", fine);
        }
        else
        {
            if (verboseActivated)
                printf("*Fine notice AVOIDED!"
                "\nDriver '%s' drove %d in speed-limit zone %d km/h\n", regNr, speed, limit);
        }
 


        //~ putchar('\n');
    }

    
	/** Close files once terminating program  - DO NOT FORGET!!!**/
    if (verboseActivated)
    {
                    
        putchar('\n');
        putchar('\n');
        
        printf("Closing file: '%s'\n", argv[ARGS_POS_1]);
        
        puts("Closing file: 'fine_notice.txt'");
        puts("Closing file: 'general_procedure.txt'");
        
    }
	fclose(fInputStream);
	fclose(fFineNoticeStream);
	fclose(fGeneralProcedureStream);
    
    printf("\nProgram '%s' run succesfully.\n", argv[ARGS_POS_0]);
    printf("Saved results to '%s' and '%s'.\n",
            outputFineNoticeFile, outputGeneralProcedureFile);
	return 0;
	
}

int GetExcessSpeed(int speed, int limit)
{
    //~ return speed - limit - UNCERTAINTY;
    
    int excessSpeed = speed - limit;
    if (excessSpeed <= UNCERTAINTY)
        return excessSpeed - UNCERTAINTY;
    return excessSpeed;
}

double GetFineAmount(int excessSpeed, int fineUnit)
{
    double fine = (double)excessSpeed * fineUnit;
    
    if (fine > MAX_FINE)
        return MAX_FINE;
    return fine;
}

bool IsGeneralProcedure(int excessSpeed)
{
    return excessSpeed > GENERAL_PROCEDURE_LOWER_THRESHOLD;
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
        case EXIT_FAILURE:
            printf("Error %d Failure to read/write file", errCode);
            break;
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
    puts("Exiting program...");
    Usage();
    exit(errCode);
}

void Usage()
{
    puts("\nUsage: ./speed_camera <filename> <mode> ");
    
    puts("\nPossible modes:" 
         "\n -v or --verbose    ----> verbose mode "
         "\n -h or --help       ----> instruction manual");
         
    puts("\n The program must be run with a filename"
         "to read the contents from it. Otherwise program will not run"
         
         "\nExample: './speed_camera input.txt -v'"
         "\nExample: './speed_camera input.txt'"
         "\nExample: './speed_camera --help'");
    
}
