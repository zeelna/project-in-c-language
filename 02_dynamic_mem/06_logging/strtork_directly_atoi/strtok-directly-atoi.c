#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ONE "1,2,3,4"
#define TWO "5 6 7 8"
#define THREE "9,10,11,12,13"

#define STR_LEN 20
#define ARR_LEN 7


void PrintArray(char stringArr[ARR_LEN][STR_LEN], int len);


int main(void)
{
	char stringArr[ARR_LEN][STR_LEN] = {0};
	
	strcpy(stringArr[0], ONE); 
	strcpy(stringArr[1], TWO); 
	strcpy(stringArr[2], THREE); 
	
	//~ int len = 2;
	
	/** Exclude the null-terminator.**/
	//~ int len = sizeof(stringArr) / sizeof(stringArr[0]);
	int len = 3;
	PrintArray(stringArr, len);

	int intList[10] = {0};
	char str[STR_LEN] = "12,10,9,13,0";
	
	printf("Convertint string '%s' into int[]: \n", str);
	int j = 0; // DO NOT FORGET ==> for intList index incrementing
	
	/** Return first token with strtok() --> as-if 'getFirstToken'**/
	char delimiter[4] = " , ";
    char* token = strtok(str, delimiter);
 
	/** Keep printing tokens while one of the delimiters present in str[]. Checks for delimiter**/
    while (token != 0) //  while (token != NULL)
    {
        
		/** Intemediary: atoi() ==> convert string to 'int' **/
		intList[j] = atoi(token);
		printf("DEBUG [%d]: %d\n", j, intList[j]); /** & store to int[]**/
		
		printf("DEBUG [%d]: %d + %d = %d\n", j, intList[j], 3 , intList[j] + 3); /** & store to int[]**/
        
        
		/** // Use of strtok,  go through other tokens **/
        token = strtok(0, delimiter);    // token = strtok(NULL, delimiter); 
        
	
        j++;   // DO NOT FORGET ==> for intList index incrementing
    }
    /** ending main.**/
    return 0;
}

void PrintArray(char stringArr[ARR_LEN][STR_LEN], int len)
{
	//~ int nString = sizeof(stringArr) / sizeof(len);
	for (int i = 0; i < len; i++)
	{
		printf("DEBUG: [%d]: '%s' \n", i + 1, stringArr[i]);
	}
	putchar('\n');
}



