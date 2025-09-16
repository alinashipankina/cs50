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

            int grayscaleGray = round((grayscaleRed + grayscaleGreen + grayscaleBlue) / 3.0);

            image[i][j].rgbtRed = grayscaleGray;
            image[i][j].rgbtGreen = grayscaleGray;
            image[i][j].rgbtBlue = grayscaleGray;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(0.393 * (double)image[i][j].rgbtRed + 0.769 * (double)image[i][j].rgbtGreen + 0.189 * (double)image[i][j].rgbtBlue);
            int sepiaGreen = round(0.349 * (double)image[i][j].rgbtRed + 0.686 * (double)image[i][j].rgbtGreen + 0.168 * (double)image[i][j].rgbtBlue);
            int sepiaBlue = round(0.272 * (double)image[i][j].rgbtRed + 0.534 * (double)image[i][j].rgbtGreen + 0.131 * (double)image[i][j].rgbtBlue);

            if (sepiaRed > 255) sepiaRed = 255;
            if (sepiaGreen > 255) sepiaGreen = 255;
            if (sepiaBlue > 255) sepiaBlue = 255;

            if (sepiaRed < 0) sepiaRed = 0;
            if (sepiaGreen < 0) sepiaGreen = 0;
            if (sepiaBlue < 0) sepiaBlue = 0;

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
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
            int totalRed = 0, totalGreen = 0, totalBlue = 0;
            int count = 0;

            // Проверяем соседние пиксели (3x3 область)
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;  // Новая координата i
                    int nj = j + dj;  // Новая координата j

                    // Проверяем, что пиксель внутри изображения
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        totalRed += image[ni][nj].rgbtRed;
                        totalGreen += image[ni][nj].rgbtGreen;
                        totalBlue += image[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Вычисляем среднее значение и округляем
            copy[i][j].rgbtRed = round((float)totalRed / count);
            copy[i][j].rgbtGreen = round((float)totalGreen / count);
            copy[i][j].rgbtBlue = round((float)totalBlue / count);
        }
    }

    // Копируем результат обратно в image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
}
