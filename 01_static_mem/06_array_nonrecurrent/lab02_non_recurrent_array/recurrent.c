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
#define IS_RECURRENT 1
#define IS_ADDITIVE_INVERSE 1

void ReadNrIntoArray(int nums[], int len);
void ReorderArray(int nums[], int result[], int len);

int CollectPosNumbers(int nums[], int posNums[], int len);
void PrintArray(int nums[], int len, char arrayPrintHeader[]);

/** Extra task prototypes**/
int GetNonRecurrentArray(int nums[], int nonRecurringNums[], int len);
void PrintAdditiveInverses(int nonRecurringNums[], int len);

int main (void)
{
	int nums[N] = {0};
	int reorderedArray[N] = {0};
	int positiveArray[N] = {0};
	
	/** Extra task initialisations**/
	int nonRecurrentArray[] = {0};
	
	/** Creating user view to insert numbers. **/
	ReadNrIntoArray(nums, N); // must give array as argument to store

	/** Printing 1st array: inserted inputs into unordered array. **/
	//~ printf("\nThe origianl array: \n");
	PrintArray(nums, N, "\nThe origianl array: \n");
	
	/** Printing 2nd array: Reordered numbers**/
	//~ printf("\nThe rearranged array: \n");
	ReorderArray(nums, reorderedArray, N); // must give array as argument to store
	PrintArray(reorderedArray, N, "\nThe rearranged array: \n");
	
	int posNumCnt = CollectPosNumbers(nums, positiveArray, N);
	
	/** Printing 3rd array: Positive numbers**/
	//~ printf("\nThe positive number array: \n");
	PrintArray(positiveArray, posNumCnt, "\nThe positive number array: \n");
	
	/** Extra01: Non-recurrent array**/
	//~ int nonRecurrentCnt = GetNonRecurrentArray(nums, nonRecurrentArray, N);
	int nonRecurrentCnt = GetNonRecurrentArray(reorderedArray, nonRecurrentArray, N);
	//~ printf("\nThe nonrecurrent array: \n");
	PrintArray(nonRecurrentArray, nonRecurrentCnt, "\nThe nonrecurrent array: \n");
	
	/** Extra02: Additive Inverse**/
	PrintAdditiveInverses(nonRecurrentArray, nonRecurrentCnt);
	
}
/** Done: **/
void ReadNrIntoArray(int nums[], int len)
{
	int inputNumber = 0;
	
	int i = 0;
	for (i = 0; i < len; i++)
	{
		printf("Enter number %d / %d: ", i+1, len);
		scanf("%3d", &inputNumber);
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

//~ void PrintArray(int nums[], int len)
void PrintArray(int nums[], int len, char arrayPrintHeader[])
{
	int i = 0;
	
	printf("%s", arrayPrintHeader);
	for(i = 0; i < len; i++)
	{
		printf("%3d",  nums[i]);
	}
	printf("\n");
}

int GetNonRecurrentArray(int nums[], int nonRecurringNums[], int len)
{
	/** Third array: Storing positive numbers.**/
	int cnt = 0;
	int i, j;
	int booleanTag = 0;	// Initializing as 0, (as opposed to IS_'RECURRENT' which is  1.
	
	for (i = 0; i < len; i++)
	{
		booleanTag = 0;
		for (j = i + 1; j < len; j++)
			if (nums[i] == nums[j])
			{
				booleanTag = IS_RECURRENT;
				break;	// breaking out (loop j) if number reoccurs atleast once.
			}
		/** If there was no re-orrurence, add into 4th array. **/
		if (booleanTag != IS_RECURRENT)
		{
		nonRecurringNums[cnt] = nums[i];
		cnt++;
		}

	}
	//~ printf("\nCnt: %d", cnt);
	return cnt;
}
void PrintAdditiveInverses(int nonRecurringNums[], int len)
{
	int booleanTag = 0;
	int i, j;
	int val1, val2;
	
	printf("\nPairs:");
	for (i = 0; i < len; i++)
	{
		booleanTag = 0;
		for (j = i + 1; j < len; j++)
		{
			//~ if (nonRecurringNums[i] == -1 * nonRecurringNums[j])
			val1 = nonRecurringNums[i];
			val2 = nonRecurringNums[j];
			if (val1 == -1 * val2)
			{
				booleanTag = IS_ADDITIVE_INVERSE;
				break;
			}
		}
		if (booleanTag == IS_ADDITIVE_INVERSE)
		{
			if (val1 < val2)
				printf(" (%3d, %3d)", val1, val2);
			else
				printf(" (%3d, %3d)", val2, val1);
			//~ printf(" (%d, %d)", nonRecurringNums[i], nonRecurringNums[j]);
		}
	}
}

//~ a = "Print a lause"
//~ b = "Print b lause"
 //~ printf("%s", (a > b) ? a : b);
