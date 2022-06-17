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
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

int cap(int num)
{
    return (num < 255) ? num : 255;
}
