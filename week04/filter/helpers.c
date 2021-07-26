#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int32_t height, int32_t width, RGBTRIPLE image[height][width])
{
    for (int32_t h = 0; h < height; h++)
    {
        for (int32_t w = 0; w < width; w++)
        {
            float average = (
                image[h][w].rgbtBlue +
                image[h][w].rgbtGreen +
                image[h][w].rgbtRed
            ) / 3;
            image[h][w].rgbtBlue = (uint8_t) average;
            image[h][w].rgbtGreen = (uint8_t) average;
            image[h][w].rgbtRed = (uint8_t) average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int32_t height, int32_t width, RGBTRIPLE image[height][width])
{
    uint8_t originalBlue;
    uint8_t originalGreen;
    uint8_t originalRed;

    int32_t sepiaBlue;
    int32_t sepiaGreen;
    int32_t sepiaRed;
    for (int32_t h = 0; h < height; h++)
    {
        for (int32_t w = 0; w < width; w++)
        {
            originalBlue = image[h][w].rgbtBlue;
            originalGreen = image[h][w].rgbtGreen;
            originalRed = image[h][w].rgbtRed;

            sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            sepiaRed = sepiaRed > 255 ? 255 : sepiaRed;

            sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            sepiaGreen = sepiaGreen > 255 ? 255 : sepiaGreen;

            sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            sepiaBlue = sepiaBlue > 255 ? 255 : sepiaBlue;

            image[h][w].rgbtBlue = (uint8_t) sepiaBlue;
            image[h][w].rgbtGreen = (uint8_t) sepiaGreen;
            image[h][w].rgbtRed = (uint8_t) sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int32_t height, int32_t width, RGBTRIPLE image[height][width])
{
    int32_t left;
    int32_t right;
    RGBTRIPLE temp;
    for(int32_t h = 0; h < height; h++)
    {
        left = 0;
        right = width - 1;
        while(left < right)
        {
            temp = image[h][left];
            image[h][left] = image[h][right];
            image[h][right] = temp;
            left++;
            right--;
        }
    }
    return;
}

typedef struct
{
    RGBTRIPLE color;
    bool isValid;
} __attribute__((__packed__))
ADJACENT;

// Blur image
void blur(int32_t height, int32_t width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*og_image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (og_image == NULL)
    {
        fprintf(stderr, "Not enough memory to store image copy.\n");
        return;
    }
    memcpy(og_image, image, height * width * sizeof(RGBTRIPLE));

    int32_t adjIndex = 0;
    ADJACENT adj[9];
    for (int32_t h = 0; h < height; h++)
    {
        for (int32_t w = 0; w < width; w++)
        {
            int32_t min_height = h - 1;
            int32_t max_height = h + 1;
            int32_t min_width = w - 1;
            int32_t max_width = w + 1;

            // Traverse the adjecent pixels and only gather the ones within the image bounds.
            adjIndex = 0;
            for (int32_t h2 = min_height; h2 <= max_height; h2++)
            {
                for (int32_t w2 = min_width; w2 <= max_width; w2++)
                {
                    // If the pixel is outside the image bounds...
                    if (h2 < 0 || w2 < 0 || h2 > height - 1 || w2 > width - 1)
                    {
                        adj[adjIndex].isValid = false;
                    }
                    else
                    {
                        adj[adjIndex].color = og_image[h2][w2];
                        adj[adjIndex].isValid = true;
                    }
                    adjIndex++;
                }
            }

            int32_t adjCount = 0;
            uint32_t blue = 0;
            uint32_t green = 0;
            uint32_t red = 0;
            for (int32_t i = 0; i < 9; i++)
            {
                if (adj[i].isValid)
                {
                    blue += adj[i].color.rgbtBlue;
                    green += adj[i].color.rgbtGreen;
                    red += adj[i].color.rgbtRed;
                    adjCount++;
                }
            }

            image[h][w].rgbtBlue = (uint8_t) round(blue /(float) adjCount);
            image[h][w].rgbtGreen = (uint8_t) round(green /(float) adjCount);
            image[h][w].rgbtRed = (uint8_t) round(red /(float) adjCount);
        }
    }

    free(og_image);
    return;
}
