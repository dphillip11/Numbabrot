//Edge detection using sobel operator

//take zoom, operate on global image variable

#include <math.h>

coordinate reposition(double zoom)
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
    RGBTRIPLE copy[SIZE][SIZE];

    while (i < SIZE)
    {
        j = 0;
        while (j < SIZE)
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
    //r = r + 1;//use this to output edge detection image
    //FILE *mask_image = create_bitmap(r);

    int bright_i = SIZE / 2;
    int bright_j = SIZE / 2;
    int brightest = 0;

    for (i = 0; i < SIZE; i ++)
    {
        for (j = 0; j < SIZE; j ++)
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
                    if (i - 1 + k > -1 && i - 1 + k < SIZE && j - 1 + l > -1 && j - 1 + l < SIZE)
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

            //track brightest pixel
            if((GxGy.R + GxGy.G + GxGy.B) > brightest)
            {
                brightest = GxGy.R + GxGy.G + GxGy.B;
                bright_i = i;
                bright_j = j;
            }

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
            //fwrite(&image[i][j], sizeof(RGBTRIPLE), 1, mask_image);
        }
    }
    //fclose(mask_image);

    coordinate p;

    //pixel offset of brightest pixel
    p.x = bright_i + 1.5 - (SIZE / 2);
    p.y = bright_j + 0.5 - (SIZE / 2);
    //size of image is 1 / zoom, pixel is 1/size
    p.x = p.x / (zoom * SIZE);
    p.y = p.y / (zoom * SIZE);

    for (int m = 0; m < 9; m ++)
    {
        Gx[m] = 0;
        Gy[m] = 0;
    }

    return p;
}
