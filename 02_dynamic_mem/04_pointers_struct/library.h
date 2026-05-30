
#ifndef LIBRARY_H

#define LIBRARY_H


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>

//~ #define DEBUG 


#define NAME_LEN 7
#define LEN 12

#define CAR 						"car"
#define ARGS_CNT 3
#define ARGS_FILE_NAME_VEHICLE 		argv[2]
#define ARGS_FILE_NAME_PERSON 		argv[1]
#define ARGS_EXEC_NAME 				argv[0]

#define MAX_STR 256
#define ID_LEN 12
#define STR_NAME_LEN 64
#define REG_LEN 7

#define NOT_ALREADY_SORTED 1
#define ALREADY_SORTED 0


#define MAX_PERSON 150


typedef struct person
{
	/** Reading from file**/
	uint64_t idCode;
	char firstName[STR_NAME_LEN];
	char lastName[STR_NAME_LEN];
	double annualIncome;

	/** Writing in program **/
	double Tax;
	double annualTaxPercentage;
	
	//~ int ownedVehicles;
	//~ char * memoryAdd;
		
	//~ person * pBeforeSort;
	//~ person * pAfterSort;

} person;

typedef struct vehicle
{
	/** Reading from file**/
	uint64_t personID;
	char regNumber[REG_LEN];
	double annualTax;
	
	/** Writing in program **/
	//~ double ownerIncome;
	//~ double annualTaxPercentage;
	char owner[MAX_STR];
	
} vehicle;

/** Bubble-sort Function prototypes**/
void BubbleSortStruct(person *pStr, int len);

int ReadVehicleData(vehicle *pStr, int limit, char *filename);
int ReadPersonData(person *pStr, int limit, char *filename);

void ConcatToFullname(char fullname[MAX_STR], person *pPerson, int i, vehicle *pVehicle, int j);

void PrintIncomeAndTaxInfo(person *pPerson, int personCnt);
void PrintPersonTaxInfo(person *pPerson);


void PrintPersonsVehicle(person * pPerson, vehicle * pVehicle,
						int personCnt, int vehicleCnt, person **pBeforeSort);

void CreateSeparatingPrintLn(char separatingLine[MAX_STR], int lineLength);

void CalculateTax(vehicle *pVehicle, int vehicleCnt, 
					person *pPerson, int personCnt);

void DebugArgs(int argc, char **argv);

#endif // LIBRARY_H
