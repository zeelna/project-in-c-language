/** 
* File:        8_1_date_base.c 
* Author:      Risto Heinsar 
* Created:     20.10.2014 
* Modified:    12.10.2023 
* 

* Description: Basecode for the date verification lab task. The code is 
*              intended to be used with stream redirection, so it doesn't  
*              write any prompts. It can be executed by just typing inputs 
*              from the keyboard. To stop entry and run the checks this way, 
*              press Ctrl+D (end of file signal) at any point during input.                  
*/ 

#include <stdio.h> 
#include <stdbool.h> 

#define MAX 100 

#define MIN_DAYS 1 
#define MIN_MONTH 1 
#define MAX_MONTH 12 
#define YEAR_MIN 1900 
#define YEAR_MAX 2100 

#define MAX_MONTH 12 
#define MIN_MONTH 1 

#define FEBRUARY 2

#define DATE_VALID 1 

#define DATE_INVALID 0 
#define YEAR_INVALID 2
#define MONTH_INVALID 3
#define DAY_EXCEEDS_MONTH 4
#define DAY_INVALID 5
#define NOT_LEAP_YEAR 6 

bool IsLeapYear(int year); 
int GetDaysInMonth(int month, int year); 
int ValidateDate(int day, int month, int year); 
int ReadDates(int day[], int month[], int year[], int max); 
void PrintDates(int day[], int month[], int year[], int n); 

void PrintErrorMessage(int statusCode) ;

int main(void) 
{ 
    int days[MAX], months[MAX], years[MAX]; 
    int dateCount = ReadDates(days, months, years, MAX); 
    PrintDates(days, months, years, dateCount); 
    return 0; 
} 

/** 
* Description:    Reads in the dates to the day month and year arrays. 
*                 The same index in each of the arrays are used for the 
*                 same date. 
*  
* Parameters:     day - an array of day values 
*                 month -array of month values 
*                 year - array of year values 
*                 max - maximum size of the arrays. 
*  
* Return:         number of dates read by the program 
*/ 

int ReadDates(int day[], int month[], int year[], int max) 
{ 
	int count = 0; 
	while (count < max) 
	{ 
	/** 
	* takes first 2 digits, stores as integer, into day array, 
	* 2 for month, stores as integer, into in month array, 
	* 4 for year, stores as integer, into year array 
	**/ 

	// Input format is ddmmyyyy (i.e 10112011) 
		int itemsScanned = scanf("%02d%02d%04d", &day[count], &month[count], &year[count]); 

	// if inputs ends or input contains invalid symbols, we stop reading 
		if (itemsScanned !=  3) 
		{ 
			break; 
		} 
	/** increment count **/ 
		count++; 
	} 
	return count; 
} 

/** 
* Description:    Prints the dates in the arrays, assumes dates with 
*                 the same index in all three arrays are related. 
*  
* Parameters:     day - an array of day values 
*                 month -array of month values 
*                 year - array of year values 
*                 n - umber of dates in the arrays 
*  
* Return:         none 
*/ 

void PrintDates(int day[], int month[], int year[], int n) 
{ 
	int statusCode = -1;
	printf("\nGot %d dates\n", n); 
	for (int i = 0; i < n; i++) 
	{ 
		printf("%02d.%02d.%04d", day[i], month[i], year[i]); 
		if (ValidateDate(day[i], month[i], year[i]) != DATE_VALID) 
		{ 
			//~ printf(" < Invalid date!"); 
			statusCode = ValidateDate(day[i], month[i], year[i]);
			PrintErrorMessage(statusCode);
		} 
		else 
		{ 
			printf(" < OK!"); 
		} 
	printf("\n"); 
	} 
} 

/** 
* Description:    Checks wheather the passed year is a leap year. 
*  
* Parameters:     year - the year to check 
*  
* Return:         true for leap year, false for normal year. 
*/ 

bool IsLeapYear(int year) 
{ 
	return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0); 
} 

/** 
* Description:    Function finds and returns the number of days in a month. 
*                 Month is given as an integer, starting from 1 (january). 
*                 Function handles leap years. 
*  
* Parameters:     month - month number starting from 1. 
*                 year - year number 
*  
* Return:         For valid dates, returns the number of days in a month.  
*                 For invalid dates, returns 0. 
*  
*/ 

int GetDaysInMonth(int month, int year) 
{ 
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
		//~ if (month == 2 && IsLeapYear(year) == 1) 
			return 29; 

		/** February on NOT leap year**/ 
		else if (month == 2 && !(IsLeapYear(year))) 
		//~ else (month == 2 && IsLeapYear(year) == 0)) 
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
* Return:         For valid dates, returns DATE_VALID (0), 
*                 For invalid dates, returns DATE_INVALID (1). 
*/ 

int ValidateDate(int day, int month, int year) 
{ 
    // Hint: use the functions GetDaysInMonth  
    // to assist in formulating the conditional statements 
    if (day < MIN_DAYS)
		return DAY_INVALID;
    
    else if (year < YEAR_MIN || year >= YEAR_MAX)  
		return YEAR_INVALID;  
		
	else if (GetDaysInMonth(month, year) == 0)	
		return MONTH_INVALID;

	else if (month == FEBRUARY && !(IsLeapYear(year)) && day >= 29)
		return NOT_LEAP_YEAR;
	
	else if (day > GetDaysInMonth(month, year)) 
		return DAY_EXCEEDS_MONTH;

	else 
		return DATE_VALID; 
} 

/** 

* Description:    Function prints respective error message of wrong date 
*  
* Parameters:     day - the day value. 
*                 month - month number starting from 1. 
*                 year - the year of the date 
*  
* Return:         For valid dates, function is passed with no print-statement.
*/  
void PrintErrorMessage(int statusCode) 
{ 
	if (statusCode == DAY_INVALID) 
		printf(" < Day before first of month!");	 
	else if (statusCode == MONTH_INVALID) 
		printf(" < No such month exists!"); 
	else if (statusCode == YEAR_INVALID) 
		printf(" < Year out of range!");
	else if (statusCode == NOT_LEAP_YEAR)
		printf(" < 29th of February only exists on leap year!");
	else if (statusCode == DAY_EXCEEDS_MONTH)	 
		printf(" < Day exceeds maximum days for given month!");
	else
		printf(" < Invalid date!");
}
