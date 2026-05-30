/**
 * File:        sequence.c
 * Author:      Frank Christopher Kirch
 * Created:     20.09.2023
 * Last edit:   23.09.2023
 *
 * Description: code for functions lab task that generates numerical
 *              sequences. 
 */
#include <stdio.h>
#include <math.h>
#include <string.h>

/* With for the divider line and menu */
#define WIDTH 65

//#define IS_PRIME 0
#define IS_PRIME 1
#define PADDING 10

//~ #define DEBUG

/* Functions for visuals */
void PrintSeparator(int width);
void PrintMenu(int width);
void PrintAsciiWelcomeMsg(void);

/* Functions to handle arithmetic sequence */
void ArithmeticSequence(void);
void ArithmeticSequenceGenerator(float start, float diff, int cnt);

/* Functions to handle geometric sequence */
void GeometricSequence(void);
void GeometricSequenceGenerator(float start, float ratio, int cnt);

int IsPrime(int num);
void PrimeSequence(void);
void PrimeGenerator(int upperbound);

void LineBreaker(int i, int padding);

int main(void)
{
    int option;
    
    PrintAsciiWelcomeMsg();
    PrintSeparator(WIDTH);
    
    /* TODO: Call the PrintMenu() function */
    
    PrintSeparator(WIDTH);
    
    printf("Enter selection\n> ");
    scanf("%d", &option);
    
    PrintSeparator(WIDTH);
    
    /* Process the user action */
    switch (option)
    {
        case 0:
			printf("Exiting...\n");
			break;
        case 1:
            ArithmeticSequence();
            break;
        case 2:
			GeometricSequence();
			break;
		case 3:
			PrimeSequence();
			break;
		
        default:
            printf("Unknown option!\n");
    }
    
    PrintSeparator(WIDTH);
        
    return 0;
}


/**
 * Description:    Starting point for the arithmetic sequence calculator. 
 *                 Pint j = 0;rompts user for the inputs required 
 *                 and calls ArithmeticSequenceGenerator()
 *
 * Parameters:     -
 *
 * Return:         -
 */
void ArithmeticSequence(void)
{
  
    int numberOfResults;
    float startValue, commonDifference;
    
    /* Header for this generation */
    printf("Arithmetic sequence generator\n");
    PrintSeparator(WIDTH);
    
    /* Get user input for the generator parameters */ 
    /* TODO: Get the user input */
    
    printf("Enter number of result: ");
    scanf("%d", &numberOfResults);
    
    printf("Enter starting value: ");
    scanf("%f", &startValue);
    
    printf("Enter common difference: ");
    scanf("%f", &commonDifference);
    
    /* Call the generator with user specified parameters */
    /* TODO: Call the generator */
    ArithmeticSequenceGenerator(startValue, commonDifference, numberOfResults);
}


/**
 * Description:    Starting point for the geometric sequence calculator. 
 *                 Prompts user for the inputs required 
 *                 and calls GeometricSequenceGenerator()
 *
 * Parameters:     -
 *
 * Return:         -
 */
void GeometricSequence(void)
{
    int numbersInSequence;
    float startingValue, commonRatio;
    
    /* Header for this generation */
    printf("Geometric sequence generator\n");
    PrintSeparator(WIDTH);
    
    /* Get user input for the generator parameters */ 
	printf("Enter number of result: ");
	scanf("%d", &numbersInSequence);
	
	printf("Enter starting value: ");
	scanf("%f", &startingValue);
	
	printf("Enter common ratio: ");
	scanf("%f", &commonRatio);
    
    /* Call the generator with user specified parameters */
    GeometricSequenceGenerator(startingValue, commonRatio, numbersInSequence);
}

void LineBreaker(int i,int padding)
{
		//~ if ((i >= PADDING) && (i % PADDING == 0))
		if ((i >= PADDING) && (i % PADDING == 0))
		{
			printf("\n");
		} 
}

void PrimeSequence(void)
{
    int upperBound;
    
    /* Header for this generation */
    printf("Prime numbers generator\n");
    PrintSeparator(WIDTH);
    
    /* Get user input for the generator parameters */
    printf("Enter upper bound: ");
    scanf("%d", &upperBound);
    
    /* Call the generator with user specified parameters */
    PrimeGenerator(upperBound);
}

/**
 * Description:    Generates and prints an arithmetic sequence
 *
 * Parameters:     start - first number in the sequence
 *                 difference - common difference for the sequence
 *                 cnt - number of members to generate
 *
 * Return:         -
 */

void ArithmeticSequenceGenerator(float start, float diff, int cnt)
{
    PrintSeparator(WIDTH);
    
    printf("Results\n");

    int i = 0;
    for (i = 0; i < cnt; i++)
    {
		printf(" %.2f ", start);
		start += diff;
		
		LineBreaker(i, PADDING);
		
	}
	printf("\n");
}


/**
 * Description:    Generates and prints a geometric sequence
 *
 * Parameters:     start - first number in the sequence
 *                 ratio - common ratio for the sequence
 *                 cnt - number of members to generate
 *
 * Return:         -
 */

void GeometricSequenceGenerator(float start, float ratio, int cnt)
{
    float iterationAnswer;
    
    printf("Results\n");
    iterationAnswer = start;
    
    int j = 0;
    for (j = 0; j < cnt; j++)
    {
		printf("%.2f ", iterationAnswer);
		iterationAnswer *= ratio;
		
		LineBreaker(j, PADDING);
	}
    printf("\n");
}

/**
 * Description:    Checks if a number is a prime or not.
 *
 * Parameters:     num - number to test for
 *
 * Return:         IS_PRIME (defined 1) when num is a prime, !IS_PRIME (0) 
 *                 if it was not.
 */
int IsPrime(int num)
{
    /* Sanity check to avoid misuse of this function */
    if (num <= 0)
    {
        return !IS_PRIME;
    }
    
    /* Check divisibility from 2 until 1 below the test value itself */
    for (int i = 2; i < num; i++)
    {
        /* If it's divisible, it's not a prime */
        if (num % i == 0)
        {
            return !IS_PRIME;
        }
    }
    /* Number is only divisible by itself and 1, so it's a prime */
    return IS_PRIME;
}

void PrimeGenerator(int upperbound)
{
	int cnt = 1;
	//~ int cnt;
	int i;
	for (i = 0; i < upperbound; i++) // not checkin 0, not divisble by anything
	{
		if (IsPrime(i))	// 1 == IS_PRIME ; 0 == !IS_PRIME 
		{
			printf("% 3d ", i);
			LineBreaker(cnt, PADDING);
			cnt++;
			
			#ifdef DEBUG
				fflush(stdout);
			#endif
		}		
	}
	printf("\n");
}

/**
 * Description:    Prints a greeting message
 *
 * Parameters:     -
 *
 * Return:         -
 */
void PrintAsciiWelcomeMsg(void)
{
    /* TODO: add ASCII art */
    printf(" FLOPPY ASCII ART!\n\n");
    
    //~ printf(
		  //~ "________                                   __"
		 //~ "/  _____/  ____   ____   ________________ _/  |_  ___________"
		//~ "/   \\  ____/ __ \\ /    \\_/ __ \\_  __ \\__  \\\\   __\\/  _ \\_  __ \\\\"
		//~ "\\    \\_\\  \\  ___/|   |  \\  ___/|  | \\// __ \\|  | (  <_> )  | \\/"
		 //~ "\\______  /\\___  >___|  /\\___  >__|  (____  /__|  \\____/|__|"
				//~ "\\/     \\/     \\/     \\/           \\/"	
			//~ );

	printf(
		" ___________________________.\n"
		"|;;|                     |;;||\n"
		"|[]|---------------------|[]||\n"
		"|;;|                     |;;||\n"
		"|;;|                     |;;||\n"
		"|;;|                     |;;||\n"
		"|;;|                     |;;||\n"
		"|;;|                     |;;||\n"
		"|;;|                     |;;||\n"
		"|;;|_____________________|;;||\n"
		"|;;;;;;;;;;;;;;;;;;;;;;;;;;;||\n"
		"|;;;;;;_______________ ;;;;;||\n"
		"|;;;;;|  ___          |;;;;;||\n"
		"|;;;;;| |;;;|         |;;;;;||\n"
		"|;;;;;| |;;;|         |;;;;;||\n"
		"|;;;;;| |;;;|         |;;;;;||\n"
		"|;;;;;| |;;;|         |;;;;;||\n"
		"|;;;;;| |___|         |;;;;;||\n"
		"\\_____|_______________|_____||\n");

printf("\n");
PrintSeparator(WIDTH);
PrintMenu(WIDTH);

}


/**
 * Description:    Prints the menu according to the allowed max width
 *
 * Parameters:     width - line width
 *
 * Return:         -
 */
void PrintMenu(int width)
{
    const int paddingLeft = 3;
    const int paddingRight = 2;
    
    /* Calculate area for a menu line text*/
    int textArea = width - (paddingLeft + paddingRight);
    
    /* Format: align left, give room up to 'textArea' characters, cut off
     *         anything that doesn't fit.
     */
    printf("#  %-*.*s #\n", textArea, textArea, "1 - Arithmetic sequence generator");
    printf("#  %-*.*s #\n", textArea, textArea, "2 - Geometric sequence generator");
    printf("#  %-*.*s #\n", textArea, textArea, "3 - Prime number generator (result count)");
    //~ printf("#  %-*.*s #\n", textArea, textArea, "4 - Prime number generator (line count)");
    printf("#  %-*.*s #\n", textArea, textArea, "0 - exit");
}


/**
 * Description:    Prints a line with the specified width using # symbols
 *
 * Parameters:     width - line width
 *
 * Return:         -
 */
void PrintSeparator(int width)
{
    /* A loop to print the separator in specified width: */
    int k = 0;
    for (k = 0; k < width; k++)
    {
		printf("#");	
	}
	printf("\n");
}
