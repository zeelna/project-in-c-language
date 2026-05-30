#ifndef READ_QUOTE_H
#define READ_QUOTE_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "read_product.h"

//~ #include "log_helper.h"

//~ #define DEBUG 1

#define RETAILER_LEN 25

typedef struct quote
{
	uint64_t quoteID_PK;
	uint64_t productCode_FK;
	double price;
	char availability;
	char *retailer;
} quote;

typedef struct quote_list
{
	quote *db;
	unsigned limit;
	unsigned used;
} quote_list;

/** Description: 	Free structure(s) of type 'quote'.
 * 					Function frees all dynamically allocated memory for strings.
 * 					
 *  Paramaters:		pointer (type quote).
 * 					number of structures.
 * 	Return:			void.
 **/
void FreeQuoteStruct(quote *p, unsigned int n);

/**
 * Description:   Function to read data from a file. During this, a dynamic
 *                struct array will be created and expanded using realloc()
 * Parameters:    ppData - dbl pointer where to store the allocated array pointer
 *                pLineCount - pointer to store the read line count
 *                fileName - name of the input file to read
 * Return:        0 if data is read successfully
 *                1 if error is encountered
 */

int ReadDynamicQuoteData(quote_list *qf, char *fileName);

/**
 * Writing a changes to Quote file. Opens file, writes and then closes file.
 **/	
 
 /** Description: 	Writing entire database of structures to file.
  * 				*** This is used to overwrite input file with changes in structure.
  * 				Opens file, writes and then closes file.
  * 
 *  Paramaters:		wrapper structure (quote_list type)
 * 					filename where to write
 *  
 * 	Return:			void.
 **/
void WriteToQuoteFile(quote_list *qf, char *fileName);

#endif // READ_PRODUCT_H
