#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string answer = get_string("Как тебя зовут? ");
    printf("Привет, %s\n", answer);
}
