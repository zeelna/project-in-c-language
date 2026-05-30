#include <stdio.h>

#define ARRAY_LEN 5

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
	
	int i, j;
	int comparison_cnt = 0;
	
	for (i = 0; i < (len - 1); i++)
	{
		for (j = 0; j < ((len - 1) - i); j++)
		{
			if (nums[j] > nums[j + 1])
			{
				/** Swapping places after if next value is larger than curr **/
				temp = nums[j];
				nums[j] = nums[j + 1];
				nums[j + 1] = temp;
				
				/** Incremending each time bubble sort occured.**/
				//~ comparison_cnt++;	// wrong.

			}
			comparison_cnt++;
		}
	}
	printf("\nComparison made during sorting: %d", comparison_cnt);
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
