#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Массив с очками за буквы
int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int number_of_points(string word);

int main(void)
{
    // Ввод слов игроками 1 и 2
    string word_1 = get_string("Player 1: ");
    string word_2 = get_string("Player 2: ");

    // Присвоение очков каждому игроку
    int points_player_1 = number_of_points(word_1);
    int points_player_2 = number_of_points(word_2);

    // Вывод кол-ва очков
    // printf("Points player 1: %i\n", points_player_1);
    // printf("Points player 2: %i\n", points_player_2);

    // Сравнение очков у игроков и выведение результатов игры
    if (points_player_1 > points_player_2)
    {
        printf("Player 1 wins! \n");
    }
    else if (points_player_1 < points_player_2)
    {
        printf("Player 2 wins! \n");
    }
    else
    {
        printf("Tie! \n");
    }
}

// Функция подсчета кол-ва очков
int number_of_points(string word)
{
    int sum = 0;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (isupper(word[i]))
        {
            sum += points[word[i] - 'A'];
        }
        else if (islower(word[i]))
        {
            sum += points[word[i] - 'a'];
        }
    }

    return sum;
}
