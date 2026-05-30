#ifndef READ_PRODUCT_H
#define READ_PRODUCT_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//~ #include "log_helper.h"

//~ #define DEBUG 1

#define OS_LEN 25
#define MARKMODEL_LEN 64

 /** Description: The following code will demonstrate a couple of hints on allocating
 *              memory in C.
 *              First of all, it will demonstrate the use of a wrapper structure
 *              which will give better control over size management. In this case,
 *              it will track how many memory slots are in use and how many are
 *              there in total. This allows to keep the data neatly together
 *              and avoid array overflows.
 *              Secondly, this code also demonstrates a possibility to safely
 *              expand the storage using reallocation. The reallocate step is 2x
 *              of what it was previously, so it would be more optimal in speed.
 **/

typedef struct product
{
	uint64_t productCode_PK;
	int ram;	
	double screenSize;
	char *operatingSystem;	
	char *markModel;
} product;

typedef struct product_list
{
	product *db;
	unsigned int limit;
	unsigned int used;
} product_list;

/** Description: 	Free structure(s) of type 'product'.
 * 					Function frees all dynamically allocated memory for strings.
 * 					
 *  Paramaters:		pointer (type product).
 * 					number of structures.
 * 	Return:			void.
 **/
void FreeProductStruct(product *p, unsigned int n);
//~ void FreeStruct((void *p, unsigned int n);

/** Description: 	Free the pointer. Avoids duplicate free() calls
 *  Paramaters:		pointer (without type). 
 * 	Return:			void.
 **/
void SafeFree(void **p);

/**
 * Description:   Function to read data from a file. During this, a dynamic
 *                struct array will be created and expanded using realloc()
 * Parameters:    ppData - dbl pointer where to store the allocated array pointer
 *                pLineCount - pointer to store the read line count
 *                fileName - name of the input file to read
 * Return:        0 if data is read successfully
 *                1 if error is encountered
 */
int ReadDynamicProductData(product_list *wf, char *fileName);

/**
 * Writing a changes to Product file. Opens file, writes and then closes file.
 **/
 
/** Description: 	Writing entire database of structures to file.
  * 				*** This is used to overwrite input file with changes in structure.
  * 				Opens file, writes and then closes file.
  * 
 *  Paramaters:		wrapper structure (product_list type)
 * 					filename where to write
 *  
 * 	Return:			void.
 **/
void WriteToProductFile(product_list *wf, char *fileName);

#endif // READ_PRODUCT_H
