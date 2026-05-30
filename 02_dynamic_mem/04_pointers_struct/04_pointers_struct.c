// gcc -o prog -fsanitize=address 04_pointers_struct.c

#include "library.h"

//~ #define DEBUG 
	
int main(int argc, char **argv)
{
	/** Step 0: Print the issued command line parameters.**/
	#ifdef DEBUG
	DebugArgs(argc, argv);
	#endif 
	/** Step 1: Initialized variables**/
	
	/** Step 2: Validate program was run with correct CLI arguments**/
	if (argc != ARGS_CNT)
	{
		/** Exit the program with 'fprintf(stderr, "message"); **/
		fprintf(stderr, "Usage: %s <data_persons_file1>.txt  <data_vehicles_file>.txt\n", ARGS_EXEC_NAME );
		return EXIT_FAILURE;
	}
	
	
	/** Step 3: Create array - consisting of struct Person**/
	person personDB[MAX_PERSON];
	person *pPersonStruct = personDB;
	
	vehicle vehicleDB[MAX_PERSON];
	vehicle *pVehicleStruct = vehicleDB;
	
	int personCount = ReadPersonData(pPersonStruct, MAX_PERSON, ARGS_FILE_NAME_PERSON);
	int vehicleCount = ReadVehicleData(pVehicleStruct, MAX_PERSON, ARGS_FILE_NAME_VEHICLE);

	
	person **pBeforeSort = &pPersonStruct;
	
	/**  Task 1**/
	BubbleSortStruct(pPersonStruct, personCount);
	
	/** Task 1**/
	PrintPersonsVehicle(pPersonStruct, pVehicleStruct, 
										personCount, 
										vehicleCount,
										pBeforeSort);
	/** Task 2**/
	CalculateTax(pVehicleStruct, vehicleCount, pPersonStruct, personCount);						
	PrintIncomeAndTaxInfo(pPersonStruct, personCount);
	
	return EXIT_SUCCESS;
}

/** Description:    Print the result, showing each vehicle of a person 
 * 	Parameters:     
 * 					1. struct pointer to person[] (person type array)
 * 					2. struct pointer to vehicle[] (vehicle type array)
 * 					3. count of person-structs in person[] 
 * 					4. count of vehicle-structs in vehicle[]
 *  Result:         void
 **/
void PrintPersonsVehicle(person * pPerson, vehicle * pVehicle, int personCnt, int vehicleCnt, person **pBeforeSort)
{
	
	int matchedVehicles = 0; 					
	int i, j;
	for (i = 0; i < personCnt; i++)
	{	
		matchedVehicles = 0; /** Tip: Must reset for each person. **/

		/** Pointer arithmetics (->) structure operator: **/
		/** Version 1: ((pStr + i)->idCode)
		 *  Version 2://~ if (*(pPersonStruct + personCnt).idCode == (*(pVehicleStruct + vehicleCnt).personID)) **/
		
		/** Option A: pointer arithmetics:
		 * 					 Increment i: ==> (p + i)->idCode **/
		  
		printf("%ld ", (pPerson + i)->idCode);
		printf("%s ", (pPerson + i)->firstName);
		printf("%s ", (pPerson + i)->lastName);
		printf("(income: %.2lf)\n", (pPerson + i)->annualIncome);
		
		for (j = 0; j < vehicleCnt; j++)
		{
			/** Version 2: (pStr + i)->idCode  **/
			if ((pPerson + i)->idCode == (pVehicle + j)->personID)
			{
				matchedVehicles++; 

				
				printf("\t car %d: ", matchedVehicles);
				printf("%7s ", (pVehicle + j)->regNumber);
				printf("(tax: %.2lf)\n", (pVehicle + j)->annualTax);
														
				/** Optional: firstname + lastname into "pVehicle->owner" **/
				//~ ConcatToFullname((pPerson + i)->firstName, (pVehicle + j)->lastname);						
				char fullname[MAX_STR] = {0};
				ConcatToFullname(fullname, pPerson, i, pVehicle, j);						
			}
		}

		
	 
		if (matchedVehicles <= 0) 
			printf("\t*** No registered cars ***\n");
		
		#ifdef DEBUG
		printf("\n\t DEBUG: \n");
		printf("\t New address: %p\n", (pPerson+ i)); // ASK THIS
		printf("\t Old address: %p\n", *(pBeforeSort));
		#endif
		
		/** Part 3**/
		putchar('\n');
		
	// TODO: Verify that vehicle belongs to 1 person (by idCode, or .owner=1)?
	}
}

/** Description:    Calculate tax percetange of annual income
 * 
 * 	Parameters:     1. struct-pointer of person[] (person type array)
 * 					2. struct pointer to vehicle[] (vehicle type array)
 * 
 * 					3. count of vehicle-structs in vehicle[] 
 * 					4. count of person-structs in person[] 
 * 
 *  Result:         void
 **/
void CalculateTax(vehicle *pVehicle, int vehicleCnt, 
					person *pPerson, int personCnt)
{
	
	for (int i = 0; i < personCnt; i++)
	{
		/** Zero-initialize structure fields**/
		(pPerson + i)->Tax = 0;
		
		//~ if ((pPerson + i)->annualIncome <= 0.00)
		(pPerson + i)->annualTaxPercentage = 0.00;
		
		/** Pointer arithmetics (->) structure operator: **/
		for (int j = 0; j < vehicleCnt; j++)
		{
			/** Version 2: (pStr + i)->idCode  **/
			if ((pPerson + i)->idCode == (pVehicle + j)->personID)
			{
				/** Step 1: Total the tax. **/ // TODO: Move outside, will  not work here!!
				
				(pPerson + i)->Tax += (pVehicle + j)->annualTax;
	
				/** Step 2: Avoid division by 0. Thus initialize as 0, if person has:
				 * 				1) less than 0 EUR income  **/

			}
		}
		if ((pPerson + i)->annualIncome > 0)
		{
			(pPerson + i)->annualTaxPercentage = 
				(pPerson + i)->Tax / (pPerson + i)->annualIncome * 100;
		}
	}
}

/** Description:    Print tax percetange, if tax > 10% of income, show warning
 * 	Parameters:     
 * 					1. struct pointer to person[] (person type array)
 * 					2. count of person-structs in person[] 

 *  Result:         void
 **/
void PrintIncomeAndTaxInfo(person *pPerson, int personCnt)
{	
	/** Step 0: Define constant to help calculate "----" separator line lenght.**/
	char nameHeader[NAME_LEN] = "Name: ";
	
	/** Step 1. Loop with pointer-arithmetic to print each block.**/
	for (int i = 0; i < personCnt; i++)
	{
		/** Step 1a.Create a separating printline "------" with varied 
		 * 											length per name-size**/
		char separatingChars[MAX_STR] = {0};

		int lineLength = strlen(nameHeader) +
						 strlen((pPerson + i)->firstName) +
						 strlen((pPerson + i)->lastName);
						 
		/** Step 1b. Create line char-line of respective length ('-' * i)**/
		CreateSeparatingPrintLn(separatingChars, lineLength); 

		/** Pointer arithmetics (p + i->firstname) or "(*(p+i).firstname) structure operator: **/
		/** Step 2a: Print final information per person 
		 * 									(per iteration of "*(pPerson + i)" **/
		printf("%s ", nameHeader);	
		printf("%s ", (pPerson + i)->firstName);
		printf("%s \n", (pPerson + i)->lastName);
		printf("%s \n", separatingChars);
		printf("Income: %*.2lf EUR \n", LEN, (pPerson + i)->annualIncome);
		printf("Tax: %*.2lf EUR \n", LEN+3, (pPerson + i)->Tax);
		printf("Tax pcnt: %*.2lf %% \n", LEN-2, (pPerson + i)->annualTaxPercentage);
		
		/** Step 3a: Create edge-case when we are alerting about 'missing income'**/
		if ((pPerson + i)->annualIncome <= 0)
		{
			printf("ERROR: Missing income\n");
		}
		else if ((pPerson + i)->annualTaxPercentage > 10.00)
		{
			printf("WARNING! Tax > 10%% \n");
		}
		
		putchar('\n');
		/** End of i-loop. **/
	}
	/** End of Function.**/
}


/** Description:   Calculate line-length --->   "name: Dolores Vilipuu"	=len
	 * 								  --->    ----------------------	=(len + 1) 
 * 
 *  Parameters:     1. person *pVehicle: 		pointer-to-struct of vehicles.
 * 					2. char *separatingLine: 	char-array of ---- we calculate.
 * 
 *  Result:   void. Fill char-array with '-' <<== len("name: " + "<fullname>"
 **/
void CreateSeparatingPrintLn(char separatingLine[MAX_STR], int lineLength)
{
	/** Calculate line-length --->   "name: Dolores Vilipuu"	=len
	 * 						  --->    ----------------------	=(len + 1)
	 * **/
	for (int i = 0; i < lineLength + 2; i++)
	{
		separatingLine[i] = '-';
	}
}


void ConcatToFullname(char fullname[MAX_STR], person *pPerson, int i, vehicle *pVehicle, int j)
{
	/** Part 2: **/
	
	strcat(fullname, (pPerson+i)->firstName);
	strcat(fullname, " ");
	strcat(fullname, (pPerson+i)->lastName);

	strcpy((pVehicle + j)->owner, fullname);
}


/** Description:    Read the contents of a file (up to a limit of lines from file)
 * 
 *  Parameters:     1. pointer to struct-array     
 * 					2. limit of lines we read from file (after we break)
 * 					3. filename we read
 * 
 *  Result:         return count of file-lines read.
 **/

int ReadPersonData(person *pStr, int limit, char *filename) 
{

	/** pointer for file stream (input file streams) **/
	FILE *fInputStream;
    fInputStream = fopen(filename, "r");
    
    /** Check if file stream EMPTY for file "input.txt" **/
	if (fInputStream == NULL)
	{
		perror("");		// error checking ("permissions denied")
		fprintf(stderr, "Error opening file '%s'\n", filename); 
	}
	
	
	/** Section 3: Read file **/
	int cnt = 0;

	while (fscanf(fInputStream, "%ld %s %s %lf",
									&(pStr + cnt)->idCode,
									(pStr + cnt)->firstName,
									(pStr + cnt)->lastName,
									&(pStr + cnt)->annualIncome) == 4) 
	{

		#ifdef DEBUG
		printf("DEBUG: Got (%d): %ld %s %s %.2lf\n",
									cnt,
									(pStr + cnt)->idCode,
									(pStr + cnt)->firstName,
									(pStr + cnt)->lastName,
									(pStr + cnt)->annualIncome);
		#endif 
		
		cnt++; // TIP: Before if-clause!
		if (cnt >= limit)
		{
			fprintf(stderr, "ERROR! Input file is too long. "
			"Allowed limit is %d entries. We read [0-%d] entries. "
			"\nReading of the file has stopped, "
			"continuing with a partial dataset.\n", limit, cnt);
		}
	}
	
	
	/** Closing file-stream **/
	fclose(fInputStream);
	
	#ifdef DEBUG
	printf("\n Successfully ran '%s'\n", __FUNCTION__);
	#endif
	
	return cnt;
}

/** Description:    Read the contents of a file (up to a limit of lines from file)
 * 
 *  Parameters:     1. pointer to struct-array     
 * 					2. limit of lines we read from file (after we break)
 * 					3. filename we read
 * 
 *  Result:         return count of file-lines read.
 **/
int ReadVehicleData(vehicle *pStr, int limit, char *filename) 
{

	/** pointer for file stream (input file streams) **/
	FILE *fInputStream;
    fInputStream = fopen(filename, "r");
    
    /** Check if file stream EMPTY for file "input.txt" **/
	if (fInputStream == NULL)
	{
        printf("Error opening file '%s'\n", filename);
		perror("");		// error checking ("permissions denied")
		fprintf(stderr, "Error opening file '%s'\n", filename); 
	}
	/**	printf("\n Successfully ran '%s'\n", __FUNCTION__); **/
	/** Section 3: Read file **/
	int cnt = 0;
	while (fscanf(fInputStream, "%ld %s %lf",
									&(*(pStr + cnt)).personID,
									(pStr + cnt)->regNumber,
									&(pStr + cnt)->annualTax) == 3) 
	{
		#ifdef DEBUG
		printf("DEBUG: Got (%d): %ld %s %.2lf\n",
									cnt,
									(*(pStr + cnt)).personID,
									(pStr + cnt)->regNumber,
									(pStr + cnt)->annualTax);
		#endif
		cnt++; // DO NOT FORGET
		
		if (cnt >= limit)
		{
			fprintf(stderr, "ERROR! Input file is too long. "
			"Allowed limit is %d entries. We read [0-%d] entries. "
			"\nReading of the file has stopped, "
			"continuing with a partial dataset.\n", limit, cnt);
		}	
	}
	/** Closing file-stream **/
	fclose(fInputStream);
	
	#ifdef DEBUG
	printf("\n Successfully ran '%s'\n", __FUNCTION__);
	#endif
	
	return cnt;
}

/** Description:   Sort the array-struct by .firstName field. Must use: pointer arithmetics 
 * 
 *  Parameters:    *pStr - pointer to array-struct
 * 					len	 - length of  of elements in struct-array
 * 
 *  Result:         (void) ----> Re-assembled the structure by pointers. 
 **/

void BubbleSortStruct(person *pStr, int len)
{
	
	person temp;
	
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
			/** Swapping elements inside the array inside the inner-loop**/
			//~ if (strcmp(struc[j].firstName, struc[j + 1].firstName) > 0)		 // without struct pointers
			if (strcmp((pStr + j)->firstName, (pStr + j + 1)->firstName) > 0)	// with struct pointers
			{
				temp = *(pStr + j);
				*(pStr + j) = *(pStr + j + 1);
				*(pStr + j + 1) = temp;
				

				booleanTag = NOT_ALREADY_SORTED;
				/** Counting whenever we swap the numbers in inner-array**/
				swapCount++;
					
			}
			
			/** Counting all comparisons. Means all iterations, regardless if swapping
			 * (NB! not same as nr. of swaps. **/
			comparison_cnt++;
		}
		
		/** Checking boolean value, breaking if sorted **/
		
		if (booleanTag == ALREADY_SORTED)  //~ (booleanTag == 0) // without macro
		{
			break;	/** Breaking out of outer-loop because current inner-loop showed we have final order!**/
		}
	}
	#ifdef DEBUG
	printf("\nComparison made during sorting: %d", comparison_cnt);
	printf("\nSwaps made during sorting: %d", swapCount);
	putchar('\n');
	#endif
}


/** Description:    Print debugging information about command line arguments
 * 
 *  Parameters:     command line argument count
 *                  command line arguement vector            
 * 
 *  Result:         void; print command line argument count and vector by each char
 **/
void DebugArgs(int argc, char **argv)
{
    int i, j, n;
    printf("Got %d command line arguments\n", argc);
    
    /** Accessing arguments one by one as strings **/
    for (i = 0; i < argc; i++)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    putchar('\n');
    
    /** Accessing arguments, character at a time **/
    for (i = 0; i < argc; i++)
    {
        for (j = 0, n = strlen(argv[i]); j < n; j++)
        {
            printf("%c ", argv[i][j]);
        }
       putchar('\n');
    }
}
 
/**
 * Description:    Reads a string from stdin and fixes the newline character
 *
 * Parameters:     str - read string to be stored here
 *                 len - maximum length for str
 *
 * Return:         none
 */
void GetString(char *str, int len)
{
    /* Grab user input */
    fgets(str, len, stdin);
    
    /* Identify the newline (if present) */
    char *pStr = str;
    while (*pStr != '\n' && *pStr != '\0')
        pStr++;
    
    /* Get rid of the trailing newline */
    *pStr = '\0';
}
