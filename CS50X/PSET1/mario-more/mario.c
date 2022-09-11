#include <cs50.h>
#include <stdio.h>

void pyramid(int i);
int main(void)

{
    int n;
    do
    {
        n = get_int("Height:");
    }
    while (n < 1 || n > 8);

//gathered suitable height value

    for (int i = 0; i < n; i++)
    {
        for (int j = n - i; j > 1; j--)
        {
            printf(" ");
        }

        // produced spaces

        pyramid(i);

        //produced blocks

        printf("  ");

        //produced spaces

        pyramid(i);

        //second set of blocks, left aligned

        printf("\n");

        //next line
    }
}

void pyramid(i)
{
    for (int k = 0; k < i + 1; k++)
    {
        printf("#");
    }
}