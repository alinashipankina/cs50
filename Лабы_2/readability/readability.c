#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int counting_letters(string text);
int counting_words(string text);
int counting_sentence(string text);

int main(void)
{
    // Ввод текста пользователем
    string text = get_string("Text: ");

    // Подсчет кол-ва букв, слов и предложений в тексте
    int letters = counting_letters(text);
    // printf("Кол-во букв: %i\n", letters);

    int words = counting_words(text);
    // printf("Кол-во слов: %i\n", words);

    int sentence = counting_sentence(text);
    // printf("Кол-во предложений: %i\n", sentence);

    float L = (float) letters / (float) words * 100.00;
    // printf("%f\n", L);

    float S = (float) sentence / (float) words * 100.00;
    // printf("%f\n", S);

    // Вычисление индекса Коулмана-Ляу
    float index;
    index = 0.0588 * L - 0.296 * S - 15.8;
    // printf("%f\n", index);

    int grade = round(index);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }

    else if (grade > 1 && grade < 17)
    {
        printf("Grade %i\n", grade);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

// Функция расчета кол-ва букв в тексте
int counting_letters(string text)
{
    int letter = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            letter++;
        }
    }

    return letter;
}

// Функция расчета кол-ва слов в тексте
int counting_words(string text)
{
    int count = 0;
    int inWord = 0; // Флаг, показывающий в слове мы сейчас или нет

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isspace(text[i]))
        {
            inWord = 0;
        }
        else if (inWord == 0)
        {
            inWord = 1;
            count++;
        }
    }

    return count;
}

// Функция расчета кол-ва предложений в тексте
int counting_sentence(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Пропускаем пробелы в начале предложения
        while (i < n && isspace(text[i]))
        {
            i++;
        }

        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            if (text[i] == '.' && i + 2 < n && text[i + 1] == '.' && text[i + 2] == '.')
            {
                i += 3;
            }
            count++;
        }

        // Пропускаем пробелы после конца предложения
        while (i + 1 < n && isspace(text[i + 1]))
        {
            i++;
        }
    }

    return count;
}
