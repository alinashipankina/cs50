#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    if (argc != 2 || !only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        long number = atoi(argv[1]);
        // printf("%li\n", number);

        string plaintext = get_string("plaintext: ");
        // printf("Открытый текст: %s\n", plaintext);

        char ciphertext[strlen(plaintext) + 1];

        for (int i = 0, n = strlen(plaintext); i <= n; i++)
        {
            char letter = rotate(plaintext[i], number);
            // printf("cipherletter: %c\n", letter);
            ciphertext[i] = letter;

            if (i == n)
            {
                ciphertext[n] = '\0';
            }
        }

        printf("ciphertext: %s\n", ciphertext);

        return 0;
    }
}

// Функция проверки вводимых чисел в аргументе командной строки
bool only_digits(string s)
{
    bool digit = true;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isdigit(s[i]) && !isalpha(s[i]))
        {
            digit = true;
        }

        else
        {
            digit = false;
            break;
        }
    }

    return digit;
}

// Функция "разворота" символов
char rotate(char c, int n)
{
    // int rotate_letter = 0;
    int ostatok = n % 26;
    if (isupper(c))
    {
        // printf("rotate('%c', %i) = ", c, ostatok);
        return 'A' + (c - 'A' + ostatok) % 26;
    }

    else if (islower(c))
    {
        // printf("rotate('%c', %i) = ", c, ostatok);
        return 'a' + (c - 'a' + ostatok) % 26;
    }
    else
    {
        return c; // Не буквы остаются без изменений
    }
}
