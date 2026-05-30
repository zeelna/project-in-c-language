#include <stdio.h>

#define CONV_RATE_EEK_IN_EUR 15.6466f 

int main(void)
{
	float valueKroons, valueEuros;
	printf("The conversion rate from EEK to EUR is %.4f\n", CONV_RATE_EEK_IN_EUR);
	printf("Please enter a value in EEK: ");
	
	
	scanf("%f", &valueKroons);

	valueEuros = valueKroons / CONV_RATE_EEK_IN_EUR;
	
	printf("%.2f EEK in EUR is %.2f\n", valueKroons, valueEuros);
	return 0;
}
