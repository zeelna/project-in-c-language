#include <stdio.h>

int main(void)
{
    /* Data for debit card, some values initialized. Do not change these values! */
    float accountBalance = 100.00f;         // current account balance
    const int pinCodeDebitCard = 1234;      // pin of the card
    int pinCodeEntered;                     // pin entered by the user
    
    /* Data for purchase, must be read from the keyboard. Don't change the variables! */
    float purchaseTotal;                    // cost of purchase
    int loyaltyCardPresented;               // does customer have loyalty card? 1 - yes, 0 - no
    int applyExtraDiscount;                 // is extra discount applied? 1 - yes, 0 - no
    
    
    /* Read in the total amount for purchase. Hint: use scanf */
    printf("Enter purchase total: ");
    scanf("%f", &purchaseTotal);
    printf("The total purchase inputted via keyboard: %.2f\n", purchaseTotal);
	
    /* Read in if loyalty card was presented? */
    printf("Did client present loyalty card?\n1 - yes\n0 - no\n");
    scanf("%d", &loyaltyCardPresented);
    printf("The client loyalty card boolean: %d\n", loyaltyCardPresented);
	
    /* Read in if extra discount was applied? */
    printf("Apply extra discount?\n1 - yes\n0 - no\n");
    scanf("%d", &applyExtraDiscount);
    printf("Extra discount input from keyboard: %d\n", applyExtraDiscount);
    
    
    
    /** Discount management
     * In this part you will practice making conditions composed of multiple conditional statements.
     * You will also need to do the percentage calculations here
     * 
     * 1. Remove the comments from the front of the following if/else statement
     * 2. Replace the comments with the correct conditional statements. 
     * 3. Add percentage calculations.
     * 4. Make sure the indentation is right!
     */
     
    // if (/* loyalty card presented AND extra discount applied */)
    // {
    //    /* reduce the cost by 20% */
    // }
    // else if (/* only loyalty card presented */)
    // {
    //     /* reduce the cost by 10% */
    // }
    
    if ((loyaltyCardPresented == 1) && (applyExtraDiscount == 1))
    {
		printf("Applying 20 percent discount...");
		purchaseTotal = purchaseTotal * 0.8;
		printf("The total purchase after 20percent discount: %.2f\n", purchaseTotal);
	}
	else if ((loyaltyCardPresented == 1) && (!applyExtraDiscount))
	{
		printf("Applying 10 percent discount...");
		purchaseTotal = purchaseTotal * 0.9;
		printf("The total purchase after 10percent discount: %.2f\n", purchaseTotal);
	}
	else 
	{

		printf("No discounts applied, because no Loyalty card applied.\n");
	}
	
    printf("Invoice total: %.2f\n", purchaseTotal);
    
 
    
    /** Transaction management	// nested if-statements
     * In the following part you need to created nested if statements.
     * The structure of the statements is already given as a comments similar to pseudocode
     * Write your statements after the comment block to implement this!
     *
     * - prompt for and read in pin code
     * - Check the pin code. NB! You must compare the preset and the entered PIN code that both are stored in variables!
     *   - If pin code is correct, check if there are enough funds
     *     - If there is enough money, print confirmation, 
     *       calculate and print new account balance
     *     - If there wasn't, print an error message
     *   - if the pin code wasn't correct, print an error message
     */
    
    printf("Please enter card PIN code: ");
    scanf("%d", &pinCodeEntered);
    printf("You have entered PIN code '%d'\n", pinCodeEntered);
    
    if (pinCodeEntered == pinCodeDebitCard)
    {
		printf("Correct PIN. You entered %d, and the correct PIN %d \n", pinCodeEntered, pinCodeDebitCard);
		
		if (purchaseTotal <= accountBalance)
		{
			printf("Enough Funds -> Purchase total: %.2f; the balance: %.2f \n", purchaseTotal, accountBalance);
			accountBalance -= purchaseTotal;
			printf("New account balance is %.2f \n", accountBalance);
		}
		else 
		{
			printf("Not enough Funds -> Purchase total: %.2f; the balance: %.2f \n", purchaseTotal, accountBalance);
			printf("Error! Not enough assets on the card! \n");
		}
		
	}
	else if (pinCodeEntered != pinCodeDebitCard)
	{
		printf("Wrong PIN. You entered %d, and the correct PIN is %d. \n", pinCodeEntered, pinCodeDebitCard);
		printf("Error! Incorrect PIN code! \n");
	}
	else 
	{
		printf("Error! Incorrect PIN code! \n");
	}
    
    
    return 0;
}
