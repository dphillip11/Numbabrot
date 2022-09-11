//print rows of fibonnaci

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int fib(int n);

int main(void)
{
    int n = get_int("n:");
    int f = fib(n);
    printf("%i\n", f);
    return 0;
}

int fib(int n)
{
    if ( n == 0)
    {
        return 0;
    }
    if (n == 1)
    {
        return 1;
    }
    if (n == 2)
    {
        return 2 ;
    }

    else
    {
        return fib(n-2) + fib(n - 1);
    }

}