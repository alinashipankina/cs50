#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long dollars = 1;
    while(true)
    {
        char c = get_char("Здесь $%li. Удваиваем сумму и передаем следующему? ", dollars);
        if (c == 'y')
        {
            dollars *= 2;
        }
        else
        {
            break;
        }
    }
    printf("Здесь $%li.\n", dollars);
}
