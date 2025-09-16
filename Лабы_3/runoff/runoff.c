#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Максимальное количество избирателей и кандидатов
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// предпочтения[i][j] - это j-е предпочтение избирателя i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// У кандидатов есть имя, подсчет голосов, статус выбывшего
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Множество кандидатов
candidate candidates[MAX_CANDIDATES];

// Число избирателей и кандидатов
int voter_count;
int candidate_count;

// Прототипы функций
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Проверка, нет ли недопустимого использования
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Заполнение массива кандидатов
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Продолжение запроса голосов
    for (int i = 0; i < voter_count; i++)
    {

        // Запрос для каждого ранга
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Протокольное голосование, если только оно не является недействительным
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Продолжайте проводить второй тур до тех пор, пока не определится победитель
    while (true)
    {
        // Подсчитайте голоса, отданные оставшимся кандидатам
        tabulate();

        // Проверьте, были ли выиграны выборы
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Отсеять кандидатов, занявших последние места
        int min = find_min();
        bool tie = is_tie(min);

        // Если ничья, выигрывают все
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Исключите любого, у кого будет минимальное количество голосов
        eliminate(min);

        // Сброс количества голосов обратно к нулю
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Запишите предпочтение, если голосование действительно
bool vote(int voter, int rank, string name)
{
    // Проверяем каждого кандидата
    for (int i = 0; i < candidate_count; i++)
    {
        // Имя кандидата совпадает с переданным name
        if (strcmp(candidates[i].name, name) == 0)
        {
            // Обновляем предпочтение избирателя voter
            preferences[voter][rank] = i; // Записываем индекс кандидата
            return true; // Успешно сохранено
        }
    }

    // Если кандидат не найден
    return false;
}

// Подсчитайте голоса за не выбывших кандидатов
void tabulate(void)
{
    // Проходим по каждому избирателю
    for (int i = 0; i < voter_count; i++)
    {
        // Проходим по предпочтениям избирателя i
        for (int j = 0; j < candidate_count; j++)
        {
            // Получаем индекс кандидата, которого избиратель i поставил на j-е место
            int candidate_index = preferences[i][j];

            // Если кандидат не выбыл, засчитываем голос и переходим к следующему избирателю
            if (!candidates[candidate_index].eliminated)
            {
                candidates[candidate_index].votes++;
                break; // Прерываем цикл, так как голос уже учтен
            }
        }
    }
}

// Выведите имя победителя выборов, если таковой имеется
bool print_winner(void)
{
    int majorty = voter_count / 2 + 1;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= majorty)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Верните минимальное количество голосов, набранных любым оставшимся кандидатом
int find_min(void)
{
    int min_votes = voter_count;

    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes < min_votes)
        {
            min_votes = candidates[i].votes;
        }
    }

    return min_votes;
}

// Возвращает значение true, если результаты выборов распределились между всеми кандидатами, и значение false в противном случае
bool is_tie(int min)
{
    // Проверяем, есть ли хотя бы один невыбывший кандидат
    bool active_candidates_exist = false;

    // Проверяем всех кандидатов
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            active_candidates_exist = true;
            // Если у кандидата не минимальное количество голосов - это не ничья
            if (candidates[i].votes != min)
            {
                return false;
            }
        }
    }

    // Если дошли сюда и есть активные кандидаты - значит ничья
    return active_candidates_exist;
}

// Исключите кандидата (или кандидатов), занявшего последнее место
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}
