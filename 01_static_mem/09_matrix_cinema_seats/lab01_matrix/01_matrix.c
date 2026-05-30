#include <stdio.h>
#include <inttypes.h>

#define SIZE 7

void ReadMatrix(int matrix[SIZE][SIZE], int rows, int cols);
void PrintMatrix(int data[SIZE][SIZE], int rows, int cols);
int32_t MainDiagonalNegSum(int data[SIZE][SIZE], int rows, int cols);
int64_t AboveAntiDiagonalPosProduct(int data[SIZE][SIZE], int rows, int cols);

int32_t MaxValueInArray(int rowArray[SIZE], int cols);
void MaxValueInMatrix(int data[SIZE][SIZE], int rows, int cols);

//~ int32_t MaxValueInMatrix(int data[SIZE][SIZE], int rows, int cols);

int main(void)
{
    int matrix[SIZE][SIZE];
    int rows = SIZE;
    int columns = SIZE;
    
    ReadMatrix(matrix, SIZE, SIZE);
    
    int32_t sum = MainDiagonalNegSum(matrix, rows, columns); 
    printf("\nThe sum of negative elements "
    "on the main diagonal is %" PRId32 " \n", sum);
    
    int64_t product = AboveAntiDiagonalPosProduct(matrix, rows, columns);
    printf("\nThe product of positive elements "
    "above the anti-diagonal is %" PRId64 " \n", product);
    
    MaxValueInMatrix(matrix, rows, columns);
    printf("\n");
    return 0;
}

/**
 * Description:    Reads a 2-dimensional array with size of rows x cols
 *                 from the standard input stream stdin.
 *
 * Parameters:     data - 2-dim array that needs to be read
 *                 rows - number of rows in data
 *                 cols - number of columns in data
 *
 * Return:         None
 */
void ReadMatrix(int data[SIZE][SIZE], int rows, int cols)
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            //printf("Enter value for matrix[%d][%d] = ", i, j);
            scanf("%d", &data[i][j]);
        }
    }
}

int32_t MainDiagonalNegSum(int data[SIZE][SIZE], int rows, int cols)
{
	int i, j;
	int32_t sum = 0;
	for (i = 0; i < rows; i++)
	{
		/** Main diagonal formula is " i == j "
		 * i -> array row
		 * j -> array coloumn
		**/
		j = i;
		
		/** Sum when the number on main diagonal is negative**/
		if (data[i][j] < 0)
			sum += data[i][j];
	}
	return sum;
}

int64_t AboveAntiDiagonalPosProduct(int data[SIZE][SIZE], int rows, int cols)
{
	int i, j;
	int64_t product = 1;	// NB! Must declare as int64_t!
	for (i = 0; i < rows ; i++)
	//~ for (i = 0; i < rows -1 ; i++)
	// must be rows -1, because last row has 1st element ON the anti-diagonal!
	{
		/** Anti-diagonal formula is " i + j == size -1 "
		 * i -> array row
		 * j -> array coloumn
		 * size -> defined length of array (preprocessor SIZE, starting from 1)
		 * 
		 * Thus, ON anti-diagonal,
		 *  -------j is 
		 * //~ j = (SIZE - 1) - i;
		 * or * //~ j = (rows - 1) - i;
		 * or j = (cols - 1) - i; **/
		
		//~ j = (SIZE - 1) - i; // <- on the diagonal
		for (j = 0; j < (SIZE - 1 - i); j++) 
		{
			if (data[i][j] > 0)
			{	
				product *= data[i][j];

			}
		}
	}
	return product;
}

int32_t MaxValueInArray(int rowArray[SIZE], int cols) // cols == row_len <- explained
{
	int i;
	/** Assign index 0 as first max-value for comparisons,
	 * do NOT assign arbitrary constant! (not 0, -1 or -10000)**/
	int32_t max = rowArray[0]; 	// should declare as int32_t datatype!
	for (i = 1; i < cols; i++)
	{
		if (rowArray[i] > max)
			max = rowArray[i];
	}
	return max;
}

//~ int32_t MaxValueInMatrix(int data[SIZE][SIZE], int rows, int cols)
void MaxValueInMatrix(int data[SIZE][SIZE], int rows, int cols)
{
	int i;
	int result = 0;
	for (i = 0; i < rows; i++) // rows == colmn_len 
	{
		result = MaxValueInArray(data[i], cols); // cols == row_len <- explained
		printf("\nGreatest number on row %d is %d", i, result);
	}
}
