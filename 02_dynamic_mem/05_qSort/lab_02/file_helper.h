/**
 * File:         file_helper.h
 * Author:       Frank Christopher Kirch
 * Created:      16.03.2024
 * Modified:     30.05.2026
 *
**/

#ifndef FILE_HELPER_H
#define FILE_HELPER_H

#include <stdbool.h>

// https://opendata.digilugu.ee
#define DOWNLOAD_URL "https://opendata.digilugu.ee/opendata_covid19_tests_total.csv"

// predefined output file names depending on type
#define OUT_FILE_NAME_CSV "opendata_covid19_tests_total.csv"
#define OUT_FILE_NAME_SPC_DELIM "opendata_covid19_tests_total.txt"

// enumeration to choose delimiter type for the file that will be written
enum Type {CSV, SPACE_DELIMITED};

/* Description: Downloads COVID-19 daily statistics opendata for Estonia.
 *              If download is specified as space delimited, the file will be
 *              first downloaded as original and then rewritten to change
 *              commas into spaces.
 *              NOTE: Only works for simple cases such as this. Do not use it
 *              in general for CSV! It will break!
 * 
 * Parameter:   enum type - type of file to store on the disk after download.
 * 
 * Example use cases:
 *              DownloadCovidData(CSV);
 *              DownloadCovidData(SPACE_DELIMITED);
 */
void DownloadCovidData(enum Type destFileType);

/*
 * Description: Asks for user input of y or n. Case insensitive. Returns only
 *              after suitable input is received. 
 *              Note: doesn't clean the buffer if there are additional chars.
 * 
 * Return:      true if input was [yY] or false if [nN]. 
 */
bool PromptYesNo(void);

/*
 * Description: Checks if the file is accessible on the drive for the user.
 * 
 * Parameter:   f - string with the file path to test
 * 
 * Return:      true if it's accessible, false if not
 */
bool CheckIfFileExists(char *f);

/*
 * Description: Downloads the file and stores it on disk.
 *              Based on libcurl sample: https://curl.se/libcurl/c/url2file.html
 * 
 * Parameter:   url - string with the download URL
 *              fname - name of the output file
 */
void DownloadFile(char *url, const char *fname);

/*
 * https://curl.se/libcurl/c/url2file.html
 */
size_t WriteData(void *ptr, size_t size, size_t nmemb, void *stream);

/*
 * Description: Replaces one character with another throughout the given file.
 * 
 * Parameter:   fName  - string with the name of the file
 *              key - character that will be replaced
 *              replacement - character that will be written instead
 */
void ReplaceCharInFile(char *fName, char key, char replacement);

#endif
