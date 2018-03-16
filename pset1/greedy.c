#include <math.h>
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    float raw_money;
    // prompt for input until we get a positive
    do
    {
        raw_money = get_float("Enter the amount:\n");
    }
    while (raw_money <= 0);

    // convert our float input to an int representing number of cents
    raw_money *= 100;
    int money = round(raw_money);
    // assign variables to represent coins to keep track
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int coins = 0;

    // increment coin counter while the amount is higher than a particlar coin
    while (money >= quarter)
    {
        coins++;
        money -= quarter;
    }
    while (money >= dime)
    {
        coins++;
        money -= dime;
    }
    while (money >= nickel)
    {
        coins++;
        money -= nickel;
    }
    // while we still have money, count the number of pennies
    while (money > 0)
    {
        coins++;
        money -= 1;
    }
    printf("%d\n", coins);
}