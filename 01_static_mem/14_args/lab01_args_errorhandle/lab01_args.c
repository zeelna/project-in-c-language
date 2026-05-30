/**
 * Your calculator must detect the following errors

    Wrong argument count
    Unknown operator
    Non-numeric operand
    Division by zero

When an error occurs, you will both present the specific error message and the guide how to use your program
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

#define TRUE 1
#define FALSE 0

#define MAX_ARGS_CNT 4
#define ARGS_POS_OP1 1
#define ARGS_POS_OP2 2
#define ARGS_POS_OP3 3

#define ERR_INVALID_ARG_CNT 1
#define ERR_INVALID_UNKNOWN_OPERAND 2
#define ERR_INVALID_NON_NUMERIC 3
#define ERR_INVALID_DIVISION_BY_ZERO 4
#define ERR_INVALID_SQUARE_ROOT_OF_NEG 5

void DebugArgs(int argc, char **argv);
void CheckArgs(int argCount, int requiredCnt);
void ErrorHandler(int errCode);

int IsOneOperandMode(int argc, char *argv[]);
int IsDot(char operand[], int i);

void Usage();

double CheckAndConvert(char operand[]);

int main(int argc, char *argv[])
{
    double val1 = 0;
    double val3 = 0;
    /** Validating if command line arguments were issued.**/
    int argsCnt = MAX_ARGS_CNT;
    printf("ArgsCnt: %d\n", argsCnt);
    
    /** If we inserted "sqrt", then we do not require 2nd operand. 
     *  Must work with: "2 sqrt"  (operand operation) **/
    if (IsOneOperandMode(argc, argv))
        argsCnt -= 1; /** decrease 4 to 3**/
    printf("ArgsCnt: %d\n", argsCnt);
        
    /** Checking if enough arguments inserted! **/
    CheckArgs(argc, argsCnt);
    
    /** Iterating argument vectors per character:**/
    DebugArgs(argc, argv);
    
    /** Checking whether all operand's chars are digits! **/
    val1 = CheckAndConvert(argv[ARGS_POS_OP1]);
    
    /** If not square-root, we must check for 3rd operand to parse it
     *  If is  square-root, then skip 3rd operand! 
     * **/
    if (!IsOneOperandMode(argc, argv))
        val3 = CheckAndConvert(argv[ARGS_POS_OP3]);
        
    /** Mathematical operation**/
    double ans = 0.00f;
 
    if (strcmp(argv[ARGS_POS_OP2], "*") == 0) // 2 * 5 
        ans = (double)val1 * val3;

    else if (strcmp(argv[ARGS_POS_OP2], "/") == 0)  // 2 / 5
        ans = (double)val1 / val3;
        
    else if (strcmp(argv[ARGS_POS_OP2], "+") == 0) // 2 + 5 
        ans = val1 + val3;
        
    else if (strcmp(argv[ARGS_POS_OP2], "-") == 0) // 2 - 5
        ans = val1 - val3;
        
    /** Extra task - START **/
    else if (strcmp(argv[ARGS_POS_OP2], "^") == 0)
        ans = pow((double)val1, (double)val3);
        
    else if (strcmp(argv[ARGS_POS_OP2], "sqrt") == 0)
    {
        if (val1 >= 0)
            ans = sqrt(val1);
        else
            ErrorHandler(ERR_INVALID_SQUARE_ROOT_OF_NEG);
        
    }
    /** Extra task - END **/
    
    else
        ErrorHandler(ERR_INVALID_UNKNOWN_OPERAND);
    
    printf("> %.2lf\n", ans);
    
    
    return EXIT_SUCCESS;    
}

int IsOneOperandMode(int argc, char *argv[])
{
    if (strcmp(argv[ARGS_POS_OP2], "sqrt") == 0)
        return TRUE;
    else
        return FALSE;
}

double CheckAndConvert(char operand[])
{
    /** Look every char and find if numerical or not**/
    double result;
    bool isNegative = FALSE;
    bool dotOccured = FALSE;
    // int i = 0 	// look into this.
    
    /** Check whether negative number (- symbol before number (index = [0])**/
    if (operand[0] == '-')
        isNegative = TRUE; // i = 1
    
    /** Loop each char to verify all are numbers (or negative or decimal dot.)**/
    int n = strlen(operand);
    for (int i = 0; i < n; i++) // not int i
    {
        /** Check if character is a digit
        * Hint: use isdigit() **/
        if (!isdigit(operand[i]))
        {
            /** If number is negative (- symbol at index 0, then skip isdigit())**/
            if (i == 0 && (isNegative)) // then can remove this.
                continue;
            
            /** 1) If char is decimal dot,
             *       and not yet occured, assign boolean-flag "dotOccured" = True
             *  2) if another char is dot, then dotOccured boolean is true,
             *       and will parse through isdigit() **/
            if (IsDot(operand, i) && (!dotOccured)) //IsDot(operand[i])
            {
                dotOccured = TRUE;
                continue;
            }
            
            printf("operand = |%c| is not a digit\n", operand[i]);
            ErrorHandler(ERR_INVALID_NON_NUMERIC);
        }
    }
    result = atof(operand); // atof will make it negative .

    return result;
}

int IsDot(char operand[], int i) // char as argument 'IsDot(char operand[i])'
{
    return operand[i] == '.';
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

void CheckArgs(int argCount, int requiredCnt)
{
    if (argCount != requiredCnt)
    {
        ErrorHandler(ERR_INVALID_ARG_CNT);
        Usage();
    }
    //~ else
        //~ printf("Amount of commands issued: %d\n", argCount);
}

void ErrorHandler(int errCode)
{
    switch(errCode)
    {
        case ERR_INVALID_ARG_CNT:
            printf("Error %d Invalid argument count", errCode);
            break;
        case ERR_INVALID_UNKNOWN_OPERAND:
            printf("Error %d! Unknown argument(s)", errCode);
            break;
        case ERR_INVALID_NON_NUMERIC:
            printf("Error %d! Non-numeric argument", errCode);
            break;
        case ERR_INVALID_DIVISION_BY_ZERO:
            printf("Error %d! Division by zero", errCode);
            break;
        case ERR_INVALID_SQUARE_ROOT_OF_NEG:
            printf("Error %d! Square root of negative number", errCode);
            break;
        default:
            printf("Error %d: Invalid execution (unknown!)", errCode);
    }
    putchar('\n');
    exit(errCode);
}


void Usage()
{
    puts("\nUsage: ./calculator operand operation operand");
    
    puts("\nPossible operations:" 
         "\n + add"
         "\n - subtract"
         "\n * multiply"
         "\n / divide"
         "\n sqrt taking a square root"
         "\n ^ power function (x^y)");
         
    puts("\n Note, that due to how the shell works,"
         "\n the multiplication operator has to be encased in quotes"
         "\n e.g. 2 \"*\" 3.5");
    
}
