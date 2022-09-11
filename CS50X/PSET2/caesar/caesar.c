#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool only_digits(string s);
string rotate(string plaintext, int key);

int main(int argc, string argv[])
{
    //too man or too few arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //are the arguments in the correct format?
    if (only_digits(argv[1]) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        //cipher key rotates letters so 25 is the largest useful key
        int cipher_key = atoi(argv[1]) % 26;

        string plain_text = get_string("plaintext: ");

        string cipher_text = rotate(plain_text, cipher_key);

        printf("ciphertext: %s\n", cipher_text);

        return 0;
    }
}

bool only_digits(string s)
{
    //assume true unless proven otherwise, all characters are digits
    bool digits = true;

    if (strlen(s) > 0)
    {
        for (int i = 0, n = strlen(s); i < n; i ++)
        {
            // ASCII values for numerals
            if (s[i] < 47 || s[i] > 58)
            {
                digits = false;
            }
        }

    }
    else
    {
        return 1;
    }
    return digits;
}

string rotate(string plaintext, int key)
//moves letters by corresponding key value
{
    string ciphertext = plaintext;

    for (int j = 0, m = strlen(plaintext); j < m; j ++)
    {
        if (isalpha(plaintext[j]))
        {
            if islower(plaintext[j])
            {
                //converts to alphabetic position then converts back
                ciphertext[j] = ((plaintext[j] - 96 + key) % 26 + 96);

            }
            else
            {
                //upper case letters
                ciphertext[j] = ((plaintext[j] - 64 + key) % 26 + 64);

            }
        }
    }
    return (string)ciphertext;
}