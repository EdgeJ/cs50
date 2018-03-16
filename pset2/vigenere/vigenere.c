#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

#define USAGE "Usage: vigenere <keyword>\n"\
              "\tAsks for a plaintext and encrypts the text using a Vigenère's cipher.\n"
#define FIRST_UPPER 65
#define LAST_UPPER 90
#define FIRST_LOWER 97
#define LAST_LOWER 122

int main(int argc, string argv[])
{
    int debug = 0; //debug flag
    if (argc < 2 || argc > 2)
    {
        printf("Incorrect number of arguments.\n");
        printf(USAGE);
        return 1;
    }
    string keyword = argv[1];
    int cipher[strlen(keyword)]; // create an array to store numeric values
    for (int i = 0; i < strlen(keyword); i++)
    {
        if (! isalpha(keyword[i]))
        {
            printf("Cipher only accepts alpha chars.\n");
            return 1;
        }
        else
        {
            // convert all to uppers, so we can worry about only 26 possibilities
            keyword[i] = toupper(keyword[i]);
        }
        /*
            we can just subtract the beginning ASCII code from all letters to
            get the number of their position in the alphabet
        */
        cipher[i] = keyword[i] - FIRST_UPPER;
    }
    string plaintext = get_string("plaintext: ");
    int initial_val;
    int new_val;
    int difference;
    int cipher_pos = 0; //track which index we take of the cipher
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if ((plaintext[i] >= FIRST_UPPER && plaintext[i] <= LAST_UPPER)
            || (plaintext[i] >= FIRST_LOWER && plaintext[i] <= LAST_LOWER))
        {
            initial_val = plaintext[i];
            new_val = initial_val + cipher[cipher_pos];
            cipher_pos++;
            // check if we've moved the index beyond the last array elem
            if (cipher_pos >= strlen(keyword))
            {
                cipher_pos = 0;
            }
            /*
            check if the ASCII val to determine case and check that the ASCII range isn't
            increased beyond the case range (i.e. not increased more than 26 beyond 1st ASCII val)
            so, take the difference between the the first ASCII value for the case, mod 26 to account
            for differences greater than the alphabet range, then add 65 + difference to 'wrap' the
            value back around the alphabet range
            */
            if (initial_val <= LAST_UPPER && new_val > LAST_UPPER)
            {
                difference = (new_val - FIRST_UPPER) % 26;
                plaintext[i] = FIRST_UPPER + difference;
            }
            else if (initial_val >= FIRST_LOWER && new_val > LAST_LOWER)
            {
                difference = (new_val - FIRST_LOWER) % 26;
                plaintext[i] = FIRST_LOWER + difference;
            }
            else
            {
                // the char doesn't need to wrap, so just assign it the new value
                plaintext[i] = new_val;
            }
        }
    }
    if (debug)
    {
        for (int i = 0; i < strlen(keyword); i++)
        {
            printf("DEBUG: %c - %i\n", keyword[i], cipher[i]);
        }
        printf("DEBUG: keyword length - %lu\n", strlen(keyword));
        printf("DEBUG: cipher length - %lu\n", sizeof(cipher) / sizeof(cipher[0]));
    }
    printf("ciphertext: %s\n", plaintext);
}