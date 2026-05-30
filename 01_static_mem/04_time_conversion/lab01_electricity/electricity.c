/**
 * File:        electricity.c
 * Author:      Frank Christopher Kirch
 * Created:     24.09.2023
 * Last edit:   24.09.2023
 *
 * Description: Starter code for functions lab task with return statements. 
 *              This will calculate the power prices and give a comparison on 
 *              savings when going from incandescent to LED bulbs.
 */
#include <stdio.h>

/* Power ratings for bulbs in watts*/
#define POWER_LED 9
#define POWER_INCANDESCENT 60

/* Number of days for calculation*/
#define DAYS_PER_MONTH 30

/* Value added tax in percentages */ 
#define VAT_PERCENTAGE 20.0f

/* FILL IN! Something you buy regularly */ 
#define ITEM_NAME "batteries"
#define ITEM_COST 0.69f

float ReadPositiveFloat(void);
int ReadPositiveInteger(void);
float ConvertMwhToKwh(float pricePerMwh);
float CalculateElectricityCost(int consumptionWatts, float price);
float CalculateVat(float price, float vatPcnt);
int CalcMonthlyConsumption(int nConsumers, int nHours, int power, int days);
int CalcItemsForMoney(float money, float costPerItem);


int main(void)
{
    float pricePerMwh, pricePerKwh, priceWithVat, vatCost;
    float costIncandescent, costLED;
    int numOfBulbs, hoursPerBulb, consIncandescent, consLED;
    int purchasableItems;
    
    printf("Enter the market price for electricity in MWh: ");
    pricePerMwh = ReadPositiveFloat();
    
    /* Convert from MWh to kWh and find prices with and without VAT */
    pricePerKwh = ConvertMwhToKwh(pricePerMwh);
    vatCost = CalculateVat(pricePerKwh, VAT_PERCENTAGE);
    priceWithVat = pricePerKwh + vatCost;
    
    
    printf("\nMarket cost of electricity is %.2f EUR / MWh.\n", pricePerMwh);
    printf("This is %.4f EUR per kWh before taxes.\n", pricePerKwh);
    printf("The government takes %.4f EUR in taxes.\n", vatCost);
    printf("With taxes, the cost for you is %.4f EUR / MWh\n\n", priceWithVat);
    
    
    printf("Lets do a rough savings estimate when switching "
           "from incandescent bulbs to LEDs\n\n");
    
    printf("Number of E27 lightbulbs in use: ");
    numOfBulbs = ReadPositiveInteger();
    
    printf("Average hours per day the bulbs are turned on for: ");
    hoursPerBulb = ReadPositiveInteger();
    
    /* Calculate avg monthly consumption for LED and incandescent bulbs */
    consIncandescent = CalcMonthlyConsumption(numOfBulbs, hoursPerBulb, 
                                                POWER_INCANDESCENT, 
                                                DAYS_PER_MONTH);
    consLED = CalcMonthlyConsumption(numOfBulbs, hoursPerBulb, POWER_LED, 
                                        DAYS_PER_MONTH);
    
    /* Calculate the equivalent cost in euros for the consumptions */
    costIncandescent = CalculateElectricityCost(consIncandescent, priceWithVat);
    costLED = CalculateElectricityCost(consLED, priceWithVat);
    
    printf("\nResults are calculated for a %d-day month.\n", DAYS_PER_MONTH);
    printf("\nUsing %d W incandescent bulbs consumes %d W, costing %.2f EUR\n",
           POWER_INCANDESCENT, consIncandescent, costIncandescent);
    printf("Using %d W LED bulbs consumes %d W, costing %.2f EUR\n",
           POWER_LED, consLED, costLED);
    
    purchasableItems = CalcItemsForMoney(costIncandescent - costLED, ITEM_COST);
    
    printf("That's a saving of %.2f EUR.\n", costIncandescent - costLED);
    printf("At the price of %.2f, you could buy %d %s with that money!", 
            ITEM_COST, purchasableItems, ITEM_NAME);
    
    return 0;
}


/**
 * Description:    Reads a positive real number value from the keyboard.
 *                 Doesn't return until user gives a positive value.
 *
 * Parameters:     -
 *
 * Return:         Positive (> 0) real number 
 */
float ReadPositiveFloat(void)
{
    float ansFloat;
	
	do 
	{
		//~ printf("\nEnter a positive value: \n");
		scanf("%f", &ansFloat);
		if (ansFloat <= 0)
		{
			printf("Retry! Must be >0.\n");
		}
	}
	while (ansFloat <= 0);
	return ansFloat;
    
    //return 0;  
}

/**
 * Description:    Reads a positive integer from the keyboard.
 *                 Doesn't return until user gives a positive value.
 *
 * Parameters:     -
 *
 * Return:         Positive (> 0) integer 
 */
int ReadPositiveInteger(void)
{
    int ansInt = -1;
	
	do 
	{
		//~ printf("\nEnter a positive value: \n");
		scanf("%d", &ansInt);
		if (ansInt <= 0)
		{
			printf("Retry! Must be >0.\n");
		}
	}
	while (ansInt <= 0);
	
	return ansInt;
    //return 0;   
}
/**
 * Description:    Converts price given in MWh (megawatt-hours) to kWh 
 *                 (kilowatt-hours)
 *
 * Parameters:     price - price for 1 MWh
 *
 * Return:         price converted for 1 KWh
 */
float ConvertMwhToKwh(float price)
{
    float kwhPrice = price / 1000.00f;
    return kwhPrice;
    //return 0;
}


/**
 * Description:    Calculates cost of electricity for the amount of energy
 *                 consumed.
 *
 * Parameters:     consumption - amount of electricity used in watt-hours (Wh)
 *                 price - cost for 1 kWh
 *
 * Return:         Energy cost for the amount of power consumed
 */
float CalculateElectricityCost(int consumption, float price)
{
    //float costOfPowerConsumed;
    float costOfPowerConsumed = (consumption / 1000.00f) * price;
    //~ return ("%f", costOfPowerConsumed);
    return costOfPowerConsumed;
    
    //return consumption * price;
}

/**
 * Description:    Calculates the amount of VAT for the given amount of money.
 *                 Does not add the VAT on top!
 *
 * Parameters:     price - money without VAT
 *                 vacPcnt - (VAT percentage)
 *
 * Return:         Amount of VAT needed to be paid on the sum
 */
 
float CalculateVat(float price, float vatPcnt)
{
    float answerVatAmount = (vatPcnt / 100.00f) * price;
    return answerVatAmount;
    //return 0;
}
/**
 * Description:    Calculates how many watt-hours are consumed in a month
 *                 by n devices using the same amount of power 
 *                 for a given amount of hours per day.
 *
 * Parameters:     nConsumers - number of power consumers
 *                 nHours - number of hours device on per day
 *                 power - power usage per device in watts
 *                 days - number of days device is on for
 *
 * Return:         Energy consumed per month for all devices in watts
 */
int CalcMonthlyConsumption(int nConsumers, int nHours, int power, int days)
{
    return nConsumers * (nHours * power * days);   
}

/**
 * Description:    Calculates how many items in full can be bought
 *                 for the given amount of money
 *
 * Parameters:     money - amount of money
 *                 costPerItem - how much one piece of an item costs
 *
 * Return:         How many items can be bought in full as an integer
 */
int CalcItemsForMoney(float money, float costPerItem)
{
    int itemsBought;    
    itemsBought = money / costPerItem;
    
    return itemsBought;
}
