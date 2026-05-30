#include "data_processor.h"
/**
 * File:         data_processor.c
 * Author:       Frank Christopher Kirch
 * Created:      16.03.2024
 * Modified:     30.05.2026
 *
**/

/** Print structures from structure array**/
void PrintStructArray(entry lineEntry[READ_LIMIT], int len) 
{
	entry *pEntry = lineEntry;
	
	for (int i = 0; i < len; i++)
	{
		printf("%s %s %d %d %d %.2lf\n",
							(pEntry)->LastStatisticsDate,
							(pEntry)->StatisticsDate,
							(pEntry)->dailyCases,
							(pEntry)->totalCases,
							(pEntry)->totalCases14Days,
							(pEntry)->perPopulation);
		pEntry++;
	}
	putchar('\n');
}

void PrintStructArrayBackWards(entry lineEntry[READ_LIMIT], int len, int limit)
{
	entry *pEntry = lineEntry + len - 1;
	
	for (int i = len-1; i > len - 1 - limit; i--)
	//~ for (int i = len-1; i > limit; i--)
	//~ int i;
	//~ while(i < 10)
	{
		printf("%s %s %d %d %d %.2lf\n",
							(pEntry)->LastStatisticsDate,
							(pEntry)->StatisticsDate,
							(pEntry)->dailyCases,
							(pEntry)->totalCases,
							(pEntry)->totalCases14Days,
							(pEntry)->perPopulation);
		pEntry--;
		//~ i++;
	}
	putchar('\n');
}

//~ void PrintDescendingOrder(int nums[], int len)
//~ {
	//~ int i = 0;
	//~ printf("\nNumbers in descending order:");
	//~ for (i = len-1; i >= 0; i--)
	//~ {
		//~ printf(" %d", nums[i]);
	//~ }
//~ }

int ComparFuncTop10Days(const void *x, const void *y)
{
	entry *pX = (entry *)x;
	entry *pY = (entry *)y;
	/** if strcmp > 0 and return 1, then sort alphabetically (ascending), Andres, Doris, Sirje jne**/
	/** if strcmp < 0 and return 1, then sort alphabetically (descending), Sirje, Doris, Andres **/
	if (pX->totalCases > pY->totalCases) // teisendame void-viida employee-viidaks. Seejärel derefence-ime, ning võrdleme
	{
		//printf("x: %s. y: %s\n", pX->fName, pY->fName);
		return -1;
	}	
		
	/** if x > y, then move y to be first**/
	//~ else if (strcmp(pX->totalCases, pY->totalCases) < 0) // teisendame void-viida employee-viidaks. Seejärel derefence-ime, ning võrdleme
	else if (pX->totalCases < pY->totalCases)
		return 1;
		
	/** if x == y, then do not move.**/
	else
		return 0;
	
}

//~ int ComparFunc14Days(const void *x, const void *y)
//~ {
	//~ return 0;
//~ }


/** Read statistics from file until limit is reached or ends before that. **/
int ReadFile(entry lineEntry[READ_LIMIT], int limit, char filename[FILE_NAME_LEN])
{
	FILE *fInputStream;
    fInputStream = fopen(filename, "r"); 
    
    /** Check if file stream EMPTY for file "input.txt" **/
	if (fInputStream == NULL)
	{
		perror("");		// error checking ("permissions denied")
		fprintf(stderr, "Error opening file '%s'\n", filename); 
	}

	entry *pEntry;
	pEntry = lineEntry;
	
	int count = 0;
	/** Ignoring header of table (LastStatisticsDate, etc..)
	 * "%*s" ignores a string until whitespace or end-of-line
	 * **/
	fscanf(fInputStream, "%*s %*s %*s %*s %*s %*s");
	
	while (fscanf(fInputStream, "%s %s %d %d %d %lf",					
							(pEntry)->LastStatisticsDate,
							(pEntry)->StatisticsDate,
							&(pEntry)->dailyCases,
							&(pEntry)->totalCases,
							&(pEntry)->totalCases14Days,
							&(pEntry)->perPopulation) == 6)
	{

		#ifdef DEBUG
		printf("Entry: Got (%d): %s %s %d %d %d %.2lf\n",
							count,
							(pEntry)->LastStatisticsDate,
							(pEntry)->StatisticsDate,
							(pEntry)->dailyCases,
							(pEntry)->totalCases,
							(pEntry)->totalCases14Days,
							(pEntry)->perPopulation);
		#endif 
		pEntry++; // DO NOT FORGET; // moving pointer by size_of to next element
		
		count++; // DO NOT FORGET;
		if (count >= limit)
		{
			fprintf(stderr, "ERROR! Input file is too long. "
			"Allowed limit is %d entries. We read [0-%d] entries. "
			"\nReading of the file has stopped, "
			"continuing with a partial dataset.\n", limit, count-1);		
			break;
		}
		
	}
	// Tip: LAST STEP Close file.
	fclose(fInputStream);
	#ifdef DEBUG
	printf("\n Successfully ran '%s'\n", __FUNCTION__);
	#endif

	putchar('\n');
	return count;
	
}
