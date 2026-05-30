
#include "read_quote.h"

/**
 * Description:   Function to read data from a file. During this, a dynamic
 *                struct array will be created and expanded using realloc()
 * Parameters:    ppData - dbl pointer where to store the allocated array pointer
 *                pLineCount - pointer to store the read line count
 *                fileName - name of the input file to read
 * Return:        0 if data is read successfully
 *                1 if error is encountered
 */

int ReadDynamicQuoteData(quote_list *qf, char *fileName)
{
	// temporary buffers for strings
    char retailerBuf[RETAILER_LEN];
    
    // temporary variable (buffer) for screen size, ram, product code
    uint64_t productCodeBuf;
    uint64_t quoteIDBuf;
    char availabilityBuf;
    double priceBuf;
    
    // temporary pointer that i'm using to check the return value of realloc()
    quote *pTemp = NULL;
 
	FILE *fInputStream;
    fInputStream = fopen(fileName, "r"); 
   
    /** Check if file stream EMPTY for file "input.txt" **/
	if (fInputStream == NULL)
	{
		/** Redirect message to standard error stream.**/
		fprintf(stderr, "Error opening file '%s'\n", fileName); 
		return 1;
	}
	
	qf->db = (quote *)calloc(1, sizeof(quote));
    if (qf->db == NULL)
    {
        perror("Error allocating memory");
        return 1;
    }
	qf->limit = 1; // 2*n presumes calloc of 1.
	
	
    int cnt = 0;     // line counter
    while (fscanf(fInputStream, "%ld,%ld,%lf,%c,%[^\n]",
										&quoteIDBuf,
										&productCodeBuf,
										&priceBuf,
										&availabilityBuf,
										retailerBuf) == 5) 
	{
		#ifdef DEBUG_M
			putchar('\n');
			printf("DEBUG FSCAN: Got (%d): %ld %ld %.1lf %c %s\n",
										cnt,
										quoteIDBuf,
										productCodeBuf,
										priceBuf,
										availabilityBuf,
										retailerBuf);
		#endif	

		// first lets create some code that detects if array is full
		if (qf->limit == qf->used)
		{
            // let's make the new limit 2x from what we had
            
		   
            int newLimit = 2 * qf->limit;
            
			#ifdef DEBUG
            printf("We ran out of memory. Trying to expand array from %d to %d\n",
                   qf->limit, newLimit);
			#endif    
			//~ char message[LOG_MESSAGE_LEN] = {0};
			//~ snprintf("We ran out of memory. Trying to expand array from %d to %d\n",
                   //~ qf->limit, newLimit);
                   
			//~ Logger(message, WARNING);
			//~ printf("%s\n", message);
 
            // reallocate the new memory
            pTemp = (quote *)realloc(qf->db, sizeof(quote) * newLimit);
 
            // check if we were successful
            if (pTemp != NULL)
            {
				#ifdef DEBUG_M
				puts("Before qf->db = pTemp");
				printf("qf->db = %p\n", qf->db);
				printf("pTemp = %p\n", pTemp);
				putchar('\n');
				#endif
				
				// "sync" the pointers and update the limit
				qf->db = pTemp;
				qf->limit = newLimit;
				
				#ifdef DEBUG
				printf("Allocation success! New limit is %d\n", qf->limit);
				#endif   
				
				#ifdef DEBUG_M
				puts("After qf->db = pTemp");
				printf("qf->db = %p\n", qf->db);
				printf("pTemp = %p\n", pTemp);
				putchar('\n');
				#endif
            } // end of if.
            else
            {
			   #ifdef DEBUG
			   printf("Allocation failed. Old limit of %d is being used\n", qf->limit);
			   #endif
			   //~ Logger("Allocation failed for enlarging list of Quotes.", WARNING);
					/** TODO: BREAK and do not cnt++/used++ **/
			   FreeQuoteStruct(qf->db, qf->used); // todo: rethink! Should I free?
			   fclose(fInputStream);
			   return 1; // log-message!
            } // end of else
        } // end of wf-limit
		
		(qf->db + qf->used)->retailer = strdup(retailerBuf);
		if ((qf->db + qf->used)->retailer== NULL)
		{
				   // TODO: BREAK and do not cnt++/used++
			FreeQuoteStruct(qf->db, qf->used); // rethink, should I free only ONE line
			return 1; // error
		}
		
        // numbers can be copied directly, there already is memory in the struct
        (qf->db + qf->used)->productCode_FK = productCodeBuf;
        (qf->db + qf->used)->quoteID_PK = quoteIDBuf;
        (qf->db + qf->used)->availability = availabilityBuf;
        (qf->db + qf->used)->price = priceBuf;
		
		#ifdef DEBUG_M
		printf("DEBUG qf->db: Got (%d): %ld %ld %c %s %.1lf",
				cnt,
				(qf->db + qf->used)->productCode_FK,
				(qf->db + qf->used)->quoteID_PK,
				(qf->db + qf->used)->availability,
				(qf->db + qf->used)->retailer,
				(qf->db + qf->used)->price);
		putchar('\n');
		#endif
		
		// Increment number of records successfully read
		qf->used++;
		cnt++;
    }
	// "sync" the pointers and update the limit
	qf->limit = qf->used;
 
	#ifdef DEBUG
	printf("\n Successfully ran '%s'\n", __FUNCTION__);
	#endif
 
	fclose(fInputStream);
    return 0;
} // end of function



/**
 * Writing a log message to file. Opens file, writes and then closes file.
 **/	
void WriteToQuoteFile(quote_list *qf, char *fileName)
{
	/** pointer for file stream (input file streams) **/
	FILE *fOutStream;
    fOutStream = fopen(fileName, "w");
    
    /** Check if file stream EMPTY for file "input.txt" **/
	if (fOutStream == NULL)
	{
		/** Logifaili avamise ebaõnnestumisel peab programm jätkama tööd, mitte väljuma! 
		 * Teavita kasutajat logimise ebaõnnestumisest.**/
	}
	else
	{
		/** Write to file **/
		for (int i = 0; i < qf->used; i++)
		{
		fprintf(fOutStream, "%ld,%ld,%.1lf,%c,%s\n",
				(qf->db + i)->quoteID_PK,
				(qf->db + i)->productCode_FK,
				(qf->db + i)->price,
				(qf->db + i)->availability,
				(qf->db + i)->retailer);
		}
		fprintf(fOutStream, "\n");
		/** Closing file-stream **/
		fclose(fOutStream);
	}	
} // end of write


/** Description: 	Free structure(s) of type 'quote'.
 * 					Function frees all dynamically allocated memory for strings.
 * 					
 *  Paramaters:		pointer (type quote).
 * 					number of structures.
 * 	Return:			void.
 **/
void FreeQuoteStruct(quote *p, unsigned int n)
{
	for (int i = 0; i < n; i++)
	{
		SafeFree((void **)&p[i].retailer);
	}
	SafeFree((void **)&p); // free entire struct.
	
	#ifdef DEBUG
	printf("\n Successfully ran '%s'\n", __FUNCTION__);
	#endif
} // end of function




