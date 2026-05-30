#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
 
/** Maximum file name length in modern systems **/
#define MAX_FILE_LEN 256

#define LIST_DATA {"csv", "xls", "xlsx", "ods"}
#define LIST_DOCUMENTS {"pdf", "doc", "docx", "rtf", "odt"}
#define LIST_IMAGES {"jpg", "jpeg", "png", "svg"}
#define LIST_CODE {"c", "h", "cpp", "hpp", "py"}
#define LIST_ARCHIVE {"zip", "rar", "7z", "tar", "gz"}
#define LIST_TEXT {"txt"}
#define LIST_OTHER // ? solve with  else-clause (not above NOR not NO_EXT)
#define LIST_NO_EXT {""}
//~ #define LIST_COUNT {}

enum FileCategory 
{
    CAT_DATA = 2,
    CAT_DOCUMENTS = 3,
    CAT_IMAGES = 4, 
    CAT_CODE = 1, 
    CAT_ARCHIVE = 0, 
    CAT_TEXT = 5, 
    CAT_OTHER = 6, 
    CAT_NO_EXT = 7, 
    CAT_COUNT
};

int GetLength(char *str);
void DebugString(char *str);
void FixTrailingNewline(char *str);
int GetLastDotPos(char *str); 
enum FileCategory FindFileCategory(char *extention);
void PrintResult(const char **categories, int *counters);

int main(void)
{		
    char name[MAX_FILE_LEN];
    int counters[CAT_COUNT] = {0};
    
    const char *categories[] = 
    {
			[CAT_ARCHIVE] = "Archives",
			[CAT_CODE] = "Code files",
			[CAT_DATA] = "Data",
			[CAT_DOCUMENTS] = "Documents",
			[CAT_IMAGES] = "Images",
			[CAT_TEXT] = "Text files",
			[CAT_OTHER] = "Other",
			[CAT_NO_EXT] = "No extension"
	};
		
    // Read in the name of a file with the extension until EOF occurs
    enum FileCategory fileCat;
    while (fgets(name, MAX_FILE_LEN, stdin) != NULL)
    {
		/** Step #1: Call a function to fix the trailing newline **/
		FixTrailingNewline(name); 
		//~ DebugString(name);		// printing the indexs and values.
	
        /** #2 Call a function to find the position of the last point **/
        int pointPos = GetLastDotPos(name); // Q1: (*name) or (name)
        
        /** #3 Call a function that finds the category type and store it.
        // This is the predefined function from the requirements!
        // Hint: think of what no point symbol in the string means!
        
        // Tip: This repeats everytime a file-string is found. **/
		if (pointPos != -1)
			fileCat = FindFileCategory(name + pointPos); 
		else
			fileCat = CAT_NO_EXT;

        // Increase the appropriate category counter
		counters[fileCat]++;
    }	
   
   
    /** Step #4: Call a function to print the results **/
	PrintResult(categories, counters);
    
    return EXIT_SUCCESS;
}

void PrintResult(const char **categories, int *counters)
{
	for (int i = 0; i < CAT_COUNT; i++) 
    {
		putchar('\n');
		printf("%13s: %d", *(categories)++, *(counters)++); 
		
	}
	putchar('\n');
}

/**
 * Description: Checks if a string is part of a list
 * 
 * Parameters:  listOfObject - list of strings to compare against
 *              n - number of strings in listOfObject
 *              object - string to check if it is a part of the list
 * 
 * Return:      true if it's part of the list, false if not
 */
bool IsTypeOfObject(const char *listOfObject[], int n, char *object)
{
    for (int i = 0; i < n; i++)
    {
		/** HOIATUS: strcmp tagastab 0 kui match, muu  kui palju nihkes matchist
		// seepärast paneme !strcmp
		// tingimuslause TRUE = 1
		// strcmp = 0 		!strcmp = 1, -1 jms. **/
        if (!strcmp(listOfObject[i], object))
            return true;
    }
    return false;
}
/**
 * Description: Identifies the type of extentsion/object based on preset lists.
 * 
 * Parameters:  extention - name of the extention
 * 
 * Return:      type of flying object
 */

enum FileCategory FindFileCategory(char *extention) 
{
	const char *dataExtentions[] = LIST_DATA;
	const char *docExtentions[] = LIST_DOCUMENTS;
	const char *imageExtentions[] = LIST_IMAGES;
	const char *codeExtentions[] = LIST_CODE;
	const char *archiveExtentions[] = LIST_ARCHIVE;
	const char *textExtentions[] = LIST_TEXT;
	
	int nData = sizeof(dataExtentions) / sizeof(char *);
	if (IsTypeOfObject(dataExtentions, nData, extention))
		return CAT_DATA;	
	
	int nDoc = sizeof(docExtentions) / sizeof(char *);
	if (IsTypeOfObject(docExtentions, nDoc, extention))
		return CAT_DOCUMENTS;
		
	int nImage = sizeof(imageExtentions) / sizeof(char *);
	if (IsTypeOfObject(imageExtentions, nImage, extention))
		return CAT_IMAGES;
	
	int nCode = sizeof(codeExtentions) / sizeof(char *);
	if (IsTypeOfObject(codeExtentions, nCode, extention))
		return CAT_CODE;
		
	int nArchive = sizeof(archiveExtentions) / sizeof(char *);
	if (IsTypeOfObject(archiveExtentions, nArchive, extention))
		return CAT_ARCHIVE;
		
	int nText = sizeof(textExtentions) / sizeof(char *);
	if (IsTypeOfObject(textExtentions, nText, extention))
		return CAT_TEXT;
		
	return CAT_OTHER;	
}


void FixTrailingNewline(char *str) 
{
		/** Step #1 Acquire length **/
		size_t len = strlen(str); 
		
		/** Step #2 Write the string terminator in place of the newline to fix the string **/
		str[len-1] = '\0'; // Between ' ' (bc \0 is 1 byte, char; DO NOT " ")
}

void DebugString(char *str)
{
    int i = 0;
    printf("String is: '%s'\n", str);
    while (*(str + i) != '\0')
    {
        printf("str[%d] = %3hhu %c\n", i, *(str + i), *(str + i));
        i++;
    }
    printf("\n");
}


int GetLastDotPos(char *str)
{
	int lastDotPos = -2;
	char *p = str;

	int i;
	for (i = 0; i < (int)strlen(str); i++)
	{
		if (*(p + i) != '.')   // if (str + i) != '.' // also works.
			continue;
		else 
			lastDotPos = i;
	}
	return (lastDotPos + 1);  // hardcode to return -1 if '.' does not occur.
}
