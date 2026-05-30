#include <stdio.h>

int main(void)
{
    // Variable declarations (INCOMPLETE!)
    float weight, pricePerKilo, totalPrice;
    int productCode;
    
    
    // List all available products (INCOMPLETE!)
    printf("			Available products\n");
    printf("1 - Banana		2  -  Orange		3 - Lemon\n");
    printf("4 - Tomato		5 - Cucumber		6 - Potato\n");
    printf("7 - Apple		8 - Pear		9 - Plum\n");
    
    // Read in product code (TODO!)
    printf("Enter the product number: ");
    scanf("%d", &productCode);
    
    
    // Read in product weight (FIX THE MISTAKE!)
    printf("Enter weight: ");
    scanf("%f", &weight);
    
    // Show which product was picked and show the name of it for confirmation.
    // INCOMPLETE!
    switch (productCode)
    {
        case 1: 
            printf("Product %d - Banana\n", productCode);    
            pricePerKilo = 1.19f;
            break;
         case 2:
			printf("Product %d - Orange\n", productCode);
			pricePerKilo = 1.22f;
			break;
		case 3:
			printf("Product %d - Lemon\n", productCode);
			pricePerKilo = 1.33f;
			break;
		case 4:
			printf("Product %d - Tomato\n", productCode);
			pricePerKilo = 1.49f;
			break;
		case 5:
			printf("Product %d - Cucumber\n", productCode);
			pricePerKilo = 1.55f;
			break;
		case 6:
			printf("Product %d - Potato\n", productCode);
			pricePerKilo = 1.66f;
			break;
		case 7:
			printf("Product %d - Apple\n", productCode);
			pricePerKilo = 1.77f;
			break;
		case 8:
			printf("Product %d - Pear\n", productCode);
			pricePerKilo = 1.88f;
			break;
		case 9:
			printf("Product %d - Plum\n", productCode);
			pricePerKilo = 1.99f;
			break;
			
        default:
            pricePerKilo = 0.0f;
    }
    
    // Calculate the total cost
    totalPrice = pricePerKilo * weight;
    
    // Output the label information (INCOMPLETE - only when no errors occurred!)
    if (totalPrice <= 0.0f )		// || ())	 // this equivalent to // if ((pricePerKilo <= 0.0f) ||  (weight  <= 0.0f)); 	// includes the following, look  line 68 (default:)		// ||  (productCode < 1 || productCode > 9 ))
    {
		printf("Inputs are 1) pricePerKilo: %.1f, 2) weight: %.1f.\n", pricePerKilo, weight);
		printf("Error!\n");
	}
    else 
    {
    printf("Price per kilo %.2f EUR\n ", pricePerKilo);
    printf("Total price: %.2f EUR\n ", totalPrice);
    
    printf("Total price: %.2f EUR (unrounded: %f)\n ", totalPrice, totalPrice);
	}
    return 0;
}

