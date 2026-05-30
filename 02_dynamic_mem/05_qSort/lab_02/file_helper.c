/**
 * File:         file_helper.c
 * Author:       Frank Christopher Kirch
 * Created:      16.03.2024
 * Modified:     30.05.2026
 *
**/

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <curl/curl.h>
#include "file_helper.h"


/*
 * Downloads the covid opendata. If file exists, prompts before 
 * downloading it again.
 */
void DownloadCovidData(enum Type destFileType)
{
	char *url = DOWNLOAD_URL;
	char *outFileName = (destFileType == CSV) ? OUT_FILE_NAME_CSV: OUT_FILE_NAME_SPC_DELIM;
	
	if (CheckIfFileExists(outFileName))
	{
		printf("Warning! The file ""%s"" already exists!\n", outFileName);
		printf("Are you sure you wish to download again?\nEnter [Y] or [N]\n");
		if (PromptYesNo() == false)
			return;
	}
	
	DownloadFile(url, outFileName);
	
	if (destFileType == SPACE_DELIMITED)
	{
		ReplaceCharInFile(outFileName, ',', ' ');
	}

}

/*
 * Prompts for user confirmation until received
 */
bool PromptYesNo(void)
{
	char c;
	while (true)
	{
		c = (char)getchar();
		if (c == '\n')
			continue;
		if (c == 'y' || c == 'Y')
			return true;
		else if (c == 'n' || c == 'N')
			return false;
		else
			printf("Please enter y or n!\n");
	}
}

/*
 * Checks if file exists
 */
bool CheckIfFileExists(char *f)
{
	return (!access(f, F_OK));
}

/*
 * file downloader curl sample
 * https://curl.se/libcurl/c/url2file.html
 */
size_t WriteData(void *ptr, size_t size, size_t nmemb, void *stream)
{
	size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
	return written;
}

/*
 * file downloader curl sample
 * https://curl.se/libcurl/c/url2file.html
 */
void DownloadFile(char *url, const char *fname)
{
	CURL *curl_handle;

	FILE *fOutput;
 
	curl_global_init(CURL_GLOBAL_ALL);
 
	/* init the curl session */
	curl_handle = curl_easy_init();
 
	/* set URL to get here */
	curl_easy_setopt(curl_handle, CURLOPT_URL, url);
 
	/* Switch on full protocol/debug output while testing */
	//curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);
 
	/* disable progress meter, set to 0L to enable it */
	curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
 
	/* send all data to this function	*/
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteData);
 
	/* open the file */
	fOutput = fopen(fname, "wb");
	if (fOutput) {
 
		/* write the page body to this file handle */
		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, fOutput);
 
		/* get it! */
		curl_easy_perform(curl_handle);
 
		/* close the header file */
		fclose(fOutput);
	}
 
	/* cleanup curl stuff */
	curl_easy_cleanup(curl_handle);
 
	curl_global_cleanup();
}

/*
 * Replaces all characters matching to key to replacement in the given file.
 */
void ReplaceCharInFile(char *fName, char key, char replacement)
{
	int ch;
	FILE *fp = fopen(fName, "r+");
	
	if (fp != NULL)
	{
		while ((ch = fgetc(fp)) != EOF)
		{
			if (ch == key)
			{
				fseek(fp, ftell(fp) - 1, SEEK_SET);
				fputc(replacement, fp);
			}
		}
		fclose(fp);
	}
}

