#include "helpers.h"
#include "math.h"

int matrixGx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
int matrixGy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = image[i][j].rgbtBlue;
            average += image[i][j].rgbtGreen;
            average += image[i][j].rgbtRed;
            average = average / 3.0;
            image[i][j].rgbtBlue = round(average);
            image[i][j].rgbtRed = round(average);
            image[i][j].rgbtGreen = round(average);
        }
    }
    return;
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
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            float red = 0.0;
            float blue = 0.0;
            float green = 0.0;
            for (int k = i - 1; k < (i + 2); k++)
            {
                for (int l = j - 1; l < (j + 2); l++)
                {
                    if (k > -1 && k < height && l > -1 && l < width)
                    {
                        red += temp[k][l].rgbtRed;
                        blue += temp[k][l].rgbtBlue;
                        green += temp[k][l].rgbtGreen;
                        count++;
                    }
                }
            }
            image[i][j].rgbtRed = round(red / count);
            image[i][j].rgbtBlue = round(blue / count);
            image[i][j].rgbtGreen = round(green / count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redGx = 0;
            int blueGx = 0;
            int greenGx = 0;

            int redGy = 0;
            int blueGy = 0;
            int greenGy = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (k + i < 0 || k + i > height - 1)
                    {
                        continue;
                    }

                    if (l + j < 0 || l + j > width - 1)
                    {
                        continue;
                    }
                    redGx += temp[k + i][l + j].rgbtRed * matrixGx[k + 1][l + 1];
                    blueGx += temp[k + i][l + j].rgbtBlue * matrixGx[k + 1][l + 1];
                    greenGx += temp[k + i][l + j].rgbtGreen * matrixGx[k + 1][l + 1];

                    redGy += temp[k + i][l + j].rgbtRed * matrixGy[k + 1][l + 1];
                    blueGy += temp[k + i][l + j].rgbtBlue * matrixGy[k + 1][l + 1];
                    greenGy += temp[k + i][l + j].rgbtGreen * matrixGy[k + 1][l + 1];
                }
            }

            int newRed = round(sqrt(redGx * redGx + redGy * redGy));
            int newBlue = round(sqrt(blueGx * blueGx + blueGy * blueGy));
            int newGreen = round(sqrt(greenGx * greenGx + greenGy * greenGy));

            if (newRed > 255)
                newRed = 255;
            if (newBlue > 255)
                newBlue = 255;
            if (newGreen > 255)
                newGreen = 255;

            image[i][j].rgbtRed = newRed;
            image[i][j].rgbtBlue = newBlue;
            image[i][j].rgbtGreen = newGreen;
        }
    }
    return;
}