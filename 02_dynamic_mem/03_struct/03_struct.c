// gcc -o prog -fsanitize=address 03_struct.c

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>

#define DEBUG 0 // turn into 0, if we want remove DEBUG messages.
#define DEBUG_F 0 // turn into 0, if we want remove "Successful Fn" messages.

#define ARGS_CNT 2
#define ARGS_FILE_NAME 		argv[1]
#define ARGS_EXEC_NAME 		argv[0]

#define ID_LEN 12
#define STR_NAME_LEN 64

#define MAX_PERSON 150

#define IS_NON_RECURRENT 1
#define IS_RECURRENT 0

#define MAX_STR 25

#define YEAR1800 1800
#define YEAR1900 1900
#define YEAR2000 2000
#define YEAR2100 2100
#define YEAR2200 2200

#define MALE1800S 1
#define FEMALE1800S 2

#define MALE1900S 3
#define FEMALE1900S 4

#define MALE2000S 5
#define FEMALE2000S 6

#define MALE2100S 7
#define FEMALE2100S 8

#define MAX_MONTHS 13

#define NOT_ALREADY_SORTED 1
#define ALREADY_SORTED 0

#define MATCH 1
#define NOT_MATCH 0


typedef struct person
{
	char idCode[ID_LEN];
	char firstName[STR_NAME_LEN];
	char lastName[STR_NAME_LEN];
	char city[STR_NAME_LEN];
	char lowercaseCity[STR_NAME_LEN];
	char capitalizedCity[STR_NAME_LEN];
	char dateOfBirth[STR_NAME_LEN];
} person;

enum Months
{
	INVALID,
	JAN, FEB, MARCH, APR, MAY, JUN, JUL, AUG, SEPT, OCT, NOV, DEC
};

/** Finding matching string that contains the substring**/
int IsInputInPhrase(char str[MAX_STR], char substr[MAX_STR]);

int ReadPersonData(person personDB[MAX_PERSON], int limit, char filename[MAX_STR],
				char nonRecurringCities[MAX_PERSON][MAX_STR],
				int *nonRecurrentCitiesLen);
				
void PrintPersonData(person personDB[MAX_PERSON], int personCount);

void ReadStrIntoArrayByIndex(char string[MAX_STR],
								char array[MAX_PERSON][MAX_STR], int index);
								
int ReadStrIntoArray(char string[MAX_STR], 
						char array[MAX_PERSON][MAX_STR], int len);


/** Formatting idCode into birthday details (d. MMMM yyyy => 9. November 1985) **/
void FormatIdCodeToBirthDate(char idCode[ID_LEN], char result[MAX_STR]);

void getMonthStr(enum Months monthEnum, char monthStr[MAX_STR]);
int getFullYear(int genderNr, int yearNr);

/** toLower and toUpper function prototypes (ctype.h)**/
void StringToLowercase(char str[MAX_STR], char lowercasedStr[MAX_STR]);
void CapitalizeLowercasedString(char str[MAX_STR], char capitalizedCity[MAX_STR]);

int IsNonRecurrent(char personsCity[MAX_STR],
				char nonRecurringCities[MAX_PERSON][MAX_STR], int len);


/** Bubble-sort Function prototypes**/
void BubbleSortStrings(char array[MAX_PERSON][MAX_STR], int len);
void PrintAscendingOrder(char array[MAX_PERSON][MAX_STR], int len);
void PrintDescendingOrder(char array[MAX_PERSON][MAX_STR], int len);

void PrintOrderedArray(char array[MAX_PERSON][MAX_STR], int len);

void PrintArray(char nonRecurringCities[MAX_PERSON][MAX_STR],
				int nonRecurrentCitiesLen);

int FindAllMatchingCities(char nonRecurringCities[MAX_PERSON][MAX_STR],
						int nonRecurrentCitiesLen,
						char substring[MAX_STR], 
						char matchingCities[MAX_PERSON][MAX_STR]);

int FindAllPersonFromCities(char matchingCities[MAX_PERSON][MAX_STR],
					int matchingCitiesLen,
					person personDB[MAX_PERSON], int personCount, 
					person personsMatched[MAX_PERSON]); 
 
int IsPersonFromCity(char matchingCities[MAX_PERSON][MAX_STR],
				int matchingCitiesLen, char personsCityFromStruct[MAX_STR]);

void BubbleSortStruct(person struc[MAX_PERSON], int len);

void DebugArgs(int argc, char **argv);

void PrintAscendingOrderStruct(person struc[MAX_PERSON], int len);

int main(int argc, char **argv)
{
	/** Step 0: Print the issued command line parameters.**/
	if (DEBUG)
		DebugArgs(argc, argv);
	
	/** Step 1: Initialized variables**/
	
	/** Step 2: Validate program was run with correct CLI arguments**/
	if (argc != ARGS_CNT)
	{
		/** Exit the program with 'fprintf(stderr, "message"); **/
		fprintf(stderr, "Usage: %s data_file\n", ARGS_EXEC_NAME );
		return EXIT_FAILURE;
	}
	
	/** Step 3: Create array - consisting of struct Person**/
	person personDB[MAX_PERSON];
	
	/** Step 4.Initialize empty array of strings (string == char-array)**/
	char nonRecurringCities[MAX_PERSON][MAX_STR] = {0};
	
	/** Step 5: Populating array of cities with fn "ReadPersonData" **/

	/** Tip: we declare len. Send its memory location, and change the value. 
	 * 		By this method, we can overwrite (store) value without 'return'**/
	
	int nonRecurrentCitiesLen = 0;
	
	int personCount = ReadPersonData(personDB, MAX_PERSON,
									ARGS_FILE_NAME,
									nonRecurringCities, &nonRecurrentCitiesLen);
	
	
												
	/** Step 8: BubbleSort Strings with (strcmp(string1, string2) > 0)"**/
	
	if (DEBUG)
		printf("\n NonRecurrent len: %d \n", nonRecurrentCitiesLen);
		
		
	BubbleSortStrings(nonRecurringCities, nonRecurrentCitiesLen);
	/** Step 9: Loop program until "exit" entered. **/

	while (1)
	{
		/** Step 10: Check user's chosen program mode: **/
		printf("\nEnter a city to search, 'list' to print available cities"
		" or 'exit' to quit\n> ");
		
		/** Step 11: Initialized and read user's chosen input to string**/
		char userInput[MAX_STR] = {0};
		scanf("%s", userInput);
		
		/** Step 12: Format to lowercase ('aLL' to 'all'; 'ALL' to 'all')**/
		char lowercasedInput[MAX_STR] = {0};
		StringToLowercase(userInput, lowercasedInput);
		
		/** Step 13: Move to correct program section. **/
		
		/** Step 14: 'list' mode will print entire array of cities.**/
		if (strcmp(lowercasedInput, "exit") == 0)
			break;
			
		else if (strcmp(lowercasedInput, "list") == 0)
		{
			printf("\nList of cities:");
			PrintAscendingOrder(nonRecurringCities, nonRecurrentCitiesLen);
		}
		/** Step 15: other input will search for persons from city**/
		else 
		{
			/** Step 16: Find input-substring from NonRecurrentCities**/
			/** Found cities (Tallinn, Kallaste) from 'aLL' input **/
			
			char matchingCities[MAX_PERSON][MAX_STR] = {0};
			int matchingCitiesLen = FindAllMatchingCities(nonRecurringCities,
												nonRecurrentCitiesLen,
											lowercasedInput, matchingCities);
			
			person personsMatched[MAX_PERSON] = {0};
			int personsMatchedLen = FindAllPersonFromCities(matchingCities, matchingCitiesLen,
					personDB, personCount, personsMatched);
					
			/** Step 17: String-compare input entire persons city-list**/
			/** Find all persons by city**/
			
			
			/** Step 19: Bubble-sorted by lastName **/
			BubbleSortStruct(personsMatched, personsMatchedLen);

			PrintAscendingOrderStruct(personsMatched, personsMatchedLen);
			
			printf("\nEmployees listed [%d/%d]\n", personsMatchedLen, personCount);
		}
			
	} 
	return EXIT_SUCCESS;
} 


void FormatIdCodeToBirthDate(char idCode[ID_LEN], char result[MAX_STR])
{
		/** Declare variables to store birthday details from person's idCode.**/
		int yearInt, genderInt, monthInt, dayInt;
		
		/** Step 0: Slice the idCode (str) to separate integers to parse later. **/
		sscanf(idCode, "%1d%2d%2d%2d", &genderInt, &yearInt, &monthInt, &dayInt);
		
		if (DEBUG)
			printf("\nIdCode: %s, genderInt: %d, yearInt: %d, monthInt: %d, dayInt: %d\n",
		idCode, genderInt, yearInt, monthInt, dayInt);		
		//~ sprintf(birthDate, "%1d%2d%2d%2d", idCode);
		
		/**------------------------------------------------------- **/
		/** Step 1: Day **/
			/** Above we sscanf to get from --	if (DEBUG)
		printf("\n Successfully ran '%s'\n", __FUNCTION__);> str: "09" to int: 9 **/
			/** Below we sprintf to get from --> int: 9 to str: 9**/
		//~ char day_d[MAX_STR] = {""};
		char day_d[MAX_STR] = {0};
		
		/** thus, formating day from integer to string with sprintf**/
		sprintf(day_d, "%d", dayInt);
		if (DEBUG)
			printf("\nday_d: %s, ", day_d);
		/**------------------------------------------------------- **/
		/** Step 2: Month**/
		//~ char month_MMMM[MAX_STR] = {""};
		char month_MMMM[MAX_STR] = {0};
		
		/** Type casting from integer to 'Enum-type' with (enum), and storing to variable**/
		//~ enum Months monthEnum = (enum)monthInt;
		enum Months monthEnum = monthInt;
		
		/** Finding string, by leveraging enums + const char * array 
		 * 	   const char * array = { [JAN] = "January", [FEB = "February"]...};**/
		getMonthStr(monthEnum, month_MMMM);
		if (DEBUG)
			printf("month_MMMM: %s, ", month_MMMM);
		/**------------------------------------------------------- **/
		/** Step 3: Year**/
		char year_yyyy[MAX_STR] = {0};
		int fullYearInt = getFullYear(genderInt, yearInt);
		
		/** Formating fullyear from integer to string with sprintf**/
		sprintf(year_yyyy, "%d", fullYearInt);
		if (DEBUG)
			printf("year_yyyy: %s \n", year_yyyy);
		/**------------------------------------------------------- **/
		
		// Tip: avoid declaring in Fn what we want to return
		// !!!Instead Pass by empty array as argument and fill !!
		
		//~ char result[MAX_STR] = {0}; 
		
		/** String-copy first item to empty string. **/
		strcpy(result, day_d);
		
		/** Concatenate**/
		strcat(result, ". ");
		strcat(result, month_MMMM);
		strcat(result, " ");
		strcat(result, year_yyyy); 
		
		if (DEBUG)
			printf("result: %s\n", result);
		
		/** Done: "result" is populated by "d. MMMM yyyy" date-format **/
		if (DEBUG_F)
			printf("\n Successfully ran '%s'\n", __FUNCTION__);
}		


void getMonthStr(enum Months monthEnum, char monthStr[MAX_STR])
{
	const char months[MAX_MONTHS][MAX_STR] = {
							[INVALID] = "Invalid",
							[JAN] = "January",
							[FEB] = "February",
							[MARCH] = "March",
							[APR] = "April",
							[MAY] = "May",
							[JUN] = "June",
							[JUL] = "July",
							[AUG] = "August",
							[SEPT] = "September",
							[OCT] = "October",
							[NOV] = "November",
							[DEC] = "December",
							};

	/** Solution: Populate string with month name in char-array format. **/
	strcpy(monthStr, months[monthEnum]);
	//~ monthStr = months[monthEnum];
		
	if (DEBUG_F)
		printf("\n Successfully ran '%s'\n", __FUNCTION__);

}

int getFullYear(int genderNr, int yearNr)
{
	if (genderNr == MALE1800S || genderNr == FEMALE1800S) {
		return YEAR1800 + yearNr;
		
	} else if (genderNr == MALE1900S || genderNr == FEMALE1900S) {
		return YEAR1900 + yearNr;
		
	} else if (genderNr == MALE2000S || genderNr == FEMALE2000S) {
		return YEAR2000 + yearNr;
		
	} else if (genderNr == MALE2100S || genderNr == FEMALE2100S) {
		return YEAR2100 + yearNr;
		
	} else {
		return YEAR2200 + yearNr;
	}
	
	
	if (DEBUG_F)
		printf("\n Successfully ran '%s'\n", __FUNCTION__);
}



int ReadPersonData(person personDB[MAX_PERSON], int limit, char filename[MAX_STR],
				char nonRecurringCities[MAX_PERSON][MAX_STR],
				int *nonRecurrentCitiesLen) 
{

	/** pointer for file stream (input file streams) **/
	FILE *fInputStream;
    fInputStream = fopen(filename, "r");
    
    /** Check if file stream EMPTY for file "input.txt" **/
	if (fInputStream == NULL)
	{
        printf("Error opening file '%s'\n", filename);
		perror("");		// error checking ("permissions denied")
		fprintf(stderr, "Error opening file '%s'\n", filename); 
	}
	if (DEBUG)
		printf("\n Successfully ran '%s'\n", __FUNCTION__);
	/** Section 3: Read file **/
	int personCnt = 0;
	int cnt = 0;

	while (fscanf(fInputStream, "%s %s %s %s",
									personDB[personCnt].idCode,
									personDB[personCnt].firstName,
									personDB[personCnt].lastName,
									personDB[personCnt].city) == 4) 
	{
		if (DEBUG)
			printf("DEBUG: Got (%d): %s %s %s %s \n",
									personCnt,
									personDB[personCnt].idCode,
									personDB[personCnt].firstName,
									personDB[personCnt].lastName,
									personDB[personCnt].city);
	
		/** Format idCode to Date (d. MMMM yyyy):
		 * 				  961112 -> 12. November 1996 **/
		FormatIdCodeToBirthDate(personDB[personCnt].idCode,
								personDB[personCnt].dateOfBirth);
								
		/** Lowering all letters a string ('keHrA' => 'kehra')**/
		StringToLowercase(personDB[personCnt].city, personDB[personCnt].lowercaseCity);
		
		/** Capitalising name ('suure-jaani' => 'Suure-Jaani')**/
		CapitalizeLowercasedString(personDB[personCnt].lowercaseCity, 
								personDB[personCnt].capitalizedCity);
		
		if (DEBUG)
			printf("\nLowercase city: %s\n", personDB[personCnt].lowercaseCity);
		


		/** Step 7: Populating array of unique cities with function:  **/
		
		if (IsNonRecurrent(personDB[personCnt].lowercaseCity,
										nonRecurringCities, cnt))
		{

			strcpy(nonRecurringCities[cnt], personDB[personCnt].lowercaseCity);
			cnt++;
		}
							
		if (personCnt >= limit)
		{
			fprintf(stderr, "ERROR! Input file is too long. "
			"Allowed limit is %d entries. We read [0-%d] entries. "
			"\nReading of the file has stopped, "
			"continuing with a partial dataset.\n", limit, personCnt);		
			break;
		}
		personCnt++; // DO NOT FORGET
	}
	
	/** Fn has return value. By next line we store "cnt" to memory location. **/
	*nonRecurrentCitiesLen = cnt;
	
	
	/** Closing file-stream **/
	fclose(fInputStream);
	
	if (DEBUG_F)
		printf("\n Successfully ran '%s'\n", __FUNCTION__);
	
	return personCnt;
}


void BubbleSortStrings(char array[MAX_PERSON][MAX_STR], int len)
{
	char temp[MAX_STR] = {0};
	int booleanTag = ALREADY_SORTED;
	
	int i, j;
	int comparison_cnt = 0;
	int swapCount = 0;
	
	for (i = 0; i < (len - 1); i++)
	{
		/** Reset boolean for outer loop to find triggers inside
		 * the inner loop
		 * so that we know we are allowed skip outer-loop.**/
		booleanTag = ALREADY_SORTED; //~ booleanTag = 0; // without macro
		for (j = 0; j < ((len - 1) - i); j++)
		{
			/** Swapping elements inside the array inside the inner-loop**/
			if (strcmp(array[j], array[j + 1]) > 0)
			{
				strcpy(temp, array[j]);
				strcpy(array[j], array[j + 1]);
				strcpy(array[j + 1], temp);
				
				booleanTag = NOT_ALREADY_SORTED;
				/** Counting whenever we swap the numbers in inner-array**/
				swapCount++;
			}
			
			/** Counting all comparisons. Means all iterations, regardless if swapping
			 * (NB! not same as nr. of swaps. **/
			comparison_cnt++;
		}

		/** Checking boolean value, breaking if sorted **/
		
		if (booleanTag == ALREADY_SORTED)  //~ (booleanTag == 0) // without macro
		{
			break;	/** Breaking out of outer-loop because current inner-loop showed we have final order!**/
		}
	}
	if (DEBUG)
	{
		printf("\nComparison made during sorting: %d", comparison_cnt);
		printf("\nSwaps made during sorting: %d", swapCount);
	}

	if (DEBUG_F)
		printf("\n Successfully ran '%s'\n", __FUNCTION__);
}


void PrintArray(char nonRecurringCities[MAX_PERSON][MAX_STR], int nonRecurrentCitiesLen)
{
	for (int i = 0; i < nonRecurrentCitiesLen; i++)
	{
		printf("\n City: %s, i: %d, len: %d \n", nonRecurringCities[i], i, nonRecurrentCitiesLen);
	}

	if (DEBUG_F)
		printf("\n Successfully ran '%s'\n", __FUNCTION__);
}

/** Description:    Format string characted to lower case
 * 
 *  Parameters:     string to be formatted to lower case
 *                  resulting string     
 * 
 *  Result:         void; populating char-array consisting lowercased letters.
 **/

void StringToLowercase(char str[MAX_STR], char lowercasedStr[MAX_STR])
{
	
	int len = strlen(str);
	
	for (int i = 0; i <= len; i++)
	{	
		if (i == len)
		{
			lowercasedStr[i] = '\0';
		}
		
		lowercasedStr[i] = (char)tolower(str[i]);    
		//~ if (DEBUG)	
		//~ printf("* i: %d,  char: %c\n", i, lowercasedStr[i]);
	}
	//~ if (DEBUG)
		//~ printf("\n%s\n", lowercasedStr);

	if (DEBUG_F)
		printf("\n Successfully ran '%s'\n", __FUNCTION__);
}

/** Description:    Wrapper function to print Bubble-Sorted array
 * 
 *  Parameters:     array of characters
 * 					len - lenght of the array
 * 
 *  Result:         void: priting to console
 **/
int IsPersonFromCity(char matchingCities[MAX_PERSON][MAX_STR],
					int matchingCitiesLen,
					char personsCityFromStruct[MAX_STR])
{
	
			
	for (int i = 0; i < matchingCitiesLen; i++)
	{
		if (DEBUG)
			printf("\nmatchingCities[i]: %s, personCity: %s\n", matchingCities[i], personsCityFromStruct);
			
		/** compare:  'all' to 'tallinn'**/
		if (strcmp(matchingCities[i], personsCityFromStruct) == 0) 
		{ 
			return MATCH;
		}
	}
	if (DEBUG_F)
		printf("\n Successfully ran '%s'\n", __FUNCTION__);
	
	return NOT_MATCH;
}


int FindAllPersonFromCities(char matchingCities[MAX_PERSON][MAX_STR], 
					int matchingCitiesLen,
					person personDB[MAX_PERSON], int personCount, 
					person personsMatched[MAX_PERSON])
{	
	
	int count = 0;
	for (int i = 0; i < personCount; i++)
	{
		if (DEBUG)
				printf("\npersonDB[%d].lowercaseCity: %s\n", i,
				personDB[i].lowercaseCity);
		
		if (IsPersonFromCity(matchingCities, matchingCitiesLen,
								personDB[i].lowercaseCity))
		{
			
			personsMatched[count] = personDB[i];
			
			if (DEBUG)
				printf("\npersonsMatched[%d]: %s\n", count, 
								personsMatched[count].lowercaseCity);

			count++;
		}
	}
	if (DEBUG_F)
		printf("\n Successfully ran '%s'\n", __FUNCTION__);
	
	return count;
}


/** Description:    Finding if user-input (example: aLL -> all) matches to any cities
 * 
 *  Parameters:     array of non-reoccuring cities (city is char array)
 * 					len of cities array 
 * 					substring (user input)
 * 					matchingCities-array to be populated
 * 
 *  Result:         int: the lenght of array consisting matched cities.
 **/
int FindAllMatchingCities(char nonRecurringCities[MAX_PERSON][MAX_STR],
						int nonRecurrentCitiesLen, char substring[MAX_STR],
						char matchingCities[MAX_PERSON][MAX_STR])

{
	int count = 0;
	for (int i = 0; i < nonRecurrentCitiesLen; i++)
	{
		if (IsInputInPhrase(nonRecurringCities[i], substring))
		{

			strcpy(matchingCities[count], nonRecurringCities[i]);
			
			if (DEBUG)
				printf("\nmatchingCities[%d]: %s ", count, matchingCities[count]);
			
			count++;
		}
	}
	if (DEBUG_F)
		printf("\n Successfully ran '%s'\n", __FUNCTION__);
		
	return count;
}

/** Description:    Printing information about person-struct
 * 
 *  Parameters:     person struct
 * 					count/index from struct-array
 * 
 *  Result:         void: printing.
 **/
void PrintPersonData(person personDB[MAX_PERSON], int personCount)
{
	printf("%s, %s \nCity: %s\nDate of birth: %s\n", 
										personDB[personCount].lastName,
										personDB[personCount].firstName,
										personDB[personCount].capitalizedCity,
										personDB[personCount].dateOfBirth);

	if (DEBUG)
		printf("Person-count: %d\n", personCount);
	
	if (DEBUG_F)
	{
		
		printf("\n Successfully ran '%s'\n", __FUNCTION__);
	}
}

int IsNonRecurrent(char personsCity[MAX_STR],
					char nonRecurringCities[MAX_PERSON][MAX_STR], int len)
{
	int booleanTag = 0;	// Initializing as 0, (as opposed to IS_'RECURRENT' 1
	
	for (int i = 0; i < len; i++)
	{
		if (strcmp(nonRecurringCities[i], personsCity) == 0) 
		{
			return IS_RECURRENT;
		}
	}
	
	if (DEBUG_F)
		printf("\n Successfully ran '%s'\n", __FUNCTION__);
		
	return IS_NON_RECURRENT;
}	
/** Description:    Copy string into an array of strings.
 * 
 *  Parameters:     string to be pushed into array
 *                  len - how many times to iterate      
 * 
 *  Result:         void; populating char-array
 **/
int ReadStrIntoArray(char string[MAX_STR], char array[MAX_PERSON][MAX_STR], int len)
{
	int i = 0;
	for (i = 0; i < len; i++)
	{
		strcpy(array[i], string); 
	}
	return i;

	if (DEBUG_F)
		printf("\n Successfully ran '%s'\n", __FUNCTION__);
}


void ReadStrIntoArrayByIndex(char string[MAX_STR],
							char array[MAX_PERSON][MAX_STR], int index)
{
	strcpy(array[index], string);
}

/** Description: Capitalize the first letter of a string (city name)
 * 
 *  Parameters:  String buffer, string (city name) to be capitalized   
 * 
 *  Result:  example: suure-kambja -> Suure-Kambja
 **/

void CapitalizeLowercasedString(char str[MAX_STR], 
								char capitalizedCity[MAX_STR])
{
	int len = strlen(str);
	
	/** Must copy the lowercase string to new string we will edit**/
	strcpy(capitalizedCity, str);
	
	/** Loop to capitalize letters --> 1st letter, also letter after '-'(hyphen)**/
	for (int i = 0; i < len; i++)
	{
		/** Only capitalize first letter (and after hyphen "Suure-Kambja") **/
		if ((i == 0) || (i != 0 && str[i-1] == '-'))
		{
			char letter = str[i];
			capitalizedCity[i] = (char)toupper(letter);

		}
	}
	
	if (DEBUG_F)
	{
		printf("\ncapitalised city: %s", capitalizedCity);
		printf("\n Successfully ran '%s'\n", __FUNCTION__);
	}
}

/** Description:    Print debugging information about command line arguments
 * 
 *  Parameters:     command line argument count
 *                  command line arguement vector            
 * 
 *  Result:         void; print command line argument count and vector by each char
 **/
void DebugArgs(int argc, char **argv)
{
    int i, j, n;
    printf("Got %d command line arguments\n", argc);
    
    /** Accessing arguments one by one as strings **/
    for (i = 0; i < argc; i++)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    putchar('\n');
    
    /** Accessing arguments, character at a time **/
    for (i = 0; i < argc; i++)
    {
        for (j = 0, n = strlen(argv[i]); j < n; j++)
        {
            printf("%c ", argv[i][j]);
        }
       putchar('\n');
    }

	if (DEBUG_F)
		printf("\n Successfully ran '%s'\n", __FUNCTION__);
}

/** Description: Sort elements in struct via widely known bubble-sort 
 * 
 *  Parameters: Struct of person, length of struct
 * 
 *  Result: return none, rearranged struct collection
 **/

void BubbleSortStruct(person struc[MAX_PERSON], int len)
{
	person temp = {0};
	int booleanTag = ALREADY_SORTED; //~ int booleanTag = 0; // without macro
	int i, j;
	int comparison_cnt = 0;
	int swapCount = 0;
	
	for (i = 0; i < (len - 1); i++)
	{
		/** Reset boolean for outer loop to find triggers inside
		 * the inner loop
		 * so that we know we are allowed skip outer-loop.**/
		booleanTag = ALREADY_SORTED; //~ booleanTag = 0; // without macro
		for (j = 0; j < ((len - 1) - i); j++)
		{
			/** Swapping elements inside the array inside the inner-loop**/
			if (strcmp(struc[j].lastName, struc[j + 1].lastName) > 0)
			{
				temp = struc[j];
				struc[j] = struc[j + 1];
				struc[j + 1] = temp;
				
				booleanTag = NOT_ALREADY_SORTED;
				/** Counting whenever we swap the numbers in inner-array**/
				swapCount++;
					
			}
			
			/** Counting all comparisons. Means all iterations, regardless if swapping
			 * (NB! not same as nr. of swaps. **/
			comparison_cnt++;
		}
		
		/** Checking boolean value, breaking if sorted **/
		
		if (booleanTag == ALREADY_SORTED)  //~ (booleanTag == 0) // without macro
		{
			break;	/** Breaking out of outer-loop because current inner-loop showed we have final order!**/
		}
	}
	if (DEBUG)
	{	printf("\nComparison made during sorting: %d", comparison_cnt);
		printf("\nSwaps made during sorting: %d", swapCount);
		putchar('\n');
		//~ PrintDescendingOrder(array, len);
		//~ putchar('\n');
		//~ PrintAscendingOrder(array, len);
	}


	if (DEBUG_F)
		printf("\n Successfully ran '%s'\n", __FUNCTION__);}

/** Description: Print elements of an array in ascending order  
 * 
 *  Parameters: array, length of array
 * 
 *  Result: (return: none), print array
 **/
void PrintAscendingOrder(char array[MAX_PERSON][MAX_STR], int len)
{
	int i = 0;
	//~ printf("\nAscending order:");
	for (i = 0; i < len; i++)
	{
		putchar('\n');

		char capitalizedStr[MAX_STR] = {0};		
		CapitalizeLowercasedString(array[i], capitalizedStr);
		printf(" %s", capitalizedStr);
	}	
	
	if (DEBUG_F)
		printf("\n Successfully ran '%s'\n", __FUNCTION__);
}

/** Description: Print elements of a struct in ascending order  
 * 
 *  Parameters: struct of person, length of array
 * 
 *  Result: (return: none), print array
**/
void PrintAscendingOrderStruct(person struc[MAX_PERSON], int len)
{
	int i = 0;

	//~ for (i = len-1; i >= 0; i--) // Descending print
	for (i = 0; i < len; i++)		 // Ascending print 
	{
		putchar('\n');

		PrintPersonData(struc, i);
					//~ printf(" %s", struc[i].id ,..., .lastname etc);
	}	
	
	if (DEBUG_F)
		printf("\n Successfully ran '%s'\n", __FUNCTION__);
}

/** Description: Print elements of an array in descending order  
 * 
 *  Parameters: array, length of array
 * 
 *  Result: (return: none), print array
 **/
void PrintDescendingOrder(char array[MAX_PERSON][MAX_STR], int len)
{
	int i = 0;
	printf("\nDescending order:");
	for (i = len-1; i >= 0; i--)
	{
		printf(" %s", array[i]);
		putchar('\n');
	}

	if (DEBUG_F)
		printf("\n Successfully ran '%s'\n", __FUNCTION__);
}

/** Description: Determine if a select phrase is inside a "parent" string.
 * 
 *  Parameters: "Parent" string, and phrase we look inside of "parent" string       
 * 
 *  Result: hardcoded values, 1 for MATCH, 0 for NOT_MATCH     
 **/
int IsInputInPhrase(char str[MAX_STR], char substr[MAX_STR])
{
	if (strstr(str, substr) != NULL)
	{
		return MATCH;
	}
	//~ if (DEBUG)
		//~ printf("\n Successfully ran '%s'\n", __FUNCTION__);
	
	return NOT_MATCH;
}
/** Description: Acquire the length of a string (character array)
 * 
 *  Parameters: The string 
 * 
 *  Result: Numerical value of the length of string given in fn parameter
 **/
int GetLength(char str[MAX_STR])
{
	//~ size_t len = strlen(str);
	int len = strlen(str);
	return len;

	if (DEBUG_F)
		printf("\n Successfully ran '%s'\n", __FUNCTION__);
}
