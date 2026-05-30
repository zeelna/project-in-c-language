

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include <limits.h>

// pinu piir
#define STACK_SIZE 10
#define STACK_EMPTY 0

#define NOT_EXIT 0
#define EXIT 1

#define MENU_OPTION_MIN 0
#define MENU_OPTION_MAX 9

#define INT_SIZE 13

// INT_MIN: -2147483648
// INT_MAX: 2147483647

typedef struct
{
	
	int *data; // pinus olevad andmed
	int size; // pinu praegune suurus / pinuviit
} stack;

void DebugInValidStackExamples();

void DebugStack(stack st);

bool isPushable(stack *st);
bool isPeekable(stack *st);

int Pop(stack *st);
void Push(stack *st, int val);


int Peek(stack *st);

void Duplicate(stack *st);

bool IsValidInteger(char numString[INT_SIZE]);

bool IsValidNegInteger(char numString[INT_SIZE]);

int GetIntInRange(int min, int max, char *prompt);
int Menu(void);
int AskInt(char *prompt);



int main(void)
{
	//~ DebugInValidStackExamples();
	
	stack myStack = {.data = NULL,
					 .size = 0};	
		
	int menuOption = -1;
	int exit = NOT_EXIT;
    while (exit == NOT_EXIT) // (!exit)
    {
        //~ menuOption = Menu();
        switch (menuOption)
        {
			case 0:
				puts("Exiting program...");
				exit = EXIT;
				break;
            case 1:
				int pushedValue = GetIntInRange(INT_MIN + 1, INT_MAX - 1, "Choose a number to push to Stack");
				Push(&myStack, pushedValue);
				
				break;
			case 2:
				if (isPeekable(&myStack)) /** In-built stackunderflow / stack NULL statements**/
				{
					int poppedValue = Pop(&myStack); // pop only one in stack ==> double free or corruption (out)
					printf("Got %d\n", poppedValue);
				}

				break;	
				
			case 3:
				if (isPeekable(&myStack)) /** In-built stackunderflow / stack NULL statements**/
				{
					int peekedValue = Peek(&myStack); // peek: Got = 0.
					printf("Got %d\n", peekedValue);
				}
				
				break;	
			case 4:
				puts("Swap...");
				break;
				
			case 5:
				puts("Duplicate...");
				if (isPeekable(&myStack) && isPushable(&myStack)) /** In-built stackunderflow / stack NULL statements**/
				{
					Duplicate(&myStack);
				}
				break;	
				
			case 9:
				DebugStack(myStack);
				break;
				
			default:
				puts("Please try again, this menu option does not exist.");
				break;
		}
		if (!exit)
		{
			menuOption = Menu();
		} // end of if !exit
	} // end of while
	
					
	return EXIT_SUCCESS;
}
/**
 * Description:    Displays the possible menu options to the user,
 *                 allows to select an action to perform.
 *
 * Parameters:     None
 *
 * Return:         Menu item number selected
 */
int Menu(void)
{
    int selection;
    putchar('\n');
    puts("Select Your action!");
    puts("1 - Push");
    puts("2 - Pop");
    puts("3 - Peek");
    puts("4 - Swap");
    puts("5 - Duplicate");
    puts("9 - DEBUG");
    puts("0 - exit");
    selection = GetIntInRange(MENU_OPTION_MIN, MENU_OPTION_MAX, "Choose menu option. ");
    return selection;
}

/**
 * Description:    Asks the user for an integer in between the given limits.
 *                 Reprompts if input is out of bounds.
 *
 * Parameters:     min - lower limit for the user input (inclusive)
 *                 max - upper limit for the user input (inclusive)
 *
 * Return:         Number within the specified limits
 */
int GetIntInRange(int min, int max, char *prompt)
{
    int num = 0;
    do
    {
        num = AskInt(prompt);
        if (num < min || num > max)
        {
            printf("\nRetry! Input must be in between %d and %d. \n", min, max);
        }
    }
    while (num < min || num > max);
	putchar('\n');
    return num;
}

/**
 * Description:    Asks the user for an integer with custom prompt
 *                 Reprompts if input is contains symbol that is not a digit
 *
 * Parameters:     prompt - string of what is asked / prompted from user
 *
 * Return:         integer, sanitized from non-digits.
 */
int AskInt(char *prompt)
{
	char numString[INT_SIZE] = {0};
	while(1)
	{
		printf("%s\n> ", prompt); // todo: atoi
		scanf("%s", numString);
			
		//~ if (IsValidInteger(numString))
		if (IsValidNegInteger(numString))
		{
			break;
		}
		else
		{
			puts("Selected value is not a integer. Please try again.");
		}
	} // end of while-loop
	int desiredNum = atoi(numString);
	return desiredNum;
} // end of function

/** Description:    Check whether the Phone Screen Size contains
 *                  valid digits (0-9)
 * 
 *  Parameters:     numString as array of chars,
 *  Result:         boolean (true/false)
 **/
bool IsValidInteger(char numString[INT_SIZE])
{   
    /** Loop each char to verify all are numbers (or negative or decimal dot.)**/
    int n = (int)strlen(numString);
    for (int i = 0; i < n; i++)
    {
        /** Check if character is a digit
        * Hint: use isdigit() **/
        if (!isdigit(numString[i]))
        {
            return false;
        }
    }
    return true;
} // end of function

										
/** Description:    Check whether the integer
 *                  valid digits (0-9) and at most 1 - (hyphen / neg symbol)
 * 
 *  Parameters:     input as string
 *  Result:         boolean 
 **/
bool IsValidNegInteger(char numString[INT_SIZE])
{
    /** Look every char and find if numerical or not**/
    bool hyphenOccured = false;
    
    /** Loop each char to verify all are numbers (or negative or decimal dot.)**/
    int n = (int)strlen(numString);
    for (int i = 0; i < n; i++)
    {
        /** Check if character is a digit
        * Hint: use isdigit() **/
        if (!isdigit(numString[i]))
        {
            /** 1) If char is hyphen (negative symbol)
             *       and not yet occured, assign boolean-flag "hyphenOccured" = True
             *  2) if another char is hyphen, then hyphenOccured boolean is true,
             *       and will parse through isdigit() **/
            if (numString[i] == '-' && (!hyphenOccured))
            {
                hyphenOccured = true;
                continue;
            }
            return false;
        }
    }
    return true;
} // end of function



/** Description: 	Check DebugStack() function in different scenarios	
 * 					* size negative
 * 					* data not NULl, but size negative
 * 					* data NULL, but size positive
 * 					
 * 					P.S: Segmentation fault(core dumped) should be avoided.
 * 							* without .size and .data checks, can lead to.
 * 							* example: when .data == NULL && .size != 0
 *  
 * 	Parameters:		void
 *  Return			void
 **/
void DebugInValidStackExamples()
{
	stack myStackWrongSize = {.data = NULL,
					 .size = -2};				 
	DebugStack(myStackWrongSize);
	
	stack myStackDataNull = {.data = NULL,
					 .size = 2};		 
	DebugStack(myStackDataNull);
	
	int num = 3;
	int *vl = &num;
	stack myStackInsantiated = {.data = vl,
					 .size = -2};	 
	DebugStack(myStackInsantiated);	
}

/** Description: 	Display information about the stack-data structure 		
 * 					(size, pointer to data, and values insize)
 * 					
 * 					P.S: Segmentation fault(core dumped) can be thrown
 * 							* if stack instantiated 
 * 							when .data == NULL && .size != 0
 *  
 * 	Parameters:		pointer to stack	
 * 
 *  Return			void
 **/
void DebugStack(stack st)
{
    printf("DEBUG\n");
    printf("\tStack size: %d\n", st.size);
    printf("\tStack limit: %d\n", STACK_SIZE);
    printf("\tData pointer: %p\n", st.data);
    
    if (st.size < STACK_EMPTY)
		printf("\tValues: None, stack size is non-positive.\n");
	else if (st.data == NULL)
		printf("\tValues: None, data pointer is NULL.\n");
    else 
    {	
		printf("\tValues: ");
		for (int i = st.size - 1; i >= 0; i--)
		{
			printf("%d ", st.data[i]);
		}
		printf("\n\n");
	}
}

/**
 * Function to check if allocated memory can be freed without memory leaks.
 **/
void SafeFree(void **p)
{
	if (p != NULL && *p != NULL)
	{
		free(*p);
		*p = NULL;
	}
} // end of function




 
/** Description: 	null-stack check (cannot operate with null-pointer stack)
 * 					
 * 					* stack underflow checks 
 * 						* (cannot pop when stack empty)
 * 						* (size non-positive)
 * 					
 * 	Parameters:		pointer to stack	
 * 
 *  Return			boolean - there exists an element
 **/
bool isPeekable(stack *st)
{
	 // veendun, et pinu edastati
	if (st == NULL) // pinu ennast ei ole
	{
		fprintf(stderr, "ERROR: No stack!\n");
		return false;
	}
	
	/** veendu, et pinu ei ole alatäitunud **/
	/** Pinu alatäitumise kontroll **/
	if (st->size <= STACK_EMPTY || st->data == NULL)
	{
		fprintf(stderr, "ERROR: Stack underflow!\n");
		return false;
	}
	return true;
}

 
/** Description: 	null-stack check (cannot operate with null-pointer stack)
 * 					
 * 					* stack overflow checks 
 * 						* (cannot pop when stack empty)
 * 						* (size non-positive)
 * 					
 * 	Parameters:		pointer to stack	
 * 
 *  Return			boolean - there exists an element
 **/
bool isPushable(stack *st)
{
// veendun, et pinu edastati
	if (st == NULL) // pinu ennast ei ole
	{
		fprintf(stderr, "ERROR: No stack!\n");
		return false;
	}
	
	// veendu, et pinu ei ole ületäitunud.
	// Pinu ületäitumise kontroll
	if (st->size >= STACK_SIZE)
	{
		fprintf(stderr, "ERROR: Stack overflow!\n");
		return false;
	}
	return true;
}
/** Description: 	Remove the most-top/recent element in stack	
 * 					Stack .size and .data will be updated, with removed element  
 * 
 * 					* null-stack check (cannot operate with null-pointer stack)
 * 					
 * 					* stack underflow checks 
 * 						* (cannot pop when stack empty)
 * 						* (size non-positive)
 * 					
 * 	Parameters:		pointer to stack	
 * 
 *  Return			integer (Stack datatype: Last in, First out).
 * 					Popping the most recent/top element in stack.
 **/
int Pop(stack *st)
{
	// veendun, et pinu edastati
	if (st == NULL) // pinu ennast ei ole
	{
		fprintf(stderr, "ERROR: No stack!\n");
		//~ return;
		exit(EXIT_FAILURE);
	}
	
	/** veendu, et pinu ei ole alatäitunud **/
	/** Pinu alatäitumise kontroll **/
	if (st->size <= STACK_EMPTY || st->data == NULL)
	{
		fprintf(stderr, "ERROR: Stack underlow!\n");
		//~ return;
		exit(EXIT_FAILURE);
	}
	
	int poppedElement = *(st->data + st->size - 1);
	
	if (st->size == 1) 
	{
		//~ SafeFree((void **) &st[st->size - 1].data);
		SafeFree((void **) &st[0].data);
		st->size--;
		//~ SafeFree((void **) &st);
	}
	else
	{
		// loo ajutine suurus (newSize), mis on täpselt 1 elemendi võrra väiksem.
		unsigned newSize = (unsigned) st->size - 1;
		
		/** Pseudokood n-1 realloc.**/
		int *pTemp = (int *)realloc(st->data, newSize * sizeof(int));
		if (pTemp == NULL)
		{
			fprintf(stderr, "ERROR: Couldn't reallocate memory for stack!\n");
			//~ return;
			exit(EXIT_FAILURE);
		}
		
		// sünkroniseerimine algse pinuviida uue (vähendatud suurusega) pinuviidata 'pTemp'
		st->data = pTemp;
		// vähendame pinuviita (toimib indeksina)
		st->size--;
	}
	
	return poppedElement;
} // end of POP

/** Description: 	Returning the most top/recent element in stack (LIFO)
 * 						* LIFO = Last In, First Out.
 * 
 * 
 * 					* null-stack check (cannot operate with null-pointer stack)
 * 					
 * 					* stack overflow checks 
 * 						* (cannot push when no more memory can be allocated)
 * 					
 * 	Parameters:		pointer to stack	
 * 
 *  Return			integer (Stack datatype: Last in, First out).
 * 					Displaying the first element without removing it.
 **/
int Peek(stack *st)
{	
	int peekedElement = *(st->data + st->size - 1);
	return peekedElement;
}

/** Description: 	Adding an element to Stack (Abstact type (LIFO): Last in, First out)
 * 					Stack .size and .data will be updated
 * 						.size will be incremented
 * 						.data will be enlarged by dynamic memory (n+1 pseudocode)
 * 
 * 					* null-stack check (cannot operate with null-pointer stack)
 * 					
 * 					* stack overflow checks 
 * 						* (cannot push when no more memory can be allocated)
 * 					
 * 	Parameters:		pointer to stack	
 * 
 *  Return			integer (Stack datatype: Last in, First out).
 * 					Popping the most recent/top element in stack.
 **/
void Push(stack *st, int val)
{
	// veendun, et pinu edastati
	if (st == NULL) // pinu ennast ei ole
	{
		fprintf(stderr, "ERROR: No stack!\n");
		return;
	}
	
	// veendu, et pinu ei ole ületäitunud.
	// Pinu ületäitumise kontroll
	if (st->size >= STACK_SIZE)
	{
		fprintf(stderr, "ERROR: Stack overflow!\n");
		return;
	}
	
	// Valmistame pinu ette uue liikme jaoks, s.t laiendamine pinu
	unsigned newSize = (unsigned)st->size + 1;
	int *pTemp = (int *)realloc(st->data, newSize * sizeof(int));
	if (pTemp == NULL)
	{
		fprintf(stderr, "ERROR: Couldn't allocate memory for stack!\n");
		return;
	}
	st->data = pTemp;
	
	// Lisame andmed pinusse ja suurendame pinuviita (toimib indeksina)
	st->data[st->size] = val;
	st->size++;
	
	
} // end of Push

void Duplicate(stack *st)
{
	Push(st, st->data[st->size - 1]);
}
