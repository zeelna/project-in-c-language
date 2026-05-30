#include <stdio.h>
#define MIN_LIMIT 1
#define MAX_LIMIT 5

void ReadNrIntoArray(int nums[], int len);
int GetIntInRange(int min, int max, char prompt[]);
void CompareValues(int val1, int val2);
void DivideValues(int val1, int val2);

int main(void)
{
	
	int numsArr[MAX_LIMIT] = {0};
	
	ReadNrIntoArray(numsArr, MAX_LIMIT);
	
	int input1 = GetIntInRange(MIN_LIMIT, MAX_LIMIT, " first ") - 1;
	int input2 = GetIntInRange(MIN_LIMIT, MAX_LIMIT, " second ") - 1;
	
	CompareValues(numsArr[input1], numsArr[input2]);
	DivideValues(numsArr[input1], numsArr[input2]);

}
void ReadNrIntoArray(int nums[], int len)
{
	//~ int inputNumber = 0;
	int i = 0;
	for (i = 0; i < len; i++)
	{
		printf("\nEnter number %d / %d: ", i+1, len);
		scanf("%d", &nums[i]);
	}
}
/**
 * Description:    Asks the user for an integer in between the given limits.
 *                 Repeats until requirements are met and returns the number.
 *
 * Parameters:     min - lower bound for the user input (inclusive)
 *                 max - upper bound for the user input (inclusive)
 *                 prompt - prompt for user input, printed before entry
 *
 * Return:         number within the specified limits
 */
int GetIntInRange(int min, int max, char prompt[])
{
 	int userInput = 0;
	while(1)
	{
		printf("\nEnter %s index: ", prompt);
		scanf("%d", &userInput);
		if (userInput >= min && userInput <= max)
		{
			//~ printf("Good index input: %d", userInput);
			break;
		}
		printf("\nError! Index must be within 1 and 5!");
	}
	return userInput;
}


/**
 * Description:    Compares the given values (val1 and val2) and prints 
 *                 results of the comparison (which is greater; or equal)
 *
 * Parameters:     val1 - first value being compared
 *                 val2 - second value being compared
 *
 * Return:         -
 */
void CompareValues(int val1, int val2)
{
	//~ char operator[];
	printf("\n");
	if (val1 > val2)
	{
		printf("\n %d > %d ", val1, val2);
	}
	else if (val1 < val2)
	{
		printf("\n %d < %d ", val1, val2);
	}
	else
	{
		printf("\n %d = %d ", val1, val2);
	}
}

/**
 * Description:    Compares the given values (val1 and val2). Performs the
 *                 division by dividing greater number with the smaller number.
 *                 Both division operation and result are printed.
 *
 * Parameters:     val1 - first value
 *                 val2 - second value
 *
 * Return:         -
 */
void DivideValues(int val1, int val2)
{	
	double result = 0.00;
	/** Ternary approach **/
	//~ int greater = val2;	// initializing as val1, just in  case val1 == val2;
	//~ greater = (val1 > val2) ? val1: val2;
	int temp = 0;
	
	if (val2 > val1)
	{
		temp = val2;
		val2 = val1;
		val1 = temp;
	}
	
	if (val2 == 0)
	{
		printf("\nError! Cannot divide by 0. Your dividend is '%d', and divisor is '%d'", val1, val2);
	}
	else
	{
		result = (double)val1 / (double)val2;
		printf("\n %d / %d = %.1lf", val1, val2, result);
	}

}
