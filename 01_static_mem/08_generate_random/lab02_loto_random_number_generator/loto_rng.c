#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define TOTAL_LOTTO 10  /* lototroni poolt genereeritavate numbrite arv */
#define TOTAL_USR 6     /* kasutaja poolt sisestavate numbrite arv */

#define BALL_MIN 1	    /* vähim lubatud lotonumber */
#define BALL_MAX 10     /* maksimaalne lubatud lotonumber */

#define NOT_ALREADY_WON_USER_NR 0
#define ALREADY_WON_USER_NR 1

#define SEED 100

void CollectUserNums(int nums[], int len);
int GetUserNumbInRange(int min, int max);
bool IsNumbUnique(int num, int nums[], int len, char errorPrompt[]);
void GenerateLotteryNumbers(int nums[], int len);
int GenerateRandomNum(int min, int max);
void PrintNumbers(int nums[], int len, char prompt[]);
int FindMatchCount(int lotteryNumbers[], int lenLottery, int userNumbers[],
                   int lenUser, int boolArray[]);
bool IsNumInArray(int nums[], int len, int num, int boolArray[]);

int main(void)
{
    /* 0. Deklareeri kõik oma vajalikud muutujad */
    int lotteryNums[TOTAL_LOTTO] = {0};
    int userNums[TOTAL_USR] = {0};
    
    /** 1. Kutsu funktsioon kasutaja arvude lugemiseks (CollectUserNums) **/
	CollectUserNums(userNums, TOTAL_USR);
    
    /** 2. Kutsu funktsioon lotoarvude genereerimiseks 
     * (GenerateLotteryNumbers) **/
    GenerateLotteryNumbers(lotteryNums, TOTAL_LOTTO);
    
    /** 3.1. Kutsu funktsioon kasutaja väljastamiseks (PrintNumbers) 
    * 3.2. Kutsu funktsioon kasutaja
     *      võidunumbrite väljastamiseks (PrintNumbers) **/
    PrintNumbers(userNums, TOTAL_USR, "\n\nUser numbers are\n");

    PrintNumbers(lotteryNums, TOTAL_LOTTO, "\nLottery numbers are\n");
    
    /** 4. Kutsu funktsioon kattuvate numbrite leidmiseks 
     *    ja kuvamiseks (FindMatchCount) **/
    int booleanArray[TOTAL_LOTTO] = {0};
    int matchingCnt = FindMatchCount(lotteryNums, TOTAL_LOTTO, 
									  userNums, TOTAL_USR, booleanArray);
    
    /** 5. Kuva lõppjäreldus - selle võid siin teha või uue funktsiooni luua **/
	printf("\nMatched %d out of %d!\n", matchingCnt, TOTAL_USR);
	
	if (matchingCnt == 0)
		printf("\nNone of the numbers matched. Better luck next time!\n");
    else if (matchingCnt == TOTAL_USR)
		printf("\nCongratulations! You won the jackpot!\n");

    return 0;
}

/**
 * Funktsioon loeb sisse kasutaja poolt antavad numbrid. Funktsioonis
 * ise lugemiskäske ei ole, vaid funktsioon kutsub esile järgmise funktsiooni
 * GetUserNumbInRange(), et lugeda ÜKS arv sisse ning salvestab tagastatud
 * väärtuse massiivi. Seda tehakse tsüklis len arv kordi.
 */
void CollectUserNums(int nums[], int len)
{
	for (int i = 0; i < len; i++)
	{
		
		printf("Enter lottery number [%d ... %d] (%d / %d): ",
					BALL_MIN, BALL_MAX, i+1, TOTAL_USR);
		do
		{
			nums[i] = GetUserNumbInRange(BALL_MIN, BALL_MAX);
			
			/** IMPORTANT PROGRESS: array length is i!!!)**/
			if (IsNumbUnique(nums[i], nums, i,
				"You've already entered this number! Retry: "))
				break;
		}
		while(1);
		
	}
}

/**
 * Funktsioon loeb kasutajalt ühe arvu. Kontrollitakse, et arv oleks vahemikus
 * min ja max. Otspunktid on mitteranged ehk min ja max on samuti lubatud.
 * Funktsioon küsib arvu senikaua, kuniks sisestus jääb
 * etteantud vahemikku, seejärel tagastab väärtuse.
 */
int GetUserNumbInRange(int min, int max)
{
	int num = 0;	// NB! BALL_MIN = 1; but we zero-initalize for security 
	
	while(1)
	{
		scanf("%d", &num);
		if (num >= min && num <= max) // BALL_MIN = 1; BALL_MAX = 25;
			break;
		else
			printf("\nInvalid number! Retry: ");	// continue
	}
	return num;
}
/** 
 * Funktsioon kontrollib kasutajalt ühte arvu. Kontrollitakse, et arv
 * ei oleks juba kasutaja poolt valitud.
 */
bool IsNumbUnique(int num, int nums[], int len, char errorPrompt[])
{
	for (int i = 0; i < len; i++)
	{
		if (num == nums[i])
		{
			printf(errorPrompt); //~ printf("You've already entered this number! Retry: ");
			return false;
		}
	}
	return true;
	
}


/**
 * Funktsioon trükib kaasa antud massiivi (nums) väärtused ühele reale, jättes
 * iga numbri vahele tühiku. Massiivi pikkuseks on len. Numbrite väljatrükile
 * järgneb reavahetus. 
 */
void PrintNumbers(int nums[], int len, char prompt[])
{
    printf("%s", prompt);
    for (int i = 0; i < len; i++)
    {
		printf("%d ", nums[i]);
	}
	printf("\n");
}

/**
 * Funktsioon genereerib lotonumbreid ja salvestab need massiivi.
 * Funktsiooni sees ise numbrit ei genereerita, vaid kutsutakse välja vastav
 * järgnev funktsioon GenerateRandomNum(), mis tagastab juhusliku numbri.
 * Tagastatud number salvestatakse massiivi
 *
 * Midagi ekraanile kuvada siin funktsioonis ei tohi.
 */
void GenerateLotteryNumbers(int nums[], int len)
{
	srand(time(NULL));
	//~ for (int i = 0; i < len; i++)
	//~ {
		//~ nums[i] = GenerateRandomNum(BALL_MIN, BALL_MAX);
	//~ }
	
	for (int i = 0; i < len; i++)
	{
		do
		{
			nums[i] = GenerateRandomNum(BALL_MIN, BALL_MAX);
			
			if (IsNumbUnique(nums[i], nums, i, "")) // print nothing here.
				break;
		}
		while(1);
	}
}

/**
 * Antud funktsioon genereerib ühe juhuarvu. Juhuarv genereeritakse vahemikus
 * min .. max, kusjuures otspunktid on lubatud. Genereeritud arv tagastatakse.
 *
 * Üldvalem: rand() % unikaalsete_tulemuste_arv + vähim_lubatud_arv
 */
int GenerateRandomNum(int min, int max)
{
	/** Sanity check **/
	//~ int result = 1;
	
	/** check 0 -2 **/
	//~ int result = rand() % 3;
	
	//~ int result = rand() % (max - min + 1) - min + 1;  //~ // for range -5...5 (included) = rand() % (max - min + 1) - min;
	int result = rand() % (max - min + 1) + min;  //~ // for 1!...25 we must use (rand % 25) + min
	return result;
}

/**
 * Funktsioon võtab endale 2 massiivi ja nende massiivide pikkused.
 * Funktsiooni eesmärgiks on teada saada mitu numbrit massiivides osutuvad
 * kattuvateks. Ühe massiivi numbri esinemist teises massiivis kontrollitakse
 * kasutades funktsiooni IsNumInArray(). Kattuvuste arv tagastatakse.
 *
 * Kattuvuse leidmisel trükitakse kattuv number välja siin funktsoonis.
 */
int FindMatchCount(int lotteryNumbers[], int lenLottery, int userNumbers[],
                   int lenUser, int boolArray[])
{
	int matchCnt = 0;
	for (int i = 0; i < lenUser; i++)
	{
		if (IsNumInArray(lotteryNumbers, lenLottery, userNumbers[i], boolArray))
		{	
			printf("\nWinning number: %d", userNumbers[i]);
			matchCnt++;
		}
	}
	return matchCnt;
}

/**
 * Järgnev funktsioon kontrollib kas muutuja value väärtus
 * esineb juba massiivis nums või mitte. Nums massiiv pikkus on len.
 * Tagastatakse vastus kas number oli massiivis või mitte.
 *
 * Midagi ekraanile kuvada siin funktsioonis ei tohi.
 */
bool IsNumInArray(int nums[], int len, int value, int boolArray[])
{
	for (int i = 0; i < len; i++)
	{
		if (value == nums[i])	// cannot do in loops: //~ return value == nums[i];	
		{
			/** Checking if user's number already matched to previous lotto numbers **/
			if (boolArray[i] == ALREADY_WON_USER_NR)	/** defined as '1' (true) **/
			/** Created new array in main, brought from Function (int FindMatchCount(...))
			 *  to store True(1) and False(1) as value.
			 *  index plays a crucial role here: mapping two ARRAYS **/
			{
				continue;	/** skips to next lotto nr, because already user's nr won. **/
			}
			else
			/** User's number matches, and has NOT YET matched with previous lotto numbers.**/ 
			{	
				boolArray[i] = ALREADY_WON_USER_NR; /** assigning defined boolean, i.e ([i] = 1), where 1 (true) is "ALREADY_WON_USER_NR" **/
				return true;
			}
		}
	}
	return false;
}

/** 
 * 							Function "IsNumInArray" loop iterations (j)	
 * 							[j = 0]					[j = 1]					[j = 2]					[j = 3]		 			[j = 4]
 * 							= 0						= 1						= 2						= 1						= 2
 * ---------------------------------------------------------------------------------------------------------------------------------
 * "FindMatchCount"		|
 * loop iterations (i)	|
 * 						|
 * 						|
 * [i = 0]				|	i=1 j=0 				i=1 j=1
 * = 1					|	1 == 0 -> F				1 == 1 ->T 
 * 						|	j++						boolArray[j=1] == TRUE(1) -> F!
 * 						|							thus, before break-out, we	
 * 						|							boolAarray[j=1] = TRUE(1)
 * 						|							now, breaked out
 *---------------------	|----------------------------------------------------------------------------------------------------------
 * [i = 1]				|	i=1 j =0				i=1 j=1					i=1 j=2
 * = 2					|	2 == 0 -> F	-> j++		2 == 1 -> F -> j++		2==2 -> T -> boolArray[j=1] = TRUE -> break-out
 * 	----------------	|----------------------------------------------------------------------------------------------------------
 * [i = 2]				|	i=2 j=0					i=2 j=1					repeat j++!			i=2 j=3
 * = 1					|	1 == 0 -> F				1 == 1 -> T				...!!!				1==1 -> T
 * 						|	j++						boolArray[j=1] == TRUE(1) -> T !!!			boolArray[j=1] == TRUE -> f
 *						|							thus, continue -> j++						boolAarray[j=1] = TRUE(1)
 * 						|																		now, breaked out
 * ---------------------|----------------------------------------------------------------------------------------------------------
 * [i = 3]				|	i = 3 j=0
 * = 0					|	0 == 0 -> T
 * 						|	boolArray[j=0] == TRUE(1) -> F!
 * 						|	thus, before break-out, we	
 * 						|	boolAarray[j=0] = TRUE(1)
 * 						|	now, breaked out
 * 						|	
 * ---------------------|-------------------------------------------------------------------------------------------------------------
 * [i = 4]				|	i = 4 j = 0				i = 4 j = 1				i=4 j=2
 * = 2					|	2 == 0 -> F				2 == 1 ->				2 == 2 -> T				
 * 						|	j++						j++						boolArray[j=2] == TRUE(1) -> F!
 * 						|													thus, before break-out, we	
 * 						|													boolAarray[j=2] = TRUE(1)
 * 						|													now, breaked out
 * --------------------------------------------------------------------------------------------------------------------------------------
 * **/					
