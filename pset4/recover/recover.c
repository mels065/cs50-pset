#include <stdio.h>
#include <stdint.h>

#include <cs50.h>

bool isJpegHeader(uint8_t *buffer);

#define NUM_OF_BYTES 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Must take 1 argument\n");
        return 1;
    }

    FILE *inptr = fopen(argv[1], "r");

    if (inptr == NULL)
    {
        printf("Could not open file %s\n", argv[1]);
        return 2;
    }

    uint8_t *buffer = malloc(sizeof(uint8_t) * NUM_OF_BYTES);
    bool currentlySearching = false;
    int fileNumber = 0;
    char *outfile = malloc(sizeof(uint8_t) * NUM_OF_BYTES * 7);
    FILE *outptr;
    size_t byteCount = fread(buffer, 1, NUM_OF_BYTES, inptr);


    while (byteCount == NUM_OF_BYTES)
    {
        if (isJpegHeader(buffer))
        {
            if (!currentlySearching)
            {
                currentlySearching = true;
            }
            else {
                fclose(outptr);
            }
            sprintf(outfile, "%03i.jpg", fileNumber);
            outptr = fopen(outfile, "w");
            if (outptr == NULL)
            {
                printf("Cannot write to file %s\n", outfile);
                return 3;
            }
            fileNumber++;
        }
        if (currentlySearching)
        {
            fwrite(buffer, NUM_OF_BYTES, 1, outptr);
        }

        byteCount = fread(buffer, 1, NUM_OF_BYTES, inptr);
    }

    free(outfile);
    free(buffer);
    fclose(outptr);
    fclose(inptr);
}

bool isJpegHeader(uint8_t *buffer)
{
    return (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0);
}
