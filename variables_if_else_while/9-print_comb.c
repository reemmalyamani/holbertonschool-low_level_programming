#include <stdio.h>

/**
 * main - Entry point
 *
 * Description: Prints all possible combinations of single-digit numbers
 * Numbers are separated by ", " and printed in ascending order.
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    int n;

    for (n = 0; n < 10; n++)
    {
        putchar(n + '0');
        if (n != 9)
        {
            putchar(',');
            putchar(' ');
        }
    }

    putchar('\n');

    return (0);
}
