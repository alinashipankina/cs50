#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
bool is_preferred(int i, int j, int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool has_cycle(int winner, int loser);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Обновить рейтинги с учетом нового голоса
bool vote(int rank, string name, int ranks[])
{
    // Проверяем, что rank находится в допустимых пределах
    if (rank < 0 || rank >= candidate_count)
    {
        return false;
    }

    // Проверяем каждого кандидата
    for (int i = 0; i < candidate_count; i++)
    {
        // Имя кандидата совпадает с переданным name
        if (strcmp(candidates[i], name) == 0)
        {
            // Обновляем предпочтение избирателя
            ranks[rank] = i; // Записываем индекс кандидата
            return true; // Успешно сохранено
        }
    }

    // Если кандидат не найден
    return false;
}

// Обновляет глобальный массив preferences на основе текущего избирателя
void record_preferences(int ranks[])
{
    // Проходим по всем парам кандидатов (i, j)
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // Если i стоит выше j в предпочтениях избирателя, увеличиваем preferences[i][j]
            if (i != j && is_preferred(i, j, ranks))
            {
                preferences[i][j]++;
            }
        }
    }
}

// Вспомогательная функция: проверяет, стоит ли кандидат i выше j в ranks
bool is_preferred(int i, int j, int ranks[])
{
    // Проходим по ranks и ищем, кто из кандидатов (i или j) встречается раньше
    for (int k = 0; k < candidate_count; k++)
    {
        if (ranks[k] == i)
        {
            return true; // i встретился раньше j → предпочтение в пользу i
        }
        if (ranks[k] == j)
        {
            return false; // j встретился раньше i → предпочтение в пользу j
        }
    }
    return false; // (теоретически недостижимо, если все кандидаты учтены)
}

// Запишите пары кандидатов, где один из них предпочтительнее другого
void add_pairs(void)
{
    // Обнуляем pair_count перед заполнением
    pair_count = 0;

    // Перебираем все уникальные пары (i, j), где i < j
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Если i предпочтительнее j
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            // Если j предпочтительнее i
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
            // Если предпочтения равны (ничья), пара не добавляется
        }
    }
}

// Сортировать пары в порядке убывания силы победителя
void sort_pairs(void)
{
    // Пузырьковая сортировка (менее эффективная, но простая)
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            // Сравниваем пары по силе победы
            int strength_current = preferences[pairs[j].winner][pairs[j].loser];
            int strength_next = preferences[pairs[j + 1].winner][pairs[j + 1].loser];

            // Если текущая пара слабее следующей, меняем местами
            if (strength_current < strength_next)
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
}

// Вспомогательная функция для проверки циклов (DFS)
bool has_cycle(int winner, int loser)
{
    // Если loser == winner, значит, цикл найден
    if (loser == winner)
    {
        return true;
    }

    // Проверяем всех кандидатов, которых loser "бьёт"
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] && has_cycle(winner, i))
        {
            return true;
        }
    }

    return false;
}

void lock_pairs(void)
{
    // Инициализация графа (все рёбра false)
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    // Добавляем рёбра из pairs, если нет цикла
    for (int k = 0; k < pair_count; k++)
    {
        int winner = pairs[k].winner;
        int loser = pairs[k].loser;

        // Проверяем, не создаёт ли ребро цикл
        if (!has_cycle(winner, loser))
        {
            locked[winner][loser] = true;
        }
    }
}

// Напечатайте победителя выборов
void print_winner(void)
{
    // Проверяем каждого кандидата
    for (int i = 0; i < candidate_count; i++)
    {
        bool is_source = true;

        // Проверяем, есть ли рёбра, ведущие к i (входящие)
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                is_source = false;
                break;
            }
        }

        // Если i — источник, выводим его имя
        if (is_source)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
