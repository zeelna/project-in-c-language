#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define NUM_OF_ROWS 14
#define NUM_OF_COLS 17

#define SEAT_OCCUPIED 2
#define SEAT_FREE 1
#define SEAT_MISSING 0
#define BOOKED 3
#define LEN 3
#define MAX_LEN 2

#define ERROR -1
#define GOOD 1

#define TRUE 1
#define FALSE 0 

#define CONFIRMED_CART 1
#define DISCARDED_CART 0
#define EXIT -1


#define MAX_TICKETS 238 // <-NUM_OF_ROWS * NUM_OF_COLS

/** Print the Cinema floor plan**/
void ReadUnmodifiedFloorPlan(uint8_t cinema[NUM_OF_ROWS][NUM_OF_COLS],
								int rows, int cols);
void PrintModifiedFloorPlan(uint8_t cinema[NUM_OF_ROWS][NUM_OF_COLS],
								int rows, int cols);
                                
void ParseSeatsInRow(uint8_t seatsInRow[NUM_OF_COLS], int cols); // cols == len;

/** Function to get input and parse into cinema floorplan format**/
void AskSeat(int inputArray[LEN]);
void StoreInput(int rowInput, int seatInput, int ticketInput, int inputArray[LEN]);
int GetSelectedRow(int inputArray[LEN]);


int FindBookedSeat(int inputArray[LEN], uint8_t seatsInRow[NUM_OF_COLS], int cols);

int GetSeatStatus(uint8_t cinema[NUM_OF_ROWS][NUM_OF_COLS], int updatedRow, int updatedSeat);

/** Moving RIGHT/LEFT in the Cinema's row '**/
int BookSeatInRight(int inputArray[LEN], uint8_t seatsInRow[NUM_OF_COLS], int cols, int updatedSeat, int  shopCartArray[MAX_TICKETS][MAX_LEN]);
int BookSeatInLeft(int inputArray[LEN], uint8_t seatsInRow[NUM_OF_COLS], int updatedSeat, int bookedSeatCnt, int  shopCartArray[MAX_TICKETS][MAX_LEN]);

/** Booking the seats **/
int SearchFreeAdjacectSeats(int inputArray[LEN], uint8_t seatsInRow[NUM_OF_COLS], int cols, int updatedSeat, int  shopCartArray[MAX_TICKETS][MAX_LEN]);
int AlterFloorPlan(int  shopCartArray[MAX_TICKETS][MAX_LEN], int bookedSeatCnt, uint8_t cinema[NUM_OF_ROWS][NUM_OF_COLS], uint8_t newStatus);

/** Confirmation whether can be booked **/
int BookingMessage(int inputArray[LEN], int bookedSeatCnt);
int GetConfirmation();

/** Fn Prototypes to color the text! **/
void red();
void yellow();
void green();
void reset();

int main(void)
{
    uint8_t cinemaHall[NUM_OF_ROWS][NUM_OF_COLS] = 
            {{2, 2, 2, 2, 2, 2, 1, 2, 2, 1, 2, 2, 1, 1, 1, 1, 1},
             {0, 0, 1, 1, 2, 2, 2, 2, 1, 2, 2, 1, 2, 1, 1, 1, 1},
             {0, 0, 1, 1, 2, 2, 1, 2, 2, 2, 1, 1, 2, 2, 2, 1, 1},
             {0, 0, 1, 1, 1, 2, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1},
             {0, 0, 1, 1, 1, 2, 2, 1, 2, 2, 1, 2, 2, 1, 2, 1, 1},
             {0, 0, 1, 1, 2, 2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 0},
             {0, 0, 1, 2, 2, 2, 1, 1, 1, 2, 2, 1, 2, 2, 1, 1, 0},
             {0, 0, 1, 1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 0},
             {0, 0, 1, 1, 1, 1, 2, 2, 1, 2, 2, 1, 1, 1, 1, 0, 0},
             {0, 0, 1, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 1, 0, 0},
             {0, 0, 1, 1, 1, 1, 2, 2, 1, 2, 2, 2, 1, 1, 1, 0, 0},
             {0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0},
             {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
             {0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 0, 0, 0}};
        
	
    
    /** Step 1. Printing floor plan without modifying it. **/
	
	
    /** Step 2. Alter the floor plan by removing missing seat/chairs**/
    
    int inputArray[LEN] = {0};
    
    //~ uint8_t shopCartArr[MAX_TICKETS][MAX_LEN] = {0};
    int shopCartArr[MAX_TICKETS][MAX_LEN] = {0};
    
    int code;
    int modifiedRowNr, modifiedSeatNr;
    int bookedSeatCnt;
    
    int confirmationStatus, bookingStatus;
    
    //~ do
    while(1)
    {
        //~ printf("\nCinema hall floorplan without any modifications: ");
        //~ printf("\n");
        //~ ReadUnmodifiedFloorPlan(cinemaHall, NUM_OF_ROWS, NUM_OF_COLS); // Recommended to uncomment for DEBUGGING RESULTS
        
        /** Printing Cinema Floor Plan (modified to view) **/
        PrintModifiedFloorPlan(cinemaHall, NUM_OF_ROWS, NUM_OF_COLS);
        
        /** Asking input **/
        AskSeat(inputArray);
    
        modifiedRowNr = GetSelectedRow(inputArray); /** For debugging, declaring variable **/
        
        /** Finding seat index to can be booked! i.e (SEAT_FREE)**/
        modifiedSeatNr = FindBookedSeat(inputArray, cinemaHall[modifiedRowNr], NUM_OF_COLS);
        
        /** Printing message whether starting seat is available**/
        int seatStatus = GetSeatStatus(cinemaHall, modifiedRowNr, modifiedSeatNr);
        if (seatStatus == ERROR)
            continue;
        
        /** Finding seats for all tickets (ie. "ticket nr", which is inputArray[2])
         * Propagating array 'shopCartArr' 
         * i= (ticket nr -1) ------------->
         *           shopCartArr[i][0] = modifiedRowNr]
         *           shopCartArr[i][1] == modifiedSearNr 
         *                                              ++ (i.e if SEAT_FREE '1', then move RIGHT)
         *                                              -- (i.e if SEAT_TAKEN 'X', then move LEFT)
         * **/
        bookedSeatCnt = SearchFreeAdjacectSeats(inputArray, cinemaHall[modifiedRowNr], NUM_OF_COLS, modifiedSeatNr, shopCartArr); // book seat cnt

        /** Propgating shopCartArr (array) with ticket**/
        code = AlterFloorPlan(shopCartArr, bookedSeatCnt, cinemaHall, BOOKED); // remove code
        
        printf("\nThe code executed to (GOOD 1) (ERROR -1): %d\n", code);
        
        bookingStatus = BookingMessage(inputArray, bookedSeatCnt);
        
        if (bookingStatus == GOOD)
        {
            PrintModifiedFloorPlan(cinemaHall, NUM_OF_ROWS, NUM_OF_COLS);
            //~ ReadUnmodifiedFloorPlan(cinemaHall, NUM_OF_ROWS, NUM_OF_COLS); // Recommended to uncomment for DEBUGGING RESULTS
            
            confirmationStatus = GetConfirmation();
            
            if (confirmationStatus != DISCARDED_CART) // means either EXIT or CONFIRMED_CART
            {
                break;
            }
            else
            {
                code = AlterFloorPlan(shopCartArr, bookedSeatCnt, cinemaHall, SEAT_FREE); // remove code!
            }
        }
        else // (bookingStatus == ERROR)
        {
            code = AlterFloorPlan(shopCartArr, bookedSeatCnt, cinemaHall, SEAT_FREE);
        }

    //~ ReadUnmodifiedFloorPlan(cinemaHall, NUM_OF_ROWS, NUM_OF_COLS); // remove later
    //~ PrintModifiedFloorPlan(cinemaHall, NUM_OF_ROWS, NUM_OF_COLS);
    } 

    return 0;
}
void red() 
{
    printf("\033[1;31m");
}
void yellow()
{
    printf("\033[1;33m");
}
void green() 
{
    printf("\033[0;32m");
}
void cyan()
{
    printf("\33[0;36m]");
}

void reset()
{
    printf("\033[0m");
}

void ReadUnmodifiedFloorPlan(uint8_t cinema[NUM_OF_ROWS][NUM_OF_COLS],
								int rows, int cols)
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("%2d", cinema[i][j]);
        }
        printf("\n");
    }
}

void PrintModifiedFloorPlan(uint8_t cinema[NUM_OF_ROWS][NUM_OF_COLS],
								int rows, int cols)
{
    int i;
    //~ for (i = rows-1; i >= 0; i--)
    for (i = 0; i < rows; i++)
    {
        reset();
        printf("\n%2d ", rows - i);
        ParseSeatsInRow(cinema[i], cols);
    }
    reset();
    printf("\n \t\t\t\t S C R E E N \t\t\t\t \n");
}




void ParseSeatsInRow(uint8_t seatsInRow[NUM_OF_COLS], int cols) // cols == len
{
	
    char nothing = ' ';
    char taken = 'X';
    int seatCounter = 1;
    int j;
	for (j = 0; j < cols; j++)
	{
		/** Print emptyspace if no seat! **/
		if (seatsInRow[j] == SEAT_MISSING)
		{
            printf("%4c", nothing);
		}
		/** Print number seat**/
		else 
		{
			if (seatsInRow[j] == SEAT_OCCUPIED) // 2
			{	
                red();
                printf("%4c", taken);
			}	
			else if (seatsInRow[j] == BOOKED)
            {
                yellow();
                printf("%4d", seatCounter);
            }
            
            /** Anomalies **/
			else //(seatsInRow[i][j] == SEAT_FREE)
			{
            	green();
                printf("%4d", seatCounter);
			}
			/** Incrementing when seat not 0!**/
			seatCounter++;
		}
	}
}		

void AskSeat(int inputArray[LEN])
{
	int rowInput, seatInput, ticketInput;
    
	reset();
    while(1)
    {
        printf("\nEnter row number:");
        scanf("%d", &rowInput);
        
        printf("Enter seat number:");
        scanf("%d", &seatInput);
        
        printf("Enter number of tickets: ");
        scanf("%d", &ticketInput);
        
        /** Check for valid input**/
        if ((rowInput > 0 && rowInput <= NUM_OF_ROWS) && 
            (seatInput > 0 && seatInput <= NUM_OF_COLS) &&
            (ticketInput > 0))
            break;
        else
        {    
            red();
            printf("\nPlease see the cinema's seating plan once again."
                    "There are no such seats."
                    "\nRow: %d\nSeat: %d\nTickets: %d",
                    rowInput, seatInput, ticketInput);
            reset();
        }    
    }
    
    /** Store Input into an array. Will be used to parse.**/
    /** at index 0 store row-nr, at index 1 store seat-nr, at index 2 store 'amount of tickets' **/
    StoreInput(rowInput, seatInput, ticketInput, inputArray);
}

void StoreInput(int rowInput, int seatInput, int ticketInput, int inputArray[LEN])
{
    /** at index 0 store row-nr, at index 1 store seat-nr, at index 2 store 'amount of tickets' **/
    inputArray[0] = rowInput;
    inputArray[1] = seatInput;
    inputArray[2] = ticketInput;
    //~ printf("\nSanity-check: unmod-row: %d, unmod-seat: %d", inputArray[0], inputArray[1]);
}

int GetSelectedRow(int inputArray[LEN])
{
    int rowInput = inputArray[0]; /** for debugging **/
    inputArray[0] = NUM_OF_ROWS - (rowInput - 1) - 1;
    //~ inputArray[0] = NUM_OF_ROWS - (inputArray[0] - 1) - 1;
    return inputArray[0];
}

int FindBookedSeat(int inputArray[LEN], uint8_t seatsInRow[NUM_OF_COLS], int cols)
{
    int SeatCnt = 1; /** Must be 1, we are iterating from 1st ticket as '1' (not '0')**/
    int i; 
    for (i = 0; i < cols + 1; i++)
    {
        
        //~ int seatLabelInCinema = seatsInRow[i]; /** for debugging 
        //~ int seatNr = inputArray[1]; /** for debugging 
        /** Must be included to count all seats cinema seats (even SEAT_TAKEN) **/
        if (seatsInRow[i] != SEAT_MISSING)
        {
            /** Here: Counting occurences of SEAT_FREE *
             * if we chose seat-nr#1, return respective index
             * else (chose not seat-nr#1), then count SEAT_FREE occurences, until matches seat-nr# **/
            if (inputArray[1] == SeatCnt) 
            {
                return i; /** If only seat-nr#1, return that index **/
            }
            else 
            {
                //~ seatLabelInCinema = seatsInRow[i]; // for debugging
                SeatCnt++;
            }
        }
    }
    return i-1; /** de-incrementing the last iterations "SeatCnt++" **/
}

int GetSeatStatus(uint8_t cinema[NUM_OF_ROWS][NUM_OF_COLS], int updatedRow, int updatedSeat)
{
    int bookingStatus;
    printf("\nDEBUG: Starting position in array: [%d][%d]", updatedRow, updatedSeat);
    if (cinema[updatedRow][updatedSeat] == SEAT_OCCUPIED)
    {
        red();    
        printf("\nSelected seat is already booked!\n");
        bookingStatus = ERROR;
    }
    else if (cinema[updatedRow][updatedSeat] == SEAT_FREE)
    {
        green();
        printf("\nSuccess finding a seat! Starting position is free!\n");
        bookingStatus = GOOD;
    }
    else 
    {
        red(); 
        printf("\nThe selected seat does not exist!\n");
        bookingStatus = ERROR;
    }
    reset();
    return bookingStatus;
}


int BookSeatInRight(int inputArray[LEN], uint8_t seatsInRow[NUM_OF_COLS], int cols, int updatedSeat, int  shopCartArray[MAX_TICKETS][MAX_LEN])
{
    
    //~ int seatStatus, seatNr, ticketNr;
    
    int rowNr, ticketsToBook;
    
    int bookedSeatCnt = 0;
    for (int i = updatedSeat; i < cols + 1; i++)
    {
        /** Variable for debugging **/
        //~ int seatStatus = seatsInRow[i];
        //~ int seatNr = inputArray[1];
        //~ int ticketsNr = inputArray[2];
        
        rowNr = inputArray[0];

        if (seatsInRow[i] == SEAT_FREE)
        {
            shopCartArray[bookedSeatCnt][0] = rowNr; 
            shopCartArray[bookedSeatCnt][1] = i; /** i = cinema's seat index on given row **/
            bookedSeatCnt++;
            /** Find nr of tickets to book, which haven't found a seat yet!'**/
            /** inputArray[2] --> stars from 1!!   This is nr of tickets we want to purchase!
             *  bookedSeantCnt      --> start from 0!!   index of shopping cart!
             * **/
            ticketsToBook = inputArray[2] - bookedSeatCnt;
            
             /** If ALL tickets have a dedicated seat, stop moving "Right", 
              * else move to next iteration of "Right"**/
            if (ticketsToBook == 0)
                break;
            
            else // can remove
                continue; //can remove
        }
        else /** seat not free/open (on given iteration)! **/
        {
            break; /** thus, break out (no free neighbouring seats when moving more "LEFT")**/
        }
    }
    return bookedSeatCnt; // //--> if (bookedSeatCnt != inputArray[2]) {BookSeatInLeft()}
}

int BookSeatInLeft(int inputArray[LEN], uint8_t seatsInRow[NUM_OF_COLS], int updatedSeat, int bookedSeatCnt, int  shopCartArray[MAX_TICKETS][MAX_LEN])
{

    int rowNr;
    int ticketsToBook;
    
    for (int i = updatedSeat-1; i >= 0; i--)
    {
        /** Variable for debugging **/
        //~ int seatStatus = seatsInRow[i];
        //~ int seatNr = inputArray[1];
        //~ int ticketsNr = inputArray[2];
        
        rowNr = inputArray[0];
        //~ ticketsToBook = inputArray[2] - bookedSeatCnt;
        
        if (seatsInRow[i] == SEAT_FREE)
        {
            /** Solve correct positioning of I. **/
            shopCartArray[bookedSeatCnt][0] = rowNr;
            shopCartArray[bookedSeatCnt][1] = i; /** i = cinema's seat index on given row **/
            bookedSeatCnt++; // should -1 here? (starts at 0)

            /** Find nr of tickets to book, which haven't found a seat yet!'**/
            /** inputArray[2] --> stars from 1!!   This is nr of tickets we want to purchase!
             *  bookedSeantCnt      --> start from 0!!   index of shopping cart!
             * **/
            ticketsToBook = inputArray[2] - bookedSeatCnt; // here is useful we dont '-1' above!
            
            /** If ALL tickets have a dedicated seat, stop moving "Left",
             *  else move to next iteration of "Left"**/
            if (ticketsToBook == 0)
                break;
            
            else // can remove 
                continue; // can remove
        }
        else /** seat not free/open (on given iteration)! **/
        {
            break; /** thus, break out (no free neighbouring seats when moving more "RIGHT")**/
        }
    }
    return bookedSeatCnt; // not needed to -1, we move to next iteration to do "BookSeatInLeft" at correct iteration 
}

int SearchFreeAdjacectSeats(int inputArray[LEN], uint8_t seatsInRow[NUM_OF_COLS], int cols, int updatedSeat, int  shopCartArray[MAX_TICKETS][MAX_LEN])
{
    int bookedSeatCnt = BookSeatInRight(inputArray, seatsInRow, cols, updatedSeat, shopCartArray);
    if (bookedSeatCnt != inputArray[2])
    {
        /** Overwriting "bookedSeatCnt" with the function "BookSeatInLeft" body **/
        bookedSeatCnt = BookSeatInLeft(inputArray, seatsInRow, updatedSeat, bookedSeatCnt, shopCartArray);
    }
    return bookedSeatCnt; // end program once confirmed
}


int AlterFloorPlan(int  shopCartArray[MAX_TICKETS][MAX_LEN], int bookedSeatCnt, uint8_t cinema[NUM_OF_ROWS][NUM_OF_COLS], uint8_t newStatus)
{
    int markedRow, markedSeat;
    for (int i = 0; i < bookedSeatCnt; i++)
    {
        markedRow = shopCartArray[i][0];
        markedSeat = shopCartArray[i][1];
        
        cinema[markedRow][markedSeat] = newStatus;
        printf("\n#1 DEBUG: Ticket#%d -> Array position[%d][%d]", i+1, markedRow, markedSeat);
    }    
    return GOOD;
}
// Printing floor-plan!

int BookingMessage(int inputArray[LEN], int bookedSeatCnt)
{
    int bookingStatus; //~ int bookingStatus = ERROR;
    
    if (bookedSeatCnt != inputArray[2])
    {
        bookingStatus = ERROR;
        
        red();
        printf("\nNot enough room for your friends\n");
        reset(); // loop entire program!
    }
    
    else
    {
        bookingStatus = GOOD;
        
        green();
        printf("\nSuccessful booking!");
        reset();
    }
    return bookingStatus;
}

int GetConfirmation()
{
    char confirmationInput = ' ';
    
    /** Validating correct input!**/
    while(1)
    //~ do
    {
        green();
        printf("\nSuccess! Tickets are available!\nDo we book them [y/n] or quit [q]?");
        reset();
        scanf(" %c", &confirmationInput);
        if (confirmationInput == 'y' || confirmationInput == 'n' || confirmationInput == 'q')
            break; 
            
        else
            printf("\nInvalid input. Please enter 'y' for yes, and 'n' for no! Enter 'q' to exit"); // hidden 'continue'
    } //~ while(confirmationInput != "y" && confirmationInput != "n" && confirmationInput != "q");
    
    /** Returning value to pass into other function! **/
    if (confirmationInput == 'y')
    {
        printf("\nTickets purchased successfully! Enjoy the movie!");
        return CONFIRMED_CART;
        }
    
    else if (confirmationInput == 'n')
    {
        cyan();
        printf("\nTickets discarded! Choose new seats");
        reset();
        return DISCARDED_CART;
    }
    
    else
    {
        cyan();
        printf("\nExiting the shopping cart!");
        reset();
        return EXIT;
    }
}
