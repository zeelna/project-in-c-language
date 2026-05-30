#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define READ_LIMIT 10
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

int ReadFile(subject subjects[READ_LIMIT], char filename[FILE_NAME_LEN]);



int main(void)
{
	
	subject subjects[READ_LIMIT] = {0};
	int cnt = ReadFile(subjects, "data_grades.csv");
	printf("\ncnt: %d\n", cnt);
	
	return EXIT_SUCCESS;
}




int ReadFile(subject subjects[READ_LIMIT], char filename[FILE_NAME_LEN])
{
	
	subject *p = subjects;
	
	FILE *fInputStream;
    fInputStream = fopen(filename, "r"); 

    /** Check if file stream EMPTY for file "input.txt" **/
	if (fInputStream == NULL)
	{
		perror("");		// error checking ("permissions denied"
		/** Redirect message to standard error stream.**/
		fprintf(stderr, "Error opening file '%s'\n", filename); 
	}
	//~ subject *p = subjects;

	int cnt = 0;
	while (fscanf(fInputStream, "%[^,],%d",
									subjects[cnt].name,
									&subjects[cnt].gradesLen) == 2) 
	{
		#ifdef DEBUG
			printf("\nDEBUG: Got (%d): '%s' <%d>",
									cnt,
									subjects[cnt].name,
									subjects[cnt].gradesLen);
		#endif
		
		#ifdef DEBUG
		puts("\nGrades:");
		#endif
		
		int i;
		for (i = 0; i < subjects[cnt].gradesLen; i++)
		{
			fscanf(fInputStream, ",%d", &subjects[cnt].grades[i]);
			
			#ifdef DEBUG
			printf(" %d", subjects[cnt].grades[i]);
			#endif
		}
		/** Important in any csv-read. **/
		fgetc(fInputStream); // DO NOT FORGET! Removes line-break \n on each line
		
		//~ p++; // DO NOT FORGET; // moving pointer by size_of to next element
		
		cnt++;
		
		
		
	}
	// Tip: LAST STEP Close file.
	fclose(fInputStream);
	
	return cnt;
}
