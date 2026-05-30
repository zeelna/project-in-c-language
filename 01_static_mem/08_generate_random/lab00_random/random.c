#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	printf("\nRange: 0 ... %d\n\n", RAND_MAX);
	srand((unsigned)time(NULL));	// seeding value refreshed every 1s, UNIX)
	for (int i = 0; i < 5; i++)
	{
		//~ srand((unsigned)time(NULL));	// starts generator from 0. 
		
		printf("Random num: %d\n", rand());
	}
	
	printf("\n");


	printf("\nRange: 0 ... 9\n");
	for (int i = 0; i < 9; i++)
	{
		printf("Random num: %d\n", rand() % 10);
	}	
	
	printf("\nRange: -5 ... 5\n");
	for (int i = -5; i < 5; i++)
	{
		printf("Random num: %d\n", rand() % 11 - 5);
	}	
	return 0;	// rand % ( max - min +1) - min
	// Universal formula for lab-task nr 2: rand % ( max - min +1) - min
}
