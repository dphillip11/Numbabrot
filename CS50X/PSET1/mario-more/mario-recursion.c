#include <cs50.h>
#include <stdio.h>

void pyramid(int i, int n);
int main(void)

{
    int n;
    do
    {
        n = get_int("Height:");
    }
    while (n < 1 || n > 8);

    //gathered suitable height value

    pyramid(n, n);
}

//recursive pyramid
void pyramid(i, n)
{
    if (i - 1 > 0)
    {
        pyramid(i - 1, n);
    }
    //right spaces
    for (int j = i; j < n; j++)
    {
        printf(" ");
    }

    for (int k = 0; k < i; k++)
    {
        printf("#");
    }
    //middle space
    printf(" ");
    //rest of pyramid
    for (int k = 0; k < i; k++)
    {
        printf("#");
    }
    printf("\n");
}