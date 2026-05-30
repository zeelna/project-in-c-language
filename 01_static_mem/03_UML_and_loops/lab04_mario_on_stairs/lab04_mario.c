#include <stdio.h>
#define WHITE_SPACE " "
#define STEPS_CONSTANT 13

int main(void)
{
	int starCount = 0;
	int starTotal = 0;
	
	int i = -1;
	int j = -1;
	
	int lineNumber = 0;
	
	/* Printing a stickman */
	printf(" O \n");
	printf("-|-\n");
	printf(" | \n");
	printf("/ \\");


	/* We continue on line with stickman's leg to format the column headers */
	for (i = 0; i <= STEPS_CONSTANT; i++)
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
		
		/* Formatting table with necessary number of white-spaces
		 * We are searching for stepsCount (line of stairs), not width of steps*/
		if (i == 0)
		{
			while (j< STEPS_CONSTANT+1) // give +1, because offset due to index and stickman's legs.
			{	
			printf(WHITE_SPACE);
			j++;
			}
		}
		else 
		{
			while (j< STEPS_CONSTANT+2) // give +2, example: 13 steps means 15 rows (keep in mind, we start at 0 and go to 14 ( j < 15)
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
			printf(" row total line\n");
		}
		else 
		{
			printf("%3d %5d %5d \n", starCount, starTotal, lineNumber);
		}
	}
	
	return 0;
}
