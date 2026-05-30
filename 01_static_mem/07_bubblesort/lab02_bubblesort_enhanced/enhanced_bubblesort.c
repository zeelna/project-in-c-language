#include <stdio.h>

#define ARRAY_LEN 5
#define NOT_ALREADY_SORTED 1
#define ALREADY_SORTED 0


int ReadIntoArray(int nums[], int len);
void BubbleSort(int nums[], int len);
void PrintAscendingOrder(int nums[], int len);
void PrintDescendingOrder(int nums[], int len);

int main(void)
{
	int nums[ARRAY_LEN] = {0};
	printf("This program takes %d numbers from the user and sorts them.", ARRAY_LEN);
	printf("\nOutput is given in both ascending and descending.\n");
	
	int inputtedArrayLen = ReadIntoArray(nums, ARRAY_LEN);
	
	BubbleSort(nums, inputtedArrayLen);
	
	PrintAscendingOrder(nums, inputtedArrayLen);
	PrintDescendingOrder(nums, inputtedArrayLen);
	
	return 0;
}

int ReadIntoArray(int nums[], int len)
{
	int i = 0;
	for (i = 0; i < len; i++)
	{
		printf("Enter number %d / %d: ", i+1, len);
		scanf("%d", &nums[i]);
	}
	return i;
}

void BubbleSort(int nums[], int len)
{
	int temp = 0;
	int booleanTag = ALREADY_SORTED; //~ int booleanTag = 0; // without macro
	int i, j;
	int comparison_cnt = 0;
	int swapCount = 0;
	
	for (i = 0; i < (len - 1); i++)
	{
		/** Reset boolean for outer loop to find triggers inside
		 * the inner loop
		 * so that we know we are allowed skip outer-loop.**/
		booleanTag = ALREADY_SORTED; //~ booleanTag = 0; // without macro
		for (j = 0; j < ((len - 1) - i); j++)
		{
			//~ if ((nums[j - 1] > nums[j + 1]) && (j >= 1))
			//~ {
				//~ booleanTag = NOT_ALREADY_SORTED; //~ booleanTag = 1; //without macro
			//~ }
			
			/** Swapping elements inside the array inside the inner-loop**/
			if (nums[j] > nums[j + 1])
			{
				/** Swapping places after if next value is larger than curr **/
				temp = nums[j];
				nums[j] = nums[j + 1];
				nums[j + 1] = temp;
				
				booleanTag = NOT_ALREADY_SORTED;
				/** Counting whenever we swap the numbers in inner-array**/
				swapCount++;
			}
			/** Counting all comparisons. Means all iterations, regardless if swapping
			 * (NB! not same as nr. of swaps. **/
			comparison_cnt++;
		}
		PrintAscendingOrder(nums, len);
		/** Checking boolean value, breaking if sorted **/
		if (booleanTag == ALREADY_SORTED)  //~ (booleanTag == 0) // without macro
		{
			break;	/** Breaking out of outer-loop because current inner-loop showed we have final order!**/
		}
	}
	printf("\nComparison made during sorting: %d", comparison_cnt);
	printf("\nSwaps made during sorting: %d", swapCount);
}

void PrintAscendingOrder(int nums[], int len)
{
	int i = 0;
	printf("\nNumbers in ascending order:");
	for (i = 0; i < len; i++)
	{
		printf(" %d", nums[i]);
	}	
}

void PrintDescendingOrder(int nums[], int len)
{
	int i = 0;
	printf("\nNumbers in descending order:");
	for (i = len-1; i >= 0; i--)
	{
		printf(" %d", nums[i]);
	}
}

/**	Explainig how code works	
 * input = 1 2 1 4 3
 * 		 	i = 0	<..loop len..>
 * j = 0			*1	 2	 1	 4|	 3		no swap ( 1 < 2)
 * j = 1			 1	*1	 2	 4|	 3		swap	( 2 not < 1)
 * j = 2			 1	 1	*2	 4|	 3		no swap	( 2 < 4)
 * j = 3			 1	 1	 2	*3|	 4		swap 	( 4 not < 3)
 * 
 * breaking out (because booleanTag) **/

/**	II version: Explainig how code works	
 * input = 1 5 4 2 3
 * 
 * 		 	i = 0	<..loop len..>
 * j = 0			*1	 5	 4	 2|	 3		no swap ( 1 < 5)
 * j = 1			 1	*4	 5	 2|	 3		swap	( 5 not < 4)
 * j = 2			 1	 4	*2	 5|	 3		swap	( 5 not < 2)
 * j = 3			 1	 4	 2	*3|	 5 		swap 	( 5 not < 3)
 * 
 * 			i = 1
 * j = 0			*1	 4	 2	 3|	 5		no swap ( 1 < 4)
 * j = 1			 1	*2	 4	 3|	 5		swap	( 4 < 2)
 * j = 2			 1	 2	*3	 4|	 5		swap	( 4 not < 3)
 * j = 3			 1	 2	 3	*4|	 5		no swap	( 4 < 5)
 * breaking out (because booleanTag) **/
