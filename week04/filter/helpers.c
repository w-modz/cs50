#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int32_t height, int32_t width, RGBTRIPLE image[height][width])
{
    for (int32_t h = 0; h < height; h++)
    {
        for (int32_t w = 0; w < width; w++)
        {
            uint8_t average = (
                image[h][w].rgbtBlue +
                image[h][w].rgbtGreen +
                image[h][w].rgbtRed
            ) / 3;
            image[h][w].rgbtBlue = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtRed = average;
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
    bool validity;
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

    int32_t adj_count;

    ADJACENT adj[9];
    for (int32_t h = 0; h < height; h++)
    {
        for (int32_t w = 0; w < width; w++)
        {
            adj_count = 0;
            uint8_t RgbBlue = 0;
            uint8_t RgbGreen = 0;
            uint8_t RgbRed = 0;
            int32_t min_height = h - 1;
            int32_t max_height = h + 1;
            int32_t min_width = w - 1;
            int32_t max_width = w + 1;

            int32_t i = 0;
            for(int32_t h2 = min_height; h2 < max_height; h2++)
            {
                for(int32_t w2 = min_width; w2 < max_width; w2++)
                {
                    if(h2 < 0 || w2 < 0 || h2 > height - 1 || w2 > width - 1)
                    {
                        adj[i].validity = false;
                        i++;
                    }
                    else
                    {
                        adj[i].color = og_image[h2][w2];
                        adj[i].validity = true;
                        i++;
                    }
                }
            }
            for (int j = 0; j < 9; j++)
            {
                if (adj[j].validity == true)
                {
                    RgbBlue = RgbBlue + adj[j].color.rgbtBlue;
                    RgbGreen = RgbGreen + adj[j].color.rgbtGreen;
                    RgbRed = RgbRed + adj[j].color.rgbtRed;
                    adj_count++;
                }
            }
            image[h][w].rgbtBlue = round(RgbBlue / adj_count);
            image[h][w].rgbtGreen = round(RgbGreen / adj_count);
            image[h][w].rgbtRed = round(RgbRed / adj_count);
        }
    }
    free(og_image);
    return;
}
