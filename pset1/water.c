#include <stdio.h>
#include <cs50.h>

int main(void){
    /* get input */
    printf("How many minutes do you shower?\n");
    int shower_length = get_int();
    /* return result */
    printf("%d\n", (shower_length * 12));
    return 0;
}