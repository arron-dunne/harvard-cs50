#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
Scan a forensic disk image and recover JPEG images, saving them locally.

(https://cs50.harvard.edu/x/2022/psets/4/recover/)
*/

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check correct usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open file
    FILE *file = fopen(argv[1], "r");

    // Check file was opened
    if (file == NULL)
    {
        printf("Cannot open file: %s\n", argv[0]);
        return 1;
    }

    int BLOCK_SIZE = 512;
    BYTE buffer[BLOCK_SIZE];
    char *filename = malloc(8);
    FILE *img;
    int writing = 0;

    int count = 0;

    // Loop over and read every block
    while (fread(&buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // Check if start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close currently open file
            if (count != 0)
            {
                fclose(img);

            }

            // Create new file
            sprintf(filename, "%03i.jpg", count);

            // Open new file
            img = fopen(filename, "w");

            // Increment count
            count++;

            writing = 1;

        }

        // Write block to file
        if (writing)
        {
            fwrite(buffer, 1, BLOCK_SIZE, img);
        }
    }

    // Close files
    fclose(file);
    fclose(img);

    // Free memory
    free(filename);

}