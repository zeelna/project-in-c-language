/**
 * File:        minmax.c
 * Author:      Frank Christopher Kirch
 * Created:     29.09.2023
 * Last edit:   29.09.2023
 *
 * Description: Code for arrays lab task. Allows the user to enter
 *              an array of integers, finds the min and max values in part 1.
 *              Finds the positions of the extreme values and the number of
 *              times they occur in the array in part 2.
 */
#include <stdio.h>
#define NUM_CNT 6

void ReadIntArray(int nums[], int len);
void PrintArray(int nums[], int len);
int PrintMax(int nums[], int len);
int PrintMin(int nums[], int len);

void PrintPos(int nums[], int len, int val);
int TimesValPresent(int nums[], int len, int val);

int main(void)
{
	int numbers[NUM_CNT];
	int maximumValue;
	int minimumValue;
	
	//~ int maxPresent = 0;
	//~ int minPresent = 0;
	
	ReadIntArray(numbers, NUM_CNT);
	PrintArray(numbers, NUM_CNT);
	
	/* Minimum value code-block */
	minimumValue = PrintMin(numbers, NUM_CNT);
	printf("\n\nMin value is %d", minimumValue);
	
	printf("\nMin value position(s): ");
	PrintPos(numbers, NUM_CNT, minimumValue);
	
	int minPresent = TimesValPresent(numbers, NUM_CNT, minimumValue);
	printf("\nMin value occured %d times\n", minPresent);
	
	
	/* Maximum value code-block */
	maximumValue = PrintMax(numbers, NUM_CNT);
	printf("\nMax value is %d", maximumValue);
	
	printf("\nMax value position(s): ");
	PrintPos(numbers, NUM_CNT, maximumValue);
	
	int maxPresent = TimesValPresent(numbers, NUM_CNT, maximumValue);
	printf("\nMax value occured %d times\n", maxPresent);
	
    return 0;
}

/**
 * Description:  Reads values from the user and stores them into the 
 *               integer array provided
 * 
 * Parameters:   nums - location to store values at
 *               len - length of the array
 *
 * Return:       -
 */
void ReadIntArray(int nums[], int len)
{
	//~ int inputNumber;
	int i = 0;
	for (i = 0; i < len; i++)
	{
		printf("Enter number %d / %d: ", i+1, NUM_CNT);
		//~ scanf("%d", &inputNumber);
		scanf("%d", &nums[i]);
		//~ nums[i] = inputNumber;
	}	
}

/**
 * Description:  Prints all integers from the array on the same line, space
 *               separated. 
 * 
 * Parameters:   nums - values that are printed
 *               len - length of the array
 * 
 * Return:       -
 */
void PrintArray(int nums[], int len)
{
    int i;
    printf("\nEntered numbers: \n");
    for (i = 0; i < len; i++)
	{
		printf("%d ", nums[i]);
	}
}


/**
 * Description:  Find the maximum value from the nums array and returns it
 * 
 * Parameters:   nums - values from which the max is searched in
 *               len - length of the array
 * 
 * Return:       Maximum value in the nums array
 */
int PrintMax(int nums[], int len)
{
	int i;
	
	int maxValue = nums[0];
	
	for (i = 1; i < len; i++)
	{
		//if (nums[i] > maxValue)
		//~ {
			//~ maxValue = nums[i];
		//~ }
		
		/* Ternary operation */
		(nums[i] > maxValue) ? (maxValue = nums[i]) : (maxValue = maxValue);
		(nums[i] > maxValue) ? (maxValue = nums[i]) : 0;  // Above bad-style.
	}
	return maxValue;
}


/**
 * Description:  Find the minimum value from the nums array and returns it
 * 
 * Parameters:   nums - values from which the min is searched in
 *               len - length of the array
 * 
 * Return:       Minimum value in the array
 */
int PrintMin(int nums[], int len)
{
	int minValue = nums[0];
	
	int i;
	for ((i = len - 1) ; i > 0; i--)
	{
		(nums[i] < minValue) ? (minValue = nums[i]) : (minValue = minValue);
		(nums[i] < minValue) ? (minValue = nums[i]) : 0; // Above bad-style.
	}
	return minValue;
}
/**
 * Description:  Prints all positions of val in the array. Shows positions 
 *               (starting from 1), instead of indexes. 
 * 
 * Parameters:   nums - values that are checked
 *               len - length of the array
 *               val - value for which the positions will be printed
 * 
 * Return:       -
 */
void PrintPos(int nums[], int len, int val)
 {
	int i;
	//~ for (i = len - 1; i >= 0; i--)
	for (i = 0; i < len; i++)
	{
		if (nums[i] == val)
		{
			printf("%d ", i+1);
		}
		//printf("Position: %d; Value: %d", i+1, nums[i]); // not needed here.
	} 
 }
 
 /**
 * Description:  Counts the number of times val is present in the array
 * 
 * Parameters:   nums - values that are checked
 *               len - length of the array
 *               val - value to search for
 * 
 * Return:       number of times val occurred in array
 */
int TimesValPresent(int nums[], int len, int val)
{
	int timesValueOccured = 0;
	int i;
	
	//~ for (i = len-1; i >= 0; i--)
	for (i = 0; i < len; i++)
	{
		//~ (val == nums[i]) ? (timesValueOccured++) : (timesValueOccured = timesValueOccured);
		(val == nums[i]) ? (timesValueOccured++) : 0; // Above bad style.
	}
	
	return timesValueOccured;
}
