#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>

#define USAGE "Usage: caesar <number to shift>\n"\
              "\tAsks for a plaintext and converts by shifting letters by the number of shifts specified.\n"
#define FIRST_UPPER 65
#define LAST_UPPER 90
#define FIRST_LOWER 97
#define LAST_LOWER 122

int main(int argc, string argv[])
{
    if (argc < 2 || argc > 2)
    {
        printf("Incorrect number of arguments.\n");
        printf(USAGE);
        return 1;
    }
    int cipher = atoi(argv[1]) % 26; // mod 26 ensures we can handle numbers greater than 26
    string plaintext = get_string("plaintext: ");
    int initial_val;
    int new_val;
    int difference;
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if ((plaintext[i] >= FIRST_UPPER && plaintext[i] <= LAST_UPPER)
            || (plaintext[i] >= FIRST_LOWER && plaintext[i] <= LAST_LOWER))
        {
            initial_val = plaintext[i];
            new_val = initial_val += cipher;
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
    printf("ciphertext: %s\n", plaintext);
}