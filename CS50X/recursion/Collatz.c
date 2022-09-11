//how many steps to get to one

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int col(int n);

int main(void)
{
    int n = get_int("n:");
    int steps = col(n);
    printf("%i\n", steps);
    return 0;
}

int col(int n)
{
    if (n == 1)
    {
        return 0;
    }
    if (n % 2 == 0)
    {
        return 1 + col(n / 2);
    }

    else
    {
        return 1 + col(3 * n +1);
    }

}