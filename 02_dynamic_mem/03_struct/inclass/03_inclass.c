#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1 // turn into 0, if we want remove DEBUG messages.
#define ARGS_CNT 2
#define ARGS_FILE_NAME 		argv[1]
#define ARGS_EXEC_NAME 		argv[0]

#define STR_NAME_LEN 64
#define MAX_STUDENTS 32

typedef struct student
{
	char name[STR_NAME_LEN];
	int grade;
} student;

int ReadStudentData(student gradeBook[], int limit, char *filename);

void PrintStudentData(student gradeBook[], int studentCount);

int main(int argc, char **argv)
{
	if (argc != ARGS_CNT)
	{
		fprintf(stderr, "Usage: %s data_file\n", ARGS_EXEC_NAME );
		return EXIT_FAILURE;
	}
	
	// loome massiivi, mille sisuks on andmetüüp 'struct student'
	student studentGrades[MAX_STUDENTS];
	
	/** Loeme failist mällu : **/
	//~ ReadStudentData(studentGrades[MAX_STUDENTS], ARGS_FILE_NAME);
	int studentCount = ReadStudentData(studentGrades, MAX_STUDENTS, ARGS_FILE_NAME);
	PrintStudentData(studentGrades, studentCount);
	return EXIT_SUCCESS;
}

int ReadStudentData(student gradeBook[], int limit, char *filename) 
{
	

	int stdCnt = 0; // number of students read from file
	
	FILE *fStudents = fopen(filename, "r");
	if (fStudents == NULL)
	{
		fprintf(stderr, "Error opening input file %s", filename);
		perror("");
		// exit(EXIT_FAILURE) // alt: nt küsi uut hoopis failinime kasutajalt
	
		return stdCnt; // return 0 students read
	}
	
	// lisa kontroll: erandjuht kus sõne liiga pikk; kus sisendandmeid n > MAX.
	while (fscanf(fStudents, "%s %d",
							gradeBook[stdCnt].name,
							&gradeBook[stdCnt].grade) == 2) 
	{
		if (DEBUG)
			printf("DEBUG: Got (%d): %s %d\n", stdCnt,
											gradeBook[stdCnt].name,
											gradeBook[stdCnt].grade);
		stdCnt++;
		
		if (stdCnt >= limit)
		{
			fprintf(stderr, "ERROR! Input file is too long. Allowed limit is "
							"%d entries. \nReading of the file has stopped, "
							"continuing with a partial dataset.\n", limit);		
			break;
		}
	}
	fclose(fStudents);
	return stdCnt;
}

void PrintStudentData(student gradeBook[], int studentCount)
{
	if (studentCount <= 0)
	{
		fprintf(stderr, "Student database is empty!\n");
		//~ return EXIT_FAILURE;
		return;
	}
	printf("Student list containts %d students\n", studentCount);
	for (int i = 0; i < studentCount; i++)
	{
		printf("%s %d\n", gradeBook[i].name, gradeBook[i].grade);
	}
}
