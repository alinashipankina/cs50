#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool only_letters(string s);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (!only_letters(argv[1]))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        string plaintext = get_string("plaintext: ");
        // printf("Открытый текст: %s\n", plaintext);

        string key = argv[1];

        // Шифрование
        printf("ciphertext: ");
        for (int i = 0; plaintext[i] != '\0'; i++)
        {
            if (isalpha(plaintext[i]))
            {
                char original_char = plaintext[i];
                char substitute;
                if (isupper(original_char))
                {
                    substitute = toupper(key[original_char - 'A']);
                }
                else
                {
                    substitute = tolower(key[original_char - 'a']);
                }
                printf("%c", substitute);
            }
            else
            {
                printf("%c", plaintext[i]);
            }
        }
        printf("\n");

        return 0;
    }
}


// Функция проверки вводимых букв в аргументе командной строки
bool only_letters(string key)
{
    // Проверка длины ключа
    if (strlen(key) != 26)
    {
        return false;
    }

    int letter_counts[26] = {0};

    for (int i = 0; key[i] != '\0'; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }

        char lower_char = tolower(key[i]);
        letter_counts[lower_char - 'a']++;

        // Проверка на дубликаты
        if (letter_counts[lower_char - 'a'] > 1)
        {
            return false;
        }
    }

    // Проверка, что все буквы присутствуют
    for (int i = 0; i < 26; i++)
    {
        if (letter_counts[i] != 1)
        {
            return false;
        }
    }

    return true;
}
