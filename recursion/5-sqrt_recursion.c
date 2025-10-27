#include "main.h"

int actual_sqrt(int n, int i);

/**
 * _sqrt_recursion - returns the natural square root of a number
 * @n: number to find the square root of
 *
 * Return: natural square root or -1
 */
int _sqrt_recursion(int n)
{
	if (n < 0)
		return (-1);

	return (actual_sqrt(n, 0));
}

/**
 * actual_sqrt - helper to find sqrt recursively
 * @n: number
 * @i: iterator
 *
 * Return: square root or -1
 */
int actual_sqrt(int n, int i)
{
	if (i * i > n)
		return (-1);

	if (i * i == n)
		return (i);

	return (actual_sqrt(n, i + 1));
}
