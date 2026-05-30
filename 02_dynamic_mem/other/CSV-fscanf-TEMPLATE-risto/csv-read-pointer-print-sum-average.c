#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define READ_LIMIT 9
#define FILE_NAME_LEN 30

#define SUBJECT_LEN 25
#define GRADES_COUNT 13

#define DEBUG

typedef struct subject
{
	char name[SUBJECT_LEN];
	int grades[GRADES_COUNT];
	
	int gradesLen;
	
	int gradesSum;
	double average;
	
} subject;

//~ int ReadFile(subject subjects[READ_LIMIT], int limit, char filename[FILE_NAME_LEN]);
int ReadFile(subject subjects[READ_LIMIT], int limit, char *filename);

double GetAverageOfGrades(int sum, int len);
int GetSumOfGrades(subject *p);

void PrintGrades(subject *p);

//~ void PrintStructArray(subject *subjects, int len) 
void PrintStructArray(subject subjects[READ_LIMIT], int len);

int main(void)
{
	
	subject subjects[READ_LIMIT] = {0};
	int countRead = ReadFile(subjects, READ_LIMIT, "data_grades.csv");
	printf("\ncnt: %d\n", countRead);
	
	subject *p = subjects;
	
	for (int i = 0; i < countRead; i++)
	{
		int sum = GetSumOfGrades(p);
		
		p->gradesSum = sum;
		p->average = GetAverageOfGrades(sum, p->gradesLen);
		
		p++; // Move pointer to next 'subjects' array-element's pointer.
	} /** End of OUTER, structure loop (p++)**/
	
	PrintStructArray(subjects, countRead); /** Wrapper, calls PrintGrades.**/
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
		
		p++; /** DO NOT FORGET; // moving pointer by size_of to next element **/
		
		cnt++; /** counting how many lines we read.**/ // BEFORE limit-check!
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


/*
 * Get the sum of all grades for that subject
 */
int GetSumOfGrades(subject *p)
{
	int len = p->gradesLen; /** Stored length of int[] in struct.**/
	
	int sum = 0;
	for (int j = 0; j < len; j++)
	{
		sum += p->grades[j];
	}
	return sum;
}


/*
 * Get the average-grade, by using sum of all grades for that subject
 */
double GetAverageOfGrades(int sum, int len)
{
	double average = (double)sum / len;
	
	return average;
}

/*
 * Print each grade of that subject. Grades stored in integer array, int[].
 */
void PrintGrades(subject *p)
{
	int len = p->gradesLen;

	int j;
	for (j = 0; j < len; j++)
	{
		printf(" %d", p->grades[j]);
	}
	putchar('\n');
}


/*
 * Print structure fields "subject name", "grades" and "average"
 */
//~ void PrintStructArray(subject *subjects, int len) 
void PrintStructArray(subject subjects[READ_LIMIT], int len) 
{
	const char notAvailable[5] = "N/A";
	subject *p = subjects;
	
	putchar('\n');
	for (int i = 0; i < len; i++)
	{
		#ifdef DEBUG
		printf("[%d]", i + 1);
		#endif
		
		printf("Subject: %s\n", p->name);

		if (p->gradesSum == 0)
		{
			
			/** Print statement to terminal**/
			printf("Grades:  %s \n", notAvailable);
			printf("Average: %s \n", notAvailable);
		}
		else 
		{
			printf("Grades: ");	
			PrintGrades(p);
		
			printf("Average: %.2lf\n", p->average);
		}
		p++; // do not forget
		putchar('\n');
	}
	putchar('\n');
	
	#ifdef DEBUG
	printf("\n Successfully ran '%s'\n", __FUNCTION__);
	#endif
}
