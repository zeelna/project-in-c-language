#include <stdio.h>
#include <stdlib.h>
#include "file_helper.h"
#include "data_processor.h"
#include "main.h"

int main(void)
{
	DownloadCovidData(SPACE_DELIMITED);
	char outFileName[FILE_NAME_LEN] = {0};
	strcpy(outFileName, OUT_FILE_NAME_SPC_DELIM);
	
	//~ DownloadCovidData(CSV);
	//~ char *outFileName =  OUT_FILE_NAME_CSV;
	
	// My added code.
	entry lineEntry[READ_LIMIT] = {0};
	int limit = READ_LIMIT;
	
	int count = ReadFile(lineEntry, limit, outFileName);
	
	printf("count: %d", count);
	
	
	int nEntries = sizeof(lineEntry) / sizeof(entry);

    while (1)
    {
        switch (ChooseMenuAction())
        {
			case 1:
                //~ Base task part 1
                puts("Nakatumiste arv 14 päeva jooksul: ");
				PrintStructArrayBackWards(lineEntry, count, 14);
                
                puts("Suurimate nakatumiste arvuga päevad (10): ");
                qsort(lineEntry, (size_t)nEntries, sizeof(entry), ComparFuncTop10Days);
                
				PrintStructArray(lineEntry, 10);	
                
                break;
            case 2:
                //~ Sort and print the integer array

                //~ Base task part 1
                puts("Nakatumiste arv viimase 7 päeva jooksul: ");
                
                break;
            case 3:

                puts("Nakatumiste arv sellele eelneva 7 päeva jooksul: ");

                
                break;
            case 4:

                puts("Perioodi vahemikud ja nakatunute koguarv neil perioodidel: ");
                

                break;
            case 5:

                puts("kas nakatumine kahe võrreldava perioodi vahel " 
				"on vähenenud, kasvanud või jäänud samaks. "
				"Näita protsenti kahe komakohaga: ");

                break;

            case 0:
                /* Exit */
                exit(EXIT_SUCCESS);
                break;
            default:
                printf("Only selections from 1 to 5 and 0 are accepted\n");
        }
    }
	#ifdef DEBUG
	printf("\n Successfully ran '%s'\n", __FUNCTION__);
	#endif
	
    return EXIT_SUCCESS;
}

unsigned ChooseMenuAction(void)
{
    unsigned ans;
    printf("\n\nVali tegevus!\n\n");
    printf("1. Leia nakatumiste arv viimase 14 päeva jooksul\n");
    printf("2. Leia nakatumiste arv viimase 7 päeva jooksul\n");
    printf("3. Leia nakatumiste arv sellele eelneva 7 päeva jooksul\n");
    printf("4. Väljasta perioodi vahemikud ja nakatunute koguarv neil perioodidel\n");
    
    printf("5. Leia ja kuva kas nakatumine kahe võrreldava perioodi vahel" 
    "on vähenenud, kasvanud või jäänud samaks. Näita protsenti kahe komakohaga.\n");
    
    printf("0. Exit\n\n");
    
    printf("> ");
    scanf("%u", &ans);
    return ans;
}
