#include <stdio.h>

int main(void)
{
    // Variable declarations (INCOMPLETE!)
    float weight, pricePerKilo, totalPrice;
    int productCode;
    int productCategory;

	// Display menus
    printf("			Available Categories\n");
    printf("1 - Vegetable		2  -  Fruit		3 - Grains\n");
    printf("\n\nDisplaying sub-menus for Vegetables, Fruits and Grains....\n");
    
    printf("-----------------------------------------------------------------\n");
	printf("			Sub-menu preview - Page 1/3\n");
	printf("			Available Vegetables\n");
	printf("1 - Tomato		2  - Cucumber		3 - Potato\n");
    printf("-----------------------------------------------------------------\n");
	printf("			Sub-menu preview  - Page 2/3\n");
	printf("			Available Fruits\n");
	printf("1 - Banana		2  -  Orange		3 - Lemon\n");
    printf("-----------------------------------------------------------------\n");
	printf("			Sub-menu preview  - Page 3/3\n");
	printf("			Available Grains\n");
	printf("1 - Wheat		2  -  Barley		3 - Oat\n");
     printf("----------------------------------------------------------------\n");
	// productCategory validation:
	do
			{
				printf("Enter the category number: ");
				scanf("%d", &productCategory);
				if (productCategory > 3) 
				{
					printf("Invalid product category chosen. Try again!\n");
				}
				else if (productCategory < 0)
				{
					printf("Error! Category cannot be negative! \n");
				}
				else if (productCategory == 0)
				{
					printf("Error! No product category chosen. Please insert a category again! \n");
				}
				else
				{
					printf("You chose product from Category '%d'.\n", productCategory);
					break;		// break out of loop.
				}	
			} while ((productCategory > 1) || (productCategory < 3));
		
	// productCode validation:
	do
			{
				printf("Enter the product number: ");
				scanf("%d", &productCode);
				if (productCode > 3) 
				{
					printf("Invalid product code chosen. Try again!\n");
				}
				else if (productCode < 0)
				{
					printf("Error! Product code cannot be negative! \n");
				}
				else if (productCode == 0)
				{
					printf("Error! No product code chosen. Please insert a code again! \n");
				}
				else
				{
					printf("You chose product with Code number '%d'.\n", productCode);
					break;		// break out of loop.
				}	
			} while ((productCode > 1) || (productCode < 3));
    
    
    // switch-statement to assign pricePerKilo
    switch (productCategory)
    {
		case 1:
			printf("Category  %d -  Vegetable\n", productCategory);

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
				// break;
			}
			break;
			
			
		case 2:
			printf("Category %d - Fruit\n", productCategory);
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
				// break;
			}
			break;
			
			
		case 3:
			printf("Category %d - Grains\n", productCategory);		
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
			}	
			break;		// break out of outer-switch ----> switch (productCategory)
	}
    
    // weight variable validation_
    do
	{
		printf("Enter weight: ");
		scanf("%f", &weight);
		if (weight > 0) 
		{
			printf("The weight of the product is: '%.2f'.\n", weight);
			break;		// break out of loop.
		}
		else if (weight < 0)
		{
			printf("Error! Product weight cannot be negative!\n");
		}
		else
		{
			printf("Error! No product on the scale. Please place your product on the scale! \n");
		}	
	} while (weight <= 0);
	
    // Calculate the total cost
    totalPrice = pricePerKilo * weight;
    printf("\n-----------------------------------\n");
    printf("Loading total price....\n");
   
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

