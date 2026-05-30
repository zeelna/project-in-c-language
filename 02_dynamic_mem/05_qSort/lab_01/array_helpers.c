/**
 * File:         array_helpers.c
 * Author:       Frank Christopher Kirch
 * Created:      16.03.2024
 * Modified:     30.05.2026
 *
 * Description:  Common helper functions to work with basic array types
 * .
 * Note:         Partial sample solution for array helpers.
 */
#include <stdio.h>
#include "array_helpers.h"


void PrintIntegerArray(int *numbers, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        printf("%d ", numbers[i]);
    }
    printf("\n");
}


void PrintFloatArray(float *numbers, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        printf("%.2f ", numbers[i]);
    }
    printf("\n");
}

/* Qsort compare functions for basic arrays  */
int ComparFuncInt(const void *x, const void *y)
{
	/** if x < y, then move x to be first**/
	if (*(int *)x < *(int *)y) // teisendame void-viida int-viidaks. Seejärel derefence-ime, ning võrdleme
	//~ return (*(int *)x - *(int *)y) // teisendame void-viida int-viidaks. Seejärel derefence-ime, ning võrdleme
		return -1;
		
	/** if x > y, then move y to be first**/
	else if (*(int *)x > *(int *)y) // teisendame void-viida int-viidaks. Seejärel derefence-ime, ning võrdleme
		return 1;
		
	/** if x == y, then do not move.**/
	else
		return 0;

}
int ComparFuncFloat(const void *x, const void *y)
{
		/** if x < y, then move x to be first**/
	if (*(float *)x < *(float *)y) // teisendame void-viida int-viidaks. Seejärel derefence-ime, ning võrdleme
		return -1;
		
	/** if x > y, then move y to be first**/
	else if (*(float *)x > *(float *)y) // teisendame void-viida int-viidaks. Seejärel derefence-ime, ning võrdleme
		return 1;
		
	/** if x == y, then do not move.**/
	else
		return 0;
}
