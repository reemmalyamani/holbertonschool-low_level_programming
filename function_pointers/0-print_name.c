#include "function_pointers.h"

/**
 * print_name - prints a name using a callback
 * @name: string to print
 * @f: function pointer that prints a string
 *
 * Return: nothing
 */
void print_name(char *name, void (*f)(char *))
{
	if (name == NULL || f == NULL)
		return;
	f(name);
}
