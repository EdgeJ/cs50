// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize <int> infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // store the percent we want to change
    int percent_change = atoi(argv[1]);

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

    // copy header information to a new header
    BITMAPFILEHEADER newbf = bf;
    BITMAPINFOHEADER newbi = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // reset HEADER information

    // height and width grow by a multiple of our integer argument
    newbi.biWidth *= percent_change;
    newbi.biHeight *= percent_change;

    // bfSize grows by a multiple of our arg * 2 to account for 2 dimensions
    // also must take into account removing and then re-adding bfOffBits
    newbf.bfSize = (bf.bfSize - bf.bfOffBits) * (percent_change * 2) + bf.bfOffBits;

    fprintf(stderr, "Original bfsize: %i\n", bf.bfSize);
    fprintf(stderr, "New bfsize: %i\n", newbf.bfSize);
    fprintf(stderr, "Original bisize: %i\n", bi.biSize);
    fprintf(stderr, "New bisize: %i\n", newbi.biSize);
    fprintf(stderr, "Original biwidth: %i\n", bi.biWidth);
    fprintf(stderr, "New biwidth: %i\n", newbi.biWidth);
    fprintf(stderr, "Original biheight: %i\n", bi.biHeight);
    fprintf(stderr, "New biheight: %i\n", newbi.biHeight);

    // write outfile's BITMAPFILEHEADER
    fwrite(&newbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&newbi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    int newpadding = (4 - (newbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // copy the data percent_change times per scanline
        for (int z = percent_change; z > 0; z--)
        {
            // keep track of how many bytes we read from infile
            int bytes_read = 0;

            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                bytes_read += sizeof(RGBTRIPLE);

                // write RGB triple to outfile percent_change times
                for (int rgb = percent_change; rgb > 0; rgb--)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < newpadding; k++)
            {
                fputc(0x00, outptr);
            }

            // seek back to the starting point in our infile to copy the data again
            if (z > 1)
            {
                fseek(inptr, -padding, SEEK_CUR);
                fseek(inptr, -bytes_read, SEEK_CUR);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
