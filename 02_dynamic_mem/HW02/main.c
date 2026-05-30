// gcc -o prog -fsanitize=address toDef1.c

#include "main.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//~ #define DEBUG 
	
//~ int main(int argc, char **argv)
int main(void)
{

	
	
	//~ /** Step 0: Print the issued command line parameters.**/
	//~ #ifdef DEBUG
	//~ DebugArgs(argc, argv);
	//~ #endif 
	
	//~ /** Step 1: Validate program was run with correct CLI arguments**/
	//~ if (argc != ARGS_CNT)
	//~ {
		//~ /** Exit the program with 'fprintf(stderr, "message"); **/
		//~ fprintf(stderr, "Usage: %s <data_persons_file1>.txt  <data_vehicles_file>.txt\n", ARGS_EXEC_NAME );
		//~ //Logger("Closing program. Input file not found.", ERROR);
		//~ return EXIT_FAILURE;
	//~ }
	
	/** Step 2: Set logging parameters**/
	int usersLogLevel = PromptEnableDisableLogging();
	LoggerSetLoggingLevel(usersLogLevel); // inner returns type 'enum LogLevel'
	
	/** Ask user to select logfile name.**/
	char logfileName[LOG_FILE_NAME_LEN] = {0};
	
	if (usersLogLevel != OFF) /** Avoid asking log-filename if user disabled logging.**/
	{
		PromptLogFileName(logfileName);
	
		/** Call setter to rewrite into  global variable 'globalfileName'**/
		LoggerSetOutputName(logfileName);
	}
	Logger("Starting program.", LOG_INFO); // log entry to logfile.

	
	/** Step 3: Move on to main program menu.**/
	//~ char *productFilename = ARGS_FILE_NAME_PRODUCT;
	//~ char *quoteFilename = ARGS_FILE_NAME_QUOTE;
	
	char *productFilename = "products.txt";
	char *quoteFilename = "quotes.txt";
	
	/** Read both files, and dynamically allocate memory**/
	product_list wf = {NULL, 0, 0};
	quote_list qf = {NULL, 0, 0};
	
	ReadFilesDynamically(productFilename, quoteFilename, &wf, &qf); // IMPORTANT
	
	/** IMPORTANT: snprintf() to include variable in log message content. **/
	char message[LOG_MESSAGE_LEN] = {0};
	snprintf(message, LOG_MESSAGE_LEN, "Read %d lines from %s", wf.used, productFilename);
	Logger(message, INFO);
	
	
	/** IMPORTANT: snprintf() to include variable in log message content. **/
	//~ char message[LOG_MESSAGE_LEN] = {0};
	strcpy(message, "");
	snprintf(message, LOG_MESSAGE_LEN, "Read %d lines from %s", qf.used, quoteFilename);
	Logger(message, INFO);
	
	/** Menu section**/
	int menuOption = 1; // Display all the data by default (case 1)
	int exit = NOT_EXIT;
    while (exit == NOT_EXIT) // (!exit)
    {
        //menuOption = Menu();
        switch (menuOption)
        {
            case 1:
				puts("--Menu Option 1: Display all the data from files-- \n");
					
				//~ PrintProducts(wf);
				//~ PrintQuotes(qf);
				PrintProductQuotes(wf.db, qf.db, wf.used, qf.used);
				
				break;
			case 2:
				puts("--Menu Option 2: Edit product screen size--\n"); // by product code or quote id
							
				int min = (int) wf.db->productCode_PK;
				int max = (int) (wf.db + (wf.used - 1))->productCode_PK;
				int desiredCode = GetIntInRange(min, max, "\nPlease choose a product by product code.");
		
				product *pFoundProduct = wf.db;
				FindProductByCode(desiredCode, &wf, &pFoundProduct);
				
				PrintOneProduct(pFoundProduct); // logger message
				
				ChangeScreenSize(pFoundProduct);
				
				WriteToProductFile(&wf, productFilename);
				break;
				
			case 3:
				puts("--Menu Option 3: Edit quote availability-- \n"); // by quote id or product id

				min = (int) qf.db->quoteID_PK;
				max = (int) (qf.db + (qf.used - 1))->quoteID_PK;
				int desiredID = GetIntInRange(min, max, "\nPlease choose a quote by the quote ID.");

				quote *pFoundQuote = qf.db;
				FindQuoteByID(desiredID, &qf, &pFoundQuote); // todo
				
				PrintOneQuote(pFoundQuote);
				
				ChangeAvailability(pFoundQuote); // todo
				
				WriteToQuoteFile(&qf, quoteFilename); // todo


				break;
				
			case 4:
				puts("--Menu Option 4: Search for a phone based on RAM-- \n");
				
				char *promptInt = "Choose desired RAM in MB. "; 
				//~ int desiredRam = AskInt(prompt);
				int desiredRam = GetIntInRange(MIN_RAM, MAX_RAM, promptInt);
				SearchForProductByRAM(desiredRam, &wf, &qf);
				break;
				
			case 5:
				puts("--Menu Option 5: Search for a phone based on Screen size-- \n");
				
				char *promptDouble = "Choose desired screen size (example '9.6').";
				double desiredSize = GetDoubleInRange(MIN_SCREEN, MAX_SCREEN, promptDouble);
				
				SearchForProductByScreenSize(desiredSize, &wf, &qf);
				break;
				
			case 0:
				puts("--Menu Option 0: Exit-- \n");
			
				char message[LOG_MESSAGE_LEN] = {0};
				snprintf(message, LOG_MESSAGE_LEN, "Freeing dynamically allocted memory from reading '%s'.", productFilename);
				Logger(message, INFO);
				//~ printf("%s\n", message);
				
				FreeProductStruct(wf.db, wf.used);
				
				char message2[LOG_MESSAGE_LEN] = {0};
				snprintf(message2, LOG_MESSAGE_LEN, "Freeing dynamically allocted memory from reading '%s'.", quoteFilename);
				Logger(message2, INFO);
				//~ printf("%s\n", message2);
				
				FreeQuoteStruct(qf.db, qf.used);
				
				puts("Exiting...\n");
				exit = EXIT;
				break;
			default:
				puts("Please try again, this option does not exist.");
				break;
		} // end of switch
		if (!exit)
		{
			menuOption = Menu();
		}
	}
	
	Logger("Program successfully ran to end.", INFO);
	if (usersLogLevel != OFF)
		printf("Log messages can be found in '%s' file.\n\n", logfileName);
	else
		printf("Logs were not collected due to 'OFF' logging status.\n\n");
	
	
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
    puts("1 - Display all data from files");
    puts("2 - Change the screen size of phone");
    puts("3 - Change the availability of a price quote");
    puts("4 - Search for a phone by RAM");
    puts("5 - Search for a phone by screen size");
 
    puts("0 - Exit program");
    selection = GetIntInRange(MENU_OPTION_MIN, MENU_OPTION_MAX, "Choose menu option. ");
    return selection;
}

/** Description:    Print debugging information about command line arguments
 * 
 *  Parameters:     command line argument count
 *                  command line arguement vector            
 * 
 *  Result:         void; print command line argument count and vector by each char
 **/
void DebugArgs(int argc, char **argv)
{
    int i, j, n;
    printf("Got %d command line arguments\n", argc);
    
    /** Accessing arguments one by one as strings **/
    for (i = 0; i < argc; i++)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    putchar('\n');
    
    /** Accessing arguments, character at a time **/
    for (i = 0; i < argc; i++)
    {
        for (j = 0, n = strlen(argv[i]); j < n; j++)
        {
            printf("%c ", argv[i][j]);
        }
       putchar('\n');
    }
} // end of function

/** Description:    Find product by product code.
 * 					1. Loop the entire database of products until match found
 * 					2. Point the double-pointer to reference found structure pointer.
 * 
 *  Parameters:     product code chosen by user 
 *       			wrapper structure (wf) storing product database  
 *  			    double-pointer to a structure (type 'product'),
 * 						that will reference the found structure.  
 * 
 *  Result:         void
 **/
void FindProductByCode(int desiredCode, product_list *wf, product **foundProduct)
{
	for (int i = 0; i < wf->used; i++)
	{
		if ((uint64_t) desiredCode == (wf->db + i)->productCode_PK)
		{
			*foundProduct = (wf->db + i);
			break;
		}
	} // end of for-loop
} // end of function

/** Description:    Find a quote by quote ID
 * 					1. Loop the entire database of quotes until match found
 * 					2. Point the double-pointer to reference found structure pointer.
 * 
 *  Parameters:     quote ID chosen by user 
 *       			wrapper structure (qf) storing quote database  
 *  			    double-pointer to a structure (type 'quote'),
 * 						that will reference the found structure.  
 * 
 *  Result:         void
 **/
void FindQuoteByID(int desiredID, quote_list *qf, quote **pFoundQuote)
{
	for (int i = 0; i < qf->used; i++)
	{
		if ((uint64_t) desiredID == (qf->db + i)->quoteID_PK)
		{
			*pFoundQuote = (qf->db + i);
			break;
		}
	} // end of for-loop
} // end of function

/** Description:    Change the screen size of a product.
 * 					1. Print the current size of the screen size of selected product
 * 					2. Prompt user to choose new size, in reasonable bounds
 * 					3. Overwrite the size with the new size, such that
 * 						the pointer ('product' type) references it.
 * 					4. Print the new size
 * 
 *  Parameters:     pointer to a structure (type 'product')  
 * 
 *  Result:         void
 **/
void ChangeScreenSize(product *pFoundProduct)
{
	printf("The current screen size is %.1lf inches.\n", (pFoundProduct)->screenSize);
	double newScreen = GetDoubleInRange(MIN_SCREEN, MAX_SCREEN, "\nPlease choose a new screen size in inches.");
	
	pFoundProduct->screenSize = newScreen;
	printf("The new screen size is %.1lf inches.\n", (pFoundProduct)->screenSize);
}

/**
 * Description:    Asks the user for a character (Y / N).
 *                 Reprompts if input is out of bounds.
 * 					*If correct input (Y/N/y/n), then
 * 					overwrite the structure field. The structure is
 *
 * Parameters:     pointer to a structure (type 'quote')
 * 					*this pointer helps to
 * 					 overwrite struct's availability field 
 *
 * Return:         void.
 */
void ChangeAvailability(quote *pFoundQuote)
{
	printf("The phone is %s.\n", ((pFoundQuote)->availability == 'Y') ? "in stock" : "out of stock");
	//~ char newAvailabilityStatus = GetCorrectCharInput(
	char input[CHAR_SIZE] = {0};
	char newAvailabilityStatus = AskChar(input,
				"\nPlease change the availability of the phone. \n"
				"Select Y or N."
				"\n 'Y' - In Stock."
				"\n 'N' - Out of Stock.");
	
	pFoundQuote->availability = toupper(newAvailabilityStatus);
	printf("The phone is now %s.\n", ((pFoundQuote)->availability == 'Y') ? "in stock" : "out of stock");
} // end of function
