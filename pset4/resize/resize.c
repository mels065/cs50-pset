/**
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>

#include <cs50.h>

#include "bmp.h"

#define SCALE_MIN 0
#define SCALE_MAX 100

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./copy infile outfile\n");
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= SCALE_MIN || n > SCALE_MAX)
    {
        fprintf(stderr, "Float must be in range %i to %i", SCALE_MIN, SCALE_MAX);
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    LONG startingWidth = bi.biWidth;
    LONG startingHeight = bi.biHeight;
    bi.biWidth *= n;
    bi.biHeight *= n;

    // determine padding for scanlines
    int startingPadding = (4 - (startingWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(startingHeight); i < biHeight; i++)
    {
        RGBTRIPLE *row = malloc(sizeof(RGBTRIPLE) * bi.biWidth);
        int rowPixel = 0;
        // iterate over pixels in scanline
        for (int j = 0; j < startingWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            for (int k = 0; k < n; k++)
            {
                row[rowPixel] = triple;
                eprintf("%i %i %i\n", row[rowPixel].rgbtRed, row[rowPixel].rgbtGreen, row[rowPixel].rgbtBlue);
                rowPixel++;
            }
        }

        fseek(inptr, startingPadding, SEEK_CUR);
        // skip over padding, if any
        for (int j = 0; j < n; j++)
        {
            fwrite(row, sizeof(RGBTRIPLE), bi.biWidth, outptr);

            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
        }

        free(row);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
