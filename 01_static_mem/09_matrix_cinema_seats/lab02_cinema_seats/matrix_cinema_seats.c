#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define NUM_OF_ROWS 14
#define NUM_OF_COLS 17

#define SEAT_OCCUPIED 2
#define SEAT_FREE 1
#define SEAT_MISSING 0
#define LEN 2

#define ERROR -1

void ReadUnmodifiedFloorPlan(uint8_t cinema[NUM_OF_ROWS][NUM_OF_COLS],
								int rows, int cols);
void PrintModifiedFloorPlan(uint8_t cinema[NUM_OF_ROWS][NUM_OF_COLS],
								int rows, int cols);
void ParseSeatsInRow(uint8_t seatsInRow[NUM_OF_COLS], int cols); // cols == len;

void AskSeat(int seatInShoppingCart[LEN]);
int FindModifiedRowNr(int seatInShoppingCart[LEN]);
int FindBookedSeat(int seatInShoppingCart[LEN], uint8_t seatsInRow[NUM_OF_COLS], int cols);

void PrintBookingStatus(uint8_t cinema[NUM_OF_ROWS][NUM_OF_COLS], int updatedRow, int updatedSeat);

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
	printf("Cinema hall floorplan without any modifications: ");
	printf("\n");
	ReadUnmodifiedFloorPlan(cinemaHall, NUM_OF_ROWS, NUM_OF_COLS);
    
    /** Step 2. Alter the floor plan by removing missing seat/chairs**/
    PrintModifiedFloorPlan(cinemaHall, NUM_OF_ROWS, NUM_OF_COLS);
    
    int bookedTicket[LEN] = {0};
    AskSeat(bookedTicket);
    
    //~ int modifiedRowNr = FindModifiedRowNr(bookedTicket);
    int modifiedRowNr = bookedTicket[0];
    
    //~ int modifiedSeatNr = FindBookedSeat(bookedTicket, uint8_t seatsInRow[NUM_OF_COLS], int cols)
    int modifiedSeatNr = FindBookedSeat(bookedTicket, cinemaHall[modifiedRowNr], NUM_OF_COLS);
    
    PrintBookingStatus(cinemaHall, modifiedRowNr, modifiedSeatNr);
    
        
    return 0;
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
        printf("\n%2d ", rows - i);
        ParseSeatsInRow(cinema[i], cols);
    }
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
				printf("%4c", taken);
				
			/** Anomalies **/
			else //(seatsInRow[i][j] == SEAT_FREE)
				printf("%4d", seatCounter);
			
			/** Incrementing when seat not 0!**/
			seatCounter++;
		}
	}
}		

void AskSeat(int seatInShoppingCart[LEN])
{
	int rowInput, seatInput;
	while(1)
    {
        printf("\nEnter row and seat number:");
        scanf("%d%d", &rowInput, &seatInput);
        /** Check for valid input**/
        if ((rowInput > 0 && rowInput <= NUM_OF_ROWS) && 
            (seatInput > 0 && seatInput <= NUM_OF_COLS))
            break;
        else
            printf("\nTry again! Selected for row: %d, col: %d", rowInput, seatInput);
            
    }
    /** at index 0 store row-nr, at index 1 store seat-nr **/
    seatInShoppingCart[0] = NUM_OF_ROWS - (rowInput - 1) - 1;
    seatInShoppingCart[1] = seatInput;
    printf("\nSanity-check: unmod-row: %d, unmod-seat: %d", seatInShoppingCart[0], seatInShoppingCart[1]);
    
}
int FindModifiedRowNr(int seatInShoppingCart[LEN])
{
    return seatInShoppingCart[0];
}

int FindBookedSeat(int seatInShoppingCart[LEN], uint8_t seatsInRow[NUM_OF_COLS], int cols)
{
    int seatLabelInCinema = 0;
    int seatNr = -1;
    
    int SeatCnt = 1;
    int i; 
    for (i = 0; i < cols + 1; i++)
    {
        seatLabelInCinema = seatsInRow[i];
        seatNr = seatInShoppingCart[1];
        //~ if (SeatCnt > 0 && seatInShoppingCart[1] == SeatCnt)

        /** Must be included to count all seats (either taken or free)**/
        if (seatsInRow[i] != SEAT_MISSING)
        {
            if (seatInShoppingCart[1] == SeatCnt)
            {
                return i;
            }
            else 
            {
                seatLabelInCinema = seatsInRow[i];
                SeatCnt++;
            }
        }

    }
    return i-1;
}

void PrintBookingStatus(uint8_t cinema[NUM_OF_ROWS][NUM_OF_COLS], int updatedRow, int updatedSeat)
{
    printf("\nDEBUG: Array position[%d][%d]", updatedRow, updatedSeat);
    if (cinema[updatedRow][updatedSeat] == SEAT_OCCUPIED)
        printf("\nSelected seat is already booked!\n");
    else if (cinema[updatedRow][updatedSeat] == SEAT_FREE)
        printf("\nSuccess! Ticket purchased!!\nEnjoy the movie!\n");
    else 
        printf("\nThe selected seat does not exist!\n");
}
