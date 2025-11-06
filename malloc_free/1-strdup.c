#include "main.h"
#include <stdlib.h>

/**
 * _strdup - returns a pointer to a newly allocated space in memory
 *           containing a copy of the string given as a parameter
 * @str: the string to duplicate
 *
 * Return: pointer to duplicated string, or NULL if str is NULL or malloc fails
 */
char *_strdup(char *str)
{
	char *dup;
	unsigned int i, length = 0;

	if (str == NULL)
		return (NULL);

	while (str[length] != '\0')
		length++;

	dup = malloc((length + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);

	for (i = 0; i < length; i++)
		dup[i] = str[i];

	dup[length] = '\0';
	return (dup);
}
