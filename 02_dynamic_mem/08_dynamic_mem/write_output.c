#include "main.h"
#include "write_output.h"

/** 
 * Pakun välja kaks erinevat võrdlusfunktsiooni võimalust.
 * Teisel juhul loome lisaviidad, mis võtavad täiendavalt mälu, kuid lihtsustavad koodi loetavust.
 **/

int ComparPersonByPoints(const void *a, const void *b)
{
    // Temporary cast pointers for readability
    candidate *pA = (candidate *)a;
    candidate *pB = (candidate *)b;
 
    if (pA->points > pB->points)
        return -1;
	else if (pA->points < pB->points)
		return 1;
	else
		return 0;
}

void PrintStructArray(candidate *candidates, int len) 
{
	int mCnt = 0;
	int iCnt = 0;
	int eCnt = 0;
	candidate *p = candidates;
	
	for (int i = 0; i < len; i++)
	{

				
		if (strcmp(p->code, "IACB") == 0) {
			iCnt++;
		} else if (strcmp(p->code, "MVEB") == 0) {
			mCnt++;
		} else if (strcmp(p->code, "EARB") == 0) {
			eCnt++;
		}
		
		if ((strcmp(p->code, "IACB") == 0 && iCnt <= 7)
		|| (strcmp(p->code, "MVEB") == 0 && mCnt <= 7)
		|| (strcmp(p->code, "EARB") == 0 && eCnt <= 7))
		{
			printf("%d %12s %10s %6s %4.1lf\n", p->ID, p->fName, p->lName, p->code, p->points);

		}
		p++;
	}
}


/**
 * Writing a log message to file. Opens file, writes and then closes file.
 **/	
void WriteToFile(char *filename, int nCandidates, candidate *p)
{
	/** pointer for file stream (input file streams) **/
	FILE *fOutStream;
    fOutStream = fopen(filename, "w");
    
    /** Check if file stream EMPTY for file "input.txt" **/
	if (fOutStream == NULL)
	{
		fprintf(stderr, "Error writing to file '%s'.\n", filename); /** Informint user that we cannot open logfile**/
	}
	else
	{
		const char headers[5][12] = {"ID", "FirstName", "SecondName", "Code", "Points"};
		fprintf(fOutStream, "%s %s %s %s %s\n", headers[0], headers[1], headers[2], headers[3], headers[4]);
		/** Write to file **/
		for (int i = 0; i < nCandidates; i++)
		{
			fprintf(fOutStream, "%d %s %s %s %.1lf\n", i,
												p->fName,p->lName,
												p->code, p->points); 
			
			p++;
		}
		/** Closing file-stream **/
		fclose(fOutStream);
	}
	#ifdef DEBUG
	printf("\n Successfully ran '%s'\n", __FUNCTION__);
	#endif	
}


/*
 * Print debug information of string. Each char, it's index and ASCII.
 */
void DebugString(char str[])
{
    int i = 0;
    printf("String is: '%s'\n", str);
    while (str[i] != '\0')
    {
        printf("str[%d] = %3hhu %c\n", i, str[i], str[i]);
        i++;
    }
    printf("\n");
}
/**
 * Description:   Function to read data from a file. During this, a dynamic
 *                struct array will be created and expanded using realloc()
 * Parameters:    ppData - dbl pointer where to store the allocated array pointer
 *                pLineCount - pointer to store the read line count
 *                fileName - name of the input file to read
 * Return:        0 if data is read successfully
 *                1 if error is encountered
 */

int ReadData(candidate **ppCandidateData, int *pLineCount, char *fileName)
{

    FILE *fInputStream;
    fInputStream = fopen(fileName, "r"); 
   
    /** Check if file stream EMPTY for file "input.txt" **/
	if (fInputStream == NULL)
	{
		perror("");		// error checking ("permissions denied")
		/** Redirect message to standard error stream.**/
		fprintf(stderr, "Error opening file '%s'\n", fileName); 
	}
    
    candidate tempCandidate;
    
    // Current line counter
    int cnt = 0;
 
    // Main pointer for the allocated array
    candidate *pArr = NULL;
    
    // Secondary temporary pointer for the allocated array
    candidate *pTemp = NULL;
 
    // Temporary buffers for reading (all variables you intend to read!)
	char lNameBuf[NAME_LEN] = {0};
	char fNameBuf[NAME_LEN] = {0};
 
   
    while (fscanf(fInputStream, "%d %s %s %s %lf",
										&tempCandidate.ID,
										lNameBuf,
										fNameBuf,
										tempCandidate.code,
										&tempCandidate.points) == 5) 
	{
		#ifdef DEBUG
			putchar('\n');
			printf("DEBUG FSCAN: Got (%d): %d %s %s %s %.1lf\n",
										cnt,
										tempCandidate.ID,
										lNameBuf,
										fNameBuf,
										tempCandidate.code,
										tempCandidate.points);
		#endif	
		
		#ifdef DEBUG
		//~ putchar('\n');
		puts("Before realloc()");
		printf("pArr = %p\n", pArr);
		printf("pTemp = %p\n", pTemp);
		putchar('\n');
		#endif
		
        // rellocate memory to fit the latest line
		pTemp = (candidate *)realloc(pArr, sizeof(candidate) * (size_t)(cnt + 1));
 
        // Check allocation was successful
		if (pTemp == NULL)
		{
			printf("Not enough memory to read more lines!\n");
			
			FreeStruct(pArr, cnt);
			fclose(fInputStream);
			return 1; // error
			
		}
		
		#ifdef DEBUG
		puts("Before pArr = pTemp");
		printf("pArr = %p\n", pArr);
		printf("pTemp = %p\n", pTemp);
		putchar('\n');
		#endif
 
        // Make both pointers point at the memory location
		pArr = pTemp; // do not forget
        
		#ifdef DEBUG
		puts("After pArr = pTemp");
		printf("pArr = %p\n", pArr);
		printf("pTemp = %p\n", pTemp);
		//~ putchar('\n');
		#endif
        
        // Allocate memory for the struct members fName and lName, check allocation!
		//~ pArr->fName = strdup(fNameBuf);
		//~ pArr->fName = strdup(tempCandidate->fName);
		
		tempCandidate.fName = strdup(fNameBuf);
		if (tempCandidate.fName == NULL)
		{

			FreeStruct(pArr, cnt);
			return 1; // error
		}
		
		tempCandidate.lName = strdup(lNameBuf);
		if (tempCandidate.lName == NULL)
		{
			FreeStruct(pArr, cnt);
			return 1; // error
		}
		#ifdef DEBUG
		//~ printf("\nDEBUG tempCandidate->: Got (%d): %d %s %s %s %.1lf",
									//~ cnt, 
									//~ tempCandidate->ID,
									//~ tempCandidate->lName,
									//~ tempCandidate->fName,
									//~ tempCandidate->code,
									//~ tempCandidate->points);
									
		//~ printf("\nDEBUG tempCandidate. : Got (%d): %d %s %s %s %.1lf",
									//~ cnt, 
									//~ tempCandidate.ID,
									//~ tempCandidate.lName,
									//~ tempCandidate.fName,
									//~ tempCandidate.code,
									//~ tempCandidate.points);
		#endif
		
        // Copy data in from the buffers into the struct array
		*(pArr + cnt) = tempCandidate;
		
		#ifdef DEBUG						
		printf("DEBUG pArr: Got (%d): %d %s %s %s %.1lf",
										cnt,
										(pArr + cnt)->ID,
										(pArr + cnt)->lName,
										(pArr + cnt)->fName,
										(pArr + cnt)->code,
										(pArr + cnt)->points);+
		putchar('\n');
		#endif

        // Increment number of records successfully read
        cnt++;
    }
    
	#ifdef DEBUG
	printf("\nDEBUG: pArr: pp: <%p> p:<%p>\n", &pArr, pArr);
	#endif
	
    // Store the allocated array through the double pointer 
    *ppCandidateData = pArr;
 
	#ifdef DEBUG
	printf("DEBUG: ppCandidateData: pp: <%p> p:<%p>\n", ppCandidateData, *ppCandidateData);
	#endif
    // Store the number of lines trough the pointer
    *pLineCount = cnt;
 
	#ifdef DEBUG
	printf("\n Successfully ran '%s'\n", __FUNCTION__);
	#endif
 
    // Everything OK
    return 0;
}
