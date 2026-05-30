#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ARGS_CNT 2

int Factorial(int n);



int main (int argc, char **argv)
{
	if (argc != ARGS_CNT)
	{
		printf("Usage: %s number\n", argv[0]);
		return 1;
	}
	
	int n = atoi(argv[1]);
	if (n < 0) 
	{
		printf("Error! Input must be 0 or grater\n");
		return 1;
	}
	
	printf("Factorial of %d is %d\n", n, Factorial(n));
	
	return 0;
}

int Factorial(int n)
{
	// Baasjuht rekursioonile (lõpetab rekursiooni)
	if (n == 0 || n == 1)
		return 1;
	
	// Üldjuht (kutsub rekursiivselt välja)
	return n * Factorial(n - 1);
}
