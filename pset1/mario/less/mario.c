#include <cs50.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        printf("Enter the height of the pyramid\n");
        height = get_int();
    }
    //ask for input until the value is between 0 and 23
    while (height < 0 || height > 23);
    if (height == 1)
    {
        // if height is 1, just print two hashes and be done
        printf("##\n");
    }
    else
    {
        for (int i = 0; i < height; i++)
        {
            // subtract 1 from the height on each successive loop
            int spaces = height - (i + 1);
            // subtract the number of spaces from the total number of characters
            // we print on each loop
            int hashes = (height + 1) - spaces;
            // use spaces and hashes as decrementing variables for while loops
            while (spaces > 0)
            {
                printf(" ");
                spaces--;
            }
            while (hashes > 0)
            {
                printf("#");
                hashes--;
            }
            printf("\n");
        }
    }
}