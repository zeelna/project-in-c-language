#include <stdio.h>

#define NUM_OF_SUMS 7

int main(void) {

	int i = 0;
	int sum = 0;
	int val = 0;
	
	printf("This program takes 5 numbers from the users and adds them up. \n");
	printf("Subtotal is shown after each addition until not asked anymore. \n");
	
	do 
	{
		printf("Enter number %d / %d \n", i +1, NUM_OF_SUMS);
		// must be "i + 1", because "i++" will store in the variable "i"
		// by incrementing by +1
	
		scanf("%d", &val);
		sum += val;

		if (i + 1 < NUM_OF_SUMS) // skip print-statement if last number.
		{
			printf("Sumtotal %d\n", sum);
		}
	
		i++;
	}
	while (i < NUM_OF_SUMS);
	printf("Loop has ended. The final amount is: %d", sum);
	return 0;
} 
