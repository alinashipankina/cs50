#include <cs50.h>
#include <stdio.h>

int calculate_quarters(int cents);
int calculate_dime(int cents);
int calculate_five_cent_piece(int cents);
int calculate_penny(int cents);

int main(void)
{
    int cents;
    do
    {
        cents = get_int("Введите сдачу в центах: ");
    }
    while (cents < 0);

    int quarters = calculate_quarters(cents);
    cents = cents - (quarters * 25);
    int dime = calculate_dime(cents);
    cents = cents - (dime * 10);
    int five_cent_piece = calculate_five_cent_piece(cents);
    cents = cents - (dime * 5);
    int penny = calculate_penny(cents);
    cents = cents - (dime * 1);
    int sum = quarters + dime + five_cent_piece + penny;

    printf("%i\n", sum);
}

int calculate_quarters(int cents)
{
    int quarters = 0;
    while (cents >= 25)
    {
        quarters++;
        cents = cents - 25;
    }
    return quarters;
}

int calculate_dime(int cents)
{
    int dime = 0;
    int ostatok = cents % 25;
    while (cents >= 10 && ostatok < 25 && ostatok > 9)
    {
        dime++;
        cents = cents - 10;
        ostatok = cents % 25;
    }
    return dime;
}

int calculate_five_cent_piece(int cents)
{
    int five_cent_piece = 0;
    int ostatok = cents % 25;
    while (cents >= 5 && ostatok < 10 && ostatok > 4)
    {
        five_cent_piece++;
        cents = cents - 5;
        ostatok = cents % 25;
    }
    return five_cent_piece;
}

int calculate_penny(int cents)
{
    int penny = 0;
    int ostatok = cents % 5;
    while (cents >= 1 && ostatok < 5 && ostatok > 0)
    {
        penny++;
        cents = cents - 1;
        ostatok = cents % 5;
    }
    return penny;
}
