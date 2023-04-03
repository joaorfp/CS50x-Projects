#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    printf("quarters: %i\n", quarters);
    cents = cents - quarters * 25;
    printf("cents: %i\n", cents);


    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    printf("dimes: %i\n", dimes);
    cents = cents - dimes * 10;
    printf("cents: %i\n", cents);

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    printf("nickels: %i\n", nickels);
    cents = cents - nickels * 5;
    printf("cents: %i\n", cents);

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    printf("pennies: %i\n", pennies);
    cents = cents - pennies * 1;
    printf("cents: %i\n", cents);

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;
    printf("coins: %i\n", coins);

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    int cash;
    // gets the quantity of change
    do
    {
        cash = get_int("Change owed: ");
    }
    while (cash < 0);
    return cash;
}

int calculate_quarters(int cents)
{
    int quarters = 0;
    // get the quantity of money, subtract by the coin value and add 1 coin each time
    while (cents >= 25)
    {
        cents -= 25;
        quarters++;
    }
    return quarters;
}

int calculate_dimes(int cents)
{
    int dimes = 0;
    // get the quantity of money, subtract by the coin value and add 1 coin each time
    while (cents >= 10)
    {
        cents -= 10;
        dimes++;
    }
    return dimes;
}

int calculate_nickels(int cents)
{
    int nickels = 0;
    // get the quantity of money, subtract by the coin value and add 1 coin each time
    while (cents >= 5)
    {
        cents -= 5;
        nickels++;
    }
    return nickels;
}

int calculate_pennies(int cents)
{
    int pennies = 0;
    // get the quantity of money, subtract by the coin value and add 1 coin each time
    while (cents >= 1)
    {
        cents -= 1;
        pennies++;
    }
    return pennies;
}
