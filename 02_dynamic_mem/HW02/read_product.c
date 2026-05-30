#include "read_product.h"

/**
 * Description:   Function to read data from a file. During this, a dynamic
 *                struct array will be created and expanded using realloc()
 * Parameters:    ppData - dbl pointer where to store the allocated array pointer
 *                pLineCount - pointer to store the read line count
 *                fileName - name of the input file to read
 * Return:        0 if data is read successfully
 *                1 if error is encountered
 */

int ReadDynamicProductData(product_list *wf, char *fileName)
{
    // temporary buffers for strings
    char OSBuf[OS_LEN], markModelBuf[MARKMODEL_LEN];
    
    // temporary variable (buffer) for screen size, ram, product code
    uint64_t productCodeBuf;
    int ramBuf;
    double screenSizeBuf;
   
    
    // temporary pointer that i'm using to check the return value of realloc()
    product *pTemp = NULL;
 
	FILE *fInputStream;
    fInputStream = fopen(fileName, "r"); 
   
    /** Check if file stream EMPTY for file "input.txt" **/
	if (fInputStream == NULL)
	{
		/** Redirect message to standard error stream.**/
		fprintf(stderr, "Error opening file '%s'\n", fileName); 
		return 1;
	}
	
	wf->db = (product *)calloc(1, sizeof(product));
    if (wf->db == NULL)
    {
        perror("Error allocating memory");
        return 1;
    }
	wf->limit = 1; // 2*n presumes calloc of 1.
	

    int cnt = 0;     // line counter
    while (fscanf(fInputStream, "%ld,%[^,],%[^,],%lf,%d",
										&productCodeBuf,
										markModelBuf,
										OSBuf,
										&screenSizeBuf,
										&ramBuf) == 5) 
	{
		#ifdef DEBUG_M
			putchar('\n');
			printf("DEBUG FSCAN: Got (%d): %ld %s %s %.1lf %d\n",
										cnt,
										productCodeBuf,
										markModelBuf,
										OSBuf,
										screenSizeBuf,
										ramBuf);
		#endif	
		
		
		// first lets create some code that detects if array is full
		if (wf->limit == wf->used)
		{
            // let's make the new limit 2x from what we had
            int newLimit = 2 * wf->limit;
            
			#ifdef DEBUG
            printf("We ran out of memory. Trying to expand array from %d to %d\n",
                   wf->limit, newLimit);
           #endif        
		   
			//~ char message[LOG_MESSAGE_LEN] = {0};
			//~ snprintf(message, LOG_MESSAGE_LEN, "We ran out of memory. Trying to expand array from %d to %d\n",
                   //~ wf->limit, newLimit);
                   
			//~ Logger(message, WARNING);
			//~ printf("%s\n", message);
 
            // reallocate the new memory
            pTemp = (product *)realloc(wf->db, sizeof(product) * newLimit);
 
            // check if we were successful
            if (pTemp != NULL)
            {
				#ifdef DEBUG_M
				puts("Before wf->db = pTemp");
				printf("wf->db = %p\n", wf->db);
				printf("pTemp = %p\n", pTemp);
				putchar('\n');
				#endif
				
				// "sync" the pointers and update the limit
				wf->db = pTemp;
				wf->limit = newLimit;
				
				#ifdef DEBUG
				printf("Allocation success! New limit is %d\n", wf->limit);
				#endif
				
				#ifdef DEBUG_M
				puts("After wf->db = pTemp");
				printf("wf->db = %p\n", wf->db);
				printf("pTemp = %p\n", pTemp);
				putchar('\n');
				#endif
            } // end of if.
            else
            {
				//~ char message[LOG_MESSAGE_LEN] = {0};
				//~ snprintf(message, LOG_MESSAGE_LEN, "Allocation failed. Old limit of %d is being used\n", wf->limit);
				//~ printf("%s\n", message);
				//~ Logger(message, WARNING);
				//~ Logger("Allocation failed for enlarging list of Products.", WARNING);
					
				printf("Allocation failed. Old limit of %d is being used\n", wf->limit);
					
					   
				/** TODO: BREAK and do not cnt++/used++ **/
			   FreeProductStruct(wf->db, wf->used); // todo: rethink! Should I free?
			   fclose(fInputStream);
			   return 1; // log-message!
			   
            } // end of else
        } // end of wf-limit
		
		(wf->db + wf->used)->operatingSystem = strdup(OSBuf);
		if ((wf->db + wf->used)->operatingSystem == NULL)
		
		{
			/** TODO: BREAK and do not cnt++/used++ **/
			FreeProductStruct(wf->db, wf->used); // rethink, should I free only ONE line
			return 1; // error
		}
		
		(wf->db + wf->used)->markModel = strdup(markModelBuf);
		if ((wf->db + wf->used)->markModel == NULL)
		{
			/** TODO: BREAK and do not cnt++/used++ **/
			FreeProductStruct(wf->db, wf->used); // rethink, should I free only ONE line
			return 1; 
		}
		
        // numbers can be copied directly, there already is memory in the struct
        (wf->db + wf->used)->productCode_PK = productCodeBuf;
        (wf->db + wf->used)->screenSize = screenSizeBuf;
        (wf->db + wf->used)->ram = ramBuf;
		
		#ifdef DEBUG_M
		printf("DEBUG wf->db: Got (%d): %ld %s %s %.1lf %d",
					cnt,
					(wf->db + wf->used)->productCode_PK,
					(wf->db + wf->used)->markModel,
					(wf->db + wf->used)->operatingSystem,
					(wf->db + wf->used)->screenSize,
					(wf->db + wf->used)->ram);
		putchar('\n');
		#endif

		wf->used++;
		// Increment number of records successfully read
		cnt++;
    }
 
	// "sync" the pointers and update the limit
	wf->limit = wf->used;
 
	#ifdef DEBUG
	printf("\n Successfully ran '%s'\n", __FUNCTION__);
	#endif

	fclose(fInputStream);
    return 0;
} // end of function

/**
 * Writing a log message to file. Opens file, writes and then closes file.
 **/	
void WriteToProductFile(product_list *wf, char *fileName)
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
		for (int i = 0; i < wf->used; i++)
		{
		fprintf(fOutStream, "%ld,%s,%s,%0.1lf,%d\n",
			(wf->db + i)->productCode_PK,
			(wf->db + i)->markModel,
			(wf->db + i)->operatingSystem,
			(wf->db + i)->screenSize,
			(wf->db + i)->ram); 
		}
		fprintf(fOutStream, "\n");
		/** Closing file-stream **/
		fclose(fOutStream);
	}	
} // end of write

/** 
 * Lugemiseks kasuta realloc() funktsiooni, laiendades mäluala suurust jooksvalt lugemise käigus.
 * **/

void FreeProductStruct(product *p, unsigned int n)
{
	for (int i = 0; i < n; i++)
	{
		SafeFree((void **)&p[i].operatingSystem);
		SafeFree((void **)&p[i].markModel);
	}
	SafeFree((void **)&p); // free entire struct.
	//~ free(p);
	
	#ifdef DEBUG
	printf("\n Successfully ran '%s'\n", __FUNCTION__);
	#endif
} // end of function

/**
 * Function to check if allocated memory can be free without memory leaks.
 **/
void SafeFree(void **p)
{
	if (p != NULL && *p != NULL)
	{
		free(*p);
		*p = NULL;
	}
} // end of function

/**
 * Allocate an initial list, mostly for demonstrative purposes and compatibility
 * with both methods of inserting members (fixed and expandable)
 */
void AllocateList(product_list *wf, unsigned int n)
{
    wf->db = (product *)calloc(n, sizeof(product));
    if (wf->db == NULL)
    {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }
    wf->limit = n;
} // end of function

