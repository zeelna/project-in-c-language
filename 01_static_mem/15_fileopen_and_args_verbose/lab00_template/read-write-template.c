#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE *fi;
	int temp;
	char inputFile[] = {"numbers2.txt"};
	
	fi = fopen(inputFile, "r");
	if (fi == NULL)
	{
		printf("Error opening file '%s'\n", inputFile);
		perror("");		// error checking ("permissions denied")
		exit(EXIT_FAILURE);
	}
	
	/** Check to see if file**/
	const char outputFile[] = {"out.txt"};
	FILE *fo;
	fo = fopen(outputFile, "w");
	if (fo == NULL)
	{
		/** Close input file, eventhough output file cannot be opened**/
		fclose(fi);
		
		/** Let know of error!**/
		printf("Error opening file '%s'\n", outputFile);
		
		/** Enable error-messages "Permission denied" etc**/
		perror("");		// error checking ("permissions denied")
		
		/** Exit**/
		exit(EXIT_FAILURE);
	}

	
	while (fscanf(fi, "%d", &temp) == 1) // 1 reads one variable! BETTER!
	//~ while (fscanf(fi, "%d", &temp) != EOF) // infinitely until \n! BAD!
	{
		printf("Got: %d\n", temp); 		// input file
		fprintf(fo, "Got %d\n", temp); //output file
	}
	fclose(fi);
	fclose(fo);
	return 0;
	
}
