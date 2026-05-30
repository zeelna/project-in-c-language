/**
 * File:         employee_db.c
 * Author:       Frank Christopher Kirch
 * Created:      16.03.2024
 * Modified:     30.05.2026
 *
 * Description:  Library to work with employee struct
 */
#include <stdio.h>
#include <string.h>
#include "employee_db.h"

/* Print function for employees*/
void PrintStructArray(employee *staff, int len) 
{
	employee *p = staff;
	for (int i = 0; i < len; i++)
	{
		printf("%7s %7s %7.2f %7d\n", p->fName, p->lName, p->wage, p->yearsEmployed);
		p++;
	}
	putchar('\n');
}

//~ /* Qsort compare functions for sorting based on one member */
int ComparFuncStructEmploymentLength(const void *x, const void *y)
{
	employee *pX = (employee *)x;
	employee *pY = (employee *)y;
	/** if x < y, then move x to be first**/
	if (pX->yearsEmployed < pY->yearsEmployed) // teisendame void-viida employee-viidaks. Seejärel derefence-ime, ning võrdleme
		return -1;
		
	/** if x > y, then move y to be first**/
	else if (pX->yearsEmployed > pY->yearsEmployed) // teisendame void-viida employee-viidaks. Seejärel derefence-ime, ning võrdleme
		return 1;
		
	/** if x == y, then do not move.**/
	else
		return 0;

}
int ComparFuncStructFirstName(const void *x, const void *y)
{
	employee *pX = (employee *)x;
	employee *pY = (employee *)y;
	/** if strcmp > 0 and return 1, then sort alphabetically (ascending), Andres, Doris, Sirje jne**/
	/** if strcmp < 0 and return 1, then sort alphabetically (descending), Sirje, Doris, Andres **/
	
	// version 1:
	return strcmp(pX->fName, pY->fName);
	
	// bversion 2:
	//~ if (strcmp(pX->fName, pY->fName) > 0) // teisendame void-viida employee-viidaks. Seejärel derefence-ime, ning võrdleme
	//~ {
		//~ // // //printf("x: %s. y: %s\n", pX->fName, pY->fName);
		//~ return 1;
	//~ }	
		
	//~ /** if x > y, then move y to be first**/
	//~ else if (strcmp(pX->fName, pY->fName) < 0) // teisendame void-viida employee-viidaks. Seejärel derefence-ime, ning võrdleme
		//~ return -1;
		
	//~ /** if x == y, then do not move.**/
	//~ else
		//~ return 0;
	
}

//~ /* Qsort compare functions for sorting based on two members */
int ComparFuncStructLastFirstName(const void *x, const void *y)
{
	employee *pX = (employee *)x;
	employee *pY = (employee *)y;
	/** if strcmp > 0 and return 1, then sort alphabetically (ascending), Andres, Doris, Sirje jne**/
	/** if strcmp < 0 and return 1, then sort alphabetically (descending), Sirje, Doris, Andres **/
	
	int result = strcmp(pX->lName, pY->lName);
	if (result == 0)
		return ComparFuncStructFirstName(x, y);
	else
		return result;
		
	//~ // version 2:
	//~ if (strcmp(pX->lName, pY->lName) > 0) // teisendame void-viida employee-viidaks. Seejärel derefence-ime, ning võrdleme
	//~ {
		//~ /// // //printf("x: %s. y: %s\n", pX->fName, pY->fName);
		//~ return 1;
	//~ }	
		
	//~ /** if x > y, then move y to be first**/
	//~ else if (strcmp(pX->lName, pY->lName) < 0) // teisendame void-viida employee-viidaks. Seejärel derefence-ime, ning võrdleme
		//~ return -1;
		
	//~ /** if x == y, then do not move.**/
	//~ else
	//~ {
		//~ return ComparFuncStructFirstName(x, y);
	//~ }
}
