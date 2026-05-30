#include <stdio.h>

int main(void)
{
    // Variable declarations (INCOMPLETE!)
    float weight, pricePerKilo, totalPrice;
    int productCode;
    
    int productCategory;
    

    printf("			Available Categories\n");
    printf("1 - Vegetable		2  -  Fruit		3 - Grains\n");
 
    printf("Enter the category number: ");
	scanf("%d", &productCategory);
    
    if (productCategory < 1 || productCategory > 3)
    {
		printf("Error! Product category cannot be large 3 or smaller than 1!");
		return 1;
	}
    else if (productCategory == 1)
    {
		printf("Category  %d -  Vegetable\n", productCategory);
		printf("			Available Vegetables\n");
		printf("1 - Tomato		2  - Cucumber		3 - Potato\n");
	
		printf("Enter the product number: ");
		scanf("%d", &productCode);
		
		switch (productCode)
		{
			case 1:
				printf("Product %d - Tomato\n", productCode);
				pricePerKilo = 1.49f;
				break;
			case 2:
				printf("Product %d - Cucumber\n", productCode);
				pricePerKilo = 1.55f;
				break;
			case 3:
				printf("Product %d - Potato\n", productCode);
				pricePerKilo = 1.66f;
				break;
			
			default:
			pricePerKilo = 0.0f;
			printf("Incorrect product selected!");
			return 1;
			// break;
		}
		//break;
	}		
	else if (productCategory == 2)
	{
		printf("Category %d - Fruit\n", productCategory);
	
		printf("			Available Fruits\n");
		printf("1 - Banana		2  -  Orange		3 - Lemon\n");
		
		printf("Enter the product number: ");
		scanf("%d", &productCode);
	
			
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
				
			default:
			pricePerKilo = 0.0f;
			printf("Incorrect product selected!");
			return 1;
			// break;
		break;
		}
	}
			
	else if (productCategory == 3)
	{
		printf("Category %d - Grains\n", productCategory);
	
		printf("			Available Grains\n");
		printf("1 - Wheat		2  -  Barley		3 - Oat\n");
		
		printf("Enter the product number: ");
		scanf("%d", &productCode);
	
		switch (productCode)
		{
			case 1: 
				printf("Product %d - Wheat\n", productCode);    
				pricePerKilo = 1.25f;
				break;
			case 2:
				printf("Product %d - Barley\n", productCode);
				pricePerKilo = 2.55f;
				break;
			case 3:
				printf("Product %d - Oat\n", productCode);
				pricePerKilo = 2.95f;
				break;	
				
			default:
			pricePerKilo = 0.0f;
			// break;
			printf("Incorrect product selected!");
			return 1;
		break;
		}
	}
	else
	{
		printf("Error! Product category must be numerical");
		return 1;
	}
	
    
	printf("Enter weight: ");
    scanf("%f", &weight);
    
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

