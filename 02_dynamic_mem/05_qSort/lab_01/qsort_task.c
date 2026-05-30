/**
 * File:         qsort_task.c
 * Author:       Frank Christopher Kirch
 * Created:      16.03.2024
 * Modified:     30.05.2026
 *
 * Description:  Base code for qsort lab task.
 */
#include <stdio.h>
#include <stdlib.h>
#include "qsort_task.h"
#include "employee_db.h"
#include "array_helpers.h"

int main(void)
{
    int intArr[] = {15, 25, 3, 19, 22, 17, -54, 0, 9};
    int nInts = sizeof(intArr) / sizeof(int);
    
    float floatArr[] = {76.60f, 11.2f, 76.40f, 235.4f, 76.50f, 341.6f};
    int nFloats = sizeof(floatArr) / sizeof(float);

    employee workForce[] = {{"Sirje",  "Vakra",  15.4f,  0},
                            {"Mark",   "Rebane", 10.3f,  5},
                            {"Doris",  "Rebane", 10.2f,  3},
                            {"Anneli", "Oja",     7.3f,  0},
                            {"Andres", "Rebane", 22.5f, 10}};
	int nWorkForce = sizeof(workForce) / sizeof(employee);

    while (1)
    {
        switch (ChooseMenuAction())
        {
            case 1:
                //~ Sort and print the integer array
                
                qsort(intArr, (size_t)nInts, sizeof(int), ComparFuncInt);
                //~ Base task part 1
                puts("Integer array: ");
                PrintIntegerArray(intArr, nInts);
                
                break;
            case 2:
                //~ Sort and print the decimal array
                qsort(floatArr, (size_t)nFloats, sizeof(float), 
														ComparFuncFloat);
                //~ Base task part 1
                puts("Decimal array: ");
                PrintFloatArray(floatArr, nFloats);
                
                break;
            case 3:
                //~ Sort and print the structures based on employment length
                //~ Base task part 2
                puts("Employees sorted by employment length: ");
                
                qsort(workForce, (size_t)nWorkForce, sizeof(employee), 
										ComparFuncStructEmploymentLength);
								
                PrintStructArray(workForce, nWorkForce);
                
                
                break;
            case 4:
                //~ Sort and print the structures based on first name
                //~ Base task part 2
                puts("Employees sorted by employment first name: ");
                qsort(workForce, (size_t)nWorkForce, sizeof(employee), 
											ComparFuncStructFirstName);
                
                PrintStructArray(workForce, nWorkForce);
                
                break;
            case 5:
                
                //~ Advanced task
                //~ Sort and print the structures based on last name.
                //~ If they are the same, sort them by first name.
                puts("Employees sorted by employment last and first name: ");
               
                qsort(workForce, (size_t)nWorkForce, sizeof(employee),
										ComparFuncStructLastFirstName);
                PrintStructArray(workForce, nWorkForce);
                
                
                break;
            case 0:
                /* Exit */
                exit(EXIT_SUCCESS);
                break;
            default:
                printf("Only selections from 1 to 5 and 0 are accepted\n");
        }
    }
    return EXIT_SUCCESS;
}


unsigned ChooseMenuAction(void)
{
    unsigned ans;
    printf("\n\nSelect your action!\n\n");
    printf("1. Sort and display integer array (intArr)\n");
    printf("2. Sort and display float array (floatArr)\n");
    printf("3. Sort and display structures ordered by employment length\n");
    printf("4. Sort and display structures ordered first name\n");
    printf("5. Sort and display structures ordered by last and first.\n");
    printf("0. Exit\n\n");
    
    printf("> ");
    scanf("%u", &ans);
    return ans;
}
