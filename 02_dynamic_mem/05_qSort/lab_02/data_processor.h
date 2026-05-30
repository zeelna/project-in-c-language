/**
 * File:         data_processor.h
 * Author:       Frank Christopher Kirch
 * Created:      16.03.2024
 * Modified:     30.05.2026
 *
**/

#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DEBUG 1

//~ #define READ_LIMIT 1472
#define READ_LIMIT 1700
//~ #define READ_LIMIT 63

#define DATE_LEN 11

#define FILE_NAME_LEN 40

typedef struct entry
{
	char LastStatisticsDate[DATE_LEN];
	char StatisticsDate[DATE_LEN];
	int dailyCases;
	int totalCases;
	int totalCases14Days;
	double perPopulation;
} entry;



int ComparFuncTop10Days(const void *x, const void *y);
void PrintStructArray(entry lineEntry[READ_LIMIT], int len);
void PrintStructArrayBackWards(entry lineEntry[READ_LIMIT], int len, int limit);

int ReadFile(entry lineEntry[READ_LIMIT], int limit, char filename[FILE_NAME_LEN]);
#endif
