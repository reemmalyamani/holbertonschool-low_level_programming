#include <stdio.h>

/**
 * main - Entry point
 *
 * Description: Prints the lowercase alphabet in reverse order,
 * using only the putchar function twice.
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    char ch;

    for (ch = 'z'; ch >= 'a'; ch--)
        putchar(ch);
    putchar('\n');

    return (0);
}
