#include <stdio.h>
#define LOWER_LIMIT 7
#define UPPER_LIMIT 20
#define	TABLE_WHITESPACE 5
#define WHITE_SPACE "a"

int main(void)
{
	int input = -1;
	int starCount = 0;
	int starTotal = 0;
	
	int i = -1;
	int j = -1;
	int k = -1;
	
	int lineNumber = 0;

	/* Asking input from user until larger than 0. */
	do
	{
		printf("Enter base width [%d-%d]: ", LOWER_LIMIT, UPPER_LIMIT);
		scanf("%d", &input);
		
		if (input < LOWER_LIMIT || input > UPPER_LIMIT)
		{
			printf("Error! Allowed base width is %d-%d!\n", LOWER_LIMIT, UPPER_LIMIT);
		}
		++k;
	} while (input < LOWER_LIMIT || input > UPPER_LIMIT);
	
	/* Printing a stickman */
	printf(" O \n");
	printf("-|-\n");
	printf(" | \n");
	printf("/ \\");


	/* We continue on line with stickman's leg to format the column headers */
	for (i = 0; i < input-1; i++)
	{
		/* Resetting the starCount for each new line*/
		starCount = 0;
		
		/* Resetting 'j' to count how many * to print on this line 'i' */
		j = 0;
		while (j < i+2)	// example when 'line 0' means 'i = 0', thus the expression 'j < 3' will print * twice. 
		{
			if (i > 0)	// skip print * when we are on line 0 (stickmen's legs), because we will put column headers on line 0.
			{
				printf("*");		
			}
			j++;	// do not forget to increment! (we are at while-loop, not for-loop)
		}
		
		lineNumber = i;	// remember, we started line 0 at stickman's legs due to formatting.
				
				
		/* Ternary Conditional Operator Explained
		 * #################################################################
		 * 	if the 'expression' (1st operand) is True, returns 2nd operand, 
		 * 	but if-instead is False, returns 3rd operand
		 * 
		 * variable = <(1st operand)> ? <2nd operand> : <3rd operand>;
		 * maxNumber = (num1 > num2)  ?        num1   :   num2;
		 * ##################################################################
		*/
		starCount = (i == starCount) ? 0 : j; 
		
		/* adding up number of stars printed thus far. */
		starTotal+= starCount;
		
		/* Formatting table with necessary number of white-spaces*/
		//while (j-1< (input + TABLE_WHITESPACE))
		//while (j < (input + TABLE_WHITESPACE))
		//~ while (j-1< input-1)	// on next line after stickman's legs, we are not adding extra white-space (j-1)
		//~ {
			//~ printf(WHITE_SPACE);
			//~ j++;
		//~ }
		
		if (i == 0)
		{
			while (j-1< input-2) // give +1, because offset due to index and stickman's legs.
			{	
			printf(WHITE_SPACE);
			j++;
			}
		}
		else 
		{
			while (j-1< input-1) // give +2, example: 13 steps means 15 rows (keep in mind, we start at 0 and go to 14 ( j < 15)
			{	
			printf(WHITE_SPACE);
			j++;
			}
		}
		
		/* When are at stickman's legs, we print column header's, 
		 * afterwards the table content's 
		 */
		if (i == 0)
		{
			printf(" row  total  line\n");
		}
		else 
		{
			printf("%3d %5d %5d \n", starCount, starTotal, lineNumber);
		}
	}
	
	return 0;
}
