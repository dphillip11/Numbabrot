// ****************************************************************************
/// @file       Mandelbrot.h
/// @brief      Creates a image file with a mandelbrot fractal.
// ****************************************************************************

#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <cmath>
#include <complex>
#include <vector>
#include <string>

class Mandelbrot
{
public:
    Mandelbrot(int width, int height, int iterations, int zsquared_max, int zoom);
    
    void CalculateMandelbrot();
    void WriteImage(const std::string& filename);
    
    void set_offset(double re_offset, double im_offset) {
        m_re_offset = re_offset;
        m_im_offset = im_offset;
    }
private:

    int CalculateMandelValue(std::complex<double> z);
    const int m_width;
    const int m_height;

    //A 2d vector of ints.
    std::vector<std::vector<int>> m_image;
    const int m_ITERATIONS;
    const int m_ZABS_MAX;
    const int m_ZOOM;

    double m_re_offset = 0;
    double m_im_offset = 0;
};

#endif // MANDELBROT_H