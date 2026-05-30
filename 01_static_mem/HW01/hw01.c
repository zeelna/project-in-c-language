/**
 * File:        hw01.c
 * Author:      Frank Christopher Kirch
 * Created:     03.10.2023
 * Last edit:   17.10.2023
 *
 * Description: Solving function y = (2x+1) / sqrt((2x^2 + 3x +4)^3 - 7) 
 * in a formatted table. 
 */

/* Including macro to allow standard I/O functions, pow(), sqrt(). */
#include <stdio.h>
#include <math.h>
#include <string.h>

/** Macros to avoid magical-numbers **/
/** Preprocessors to validate user input for function's step variable**/
#define UNDIVISABLE_STEP 1
#define MIN_STEP 0
#define MAX_STEP_NR 20

/** Preprocessors to set function's range. **/
#define Y_MIN -0.271
#define Y_MAX 0.144


/** Extra Task part: Preprocessors to print correct preset info-table.**/
#define PRESET_TEST_1 1
#define TEST_1_MIN -5.555
#define TEST_1_MAX 5.554
#define TEST_1_STEP 30

#define PRESET_TEST_2 2
#define TEST_2_MIN -4.500
#define TEST_2_MAX 5.550
#define TEST_2_STEP 11

#define PRESET_TEST_3 3
#define TEST_3_MIN -4.500
#define TEST_3_MAX 5.950
#define TEST_3_STEP 11

/* Prototypes of the functions. */
/** Prototypes of function to get input from user**/
double GetStartInput();
double GetEndInput(double startInput);
int GetStepInt();
int ModifyStepIntoBound(int stepValue, int maxStep);

/** Prototypes to find Function's solutions.**/
double CalcH(double startValue, double stopValue, int stepValue);

int GetArrayY(double yArray[], double xArray[], int yArrLenCnt);
int GetArrayX(double xArray[], double startValue, int stepValue, double valueH);

void PrintTable(double xArray[], double yArray[], int yArrLenCnt, int stepValue);


/** Prototypes of program (input-mode). **/
void PrintGreetMessage();
void BaseSolution();


/** Extra Task prototypes (preset input, example '--TEST1' CLI argument **/
void TestHardcodedValues(double startValue, double endValue, int stepValue, int maxStep, int testNr);
void PrintPresetTable(double minValue, double maxValue, int stepValue, int testNr);

/** Defining main body of the program, which is called out by Running the code. **/
int main(int argc, char *argv[])
{
	/** Creating variables in main function. Global variables forbidden! **/
	int exitCode = 1;

	/** Checking if user suitable passed command-line argument **/
	if (argc == 2)
	{
		if (strcmp(argv[1], "--TEST1") == 0)
		{
			TestHardcodedValues(TEST_1_MIN, TEST_1_MAX, TEST_1_STEP, MAX_STEP_NR, PRESET_TEST_1);
			return 0;
		}
		else if (strcmp(argv[1], "--TEST2") == 0)
		{
			TestHardcodedValues(TEST_2_MIN, TEST_2_MAX, TEST_2_STEP, MAX_STEP_NR, PRESET_TEST_2);
			return 0;
		}	
		else if (strcmp(argv[1], "--TEST3") == 0)
		{
			TestHardcodedValues(TEST_3_MIN, TEST_3_MAX, TEST_3_STEP, MAX_STEP_NR, PRESET_TEST_3);
			return 0;
		}
		else
		{
			printf("\nWrong input\n");
			return 1;	/** exiting program (incorrect terminal argument) **/
		}
	}
	/** User did not pass command-line argument. Thus user can give inputs. **/
	else
	{
		do 
		{
			BaseSolution();	/**run program 1st time regardless (do-while-loop) **/
			/** Re-looping entire program until user input's 0 at terminal prompt.**/
			printf("\nPlease enter '0' to exit the program or anything other number to repeat the program: ");
			scanf("%d", &exitCode);
		}
		while (exitCode != 0);
	}
	return 0; /** exiting program (program ran) **/
	
}

/**
 * Description:    Display introductory information to user of 
 * 				   the Function: y = (2x+1) / sqrt((2x^2 + 3x +4)^3 - 7)
 * Parameters:     -
 * Return:         -
**/
void PrintGreetMessage()
{
	printf("\nThe program solves function y = (2x+1) / sqrt((2x^2 + 3x +4)^3 - 7)\n");
	printf("The function's domain is: [-inf; inf].\n");
}

/**
 * Description:    Solving function with command line argument '--TEST2'
 * 					'--TEST2' CLI argument gives preset argument values.
 * 				   Function y = (2x+1) / sqrt((2x^2 + 3x +4)^3 - 7) 
 *
 * 					NB! Function will not display all x (not all steps).
 * 					This is because 10th X-values is larger than stopping/ending x-value
 * Parameters:     -
 *
 * Return:         -
**/
void TestHardcodedValues(double startValue, double endValue, int stepValue, int maxStep, int testNr)
{
	double valueH;
	double arrayX[MAX_STEP_NR] = {0};
	double arrayY[MAX_STEP_NR] = {0};	
	int xArrayLenCnt, yArrayLenCnt;
	
	/** A. Printing greet-statements for user. **/
	PrintGreetMessage();
	PrintPresetTable(startValue, endValue, stepValue, testNr);
	
	int newStepValue = ModifyStepIntoBound(stepValue, maxStep);
	valueH = CalcH(startValue, endValue, newStepValue);
	
	xArrayLenCnt = GetArrayX(arrayX, startValue, newStepValue, valueH);
	yArrayLenCnt = GetArrayY(arrayY, arrayX, xArrayLenCnt);
	
	PrintTable(arrayX, arrayY, yArrayLenCnt, stepValue);
}

/**
 * Description:     Print sample input table with correct format.
 *				
 * Parameters:	    starting x, ending x, step amount, 
 * 					Preset test number (--TEST<1>).
 * 
 * Return:          -
**/
void PrintPresetTable(double minValue, double maxValue, int stepValue, int testNr)
{
	printf("\n--------------------------");
	printf("\n--  Running TESTSET %d!  --", testNr);
	printf("\n--------------------------");
	printf("\n-- min \t %6.3lf \t--", minValue);
	printf("\n-- max \t %6.3lf \t--", maxValue);
	printf("\n-- step  %6d \t--", stepValue);
	printf("\n--------------------------");
	printf("\n");
}
/**
 * Description:    Call functions to ask inputs, solve 'y = Fn(x)' and print.
 *				   This is program's 'main'-Fn body (without Extra-Task)
 * Parameters:	   -
 * Return:         -
**/
void BaseSolution()
{
	double startInput = 0.00;
	double endInput = 0.00;
	int stepInput = 0;
	
	double valueH = 0;
	
	double arrayX[MAX_STEP_NR] = {0};
	double arrayY[MAX_STEP_NR] = {0};
	int xArrayLenCnt, yArrayLenCnt;

	PrintGreetMessage();
	
	/** A. Asking Function's argument starting value (X0 = A)**/
	startInput = GetStartInput();
	
	/** B. Asking Function's stopping value (B) **/
	endInput = GetEndInput(startInput);

	/** C. Asking Function's step (N) - (i.e how many x's user wants?). **/
	stepInput = GetStepInt(MAX_STEP_NR);
	
	/** D. Re-adjusting step (N) to '20' (MAX_STEP_NR), if is larger than 20 (MAX_STEP_NR). **/
	int newStepInput = ModifyStepIntoBound(stepInput, MAX_STEP_NR);
	
	/** E. Calculate step size (H). (i.e how large is the difference between x1 - x2) **/
	valueH = CalcH(startInput, endInput, newStepInput);
	
	/** G. Fill arrayX and return the length of the arrayX. --> is this VLA?**/ 
	xArrayLenCnt = GetArrayX(arrayX, startInput, newStepInput, valueH);
	
	/** G. Fill arrayY and return the length of the arrayY. --> is this VLA?**/ 
	yArrayLenCnt = GetArrayY(arrayY, arrayX, xArrayLenCnt);
	
	/** H. Print results into a table, acquiring values from two arrays (x and y)**/
	PrintTable(arrayX, arrayY, yArrayLenCnt, stepInput);
	
}
/**
 * Description:    Ask user input about start of the function point.
 *
 * Parameters:	   -
 * Return:         double: starting x of the function, by user input.
**/
double GetStartInput()
{
	double startInput;
	printf("\nPlease enter Starting point of Function: ");
	scanf("%lf", &startInput);
	return startInput;
}
/**
 * Description:    Ask user input about end of the function point.
 *
 * Parameters:	   -
 * Return:         double: Last/ending x of fuction by user input.
**/
double GetEndInput(double startInput)
{
	double endInput;
	while(1)
	{
		printf("\nPlease enter Ending point of Function: ");
		scanf("%lf", &endInput);
		if (endInput <= startInput)
		{
			printf("Try again! End value was %6.3lf. It cannot be smaller than start value %6.3lf", endInput, startInput);
		}
		else
		{
			break;
		}
	}
	return endInput;
}

/**
 * Description:   	Ask user input step of function points
 *
 * Parameters:	   	integer: largest allowed step ('20') (MAX_STEP_NR)
 * 
 * Return:			integer: user inputted step that is a whole number and not larger than 20.
**/
int GetStepInt()
{
	int stepInput = 0;
	
	while(1)
	{
		printf("\nPlease enter Step of Function: ");
		scanf("%d", &stepInput);
		if (stepInput <= MIN_STEP)
		{
			printf("Please try again! Step must be more than 0. (chosen input: '%d')\n", stepInput);
		}
		else if (stepInput == UNDIVISABLE_STEP)
		{
			printf("Please try again! ");
			printf("Step value cannot be '%d', because equation is then unsolvable: ", stepInput);
			printf("'H = (B - A) / (N - 1)'\n");
		}
		
		else
		{
			break;
		}
	}
	return stepInput;
}

/**
 * Description:     Re-adjusting too large number of steps (N) into maximum allowed step nr.
 *				
 * Parameters:	    number of steps (N), maximum allowed number of steps (N)
 * 
 * Return:          int: number of steps (N) (adjusted)
**/
int ModifyStepIntoBound(int stepValue, int maxStep)
{
	stepValue = (stepValue > maxStep) ? maxStep : stepValue;
	return stepValue;
}

/**
 * Description:    Calculate H --> H = (B - A) / (N - 1). Re-asking if undivisable. ---> Should we move it to function GetStepInt(maxStep)?
 *
 * Parameters:	    
 *					A = starting x value,
 * 					B - stopping x value, 
 *  				N = steps  in function argument
 * 					maximum allowed nr of steps. (MAX_STEP_NR)
 * 
 * Return:         	double: size of the step (i.e distance/difference between x0 and x1)
**/
double CalcH(double startValue, double stopValue, int stepValue)
{
	return (double)(stopValue - startValue) / (stepValue - 1); /** return valueH; **/
}

/**
 * Description:     Populate array of Xs and get the length of the array.
 *
 * Parameters:	    array of Xs, starting X, ending X, step count/value
 * 					value of H (look CalcH function)
 * 					maximum nr of allowed steps
 * 					boolean to notify in results, that we crossed max nr of allowed steps. 
 * 
 * Return:          integer: length of array X.
**/
int GetArrayX(double xArray[], double startValue, int stepValue, double valueH)
{
	int xArrLenCnt = 0;
	double valueX = 0.00;
	int i = 0;

	for (i = 0; i < stepValue; i++)
	{
		valueX = (double)(startValue + (xArrLenCnt * valueH));	/** converting int 'cnt' into double. **/
		xArray[xArrLenCnt] = valueX;	/** storing x (smaller-equal of stopValue) into array as position 'cnt' **/
		xArrLenCnt++;	/** incrementing count. **/

	}
	/** in this function I place valueX per iteration into xArray until limit (either valueX > stopValue or  **/
	return xArrLenCnt-1;	
}
/**
 * Description:    Populate array of Ys to the length of array X
 *
 * Parameters:	   array of Ys, array of Xs, length of array X
 * 
 * Return:         integer: length of array of Ys
**/
int GetArrayY(double yArray[], double xArray[], int xArrLenCnt)
{
	double dividend, divisor;
	double valueX = 0.00;
	double valueY = 0.00;

	int yCnt = 0;
	int i = 0;
	for (i = 0; i <= xArrLenCnt; i++)
	{
		/** Taking valueX from array, calculating valueY based on valueX **/
		valueX = xArray[i];	
		dividend = (2 * valueX) + 1;
		divisor = sqrt((pow(((2 * pow(valueX, 2) + 3*valueX + 4)), (double)3)) - 7);
		valueY = (dividend / divisor); 
		
		/** Populating yArray at index 'i' with calculated valueY **/
		yArray[yCnt] = valueY;
		yCnt++;
	}
	return yCnt-1;
}
/**
 * Description:    Print the Table in format with results.
 *
 * Parameters:	   array of Xs, array of Ys, size of step (H),
 * 				   length of array Y,
 *  
 *				   booleanTag (whether we have crossed Max allowed step nr)
 * 
 * Return:         -
**/
void PrintTable(double xArray[], double yArray[], int yArrLenCnt, int stepValue)
{
	char *columnHeader[] = {"ind", "X", "Y" };

	printf("\n---------------------------------");
	printf("\n----------- RESULTS -------------");
	printf("\n---------------------------------");
	printf("\n-- | %3s | %7s | %7s | --", columnHeader[0], columnHeader[1], columnHeader[2]);
	printf("\n---------------------------------");
	int i = 0;
	for (i = 0; i <= yArrLenCnt; i++)  /** Modify?**/
	{
		/** Print results, and call array on specific position/index **/
		printf("\n-- | %3d | %7.3lf | %7.3lf | --", i+1, xArray[i], yArray[i]);
	}
	printf("\n---------------------------------\n");
	
	/** Inform user that we limit the number of results displayed**/	
	if (i < stepValue)
	{
		printf("\nError! \nWe are not allowed to calculate more than %d steps of X! \nYour step input '%d' is changed to maximum of '%d'.\n", MAX_STEP_NR, stepValue,  MAX_STEP_NR);
	}
		
}
