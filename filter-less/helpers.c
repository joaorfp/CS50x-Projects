#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loops to "read" the whole picture
    for (int index = 0; index < height; index++)
    {
        for (int j = 0; j < width; j++)
        {
            //turns the pic into gray
            int rgbtGray = round((image[index][j].rgbtBlue + image[index][j].rgbtGreen + image[index][j].rgbtRed) / 3.0);
            image[index][j].rgbtBlue = image[index][j].rgbtGreen = image[index][j].rgbtRed = rgbtGray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // loops to "read" the whole picture
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // changing the aspect of the picture
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);

            // ternary operator for checking how much is the scale of colour
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // loops to "read" the height of the picture
    for (int i = 0; i < height; i++)
    {
        // chechinkg if the width is pair
        if (width % 2 == 0)
        {
            // goes thru the width
            for (int j = 0; j < width / 2; j++)
            {
                // reflects the image
                RGBTRIPLE temp[height][width];
                temp[i][j] = image[i][j];
                image[i][j] = image[i][width - (j + 1)];
                image[i][width - (j + 1)] = temp[i][j];
            }
        }

        else if (width % 2 != 0)
        {
            // if width is odd, the loop "correct" it
            for (int j = 0; j < (width - 1) / 2; j++)
            {
                // reflects the image
                RGBTRIPLE temp[height][width];
                temp[i][j] = image[i][j];
                image[i][j] = image[i][width - (j + 1)];
                image[i][width - (j + 1)] = temp[i][j];
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // temporary variable
    RGBTRIPLE temp[height][width];

    // loops to "read" the whole picture
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sumBlue = 0;
            float sumGreen = 0;
            float sumRed = 0;
            float counter = 0;

            for (int r = -1; r < 2; r++)
            {
                for (int c = -1; c < 2; c++)
                {
                    // checks if the indexes are correct
                    if (i + r < 0 || i + r > height - 1)
                    {
                        continue;
                    }
                    // checks if the indexes are correct

                    if (j + c < 0 || j + c > width - 1)
                    {
                        continue;
                    }
                    // sum the value of the rgb passing thru height and width of the image
                    sumBlue += image[i + r][j + c].rgbtBlue;
                    sumGreen += image[i + r][j + c].rgbtGreen;
                    sumRed += image[i + r][j + c].rgbtRed;
                    counter++;
                }
            }
            temp[i][j].rgbtBlue = round(sumBlue / counter);
            temp[i][j].rgbtGreen = round(sumGreen / counter);
            temp[i][j].rgbtRed = round(sumRed / counter);
        }
    }

    // loops to "read" the whole picture
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // assing the value of the image param to the temp variable
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }

    }

    return;
}