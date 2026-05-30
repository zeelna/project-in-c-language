
#ifndef MAIN_H
#define MAIN_H

#include "read_product.h"

#include "read_quote.h"

#include "print_results.h"

#include "search.h"

#include "log_helper.h"

#include "ask_input.h"

//~ #define DEBUG 1

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>
#include <stdint.h>
#include <inttypes.h>


#define NOT_EXIT 0
#define EXIT 1

#define MENU_OPTION_MIN 0
#define MENU_OPTION_MAX 5

#define MIN_RAM 0
#define MAX_RAM 64000

#define MIN_SCREEN 5.0
#define MAX_SCREEN 40.0


#define ARGS_CNT 3
#define ARGS_EXEC_NAME 				argv[0]
#define ARGS_FILE_NAME_PRODUCT 		argv[1]
#define ARGS_FILE_NAME_QUOTE 		argv[2]



/**
 * Description:    Displays the possible menu options to the user,
 *                 allows to select an action to perform.
 *
 * Parameters:     None
 *
 * Return:         Menu item number selected
 */
int Menu(void);

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
void FindProductByCode(int desiredCode, product_list *wf, product **foundProduct);

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
void ChangeScreenSize(product *pFoundProduct);

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
void ChangeAvailability(quote *pFoundQuote);

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
void FindQuoteByID(int desiredID, quote_list *qf, quote **pFoundQuote);


/** Description:    Print debugging information about command line arguments
 * 
 *  Parameters:     command line argument count
 *                  command line arguement vector            
 * 
 *  Result:         void; print command line argument count and vector by each char
 **/
void DebugArgs(int argc, char **argv);

#endif // MAIN_H
