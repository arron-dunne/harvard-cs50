#include "helpers.h"
#include "math.h"

/*
Implementation of the 4 filters used in "filter.c"

(https://cs50.harvard.edu/x/2022/psets/4/filter/more/)
*/

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary variable to hold new immage
    RGBTRIPLE temp[height][width];

    // Loop over each row
    for (int i = 0; i < height; i++)
    {
        // Loop over each pixel
        for (int j = 0; j < width; j++)
        {
            // Calculate average colour value
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            // Set BGR to average colour
            temp[i][j].rgbtBlue = average;
            temp[i][j].rgbtGreen = average;
            temp[i][j].rgbtRed = average;
        }
    }

    // Set image to the grey image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary variable to hold new immage
    RGBTRIPLE temp[height][width];

    // Loop over each row
    for (int i = 0; i < height; i++)
    {
        // Create a buffer row for reflected pixels
        // RGBTRIPLE buffer[width];

        // Loop over each pixel
        for (int j = 0; j < width; j++)
        {
            // Place pixel at opposite end in new image
            temp[i][width - 1 - j] = image[i][j];
        }
    }

    // Set image to the reflected image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary variable to hold new immage
    RGBTRIPLE temp[height][width];

    // Loop over each row
    for (int i = 0; i < height; i++)
    {
        // Loop over each pixel
        for (int j = 0; j < width; j++)
        {
            // Variables used to calculate averages
            float red = 0;
            float green = 0;
            float blue = 0;
            int count = 0;

            // Loop over adjacent rows
            for (int k = -1; k < 2; k++)
            {
                // Loop over adjacent pixels
                for (int l = -1; l < 2; l++)
                {
                    // Check pixel is in valid range
                    if (i + k < 0 || i + k > height - 1
                        || j + l < 0 || j + l > width - 1)
                    {
                        continue;
                    }

                    // Update colour sum count
                    red += image[i + k][j + l].rgbtRed;
                    green += image[i + k][j + l].rgbtGreen;
                    blue += image[i + k][j + l].rgbtBlue;

                    // Update quantity count
                    count++;
                }
            }

            // Set image pixel to blurred value
            temp[i][j].rgbtRed = round(red / count);
            temp[i][j].rgbtGreen = round(green / count);
            temp[i][j].rgbtBlue = round(blue / count);
        }
    }

    // Set image to the blurred image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary variable to hold new immage
    RGBTRIPLE temp[height][width];

    // Gx matrix
    int GxGrid[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int GyGrid[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Loop over each row
    for (int i = 0; i < height; i++)
    {
        // Loop over each pixel
        for (int j = 0; j < width; j++)
        {
            // Initialise variables for R G B values
            float Gx[] = {0, 0, 0};
            float Gy[] = {0, 0, 0};

            float red = 0;
            float green = 0;
            float blue = 0;

            // Loop over adjacent rows
            for (int k = -1; k < 2; k++)
            {
                // Loop over adjacent pixels
                for (int l = -1; l < 2; l++)
                {
                    // Check pixel is in valid range
                    if (i + k < 0 || i + k > height - 1
                        || j + l < 0 || j + l > width - 1)
                    {
                        continue;
                    }

                    Gx[0] += image[i + k][j + l].rgbtRed * GxGrid[k + 1][l + 1];
                    Gx[1] += image[i + k][j + l].rgbtGreen * GxGrid[k + 1][l + 1];
                    Gx[2] += image[i + k][j + l].rgbtBlue * GxGrid[k + 1][l + 1];

                    Gy[0] += image[i + k][j + l].rgbtRed * GyGrid[k + 1][l + 1];
                    Gy[1] += image[i + k][j + l].rgbtGreen * GyGrid[k + 1][l + 1];
                    Gy[2] += image[i + k][j + l].rgbtBlue * GyGrid[k + 1][l + 1];
                }
            }

            red = round(sqrt(pow(Gx[0], 2) + pow(Gy[0], 2)));
            green = round(sqrt(pow(Gx[1], 2) + pow(Gy[1], 2)));
            blue = round(sqrt(pow(Gx[2], 2) + pow(Gy[2], 2)));

            // Cap values to 255
            if (red >= 255)
            {
                red = 255;
            }
            if (green >= 255)
            {
                green = 255;
            }
            if (blue >= 255)
            {
                blue = 255;
            }

            // Update pixel
            temp[i][j].rgbtRed = red;
            temp[i][j].rgbtGreen = green;
            temp[i][j].rgbtBlue = blue;
        }
    }

    // Set image to the edges image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}
