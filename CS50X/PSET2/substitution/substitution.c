#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool only_letters(string s);
string encode(string plaintext, string key);
bool repeated_letters(string key);

int main(int argc, string argv[])
{
    //too many or too few arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //correct length key?
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 letters\n");
        return 1;
    }

    //are the arguments in the correct format?
    if (only_letters(argv[1]) == false)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    if (repeated_letters(key) != true)
    {
        printf("Key must contain 26 letters\n");
        return 1;
    }

    //prompt user for plain text
    string plain_text = get_string("plaintext: ");

    //apply substitution
    string cipher_text = encode(plain_text, key);

    printf("ciphertext: %s\n", cipher_text);

    return 0;

}

bool only_letters(string s)
{
    //assume true unless proven otherwise, all characters are letters
    bool letters = true;

    //iterate for each letter
    for (int i = 0, n = strlen(s); i < n; i ++)
    {
        // check letters
        if (isalpha(s[i]) == 0)
        {
            letters = false;
        }
    }

    return letters;
}

bool repeated_letters(string key)
{

    for (int k = 0; k < 26; k ++)
    {
        int repeat_count = 0;
        for (int l = 0; l < 26; l++)
        {
            if (tolower(key[k]) == tolower(key[l]))
            {
                repeat_count ++;
            }

        }
        if (repeat_count != 1)
        {
            return false;
        }

    }
    return true;
}

string encode(string plaintext, string key)
//substitutes letters
{
    string ciphertext = plaintext;

    for (int j = 0, m = strlen(plaintext); j < m; j ++)
    {
        if (isalpha(plaintext[j]))
        {
            if islower(plaintext[j])
            {
                //converts to alphabetic position then apply key
                ciphertext[j] = tolower(key[plaintext[j] - 97]);

            }
            else
            {
                //upper case letters
                ciphertext[j] = toupper(key[plaintext[j] - 65]);

            }
        }
    }
    return (string)ciphertext;
}