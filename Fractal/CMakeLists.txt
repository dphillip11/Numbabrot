cmake_minimum_required(VERSION 3.10)
project(fractal VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

ADD_EXECUTABLE(fractal
    ./main.cpp
    ./Mandelbrot.cpp
    ./Mandelbrot.h
)