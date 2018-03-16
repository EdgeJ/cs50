#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    // get user input and assign to var name
    string name = get_string();
    int initials[6] = {0, 0, 0, 0, 0, 0}; //store the initials in a array
    bool store_next_val = false; //bool to store next letters or not
    int index_val = 0;

    for (int i = 0; i < strlen(name); i++)
    {
        if (i == 0)
        {
            initials[index_val] = name[i];
            index_val++; //increment index value to add next char
        }
        else if (name[i] == 32)
        {
            store_next_val = true; //elem is a space, so capture next elem
        }
        else if (store_next_val)
        {
            initials[index_val] = name[i];
            index_val++; //move on to the next element
            store_next_val = false; //don't store the next char
        }
    }
    for (int i = 0; i < 5; i++)
    {
        if (initials[i] > 0 && initials[i] < 127)
        {
            printf("%c", toupper(initials[i]));
        }
    }
    printf("\n");
}