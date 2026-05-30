#include "search.h"
#include "log_helper.h"


/**
 * Description:    Read files of products and quotes.
 * 					
 *                 	1. Read products into products_list while allocating memory 
 * 					2. Read quotes into quotes_list while allocating memory
 * 					3. Log failures to do so.
 * 
 * 	Parameters:    product filename
 * 				   quote filename
 * 				   entire database of products (product_list)
 * 				   entire database of quotes (quote_list)
 *
 * Return:         void
 */
void ReadFilesDynamically(char *productFilename, char *quoteFilename,
								product_list *wf, quote_list *qf)
{	// do not delete {


	int returnval = ReadDynamicProductData(wf, productFilename);
	if (returnval == 1)
	{
		Logger("Closing program. Could not read file.", ERROR);
		
		/** IMPORTANT: snprintf() to include variable in log message content. **/
		char message[LOG_MESSAGE_LEN] = {0};
		snprintf(message, LOG_MESSAGE_LEN, "Closing program. Could not read file %s.", productFilename);
		Logger(message, ERROR);
		
		
		printf("%s", message);
		exit(EXIT_FAILURE);
	}
	
	
	/** Step 2: Check if enough memory can be allocated.**/
	if (wf->db == NULL)
	{
		printf("Not enough memory after reading '%s'!\n", productFilename);
		
		/** IMPORTANT: snprintf() to include variable in log message content. **/
		char message[LOG_MESSAGE_LEN] = {0};
		snprintf(message, LOG_MESSAGE_LEN, "Not enough memory after reading '%s'!\n", productFilename);
		Logger(message, ERROR);
		
		printf("%s", message);
		exit(EXIT_FAILURE);
	}

	//~ quote_list qf = {NULL, 0, 0};
	
	int returnval2 = ReadDynamicQuoteData(qf, quoteFilename);
	if (returnval2 == 1)
	{
		/** IMPORTANT: snprintf() to include variable in log message content. **/
		char message[LOG_MESSAGE_LEN] = {0};
		snprintf(message, LOG_MESSAGE_LEN, "Closing program. Could not read file %s.", quoteFilename);
		Logger(message, ERROR);
		
		printf("%s", message);
		exit(EXIT_FAILURE);
	}
	
	
	/** Step 2: Check if enough memory can be allocated.**/
	if (qf->db == NULL)
	{
		/** IMPORTANT: snprintf() to include variable in log message content. **/
		char message[LOG_MESSAGE_LEN] = {0};
		snprintf(message, LOG_MESSAGE_LEN, "Not enough memory after reading '%s'!\n", quoteFilename);
		Logger(message, ERROR);
		
		printf("%s", message);
		exit(EXIT_FAILURE);
	}
	
	#ifdef DEBUG
	printf("qf->used: %d, qf->limit %d\n", qf->used, qf->limit);
	#endif
	
} // end of function

/**
 * Description:    Search for all products with user's inputted RAM in MB.
 *                 	1. Group the results 
 * 					2. Filter for available quotes
 * 					3. Print the results.
 * 
 * Parameters:     user's chosen RAM in MB.
 * 				   entire database of products (product_list)
 * 				   entire database of quotes (quote_list)
 *
 * Return:         void
 */
void SearchForProductByRAM(int desiredRam, product_list *wf, quote_list *qf) 
{
	
	int matchedProducts = 0;
	for (int i = 0; i < wf->used; i++)
	{
		if ((wf->db + i)->ram == desiredRam)
		{
			matchedProducts++; 
			
			int quotesFound = 0;
			for (int j = 0; j < qf->used; j++)
			{
				uint64_t pk = (wf->db + i)->productCode_PK;
				uint64_t fk = (qf->db + j)->productCode_FK;
				if (pk == fk)
				{
					if ((qf->db + j)->availability == 'Y')
					{
						quotesFound++;
						
						PrintOneProduct(wf->db + i);
						printf("\t Quote no: %d: | ", quotesFound);
						PrintOneQuote(qf->db + j);
						
					}
				} // if-store
			}
			if (quotesFound <= 0)
			{
				printf("\t*** Phone '%s' has %d RAM in MB. ***\n"
				"\t***The product is out of stock for all retailers ***\n", (wf->db + i)->markModel, desiredRam);
			}
		} // if-ram
		
	} // end of loop
	if (matchedProducts <= 0)
	{
		printf("\t*** No registered quotes for any retailers for a Phone with '%d' RAM in MB ***\n", desiredRam);
	}
} // end of function

/**
 * Description:    Search for all products with user's inputted screen size
 *                 	1. Group the results 
 * 					2. Filter for available quotes
 * 					3. Print the results.
 * 
 * Parameters:     user's chosen screen size in inches (double datatype)
 * 				   entire database of products (product_list)
 * 				   entire database of quotes (quote_list)
 *
 * Return:         void
 */
void SearchForProductByScreenSize(double desiredSize, product_list *wf, quote_list *qf) 
{

	int matchedProducts = 0;
	for (int i = 0; i < wf->used; i++)
	{
		if ((wf->db + i)->screenSize == desiredSize)
		{
			matchedProducts++; 
			
			int quotesFound = 0;
			for (int j = 0; j < qf->used; j++)
			{
				uint64_t pk = (wf->db + i)->productCode_PK;
				uint64_t fk = (qf->db + j)->productCode_FK;
				if (pk == fk)
				{
					if ((qf->db + j)->availability == 'Y')
					{
						quotesFound++;
						PrintOneProduct(wf->db + i);
						printf("\t Quote no: %d: | ", quotesFound);
						PrintOneQuote(qf->db + j);
						
					}
				} // if-store
			}
			if (quotesFound <= 0)
			{
				printf("\t*** Phone '%s' has %.1lf inches for the screen size. *** \n"
				"\t*** This product is out of stock for all retailers. ***\n", (wf->db + i)->markModel, desiredSize);
			}
		} // if-ram
		
	} // end of loop
	if (matchedProducts <= 0)
	{
		printf("\t*** No registered quotes for any retailers for a Phone with screen size '%.1lf'. ***\n", desiredSize);
	}
} // end of function
