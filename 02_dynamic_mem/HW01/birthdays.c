
/** 
* File:        birthdays.c 
* Author:      Frank_Christopher_Kirch 
* Created:     23.02.2024 
* Modified:    27.02.2024 
* 

* Description: 
	       Koodilahendus lähenevate sünnipäevade leidmiseks.
	       Kood on mõeldud kasutada käsurea argumendiga, milleks on failinimi.
	       
	       Loeme sisendfailist nimed ja sünnipäevad ()
	       Kirjutame väljundfaili vaid need nimed ja sünnipäevad, kelle sünnipäev 14p jooksul
	       Silumine: Kirjutame lisa-väljundfaili kõik loetud kirjed
*/ 

#include "birthday.h"

int main(int argc, char *argv[MAX_ARG_LEN])
{
	/** Step 0: Print the issued command line parameters.**/

	#ifdef DEBUG
	DebugArgs(argc, argv);
	#endif
	
	/** Step 1: Initialized variables**/
	char cliSuffix[STR_NAME_LEN] = {0};
	
    char inputFile[STR_NAME_LEN] = {0};
    char outputFile[STR_NAME_LEN] = {0};
    
	/** Step 2: Validate program was run with correct CLI arguments**/
	if (argc <= 1)
	{
		Usage();
		exit(EXIT_FAILURE);
	}
	
	else if (argc > ARGS_CNT)
	{
		/** Exit the program with 'fprintf(stderr, "message"); **/
		Usage();
		exit(EXIT_FAILURE);
	}
	
	/** ./birthday --help or ./birthday -h**/
	else if (argc == 2 && IsHelpMode(argv))
    {
		
		RunHelpMode();
		exit(EXIT_SUCCESS); 
    }
    else if (argc == 2) 
	{
		 /** Verifying program mode "./birthday --input=in.txt or -i=in.txt**/
		 GetProgramModeSuffix(argv, cliSuffix, ARGS_POS_1);
		 if (IsDefaultFileInputMode(cliSuffix))
		 {
			GetFilename(argv, cliSuffix, inputFile, ARGS_POS_1);
			
			RunProgram(inputFile, OUTPUT_FILENAME, PROMPT_NOT_DISABLED);
			exit(EXIT_SUCCESS);
		 }	 
	}
	else if (argc == 3)
	{
		 /** -o=output.txt OR -p=disabled **/
		 
		 /** Get "--input" from --input=input.txt**/
		 GetProgramModeSuffix(argv, cliSuffix, ARGS_POS_1);
		 
		 /** ./birthday --input=in.txt --prompt=disabled **/
		 if (IsDefaultFileInputMode(cliSuffix) && IsPromptDisabledMode(argv, ARGS_POS_2))
		 {
			/** Get "input.txt" from --input=input.txt**/
			GetFilename(argv, cliSuffix, inputFile, ARGS_POS_1);

			/** Run mode (without 'printf(outputStream)', default output-filename 'output.txt' **/
			RunProgram(inputFile, OUTPUT_FILENAME, PROMPT_DISABLED);
			
			exit(EXIT_SUCCESS);
		 }
		 /** ./birthday --input=in.txt ... **/
		 else if (IsDefaultFileInputMode(cliSuffix) && !IsPromptDisabledMode(argv, ARGS_POS_2))
		 {
			  /** Get "input.txt" from --input=input.txt**/
			 GetProgramModeSuffix(argv, cliSuffix, ARGS_POS_1);
			 GetFilename(argv, cliSuffix, inputFile, ARGS_POS_1);

			/** Get "--output" from --output=output.txt**/
			 char cliSuffix[STR_NAME_LEN] = {0};
			 
			 GetProgramModeSuffix(argv, cliSuffix, ARGS_POS_2);
				 
			 if (IsOutputFileMode(cliSuffix))
			 {	
				GetFilename(argv, cliSuffix, outputFile, ARGS_POS_2);
				/** Run mode - Write to custom output file and print in terminal **/
				RunProgram(inputFile, outputFile, PROMPT_NOT_DISABLED);
				exit(EXIT_SUCCESS);
			 }
		 }
	}
	else if (argc == 4)
	{
		 /** -o=output.txt AND -p=disabled **/
		 
		 /** Get "--input" from --input=input.txt**/
		 GetProgramModeSuffix(argv, cliSuffix, ARGS_POS_1);
		 
		 if (IsDefaultFileInputMode(cliSuffix) && IsPromptDisabledMode(argv, ARGS_POS_2))
		 {
			 /** Get "input.txt" from --input=input.txt**/
			 GetFilename(argv, cliSuffix, inputFile, ARGS_POS_1);

			/** Get "--output" from --output=output.txt**/
			 char cliSuffix[STR_NAME_LEN] = {0};
			 GetProgramModeSuffix(argv, cliSuffix, ARGS_POS_3);
				 
			 if (IsOutputFileMode(cliSuffix))
			 {	
				 /** Get "--output" from --output=output.txt**/
				 char cliSuffix[STR_NAME_LEN] = {0};
				 GetProgramModeSuffix(argv, cliSuffix, ARGS_POS_3);
				 
				 /** Get "output.txt" from --output=output.txt**/
				 char outputFile[STR_NAME_LEN] = {0};
				 GetFilename(argv, cliSuffix, outputFile, ARGS_POS_3);
				 
				 RunProgram(inputFile, outputFile, PROMPT_DISABLED);
				 exit(EXIT_SUCCESS);
			 }
		}
	}
	/** Consolidated all edge-cases to here. Invalid input.
	 *  Do not call main function "RunProgram()**/
	Usage();
	exit(EXIT_FAILURE);

}
/** Description:   Run program based on given input and output filename.
 * 
 *  Parameters:    input file name 
 * 				   output file name
 * 				   isPromptModeDisabled: boolean.
 * 					*if true, then output to only output file, do not output terminal-prompt
 * 					*if false, print also in terminal prompt (and outputfile)
 *
 *  Result:        void; Running core program functionality
 **/
void RunProgram(char inputFile[STR_NAME_LEN],
									char *outputFile,
									bool isPromptModeDisabled)
{	

	char stdoutStream[MAX_STR_512] = {0};
	
	int size = ParseAllEntriesToStructFromInputFile(inputFile, stdoutStream);	
	
	WriteStdoutToFile(size, stdoutStream, outputFile); 
	
	if (!isPromptModeDisabled)
	{	
		printf("%s", stdoutStream);
		putchar('\n');
		
	}
	printf("Successfully ran the program. Please see the results in the "
		"file '%s'.\n", outputFile);
}


/** Description:   Read file to store values in sturct and substruct
 * 					Aim: Initialize fields, AND bubble-sort structs by mm-dd-yyyy format.
 * 
 *  Parameters:    inputFile: filename to read from
 * 				   stdoutStream: the char-array we store the entire result.
 *
 *  Result:        void; populate stdoutStream in entirety.
 **/
int ParseAllEntriesToStructFromInputFile(char inputFile[STR_NAME_LEN], 
									char stdoutStream[MAX_STR_512])
{
	/** Step 3: Validate user input format (Before reading file!) **/
	int attemptCount = 0;
	int maxAttempts = MAX_ATTEMPTS;
	
	int inputDay, inputMonth, inputYear;
	
	char userInput[DATE_LEN] = {0};
	char *pInput = userInput;
	
	printf("Greetings! This program will read a file <firstname> <dd.mm.yyyy>\n"
	"Each name-birthday pair will on a new line (for example, 'Mary 29.04.2004'). \n"
	"\nThe programm will determine the following information: \n"
	"1. Birthdays for a chosen date \n2. Birthdays in two weeks time\n\n");
	while (1)
	{
		AskInputDate(pInput, MAX_ATTEMPTS);
		
		/** Step 4: Format date **/

		sscanf(pInput, "%2d.%2d.%4d", &inputDay, &inputMonth, &inputYear);
		putchar('\n');
		/** Step 5: Check date validity **/
		if (IsValidDate(inputDay, inputMonth, inputYear))
		{
			#ifdef DEBUG
			printf("\nDEBUG: valid input: %02d.%02d.%04d\n", inputDay, inputMonth, inputYear);
			#endif
			
			break; /** do not forget to break out if suitable date inputted! **/
		}
		attemptCount++; 	/** increment count **/ 
	
		/** Exit program if user has inserted incorrectly enough time. **/
		if (attemptCount >= maxAttempts) 
		{
			fprintf(stderr, "You have entered an invalid date too many times [%d/%d].\n"
							"Exiting program\n", attemptCount, maxAttempts);
			#ifdef DEBUG
			return EXIT_FAILURE;
			#endif
		}
		else 
		{
			printf("You entered an uknown date.\n");
		}
	}
	
	/** Step 5: Modulo daysInMonth **/
	/** if i = 1 on JAN, i = 0 DEC**/
	/** if i = 0, then i-1 = 12**/
	
	/** Step 6: ReadFile**/
	person personDB[MAX_PERSON];
	person *pPerson = personDB;
	
	int personCount = ReadFileToStruct(pPerson, MAX_PERSON, inputFile);
	
	/** Step 7: Check Date Valid **/
	InitializeStructWithValidBirthDate(pPerson, personCount);

	int birthdayCount =  PersonsWithBirthdays(pPerson, personCount, inputDay, inputMonth, inputYear);
	int birthdayIn14daysCnt = PersonsWithBirthdaysInTwoWeeks(pPerson, personCount, inputDay, inputMonth, inputYear);
	
	InitializeFieldForDateSorting(pPerson, personCount);
	BubbleSortStruct(pPerson, personCount);
	
	#ifdef DEBUG
	printf("\nbirtdaycnt: %d. in14Days cnt: %d\n", birthdayCount, birthdayIn14daysCnt);
	#endif
							
	int size = CreateOutputString(stdoutStream, pPerson, personCount, MAX_PERSON,
									birthdayCount, birthdayIn14daysCnt,
									inputDay, inputMonth, inputYear);
	return size;
}

/** Description:   intialize field to bubble-sort structs by mm-dd-yyyy format.
 * 
 *  Parameters:    person struct
 * 				   count of person-structs
 *
 *  Result:        void; initializing "formatForSorting" substruct field
 **/
void InitializeFieldForDateSorting(person *pPerson, int personCount)
{
	for (int i = 0; i < personCount; i++)
	{
		/** Creating mm-dd-yyyy format to sort birthdays by month, then day, then year**/
		if (!((pPerson + i)->dateOfBirth.isValidBirthDate))
		{
			/** Result: 0**/
			strcpy((pPerson + i)->dateOfBirth.formatForSorting, "0");
		}
		else /** else: if ((pPerson + i)->dateOfBirth.isValidBirthDate))**/
		{
					
			sprintf((pPerson + i)->dateOfBirth.formatForSorting, "%02d-%02d-%04d",
											(pPerson + i)->dateOfBirth.month,
											(pPerson + i)->dateOfBirth.day,							
											(pPerson + i)->dateOfBirth.year);
			
			
			#ifdef DEBUG
			printf("DEBUG [%d/%d]: %s's dateStr: %s -> format manupulation: %s\n",
												i, personCount,
												(pPerson + i)->firstName,
												(pPerson + i)->dateOfBirth.dateStr,
												(pPerson + i)->dateOfBirth.formatForSorting);
			#endif							
		}
	}
}
/** Description:   intialize valid substruct fields, if valid.
 * 						else zero-initialize.
 * 
 * 				   Aim: to avoid outputting when there is no birthday.
 * 
 *  Parameters:    person struct
 * 				   count of person-structs
 *
 *  Result:        void; initializing struct fields
 **/
void InitializeStructWithValidBirthDate(person *pPerson, int personCount)
{
	for (int i = 0; i < personCount; i++)
	{
		int tempDay, tempMonth, tempYear; 
		
		/** Sscanf scannes 2 integer-string until meets ".", etc. **/
		sscanf((pPerson + i)->dateOfBirth.dateStr, "%2d.%2d.%4d",
										&tempDay, &tempMonth, &tempYear);
											
		#ifdef DEBUG
		printf("DEBUG [%d/%d]: %s's birthdate raw: %02d.%02d.%04d\n",
											i, personCount,
											(pPerson + i)->firstName,
											tempDay, tempMonth, tempYear);
		#endif		
		
		if (!IsValidDate(tempDay, tempMonth, tempYear))
		{
			/** Comment: Reset each invalid sub-struct's "dateOfBirth" field values!
			 * 	Explained: avoid using invalid date-formats in program. **/
			ZeroInitializeBooleansAndIntegers(pPerson + i);

			#ifdef DEBUG
			printf("DEBUG [%d/%d]: %s's birthdate zero-ed out: %02d.%02d.%04d\n",
									i, personCount,
									(pPerson + i)->firstName,
									(pPerson + i)->dateOfBirth.day,
									(pPerson + i)->dateOfBirth.month, 
									(pPerson + i)->dateOfBirth.year);
			putchar('\n');
			#endif
			continue;
		}
		else
		{
			/** Correct dates ---> Populate sub-structure **/
			(pPerson + i)->dateOfBirth.day = tempDay;
			(pPerson + i)->dateOfBirth.month = tempMonth;
			(pPerson + i)->dateOfBirth.year = tempYear;
			(pPerson + i)->dateOfBirth.isValidBirthDate = true;
		}
	}
}


/** Description:   Count persons with birthday on user chosen date.
 * 					 and intialize "isBirthday" struct field
 * 
 * 				   Aim: to avoid outputting when there is no birthday.
 * 
 *  Parameters:    person struct
 * 				   day user chose
 * 				   month user chose
 * 				   year user chose
 *
 *  Result:        count of persons with birthdays on chosen date.
 **/

int PersonsWithBirthdaysInTwoWeeks(person *pPerson, int personCount, int inputDay, int inputMonth, int inputYear)
{
	int birthdayIn14daysCnt = 0;
	for (int i = 0; i < personCount; i++)
	{
		if ((pPerson + i)->dateOfBirth.isValidBirthDate)
		{

			if (IsBirthdayInTwoWeeks((pPerson + i), inputDay, inputMonth, inputYear))
			{
				(pPerson + i)->dateOfBirth.isBirthDayInTwoWeeks = true;
				birthdayIn14daysCnt++;
				
				#ifdef DEBUG
				printf("BIRTHDAY IN TWO WEEKS! [%d/%d]: %s's will be set true and incremented! Date: %02d.%02d.%04d\n",
								i, personCount,
								(pPerson + i)->firstName,
								(pPerson + i)->dateOfBirth.day,
								(pPerson + i)->dateOfBirth.month, 
								(pPerson + i)->dateOfBirth.year);
				putchar('\n');
				#endif
			}
			else
			{
				(pPerson + i)->dateOfBirth.isBirthDayInTwoWeeks = false;
			}
		}
	}
	return birthdayIn14daysCnt;
}

/** Description:   Sort the array-struct by .firstName field. Must use: pointer arithmetics 
 * 
 *  Parameters:    *pStr - pointer to array-struct
 * 					len	 - length of  of elements in struct-array
 * 
 *  Result:         (void) ----> Re-assembled the structure by pointers. 
 **/

void BubbleSortStruct(person *pStr, int len)
{
	person temp;
	 
	int booleanTag = ALREADY_SORTED;
	int i, j;
	int comparison_cnt = 0;
	int swapCount = 0;
	
	for (i = 0; i < (len - 1); i++)
	{
		/** Reset boolean for outer loop to find triggers inside
		 * the inner loop
		 * so that we know we are allowed skip outer-loop.**/
		booleanTag = ALREADY_SORTED; 
		for (j = 0; j < ((len - 1) - i); j++)
		{
			/** Swapping elements inside the array inside the inner-loop**/
	
			if (strcmp((pStr + j)->dateOfBirth.formatForSorting,
					(pStr + j + 1)->dateOfBirth.formatForSorting) > 0)
			{
				temp = *(pStr + j);
				*(pStr + j) = *(pStr + j + 1);
				*(pStr + j + 1) = temp;
				

				booleanTag = NOT_ALREADY_SORTED;
				/** Counting whenever we swap the numbers in inner-array**/
				swapCount++;
					
			}
			
			/** Counting all comparisons. Means all iterations, regardless if swapping
			 * (NB! not same as nr. of swaps. **/
			comparison_cnt++;
		}
		
		/** Checking boolean value, breaking if sorted **/
		
		if (booleanTag == ALREADY_SORTED)
		{
			break;	/** Breaking out of outer-loop because current inner-loop showed we have final order!**/
		}
	}
	#ifdef DEBUG
	printf("\nComparison made during sorting: %d", comparison_cnt);
	printf("\nSwaps made during sorting: %d", swapCount);
	putchar('\n');
	#endif
}
	
	
/** Description:   Count persons with birthday in 14 days
 * 					 and intialize "isBirthdayInTwoWeeks" struct field
 * 
 * 				   Aim: to avoid outputting when there is no birthday soon.
 * 
 *  Parameters:    person struct
 * 				   day user chose
 * 				   month user chose
 * 				   year user chose 
 *
 *  Result:        count of persons with birthday in 14 days
 **/
int PersonsWithBirthdays(person *pPerson, int personCount, int inputDay, int inputMonth, int inputYear)
{
	int birthdayCount = 0;
	for (int i = 0; i < personCount; i++)
	{
		if ((pPerson + i)->dateOfBirth.isValidBirthDate) /** else "continue" **/
		{
			if (!isBirthday((pPerson + i), inputDay, inputMonth, inputYear))
			{
				(pPerson + i)->dateOfBirth.isBirthDay = false;
			}
			else
			{
				(pPerson + i)->dateOfBirth.isBirthDay = true;
				birthdayCount++;
				
				#ifdef DEBUG
				printf("BIRTHDAY! [%d/%d]: %s's will be set true and incremented! Date: %02d.%02d.%04d\n",
								i, personCount,
								(pPerson + i)->firstName,
								(pPerson + i)->dateOfBirth.day,
								(pPerson + i)->dateOfBirth.month, 
								(pPerson + i)->dateOfBirth.year);
				putchar('\n');
				#endif
			}
		}
	}
	return birthdayCount;
}
/** Description:   Zero-intialiaze structure fields with 0s, 
 * 				   to avoid misuse with file-read person's birthdate 
 * 
 *  Parameters:    person struct
 *
 *  Result:        void (rewriting struct "person" fields) 
 **/
void ZeroInitializeBooleansAndIntegers(person *pPerson)
{
/** Filter out unknown dates to avoid incorrect output File creation**/

	/** Reset values due to incorrect date issued. **/
	strcpy(pPerson->dateOfBirth.dateStr, "");
	pPerson->dateOfBirth.day = 0;
	pPerson->dateOfBirth.month = 0;
	pPerson->dateOfBirth.year = 0;
	
	pPerson->dateOfBirth.isValidBirthDate = false;
	pPerson->dateOfBirth.isBirthDayInTwoWeeks = false;
	pPerson->dateOfBirth.isBirthDay = false;

}

/** Description:   Check whether user-inputted date is matching with person's birthdate 
 * 
 *  Parameters:    person struct
 * 				   user inputted day
 * 				   user inputted month
 * 				   user inputted year
 *
 *  Result:        boolean: true or false. 
 **/


bool isBirthday(person *pPerson, int inputDay, int inputMonth, int inputYear)
{
	return (pPerson->dateOfBirth.day == inputDay &&
			pPerson->dateOfBirth.month == inputMonth &&
			pPerson->dateOfBirth.year <= inputYear);
}

/** Description:  Calculate +14 days to see who will have birthday soon
*  
* Parameters:     
*  				  inputMonth - user's selected month, parsed from entire input
*                 inputDay	 - user's selected day               
*                 inputYear	 - user's selected year                           
* 				  pPerson 	  - pointer to one person-struct. 
* 
* Return:         true for leap year, false for normal year. /
*/ 	

bool IsBirthdayInTwoWeeks(person *pPerson, int inputDay, int inputMonth, int inputYear)
{
	int maxDaysInMonth = GetDaysInMonth(inputMonth, inputYear);
	
	#ifdef DEBUG
	printf("input: %d. structy: %d \n", inputYear, pPerson->dateOfBirth.year);
	#endif
	
	/** Modular arithmetic to avoid moving from Dec to Jan and going to 13th month.
	 * 		Tip: overwrite to 0 for following operations. 
			
			Formula: "a mod n" (a is in range of circular set of Integers [0, 1... n-1]
	 * **/
	bool isYearChange = false;
	if ((inputMonth + 1) % MONTHS_12 == 0)
	{
		inputMonth = JAN - 1; /** offset this by -1 for next if statement**/
		isYearChange = true;
	}
	
	/** If birthday in range of [0-13], i.e less than 14 days of a month  **/
	/** This "if-block" explained:
	 * 		Let's say today 24.12 and Mari's birthday 07.01.
	 * 			OR let's say today is 28.01 and Tom's birthday is 04.01**/
	if (inputDay + 14 > maxDaysInMonth && pPerson->dateOfBirth.month == inputMonth + 1)
	{

		/** Rewrite DEC to JAN. And also 2001 Dec rewrite to 2002 Jan**/
		if (isYearChange)
		{
			inputMonth = JAN; // REMOVE?
			inputYear += 1;
			
			#ifdef DEBUG
			printf("input: %d. structy: %d \n", inputYear, pPerson->dateOfBirth.year);
			#endif
		}
		
		int remainder = maxDaysInMonth - inputDay;
		int Day14fromInput = 14 - remainder;
		 /** NB: "remainder" example:   selected 28Dec, then DEC_MAX - 28DEC = 3. 
		  * 	Thus, 14 - remainder (3) = 11
		  * 		Now use 11 + 0 = 11. **/
		  
		  		 /** Example: birthday: 7th Jan 
		  		  *  7 th Jan < 11th Jan (last day of "next 14-days" timeframe)
		  * 		 ----> success, will have birthday in 14days or less **/
		 #ifdef DEBUG
		 printf("%s's date - %02d.%02d.%04d <==> input+14days : %02d.%02d.%04d\n", pPerson->firstName,
		  pPerson->dateOfBirth.day, pPerson->dateOfBirth.month, pPerson->dateOfBirth.year, Day14fromInput, inputMonth, inputYear);		
		 #endif
		 
		 /** Comment: Calculate age for stdout stream 
		  * 				(using -> age in Fn 'CreateOutputString()'**/
		 pPerson->age = inputYear - pPerson->dateOfBirth.year;
		 
		/** main return statement **/
		 return inputYear > pPerson->dateOfBirth.year && pPerson->dateOfBirth.day <=  Day14fromInput;
	} 

	
	/** If birthday in range of [14-...]**/
	else if (pPerson->dateOfBirth.month == inputMonth &&
						((pPerson->dateOfBirth.day - 14) <= inputDay) &&
							inputYear > pPerson->dateOfBirth.year)
	{
		int Day14fromInput = (pPerson->dateOfBirth.day) - 14;
		 #ifdef DEBUG
		 printf("%s's date - %02d.%02d.%04d <==> input+14days : %02d.%02d.%04d\n", pPerson->firstName,	
		 pPerson->dateOfBirth.day, pPerson->dateOfBirth.month, pPerson->dateOfBirth.year, Day14fromInput, inputMonth, inputYear);		
		 #endif
		 
		/** Comment: Calculate age for stdout stream 
		* 				(using -> age in Fn 'CreateOutputString()'**/
		pPerson->age = inputYear - pPerson->dateOfBirth.year;
		
		/** main return statement **/
		return (inputDay >= Day14fromInput && inputDay < pPerson->dateOfBirth.day);
	}
	else
	{
		/** Comment: Calculate age for stdout stream 
		* 				(using -> age in Fn 'CreateOutputString()'**/
		pPerson->age = inputYear - pPerson->dateOfBirth.year;
		
		/** main return statement **/
		return false;
	}
}
 
 
/** Description:    Checks wheather the passed year is a leap year. 
*  
* Parameters:    Year - year number.
*  
* Return:         true for leap year, false for normal year. 
*/ 

bool IsLeapYear(int year) 
{ 
	return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0); 
} 

/** Description:    Function finds and returns the number of days in a month. 
*                 Month is given as an integer, starting from 1 (january). 
*                 Function handles leap years. 
*  
* Parameters:     month - month number. Month nr starting from 1. 
*                 year - year number.
*  
* Return:         For valid dates, returns the number of days in a month.  
*                 For invalid dates, returns 0. 
*  
*/ 
int GetDaysInMonthEnum(int month, int year)			
{
	int daysInMonth[MONTHS_12] = {
							[INVALID_MONTH_0] = 0,
							[JAN] = 31,
							[FEB] = 28,
							[MARCH] = 31,
							[APR] = 30,
							[MAY] = 31,
							[JUN] = 30,
							[JUL] = 31,
							[AUG] = 31,
							[SEPT] = 30,
							[OCT] = 31,
							[NOV] = 30,
							[DEC] = 31,
							};
							
	if (month > MAX_MONTH || month < MIN_MONTH) 
    { 
		return 0; 
	}  
							
	if (month == FEB && IsLeapYear(year))
	{
		return 29;
	}	
	return daysInMonth[month];
}

 
/** Description:    Function finds and returns the number of days in a month. 
*                 Month is given as an integer, starting from 1 (january). 
*                 Function handles leap years. 
*  
* Parameters:     month - month number. Month nr starting from 1. 
*                 year - year number.
*  
* Return:         For valid dates, returns the number of days in a month.  
*                 For invalid dates, returns 0. 
*  
*/ 
int GetDaysInMonth(int month, int year) 
{ 
	
	/** Using pointer referencing integers. month notation == dereferencing **/
    if (month > MAX_MONTH || month < MIN_MONTH) 
    { 
		return 0; 
	}  
	else  
	{ 
		/** Jan, March, May, July, Aug., Oct and Dec have 31 days. **/ 
		if (month == 1 || month == 3 || month == 5 || 
			month == 7 || month == 8 || month == 10 || month == 12) 
			return 31; 
		/** April, June, September and November have 30 days **/ 

		else if (month == 4 || month == 6 || 
				month == 9 || month == 11) 
			return 30; 

		/** February on leap year **/  
		if (month == 2 && IsLeapYear(year)) 
			return 29; 

		/** February on NOT leap year**/ 
		else if (month == 2 && !(IsLeapYear(year))) 
			return 28; 
	} 
	return 0; 
} 

/** 

* Description:    Function finds if the date passed is valid or not. 
*  
* Parameters:     day - the day value. 
*                 month - month number starting from 1. 
*                 year - the year of the date 
*  
* Return:         For valid dates, returns DATE_VALID (1), 
*                 For invalid dates, returns DATE_INVALID (0). 
*/ 

bool IsValidDate(int day, int month, int year) 
{ 
    if (year < YEAR_MIN || year >= YEAR_MAX) 
    { 
		return false; 
	} 

	if (GetDaysInMonth(month, year) == 0 
	|| day > GetDaysInMonth(month, year) 
	|| day <= 0) 
	{ 
		return false;  
	}
	return true; 
	 
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
}


/** 
* Description:    Reads user input if correct format. 
*  
* Parameters:     pInput: pointer to input to store the value
* 				  maxAttempts: how much times user can insert invalid until program exits
*  
* Return:         (void). Populating char-array with correctly formatted input.
**/ 

void AskInputDate(char *pInput, int maxAttempts)
{ 
	int attemptCount = 0; 
	printf("Please insert a date in format 'dd.mm.yyyy' "
	       "(example  31.12.2001) \nEnter the date here: ");
	       
	while (1) 
	{ 
	/** Scan input into variable: Input format is dd.mmy.yyy (i.e 10.11.2011) **/
		scanf("%s", pInput); 
		
		
		/** if inputs ends or input contains invalid symbols, we stop reading **/
		if (IsCorrectInputFormat(pInput, DATE_LEN)) 
		{ 
			break; 
		}
		attemptCount++; 	/** increment count **/ 
	
		/** Exit program if user has inserted incorrectly enough time. **/
		if (attemptCount >= maxAttempts) 
		{
			putchar('\n');
			fprintf(stderr, "You have entered incorrectly %d times.\n"
							"Exiting program.\n", attemptCount);
			exit(EXIT_FAILURE);
		}
		else 
		{
			putchar('\n');
			printf("You entered the date incorrectly. \n Please enter a date: ");
		}
	} 
} 

/** 
* Description:    Verifies user input is of format 'dd.mm.yyyy' 
*  
* Parameters:     dateInput - char-array of user input
*                 limit - the maxiumum allowed length of user-input

* Return:         true (IS_CORRECT) or false (NOT_CORRECT)
*/ 

bool IsCorrectInputFormat(char str[DATE_LEN], int limit)
{
	
	/** input must be of fix length**/
	int len = strlen(str);
	
	if (len >= limit) /** limit == FORMAT_LEN (11)**/ 
	{
		return false;
	}
	
	for (int i = 0; i < len; i++)
	{
		#ifdef DEBUG
		printf("i: %d, c:%c \n", i, str[i]);
		#endif
		
		/** each char must be number (excluding "dots" ==> 01.01.2001**/
		if ((i == DAY_DOT_INDEX || i == MONTH_DOT_INDEX) && (str[i] != '.')) 
		{
			return false;
		}
		
		else if ((i != DAY_DOT_INDEX && i != MONTH_DOT_INDEX) && !isdigit(str[i]))
		{
			return false;
		}
	}
	return true;
}

/** Description:    Read the contents of a file (up to a limit of lines from file)
 * 
 *  Parameters:     1. pointer to struct-array     
 * 					2. limit of lines we read from file (after we break)
 * 					3. filename we read
 * 
 *  Result:         return count of file-lines read.
 **/

int ReadFileToStruct(person *pStr, int limit, char *filename) 
{

	/** pointer for file stream (input file streams) **/
	FILE *fInputStream;
    fInputStream = fopen(filename, "r");
    
    /** Check if file stream EMPTY for file "input.txt" **/
	if (fInputStream == NULL)
	{
		perror("");		/** error checking ("permissions denied") **/
		fprintf(stderr, "Error opening file '%s'\n", filename); 
	}
	
	
	/** Section 3: Read file **/
	int cnt = 0;

	while (fscanf(fInputStream, "%s %s",
									(pStr + cnt)->firstName,
									(pStr + cnt)->dateOfBirth.dateStr) == 2) 
	{


		#ifdef DEBUG
		printf("DEBUG: Got (%d): %s %s \n",
									cnt,
									(pStr + cnt)->firstName,
									(pStr + cnt)->dateOfBirth.dateStr);
		#endif 
		
		cnt++; /** Do not forget**/
		
		if (cnt >= limit)
		{
			fprintf(stderr, "ERROR! Input file is too long. "
			"Allowed limit is %d entries. We read [0-%d] entries. "
			"\nReading of the file has stopped, "
			"continuing with a partial dataset.\n", limit, cnt);
			return cnt;
		}
	}
	
	/** Closing file-stream **/
	fclose(fInputStream);
	
	#ifdef DEBUG
	printf("\n Successfully ran '%s'\n", __FUNCTION__);
	#endif
	
	return cnt;
}




/** Description:   Write results into file. Only persons with birthday or in 2 weeks 
 * 
 *  Parameters:    person structure,
 * 				   total nr people read from file
 * 			       limit of writing to file, to avoid excessive entries
 * 				   output files name
 * 				   total nr of people with matching birthdays to user input
 * 				   total nr of people with birthday in 2 weeks. 
 * 
 *  Result:	       void (write to file results).         
 **/
void WriteToFile(person *pPerson, int personCount, int limit, 
								char *filename, int cntBirthdayPeople,
								 int cntBirthdayInTwoWeeksPeople,
								 int inputDay, int inputMonth, int inputYear) 
{



	int iterBirthday14days = 0;
	int iterBirthdayNow = 0;
	/** pointer for file stream (input file streams) **/
	FILE *fOutputStream;
    fOutputStream = fopen(filename, "w");
    
    /** Check if file stream EMPTY for file "input.txt" **/
	if (fOutputStream == NULL)
	{
		perror("");		/** error checking ("permissions denied") **/
		fprintf(stderr, "Error opening file '%s'\n", filename); 
	}

	/** Step 1b. Create line char-line of respective length ('-' * i)**/
	
	char headerBirthdayInTwoWeeks[MAX_STR] = "Reminder: Upcoming birthdays in 14 days: ";
	fprintf(fOutputStream, "%s", headerBirthdayInTwoWeeks);
	
	
	/** Section 2. Writing about birthdays nearing in 2 weeks (14 days)!**/
	if (cntBirthdayInTwoWeeksPeople <= 0)
	{	
		fprintf(fOutputStream, "%d people\n", cntBirthdayInTwoWeeksPeople);	
	}
	else
	{
		/** Outputting total of birthdays. Afterwhich, linebreak for "---" **/
		fprintf(fOutputStream, "%d people. \n", cntBirthdayInTwoWeeksPeople);
		
		/** Create "---------" linebreak into output**/
		char separatingLn[MAX_STR] = {0};
		char *pSeparatingLn = separatingLn;
		CreateSeparatingPrintLn(headerBirthdayInTwoWeeks, BUFFER, pSeparatingLn); 
		
		fprintf(fOutputStream, "%s\n", separatingLn);
		
		for (int i = 0; i < personCount; i++)
		{
			if ((pPerson + i)->dateOfBirth.isBirthDayInTwoWeeks)
			{
				iterBirthday14days++;
				fprintf(fOutputStream, "[%d/%d] %s celebrates their birthday on %02d.%02d.%04d.\n",
										iterBirthday14days, cntBirthdayInTwoWeeksPeople,
										(pPerson + i)->firstName,
										(pPerson + i)->dateOfBirth.day,
										(pPerson + i)->dateOfBirth.month,
										(pPerson + i)->dateOfBirth.year);	
			}
		}
	}
	putchar('\n');
	/** Section 2. Writing about birthdays matching to user-input. Write to file!**/
	if (cntBirthdayPeople <= 0)
	{		

		char headerNoBirthday[MAX_STR] = "No birthdays found for this date ";
		fprintf(fOutputStream, "\n\n%s\n", headerNoBirthday);
		
		/** Create "---------" linebreak into output**/
		char separatingLn[MAX_STR] = {0};
		char *pSeparatingLn = separatingLn;
		CreateSeparatingPrintLn(headerNoBirthday, BUFFER, pSeparatingLn); 
	 
		fprintf(fOutputStream, "%s\n", separatingLn);				
	}
	else
	{
		fprintf(fOutputStream, "\n\nCongratulations, %d birthday(s) for this selected date '%02d.%02d.%04d'. \n",
							cntBirthdayPeople, inputDay, inputMonth, inputYear);
		
		char headerBirthdays[MAX_STR] = "\nCongratulations, XX birthday(s) for this selected date 'dd.mm.yyyy'.";
		
		char separatingLn[MAX_STR] = {0};
		char *pSeparatingLn = separatingLn;
		CreateSeparatingPrintLn(headerBirthdays, ZERO, pSeparatingLn); 
	 
		fprintf(fOutputStream, "%s\n", separatingLn);
		
		/** Step 1b. Create line char-line of respective length ('-' * i)**/
		
		
		for (int i = 0; i < personCount; i++)
		{
			if ((pPerson + i)->dateOfBirth.isBirthDay)
			{
				iterBirthdayNow++;
				fprintf(fOutputStream, "[%d/%d] %s celebrates their birthday on this date! %s is born on %02d.%02d.%04d.\n",
										iterBirthdayNow, cntBirthdayPeople,
										(pPerson + i)->firstName,
										(pPerson + i)->firstName,
										(pPerson + i)->dateOfBirth.day,
										(pPerson + i)->dateOfBirth.month,
										(pPerson + i)->dateOfBirth.year);
			}	
		}
	}
	/** Closing file-stream **/
	fclose(fOutputStream);
	
	#ifdef DEBUG
	printf("\n Successfully ran '%s'\n", __FUNCTION__);
	#endif
}	
/** Description: Calculate separating line length and fill the string-variable
 * 
 *  Parameters:     1. string (char array): headerline. Aim: separatingLn
 * 									will reside below this headerline.
 * 									thus we need the length of headerline.
 * 
 * 					2. int: buffer. Any whitespace (or such) added to lenght
 * 
 * 					3. string (char array): separatingLine: 	char-array of ---- we calculate.
 * 
 *  Result:   void. Fill char-array with '-' 
 **/
void CreateSeparatingPrintLn(char headerLine[MAX_STR], int buffer, char *pSeparatingLine)
{
	int len = strlen(headerLine);
	for (int i = 0; i < len + buffer; i++)
	{
		*(pSeparatingLine + i) = '-';
	}
}


/** Description:   Create stdoutput for terminal or output-file.
 * 					the resulting output contains:
 * 						Only persons with birthday or in 2 weeks 
 * 
 *  Parameters:    "stdoutStream": a char-array of output 
 * 				   person structure,
 * 				   total nr people read from file
 * 			       limit of writing to file, to avoid excessive entries
 * 				   output files name
 * 				   total nr of people with matching birthdays to user input
 * 				   total nr of people with birthday in 2 weeks. 
 * 
 *  Result:	       int: size of entire "stdoutStream".         
 **/
int CreateOutputString(char stdoutStream[MAX_STR_512], person *pPerson, 
								 int personCount, int limit,
								 int cntBirthdayPeople,
								 int cntBirthdayInTwoWeeksPeople,
								 int inputDay, int inputMonth, int inputYear) 
{
	char separatingLn[MAX_STR] = {0};
	int iterBirthday14days = 0;
	int iterBirthdayNow = 0;
	/** pointer for file stream (input file streams) **/
	
	/** Step 1b. Create line char-line of respective length ('-' * i)**/
	
	int size = 0;
	
	char headerBirthdayInTwoWeeks[MAX_STR] = "Reminder: Upcoming birthdays in 14 days: ";
	size += sprintf(stdoutStream + size, "%s", headerBirthdayInTwoWeeks);
	
	
	
	/** Section 2. Writing about birthdays nearing in 2 weeks (14 days)!**/
	if (cntBirthdayInTwoWeeksPeople <= 0)
	{
		size += sprintf(stdoutStream + size, "%d people\n", cntBirthdayInTwoWeeksPeople);	
	}
	else
	{
		/** Outputting total of birthdays. Afterwhich, linebreak for "---" **/
		size += sprintf(stdoutStream + size, "%d people. \n", cntBirthdayInTwoWeeksPeople);
		
		/** Create "---------" linebreak into output**/
		char separatingLn[MAX_STR] = {0};
		char *pSeparatingLn = separatingLn;
		CreateSeparatingPrintLn(headerBirthdayInTwoWeeks, BUFFER, pSeparatingLn); 
		
		size += sprintf(stdoutStream + size, "%s\n", separatingLn);
		
		for (int i = 0; i < personCount; i++)
		{
			if ((pPerson + i)->dateOfBirth.isBirthDayInTwoWeeks)
			{
				iterBirthday14days++;
 
				size += sprintf(stdoutStream + size, "[%d/%d] %s turns %d-years old during the following 14 days. %s was born on %02d.%02d.%04d.\n",
										iterBirthday14days, cntBirthdayInTwoWeeksPeople,
										(pPerson + i)->firstName, (pPerson + i)->age,
										(pPerson + i)->firstName,
										(pPerson + i)->dateOfBirth.day,
										(pPerson + i)->dateOfBirth.month,
										(pPerson + i)->dateOfBirth.year);	
			}
		}
	}
	/** Section 2. Writing about birthdays matching to user-input. Write to file!**/
	if (cntBirthdayPeople <= 0)
	{		

		char headerNoBirthday[MAX_STR] = "No birthdays found for this date ";
		size += sprintf(stdoutStream + size, "\n\n%s\n", headerNoBirthday);
		
		/** Create "---------" linebreak into output**/
		char separatingLn[MAX_STR] = {0};
		char *pSeparatingLn = separatingLn;
		CreateSeparatingPrintLn(headerNoBirthday, BUFFER, pSeparatingLn); 
	 
		size += sprintf(stdoutStream + size, "%s\n", separatingLn);				
	}
	else
	{
		size += sprintf(stdoutStream + size, "\n\nCongratulations, %d birthday(s) for this selected date '%02d.%02d.%04d'. \n",
							cntBirthdayPeople, inputDay, inputMonth, inputYear);
		
		char headerBirthdays[MAX_STR] = "\nCongratulations, XX birthday(s) for this selected date 'dd.mm.yyyy'.";
		
		char separatingLn[MAX_STR] = {0};
		char *pSeparatingLn = separatingLn;
		CreateSeparatingPrintLn(headerBirthdays, ZERO, pSeparatingLn); 
	 
		size += sprintf(stdoutStream + size, "%s", separatingLn);
		
		/** Step 1b. Create line char-line of respective length ('-' * i)**/
		
		
		for (int i = 0; i < personCount; i++)
		{
			if ((pPerson + i)->dateOfBirth.isBirthDay)
			{
				iterBirthdayNow++;
				
				if ((pPerson + i)->age <= 0)
				{	
					size += sprintf(stdoutStream + size, "\n[%d/%d] %s was born today! %s was born on %02d.%02d.%04d.",
						iterBirthdayNow, cntBirthdayPeople,
						(pPerson + i)->firstName,
						(pPerson + i)->firstName,
						(pPerson + i)->dateOfBirth.day,
						(pPerson + i)->dateOfBirth.month,
						(pPerson + i)->dateOfBirth.year);
				}
				else 
				{
					size += sprintf(stdoutStream + size, "\n[%d/%d] %s turns %d-years old on this date! %s was born on %02d.%02d.%04d.",
										iterBirthdayNow, cntBirthdayPeople,
										(pPerson + i)->firstName, (pPerson + i)->age,
										(pPerson + i)->firstName,
										(pPerson + i)->dateOfBirth.day,
										(pPerson + i)->dateOfBirth.month,
										(pPerson + i)->dateOfBirth.year);
				}
			}	
		}
	}
	sprintf(stdoutStream + size, "%s\n", separatingLn);		

	#ifdef DEBUG
	printf("\n Successfully ran '%s'\n", __FUNCTION__);
	#endif
	return size;
}

/** Description:  Write stdoutput to output-file.
 * 					the resulting output contains:
 * 						Only persons with birthday or in 2 weeks 
 * 
 *  Parameters:    "stdoutStream": a char-array of output 
 * 				   "size": size of the "stdoutStream".
 * 				   "* filename": pointer to filename we write to.  
 * 
 *  Result:	       void (writing to file)        
 **/
void WriteStdoutToFile(int size, char stdoutStream[MAX_STR_512], char filename[STR_NAME_LEN]) 
{
	/** pointer for file stream (input file streams) **/
	FILE *fOutputStream;
    fOutputStream = fopen(filename, "w");
    
    /** Check if file stream EMPTY for file "input.txt" **/
	if (fOutputStream == NULL)
	{
		perror("");		/** error checking ("permissions denied") **/
		fprintf(stderr, "Error opening file '%s'\n", filename); 
	}
	else
	{
		fprintf(fOutputStream, "%s", stdoutStream);
	}
		/** Closing file-stream **/
	fclose(fOutputStream);
	
	#ifdef DEBUG
	printf("\n Successfully ran '%s'\n", __FUNCTION__);
	#endif
	
}
/** Description:    Print basic useable commands
 * 
 *  Parameters:     void                  
 * 
 *  Result:         void
 **/
void Usage()
{
	 puts("\n Usage of the program: ./birthdays --input=filename.txt" 
         "\n Program identifies birthdays and any birthdays in the following 2 weeks from a select date."
         "\n\n The program requires a minimum of a filename to read data from."
         
         "\n\t Program reads the input from the given file"
         "\n\t and outputs results to terminal-prompt and 'output.txt' by default."
         "\n\t *Example: './birthdays -i=input.txt"
         "\n\t *Example: './birthdays --input=input.txt\n"
         
         "\n\t Possible argument variations:"
         "\n\t *Example: './birthdays -i=input.txt --prompt=disabled'"
         "\n\t *Example: './birthdays -i=input.txt --output=output.txt'"
         "\n\t *Example: './birthdays --input=input.txt --prompt=disabled'--output=output.txt\n"
         "\n\t For more information, type './birthdays --help' or ''./birthdays -h'");
}

/** Description:    Print instructions of the program (--help or -h)
 * 
 *  Parameters:     void                  
 * 
 *  Result:         void
 **/
void RunHelpMode()
{    
    puts("\n Manual page of the program ./birthdays --input=filename.txt" 
         "\n Program identifies birthdays and any birthdays in the following 2 weeks from a select date."
         "\n\n The program requires a minimum of a filename to read data from."
         
         "\n\t Program reads the input from the given file"
         "\n\t and outputs results to terminal-prompt and 'output.txt' by default."
         "\n\t *Example: './birthdays -i=input.txt"
         "\n\t *Example: './birthdays --input=input.txt"

         "\n\n -p=disabled or --prompt=disabled"
         "\n\t Program reads input from file stream and outputs to file stream."
		 "\n\t The program will not show results in the terminal-prompt."
         "\n\t Results are directed to file 'output.txt' by default ."
         "\n\t *Example: './birthdays -i=input.txt -p=disabled'"
         "\n\t *Example: './birthdays -i=input.txt --prompt=disabled'"
         
		 "\n\n -o=output_filename.txt or --output=output_filename.txt"
         "\n\t Program creates a file and directs result to chosen filename."
         "\n\t The program will show results in the terminal-prompt by default."
         "\n\t Results are directed to file 'output.txt' by default ."
		 "\n\t *Example: './birthdays -i=input.txt -o=output.txt'"
         "\n\t *Example: './birthdays -i=input.txt -o=output.txt'\n"
         
         "\n\t The program allows to skip prompts and strictly output to only the chosen output files."
         "\n\t Use '-p=disabled' or '--prompt=disabled'."
         "\n\t *Example: './birthdays -i=input.txt -p=disabled -o=output.txt'"
         "\n\t *Example: './birthdays --input=input.txt --prompt=disabled'--output=output.txt"

         
         "\n\n -h or --help"
         "\n\t Prints a manual of the programs modes and explanations."
         "\n\t *Example: './birthdays --help'"
         "\n\t *Example: './birthdays -h'");
         
}
		
/** Description:    Identify if user inserted command line argument
 *                  "--help" or "-h"
 * 
 *  Parameters:     command line argument vector              
 * 
 *  Result:         boolean: True/False
 **/
bool IsHelpMode(char *argv[MAX_ARG_LEN])
{
    return ((strcmp(argv[ARGS_POS_1], "-h") == 0) ||
        (strcmp(argv[ARGS_POS_1], "--help") == 0));
}	


/** Description:    Get the '-i', '--input' or any suffix from CLI argument
 * 
 *  Parameters:     char *argv[]:   pointer of argument vector (CLI args)
 *  				char cliSuffix: the suffix we find in this function  
 * 					int argsIndex:   the position of argv. 
 * 											example: argv[2] or argv[3]
 * 
 *  Result:         void (filling the char-array "cliSuffix") 
 **/
void GetProgramModeSuffix(char *argv[MAX_ARG_LEN], char cliSuffix[STR_NAME_LEN], int argsIndex)
{
    /** Step 1: Parsing CLI ('-i=' or '--input='), **/
    for (int i = 0; i < strlen(argv[argsIndex]); i++)
    {
        cliSuffix[i] = argv[argsIndex][i];
        
        if (argv[argsIndex][i] == '=')
        {
            #ifdef DEBUG
			printf("\n DEBUG: str[%d]= '%c' "
                        "\n Found delimiting '=' to parse filename "
                        "from entire command line argument.", i, argv[argsIndex][i]);
            #endif
            break;
        }
        #ifdef DEBUG
		printf("\n DEBUG: str[%d] = %c ", i, argv[argsIndex][i]);
		#endif
    }
    strcat(cliSuffix, "\0"); /** Do we require this?**/  
}

/** Description:    Identify if program is initiated to read a file.
 *                  -i=filename or --input=filename
 * 
 *  Parameters:     char: suffix "-i" or "--input" in the  command-line arugment 
 *  Result:         boolean:        TRUE or FALSE (not file-reading mode)
 **/
bool IsDefaultFileInputMode(char cliSuffix[STR_NAME_LEN])
{
    return ((strcmp(cliSuffix, "-i=") == 0) || (strcmp(cliSuffix, "--input=") == 0));
}	

/** Description:    Identify if program is initiated to write to a selected file.
 *                  -o=filename or --output=filename
 * 
 *  Parameters:     char: suffix "-o" or "--output" in the  command-line arugment 
 *  Result:         boolean:        TRUE or FALSE (not file-reading mode)
 **/

bool IsOutputFileMode(char cliSuffix[STR_NAME_LEN])
{
    return ((strcmp(cliSuffix, "-o=") == 0) ||
    (strcmp(cliSuffix, "--output=") == 0));
}		
	

/** Description:    Parsing filename from command-line argument 
 *                  "--input=<filename>" or "-i=<filename>"
 *                  
 *                  Will start iterating from '=' symbol
 *                           (in -i=filename) or
 *                           (in --input=filename)
 *
 *                  Thus, we locate correct index -> j = strlen(string)
 * 
 *  Parameters:     argument vector - *argv[]
 *                  string containing -i or --input
 *                  filename (that we populate with this Function)
 *
 *  Result:         return: void (nothing). 
 *                  We will populate filename array-variable.
 **/
void GetFilename(char *argv[MAX_ARG_LEN], char cliSuffix[STR_NAME_LEN],
                 char inputFile[STR_NAME_LEN], int argIndex)
{
    int idx = 0;
    for (int j = strlen(cliSuffix); j < strlen(argv[argIndex]); j++)
    {
        inputFile[idx] = argv[argIndex][j];
        idx++;
        
    }
    inputFile[idx] = '\0'; /** verify whether needed **/
    
	#ifdef DEBUG
	DebugString(inputFile);
	#endif
    
}	

/** Description:    Print each character in array of characters
 * 
 *  Parameters:     array of chars,                   
 * 
 *  Result:         void 
 **/
void DebugString(char str[STR_NAME_LEN])
{
    int i = 0;
    printf("\nString is: '%s'\n", str);
    while (str[i] != '\0')
    {
        printf("str[%d] = %3hhu %c\n", i, str[i], str[i]);
        i++;
    }
    printf("\n");
} 

/** Description:    Determine whether -p=disabled or --prompt=disabled
 * 						was entered in the command-line vector.
 * 
 *  Parameters:     argv: argument vector                   
 * 					index of argv
 *  Result:         bool: true or false 
 **/
bool IsPromptDisabledMode(char *argv[MAX_ARG_LEN], int index)
{
    return ((strcmp(argv[index], "-p=disabled") == 0) ||
        (strcmp(argv[index], "--prompt=disabled") == 0));
}

