#include "libs/ppm_io.h"

#include <iostream>

int main(int argc, char ** argv)
{
    PPM ppmIn;
    int status;

    std::cout << "Reading PPM images from " << argv[1] << "..." << std::endl;

    status = ppmIn.read(argv[1]);
    if (status != 0)
    {
        std::cout << "Reading PPM image failed." << std::endl;
        return 1;
    }
    std::cout << "Reading PPM image successful." << std::endl;

    // Test copy constructor
    std::cout << "Testing copy constructor..." << "..." << std::endl;
    
    PPM ppmOut = ppmIn;

    std::cout << "Writing PPM images to " << argv[2]  << "..." << std::endl;
    status = ppmOut.write(argv[2]);

    if (status != 0)
    {
        std::cout << "Writing PPM images failed." << std::endl;
        return 1;
    }
    std::cout << "Writing PPM image successful." << std::endl;

    // Test assign operator
    std::cout << "Testing assign operator..." << std::endl;
    ppmOut = ppmIn;

    std::cout << "Writing PPM images to " << argv[2]  << "..." << std::endl;
    status = ppmOut.write(argv[2]);

    if (status != 0)
    {
        std::cout << "Writing PPM images failed." << std::endl;
        return 1;
    }
    std::cout << "Writing PPM image successful." << std::endl;

    // Check Equivalence
    PPM ppmIn2(argv[2]);

    if (ppmIn == ppmIn2)
    {
        std::cout << "PPM image in and out are the same." << std::endl;
    }
    else
    {
        std::cout << "PPM image in and out are not the same!" << std::endl;
    }
    
    return 0;
}