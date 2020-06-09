#include "helpers.h"
#include <math.h>
#include <stdbool.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
}

// Normalize value of the pixel
BYTE normalize(int value)
{
    if (value > 255)
    {
        return 255;
    }
    else
    {
        return value;
    }

}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int new_rgbtBlue = round((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue));
            int new_rgbtGreen = round((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue));
            int new_rgbtRed = round((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue));

            image[i][j].rgbtBlue = normalize(new_rgbtBlue);
            image[i][j].rgbtGreen = normalize(new_rgbtGreen);
            image[i][j].rgbtRed = normalize(new_rgbtRed);

        }
    }
}

// Swaps to values of type RGBTRIPLE
void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
    RGBTRIPLE tmp = *a;
    *a = *b;
    *b = tmp;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j], &image[i][width - 1 - j]);
        }
    }
}

// Check if pixel is in boundaries of the image
bool is_in_bounds(int i, int j, int height, int width)
{
    return i >= 0 && i < height && j >= 0 && j < width;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];

    // Count total values of neighbors pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int total_green = 0;
            int total_blue = 0;
            int total_red = 0;
            int neighbors_count = 0;

            total_green += image[i][j].rgbtGreen;
            total_blue += image[i][j].rgbtBlue;
            total_red += image[i][j].rgbtRed;
            neighbors_count ++;

            // Add if in bounds
            if (is_in_bounds(i - 1, j - 1, height, width))
            {
                total_green += image[i - 1][j - 1].rgbtGreen;
                total_blue += image[i - 1][j - 1].rgbtBlue;
                total_red += image[i - 1][j - 1].rgbtRed;
                neighbors_count ++;
            }

            // Add if in bounds
            if (is_in_bounds(i - 1, j, height, width))
            {
                total_green += image[i - 1][j].rgbtGreen;
                total_blue += image[i - 1][j].rgbtBlue;
                total_red += image[i - 1][j].rgbtRed;
                neighbors_count ++;
            }

            // Add if in bounds
            if (is_in_bounds(i - 1, j + 1, height, width))
            {
                total_green += image[i - 1][j + 1].rgbtGreen;
                total_blue += image[i - 1][j + 1].rgbtBlue;
                total_red += image[i - 1][j + 1].rgbtRed;
                neighbors_count ++;
            }

            // Add if in bounds
            if (is_in_bounds(i, j - 1, height, width))
            {
                total_green += image[i][j - 1].rgbtGreen;
                total_blue += image[i][j - 1].rgbtBlue;
                total_red += image[i][j - 1].rgbtRed;
                neighbors_count ++;
            }

            // Add if in bounds
            if (is_in_bounds(i, j + 1, height, width))
            {
                total_green += image[i][j + 1].rgbtGreen;
                total_blue += image[i][j + 1].rgbtBlue;
                total_red += image[i][j + 1].rgbtRed;
                neighbors_count ++;
            }

            // Add if in bounds
            if (is_in_bounds(i + 1, j - 1, height, width))
            {
                total_green += image[i + 1][j - 1].rgbtGreen;
                total_blue += image[i + 1][j - 1].rgbtBlue;
                total_red += image[i + 1][j - 1].rgbtRed;
                neighbors_count ++;
            }

            // Add if in bounds
            if (is_in_bounds(i + 1, j, height, width))
            {
                total_green += image[i + 1][j].rgbtGreen;
                total_blue += image[i + 1][j].rgbtBlue;
                total_red += image[i + 1][j].rgbtRed;
                neighbors_count ++;
            }

            // Add if in bounds
            if (is_in_bounds(i + 1, j + 1, height, width))
            {
                total_green += image[i + 1][j + 1].rgbtGreen;
                total_blue += image[i + 1][j + 1].rgbtBlue;
                total_red += image[i + 1][j + 1].rgbtRed;
                neighbors_count ++;
            }

            // Count an average
            new_image[i][j].rgbtGreen = round((float) total_green / (float) neighbors_count);
            new_image[i][j].rgbtBlue = round((float) total_blue / (float) neighbors_count);
            new_image[i][j].rgbtRed = round((float) total_red / (float) neighbors_count);

        }
    }

    // Update current image with blur effect
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }
}
