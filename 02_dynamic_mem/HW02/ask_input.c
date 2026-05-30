#include "ask_input.h"

/**
 * Description:    Asks the user for an integer with custom prompt
 *                 Reprompts if input is contains symbol that is not a digit
 *
 * Parameters:     prompt - string of what is asked / prompted from user
 *
 * Return:         integer, sanitized from non-digits.
 */
char AskChar(char charString[CHAR_SIZE], char *prompt)
{
	while(1)
	{
		printf("%s\n> ", prompt); // todo: atoi
		scanf("%s", charString);
			
		if (IsValidChar(charString))
		{
			break;
		}
		else
		{
			puts("Selected value is not a character. Please try again."); // log message
		}
	} // end of while-loop
	char result = charString[0];
	return result;
} // end of function

/** Description:    Check whether the Phone Screen Size contains
 *                  valid digits (0-9)
 * 
 *  Parameters:     numString as array of chars,
 *  Result:         boolean (true/false)
 **/
bool IsValidChar(char charString[CHAR_SIZE])
{   
    if ((int)strlen(charString) != 1)
    {
		return false; // log message
	}

	char c = charString[0];
	if (c != 'N' && c != 'n' && c!= 'Y' && c!= 'y')
	{
		return false; // log message
	}
	return true;
} // end of function


/**
 * Description:    Asks the user for an integer in between the given limits.
 *                 Reprompts if input is out of bounds.
 *
 * Parameters:     min - lower limit for the user input (inclusive)
 *                 max - upper limit for the user input (inclusive)
 *
 * Return:         Number within the specified limits
 */
int GetIntInRange(int min, int max, char *prompt)
{
    int num = 0;
    do
    {
        num = AskInt(prompt);
        if (num < min || num > max)
        {
            printf("\nRetry! Input must be in between %d and %d. \n", min, max);
        }
    }
    while (num < min || num > max);
	putchar('\n');
    return num;
}

/**
 * Description:    Asks the user for an integer with custom prompt
 *                 Reprompts if input is contains symbol that is not a digit
 *
 * Parameters:     prompt - string of what is asked / prompted from user
 *
 * Return:         integer, sanitized from non-digits.
 */
int AskInt(char *prompt)
{
	char numString[INT_SIZE] = {0}; // dynamically?
	while(1)
	{
		printf("%s\n> ", prompt); // todo: atoi
		scanf("%s", numString);
			
		if (IsValidInteger(numString))
		{
			break;
		}
		else
		{
			puts("Selected value is not a integer. Please try again.");
		}
	} // end of while-loop
	int desiredNum = atoi(numString);
	return desiredNum;
} // end of function

/** Description:    Check whether the Phone Screen Size contains
 *                  valid digits (0-9)
 * 
 *  Parameters:     numString as array of chars,
 *  Result:         boolean (true/false)
 **/
bool IsValidInteger(char numString[INT_SIZE])
{   
    /** Loop each char to verify all are numbers (or negative or decimal dot.)**/
    int n = (int)strlen(numString);
    for (int i = 0; i < n; i++)
    {
        /** Check if character is a digit
        * Hint: use isdigit() **/
        if (!isdigit(numString[i]))
        {
            return false;
        }
    }
    return true;
} // end of function

/**
 * Description:    Asks the user for a double in between the given limits.
 *                 Reprompts if input is out of bounds.
 *
 * Parameters:     min - lower limit for the user input (inclusive)
 *                 max - upper limit for the user input (inclusive)
 *
 * Return:         Number within the specified limits
 */
double GetDoubleInRange(double min, double max, char *prompt)
{
    double num = 0.0;
    do
    {
        num = AskDouble(prompt);
        if (num < min || num > max)
        {
            printf("\nRetry! Input must be in between %.1lf and %.1lf. \n", min, max);
        }
    }
    while (num < min || num > max);
	putchar('\n');
    return num;
}

/**
 * Description:    Asks the user for a double with custom prompt
 *                 Reprompts if input is contains symbol that is not a digit
 * 					except for ONE decimal-dot "."
 *
 * Parameters:     prompt - string of what is asked / prompted from user
 *
 * Return:         double, sanitized from non-digits. Allowing one dot.
 */			
double AskDouble(char *prompt)
{
	char numString[DOUBLE_SIZE] = {0}; // dynamically?
	while(1)
	{
		printf("%s\n> ", prompt); // todo: atoi
		scanf("%s", numString);
			
		if (IsValidDouble(numString))
		{
			break;
		}
		else
		{
			puts("Selected value is not a double. Please try again."); // log message
		}
	} // end of while-loop
	double desiredNum = atof(numString);
	return desiredNum;
} // end of function
										
/** Description:    Check whether the Phone Screen Size contains
 *                  valid digits (0-9 and decimal dot
 * 
 *  Parameters:     screenSize as array of chars,
 *  Result:         return score (type: double)
 **/
bool IsValidDouble(char doubleString[DOUBLE_SIZE])
{
    /** Look every char and find if numerical or not**/
    bool dotOccured = false;
    
    /** Loop each char to verify all are numbers (or negative or decimal dot.)**/
    int n = (int)strlen(doubleString);
    for (int i = 0; i < n; i++)
    {
        /** Check if character is a digit
        * Hint: use isdigit() **/
        if (!isdigit(doubleString[i]))
        {
            /** 1) If char is decimal dot,
             *       and not yet occured, assign boolean-flag "dotOccured" = True
             *  2) if another char is dot, then dotOccured boolean is true,
             *       and will parse through isdigit() **/
            if (doubleString[i] == '.' && (!dotOccured))
            {
                dotOccured = true;
                continue;
            }
            return false;
        }
    }
    return true;
} // end of function
