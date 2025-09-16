#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int grayscaleRed = image[i][j].rgbtRed;
            int grayscaleGreen = image[i][j].rgbtGreen;
            int grayscaleBlue = image[i][j].rgbtBlue;

            int grayscaleGrey = round((grayscaleRed + grayscaleGreen + grayscaleBlue) / 3.0);

            image[i][j].rgbtRed = grayscaleGrey;
            image[i][j].rgbtGreen = grayscaleGrey;
            image[i][j].rgbtBlue = grayscaleGrey;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;

        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blurRed = 0;
            int blurGreen = 0;
            int blurBlue = 0;

            int count = 0;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        blurRed += image[ni][nj].rgbtRed;
                        blurGreen += image[ni][nj].rgbtGreen;
                        blurBlue += image[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            copy[i][j].rgbtRed = round((float)blurRed / count);
            copy[i][j].rgbtGreen = round((float)blurGreen / count);
            copy[i][j].rgbtBlue = round((float)blurBlue / count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Gx_Red = 0, Gx_Green = 0, Gx_Blue = 0;
            int Gy_Red = 0, Gy_Green = 0, Gy_Blue = 0;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        // Применяем ядра Gx и Gy
                        int weight_x = Gx[di + 1][dj + 1];
                        int weight_y = Gy[di + 1][dj + 1];

                        Gx_Red += image[ni][nj].rgbtRed * weight_x;
                        Gx_Green += image[ni][nj].rgbtGreen * weight_x;
                        Gx_Blue += image[ni][nj].rgbtBlue * weight_x;

                        Gy_Red += image[ni][nj].rgbtRed * weight_y;
                        Gy_Green += image[ni][nj].rgbtGreen * weight_y;
                        Gy_Blue += image[ni][nj].rgbtBlue * weight_y;
                    }
                }
            }

            // Вычисляем итоговый градиент
            int red = round(sqrt(Gx_Red * Gx_Red + Gy_Red * Gy_Red));
            int green = round(sqrt(Gx_Green * Gx_Green + Gy_Green * Gy_Green));
            int blue = round(sqrt(Gx_Blue * Gx_Blue + Gy_Blue * Gy_Blue));

            // Обрезаем до 255
            copy[i][j].rgbtRed = (red > 255) ? 255 : red;
            copy[i][j].rgbtGreen = (green > 255) ? 255 : green;
            copy[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
}
