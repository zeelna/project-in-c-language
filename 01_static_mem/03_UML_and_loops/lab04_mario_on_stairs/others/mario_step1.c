#include <stdio.h>
#define LOWER_LIMIT 7
#define UPPER_LIMIT 20
#define TABLE_WHITESPACE 5
#define STICKMAN_HEIGHT 3
#define WHITE_SPACE " "

int main(void)
{
	int input;
	int starCount;
	int starTotal = 0;
	
	int i = 0;
	int j;
	int k = 0;
	
	int lineNumber;
	
	/* Formatting table with necessary number of white-spaces
	 * 
	 *	   j 0 1 2 3 4
	 * 
	 * 	   i
		 * 0       O
		 * 1      -|-
		 * 2	   | 
		 * 3	  / \
		 * 4     * * *
		 * 5   * * * *
		 * 6 * * * * *
	*/

	/* Asking input from user until larger than 0. */
	do
	{
		printf("Enter base width [%d-%d]: ", LOWER_LIMIT, UPPER_LIMIT);
		scanf("%d", &input);
		
		if (input < LOWER_LIMIT || input > UPPER_LIMIT)
		{
			printf("Error! Allowed base width is %d-%d!\n", LOWER_LIMIT , UPPER_LIMIT);
		}
		++k;	// DO NOT FORGET TO INCREMENT!
	} while (input < LOWER_LIMIT || input > UPPER_LIMIT);
	

	/* We continue on line with stickman's leg to format the column headers */
	for (i = 0; i < input+2; i++)
	{
		/* Resetting the starCount for each new line IN THIS FOR-LOOP */
		starCount = 0;
		
		/* Resetting 'j' to count how many * to print on this line 'i' IN THIS FOR-LOOP*/
		j = 0;
		
		/* Bulding stickman (shifted to right)*/
		while (i <= STICKMAN_HEIGHT)	// is 3 (counted 0 to 3, 4digits)
		{
			/* adding white-spaces for stickman  */
			for (k = 0; k < (input - 3); k++)	//  ' <  input - 3' is whitespace until stickman starts.
			{
				printf(WHITE_SPACE);
			}
			//i++;	// do not forget to increment!

			/* printing stickman */
			switch (i) 
			{
				case 0:
				printf(" O \n");
				break;
				case 1:
				printf("-|-\n");
				break;
				case 2:
				printf(" | \n");
				break;
				case 3:
				printf("/ \\ row total steps line\n"); // more fun option
				//printf("/ \\ row total \n");		// exercise section.
				break;
				default:
				break;
			}
		i++;	// do not forget to increment!		
		}
		
		/* Mario staircase formatting with whitespace before '*' */
		while (j-1 < (input - (i))) // j-1 because we must give *** for first platoo. (otherwise ** if 'j < ...')
		//while (j < ((input+2)-(i+1)))
		{
			printf(WHITE_SPACE);	
			j++;
		}

		/* Moving on to add * 
		 *  increment j+1 because,
		 * 
		 *i = 4    aaa/ \		otherwise		i = 4 	  aaa/ \
		 *i = 5	   aaa***						i = 5	 aaa****
		 *i = 6	 aaaa****						i = 6	aaaa****
		 */
		while ((j+1 < (input+1)) && (i > STICKMAN_HEIGHT))	// excluding when we are at stickman (i = {0,1,2,3})
		{
			printf("*");		
			j++;	// do not forget to increment! (we are at while-loop, not for-loop)
			starCount++;	// do not forget to increment separately. Important to sum starTotal
		}
		
		lineNumber = i;	// remember, we started line 4 at stickman's legs due to formatting.
				
		/* Ternary Conditional operator 
		 * variable = (expression) ? 2nd operand (==True) : 3rd operand (==False) 
		 * 
		 * if expression True, then assign 2nd operand to varible, if expression False then assign 3rd operand to variable 
		 */
		starCount = (i <= STICKMAN_HEIGHT) ? 0 : starCount; 
		/* assigned starCount = 0, if we at line 0 (step 0) meaning stickman's legs.*/
		
			
		/* adding up number of stars printed thus far. */
		starTotal+= starCount;
		if (i > 3) // stickman legs at 'i: 3'.
		{
			printf("%3d %5d %5d %5d\n", starCount, starTotal, lineNumber-4, lineNumber);
			//printf("%3d %5d \n", starCount, starTotal);
		}
	}
	
	return 0;
}
