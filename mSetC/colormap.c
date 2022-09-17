#include "bmp.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

//array of linearly spaced values
int RED[COLORS];
int GREEN[COLORS];
int BLUE[COLORS];

//fill array of linearly spaced values
void initialise_colormap()
{
    // random seed
    // time_t t;
    // srand((unsigned) time(&t));

    // Select from 0-180 degrees
    int increment = 180 / (COLORS - 1);

    // randomly offset sin waves
    int offset_r =0; //rand() % 360;
    int offset_g =30; //rand() % 360;
    int offset_b =60;//rand() % 360;

    for (int i = 0; i < COLORS; i ++)
    {
        RED[i] = 125 * (sin((increment * i) + offset_r)+1);
        GREEN[i] = 125 * (sin((increment * i) + offset_b) +1);
        BLUE[i] = 125 * (sin((increment * i) + offset_g)+1);
    }
}

//select values from array and output them as RGBTriple
RGBTRIPLE colormap(int colorvalue)
{
    RGBTRIPLE pixel;
    pixel.rgbtRed = RED[colorvalue];
    pixel.rgbtBlue = BLUE[colorvalue];
    pixel.rgbtGreen = GREEN[colorvalue];

    return pixel;
}