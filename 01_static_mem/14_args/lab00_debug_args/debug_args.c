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

void DebugArgs(int argc, char **argv);
void CheckArgs(int argCount);
void PrintInsturction();

int main(int argc, char *argv[])
{
    /** Iterating argument vectors:**/

    DebugArgs(argc, argv);
    CheckArgs(argc);
    return EXIT_SUCCESS;    
}

void DebugArgs(int argc, char **argv)
{
    int i, j, n;
    printf("Got %d command line arguments\n", argc);
    
    // Accessing arguments one by one as strings
    for (i = 0; i < argc; i++)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    printf("\n");
    
    // Accessing arguments, character at a time
    for (i = 0; i < argc; i++)
    {
        for (j = 0, n = strlen(argv[i]); j < n; j++)
        {
            printf("%c ", argv[i][j]);
        }
        printf("\n");
    }
}

void CheckArgs(int argCount)
{
    if (argCount <= 1)
    {
        puts("Error 0! Invalid argument count or uknown arguement(s)");
        PrintInsturction();
        exit(EXIT_FAILURE);
    }
    else
        puts("You inserted a command line argument.");
    
    printf("Amount of commands issued: %d\n", argCount);

}

void PrintInsturction()
{
    puts("\nUsage: ./calculator operand operation operand");
    
    puts("\nPossible operations:" 
         "\n + add"
         "\n - subtract"
         "\n * multiply"
         "\n / divide");
         
    puts("\n Note, that due to how the shell works,"
         "\n the multiplication operator has to be encased in quotes"
         "\n e.g. 2 \"*\" 3.5");
    
}
