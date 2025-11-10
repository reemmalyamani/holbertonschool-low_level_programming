#ifndef FUNCTION_POINTERS_H
#define FUNCTION_POINTERS_H

#include <stddef.h>

/**
 * print_name - calls a function to print a name
 * @name: string to print
 * @f: function pointer to a printer that takes (char *)
 */
void print_name(char *name, void (*f)(char *));

#endif /* FUNCTION_POINTERS_H */
