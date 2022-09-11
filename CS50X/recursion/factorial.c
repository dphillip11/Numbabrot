// factorial function

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int factorial(int n);

int main(void)
{
    int n = get_int("n:");
    int f = factorial(n);
    printf("factorial = %i\n", f);
    return 0;

}

int factorial(int n)
{
    if (n == 1)
        return 1;
    else
        return n * factorial(n-1);
}