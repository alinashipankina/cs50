#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int HEADER_SIZE = 512;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    uint8_t buffer[HEADER_SIZE];
    FILE *img = NULL;
    char filename[8];
    int i = 0;

    while (fread(buffer, sizeof(uint8_t), 512, card) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] >= 0xe0 && buffer[3] <= 0xef))
        {
            if (img != NULL)
            {
                fclose(img);
            }

            sprintf(filename, "%03i.jpg", i);
            i++;

            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Could not create image file.\n");
                return 1;
            }
        }

        if (img != 0)
        {
            fwrite(buffer, sizeof(uint8_t), 512, img);
        }
    }

    if (img != NULL)
    {
        fclose(img);
    }

    fclose(card);
}
