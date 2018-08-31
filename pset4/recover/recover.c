#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // handle args, return error if no filename is given
    if (argc < 2) {
        fprintf(stderr, "0 Arguments supplied, expected 1\n\tUsage: recover <filename>\n");
        return 1;
    }

    //open card file
    FILE *rawfile;
    rawfile = fopen(argv[1], "r");

    // create pointer for saving jpegs
    FILE *jpegfile;

    if (rawfile == NULL)
    {
        fprintf(stderr, "File %s does not exist or could not be opened.\n", argv[1]);
        return 2;
    }

    //read 512 bytes into buffer
    BYTE *buf;
    buf = malloc(512 * sizeof(BYTE));

    // keep count of the file we've processed to set the output file name
    int filecount = 0;
    char outfile_name[9] = "000.jpg";
    jpegfile = fopen(outfile_name, "w+");

    // repeat until end of card
    // using 512 block reads (FAT formatting)
    while(fread(buf, 1, 512, rawfile) == 512)
    {
        //check for start of new jpeg
        if (
                buf[0] == 0xff &&
                buf[1] == 0xd8 &&
                buf[2] == 0xff &&
                (buf[3] & 0xf0) == 0xe0
            )
            {
                fclose(jpegfile);
                // set the filename by increments of the file count
                sprintf(outfile_name, "%03i.jpg", filecount++);
                jpegfile = fopen(outfile_name, "w+");
            }
        fwrite(buf, 1, 512, jpegfile);
    }

    //close any remaining files
    fclose(rawfile);
    fclose(jpegfile);
    return 0;
};