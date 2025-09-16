#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int kol_symbol(long number);
bool first_figures(long figure, int find_number);
bool check_sum(long figure);

int main(void)
{
    long card = get_long("Number: ");
    int kol = kol_symbol(card);
    bool is_valid = check_sum(card);
    // printf("%d\n", is_valid);

    if (is_valid)
    {
         if (kol == 15 && (first_figures(card, 34) || first_figures(card, 37)))
         {
             printf("AMEX\n");
         }
         else if (kol == 16 && (first_figures(card, 51) || first_figures(card, 52) || first_figures(card, 53) || first_figures(card, 54) || first_figures(card, 55)))
         {
             printf("MASTERCARD\n");
         }
         else if ((kol == 13 || kol == 16) && first_figures(card, 4))
         {
             printf("VISA\n");
         }
         else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}


int kol_symbol(long number)
{
    int lenght = 1;

    while (true) {
        number = number / 10;
        if (number < 1) {
            break;
        }
        lenght = lenght + 1;
    }
    return lenght;
}

bool first_figures(long figure, int find_number)
{
    bool result = false;
    int find_number_lenght = kol_symbol(find_number);
    int x = kol_symbol(figure);

    while (x >= 1){
        figure = figure / 10;
        x = x - 1;
        if (x == find_number_lenght && figure == find_number) {
            result = true;
            break;
        }
    }
    return result;
}

bool check_sum(long figure)
{
    int n = kol_symbol(figure);
    // printf("Кол-во символов в номере карты: %i\n", n);
    char s[n];
    sprintf(s, "%li", figure);
    // printf("Строковое число: %s\n", s);

    int sum_1 = 0;
    int sum_2 = 0;

    for (int i = n - 2; i >= 0; i = i - 2)
    {
        int char_to_int = s[i] - '0';
        char_to_int *= 2;

        if (char_to_int > 9)
        {
            char_to_int = (char_to_int / 10) + (char_to_int % 10);
        }

        sum_1 = sum_1 + char_to_int;

    }
    // printf("Сумма каждой второй цифры, начиная с предпоследней: %i\n", sum_1);

    for (int j = n - 1; j >= 0 ; j = j - 2)
    {
        int char_to_int = s[j] - '0';

        if (char_to_int > 9)
        {
            char_to_int = (char_to_int / 10) + (char_to_int % 10);
        }

        sum_2 = sum_2 + char_to_int;

    }
    // printf("Сумма оставшихся цифр: %i\n", sum_2);

    int all_sum = sum_1 + sum_2;

    return all_sum % 10 == 0;
}
