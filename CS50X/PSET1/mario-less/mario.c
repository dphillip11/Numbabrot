#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Height:");
    }
    while (n < 1 || n > 8);

    for (int i = 0; i < n; i++)
    {
        //produce spaces to right align
        for (int k = n - i; k > 1; k--)
        {
            printf(" ");
        }
        //place blocks and move right
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        // go to next line
        printf("\n");
    }
}