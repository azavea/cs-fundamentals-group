#include "helpers.h"
#include <stdio.h>
#include <math.h>

int cap(int num);

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
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int iOffset[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
            int jOffset[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
            int xWeight[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
            int yWeight[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

            float sumBlue_X = 0.0;
            float sumGreen_X = 0.0;
            float sumRed_X = 0.0;
            
            float sumBlue_Y = 0.0;
            float sumGreen_Y = 0.0;
            float sumRed_Y = 0.0;

            for (int k = 0; k < 9; k++)
            {
                // If pixel exists
                if (i + iOffset[k] > 0 && i + iOffset[k] < height - iOffset[k] && j + jOffset[k] > 0 && j + jOffset[k] < width - iOffset[k])
                {
                    RGBTRIPLE thisColor = image[i + iOffset[k]][j + jOffset[k]];

                    sumBlue_X = sumBlue_X + (thisColor.rgbtBlue*xWeight[k]);
                    sumGreen_X = sumGreen_X + (thisColor.rgbtGreen*xWeight[k]);
                    sumRed_X = sumRed_X + (thisColor.rgbtRed*xWeight[k]);

                    sumBlue_Y = sumBlue_Y + (thisColor.rgbtBlue*yWeight[k]);
                    sumGreen_Y = sumGreen_Y + (thisColor.rgbtGreen*yWeight[k]);
                    sumRed_Y = sumRed_Y + (thisColor.rgbtRed*yWeight[k]);
                }
                else {
                    sumBlue_X = sumBlue_X + 0;
                    sumGreen_X = sumGreen_X + 0;
                    sumRed_X = sumRed_X + 0;

                    sumBlue_Y = sumBlue_Y + 0;
                    sumGreen_Y = sumGreen_Y + 0;
                    sumRed_Y = sumRed_Y + 0;
                }
            }
            image[i][j].rgbtBlue = cap((int)round(sqrt(pow(sumBlue_X, 2)+pow(sumBlue_Y, 2))));
            image[i][j].rgbtGreen = cap((int)round(sqrt(pow(sumGreen_X, 2)+pow(sumGreen_Y, 2))));
            image[i][j].rgbtRed = cap((int)round(sqrt(pow(sumRed_X, 2)+pow(sumRed_Y, 2))));
        }
    }
    return;
}
