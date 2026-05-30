#ifndef ASK_INPUT_H
#define ASK_INPUT_H


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>
#include <stdint.h>

#define DOUBLE_SIZE 6
#define INT_SIZE 7
#define CHAR_SIZE 3

/**
 * Description:    Asks the user for an integer in between the given limits.
 *                 Reprompts if input is out of bounds.
 *
 * Parameters:     min - lower limit for the user input (inclusive)
 *                 max - upper limit for the user input (inclusive)
 *
 * Return:         Number within the specified limits
 */
int GetIntInRange(int min, int max, char* prompt);

/**
 * Description:    Asks the user for an integer with custom prompt
 *                 Reprompts if input is contains symbol that is not a digit
 *
 * Parameters:     prompt - string of what is asked / prompted from user
 *
 * Return:         integer, sanitized from non-digits.
 */
int AskInt(char *prompt);

/** Description:    Check whether the Phone Screen Size contains
 *                  valid digits (0-9)
 * 
 *  Parameters:     numString as array of chars,
 *  Result:         boolean (true/false)
 **/
bool IsValidInteger(char numString[INT_SIZE]);

/**
 * Description:    Asks the user for a double in between the given limits.
 *                 Reprompts if input is out of bounds.
 *
 * Parameters:     min - lower limit for the user input (inclusive)
 *                 max - upper limit for the user input (inclusive)
 *
 * Return:         Number within the specified limits
 */
double GetDoubleInRange(double min, double max, char *prompt);

/**
 * Description:    Asks the user for a double with custom prompt
 *                 Reprompts if input is contains symbol that is not a digit
 * 					except for ONE decimal-dot "."
 *
 * Parameters:     prompt - string of what is asked / prompted from user
 *
 * Return:         double, sanitized from non-digits. Allowing one dot.
 */	
double AskDouble(char *prompt);

/** Description:    Check whether the Phone Screen Size contains
 *                  valid digits (0-9 and decimal dot
 * 
 *  Parameters:     screenSize as array of chars,
 *  Result:         return score (type: double)
 **/
bool IsValidDouble(char doubleString[DOUBLE_SIZE]);


/**
 * Description:    Asks the user for an integer with custom prompt
 *                 Reprompts if input is contains symbol that is not a digit
 *
 * Parameters:     prompt - string of what is asked / prompted from user
 *
 * Return:         integer, sanitized from non-digits.
 */
char AskChar(char charString[CHAR_SIZE], char *prompt);

/** Description:    Check whether the Phone Screen Size contains
 *                  valid digits (0-9)
 * 
 *  Parameters:     numString as array of chars,
 *  Result:         boolean (true/false)
 **/
bool IsValidChar(char charString[CHAR_SIZE]);

#endif // ASK_INPUT_H
