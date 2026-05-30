#include <stdio.h>
#include <string.h>

#define LEN_STR 128
#define FINAL_LEN_STR 256

#define MATCH 1
#define NOTMATCH 0

#define VALIDLOGIN 1
#define INVALIDLOGIN 0

void GetString(char str[], int n);
void DebugString(char str[]);
void PromptString(char str[], int n, char prompt[]);

int GetLength(char str[]);
int IsInputInPhrase(char str[], char substr[]);

int PromptPassword(char correctPassword[], int maxLen);

//~ void FormulateSentence(void);
void FormulateSentence(char sentence[LEN_STR * 2 + 16]);
void CountAplhabeticalChars(char sentence[LEN_STR * 2 + 16]);

int main(void)
{
	/** Step 04 start **/
	char correctPassword[LEN_STR] = "JohnSmith";

	if (!PromptPassword(correctPassword, LEN_STR))
		return 1;
	else
	/** Step 04 end **/
	{
		/** Step 01 start **/
		char sentence[LEN_STR];
		// Call this function, do not write scanf's!
		PromptString(sentence, LEN_STR, "Enter a sentence: ");
		printf("Sentence: \"%s\" \n", sentence);
		/** Step 01 end **/
		
		/** Step 02 start **/  
		int sentenceLen = GetLength(sentence); // int sentenceLen = strlen(sentence);
		printf("The sentence lenght is: %d\n", sentenceLen);
		/** Step 02 end **/
		
		
		/** Step 03 start **/
		char searchPhrase[LEN_STR];
		PromptString(searchPhrase, LEN_STR, "Enter a search phrase: ");
		
		/** Display length of search phrase for DEBUGGING**/
		int searchLen = GetLength(searchPhrase); // int sentenceLen = strlen(sentence);
		printf("The sentence lenght is: %d\n", searchLen);

		/** See if search-phrase is in sentence -> strstr(string, substring) **/
		if (IsInputInPhrase(sentence, searchPhrase))
			printf("Yes, the search phrase existed in previously entered sentence!\n");
		else
			printf("No, the search phrase DID NOT exist in previously entered sentence!\n");
		/** Step 03 end **/
		
		/** Step 05 start **/
		char newSentence[LEN_STR * 2 + 16];
		FormulateSentence(newSentence);
		/** Step 05 end **/
		
		CountAplhabeticalChars(newSentence);
		
		return 0;
	}
}

void PromptString(char str[], int n, char prompt[])
{
	// version 1:
	puts(prompt);
	
	// version 2:
	//~ printf("%s", prompt);
	
	GetString(str, n);
}

void GetString(char str[], int n)
{
	// Read the string from keyboard
	fgets(str, n, stdin);
	
	// TODO: Find the length of the actual string we just read
	size_t len = strlen(str); // replace with GetLenght Fn?
	
	// TODO: Write the string terminator in place of the newline to fix the string
	str[len-1] = '\0'; // Between ' ' (bc \0 is 1 byte, char; DO NOT " ")
	
	DebugString(str);
}

void DebugString(char str[])
{
    int i = 0;
    printf("String is: '%s'\n", str);
    while (str[i] != '\0')
    {
        printf("str[%d] = %3hhu %c\n", i, str[i], str[i]);
        i++;
    }
    printf("\n");
}

int GetLength(char str[])
{
	//~ size_t len = strlen(str);
	int len = strlen(str);
	return len;
}

int IsInputInPhrase(char str[], char substr[])
{
	// edge-case:
	 //~ if (strlen(substr) > strlen(str))
	if (strstr(str, substr) != NULL)
	{
		return MATCH;
	}
	else
	{
		return NOTMATCH;
		//~ return strstr(); // will give
	}
}

int PromptPassword(char correctPassword[], int maxLen)
{
    char userEnteredPassword[maxLen];
    int cnt = 0;
    
    // Write your loop for password prompt here
    while (1)
    {
		PromptString(userEnteredPassword, maxLen, "Enter the correct password: ");
		if (strcmp(userEnteredPassword, correctPassword) != 0)
		{
			puts("Incorrect password! Try again.");
			
			cnt++; /** increment attempts user tried to log-in**/
			/** Limit of allowed login attempts:**/
			if (cnt >= 3)
			{
				puts("Exceeded limit of login attempts. Exiting out.");
				return INVALIDLOGIN;
			}
		}
		else
		{
			puts("Correct password. Welcome!");
			return VALIDLOGIN;
		}	
	}
}

void FormulateSentence(char sentence[LEN_STR * 2 + 16])
{
    // String where the final sentence will be held
    // should we enlargen FINAL_LEN_STR this by 2xLEN_STR + "is an ___ person"?
    
	//~ char newSentence[LEN_STR * 2 + 16];
	
    // Strings for the two user-entered words
    
    char name[LEN_STR];
    char adjective[LEN_STR];
    
    // Prompt the user for the two words
	
	PromptString(name, LEN_STR, "Enter a name: ");
	PromptString(adjective, LEN_STR, "Enter an adjective: ");
 
    // Formulating the final sentence
	strcat(sentence, name);
	strcat(sentence, " is a "); // should remove \0?
	strcat(sentence, adjective);
	strcat(sentence, " person!"); // should remove \0?
 
    // Print the final formulated sentence
    printf("Result: %s\n", sentence);
}

void CountAplhabeticalChars(char sentence[LEN_STR * 2 + 16])
{
	float percentage = 0.0f;
	int count = 0;
	int alphaCount = 0;
	
	//version 1:
	int len = strlen(sentence); 
	for (int i = 0; i < len; i++)
		if ((sentence[i] == '?') ||
			(sentence[i] == '\'') ||
			(sentence[i] == '.') ||
			(sentence[i] == ';') ||
			(sentence[i] == ' ') ||
			(sentence[i] == '!'))
		{
			printf("Found a non-character in sentence.\n");
			count++;			
		}
		else
			alphaCount++;
	
	printf("Alphabetical characters count is: %d\n", alphaCount);
	percentage = (float)count / len * 100;
	printf("Non-alphabetical characters: %d\n", count);
	printf("Percentage of other characters: %.2f\% \n", percentage);
}
