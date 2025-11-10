#include "function_pointers.h"

/**
 * print_name - prints a name using a callback
 * @name: string to print
 * @f: function pointer that prints a string
 */
void print_name(char *name, void (*f)(char *))
{
	/* Betty: use tabs, not spaces */
	if (name == NULL || f == NULL)
		return;

	f(name);
}
