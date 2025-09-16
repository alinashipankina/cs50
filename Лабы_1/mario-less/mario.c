#include <cs50.h>
#include <stdio.h>

void print_row(int spaces, int bricks);

int main(void)
{
    // Указание высоты пирамиды пользователем
    int height;
    do
    {
        height = get_int("Введите высоту пирамиды: ");
    }
    while (height < 1 || height > 8);

    // Вывод пирамиды
    for (int i = 0; i < height; i++)
    {
        // Вывод строк с кирпичами
        print_row(height - i, i + 1);
    }
}

void print_row(int spaces, int bricks)
{
    // Вывод пробелов
    for (int i = 0; i < spaces - 1; i++)
    {
        printf(" ");
    }

    for (int j = 0; j < bricks; j++)
    {
        printf("#");
    }

    printf("\n");
}
