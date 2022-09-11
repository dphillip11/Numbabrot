#include <cs50.h>
#include <stdio.h>
#include <math.h>


int main(void)

{

    long number = get_long("Number:");

    int lastdigit = number % 10;
    int i = 1;
    int sumofodds = 0;
    int sumofdoubles = 0;
    int twofold;
    int thirteen = 0, fourteen = 0, fifteen = 0, sixteen = 0;

    //initialise variable for digit numbers, i will represent digit number


    //find last digit, shorten number by one digit, add digits to checksum total as we go along
    //checksum = sum of odd digits plus the sum of characters used in the doubles of even digits

    while (number > 0)
    {
        if (i % 2 == 1)
        {
            sumofodds += lastdigit;
        }
        else
        {
            twofold = 2 * lastdigit;

            if (twofold > 9)
            {
                sumofdoubles += (twofold % 10) + 1;
            }
            else
            {
                sumofdoubles += twofold;
            }
        }

        //store condition digits to determine card type

        if (i == 13)
        {
            thirteen = lastdigit;
        }

        if (i == 14)
        {
            fourteen = lastdigit;
        }

        if (i == 15)
        {
            fifteen = lastdigit;
        }

        if (i == 16)
        {
            sixteen = lastdigit;
        }

        number = (number - lastdigit) / 10;

        lastdigit = number % 10;

        i = i + 1;

    }

    int checksum = sumofodds + sumofdoubles;

    //checksum passes criteria, ends in 0
    //initialise boolean conditions for card type
    int amex = 0;
    int mastercard = 0;
    int visa = 0;

    if (checksum % 10 == 0)
    {
        //boolean for pass checksum, useful for debugging
        int pass_checksum = 1;

        if (i == 16 && fifteen == 3 && (fourteen == 4 || fourteen == 7))
        {
            printf("AMEX\n");

            amex = 1;
        }

        if (i == 17 && sixteen == 5 && fifteen > 0 && fifteen < 6)
        {
            printf("MASTERCARD\n");

            mastercard = 1;
        }

        if ((i == 14 && thirteen == 4) || (i == 17 && sixteen == 4))
        {
            printf("VISA\n");

            visa = 1;
        }

        //not any of the given card types
        if (amex == 0 == mastercard == visa)
        {
            printf("INVALID\n");
        }
    }

    else
    {
        //failed checksum
        printf("INVALID\n");

        int pass_checksum = 0;
    }

}