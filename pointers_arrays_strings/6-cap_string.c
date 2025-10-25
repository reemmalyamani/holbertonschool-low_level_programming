#include "main.h"

/**
 * cap_string - capitalizes all words of a string
 * @str: the string to modify
 * Return: pointer to str
 */
char *cap_string(char *str)
{
	int i = 0, j;
	char separators[] = " \t\n,;.!?\"(){}";

	while (str[i] != '\0')
	{
		/* Capitalize first character if it's lowercase */
		if (i == 0 && (str[i] >= 'a' && str[i] <= 'z'))
			str[i] -= 32;

		/* Check if current char is a separator */
		for (j = 0; separators[j] != '\0'; j++)
		{
			if (str[i] == separators[j])
			{
				if (str[i + 1] >= 'a' && str[i + 1] <= 'z')
					str[i + 1] -= 32;
				break;
			}
		}
		i++;
	}
	return (str);
}

