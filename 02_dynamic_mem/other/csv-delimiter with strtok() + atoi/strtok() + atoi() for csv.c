#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DEBUG 1

#define ONE "1,2,3,4"
#define TWO "5 6 7 8"
#define THREE "9,10,11,12,13"

#define STR_LEN 20
#define ARR_LEN 7


int StringToIntArray(char string[STR_LEN], int intArr[STR_LEN]);

void PrintArray(char stringArr[ARR_LEN][STR_LEN], int len);

void PrintIntArray(int *intArr, int len);

int main(void)
{
	char stringArr[ARR_LEN][STR_LEN] = {0};

	strcpy(stringArr[0], ONE); 
	strcpy(stringArr[1], TWO); 
	strcpy(stringArr[2], THREE); 
	
	//~ int len = sizeof(stringArr) / sizeof(stringArr[0]); // wrong
	int len = 3;
	
	puts("Unconverted array:");
	PrintArray(stringArr, len);
	
	/** Main body **/
	int intArr[STR_LEN] = {0};
	char string[STR_LEN] = "12,10,9,13,0";
	
	/** Convert string: "2,1,9,3" int int:[2, 1, 9, 3]. Return length of int[]**/
	int intArrLen = StringToIntArray(string, intArr);
	/** Function implements strtok() split str by ",".  **/
		/** Look inside to change delimiter**/
	
	puts("Int converted array:");
	PrintIntArray(intArr, intArrLen);
	printf("'intArrLen': %d \n", intArrLen);
	
    /** ending main.**/
    return 0;
}

void PrintArray(char stringArr[ARR_LEN][STR_LEN], int len)
{
	for (int i = 0; i < len; i++)
	{
		printf("DEBUG: [%d]: '%s' \n", i + 1, stringArr[i]);
	}
	putchar('\n');
}


void PrintIntArray(int *intArr, int len)
//~ void PrintIntArray(int intArr[STR_LEN], int len)
{
	for (int i = 0; i < len; i++)
	{
		#ifdef DEBUG
		printf("DEBUG [%d]: %d + %d = %d. Successfully does 'addition', thus int.\n", i, *(intArr + i), 3 , *(intArr +i) + 3); /** & store to int[]**/
		#endif
		
		#ifndef DEBUG
		printf("%d ", *(intArr + i));
		//~ printf("%d ", intArr[i]);
		#endif
	}
	putchar('\n');
}

int StringToIntArray(char string[STR_LEN], int intArr[STR_LEN])
{
	/** Tip: [1 + STR_LEN / 2] <=== "2,1,9,3" is with len 7  
	 * 								[2, 1, 9, 3] with len 4**/
	
	printf("Convertint string '%s' into int[]: \n", string);
	int cnt = 0; // DO NOT FORGET ==> length of intArr.
	
	int *pIntArr = intArr; // Pointer initialization.
	
	/** Return first token with strtok() --> as-if 'getFirstToken'**/
	char delimiter[4] = " , ";
    char* token = strtok(string, delimiter);
 
	/** Keep printing tokens while one of the delimiters present in str[]. Checks for delimiter**/
    while (token != 0) //  while (token != NULL)
    {
		/** Intemediary: atoi() ==> convert string to 'int' **/
		*pIntArr = atoi(token);
		
		#ifdef DEBUG
		//~ printf("DEBUG [%d]: %d\n", cnt, *pIntArr); /** & store to int[]**/
		
		printf("DEBUG [%d]: %d + %d = %d. Successfully does 'addition', thus int.\n", cnt, *pIntArr, 3 , *pIntArr + 3); /** & store to int[]**/
        #endif
        
		/** // Use of strtok,  go through other tokens **/
        token = strtok(0, delimiter);    // token = strtok(NULL, delimiter); 
        
        cnt++;   // DO NOT FORGET ==> for intArr index incrementing
        pIntArr++; // DO NOT FORGET ==> move pointer to next location.
    }
    
    return cnt; /** lenght of intArr **/
}



