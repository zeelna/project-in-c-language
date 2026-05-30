/**
 * File:        timetable_without_days.c
 * Author:      Frank Christopher Kirch
 * Created:     21.09.2023
 * Last edit:   24.09.2023
 *
 * Description: Starter code for the functions lab task, generating an 
 *              appointment schedule for clients.
 */
#include <stdio.h>

#define WORKDAY_START_HOUR 8
#define WORKDAY_START_MIN 0

int GetPositiveInt(void);

int CalcNextHour(int cMin, int cHour, int interval);
int CalcNextMin(int cMin, int cHour, int interval);


void PrintTime(int cHour, int cMin);
void PrintTimeInterval(int startHour, int startMin, int endHour, int endMin);

void PrintTimetable(int startHour, int startMin, int nClients, int appLen);


int main(void)
{
	int clients;
	int interval;
	
    printf("Workday starts at");
    PrintTime(WORKDAY_START_HOUR, WORKDAY_START_MIN);
    
    
    printf("\n\n");
    
    printf("Enter num of clients\n");
	scanf("%d", &clients);
    
    printf("Enter client session length\n");
	scanf("%d", &interval);
  
  
    PrintTimetable(WORKDAY_START_HOUR, WORKDAY_START_MIN, clients, interval);

    
    return 0;
}


/**
 * Description:    Returns a positive integer from the user. On non-positive
 *                 input, gives an error and reprompts the user
 *
 * Parameters:     -
 *
 * Return:         Positive integer entered by the user
 */
int GetPositiveInt(void)
{
	int input;
	
	do
	{
		printf("Enter a positive number larger than 0.\n");
		scanf("%d", &input);
		
		if (input <= 0)
		{
			printf("You entered non-positive. Try again!\n");
		}
	} while (input <= 0);
	printf("You entered a positive integer. Thank you!\n");
	
	return input;
}


/**
 * Description:    Finds the hour value when adding period to current time.
 *
 * Parameters:     cMin - current minute value
 *                 cHour - current hour value
 *                 interval - number of minutes to add to current time
 *
 * Return:         Hour value after adding the period
 */

int CalcNextHour(int cMin, int cHour, int interval)
{
	// Adding hours (example interval = 140 / 60 = 2 --> newHour = 8 + 2 = 10)
	
	cHour += ((cMin + interval) / 60);
	
	/* if 26 / 24 = 1 and 26 % 24 = 2 ----> newHour = 0 --> newHour = 26 % 24 = 2 */
	if (((cHour / 24) >= 1) && ((cHour % 24) >= 0))
	{ 
		cHour = (cHour % 24);	// 26 % 24 = 2 --> assign to cHour;
	} 
	return cHour;
}



/**
 * Description:    Finds the minute value when adding period to current time.
 *
 * Parameters:     cMin - current minute value
 *                 cHour - current hour value
 *                 interval - number of minutes to add to current time
 *
 * Return:         Minute value after adding the period
 */


int CalcNextMin(int cMin, int cHour, int interval)
{

	cMin += interval;
	/* 140 / 60 = 2 --> && 140 % 60 = 20*/
	if (((cMin / 60) >= 1) && ((cMin % 60) >= 0))
	{
		cMin = (cMin % 60); // 140 & 60 = 20 --> assign to cMin;
	}
	return cMin;

}


/**
 * Description:    Prints the time passed using hh:mm format. Hour values below
 *                 10 are space-padded and minue values below 10 are zero-padded
 *
 * Parameters:     hour - current hour value
 *                 min - current minute value
 *                 
 * Return:         -
 */
void PrintTime(int cHour, int cMin)
{
	if (cHour < 10)
	{
		printf("%2d", cHour);
	}
	else
	{
		printf("%d", cHour);
	}
	
	// Ternarny
	//answer = (cHour < 10) ? printf("%2d", cHour): printf("%d", cHour);
	
	
	if (cMin < 10)
	{
		printf(":%02d", cMin);
	}
	else
	{
		printf(":%d", cMin);
	}
}


/**
 * Description:    Prints a time interval using hh:mm - hh:mm format.
 *
 * Parameters:     startHour - Starting hour value
 *                 startMin - Starting minute value
 *                 endHour - End hour value
 *                 endMin - End minute value
 *                 
 * Return:         -
 */
void PrintTimeInterval(int startHour, int startMin, int endHour, int endMin)
{
    
    PrintTime(startHour, startMin);
    printf(" - ");
    PrintTime(endHour, endMin);
    
}

/**
 * Description:    Prints the timetable for the client appointments
 *
 * Parameters:     startHour - Start of the work day (hours)
 *                 startMin - Start of the workday (minutes)
 *                 nClients - number of clients to schedule an appointment for
 *                 appLen - appointment length
 *                 
 * Return:         -
 */
void PrintTimetable(int startHour, int startMin, int nClients, int appLen)
{
	int endOfHour;
	int endOfMinute;
	
	
	int currMin = startMin;
	int currHour = currHour;
	
	currMin = WORKDAY_START_MIN;
	currHour = WORKDAY_START_HOUR;
	
	int i;
	for (i = 0; i < nClients; i++)
	{
		printf("\nClient %2d: ", i+1);
		

		endOfHour = CalcNextHour(currMin, currHour, appLen);
		endOfMinute = CalcNextMin(currMin, currHour, appLen);
		
		PrintTimeInterval(currHour, currMin, endOfHour, endOfMinute);
		currHour = endOfHour;
		currMin = endOfMinute;

	}
}
