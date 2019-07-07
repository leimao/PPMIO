cmake_minimum_required(VERSION 3.0.0)

project(PPMIO-DEMO VERSION 1.0.0)

set (CMAKE_CXX_STANDARD 11)

add_subdirectory(libs)

add_executable(ppm_io_demo ppm_io_demo.cpp)
target_link_libraries(ppm_io_demo PRIVATE ppm_io)