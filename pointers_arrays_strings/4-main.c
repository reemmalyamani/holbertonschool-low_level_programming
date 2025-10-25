#include "main.h"
#include <stdio.h>

/**
 * main - check the code
 *
 * Return: Always 0.
 */
int main(void)
{
    int n;
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i;

    n = sizeof(a) / sizeof(int);

    for (i = 0; i < n; i++)
    {
        printf("%d", a[i]);
        if (i < n - 1)
            printf(", ");
    }
    printf("\n");

    reverse_array(a, n);

    for (i = 0; i < n; i++)
    {
        printf("%d", a[i]);
        if (i < n - 1)
            printf(", ");
    }
    printf("\n");

    return (0);
}

