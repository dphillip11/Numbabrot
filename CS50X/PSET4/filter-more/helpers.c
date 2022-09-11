#include "helpers.h"
#include <math.h>




// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float averageRGB = 0;
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            averageRGB = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = averageRGB;
            image[i][j].rgbtGreen = averageRGB;
            image[i][j].rgbtBlue = averageRGB;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer;

    for (int i = 0; i < height; i ++)
    {
        //only go half way across image
        for (int j = 0; j < (width + 1) / 2; j ++)
        {
            //swap pixels from the front half horizontally to the back half
            buffer = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = buffer;

        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //count pixels surrounding each pixel
    int pixel_count = 0;
    // add up RGB values
    float totalRed;
    float totalGreen;
    float totalBlue;

    //create copy so calculation value don't change
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

    //move through all pixels
    for (i = 0; i < height; i ++)
    {
        for (j = 0; j < width; j ++)
        {
            pixel_count = 0;
            totalRed = 0;
            totalGreen = 0;
            totalBlue = 0;

            //move in a grid around each pixel
            for (int k = i - 1; k < i + 2; k ++)
            {
                for (int l = j - 1; l < j + 2; l ++)
                {
                    //avoid going over edges
                    if (k > -1 && k < height && l > -1 && l < width)
                    {
                        //sum colour values
                        pixel_count ++;
                        totalRed += copy[k][l].rgbtRed;
                        totalGreen += copy[k][l].rgbtGreen;
                        totalBlue += copy[k][l].rgbtBlue;
                    }
                }

            }
            //average RGB values
            image[i][j].rgbtRed = round(totalRed / pixel_count);
            image[i][j].rgbtGreen = round(totalGreen / pixel_count);
            image[i][j].rgbtBlue = round(totalBlue / pixel_count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
//structure for converting RGBtriple to float values
    typedef struct
    {
        float R;
        float G;
        float B;
    }
    totalRGB;

    //kernels
    int Gx[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int Gy[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    //totals from kernels, much larger than 255 each
    totalRGB TotalGx;
    totalRGB TotalGy;

    //sqrt(sum of gx^2 + gy^2)
    totalRGB GxGy;

    //create copy so calculation values don't change
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

    //move through each pixel

    for (i = 0; i < height; i ++)
    {
        for (j = 0; j < width; j ++)
        {
            //zero totals for each pixel
            TotalGx.R = 0;
            TotalGx.G = 0;
            TotalGx.B = 0;
            TotalGy.R = 0;
            TotalGy.G = 0;
            TotalGy.B = 0;

            //move through pixels
            for (int k = 0; k < 3; k ++)
            {
                for (int l = 0; l < 3; l ++)
                {
                    //avoid going over edges
                    if (i - 1 + k > -1 && i - 1 + k < height && j - 1 + l > -1 && j - 1 + l < width)
                    {
                        //multiply kernel value by pixel value from preserved copy
                        TotalGx.R += Gx[(3 * k) + l] * (copy[i - 1 + k][j - 1 + l].rgbtRed);
                        TotalGx.G += Gx[(3 * k) + l] * (copy[i - 1 + k][j - 1 + l].rgbtGreen);
                        TotalGx.B += Gx[(3 * k) + l] * (copy[i - 1 + k][j - 1 + l].rgbtBlue);
                        TotalGy.R += Gy[(3 * k) + l] * (copy[i - 1 + k][j - 1 + l].rgbtRed);
                        TotalGy.G += Gy[(3 * k) + l] * (copy[i - 1 + k][j - 1 + l].rgbtGreen);
                        TotalGy.B += Gy[(3 * k) + l] * (copy[i - 1 + k][j - 1 + l].rgbtBlue);
                    }
                }
            }
            //sum of squares
            GxGy.R = (TotalGx.R * TotalGx.R) + (TotalGy.R * TotalGy.R);
            GxGy.G = (TotalGx.G * TotalGx.G) + (TotalGy.G * TotalGy.G);
            GxGy.B = (TotalGx.B * TotalGx.B) + (TotalGy.B * TotalGy.B);
            //round sqrt
            GxGy.R = round(sqrt(GxGy.R));
            GxGy.G = round(sqrt(GxGy.G));
            GxGy.B = round(sqrt(GxGy.B));
            //set extreme values to 255
            if (GxGy.R > 255)
            {
                GxGy.R = 255;
            }
            if (GxGy.G > 255)
            {
                GxGy.G = 255;
            }
            if (GxGy.B > 255)
            {
                GxGy.B = 255;
            }
            //apply filtered pixel to image
            image[i][j].rgbtRed = GxGy.R;
            image[i][j].rgbtGreen = GxGy.G;
            image[i][j].rgbtBlue = GxGy.B;
        }
    }
    return;
}


