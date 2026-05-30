#ifndef PRINT_RESULTS_H
#define PRINT_RESULTS_H

#include "read_quote.h"
#include "read_product.h"

/**
 * Description:		Prints the list of product in the struct array of all product
 * 
 * Parameters:		entire structure array of products
 * 	
 * Returns:			void
 **/
void PrintProducts(product_list wf);

/**
 * Description:		Prints the list of product in the struct array of all product
 * 
 * Parameters:		pointer to structure array of products
 * 					pointer to structure array of quotes
 *					count of products
 *					count of quotes
 * 
 * Returns:			void
 **/
void PrintProductQuotes(product *pProduct, quote *pQuote,
				int productCnt, int quoteCnt);
		
		
/**
 * Description:		Prints the list of quotes in the struct array of all quotes
 * 
 * Parameters:		entire structure array of quotes
 * 	
 * Returns:			void
 **/			
void PrintQuotes(quote_list wf);

/**
 * Description:		Prints a quote by precise pointer
 * 
 * Parameters:		pointer to quote
 * 	
 * Returns:			void
 **/	
void PrintOneQuote(quote *p);

/**
 * Description:		Prints a product by precise pointer
 * 
 * Parameters:		pointer to product
 * 	
 * Returns:			void
 **/	
void PrintOneProduct(product *p);

#endif // PRINT_RESULTS_H
