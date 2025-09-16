#include <stdio.h>
#include <cs50.h>

int get_positive_int(void);
void meow(int n);

int main(void)
{
    int n = get_positive_int();
    meow(n);
}

int get_positive_int(void)
{
    int n;
    do
    {
        n = get_int("Число: ");
    }
    while (n < 1);
    return n;
}

void meow(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("meow\n");
    }
}
