cmake_minimum_required(VERSION 3.0.0)

project(PPMIO VERSION 1.0.0)

set (CMAKE_CXX_STANDARD 11)

add_library(ppm_io SHARED
    ppm_io.h
    ppm_io.cpp)