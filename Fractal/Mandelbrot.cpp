// ****************************************************************************
/// @file       Mandelbrot.cpp
/// @brief      Creates a image file with a mandelbrot fractal.
// ****************************************************************************

#include "Mandelbrot.h"
#include <fstream>
#include <iostream>

Mandelbrot::Mandelbrot(int width, int height, int iterations, int zabs_max, int zoom): 
m_width(width),
m_height(height),
m_ITERATIONS(iterations),
m_ZABS_MAX(zabs_max),
m_ZOOM(zoom)
{
    m_image.resize(height);
    for (int i = 0; i < height; i++)
    {
        m_image[i].resize(width);
    }
}

int Mandelbrot::CalculateMandelValue(std::complex<double> z)
{
    int iterations = 0;
    auto c = z;
    while (std::abs(z) < m_ZABS_MAX && iterations < m_ITERATIONS)
    {
        z = z * z + c;
        iterations++;
    }

    return iterations;
}

void Mandelbrot::CalculateMandelbrot()
{
    for (int i = 0; i < m_image.size(); i++)
    {
        std::cout << "Row " << i << " of " << m_image.size() << std::endl;
        for (int j = 0; j < m_image[i].size(); j++)
        {
				double y = (2 * (double)i) / (double)m_height;//gives a range from 0 to 2
				y = y - 1.0;//centres about origin
				y = y / m_ZOOM; //magnifies coordinates
				y = y + m_im_offset; //moves centre of magnification


				double x = (2 * (double)j) / (double)m_width;//gives a range from 0 to 2
				x = x - 1.0;//centres about origin
				x = x / m_ZOOM; //magnifies coordinates
				x = x + m_re_offset; //moves centre of magnification
                
                std::complex<double> z(x, y);
                m_image[i][j] = CalculateMandelValue(z);
        }
    }
}

void Mandelbrot::WriteImage(const std::string& filename)
{   
    //Outpit Vector to file
    std::ofstream outfile(filename);
    for (int i = 0; i < m_image.size(); i++)
    {
        for (int j = 0; j < m_image[i].size(); j++)
        {
            outfile << m_image[i][j] << "\n";
        }
    }

    outfile.close();
}