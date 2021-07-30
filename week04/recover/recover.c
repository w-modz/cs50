#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCK_LENGTH 512

typedef uint8_t BYTE;

int8_t *get_filename(int32_t *imageCount);

int32_t main(int32_t argc, int8_t *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover <file_path>\n");
        return 1;
    }

    int8_t *filename = argv[1];
    FILE *inptr = fopen(filename, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", filename);
        return 1;
    }

    BYTE *buffer = calloc(BLOCK_LENGTH, sizeof(BYTE));
    if (buffer == NULL)
    {
        fprintf(stderr, "Not enough memory to store image copy.\n");
        return 2;
    }

    FILE *currentImg = NULL;
    int32_t imageCount = 1;
    while (fread(buffer, sizeof(BYTE), BLOCK_LENGTH, inptr))
    {
        // If we find a new JPG image...
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (currentImg)
            {
                fclose(currentImg);
                imageCount++;
            }

            int8_t *imageName = get_filename(&imageCount);
            currentImg = fopen(imageName, "w");
            if (!currentImg)
            {
                fprintf(stderr, "Could not create a new image copy. [imageName=%s]\n", imageName);
                free(buffer);
                fclose(inptr);
                return 3;
            }
            fwrite(buffer, sizeof(BYTE), BLOCK_LENGTH, currentImg);
        }
        else if (currentImg)
        {
            // We're still processing the given image.
            fwrite(buffer, sizeof(BYTE), BLOCK_LENGTH, currentImg);
        }
        else
        {
            // No image found yet, skip the block.
            fseek(inptr, BLOCK_LENGTH, SEEK_CUR);
        }
    }

    if (currentImg)
    {
        fclose(currentImg);
    }
    free(buffer);
    fclose(inptr);
}

int8_t *get_filename(int32_t *fileCount)
{
    static int8_t fileName[8] = "000.jpg";
    fileName[0] = *fileCount / 100 + 48;
    fileName[1] = *fileCount / 10 % 10 + 48;
    fileName[2] = *fileCount % 10 + 48;
    return fileName;
}
