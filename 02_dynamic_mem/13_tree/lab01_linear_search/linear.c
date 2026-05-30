/**
 * File:        linear.c
 * Author:      Frank Christopher Kirch
 * Created:     28.04.2024
 * Last edit:   30.05.2026
 *
 * Description: Code to find unique strings in a file.
 *              Uses a dynamically expanded array to store data and linear
 *              search for finding unique values.
 * 
 * Usage:       ./program_name name_of_input_file
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

#define MAX_NAME 64
#define NAME_NOT_UNIQUE -1

typedef struct
{
    char name[MAX_NAME];
    unsigned int count;
    
} person;

int CheckNameUnique(person *db, int n, char *name);
int ReadData(person **db, char *file);
void PrintData(person *db, int n);

void SafeFree(void **p);

int main(int argc, char **argv)
{
    person *data = NULL;
    int n;

    /* Makes sure that the input file name was passed to the program */        
    if (argc != 2)
    {
        printf("No input file provided!\n");
        exit(EXIT_FAILURE);
    }
    
    clock_t start, end;
    start = clock();
    
    n = ReadData(&data, argv[1]);
    
    end = clock();
    double timeRead = (double)(end - start) / CLOCKS_PER_SEC;
	
    
    
    start = clock();
     
    PrintData(data, n);
    
    end = clock();
    double timePrint = (double)(end - start) / CLOCKS_PER_SEC;
    
    start = clock();
    
    SafeFree((void **) &data);
    
    end = clock();
    double timeFree = (double)(end - start) / CLOCKS_PER_SEC;

	putchar('\n');
    printf("Time it took to read '%d' lines: %.6lf seconds.\n", n, timeRead);
    printf("Time it took to print '%d' lines: %.6lf seconds.\n", n, timePrint);
	printf("Time it took to free structure: %.6lf seconds.\n", timeFree);
	putchar('\n');
    
    return EXIT_SUCCESS;
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

/**
 * Description:    prints out the number of members, followed by the
 *                 members themselves.
 *
 * Parameters:     db - pointer to the data array
 *                 n - number of members in the data array
 *
 * Return:         void
 */
void PrintData(person *db, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%s", db[i].name);
        printf(": %d times. \n", db[i].count);
    }
    
    putchar('\n');
    printf("Found %d unique names\n", i);
	putchar('\n');
}

/**
 * Description:    Reads the data from a file and stores it to a dynamic array,
 *
 * Parameters:     db - double pointer to the struct array. A new array
 *                 will be assigned there after reading.
 *                 file - string with the name (path) of the file to read from
 *
 * Return:         int, number of lines read from the file
 */
int ReadData(person **db, char *file)
{
    int namePos;
    int uniqueNames = 0;    /* Amount of unique names*/
    person *pTemp, *pData;
    
    char fullName[MAX_NAME];
    
    char fName[MAX_NAME];
    char lName[MAX_NAME];
    char locationBuf[MAX_NAME];
    int idBuf;
    
    FILE *fp = fopen(file, "r");
    if (fp == NULL)
    {        
        perror("Opening of input file failed");
        exit(EXIT_FAILURE);
    }
    
    pData = NULL;
    while (fscanf(fp, "%d %s %s %s", &idBuf, fName, lName, locationBuf) == 4)
    {
        snprintf(fullName, MAX_NAME * 2, "%s %s", fName, lName);
     
        /* Checks for uniqueness of the name, stores the index if not unique */
        namePos = CheckNameUnique(pData, uniqueNames, fullName);
        
        if (namePos == NAME_NOT_UNIQUE)
        {
            /* Name unique, need to make room for it in the array*/            
            pTemp = realloc(pData, sizeof(person) * ((unsigned)uniqueNames + 1));
            if (pTemp == NULL)
            {
                fprintf(stderr, "Error expanding memory!\n");
                free(pData);
                exit(EXIT_FAILURE);
            }
            pData = pTemp;
            
            /* Copies  the new string into the data struct */
            strcpy(pData[uniqueNames].name, fullName);
            
			pData[uniqueNames].count = 1;
            
            /* Increases the count of unique names */
            uniqueNames++;
        }
        else  /** namePos is the unique-occurence's index.**/
        {
			pData[namePos].count++; /** Struct-array @ index 'namePos', we .cnt++ **/
		}
    }
    *db = pData;
    fclose(fp);
    return uniqueNames;
}

/**
 * Description:    Checks if the passed name is already a part of the array
 *
 * Parameters:     db - pointer to the data array
 *                 n - number of members in the data array (at the moment)
 *                 name - string that will be checked if already in the array
 *
 * Return:         integer. Index of the name if it is found in the array.
 *                 NAME_NOT_UNIQUE is returned if it is not found.
 */
int CheckNameUnique(person *db, int n, char *name)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (!strcmp(name, db[i].name))
        {
            /* The name was foumd, thus it's not unique. Returning the indx.*/
            return i;
        }
    }
    /* The name was not found in the struct array */
    return NAME_NOT_UNIQUE;
}
