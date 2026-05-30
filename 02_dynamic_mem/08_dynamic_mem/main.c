#include "main.h"
#include "write_output.h"



int main(void)
{
	char *filename = "v1.txt";
	int nCandidates;
	candidate *pData = NULL;
	
	/** Step 1: allocate memory**/
	int returnval= ReadData(&pData, &nCandidates, filename);
	//~ printf("pData --> pp: %p\n", (void *)pData);
	if (returnval == 1)
	{
		puts("exiting due to returnval 1");
		exit(EXIT_FAILURE);
	}
	
	/** Step 2: Check if enough memory can be allocated.**/
	if (pData == NULL)
	{
		printf("Not enough memory after read!\n");
		exit(EXIT_FAILURE);
	}
	
	/** ComparCandidate sorts by Lastname, and if matches, then first name.**/
	qsort(pData, (size_t)nCandidates, sizeof(candidate),
										ComparPersonByPoints);

	PrintStructArray(pData, nCandidates);
	
	FreeStruct(pData, nCandidates);
	
	#ifdef DEBUG
	printf("\n Successfully ran '%s'\n", __FUNCTION__);
	#endif
	
	return EXIT_SUCCESS;
}


/**
 * Function to allocate memory dynamically dependant of size.
 **/
void AllocateData(int **data, int n)
{
	*data = (int *)calloc(sizeof(int), (size_t)n);
}

/**
 * Function to allocate memory dynamically dependant of size.
 **/
void ReallocateData(candidate **pData, int len, candidate **pTemp)
{	
	if (len <= 0)
	{
		printf("\n ERROR: Cannot allocate memory for 0 or less bytes (len = %d)", len);
		exit(EXIT_FAILURE);
	}
	/** Attempting to increase (or decrease) the memory by length-amounnt **/
	*pTemp = (candidate *)realloc(pData, sizeof(candidate) * (size_t)len);
	
	/** Failed to reallocate, due to NOT enough consequential memory**/
	if (*pTemp == NULL) 
	{
		printf("Not enough memory!\n");
		exit(EXIT_FAILURE);
	}
	else 
	{
		pData = pTemp;
		
		/** End of function**/
		#ifdef DEBUG
		//~ printf("\n pData: pp: <%p> , p: <%p>, v: <%d>", pData, *pData, *pData->ID);
		printf("\n pData: pp: <%p> , p: <%p>", pData, *pData);
		#endif
		
	}
	#ifdef DEBUG
	printf("\n Successfully ran '%s'\n", __FUNCTION__);
	#endif
} /** End of function. **/


/** 
 * Lugemiseks kasuta realloc() funktsiooni, laiendades mäluala suurust jooksvalt lugemise käigus.
 * **/

//~ void FreeStruct(void **p, int n)
void FreeStruct(candidate *p, int n)
{
	for (int i = 0; i < n; i++)
	{
		SafeFree((void **)&p[i].fName);
		SafeFree((void **)&p[i].lName);
	}
	SafeFree((void **)&p); // free entire struct.
	#ifdef DEBUG
	printf("\n Successfully ran '%s'\n", __FUNCTION__);
	#endif
}


/**
 * Function to check if allocated memory can be free without memory leaks.
 **/
void SafeFree(void **p)
{
	if (p != NULL && *p != NULL)
	{
		free(*p);
		*p = NULL;
	}
}
