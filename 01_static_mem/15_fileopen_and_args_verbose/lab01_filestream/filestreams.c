#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	/** pointer for file stream (input file streams) **/
	FILE *fInputStream;
	
	int temp;
	char inputFile[] = {"input.txt"};
	
	fInputStream = fopen(inputFile, "r");
	if (fInputStream == NULL)
	{
		printf("Error opening file '%s'\n", inputFile);
		perror("");		// error checking ("permissions denied")
		exit(EXIT_FAILURE);
	}
	
	/** pointer for file stream (output file streams) **/
	FILE *fOutputEvenNrStream;
	
	const char outputEvenFile[] = {"even.txt"};
	fOutputEvenNrStream = fopen(outputEvenFile, "w");

	/** Check file stream of "even.txt" **/
	if (fOutputEvenNrStream == NULL)
	{
		/** Close input file, eventhough output file cannot be opened**/
		fclose(fInputStream);
		
		/** Let know of error!**/
		printf("Error opening file '%s'\n", outputEvenFile);
		
		/** Enable error-messages "Permission denied" etc**/
		perror("");		// error checking ("permissions denied")
		
		/** Exit**/
		exit(EXIT_FAILURE);
	}
	
	/** pointer for file stream (output file streams) **/
	FILE *fOutputOddNrStream;
	
	const char outputOddFile[] = {"odd.txt"};
	fOutputOddNrStream = fopen(outputOddFile, "w");
	/** 3. Check file stream of "odd.txt" **/
	if (fOutputOddNrStream == NULL)
	{
		/** Close input file, eventhough output file cannot be opened**/
		fclose(fOutputEvenNrStream); // DO NOT FORGET TO CLOSE ALL!!! OPENED FILES
		fclose(fInputStream);
		
		/** Let know of error!**/
		printf("Error opening file '%s'\n", outputOddFile);
		
		/** Enable error-messages "Permission denied" etc**/
		perror("");		// error checking ("permissions denied")
		
		/** Exit**/
		exit(EXIT_FAILURE);
	}

	/** Writing contents to file! **/
	while (fscanf(fInputStream, "%d", &temp) == 1) // 1 reads one variable! BETTER!
	{
		printf("Got: %d\n", temp); 		// input file
		if (temp % 2 == 0 && temp > 0)
			fprintf(fOutputEvenNrStream, "Got %d\n", temp);
		else if (temp % 2 == 1 && temp > 0)
			fprintf(fOutputOddNrStream, "Got %d\n", temp); //output file
	}
	
	/** Close files once terminating program  - DO NOT FORGET!!!**/
	fclose(fInputStream);
	fclose(fOutputOddNrStream);
	fclose(fOutputEvenNrStream);
	return 0;
	
}
