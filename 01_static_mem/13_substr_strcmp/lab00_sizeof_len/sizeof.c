#include <stdio.h>
#include <stdbool.h>
#include <string.h>


void ProcessPerson(const char entry[]);
void GenerateEmails(char *data[], int n);

#define MAX_NAME 52 // space and \0
#define NAME 20 // 2x + space + \0
#define UNIID_LEN 6 
#define EMAIL_LEN 8 // UNIID_LEN + 7 + \0

void GetString(char str[], int n);
void DebugString(char str[]);


int main(void)
{
    char *data[] = {"Maria,Kask",
                    "Johanna-Maria,Kask",
                    "Kalev Kristjan,Kuusk"};
    
    // Divides size of a pointer array with a size of a single pointer to find
    // how many many strings in data pointer array. 
    // Don't worry, you don't need to understand it yet!
    int numOfPeople = sizeof data / sizeof (char *);

    GenerateEmails(data, numOfPeople);

    /**
     * By knowing the location of the comma, you will also be able to calculate the position of the first character from the last name
    Lower and upper case ASCII characters differ from each other by a single bit, which is valued at 32 (e.g. A is 65, a is 97)
    All operations in this task besides adding the domain address in the end are easiest done character at a time. 
     **/

    // The most common mistake in this task is forgetting to add a string terminator to the end after copying over the name part of the address!
    return 0;
}

void GenerateEmails(char *data[], int n)
{
    int i;
    
    printf("Number of CSV lines: %d\n\n", n);
    
    for (i = 0; i < n; i++)
    {
        // Pass each name separately
        ProcessPerson(data[i]);
    }
}

void ProcessPerson(const char entry[])
{
    char delimiter = 44; // comma ( , ) is ASCII 44 (DECIMAL). dot is 46, semicolon 59. 
    
    bool isLastname = false; // boolean to toggle whether entry[i] has passed delimiter (comma , )
    int delimiterIndex; // CSV delimiter's index
    
    int firstnameCharCnt = 0;
    int lastnameCharCnt = 0;
    
    char firstname[NAME];
    char lastname[NAME];
    char uniId[UNIID_LEN];
    
    printf("Processing line: '%s'\n", entry);

    // WRITE CODE HERE!
    int len = strlen(entry);
    
    for (int i = 0; i < len; i++)
    {
        
        /** Adding booleanFlag if we encounter delimiter (here: comma)**/
        if (entry[i] == delimiter)
        {
            isLastname = true;
            delimiterIndex = i;
            continue; // skip this iteration from following code, because we do not concat delimiter!
        }
        
        /** Concatenating char from string, based on booleanFlag
         *  - if we haven't yet met with delimiter, concat to firstName
         *  + if we have already met demiliter, then concat to lastName'**/
        if (!isLastname)
        {
            /** Concatinate character (char) to array (firstName) **/
            strcat(firstname, entry[i]);
            
            /** Add two chars of firstName into email**/
            if (firstnameCharCnt <= 2)
            {
                if (65 <= entry[i] && entry[i] <= 90) // [A-Z] in ASCII (A is 65) (Z is 90)
                {
                    /** Lower and upper case ASCII characters differ
                     *  from each other by a single bit,
                     *  which is valued at 32 (e.g. A is 65, a is 97) **/
                    strcat(uniId, entry[i] + 32); // thus + 32 (in ASCII)
                }
                
                firstnameCharCnt++; // iterate counter!
            }
        }    
        else // else if (isLastname)
        {
            /** Concatinate character (char) to array (lastName) **/
            strcat(lastname, entry[i]); 
        
            /** add three chars of lastName into email **/
            if (lastnameCharCnt <= 3)
            {
                if (65 <= entry[i] && entry[i] <= 90) // [A-Z] in ASCII (A is 65) (Z is 90)
                {
                    /** Lower and upper case ASCII characters differ
                     *  from each other by a single bit,
                     *  which is valued at 32 (e.g. A is 65, a is 97) **/
                    strcat(uniId, entry[i] + 32); // thus + 32 (in ASCII)
                }
                
                lastnameCharCnt++; // iterate counter! // NOT NEEDED?
            }
        }
    }

    /** Concat firstname and lastname**/
    char fullName[2 * NAME + 1];
    strncat(fullName, firstname, NAME);
    strcat(fullName, " ");
    strncat(fullName, lastname, NAME);
    
    
    int lenFullname = strlen(fullName);
    GetString(fullName, lenFullname); // should remove 2nd argument (unnecessary)
    printf("Name: %s \n", fullName);
    
    char emailAddress[UNIID_LEN + 8];
    strncat(emailAddress, uniId, UNIID_LEN);
    
    int lenEmailAddress = strlen(emailAddress);
    GetString(emailAddress, lenEmailAddress);
    printf("E-mail: %s\n", emailAddress);
}

void GetString(char str[], int n)
{
	// Read the string from keyboard
	//~ fgets(str, n, stdin);
	
	// TODO: Find the length of the actual string we just read
	int len = strlen(str); // replace with GetLenght Fn?
	//~ int len = strlen(str); // replace with GetLenght Fn?
	
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
