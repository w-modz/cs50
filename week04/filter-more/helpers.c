#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

#define ERR_OUT_OF_MEMORY -1

RGBTRIPLE** copy_image(int height, int width, RGBTRIPLE image[height][width]);

const int GxKernel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
const int GyKernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

typedef struct
{
    float red;
    float green;
    float blue;
} vertical;
typedef struct
{
    float red;
    float green;
    float blue;
} horizontal;

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE **ogImage = copy_image(height, width, image);

    RGBTRIPLE adj[9];
    for (int32_t h = 0; h < height; h++)
    {
        for (int32_t w = 0; w < width; w++)
        {
            int32_t min_height = h - 1;
            int32_t max_height = h + 1;
            int32_t min_width = w - 1;
            int32_t max_width = w + 1;

            vertical Gx;
            horizontal Gy;
            Gx.red = 0;
            Gx.green = 0;
            Gx.blue = 0;
            Gy.red = 0;
            Gy.green = 0;
            Gy.blue = 0;

            // Traverse the 3x3 grid of adjacent pixels and calculate Gx and Gy
            int32_t adjIndex = 0;
            int32_t index1 = 0;
            int32_t index2 = 0;

            for (int32_t h2 = min_height; h2 <= max_height; h2++)
            {
                for (int32_t w2 = min_width; w2 <= max_width; w2++)
                {
                    // Set the pixel color to solid black if outside the image bounds
                    if (h2 < 0 || w2 < 0 || h2 > height - 1 || w2 > width - 1)
                    {
                        adj[adjIndex].rgbtBlue = 0;
                        adj[adjIndex].rgbtGreen = 0;
                        adj[adjIndex].rgbtRed = 0;
                    }
                    else
                    {
                        adj[adjIndex] = ogImage[h2][w2];
                    }

                    Gx.red += (int32_t)adj[adjIndex].rgbtRed * GxKernel[index2][index1];
                    Gx.green += (int32_t)adj[adjIndex].rgbtGreen * GxKernel[index2][index1];
                    Gx.blue += (int32_t)adj[adjIndex].rgbtBlue * GxKernel[index2][index1];
                    Gy.red += (int32_t)adj[adjIndex].rgbtRed * GyKernel[index2][index1];
                    Gy.green += (int32_t)adj[adjIndex].rgbtGreen * GyKernel[index2][index1];
                    Gy.blue += (int32_t)adj[adjIndex].rgbtBlue * GyKernel[index2][index1];
                    adjIndex++;
                    if (index1 == 2)
                    {
                        index1 = 0;
                        index2++;
                    }
                    else
                    {
                        index1++;
                    }
                    // Calculate the final color values for the pixel
                    int32_t Red;
                    int32_t Green;
                    int32_t Blue;

                    Red = round(sqrt((Gx.red * Gx.red) + (Gy.red * Gy.red)));
                    Green = round(sqrt((Gx.green * Gx.green) + (Gy.green * Gy.green)));
                    Blue = round(sqrt((Gx.blue * Gx.blue) + (Gy.blue * Gy.blue)));

                    if (Red > 255)
                    {
                        Red = 255;
                    }
                    if (Green > 255)
                    {
                        Green = 255;
                    }
                    if (Blue > 255)
                    {
                        Blue = 255;
                    }

                    // Change the pixel on the image
                    image[h][w].rgbtBlue = Blue;
                    image[h][w].rgbtGreen = Green;
                    image[h][w].rgbtRed = Red;
                }
            }
        }
    }

    free(ogImage);
    return;
}

RGBTRIPLE **copy_image(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE **copy = NULL;
    if (!(copy = (RGBTRIPLE **)calloc(height, sizeof(RGBTRIPLE))))
    {
        fprintf(stderr, "Not enough memory to store image copy.\n");
        exit(ERR_OUT_OF_MEMORY);
    }

    for (uint32_t row = 0; row < width; row++)
    {
        if (!(copy[row] = (RGBTRIPLE *)calloc(width, sizeof(RGBTRIPLE))))
        {
            fprintf(stderr, "Not enough memory to store image copy.\n");
            free(copy);
            exit(ERR_OUT_OF_MEMORY);
        }
        memcpy(copy[row], image[row], width * sizeof(RGBTRIPLE));
    }

    return copy;
}
