#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*
Modify the volume of an audio file. Take as arguments; an input audio file,
an output file name, and a magnitude. Change the volume of the audio file
by the magnitude and save it to the output file. For example:
`./volume sample.wav out.wav 3.0` increases the sample volume by a factor of 3.

(https://cs50.harvard.edu/x/2022/labs/4/)
*/

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Array to hold the header bytes
    uint8_t header[HEADER_SIZE];

    // Read the header
    fread(header, sizeof(uint8_t), HEADER_SIZE, input);

    // Copy header from input file to output file
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);

    // Buffer to store each sample
    int16_t buffer;

    // Read samples from input file
    while (fread(&buffer, sizeof(int16_t), 1, input) == 1)
    {
        // Mutiply sample by volume factor
        buffer = buffer * factor;

        // Write updated data to output file
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
