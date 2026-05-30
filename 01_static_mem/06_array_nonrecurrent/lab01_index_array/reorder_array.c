/** 
    You are given an array of N integers as input.
    Reorder the numbers in the array in such a way that negative numbers are in the beginning of the array, followed by the positive numbers.
    Do not change the order of appearance
    Example:
    Input: 5, -7, -87, -221, 7, 97, 1, -5, 5
    Result: -7, -87, -221, -5, 5, 7, 97, 1, 5

Variation 1: The same rules apply for the number 0 as was for the positive integers.

Variation 2: All occurrences of the number 0 will be removed. The resulting array may be shorter.

Variation 3: All occurrences of 0 will be pushed to the end of the array
 * 
 **/

#include <stdio.h>

#define N 6
void ReadNrIntoArray(int nums[], int len);
void ReorderArray(int nums[], int result[], int len);

int CollectPosNumbers(int nums[], int posNums[], int len);
void PrintArray(int nums[], int len);

int main (void)
{
	int nums[N] = {0};
	int reorderedArray[N] = {0};
	int positiveArray[N] = {0};
	
	/** Creating user view to insert numbers. **/
	ReadNrIntoArray(nums, N); // must give array as argument to store

	/** Printing 1st array: inserted inputs into unordered array. **/
	printf("\nThe origianl array \n");
	PrintArray(nums, N);
	
	/** Printing 2nd array: Reordered numbers**/
	printf("\nThe rearranged array \n");
	ReorderArray(nums, reorderedArray, N); // must give array as argument to store
	PrintArray(reorderedArray, N);
	
	int posNumCnt = CollectPosNumbers(nums, positiveArray, N);
	
	/** Printing 3rd array: Positive numbers**/
	printf("\nThe positive number array \n");
	PrintArray(positiveArray, posNumCnt);
	
	
}
/** Done: **/
void ReadNrIntoArray(int nums[], int len)
{
	int inputNumber = 0;
	
	int i = 0;
	for (i = 0; i < len; i++)
	{
		printf("Enter number %d / %d: ", i+1, len);
		scanf("%d", &inputNumber);
		nums[i] = inputNumber;
	}
}

/** TO-DO: **/
void ReorderArray(int nums[], int result[], int len)
{
	int resultPos = 0;
	
	/** Placing negative numbers into array **/
	int i = 0;
	for (i = 0; i < len; i++)
	{
		if (nums[i] < 0)
		{
			result[resultPos] = nums[i];
			resultPos++;
		}
	}
	/** Moving to placing natural numbes into array. **/

	for (i = 0; i < len; i++)
	{
		if (nums[i] >= 0)
		{
			result[resultPos] = nums[i];
			resultPos++;
		}
	}
	/** Moving 0s to end of array.**/
	//~ int i = 0;
	//~ for (i = 0; i < len; i++)
	//~ {
		//~ if (nums[i] == 0)
		//~ {
			//~ result[resultPos] = nums[i];
			//~ resultPos++;
		//~ }
	//~ }
}
int CollectPosNumbers(int nums[], int posNums[], int len)
{
	/** Third array: Storing positive numbers.**/
	int cnt = 0;
	int i = 0;
	for (i = 0; i < len; i++)
	{
		if (nums[i] > 0)
		{
			posNums[cnt] = nums[i];
			cnt++;
		}
	}
	return cnt;
}

void PrintArray(int nums[], int len)
{
	int i = 0;
	for(i = 0; i < len; i++)
	{
		printf("%3d", nums[i]);
	}
	printf("\n");
}
