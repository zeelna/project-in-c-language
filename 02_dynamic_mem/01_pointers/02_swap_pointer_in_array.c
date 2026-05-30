/**
 * File:           swap_pointers_in_array.c
 * Author:         Frank Christopher Kirch
 * Created:        18.02.2024
 * Last edit:      30.05.2026
 *
 * Description:     
 *                 Read and swap two numbers in array using pointers.
 */
 
#include <stdio.h>

#define LEN 9

// TODO: Write your prototypes for the functions here
void ReadIntoArray(int array[], int len);
void PrintArray(int array[], int len);
void DebugArray(int array[], int len);
void GetMinMax(int *array, int len, int **pMin, int **pMax);
void PrintSubArray(int *pStart, int *pEnd);

int main(void)
{
    int array[LEN];
	int len = LEN;
    printf("Running '%s'\n", __FUNCTION__);
    
    ReadIntoArray(array, LEN);

    PrintArray(array, LEN);
    
    // DebugArray(array, LEN);
    /** Task 02 Part 1 --> Find Min and Max by use of pointers **/
    int *pMin = array; 
    int *pMax = array;
    GetMinMax(array, len, &pMin, &pMax);
	printf("\nMin: %d; address %p", *pMin, pMin);
	printf("\nMax: %d; address %p;", *pMax, pMax);
    putchar('\n');
    
	/** Task 02 part 2 **/
    printf("\nArray print from 0 to 9\n");
    PrintSubArray(array, array + 9);
    
    printf("\nArray print from 0 to 4\n");
    PrintSubArray(array, array + 4);
    
    printf("\nArray print from 3 to 7\n");
    PrintSubArray(array + 3, array + 7);
    
    PrintArray(array + 3, 5);
    return 0;
}
/**
 * Description:    Scan for two integer values and stores the values to the
 *                 locations passed as pointers. It will also print
 *                 out the two locations where the values are stored.
 *
 * Parameters:     a - pointer to the first value
 *                 b - pointer to the second value
 *
 * Return:         none
 */

void PrintArray(int array[], int len)  // use len as pointer arithmetic operator.
{
	int *p; // initializing pointer-variable referencing integer-type value
	p = array;  // pointer-variable storing reference to location of 1st array element.

	printf("\n\nOriginal array in '%s'\n", __FUNCTION__);
	
	int i = 0;
	while (i < len)
	{
		printf("%p: %d \n", (p + i), *(p + i));
		i++; // increment index
	}
	
}
/**
 * Description:    Ask user to input n-times an integer.
 * 					Store value into array with pointer arithmetic.
 *
 * Parameters:     n -> amount of times input is asked from user.
 *
 * Return:         none
 */
void ReadIntoArray(int array[], int len)
{
	// Step 1: Assigns the start of the array to p
	int *pArr;
	pArr = array;	// store array 1st element location into pointer-variable

	int i = 0;
	do
	{
		// Step 2: 
		printf("Enter value for index %d / %d: ", i, len);
		scanf("%d", pArr + i);  // do this (pArr + i) to skip "Step 3".
		
		// Step 3: increment the address by 1 element (type dependant)
		//~ p++;
		//~ pArr++;
		
		i++;  // do not forget to increment --> i++!
	} while (i <= len);
}

/**
 * Description:    Store value into array with pointer arithmetic
 *
 * Parameters:     *pVal -> pass a pointer-variable?
 *
 * Return:         none
 */
void DebugArray(int array[], int len)
{
	puts("\nDEBUG: Print array by [i] method for confirmation");
	for (int i = 0; i <= len; i++)
	{
		printf("Array i = %d, value = %d\n", i, array[i]);
	}
	putchar('\n');
}


void PrintSubArray(int *pStart, int *pEnd)
{
	int i = 0;
	int n = 0;
	int *p = pStart;
	
	while (p <= pEnd)
	{
		printf("%p: %d \n", (p + i), *(p + i));
		
		p++; // increment by sizeof(type)
		n++; // count the number of 
	}
	putchar('\n');
}

void GetMinMax(int *array, int len, int **pMin, int **pMax)
{
	int *p = array;	
	
	int i = 0;
	//~ int minIndex;
	//~ int maxIndex;
	
	for (i = 1; i <= len; i++)
	{
		/** Tip: Option to omit creating 'int *p = array' and use: **/
		//~ (array + i), *(array + i)
		
		/** GetMin --> Comparing values, and overwriting each SMALLER value into pointer-variable **/
		if (**pMin > *(p + i))
		{
			*pMin = (p + i);	// IMPORTANT: storing a new pointer to pointer:pMin 
			//~ minIndex = i;  // not required, 
		}
		
		/** GetMax --> Comparing values, and overwriting each LARGER value into pointer-variable **/
		if (**pMax < *(p + i))
		{
			*pMax = (p + i);	// IMPORTANT: storing a new pointer to pointer:pMax 
			//~ maxIndex = i;  // not required, 
		}
	}
}
