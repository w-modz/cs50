#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCK_LENGTH 512

typedef uint8_t BYTE;

bool is_jpg_start(BYTE *buffer);
FILE *supersede_file(FILE *file, int32_t *fileCount);
char *get_filename(int32_t *imageCount);

int32_t main(int32_t argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover <file_path>\n");
        return 1;
    }

    char *filename = argv[1];
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
        if (is_jpg_start(buffer))
        {
            if (!(currentImg = supersede_file(currentImg, &imageCount)))
            {
                fprintf(stderr, "Could not create a new image copy. [imageCount=%i]\n", imageCount);
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

bool is_jpg_start(BYTE *buffer)
{
    return buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;
}

FILE *supersede_file(FILE *file, int32_t *fileCount)
{
    if (file)
    {
        fclose(file);
        (*fileCount)++;
    }

    char *fileName = get_filename(fileCount);
    return fopen(fileName, "w");
}

char *get_filename(int32_t *fileCount)
{
    static char fileName[8] = "000.jpg";
    fileName[0] = *fileCount / 100 + 48;
    fileName[1] = *fileCount / 10 % 10 + 48;
    fileName[2] = *fileCount % 10 + 48;
    return fileName;
}
