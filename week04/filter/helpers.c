#include <math.h>

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

// Blur image
void blur(int32_t height, int32_t width, RGBTRIPLE image[height][width])
{
    return;
}
