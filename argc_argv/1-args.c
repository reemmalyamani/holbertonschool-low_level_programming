#include <stdio.h>

/**
 * main - prints the number of arguments passed
 * @argc: number of arguments
 * @argv: array of arguments (unused)
 *
 * Return: Always 0
 */
int main(int argc, char *argv[] __attribute__((unused)))
{
	printf("%d\n", argc - 1);
	return (0);
}
