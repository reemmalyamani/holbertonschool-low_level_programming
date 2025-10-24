#include "main.h"

/**
 * _atoi - converts a string to an integer
 * @s: the string to convert
 *
 * Return: the integer value of the string, or 0 if none found
 */
int _atoi(char *s)
{
	int i = 0;
	int sign = 1;
	unsigned int result = 0;
	int number_found = 0;

	/* skip all non-number and sign characters */
	while (s[i] != '\0')
	{
		if (s[i] == '-')
			sign *= -1;
		else if (s[i] >= '0' && s[i] <= '9')
		{
			number_found = 1;
			result = (result * 10) + (s[i] - '0');
		}
		else if (number_found)
			break;
		i++;
	}

	return (result * sign);
}
