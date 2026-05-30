
/**
 * File:        fib.c
 * Author:      Frank Christopher Kirch
 * Created:     22.04.2023
 * Last edit:   22.04.2023
 *
 * Description: A demo program showing how to find sum of elenment recursively.
 *              Uses tail recursion.
 */
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define ARGS_CNT 2
#define ARGS_EXEC 		 argv[0]
#define ARGS_N  		 argv[1]

int Fibonacci(int n);


int main (int argc, char **argv)
{
	if (argc != ARGS_CNT)
	{
		printf("Usage: '%s' - x^y \n", ARGS_EXEC);
		return EXIT_FAILURE;
	}
	int n = atoi(ARGS_N);
	
	printf("fib(%d) = %d \n", n, Fibonacci(n));

	return EXIT_SUCCESS;
}


int Fibonacci(int n)
{
	if (n < 3)
		return 1;
	return Fibonacci(n - 1) + Fibonacci(n - 2);
}




 

