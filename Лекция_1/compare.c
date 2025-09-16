#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x = get_int("Введите x: ");
    int y = get_int("Введите y: ");

    if (x < y)
    {
        printf("x меньше, чем y\n");
    }
    else if (x > y)
    {
        printf("x больше, чем y\n");
    }
    else
    {
        printf("x равен y\n");
    }
}
