#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    char *infile = argv[1];

    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s\n", infile);
        return 1;
    }

    int number = 0;
    char filename[8];
    unsigned char filebuffer[512];
    FILE *outptr = NULL;

    while (fread(filebuffer, 512, 1, inptr) == 1)
    {
        if (filebuffer[0] == 0xff && filebuffer[1] == 0xd8 && filebuffer[2] == 0xff && (filebuffer[3] & 0xf0) == 0xe0)
        {
            if (number > 0)
                fclose(outptr);

            sprintf(filename, "%03d.jpg", number);
            outptr = fopen(filename, "w");
            number++;
        }

        if (outptr != NULL)
            fwrite(filebuffer, 512, 1, outptr);
    }
    fclose(inptr);
    fclose(outptr);
}