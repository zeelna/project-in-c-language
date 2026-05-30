/**
 * File:        generator.c
 * Author:      Frank Christopher Kirch
 * Created:     26.03.2024
 * Modified     30.05.2026
 *
 * Description: This is a random data generator
 * 
 * Note:        This is a starter code for a lab task
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <time.h>

#include "name_pools.h"

#include "filename_helper.h"
#include "generator.h"


int main(void)
{
    /* Names are assigned from the pools in the header*/
    const char *firstNames[] = FIRST_NAME_POOL;
    const char *lastNames[] = LAST_NAME_POOL;
    const char *curriculumCodes[] = CURRICULUM_CODES;

    /* Find the counts for the pool sizes */
    int firstNamePoolSize = sizeof(firstNames) / sizeof(char *);
    int lastNamePoolSize = sizeof(lastNames) / sizeof(char *);
    int curriculumCodePoolSize = sizeof(curriculumCodes) / sizeof(char *);

    printf("The database contains:\n"
           "\t%4d first names\n"
           "\t%4d last names\n"
           "\t%4d curriculum codes\n",
           firstNamePoolSize, lastNamePoolSize, curriculumCodePoolSize);

	/** Ask user how many candidates we generate (random names, random codes and scores)**/
	int nCandidates = PromptNumberOfCandidates();
	
	#ifdef DEBUG
	printf("Selected '%d' candidates. \n", nCandidates);
	#endif
	
	//~ candidate candidates[READ_LIMIT] = {0};
	/** Step 1: allocate memory**/
	candidate *p = (candidate *)calloc((size_t)nCandidates, sizeof(candidate));
	
	/** Step 2: Check if enough memory can be allocated.**/
	if (p == NULL)
	{
		printf("Not enough memory!\n");
		exit(EXIT_FAILURE);
	}
	
	
	//~ srand((u_int)time(NULL)); // DO NOT FORGET. Resets random number.
	srand(time(NULL)); // DO NOT FORGET. Resets random number.
	
	for (int i = 0; i < nCandidates; i++) /** nCandidates is userInput.**/
	{
		//~ srand((u_int)time(NULL)); // DO NOT FORGET. Resets random number.
		int fNameIdx = GetRand(0, firstNamePoolSize - 1);
		(p + i)->fName = firstNames[fNameIdx];
		
		int lNameIdx = GetRand(0, lastNamePoolSize - 1);
		(p + i)->lName = lastNames[lNameIdx];
		
		int codeIdx = GetRand(0, curriculumCodePoolSize - 1);
		(p + i)->code = curriculumCodes[codeIdx];
		
		/** Finding pseudo-random nrs from 100 to 300, and dividing by 10, we get 10.0 - 30.0 **/
		(p + i)->points = GetRand(100, 300) / (double)10;		
		
		#ifdef DEBUG
		printf("\n DEBUG[%d]: fName: %s <%p>.", i, (p + i)->fName, (p + i)->fName);
		printf("\n DEBUG[%d]: lName: %s <%p>.", i, (p + i)->lName, (p + i)->lName);
		printf("\n DEBUG[%d]: code: %s <%p>.", i, (p + i)->code, (p + i)->code);
		printf("\n DEBUG[%d]: points: %.1lf <%p>.", i, (p + i)->points, &(p + i)->points);
		putchar('\n');
		#endif
	}
	puts("Candidates sorted by last and first name: ");
      
	/** ComparCandidate sorts by Lastname, and if matches, then first name.**/
	qsort(p, (size_t)nCandidates, sizeof(candidate),
										ComparCandidate);
		
	/** Print results in formatted table.**/
	PrintStructArray(p, nCandidates);

	/** Extra 01.**/
	char outputFileName[FILE_LEN] = {0};

	char *userExtention = ".csv"; /** default value.**/
	
	
	/** Constant string array, indexed by 'enum Type'. Prompting user to choose type.**/
	char *formats[EXT_LEN] = {[SPACE_DELIMITED] = ".txt",
										  [CSV] = ".csv"
							  }; 
  
	/** Leverange prompt to return enum type, hardcoded with CSV = 0 and SPACE = 1**/
	int destFileType = PromptCsvOrSpaceDelimited(outputFileName);
	
	userExtention = (destFileType == CSV) ? formats[CSV]: formats[SPACE_DELIMITED];
	
	/** Ask for filename as string**/
	PromptOutputFileName(outputFileName);
	

	if (!IsValid(outputFileName, userExtention)) /** userExtention is 1 single string (".txt" OR ".csv") **/
	{
		ConcatExtention(outputFileName, userExtention);
	}
	
	/** Write to file with space delimited. **/
	WriteToFile(outputFileName, nCandidates, p);
	
	/** Dependant if user wants CSV or SPACE_DELIMITED, replace.**/
	if (destFileType == CSV)
	{
		/** Opening the outputFileName's filestream and swapping 'white-space' with 'comma**/
		ReplaceCharInFile(outputFileName, ' ', ',');
	}
	else 
	{
		/** Opening the outputFileName's filestream and swapping 'white-space' with 'comma**/
		ReplaceCharInFile(outputFileName, ',', ' ');
	}
	
	/** Step 3. Release allocated memory. **/
	free(p); // free dynamically allocated memory.
	
	printf("Results were written to file '%s'.\n", outputFileName);
	printf("Successfuly ran this program.\n");
    return EXIT_SUCCESS;
}
/**
 * Description:    Generates a random number in range provided, ends inclusive
 *
 * Parameters:     min, minimum value
 *                 max, maximum vale
 *
 * Return:         integer, generated random number
 */
int GetRand(int min, int max)
{
    //~ srand((u_int)time(NULL)); // DO NOT FORGET. Resets random number.
    return (rand() % (max - min + 1)) + min;
}


/**
 * Description:    Ask user for number of candidates
 *
 * Parameters:     void.
 *
 * Return:         integer, number of candidates.
 */

int PromptNumberOfCandidates(void)
{
	putchar('\n');
	puts("Enter number of candidates: ");
	
	int nCandidates = 0;
	scanf("%d", &nCandidates);
	
	return nCandidates;
}

/** 
 * Pakun välja kaks erinevat võrdlusfunktsiooni võimalust.
 * Teisel juhul loome lisaviidad, mis võtavad täiendavalt mälu, kuid lihtsustavad koodi loetavust.
 **/
int ComparCandidate(const void *a, const void *b)
{
    // Temporary cast pointers for readability
    candidate *pA = (candidate *)a;
    candidate *pB = (candidate *)b;
 
    // Get comparison for last names
    int ret = strcmp(pA->lName, pB->lName);
    
    // When last names match, return difference by first name
    if (ret == 0)
        return strcmp(pA->fName, pB->fName);
    
    // return difference by last name
    return ret;
}

void PrintStructArray(candidate *candidates, int len) 
{
	candidate *p = candidates;
	
	for (int i = 0; i < len; i++)
	{
		printf("%12s %10s %6s %4.1lf\n", p->fName, p->lName, p->code, p->points);
		p++;
	}
	putchar('\n');
}

/**
 * Writing a log message to file. Opens file, writes and then closes file.
 **/	
//~ void WriteToFile(char filename[FILE_LEN], int nCandidates, candidate *p)
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
		//~ fprintf(fOutStream, "ID FirstName SecondName Code Points\n");
		fprintf(fOutStream, "%s%s %s %s %s\n", headers[0], headers[1], headers[2], headers[3], headers[4]);
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
}


enum Type PromptCsvOrSpaceDelimited(char *outputFileName)
{
	printf("Do you want to send results to CSV file.\n");
	if (PromptYesNo() == false)
	{
		printf("Results will be written to'.txt' file.");
		return SPACE_DELIMITED;
	}
	else
	{
		printf("Results will be written to CSV format.\n");
		return CSV;
	}
}

/**
 * Prompts for user confirmation until received
 **/
bool PromptYesNo(void)
{
	puts("Enter [Y] or [N]");
	putchar('>');
	char c;
	while (true)
	{
		c = (char)getchar();
		if (c == '\n')
			continue;
		if (c == 'y' || c == 'Y')
			return true;
		else if (c == 'n' || c == 'N')
			return false;
		else
			printf("Please enter y or n!\n");
	}
}

/**
 * Ask user to choose a filename where logs will be sent. Avoid empty input.
 */
void PromptOutputFileName(char newFilename[FILE_LEN])
{
	puts("Enter a filename to send the result: ");
	//~ putchar('\n');
	char ext[EXT_LEN] = {0};
	while (true)
	{
		scanf("%s", newFilename);
		//~ scanf("%*c%[^.].%s", newFilename, ext);
		
		#ifdef DEBUG
		DebugString(newFilename);
		//~ DebugString(ext);
		#endif
		
		#ifdef DEBUB
		printf("\nfilename: %s, ext: %s\n", newFilename, ext);
		#endif
		
		if (strcmp(newFilename, "") != 0)
			break;
	}
}

/**
 * Print debug information of string. Each char, it's index and ASCII.
 **/
void DebugString(char *str)
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

