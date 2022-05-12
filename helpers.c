#include <stdio.h>
#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int k = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtBlue = k;
            image[i][j].rgbtGreen = k;
            image[i][j].rgbtRed = k;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    printf("sepia successful\n");

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalBlue = image[i][j].rgbtBlue;
            int originalGreen = image[i][j].rgbtGreen;
            int originalRed = image[i][j].rgbtRed;

            int R = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);

            if ( R > 255)
            {
                 image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = R;
            }

            int G = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);

            if ( G > 255)
            {
                 image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = G;
            }

            int B = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            if ( B > 255)
            {
                 image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = B;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            RGBTRIPLE swap = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = swap;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }
    }

    float RedBlur;
    float BlueBlur;
    float GreenBlur;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((j == 0) && (i == 0)) // top left 4
            {
                RedBlur = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 4.0);

                BlueBlur = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 4.0);

                GreenBlur = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 4.0);

                image[i][j].rgbtRed = RedBlur;
                image[i][j].rgbtBlue = BlueBlur;
                image[i][j].rgbtGreen = GreenBlur;
            }
            else if (j == (width - 1) && i == 0) // top right 4
            {
                RedBlur = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][ j + 1].rgbtRed + copy[i + 1][j].rgbtRed) / 4.0);

                BlueBlur = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][ j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue) / 4.0);

                GreenBlur = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][ j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen) / 4.0);

                image[i][j].rgbtRed = RedBlur;
                image[i][j].rgbtBlue = BlueBlur;
                image[i][j].rgbtGreen = GreenBlur;
            }

            else if (j == 0 && i == (height - 1)) //lower left 4
            {
                RedBlur = round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j + 1].rgbtRed) / 4.0);

                BlueBlur = round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue) / 4.0);

                GreenBlur = round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) / 4.0);

                image[i][j].rgbtRed = RedBlur;
                image[i][j].rgbtBlue = BlueBlur;
                image[i][j].rgbtGreen = GreenBlur;
            }

            else if (j == (width - 1) && (i == height - 1)) // lower right 4
            {
                RedBlur = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed) / 4.0);

                BlueBlur = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue) / 4.0);

                GreenBlur = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen) / 4.0);

                image[i][j].rgbtRed = RedBlur;
                image[i][j].rgbtBlue = BlueBlur;
                image[i][j].rgbtGreen = GreenBlur;
            }

            else if (j == 0 && (i > 0 && i < (height - 1))) // left edge 6
            {
                RedBlur = round((copy[i][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed) / 6.0);

                BlueBlur = round((copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) / 6.0);

                GreenBlur = round((copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) / 6.0);

                image[i][j].rgbtRed = RedBlur;
                image[i][j].rgbtBlue = BlueBlur;
                image[i][j].rgbtGreen = GreenBlur;
            }

            else if (j == (width - 1) && (i > 0 && i < (height - 1))) // right edge 6
            {
                RedBlur = round((copy[i - 1][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed) / 6.0);

                BlueBlur = round((copy[i - 1][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue) / 6.0);

                GreenBlur = round((copy[i - 1][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen) / 6.0);

                image[i][j].rgbtRed = RedBlur;
                image[i][j].rgbtBlue = BlueBlur;
                image[i][j].rgbtGreen = GreenBlur;
            }

            else if ((j > 0 && j < (width - 1)) && i == 0) // upper edge 6
            {
                RedBlur = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed) / 6.0);

                BlueBlur = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue) / 6.0);

                GreenBlur = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen) / 6.0);

                image[i][j].rgbtRed = RedBlur;
                image[i][j].rgbtBlue = BlueBlur;
                image[i][j].rgbtGreen = GreenBlur;
            }

            else if ((j > 0 && j < (width - 1)) && i == (height - 1)) // bottom edge 6
            {
                RedBlur = round((copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed) / 6.0);

                BlueBlur = round((copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue) / 6.0);

                GreenBlur = round((copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) / 6.0);

                image[i][j].rgbtRed = RedBlur;
                image[i][j].rgbtBlue = BlueBlur;
                image[i][j].rgbtGreen = GreenBlur;
            }

            else
            {
                RedBlur = round((copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed) / 9.0);

                BlueBlur = round((copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue) / 9.0);

                GreenBlur = round((copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) / 9.0);

                image[i][j].rgbtRed = RedBlur;
                image[i][j].rgbtBlue = BlueBlur;
                image[i][j].rgbtGreen = GreenBlur;
            }
        }
    }
    return;
}
