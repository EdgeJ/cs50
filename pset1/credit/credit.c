#include <stdio.h>
#include <string.h>
#include <cs50.h>

int main(void)
{
    string card_number = get_string();
    if (strlen(card_number) < 13 || strlen(card_number) > 16)
    {
        printf("INVALID\n");
        return 1;
    }
    for (int i = strlen(card_number) - 2; i > 0; i -= 2)
    {
        printf("%s\n", strchr(card_number, i));
        /*
        int converted_num = atoi(num);
        printf("%d\n", converted_num);
        */
    }
}