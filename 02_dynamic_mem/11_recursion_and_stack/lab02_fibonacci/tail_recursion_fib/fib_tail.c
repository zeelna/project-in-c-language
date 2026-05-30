
/**
 * File:        fib_tail.c
 * Author:      Frank Christopher Kirch
 * Created:     23.04.2023
 * Last edit:   23.04.2023
 *
 * Description: A demo program showing how to find fibonacci recursively.
 *              Uses tail recursion.
 */
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define ARGS_CNT 2
#define ARGS_EXEC 		 argv[0]
#define ARGS_N  		 argv[1]

int FibTail(int n, int prev, int fib);

int Fibonacci2(int n, int ans);

int main (int argc, char **argv)
{
	if (argc != ARGS_CNT)
	{
		printf("Usage: '%s' - x^y \n", ARGS_EXEC);
		return EXIT_FAILURE;
	}
	int n = atoi(ARGS_N);
	printf("fib(%d) = %d \n", n, FibTail(n, 1, 1));
	return EXIT_SUCCESS;
}

int FibTail(int n, int fib, int prev)
{
	if (n == 1)
		return prev;
	return FibTail(n - 1, prev + fib, fib);
	
}
 

