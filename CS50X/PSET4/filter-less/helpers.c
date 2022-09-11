#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int i = 0;
    int j = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            float average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
            j ++;
        }
        i ++;
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int i = 0;
    int j = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            float sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            float sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            float sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
            j ++;
        }
        i ++;
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int i = 0;
    int j = 0;
    RGBTRIPLE buffer;
    while (i < height)
    {
        j = 0;
        while (j < width / 2)
        {
            //pour liquid into spare glass, then refill
            buffer.rgbtRed = image[i][j].rgbtRed;
            buffer.rgbtGreen = image[i][j].rgbtGreen;
            buffer.rgbtBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            image[i][width - j - 1].rgbtRed = buffer.rgbtRed;
            image[i][width - j - 1].rgbtGreen = buffer.rgbtGreen;
            image[i][width - j - 1].rgbtBlue = buffer.rgbtBlue;
            j ++;
        }
        i ++;
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int i = 0;
    int j = 0;
    RGBTRIPLE copy[height][width];

    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            //create spare copy to preserve data
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            j ++;
        }
        i ++;
    }

    i = 0;
    j = 0;

    //average values
    float mRed = 0;
    float mGreen = 0;
    float mBlue = 0;

    //9 pixel pass
    int filter_i = 0;
    int filter_j = 0;
    int pixel_count = 0;

    while (i < height)
    {
        j = 0;

        while (j < width)
        {
            mRed = 0;
            mGreen = 0;
            mBlue = 0;
            pixel_count = 0;

            //move over grid of pixels surrounding target
            for (filter_i = i - 1; filter_i < i + 2; filter_i ++)
            {

                for (filter_j = j - 1; filter_j < j + 2; filter_j ++)
                {
                    if (filter_i < height && filter_i >= 0 && filter_j < height && filter_j >= 0)
                    {
                        mRed += copy[filter_i][filter_j].rgbtRed;
                        mGreen += copy[filter_i][filter_j].rgbtGreen;
                        mBlue += copy[filter_i][filter_j].rgbtBlue;
                        pixel_count ++;
                    }
                }
            }
            //average the total colour values
            mRed = round(mRed / pixel_count);
            mGreen = round(mGreen / pixel_count);
            mBlue = round(mBlue / pixel_count);

            image[i][j].rgbtRed = mRed;
            image[i][j].rgbtGreen = mGreen;
            image[i][j].rgbtBlue = mBlue;

            j ++;
        }
        i++;
    }

    return;
}
