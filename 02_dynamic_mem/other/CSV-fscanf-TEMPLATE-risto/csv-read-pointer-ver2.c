#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define READ_LIMIT 9
#define FILE_NAME_LEN 30

#define SUBJECT_LEN 10
#define GRADES_COUNT 13

#define DEBUG

typedef struct subject
{
	char name[SUBJECT_LEN];
	int grades[GRADES_COUNT];
	int gradesLen;
	
} subject;

//~ int ReadFile(subject subjects[READ_LIMIT], int limit, char filename[FILE_NAME_LEN]);
int ReadFile(subject subjects[READ_LIMIT], int limit, char *filename);



int main(void)
{
	
	subject subjects[READ_LIMIT] = {0};
	int cnt = ReadFile(subjects, READ_LIMIT, "data_grades.csv");
	printf("\ncnt: %d\n", cnt);
	
	return EXIT_SUCCESS;
}




//~ int ReadFile(subject subjects[READ_LIMIT], int limit, char filename[FILE_NAME_LEN])
int ReadFile(subject subjects[READ_LIMIT], int limit, char *filename)
{

	FILE *fInputStream;
    fInputStream = fopen(filename, "r"); 

    /** Check if file stream EMPTY for file "input.txt" **/
	if (fInputStream == NULL)
	{
		perror("");		// error checking ("permissions denied"
		/** Redirect message to standard error stream.**/
		fprintf(stderr, "Error opening file '%s'\n", filename); 
	}
	/** Pointer variable to, points to 1st element (0th index) on array.**/
	subject *p = subjects;
	
	int cnt = 0;
	while (fscanf(fInputStream, "%[^,],%d",
									p->name,
									&p->gradesLen) == 2) 
	{
		#ifdef DEBUG
			putchar('\n');
			printf("\nDEBUG: Got (%d): '%s' <%d>",
									cnt,
									p->name,
									p->gradesLen);
		#endif
		
		#ifdef DEBUG
		printf("\nGrades:");
		#endif
		
		int i;
		for (i = 0; i < p->gradesLen; i++)
		{
			fscanf(fInputStream, ",%d", &p->grades[i]);
			
			#ifdef DEBUG
			printf(" %d", p->grades[i]);
			#endif
		}
		/** If no grades to be found from CSV, then print N/A.**/
		if (i <= 0)
		{
			printf(" N/A");
		}
		
		
		/** Important in any csv-read. **/
		fgetc(fInputStream); // DO NOT FORGET! Removes line-break \n on each line
		
		p++; // DO NOT FORGET; // moving pointer by size_of to next element
		
		cnt++; // counting how many lines we read. BEFORE limit-check!
		if (cnt >= limit)
		{
			/** Outside log-file**/ // for some reason, stderr prints before loop of grades above.
			fprintf(stderr, "\nERROR! Input file is too long. "
			//~ printf("\nERROR! Input file is too long. "
			"Allowed limit is %d entries. We read [0-%d] entries. "
			"\nReading of the file has stopped, "
			"continuing with a partial dataset.\n", limit, cnt-1);		
			break;
		}
		
	}
	// Tip: LAST STEP Close file.
	fclose(fInputStream);
	
	return cnt;
}
