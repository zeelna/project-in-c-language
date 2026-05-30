#include <stdio.h>

#define PIN_ATTEMPT_CAP 3
// #define PIN_CODE_DEBIT_CARD = 1234;

int main(void)
{
    /* Data for debit card, some values initialized */
    float accountBalance = 100.00f;        // current account balance
    int pinCodeDebitCard = 1234;        // pin of the card
    int pinCodeEntered;                    // pin entered by the user
    
    /* Data for purchase, must be scanned in */
    float purchaseTotal;                // cost of purchase
    int loyaltyCardPresented;            // does customer have client card? 1 - yes, 0 - no
    int applyExtraDiscount;                // is extra discount applied? 1 - yes, 0 - no
    

    
    printf("Enter purchase total: ");
    /* Read in the total amount for purchase. Hint: use scanf */	
	scanf("%f", &purchaseTotal);
	
    do 
    {	
		printf("Did client present loyalty card?\n1 - yes\n0 - no\n");
		/* Read in if loyalty card was presented? */
		scanf("%d", &loyaltyCardPresented);
		
		if (loyaltyCardPresented > 1 || loyaltyCardPresented < 0)
		{
			printf("Error! Enter 1 for yes or 0 for no!\n");
		}
	}
	while (loyaltyCardPresented > 1 || loyaltyCardPresented < 0);
	printf("You entered 1 or 0 for Loyalty card. Great!\n");
    
    
    
     /* Read in if extra discount was applied? */
    
    //while (applyExtraDiscount != 0 || applyExtraDiscount != 1)
    while (applyExtraDiscount > 1 || applyExtraDiscount < 0)
    {	
		printf("Apply extra discount?\n1 - yes\n0 - no\n");
		scanf("%d", &applyExtraDiscount);
		
		if (applyExtraDiscount == 1 || applyExtraDiscount == 0)
		{
			printf("Thank you for answering 0 or 1 about Extra Discount. Splended!\n");
			break;	
		}
	
		printf("Error! Enter 1 for yes or 0 for no!\n");	
	}
    
    /** Discount manag
     * Use else if statement and combine  multiple conditional statements
     * 
     * Replace the comments with proper conditional statements and calculations
     */
     
    if (loyaltyCardPresented && applyExtraDiscount)
    {
        /* reduce the cost by 20% */
        purchaseTotal *= 0.8f;
    }
    else if (loyaltyCardPresented)
    {
        /* reduce the cost by 10% */
        purchaseTotal *= 0.9f;
    }
    printf("Invoice total: %.2f\n", purchaseTotal);
    
    /** Transaction management
     * Use nested if statements
     *
     * - prompt for and read in pin code
     * - Check the pin code
     *   - If pin code is correct, check if there are enough funds
     *     - If there is enough money, print confirmation, 
     *       calculate and print new account balance
     *     - If there wasn't, print an error message
     *   - if the pin code wasn't correct, print an error message
     */
    
    int i = 0;											// PIN-code input validation.
    //int attemptsRemaining = PIN_ATTEMPT_CAP;				// PIN-code validation.
    
    while (i < PIN_ATTEMPT_CAP)
	{
		printf("Please enter card PIN code: ");
		scanf("%d", &pinCodeEntered);
		
		i++;
		//attemptsRemaining -= 1;
		
		if (pinCodeDebitCard == pinCodeEntered)
		{
			printf("Correct PIN.\n");
			
			if (accountBalance >= purchaseTotal)
			{
				accountBalance -= purchaseTotal;
				printf("Purchase complete!\n");
				printf("New account balance is %.2f\n", accountBalance);
				printf("Thank you, come again!\n");
			}
			else
			{
				printf("Error! Not enough assets on the card!\n");
			}
			break;
		}
		else 
		{
			printf("Error! Incorrect PIN code!\n");
			printf("You have %d attempts left!\n ", PIN_ATTEMPT_CAP-i);
			//printf("You have %d attempts left!\n ", attemptsRemaining);
		}
		
		//if (attemptsRemaining < 1)
		if (PIN_ATTEMPT_CAP-i < 1)
		{
			printf("This was the last attempt. Goodbye!\n");
			break;
		}
	}
	

        

}
