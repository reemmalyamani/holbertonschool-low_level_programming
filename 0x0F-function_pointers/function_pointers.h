#ifndef FUNCTION_POINTERS_H
#define FUNCTION_POINTERS_H

#include <stddef.h>

/**
 * print_name - prints a name
 * @name: the name to be printed
 * @f: pointer to a function that prints a name
 */
void print_name(char *name, void (*f)(char *));

#endif /* FUNCTION_POINTERS_H */
