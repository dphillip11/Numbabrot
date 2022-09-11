#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


int main(void)

{

    string number = get_string("Number:");

    int length = strlen(number);
    int sumofodds = 0;
    int sumofdoubles = 0;
    int twofold;
    int first = (number[0]-48), second = (number[1]-48), third = (number[2]-48), fourth = (number[3]-48);

    //initialise variable for digit numbers, i will represent digit number


    //find last digit, shorten number by one digit, add digits to checksum total as we go along
    //checksum = sum of odd digits plus the sum of characters used in the doubles of even digits

    for (int i = 1 ; i < length + 1; i ++)
    {
        if (i % 2 == 1)
        {
            sumofodds += (number[length - i] - 48);
        }
        else
        {
            twofold = 2 * (number[length - i] - 48);

            if (twofold > 9)
            {
                sumofdoubles += (twofold % 10) + 1;
            }
            else
            {
                sumofdoubles += twofold;
            }
        }
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

        if (length == 15 && first == 3 && (second == 4 || second == 7))
        {
            printf("AMEX\n");

            amex = 1;
        }

        if (length == 16 && first == 5 && second > 0 && second < 6)
        {
            printf("MASTERCARD\n");

            mastercard = 1;
        }

        if ((length == 13 && first == 4) || (length == 16 && first == 4))
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