/**
 * File:           01_swap_pointers.c
 * Author:         Frank Christopher Kirch
 * Created:        18.02.2024
 * Last edit:      30.05.2026
 *
 * Description:    
 *                 Read and swap two numbers using pointers.
 */
 
#include <stdio.h>

// TODO: Write your prototypes for the functions here

void ReadValues(int *a, int *b);
void SwapValues(int *a, int *b);

int main(void)
{
    int x, y;
    
    printf("Addresses in function %s\n", __FUNCTION__);
    
    ReadValues(&x, &y);
    
    // Print out the values to verify that the numbers are scanned correctly.
    printf("\n\nOriginal values in %s\nx = %d\ny = %d\n\n", __FUNCTION__, x, y);
    
    SwapValues(&x, &y);
    
    // Print out the values to confirm that swapping worked
    printf("Updated values in %s\nx = %d\ny = %d\n", __FUNCTION__, x, y);
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

void ReadValues (int *a, int *b)
{
	printf("Enter a \n");
	scanf("%d", a);
	
	printf("Enter b \n");
	scanf("%d", b);
	
	printf("x is %d @ %p \n", *a, a);
	printf("y is %d @ %p \n", *b, b);
}


/**
 * Description:    Swaps the two values pointed by the pointers passed to this
 *                 function. It will also print out the locations of the two 
 *                 values that are being swapped.
 *
 * Parameters:     a - pointer to the first value
 *                 b - pointer to the second value
 *
 * Return:         none
 */

void SwapValues(int *a, int *b)
{
	// version 1:
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
	printf("x is %d @ %p \n", *a, a);
	printf("y is %d @ %p \n", *b, b);

	// Version 2: swapping memory address strings:
	//~ int *temp;
	//~ temp = a;
	//~ a = b;
	//~ b = temp;
}
