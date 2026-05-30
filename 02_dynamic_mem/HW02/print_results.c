#include "print_results.h"

/**
* Print the products and group all quotes related to them.
**/
void PrintProductQuotes(product *pProduct, quote *pQuote,
				int productCnt, int quoteCnt)
{
	int matchedProducts = 0; 					
	int i, j;
	for (i = 0; i < productCnt; i++)
	{	
		matchedProducts = 0; /** Tip: Must reset for each person. **/
		  
		printf("Product ID (PK): %ld \n", (pProduct + i)->productCode_PK);
		printf("Phone: %s | ", (pProduct + i)->markModel);
		printf("OS: %s | ", (pProduct + i)->operatingSystem);
		printf("RAM: %d  | ", (pProduct + i)->ram);
		printf("Screen size: %.1lf | \n", (pProduct + i)->screenSize);


		for (j = 0; j < quoteCnt; j++)
		{
			uint64_t pk = (pProduct + i)->productCode_PK;
			uint64_t fk = (pQuote + j)->productCode_FK;
			//~ if ((pProduct + i)->productCode_PK == (pQuote + j)->productCode_FK)
			if (pk == fk)
			{
				matchedProducts++; 

				printf("\t Match nr: %d: | ", matchedProducts);
				printf("Quote ID (PK): %ld | ", (pQuote + j)->quoteID_PK);
				//~ printf("Product ID (PK): %ld | ", (pProduct + i)->productCode_PK);
				printf("Product ID (FK): %ld | ", (pQuote + j)->productCode_FK);
				printf("Price: %.2lf€ | ", (pQuote + j)->price);													
				printf("Available: %s\n", ((pQuote + j)->availability == 'Y') ? "Yes" : "No");													
			}
		} // end of for-j
		if (matchedProducts <= 0) {
			printf("\t*** No registered quotes ***\n");
		}
		
		/** Part 3**/
		putchar('\n');
	} // end of for-i
} // end of function

/**
 * Prints a single quote.
 */
void PrintOneQuote(quote *p)
{
	if (p == NULL)
	{
		puts("No such quote found."); // logger message
	}
	
	printf("Quote ID (PK): %ld | ", p->quoteID_PK);
	printf("Product ID (FK): %ld | ", p->productCode_FK);
	printf("Price: %.2lf€ | ", p->price);	
	printf("Avaiable: %s\n", (p->availability == 'Y') ? "Yes" : "No");	
}

/**
 * Prints phone full specification
 */
void PrintOneProduct(product *p)
{
	if (p == NULL)
	{
		puts("No such product found."); // logger message
	}
	else
	{
		printf("Product ID (PK): %ld \n", p->productCode_PK);
		printf("Phone: %s | ", p->markModel);
		printf("OS: %s | ", p->operatingSystem);
		printf("RAM: %d  | ", p->ram);
		printf("Screen size: %.1lf | \n", p->screenSize);
	}
	//~ putchar('\n');
}

/**
 * Prints the list of products in the struct array of all products
 */
void PrintProducts(product_list wf)
{
    #ifdef DEBUG
    printf("%d out of %d slots are in use\n", wf.used, wf.limit);
    #endif
    
	puts("Displaying all Products...");
    
    printf("%7s | %24s | %16s | %12s | %9s\n",
		"code-PK", "Product make and model",
		"Operating system", "Screen size", "RAM in MB");
		
    for (int i = 0; i < wf.used; i++)
    {
        printf("%7ld | %24s | %16s | %12.1lf | %9d\n", (wf.db + i)->productCode_PK,
			(wf.db + i)->markModel, (wf.db + i)->operatingSystem, (wf.db + i)->screenSize,
			(wf.db + i)->ram);
    }
	putchar('\n');
} // end of function


/**
 * Prints the list of quotes in the struct array of all quotes
 */
void PrintQuotes(quote_list qf)
{
	#ifdef DEBUG
    printf("%d out of %d slots are in use\n", qf.used, qf.limit);
    #endif
    
    puts("Displaying all Quotes...");
    
    printf("%9s | %7s | %14s | %8s | %12s\n", "Quote-PK", "Code-FK",
    "Retailer", "Price", "Availability");
    for (int i = 0; i < qf.used; i++)
    {
        printf("%9ld | %7ld | %14s | %8.1lf | %12c\n",
         (qf.db + i)->quoteID_PK, (qf.db + i)->productCode_FK, 
         (qf.db + i)->retailer, (qf.db + i)->price,
		 (qf.db + i)->availability);
    }
	putchar('\n');
} // end of function
