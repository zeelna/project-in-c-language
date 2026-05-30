#include <stdio.h>

/* Number of age groups in total */ 
#define GROUPS 11
/* Array position for minors group */
#define GROUP_MINOR (GROUPS - 2)
/* Array position for elders group */
#define GROUP_ELDER (GROUPS - 1)
/* Group size*/
#define GROUP_STEP 5
/* Upper bound for minors */
#define MINOR_UPPER_BOUND 17
/* Calculates lower bound for elders */
#define ELDER_LOWER_BOUND (MINOR_UPPER_BOUND + (GROUP_STEP * (GROUPS - 2)))

#define MAX_PERSONS 10

int GetAgeInput(void);
int FindAgeGroupIndex(int inputAge);
void GetAgeGroupInfo(int groups[]);

int main(void)
{
    int ageGroups[GROUPS] = {0};
    int idx;   
    int ageInput = 0;

    /* Program introduction Print message: */
    printf("This program categorizes participants of the event into age brackets!\n");
    printf("To stop entry and show statistics, enter 0 or a negative number at any point!\n");
    
    /** Extra: 1/2: Remove //~ to and below**/
    /**
    //int j= 0;
    //~ int personsInGroup;
    **/
    while (1)  
    {
        printf("\n\nEnter pariticipants age: ");
        ageInput = GetAgeInput();
        
		if (ageInput <= 0)
		{
			break;
		}	
		
        idx = FindAgeGroupIndex(ageInput);
        printf("DEBUG: ind = %d", idx);
        
        /* Add to the age group counter */
        ageGroups[idx]++;		// does not count personsInGroup if we type ageGroups[idx++]
        
        /** Extra: 2/2: Remove //~ to see iteration-count AND Array is being incremented at specific Age-Group (i.e at index)**/
        /**
        //~ personsInGroup = ageGroups[idx]++;		// does not count personsInGroup if we type ageGroups[idx++]
        //printf("\nageGroups[idx]++: %d ", personsInGroup); 
        //printf("\nIndex: %d", j);	// unnecessary
        //j++;	// unnecessary
        **/
    }
    /* Print the results (Call your function!) */
    GetAgeGroupInfo(ageGroups); 
    return 0;
}
int GetAgeInput(void)
{
	int userInput = 0;
	//~ return scanf("%d", &userInput); 	// WHY DOES THIS NOT WORK?????
	scanf("%d", &userInput);
	return userInput;
}

int FindAgeGroupIndex(int inputAge)
{
	int index;
	if (inputAge <= MINOR_UPPER_BOUND)
	{
		index = GROUP_MINOR; //return GROUP_MINOR
	} 
	else if (inputAge > ELDER_LOWER_BOUND)
	{
		index = GROUP_ELDER; //return GROUP_ELDER
	}
	else
	{
		index = (inputAge - (MINOR_UPPER_BOUND + 1)) / GROUP_STEP; // return ((inputAge - (MINOR_UPPER_BOUND + 1)) / GROUP_STEP)
	}
	return index;	// if implement "return" statements above (all 3), than can remove "return index"
}
void GetAgeGroupInfo(int groups[])
{
	int currLowerBound = MINOR_UPPER_BOUND+1;
	int currUpperBound = 0;
	
	/* Print Minor count: */
	printf("\nMinors: %d", groups[GROUP_MINOR]);
	int i;
	for (i = 0; i < GROUPS-2; i++)	// -2 means not counting minors and elders. Last Group (elders: GROUP-1) and First group (minors: GROUP-2)
	{ 
		currUpperBound = currLowerBound + GROUP_STEP;	// Avoid magical numbers (including GROUP_STEP)
		printf("\nAges %2d - %2d: %d", currLowerBound, currUpperBound-1, groups[i]);
		
		/* Updating variable for next loop-iteration! */
		currLowerBound = currUpperBound;
	}
	
	/* Print elder count:*/
	printf("\nElders: %d", groups[GROUP_ELDER]);
}
/** Bad solution. **/
//~ void GetAgeGroupInfo(int index)
//~ {
	//~ printf("\nAges %2d - %2d: ", ((index * GROUP_STEP) + MINOR_UPPER_BOUND + 1), (GROUP_STEP + ((index * GROUP_STEP) + MINOR_UPPER_BOUND))); 
//~ }
