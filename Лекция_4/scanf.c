#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *s = malloc(4);
    if (s == NULL)
    {
        return 1;
    }
    printf("s: ");
    scanf("%s", s);
    printf("s: %s\n", s);
    free(s);
    return 0;

    // int n;
    // printf("n: ");
    // scanf("%i", &n);
    // printf("n: %i\n", n);
}
