/**
 * File:         distance_converter.c
 * Author:       Frank Christopher Kirch
 * Created:      04.10.2023
 * Last edit:    04.10.2023
 *
 * Description:  Reads an array filled with integers (representing distances 
 *               in kilometers) and converts it to miles. 
 *               Prints the sum of all distances in miles.
 */
#include <stdio.h>
 
#define DIST_COUNT 4
#define MILES_IN_KM 1.609f
 
void ReadDistances(int dist[], int n);
void ConvertArrToMiles(int distKm[], float distMi[], int n);
void PrintDistances(float dist[], int n);
float SumOfAllDist(float dist[], int n);
 
int main(void)
{
    int distancesInKilometers[DIST_COUNT];
    float distancesInMiles[DIST_COUNT], totalDist;
    
    ReadDistances(distancesInKilometers, DIST_COUNT);
    ConvertArrToMiles(distancesInKilometers, distancesInMiles, DIST_COUNT);
    PrintDistances(distancesInMiles, DIST_COUNT);
    
    totalDist = SumOfAllDist(distancesInMiles, DIST_COUNT);
    printf("The sum of all distances is %.2f miles!\n", totalDist);
    return 0;
}
 
 
/**
 * Description:    Asks the user for n integers and stores them in an array.
 *
 * Parameters:     dist - array to store distances entered by the user
 *                 n - number of distances to read (also length of array)
 *
 * Return:         none
 */
void ReadDistances(int dist[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("Enter distance %d in km (integer): ", i + 1);
        scanf("%d", &dist[i]);
    }
}
 
 
/**
 * Description:    Converts an array filled with distances in kilometers to
 *                 miles and stores them in the second array.
 *
 * Parameters:     distKm - array with distances in kilometers
 *                 distMi - array to store calculated distances in miles
 *                 n - number of distances to convert (length of both arrays)
 *
 * Return:         none
 */
void ConvertArrToMiles(int distKm[], float distMi[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        distMi[i] = (float)distKm[i] / MILES_IN_KM;
    }
}
 
 
/**
 * Description:    Prints the given array of distances with 2 decimal places 
 *                 after the comma.
 *
 * Parameters:     dist - array with distances as decimals
 *                 n - length of the array.
 *
 * Return:         none
 */
void PrintDistances(float dist[], int n)
{
    int i;
    printf("The converted distances are: ");
 
    for (i = 0; i < n; i++)
    {
        printf("%.2f ", dist[i]);
    }
    printf("\n");
}
 
/**
 * Description:    Sums up all the distances in the array, returns the sum
 *
 * Parameters:     dist - array with distances as decimals
 *                 n - length of the array.
 *
 * Return:         the sum of given array members (total distance)
 */
float SumOfAllDist(float dist[], int n)
{
    int i;
    float sum = 0;
 
    for (i = 0; i < n; i++)
    {
        sum += dist[i];
    }
    return sum;
}
