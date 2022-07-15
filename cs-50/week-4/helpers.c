#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int cap(int num);
double squareOf(double num);
int magnitudeOf(double x, double y);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate through each RGBTRIPLE of image for height for width
    // for each RGBTRIPLE, average them ex: x345
    // set RGBTRIPLE to be average x444
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalBlue = image[i][j].rgbtBlue;
            int originalGreen = image[i][j].rgbtGreen;
            int originalRed = image[i][j].rgbtRed;

            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);

            // Assign values at end
            image[i][j].rgbtBlue = cap(sepiaBlue);
            image[i][j].rgbtGreen = cap(sepiaGreen);
            image[i][j].rgbtRed = cap(sepiaRed);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int halfWidth = floor(width / 2);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < halfWidth; j++)
        {
            // Swap with width - 1 - j
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int iOffset[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
            int jOffset[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

            float sumBlue = 0.0;
            float sumGreen = 0.0;
            float sumRed = 0.0;
            int neighbors = 0;

            for (int k = 0; k < 9; k++)
            {
                // If pixel exists
                if (i + iOffset[k] > 0 && i + iOffset[k] < height - iOffset[k] && j + jOffset[k] > 0 && j + jOffset[k] < width - iOffset[k])
                {
                    RGBTRIPLE thisColor = image[i + iOffset[k]][j + jOffset[k]];

                    sumBlue = sumBlue + thisColor.rgbtBlue;
                    sumGreen = sumGreen + thisColor.rgbtGreen;
                    sumRed = sumRed + thisColor.rgbtRed;
                    neighbors++;
                }
            }
            image[i][j].rgbtBlue = (int)round(sumBlue / neighbors);
            image[i][j].rgbtGreen = (int)round(sumGreen / neighbors);
            image[i][j].rgbtRed = (int)round(sumRed / neighbors);
        }
    }
    return;
}

int cap(int num)
{
    return (num < 255) ? num : 255;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // RGBTRIPLE imageCopy[height][width];

    // Allocate memory for image
    RGBTRIPLE(*imageCopy)
    [width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (imageCopy == NULL)
    {
        printf("Not enough memory to store image copy.\n");
        return;
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int iOffset[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
            int jOffset[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

            int xWeight[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
            int yWeight[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

            double sumBlue_X = 0.0;
            double sumGreen_X = 0.0;
            double sumRed_X = 0.0;

            double sumBlue_Y = 0.0;
            double sumGreen_Y = 0.0;
            double sumRed_Y = 0.0;

            imageCopy[i][j] = image[i][j];

            for (int k = 0; k < 9; k++)
            {
                // If pixel exists
                if (i + iOffset[k] > 0 && i + iOffset[k] < height - iOffset[k] && j + jOffset[k] > 0 && j + jOffset[k] < width - iOffset[k])
                {
                    // RGBTRIPLE thisColor = image[i + iOffset[k]][j + jOffset[k]];
                    double thisBlue = (double)imageCopy[i + iOffset[k]][j + jOffset[k]].rgbtBlue;
                    double thisGreen = (double)imageCopy[i + iOffset[k]][j + jOffset[k]].rgbtGreen;
                    double thisRed = (double)imageCopy[i + iOffset[k]][j + jOffset[k]].rgbtRed;

                    sumBlue_X = sumBlue_X + (thisBlue * xWeight[k]);
                    sumGreen_X = sumGreen_X + (thisGreen * xWeight[k]);
                    sumRed_X = sumRed_X + (thisRed * xWeight[k]);

                    sumBlue_Y = sumBlue_Y + (thisBlue * yWeight[k]);
                    sumGreen_Y = sumGreen_Y + (thisGreen * yWeight[k]);
                    sumRed_Y = sumRed_Y + (thisRed * yWeight[k]);
                }
            }
            image[i][j].rgbtBlue = magnitudeOf(sumBlue_X, sumBlue_Y);
            image[i][j].rgbtGreen = magnitudeOf(sumGreen_X, sumGreen_Y);
            image[i][j].rgbtRed = magnitudeOf(sumRed_X, sumRed_Y);
            // For checking just the Y or X values
            // image[i][j].rgbtBlue = cap((int)round(sumBlue_Y));
            // image[i][j].rgbtGreen = cap((int)round(sumGreen_Y));
            // image[i][j].rgbtRed = cap((int)round(sumRed_Y));
        }
    }
    // Free memory for image
    free(imageCopy);

    return;
}

double squareOf(double num)
{
    return pow(num, 2);
}

int magnitudeOf(double x, double y)
{
    return cap((int)round(sqrt(squareOf(x) + squareOf(y))));
}