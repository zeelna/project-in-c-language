/**
 * File:        8_1_date_base.c
 * Author:      Risto Heinsar
 * Created:     05.10.2015
 * Modified:    12.10.2023
 *
 * Description: Basecode for the lab task to switch rows and columns in a
 *              matrix. Matrix is generated randomly and can be regenerated.
 *              Program runs infinitely in a menu loop until user exits.            
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Limits for the matrix size */
#define LIMIT_ROWS 10
#define LIMIT_COLS 20

#define MIN_ROWS 1
#define MIN_COLS 1

/* Limits for the random numbers */
#define RAND_LOWER 0
#define RAND_UPPER 99

/* Limits for the menu */
#define MENU_OPTION_MIN 0
#define MENU_OPTION_MAX 9

#define EXIT 1
#define NOT_EXIT 0

#define IS_DELETED 1
#define NOT_DELETED 0


int Menu(void);
int GetIntInRange(int min, int max);
void GenerateMatrix(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols);
void DisplayMatrix(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols);

/** Non-template functions: **/
int GenerateRandomNum(int min, int max);
int AskInput(char prompt[], int min, int max);

void SwitchRows(int matrix[LIMIT_ROWS][LIMIT_COLS], int cols,
				int sourceRow, int destinationRow);

void SwitchCols(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows,
				int sourceCol, int destinationCol);
                
int DeleteCol(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols, int deleteCol);
int DeleteRow(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols, int deleteRow);                

int IsMatrixDeleted(int rows, int cols, char deleteMessage[]); // char prompt[]

int AddCol(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols, int addColNr);
int AddRow(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols, int addRowNr);

void TransposeMatrix(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols);

int main(void)
{
    int data[LIMIT_ROWS][LIMIT_COLS] = {{0}};
    
    
    /** Create a matrix before going into the menu! Version 2**/
	int userRows;// = AskInput("width", MIN_ROWS, LIMIT_ROWS);
	int userCols;// = AskInput("length", MIN_COLS, LIMIT_COLS);
	//~ GenerateMatrix(data, userRows, userCols);
	
    int menuOption = 1; // generate matrix by jumping to Menu-1 immediately!
    
	int exit = NOT_EXIT;
    while (exit == NOT_EXIT)//(!exit)
    {
        //menuOption = Menu();
        switch (menuOption)
        {
            case 1:
                puts("Case 1: Enter new matrix dimensions and generate matrix");
                /** 1. Get the dimensions of the desired matrix
                 * 2. Call GenerateMatrix() to generate it **/
                userRows = AskInput("width", MIN_ROWS, LIMIT_ROWS);
				userCols = AskInput("length", MIN_COLS, LIMIT_COLS);
				
                GenerateMatrix(data, userRows, userCols);
                break;
            case 2:
                puts("Case 2: Print matrix");
                //~ if (!IsMatrixDeleted(userRows, userCols, 
                    //~ "Cannot print matrix. Matrix has been previously deleted. \nReturning to menu\n"))
                DisplayMatrix(data, userRows, userCols); // must we INDENT??? (i'd like to print empty matrix in all cases.)
                break;
            case 3:
                puts("Case 3: Switch rows");
                if (!IsMatrixDeleted(userRows, userCols, 
                    "Cannot switch any rows! Matrix has been previously deleted. \nReturning to menu\n"))
                {
                    /** Asking input from user to switch Rows **/    
                    int sourceRow = AskInput("source row", MIN_ROWS, userRows);
                    int destinationRow = AskInput("destination row", MIN_ROWS, userRows);
                
                    /** Switching columns. NB!!!! Must offset -1, user enters REALNUMBERS, not INDEX**/
                    SwitchRows(data, LIMIT_COLS, sourceRow - 1, destinationRow -1); // must offset, user enters real-numbers (not index-nr)
                }
                break;
            case 4:
                puts("Case 4: Switch columns");
                if (!IsMatrixDeleted(userRows, userCols, 
                    "Cannot switch any columns! Matrix has been previously deleted. \nReturning to menu\n"))
                {
                    /** Asking input from user to switch Columns**/
                    int sourceCol = AskInput("source column", MIN_COLS, userCols);
                    int destinationCol = AskInput("destination column", MIN_COLS, userCols);
                    
                    /** Switching columns. NB!!!! Must offset -1, user enters REALNUMBERS, not INDEX**/
                    SwitchCols(data, LIMIT_ROWS, sourceCol - 1, destinationCol - 1); // must offset, user enters real-numbers (not index-nr)
                }
                break;
            case 5:
				puts("Case 5: Delete a row");
                if (!IsMatrixDeleted(userRows, userCols, 
                    "Cannot delete any rows! Matrix has been previously deleted. \nReturning to menu\n")) //~ if (userCols < MIN_COLS || userRows < MIN_ROWS)
                {
                    int deleteRow = AskInput("a row to be deleted, ", MIN_ROWS, userRows);
                    /** Function deletes 1 row, and return amount of rows - 1**/
                    userRows = DeleteRow(data, userRows, userCols, deleteRow);  
                }
                break;
                
			case 6:
				puts("Case 6: Delete a column");
				if (!IsMatrixDeleted(userRows, userCols,
                    "Cannot delete any columns! Matrix has been previously deleted. \nReturning to menu\n"))  //~ if (userCols < MIN_COLS || userRows < MIN_ROWS)
                {
                    int deleteCol = AskInput("a column to be deleted, ", MIN_COLS, userCols);
                    /** Function deletes 1 column, and return amount of columns - 1**/
                    userCols = DeleteCol(data, userRows, userCols, deleteCol);
                }
				break;	
            
            case 7:
                puts("Case 7: Add a row");
                
                /** Populate existing matrix**/
                if (userRows >= LIMIT_ROWS)
                    printf("Cannot add row to matrix! Matrix can have at most %d rows. \nReturning to menu\n", LIMIT_ROWS);
                else
                {
                    int addRowNr = AskInput("a position where a new row will be added, ", MIN_ROWS, userRows); // fix: userCols 0, MIN_COLS 1
                    
                    /** Function deletes 1 row, and return amount of "rows - 1"**/
                    userRows = AddRow(data, userRows, userCols, addRowNr);
                    
                    /** Explain: 'AddRow' return "userRows +1",
                     *           but we need to userCols (0) to be 1 (thus if 0 then "userCols == MIN_COLS").
                     *           TO print the matrix!!!!
                     * Thus, Ternary: **/
                    userCols = (userCols < MIN_COLS) ? MIN_COLS : userCols; // WITHOUT this Ternary! AddRow does not work!!!!
                    
                    /** Küsimus: !!!Ülemise ternary kohta!
                     * kas rida 180(178) Ternary operatsioon on õigustatud?
                     *  Nimelt, toon 0-väärtusega tabeli columni väärtusele 1 (st. MIN_COLS), et oleks võimalik tabelit printida.
                     * Kordan seda ka real 160(158) **/
                    
                    /** Teacher feedback:
                     * 1 - pigem ei ole õigustatud  sest kasutaja ei soovinud tulpa lisada. 
                     * Lisaks sa pead arvestama, 
                     * et kui genereerimisse läksid nullise tulpade arvuga,
                     *  siis tegelikult genereerimist ei toimunud 
                     * ja näidatakse tõenäoliselt vana väärtust.  **/
                }
                break;
            case 8:
                puts("Case 8: Add a column");
                /** Populate existing matrix**/
                if (userCols >= LIMIT_COLS)
                    printf("Cannot add column to matrix! Matrix can have at most %d columns. \nReturning to menu\n", LIMIT_COLS);
                else
                {
                    
                    int addColNr = AskInput("a position where a new column will be added, ", MIN_COLS, userCols); // fix: userCols 0, MIN_COLS 1
                    /** Function deletes 1 column, and return amount of columns - 1**/
                    
                    userCols = AddCol(data, userRows, userCols, addColNr);
                    
                    /** Explain: 'AddCol' returns "userCols +1",
                     *           but we need to userRows (0) to be 1 (thus if 0, then "userRows = MIN_ROWS").
                     *           TO print the matrix!!!!
                     * Thus, Ternary: **/
                    userRows = (userRows < MIN_ROWS) ? MIN_ROWS : userRows; // WITHOUT this Ternary! AddRow does not work!!!!
                    
                    /** Küsimus: !!!Ülemise ternary kohta!
                     * kas rida 180(178) Ternary operatsioon on õigustatud?
                     *  Nimelt, toon 0-väärtusega tabeli columni väärtusele 1 (st. MIN_COLS), et oleks võimalik tabelit printida.
                     * Kordan seda ka real 160(158) **/
                    
                    /** Teacher feedback:
                     * 1 - pigem ei ole õigustatud  sest kasutaja ei soovinud tulpa lisada. 
                     * Lisaks sa pead arvestama, 
                     * et kui genereerimisse läksid nullise tulpade arvuga,
                     *  siis tegelikult genereerimist ei toimunud 
                     * ja näidatakse tõenäoliselt vana väärtust.  **/
                }
                
                break;
                
            case 9:
                puts("Case 9: Transpose matrix");
                
                if (!IsMatrixDeleted(userRows, userCols,
                    "Cannot Transpose the matrix! Matrix has been previously deleted. \nReturning to menu\n"))  //~ if (userCols < MIN_COLS || userRows < MIN_ROWS)
                {
                    /** Uncomment if-else, when we are permitted to transpose 10x20 matrix into 20x10 matrix (breaching LIMIT_ROWS(10) **/
                    //~ if (userCols > LIMIT_ROWS || userRows > LIMIT_COLS)
                        //~ printf("Cannot transponse matrix, because matrix width (rows) larger than allowed.\n");
                    //~ else
                    //~ { 
                            TransposeMatrix(data, userRows, userCols);
                            int temp = userRows;
                            userRows = userCols;
                            userCols = temp;
                    //~ }            // remove when if-else not needed (including curly-brackets.
                }
                break;
            case 0:
                puts("Case 0: Exiting");
                exit = EXIT; // stack smashing detected! FIX with 10x20 matrix.
                break;
            default:
                puts("Case ?: Sorry! We didn't understand Your request");
                break;
        }
        /** **/
        if (IsMatrixDeleted(userRows, userCols, "")) // fix: prints twice.
        {
            userRows = 0;
            userCols = 0;
        }
        
        if (!exit)
            /** Print menu-prompt for next-iteration**/ 
            menuOption = Menu(); // fix: Prints on QUIT!
    }

    return 0;
}

/**
 * Description:    Displays the possible menu options to the user,
 *                 allows to select an action to perform.
 *
 * Parameters:     None
 *
 * Return:         Menu item number selected
 */
int Menu(void)
{
    int selection;
    putchar('\n');
    puts("Select Your action!");
    puts("1 - Generate new matrix");
    puts("2 - Display matrix");
    puts("3 - Switch rows");
    puts("4 - Switch columns");
    puts("5 - Delete a row");
    puts("6 - Delete a column");
    puts("7 - Add a row");
    puts("8 - Add a column");
    puts("9 - Transpose the matrix");
    puts("0 - Exit program");
    selection = GetIntInRange(MENU_OPTION_MIN, MENU_OPTION_MAX);
    return selection;
}
/**
 * Description:    Ask user input
 *
 * Parameters:     prompt[] - value we want to ask from user.
 * 				   min - minimum allowed input
 * 				   max - maximum allowed input
 *
 * Return:         Return the valid input
 */
int AskInput(char prompt[], int min, int max)
{
	/** Ternary operation - if min is bigger than max, overwrite max to min's value  **/
    max = (max < min) ? min : max;
    
    printf("\nEnter %s between %d and %d", prompt, min, max);
    int result = GetIntInRange(min, max);
	return result;
}

/**
 * Description:    Asks the user for an integer in between the given limits.
 *                 Reprompts if input is out of bounds.
 *
 * Parameters:     min - lower limit for the user input (inclusive)
 *                 max - upper limit for the user input (inclusive)
 *
 * Return:         Number within the specified limits
 */
int GetIntInRange(int min, int max)
{
    int num;
    do
    {
        printf("\n> ");
        scanf("%d", &num);
        //~ if (num < min || num > max)
        if (num < min || num > max)
        {
            printf("\nRetry! Input must be in between %d and %d", min, max);
        }
    }
    while (num < min || num > max);
    return num;
}

/**
 * Description:    Generates random numbers and stores them into the matrix. 
 *                 Numbers are only generated within the area specified by rows
 *                 and cols (regardless of the defined size). 
 *                 Random numbers will be in between RAND_LOWER and RAND_UPPER.
 *GenerateMatrix(data, userRows, userCols);
 * Parameters:     matrix - 2-dimensional array to store the numbers into, 
 *                          size at declaration is given by macros.
 *                 rows - number of rows to generate
 *                 cols - number of columns to generate
 *
 * Return:         none
 */
void GenerateMatrix(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols)
{
    /* write your function body here!*/
    srand(time(NULL));
    
    int i, j;
    for (i = 0; i < rows; i++)
    {
		for (j = 0; j < cols; j++)
		{
			matrix[i][j] = GenerateRandomNum(RAND_LOWER, RAND_UPPER);
		}
	}
}

/**
 * Description:    HELPER-FUNCTION: Generates random numbers
 *                 Random numbers will be in between RAND_LOWER and RAND_UPPER.
 *
 * Parameters:     integers to restrict the value into a range.               
 *                 max - number of maximum allowed value (included)
 *                 max - number of minimum allowed value (included)
 * Return:         random generated number
 */
int GenerateRandomNum(int min, int max)
{
	int result = rand() % (max - min + 1) + min;
	return result;
}

/**
 * Description:    Displays the matrix with its columns aligned for integers
 *                 up to 99(9?). Only prints the area specified by rows x cols.
 * 
 * Parameters:     matrix - matrix that is printed.
 *                 rows - number of rows to display
 *                 cols - number of columns to display
 *
 * Return:         none
 */
void DisplayMatrix(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols)
{
	/** Using while, as exercise spec:**/
	int i = 0;
	int j = 0;
	int value = 0;
	while (i < rows)
	{
		j = 0; // DO NOT FORGET THIS!!!!
		while (j < cols)
		{
			value = matrix[i][j];
			printf("%4d", value);
			j++;
		}
		putchar('\n');
		i++;
	}
}

/**
 * Description:    switch the matrix's rows. Updated the matrix.
 * 				   Uses "temp" variable to change.
 * 
 * Parameters:     matrix - matrix that is printed.
 *                 rows - number of rows to display
 *                 cols - number of columns to display
 * 				   changing rows - new rows
 *
 * Return:         none
 */
void SwitchRows(int matrix[LIMIT_ROWS][LIMIT_COLS], int cols,
				int sourceRow, int destinationRow)
{
	int temp = 0;

	for (int j = 0; j < cols; j++)
	{
		temp = matrix[sourceRow][j];
		matrix[sourceRow][j] = matrix[destinationRow][j];
		matrix[destinationRow][j] = temp; 
	}
}

/**
 * Description:    switch the matrix's columns. Updated the matrix.
 * 				   Uses "temp" variable to change.
 * 
 * Parameters:     matrix - matrix that is printed.
 *                 rows - number of rows to display
 *                 cols - number of columns to display
 * 				   changing columns - new columns
 *
 * Return:         none
 */
void SwitchCols(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows,
				int sourceCol, int destinationCol)
{
	int temp = 0;
	
	for (int i = 0; i < rows; i++)
	{
		temp = matrix[i][sourceCol];
		matrix[i][sourceCol] = matrix[i][destinationCol];
		matrix[i][destinationCol] = temp;
	}
	
}
/**
 * Description:    Delete row of matrix. Updated the matrix.
 * 
 * Parameters:     matrix - matrix that is printed.
 *                 rows - number of rows to display
 *                 cols - number of columns to display
 * 				   deleteRow - row nr (not index, thus currently is +1)
 *
 * Return:         updated row count (row + 1)
 */

int DeleteRow(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols, int deleteRow)
{
    int deleteRowIndex = deleteRow - 1; //offset by 1 (user enters real-nr)

    /** Deleting row, and shifting rows**/
    
        for (int i = deleteRowIndex; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                matrix[i][j] = matrix[i + 1][j];
            }
        }
        
    /** Separate for-cycle to zero-out values **/
        if (deleteRowIndex == (rows - 1)) // DO NOT FORGET TO -1
        {
            for (int j = 0; j < cols; j++)
            {
                matrix[deleteRowIndex][j] = 0; // NULL
            }
        }
    /** DO NOT FORGET: Delete the count of rows by 1**/
    return rows - 1; // we have deleted a row, thus update nr. of rows.
}


/**
 * Description:    Delete column of matrix. Updated the matrix.
 * 
 * Parameters:     matrix - matrix that is printed.
 *                 rows - number of rows to display
 *                 cols - number of columns to display
 * 				   deleteCol - col nr (not index, thus currently is +1)
 *
 * Return:         updated column count (+1)
 */
int DeleteCol(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols, int deleteCol)
{
    int deleteColIndex = deleteCol - 1; //offset by 1 (user enters real-nr)
    
        /** Main for-cycle!**/
        for (int i = 0; i < rows; i++)
        {
            /** Deleting col that is not last-col**/
            for (int j = deleteColIndex; j < cols; j++)
            {
                matrix[i][j] = matrix[i][j + 1];
            }
        }
        
        /** Separate for-cycle to zero-out values**/
        if (deleteColIndex == (cols - 1)) // DO NOT FORGET TO -1
        {
            for (int i = 0; i < rows; i++)
            {
                matrix[i][deleteColIndex] = 0; // NULL
            } 
        }
    /** DO NOT FORGET: Delete the count of Columns by 1**/
    return cols - 1; // we have deleted a column, thus update nr. of ""cols".
}

/** uhtalt selle ülesande raames nullimine ei ole oluline  sest see rida ei saaks ühelgi juhul uuesti nähtavaks. 
 * Turvalisuse aspektist sa tahad, et sinu tundlikud andmed on nullitud pärast mingi mäluala kasutamise lõpetamist,
 *  et seda ei saaks järgmine rakendus välja nihverdada.
 *  Jõudluse kohapealt, kui nullida on vaja, siis mina ei teeks seda if/else kujundina,
 *  vaid ma teeks sealolevas tsüklis ainukese lükkena nihutamise.
 *  Seejärel alla kirjutaks eraldi tsükli,
 *  kus vaid konkreetne rida/veerg nullitaks eraldi
 *  (if/else tekitab vajaduse kontrollida kuniks kompilaatoor välja ei optimeeri ning vähendab koodi loetavust
 * 
 * Selle viimase kohapealt on tegelikult eraldi reegel ka
 *  - kõik tegevused mida sa teed ainult tsükli esimesel või viimasel iteratsioonil on kasulik tuua tsüklist välja,
 *    kas siis selle ette või pärast tsüklit. Sellised if (i == 0) või if (i == n - 1) asjad on üsna nõmedad,
 *    muutes koodi aeglasemaks, keerukamaks ja halvemini loetavamaks. 
 * Mõnel harval juhul võbi eksisteerida olukorrad küll kus see vajadus tekib (teoreetiliselt, ise pole kohanud)**/

/**
 * Description:    Checking whether matrix rows or columns has 0
 * 
 * Parameters:  
 *                 rows - number of rows to display
 *                 cols - number of columns to display
 *
 * Return:         boolean - IS_DELETED (1) or NOT_DELETED(0)
 */
int IsMatrixDeleted(int rows, int cols, char deleteMessage[])
{
    if (rows < MIN_ROWS || cols < MIN_COLS) 
    {
        printf(deleteMessage);
        return IS_DELETED;
    } // no need for else, naturally occurs due to above "return IS_DELETED"
    return NOT_DELETED;
}
/**
 * Description:    Add a row to the matrix to user-requested row-nr
 * 
 * Parameters:     matrix - matrix that is printed.
 *                 rows - number of rows to display
 *                 cols - number of columns to display
 * 				   addRowNr - row nr (not index, thus currently is +1)
 * 
 * Return:         updated count of rows (+1)
 */
 
/** Frank version! - WORKS, but over-engineered **/
//~ int AddRow(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols, int addRowNr)
//~ {
    //~ int addRowIndex = addRowNr - 1; //offset by 1 (user enters real-nr)
    //~ int temp = 0;

    //~ for (int j = 0; j < cols + 1; j++)
    //~ {
        //~ /** Last column if-conditional.**/
        //~ if (addRowIndex >= (rows - 1))
        //~ {
            //~ temp = matrix[addRowIndex][j];
            //~ matrix[addRowIndex][j] = GenerateRandomNum(RAND_LOWER, RAND_UPPER);
            //~ matrix[addRowIndex + 1][j] = temp;
        //~ }
        
        //~ /** If user did not choose the last row**/
        //~ else
        //~ { 
            //~ for (int i = rows+1; i > addRowIndex; i-= 2)
            //~ {
                //~ temp = matrix[i-1][j];
                //~ matrix[i-1][j] = matrix[i-2][j]; // important algorithm
                //~ matrix[i][j] = temp;
                
            //~ }
            //~ matrix[addRowIndex][j] = GenerateRandomNum(RAND_LOWER, RAND_UPPER);
        //~ }
    //~ }
    //~ return rows + 1;
//~ }
 
 
/** Teacher's version '**/
int AddRow(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols, int addRowNr)
{
    int addRowIndex = addRowNr - 1; //offset by 1 (user enters real-nr)
    /** Shift until we are at index/pos where new row will be added (in next code-section row 606)**/
    for (int i = rows - 1; i >= addRowIndex; i--) 
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i + 1][j] = matrix[i][j];
        }
    }
    
    /** Adding randomly generated value to the newly generated zero-d out row. **/
    for (int i = 0; i < cols; i++)
    {
        matrix[addRowIndex][i] = GenerateRandomNum(RAND_LOWER, RAND_UPPER);
    }
    return rows + 1;
} 
 
/**
 * Description:    Add a row to the matrix to user-requested row-nr
 * 
 * Parameters:     matrix - matrix that is printed.
 *                 rows - number of rows to display
 *                 cols - number of columns to display
 * 				   addColNr - col nr (not index, thus currently is +1)
 * 
 * Return:         updated count of columns (+1)
 */
 
/** Frank's solution! Works. BUT OVER-ENGINEERED'**/
//~ int AddCol(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols, int addColNr)
//~ {
    //~ int addColIndex = addColNr - 1; //offset by 1 (user enters real-nr)
    //~ int temp = 0;
    //~ for (int i = rows -1; i >= rows +1  ; i++) // ??? is it okay to +1, (thus last i is garbage-values)
    //~ {
        //~ /** Last column if-conditional.**/
        //~ if (addColIndex >= (cols - 1))
        //~ {
            //~ /** Must be "temp" approach! "**/
            //~ temp = matrix[i][addColIndex];
            //~ matrix[i][addColIndex] = GenerateRandomNum(RAND_LOWER, RAND_UPPER);
            //~ matrix[i][addColIndex + 1] = temp;
        //~ }
        
        //~ /** If user did not choose the last row**/
        //~ else
        //~ {
            //~ for (int j = cols+1; j > addColIndex; j-= 2)
            //~ {
                //~ /** Must be "temp" approach! "**/
                //~ temp = matrix[i][j-1];
                //~ matrix[i][j-1] = matrix[i][j-2]; // important algorithm
                //~ matrix[i][j] = temp;
                
            //~ }
            //~ matrix[i][addColIndex] = GenerateRandomNum(RAND_LOWER, RAND_UPPER);
        //~ }
    //~ }
    //~ return cols + 1;
//~ }

/** Teacher's version '**/
int AddCol(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols, int addColNr)
{
    int addColIndex = addColNr - 1; //offset by 1 (user enters real-nr)
    /** Shift until we are at index/pos where new row will be added (in next code-section row 606)**/
    for (int i = 0; i < rows; i++)
    {
        for (int j = cols - 1; j >= addColIndex; j--) 
        {
            matrix[i][j + 1] = matrix[i][j];
        }
    }
    /** Adding randomly generated value to the newly generated zero-d out column. **/
    for (int i = 0; i < rows; i++)
    {
        matrix[i][addColIndex] = GenerateRandomNum(RAND_LOWER, RAND_UPPER);
    }
    return cols + 1;
} 

/**
 * Description:    Transpone the matrix (i.e Rows to columns, and columns as rows).
 *                 Mirror over matrix's Diagonal (not anti-diagonal)
 *                 update the matrix!
 *              
 * Parameters:     matrix - matrix that is printed.
 *                 rows - number of rows to display
 *                 cols - number of columns to display)
 * 
 * Return:         none
 */
void TransposeMatrix(int matrix[LIMIT_ROWS][LIMIT_COLS], int rows, int cols)
{
    /** Ternary: to prevent matrix printing 0's when inserting 7x5 (rows > cols) **/
    cols = (rows > cols) ? rows : cols;
    
    rows = (cols > rows) ? cols : rows; // if LIMIT_ROWS 20, LIMIT_COLS 10 // does not transpose correctly.
    
    /** Main function body. Do not alter**/
    for (int i = 0; i < rows; i++) // 
    {
        for (int j = i; j < cols; j++) // int j = i
        {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = temp;
        }
    }
}
