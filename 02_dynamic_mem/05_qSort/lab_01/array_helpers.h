/**
 * File:         array_helpers.h
 * Author:       Frank Christopher Kirch
 * Created:      16.03.2024
 * Modified:     30.05.2026
 *
 * Description:  Library description for basic data type helper functions
 */
 
#ifndef ARRAY_HELPERS_H
#define ARRAY_HELPERS_H

/* Print functions for basic arrays*/
void PrintIntegerArray(int *numbers, int len);
void PrintFloatArray(float *numbers, int len);

/* Qsort compare functions for basic arrays  */
int ComparFuncInt(const void *x, const void *y);
int ComparFuncFloat(const void *x, const void *y);

#endif // ARRAY_HELPERS_H
