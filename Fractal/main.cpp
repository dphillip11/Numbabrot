// ****************************************************************************
/// @file       Main.cpp
/// @brief      Creates a image file of the given fractal algorithm.
// ****************************************************************************

#include <iostream>
#include "Mandelbrot.h"

int main(int argc, char* argv[])
{   
    int image_size = 4000;
    int iterations = 360;
    int zsquared_max = 4;
    int zoom = 1e6;

    //Optionally read in values from argv
    //Parse arguments image_size, iterations, zsquared_max, zoom
    if (argc > 1)
    {
       //display usage
         std::cout << "Usage: " << argv[0] << " [image_size] [iterations] [zsquared_max] [zoom]" << std::endl;

         //check correct number of arguments provided
            if (argc != 5)
            {
                std::cout << "Incorrect number of arguments provided." << std::endl;
                std::cout << "Using default values as : image_size " << image_size 
                << " iterations " << iterations << " zsquared_max " << zsquared_max 
                << " zoom " << zoom << std::endl; 
            }
            else
            {
                image_size = atoi(argv[1]);
                iterations = atoi(argv[2]);
                zsquared_max = atoi(argv[3]);
                zoom = atoi(argv[4]);
            }
    }


    Mandelbrot mandelbrot(image_size, image_size, iterations, zsquared_max, zoom);
    mandelbrot.set_offset(-1.94161, -0.000229);
    mandelbrot.CalculateMandelbrot();
    mandelbrot.WriteImage("mandelbrot.csv");

    return 0;
}