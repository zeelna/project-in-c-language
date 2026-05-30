#ifndef STRUCT_PROCESSOR_H
#define STRUCT_PROCESSOR_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define LOG_OFF 0
#define LOG_ERROR 1
#define LOG_WARNING 2
#define LOG_INFO 3


#define LINE_LEN 100
#define SUBJECT_LEN 30
#define GRADES_COUNT 16
#define FILE_NAME_LEN 50
#define READ_LIMIT 15

#define DELIMITER_LEN 1

#define GRADES_COUNT2 14

typedef struct subject
{
	char name[SUBJECT_LEN];
	int grades[GRADES_COUNT2];
	double average;
	
	char entry[LINE_LEN];
	
	char gradesStr[LINE_LEN];
	int gradeStrLen;
	
	int nameLen;
	int gradesLen;
	
	int gradesSum;
	
} subject;

/*
 * Replaces all characters matching to key to replacement in the given string.
 */
int StringToIntArray(char string[LINE_LEN], int intArr[GRADES_COUNT], char delimiter[DELIMITER_LEN], subject *pSubject);



/*
 * Get the input AND swap line-break for null-terminator
 */
//~ void GetString(char str[], int n);
void GetString(char str[]);

/*
 * Print debug information of string. Each char, it's index and ASCII.
 */
void DebugString(char str[]);


/*
 * Get the sum of all grades for that subject
 */
int GetLength(char str[]);

/**
 *  Read statistics from file until limit is reached or ends before that.
 *  **/
int ReadFile(subject subjects[READ_LIMIT], int limit, char filename[FILE_NAME_LEN]);

/*
 * Get the average-grade, by using sum of all grades for that subject
 */
double GetAverageOfGrades(subject *p, int sum);


 /*
 * Get the sum of all grades for that subject
 */
int GetSumOfGrades(subject *p);
			
		
/*
 * Print each grade of that subject. Grades stored in integer array, int[].
 */
void PrintGradesIntArray(subject *p);


/*
 * Print structure fields "subject name", "grades" and "average"
 */
void PrintStructArray(subject *subjects, int len);			

#endif
