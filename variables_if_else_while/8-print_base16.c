#include <stdio.h>

/**
 * main - Entry point
 *
 * Description: Prints all the numbers of base 16 in lowercase,
 * using only the putchar function three times.
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    int n;

    for (n = 0; n < 10; n++)
        putchar(n + '0');

    for (n = 'a'; n <= 'f'; n++)
        putchar(n);

    putchar('\n');

    return (0);
}
