#include <stdio.h>
#include "../../lib/cs50.h"

/* 
Recreate the mario block pyramids using text. First prompt the user
for the size of the pyramid and then print it out to the console.
(https://cs50.harvard.edu/x/2022/psets/1/mario/more/)
*/

int main(void)
{
    int height;

    // Prompt the user for the Height, if is is not between 1 and 8 (inclusive) prompt again
    do
    {
        // Get the user input for height
        height = get_int("Height : ");
    }
    while (height < 1 || height > 8);

    // Loop over each vertical row
    for (int i = 0; i < height; i++)
    {
        // Print the spaces at the beggining of each row
        for (int j = 0; j < height - 1 - i; j++)
        {
            printf(" ");
        }
        // Print the blocks on the left
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        // Print the spaces in the middle
        printf("  ");
        // Print the blocks on the right
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        // Print a new line so the next row appear below
        printf("\n");
    }
}
