#include <cs50.h>
#include <stdio.h>

int main(void)
{
    char c = get_char("Вы согласны? ");

    if (c == 'y' || c == 'Y')
    {
        printf("Согласен.\n");
    }
    else if (c == 'n' || c == 'N')
    {
        printf("Не согласен.\n");
    }
}
