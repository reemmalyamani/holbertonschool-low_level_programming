#include "main.h"

/**
 * _isupper - checks for uppercase character
 * @c: The character code to check
 *
 * Return: 1 if c is uppercase (A-Z), 0 otherwise
 */
int _isupper(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}
