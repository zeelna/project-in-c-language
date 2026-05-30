#include "struct_helper.h"

/**
 *  Read statistics from file until limit is reached or ends before that.
 *  **/
int ReadFile(subject subjects[READ_LIMIT], int limit, char filename[FILE_NAME_LEN])
{
	FILE *fInputStream;
    fInputStream = fopen(filename, "r"); 
    
    /** Check if file stream EMPTY for file "input.txt" **/
	if (fInputStream == NULL)
	{
		perror("");		// error checking ("permissions denied")
		fprintf(stderr, "Error opening file '%s'\n", filename); 
	}

	subject *p = subjects;
	int count = 0;
	
	char line[LINE_LEN] = {0};
	/** fgets can read whitespaces inclusively. Thus do not use fscanf here.**/
	while (fgets(line, LINE_LEN, fInputStream)) 
	{
		/** fgets append '\n' we need to swap for '\0' **/
		int len = GetLength(line);
		GetString(line, len);
		
		/** Reading subject as string into struct's field**/		
		strcpy(p->entry, line); 
		
		/** Reading each grade (4, 5, 6, 7) into struct's grades[] **/
		
		#ifdef DEBUG
		printf("Entry: Got (%d): %s \n", count, p->entry);
		#endif 
		
		p++; // DO NOT FORGET; // moving pointer by size_of to next element
		
		count++; // DO NOT FORGET;
		if (count >= limit)
		{
			fprintf(stderr, "ERROR! Input file is too long. "
			"Allowed limit is %d entries. We read [0-%d] entries. "
			"\nReading of the file has stopped, "
			"continuing with a partial dataset.\n", limit, count-1);		
			break;
		}
	}
	// Tip: LAST STEP Close file.
	fclose(fInputStream);
	#ifdef DEBUG
	printf("\n Successfully ran '%s'\n", __FUNCTION__);
	#endif

	putchar('\n');
	return count;
}




/*
 * Get the input AND swap line-break for null-terminator
 */
void GetString(char str[], int n)
{
	// Read the string from keyboard
	//~ fgets(str, n, stdin);
	
	// TODO: Find the length of the actual string we just read
	size_t len = strlen(str); // replace with GetLenght Fn?
	
	// TODO: Write the string terminator in place of the newline to fix the string
	str[len-1] = '\0'; // Between ' ' (bc \0 is 1 byte, char; DO NOT " ")
	
	#ifdef E_DEBUG
	DebugString(str);
	#endif
}


/*
 * Get the sum of all grades for that subject
 */
int GetLength(char str[])
{
	//~ size_t len = strlen(str);
	int len = strlen(str);
	return len;
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

/*
 * Replaces all characters matching to key to replacement in the given string.
 */
int StringToIntArray(char string[LINE_LEN], int intArr[LINE_LEN], char delimiter[DELIMITER_LEN], subject *pSubject)

{
	/** Tip: [1 + STR_LEN / 2] <=== "2,1,9,3" is with len 7  
	 * 								[2, 1, 9, 3] with len 4**/
	
	int cnt = 0; // DO NOT FORGET ==> length of intArr.
	
	int *pIntArr = intArr; // Pointer initialization.
	
	/** Return first token with strtok() --> as-if 'getFirstToken'**/
    char* token = strtok(string, delimiter);

	/** Keep printing tokens while one of the delimiters present in str[]. Checks for delimiter**/
    while (token != 0) //  while (token != NULL)
    {
		/** Intemediary: atoi() ==> convert string to 'int' **/
		*pIntArr = atoi(token);
		
        //~ pSubject->grades[cnt] = *pIntArr; // Alternative, assign to struct.
        
		#ifdef DEBUG_E
		printf("DEBUG [%d]: %d + %d = %d. Successfully does 'addition', thus int.\n", cnt, pSubject->grades[cnt], 3 , pSubject->grades[cnt] + 3); /** & store to int[]**/
        #endif
        
        
		/** // Use of strtok,  go through other tokens **/
        token = strtok(0, delimiter);    // token = strtok(NULL, delimiter); 
        
        cnt++;   // DO NOT FORGET ==> for intArr index incrementing
        pIntArr++; // DO NOT FORGET ==> move pointer to next location.
    }
    
    #ifdef DEBUG
    printf("strtok() count: %d. <= Amount of items found by separating with delimiter. \n", cnt);
    printf("\n Successfully ran '%s'\n", __FUNCTION__);
    #endif
    return cnt; /** lenght of intArr **/
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
double GetAverageOfGrades(subject *p, int sum)
{
	double average = (double)sum / p->gradesLen;
	return average;
}

/*
 * Print structure fields "subject name", "grades" and "average"
 */
void PrintStructArray(subject *subjects, int len) 
{
	const char notAvailable[5] = "N/A";
	subject *p = subjects;
	putchar('\n');
	for (int i = 0; i < len; i++)
	{
		#ifdef DEBUG
		printf("[%d]", i + 1);
		#endif
		
		printf("Subject: %-15s\n", p->name);

		if (p->gradesSum == 0)
		{
			printf("Grades:  %s \n", notAvailable);
			printf("Average: %s \n", notAvailable);
		}
		else 
		{
			printf("Grades: ");	
			PrintGradesIntArray(p);
		
			printf("Average: %.2lf\n", p->average);
		}
		p++; // dot not forget
		putchar('\n');
	}
	putchar('\n');
	
	#ifdef DEBUG
	printf("\n Successfully ran '%s'\n", __FUNCTION__);
	#endif
}
/*
 * Print each grade of that subject. Grades stored in integer array, int[].
 */

void PrintGradesIntArray(subject *p)
{
	int len = p->gradesLen;

	int j;
	for (j = 0; j < len; j++)
	{
		printf(" %d", p->grades[j]);
	}
	putchar('\n');
}



